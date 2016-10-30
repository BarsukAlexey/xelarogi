#include "handbookdialog.h"
#include "ui_handbookdialog.h"

#include <QDebug>

QSqlRecord HandbookDialog::m_record;

HandbookDialog::HandbookDialog(QString tableName, QString tableRusName,
                               const QSqlDatabase &database,
                               QWidget *parent,
                               QStringList hiddenColumns):

    QDialog(parent),
    ui(new Ui::HandbookDialog),
    m_database(database),
    mHiddenColumns(hiddenColumns)
{
    ui->setupUi(this);

    ui->label->setText(tableRusName);
    this->setWindowTitle("Редактирование справочника: " + tableRusName);

//    QMap<QString, QString> rusFieldNames = DataBaseExpert::fieldTranslationMap(m_database);
//    auto ralTablesForFields = DataBaseExpert::ralationTablesForFields(m_database);
    QMap<QString, std::tuple<QString, QString> > map = DBUtils::get_NAME_RUS__RELATION_TABLE_NAME();

    m_record = database.record(tableName);

    QSqlRelationalTableModel * model = new QSqlRelationalTableModel(0, database);
    model->setTable(tableName);
    for (int i = 0; i < m_record.count(); ++i)
    {
        QString fieldName = m_record.fieldName(i);
        if (fieldName.right(3) == "_FK")
        {
            model->setRelation(i, QSqlRelation(std::get<1>(map[fieldName]), "UID", "NAME"));
        }
    }
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    for (int i = 0; i < m_record.count(); ++i)
    {
        model->setHeaderData(i, Qt::Horizontal, std::get<0>(map[m_record.fieldName(i)]));
    }

    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new HandlebookRelationDelegate(ui->tableView));

    for (int i = 0; i < m_record.count(); ++i)
    {
        if (mHiddenColumns.contains(m_record.fieldName(i), Qt::CaseInsensitive))
        {
            ui->tableView->setColumnHidden(i, true);
        }
    }

    connect(ui->btnInsert, &QPushButton::clicked, [model]()
    {
        model->insertRow(model->rowCount());
    });
    connect(ui->btnSave, &QPushButton::clicked, [model]()
    {
        if (!model->submitAll())
            QMessageBox::critical(0, "", model->lastError().text());
        model->select();
    });
    connect(ui->btnRevert, &QPushButton::clicked, [model]()
    {
        model->revertAll();
    });
    connect(ui->btnExit, &QPushButton::clicked, [this]()
    {
        this->accept();
    });

    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);


    connect(ui->tableView, &QTableView::customContextMenuRequested, [this, &tableName, model] (const QPoint& pos)
    {
        QMenu * contextMenu = new QMenu(tr("Выбор действия со строкой"), ui->tableView);

        QAction* insertAction = new QAction(tr("Добавить"), contextMenu);
        contextMenu->addAction(insertAction);
        connect(insertAction, &QAction::triggered, [this, &model] ()
        {
            model->insertRow(model->rowCount());
        });

        QAction * delAction = new QAction(tr("Удалить"), contextMenu);
        contextMenu->addAction(delAction);
        connect(delAction, &QAction::triggered, [this, &pos, &tableName, model] ()
        {
            QModelIndex index = ui->tableView->indexAt(pos);
            model->removeRow(index.row());
            model->submitAll();
        });


        contextMenu->exec(ui->tableView->viewport()->mapToGlobal(pos));
    });



//    connect(ui->label_2, &QLabel::linkActivated, [this]()
//    {
//        WebReportDialog dlg(this->ui->label_2->text(), this);
//        dlg.exec();
//    });
    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);
    if (parent == 0)
        setWindowFlags(windowFlags() | Qt::WindowMinMaxButtonsHint);
    ui->tableView->resizeColumnsToContents();
}

HandbookDialog::~HandbookDialog()
{
    delete ui;
}


void HandlebookRelationDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (HandbookDialog::m_record.fieldName(index.column()).contains("IS_", Qt::CaseSensitive))
    {
        if (index.data().toInt() > 0)
        {
            painter->drawText(option.rect, "Да");
        }
        else
        {
            painter->drawText(option.rect, "Нет");
        }
        //painter->save();
    }
    else if (HandbookDialog::m_record.fieldName(index.column()).contains("DATE", Qt::CaseSensitive))
    {
        painter->drawText(option.rect, Qt::AlignHCenter | Qt::AlignVCenter, QDate::fromString(index.data().toString(), "yyyy-MM-dd").toString("dd.MM.yyyy"));
    }
    else
    {
        QItemDelegate::paint(painter, option, index);
    }
}

QWidget *HandlebookRelationDelegate::createEditor(QWidget *aParent,
                                                  const QStyleOptionViewItem &option,
                                                  const QModelIndex &index) const
{
    const QSqlRelationalTableModel *sqlModel = qobject_cast<const QSqlRelationalTableModel *>(index.model());
    QSqlTableModel *childModel = sqlModel ? sqlModel->relationModel(index.column()) : 0;
    if (!childModel)
    {
        if (HandbookDialog::m_record.fieldName(index.column()).contains("IS_", Qt::CaseSensitive))
        {
            QCheckBox * checkBox = new QCheckBox(aParent);
            checkBox->setChecked(index.data().toInt() > 0);
            return checkBox;
        }
        else if (HandbookDialog::m_record.fieldName(index.column()).contains("DATE", Qt::CaseSensitive))
        {
            QDateEdit * dateEdit = new QDateEdit(aParent);
            dateEdit->setDate(QDate::fromString(index.data().toString(), "yyyy-MM-dd"));
            return dateEdit;
        }
        else
        {
            return QItemDelegate::createEditor(aParent, option, index);
        }
    }
    else
    {
        if (HandbookDialog::m_record.fieldName(index.column()) == "REGION_FK")
        {
            int countryColumn = -1;
            for (int i = 0; i < HandbookDialog::m_record.count(); ++i)
            {
                if (HandbookDialog::m_record.fieldName(i) == "COUNTRY_FK")
                {
                    countryColumn = i;
                }
            }
            QModelIndex countryIndex = sqlModel->index(index.row(), countryColumn);
            QString countryName = countryIndex.data(Qt::DisplayRole).toString();

            //sqlModel->relationModel(countryIndex);

            QString countryFK = "";
            QSqlQuery query;
            query.prepare("SELECT * FROM COUNTRIES WHERE NAME = ?");
            query.bindValue(0, countryName);
            if (query.exec() && query.next())
            {
                countryFK = query.value("UID").toString();
            }
            query.clear();



            QSqlTableModel *regionModel = new QSqlTableModel(aParent);
            regionModel->setTable(childModel->tableName());
            regionModel->setFilter("COUNTRY_FK = " + countryFK);
            regionModel->select();
            QComboBox *combo = new QComboBox(aParent);
            combo->setModel(regionModel);
            combo->setModelColumn(regionModel->fieldIndex("NAME"));
            combo->installEventFilter(const_cast<HandlebookRelationDelegate *>(this));
            qDebug() << "Here: ";

//            QComboBox *combo = new QComboBox(aParent);
//            query.prepare("SELECT * REGIONS WHERE COUNTRY_FK = " + countryFK);
//            QSqlTableModel* regionModel = new QSqlTableModel;
//            regionModel->setTable("REGIONS");
//            regionModel->setFilter("COUNTRY_FK = " + countryFK);
//            regionModel->select();
//            combo->setModel(regionModel);
//            combo->setModelColumn(regionModel->fieldIndex("NAME"));
//            combo->installEventFilter(const_cast<HandlebookRelationDelegate *>(this));

            return combo;
        }
        else if (HandbookDialog::m_record.fieldName(index.column()) == "REGION_UNIT_FK")
        {
            int regionColumn = -1;
            for (int i = 0; i < HandbookDialog::m_record.count(); ++i)
            {
                if (HandbookDialog::m_record.fieldName(i) == "REGION_FK")
                {
                    regionColumn = i;
                }
            }
            QModelIndex regionIndex = sqlModel->index(index.row(), regionColumn);
            QString regionName = regionIndex.data(Qt::DisplayRole).toString();

            QString regionFK = "";
            QSqlQuery query;
            query.prepare("SELECT * FROM REGIONS WHERE NAME = ?");
            query.bindValue(0, regionName);
            if (query.exec() && query.next())
            {
                regionFK = query.value("UID").toString();
            }
            query.clear();

            QComboBox *combo = new QComboBox(aParent);
            query.prepare("SELECT * REGION_UNITS WHERE REGION_FK = " + regionFK);
            QSqlTableModel* regionModel = new QSqlTableModel;
            regionModel->setTable("REGION_UNITS");
            regionModel->setFilter("REGION_FK = " + regionFK);
            regionModel->select();
            combo->setModel(regionModel);
            combo->setModelColumn(regionModel->fieldIndex("NAME"));
            combo->installEventFilter(const_cast<HandlebookRelationDelegate *>(this));

            return combo;
        }
        else
        {
            QComboBox *combo = new QComboBox(aParent);
            combo->setModel(childModel);
            combo->setModelColumn(childModel->fieldIndex(sqlModel->relation(index.column()).displayColumn()));
            combo->installEventFilter(const_cast<HandlebookRelationDelegate *>(this));

            return combo;
        }
    }
}

void HandlebookRelationDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (!index.isValid())
        return;

    QSqlRelationalTableModel *sqlModel = qobject_cast<QSqlRelationalTableModel *>(model);
    QSqlTableModel *childModel = sqlModel ? sqlModel->relationModel(index.column()) : 0;
    QComboBox *combo = qobject_cast<QComboBox *>(editor);

    if (HandbookDialog::m_record.fieldName(index.column()) == "REGION_FK")
    {
        childModel = qobject_cast<QSqlTableModel *>(combo->model());
    }
    else if (HandbookDialog::m_record.fieldName(index.column()) == "REGION_UNIT_FK")
    {
        childModel = qobject_cast<QSqlTableModel *>(combo->model());
    }

    if (!sqlModel || !childModel || !combo) {
        if (HandbookDialog::m_record.fieldName(index.column()).contains("IS_", Qt::CaseSensitive))
        {
            QCheckBox * checkBox = qobject_cast<QCheckBox *>(editor);
            sqlModel->setData(index, checkBox->isChecked(), Qt::DisplayRole);
            sqlModel->setData(index, checkBox->isChecked(), Qt::EditRole);
            return;
        }
        else if (HandbookDialog::m_record.fieldName(index.column()).contains("DATE_", Qt::CaseSensitive))
        {
            QDateEdit * dateEdit = qobject_cast<QDateEdit *>(editor);
            sqlModel->setData(index, dateEdit->date().toString("yyyy-MM-dd"), Qt::DisplayRole);
            sqlModel->setData(index, dateEdit->date().toString("yyyy-MM-dd"), Qt::EditRole);
            return;
        }
        else
        {
            QItemDelegate::setModelData(editor, model, index);
            return;
        }
    }

    int currentItem = combo->currentIndex();
    int childColIndex  = childModel->fieldIndex(sqlModel->relation(index.column()).displayColumn());
    int childEditIndex = childModel->fieldIndex(sqlModel->relation(index.column()).indexColumn());
    sqlModel->setData(index,
            childModel->data(childModel->index(currentItem, childColIndex), Qt::DisplayRole),
            Qt::DisplayRole);
    sqlModel->setData(index,
            childModel->data(childModel->index(currentItem, childEditIndex), Qt::EditRole),
            Qt::EditRole);
}
