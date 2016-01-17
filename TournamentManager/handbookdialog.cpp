#include "handbookdialog.h"
#include "ui_handbookdialog.h"

#include <QDebug>

QSqlRecord HandbookDialog::m_record;

HandbookDialog::HandbookDialog(QString tableName, QString tableRusName, const QSqlDatabase &database, QWidget *parent) :
    m_database(database),
    QDialog(parent),
    ui(new Ui::HandbookDialog)
{
    ui->setupUi(this);

    ui->label->setText(tableRusName);
    this->setWindowTitle("Редактирование справочника: " + tableRusName);

    QMap<QString, QString> rusFieldNames = DataBaseExpert::fieldTranslationMap(m_database);
    auto ralTablesForFields = DataBaseExpert::ralationTablesForFields(m_database);
    m_record = database.record(tableName);

    QSqlRelationalTableModel * model = new QSqlRelationalTableModel(0, database);
    model->setTable(tableName);
    for (int i = 0; i < m_record.count(); ++i)
    {
        QString fieldName = m_record.fieldName(i);
        if (fieldName.size() > 3 && fieldName.right(3) == "_FK")
        {
            model->setRelation(i, QSqlRelation(ralTablesForFields[fieldName], "UID", "NAME"));
        }
    }
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //model->removeColumn(0);
    model->select();

    for (int i = 0; i < m_record.count(); ++i)
    {
        model->setHeaderData(i, Qt::Horizontal, rusFieldNames[m_record.fieldName(i)]);
    }

    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new MySqlRelationDelegate(ui->tableView));

    connect(ui->btnInsert, &QPushButton::clicked, [model]()
    {
        model->insertRow(model->rowCount());
    });
    connect(ui->btnSave, &QPushButton::clicked, [model]()
    {
        if (!model->submitAll())
            qDebug() << model->lastError().text();
    });
    connect(ui->btnRevert, &QPushButton::clicked, [model]()
    {
        model->revertAll();
    });
    connect(ui->btnExit, &QPushButton::clicked, [this]()
    {
        this->accept();
    });

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);






//    connect(ui->label_2, &QLabel::linkActivated, [this]()
//    {
//        WebReportDialog dlg(this->ui->label_2->text(), this);
//        dlg.exec();
//    });
}

HandbookDialog::~HandbookDialog()
{
    delete ui;
}


void MySqlRelationDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
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
    else if (HandbookDialog::m_record.fieldName(index.column()).contains("DATE_", Qt::CaseSensitive))
    {
        painter->drawText(option.rect, QDate::fromString(index.data().toString(), "yyyy-MM-dd").toString("dd.MM.yyyy"));
    }
    else
    {
        QItemDelegate::paint(painter, option, index);
    }
}

QWidget *MySqlRelationDelegate::createEditor(QWidget *aParent, const QStyleOptionViewItem &option, const QModelIndex &index) const
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
        else if (HandbookDialog::m_record.fieldName(index.column()).contains("DATE_", Qt::CaseSensitive))
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

    QComboBox *combo = new QComboBox(aParent);
    combo->setModel(childModel);
    combo->setModelColumn(childModel->fieldIndex(sqlModel->relation(index.column()).displayColumn()));
    combo->installEventFilter(const_cast<MySqlRelationDelegate *>(this));

    return combo;
}

void MySqlRelationDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (!index.isValid())
        return;

    QSqlRelationalTableModel *sqlModel = qobject_cast<QSqlRelationalTableModel *>(model);
    QSqlTableModel *childModel = sqlModel ? sqlModel->relationModel(index.column()) : 0;
    QComboBox *combo = qobject_cast<QComboBox *>(editor);
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
    int childColIndex = childModel->fieldIndex(sqlModel->relation(index.column()).displayColumn());
    int childEditIndex = childModel->fieldIndex(sqlModel->relation(index.column()).indexColumn());
    sqlModel->setData(index,
            childModel->data(childModel->index(currentItem, childColIndex), Qt::DisplayRole),
            Qt::DisplayRole);
    sqlModel->setData(index,
            childModel->data(childModel->index(currentItem, childEditIndex), Qt::EditRole),
            Qt::EditRole);
}
