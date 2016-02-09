#include "createtournamentordersdialog.h"
#include "ui_createtournamentordersdialog.h"

QSqlRecord CreateTournamentOrdersDialog::m_record;

CreateTournamentOrdersDialog::CreateTournamentOrdersDialog(const QSqlDatabase &database,
                                                           long long tournamentUID,
                                                           QWidget *parent,
                                                           QStringList hiddenColumns
                                                           ):
    m_database(database),
    mTournamentUID(tournamentUID),
    mHiddenColumns(hiddenColumns),
    QDialog(parent),
    ui(new Ui::CreateTournamentOrdersDialog)
{
    ui->setupUi(this);

    QString tournamentName = "";
    QSqlQuery query("SELECT * FROM TOURNAMENTS WHERE UID = " + QString::number(tournamentUID));
    if (query.exec() && query.next())
    {
        tournamentName = query.value("NAME").toString();
    }
    ui->label->setText("Заявки на турнир \"" + tournamentName + "\"");

    QMap<QString, QString> rusFieldNames = DataBaseExpert::fieldTranslationMap(m_database);
    auto ralTablesForFields = DataBaseExpert::ralationTablesForFields(m_database);
    m_record = database.record("ORDERS");

    QSqlRelationalTableModel * model = new QSqlRelationalTableModel(0, database);
    model->setTable("ORDERS");
    for (int i = 0; i < m_record.count(); ++i)
    {
        QString fieldName = m_record.fieldName(i);
        if (fieldName.size() > 3 && fieldName.right(3) == "_FK")
        {
            model->setRelation(i, QSqlRelation(ralTablesForFields[fieldName], "UID", "NAME"));
        }
    }
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    QString allowTournamentCategories = "(-100";
    QSqlQuery categoriesQouery("SELECT UID FROM TOURNAMENT_CATEGORIES WHERE TOURNAMENT_FK = " + QString::number(tournamentUID));
    if (categoriesQouery.exec())
    {
        while (categoriesQouery.next())
        {
            allowTournamentCategories += ", " + categoriesQouery.value("UID").toString();
        }
    }
    allowTournamentCategories += ")";
    model->setFilter("TOURNAMENT_CATEGORY_FK IN " + allowTournamentCategories);

    model->select();

    for (int i = 0; i < m_record.count(); ++i)
    {
        model->setHeaderData(i, Qt::Horizontal, rusFieldNames[m_record.fieldName(i)]);
    }

    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new OrdersRelationDelegate(ui->tableView));

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

    ui->tableView->resizeColumnsToContents();


    connect(ui->tableView, &QTableView::customContextMenuRequested, [this, model] (const QPoint& pos)
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
        connect(delAction, &QAction::triggered, [this, &pos, model] ()
        {
            QModelIndex index = ui->tableView->indexAt(pos);
            model->removeRow(index.row());
            model->submitAll();
        });


        contextMenu->exec(ui->tableView->viewport()->mapToGlobal(pos));
    });

    connect(ui->loadBtn, &QPushButton::clicked, this, &CreateTournamentOrdersDialog::loadFromExcel);
}

CreateTournamentOrdersDialog::~CreateTournamentOrdersDialog()
{
    delete ui;
}

void CreateTournamentOrdersDialog::loadFromExcel()
{
    QAxObject* excel = new QAxObject( "Excel.Application", 0 );
    QAxObject* workbooks = excel->querySubObject( "Workbooks" );
    QAxObject* workbook = workbooks->querySubObject( "Open(const QString&)", "D:/orders.xlsx" );


    QAxObject* sheets = workbook->querySubObject( "Sheets" );
    int sheetCount = sheets->dynamicCall("Count()").toInt();

    for (int sheetNumber = 1; sheetNumber <= sheetCount; ++sheetNumber)
    {
        QAxObject* sheet = sheets->querySubObject( "Item( int )", sheetNumber );

        QAxObject* usedrange = sheet->querySubObject( "UsedRange");
        QAxObject * rows = usedrange->querySubObject("Rows");
        QAxObject * columns = usedrange->querySubObject("Columns");
        int intRowStart = usedrange->property("Row").toInt();
        int intColStart = usedrange->property("Column").toInt();
        int intCols = columns->property("Count").toInt();
        int intRows = rows->property("Count").toInt();

        QAxObject* c = sheet->querySubObject("Cells( int, int )", 7, 3);
        QString countryName = c->dynamicCall("Value()").toString();
        delete c;

        c = sheet->querySubObject("Cells( int, int )", 8, 3);
        QString regionName = c->dynamicCall("Value()").toString();
        delete c;

        for (int row = 15 ; row < intRowStart + intRows ; ++row) {

            QAxObject* cell = sheet->querySubObject( "Cells( int, int )", row, 2 );
            QVariant value = cell->dynamicCall( "Value()" );
            QString firstName = value.toString();
            delete cell;

            cell = sheet->querySubObject( "Cells( int, int )", row, 3 );
            value = cell->dynamicCall( "Value()" );
            QString secondName = value.toString();
            delete cell;

            cell = sheet->querySubObject( "Cells( int, int )", row, 4 );
            value = cell->dynamicCall( "Value()" );
            QString patronymic = value.toString();
            delete cell;

            cell = sheet->querySubObject( "Cells( int, int )", row, 5 );
            value = cell->dynamicCall( "Value()" );
            QString birthday = value.toString();
            delete cell;

            cell = sheet->querySubObject( "Cells( int, int )", row, 6 );
            value = cell->dynamicCall( "Value()" );
            QString weight = value.toString();
            delete cell;

            cell = sheet->querySubObject( "Cells( int, int )", row, 7 );
            value = cell->dynamicCall( "Value()" );
            QString gender = value.toString();
            delete cell;

            cell = sheet->querySubObject( "Cells( int, int )", row, 8 );
            value = cell->dynamicCall( "Value()" );
            QString category = value.toString();
            delete cell;

            cell = sheet->querySubObject( "Cells( int, int )", row, 9 );
            value = cell->dynamicCall( "Value()" );
            QString regionUnitName = value.toString();
            delete cell;

            cell = sheet->querySubObject( "Cells( int, int )", row, 10 );
            value = cell->dynamicCall( "Value()" );
            QString clubName = value.toString();
            delete cell;

            cell = sheet->querySubObject( "Cells( int, int )", row, 11 );
            value = cell->dynamicCall( "Value()" );
            QString sportKind = value.toString();
            delete cell;

            cell = sheet->querySubObject( "Cells( int, int )", row, 12 );
            value = cell->dynamicCall( "Value()" );
            QString coachName = value.toString();
            delete cell;



            //QSqlQuery query("INSERT INTO COUNTRIES(NAME, NAME_ENG, SHORTNAME, SHORTNAME_ENG) VALUES('" + name + "','" + nameEng + "','" + shortNameEng2 + "','" + shortNameEng3 + "')", m_database);
            //if (!query.exec())
            //    qDebug() << query.lastError().text() << query.lastQuery();
        }
    }

    // clean up and close up
    workbook->dynamicCall("Close()");
    delete workbook;
    excel->dynamicCall("Quit()");
    delete excel;
}


void OrdersRelationDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (CreateTournamentOrdersDialog::m_record.fieldName(index.column()).contains("DATE", Qt::CaseSensitive))
    {
        painter->drawText(option.rect, Qt::AlignHCenter | Qt::AlignVCenter, QDate::fromString(index.data().toString(), "yyyy-MM-dd").toString("dd.MM.yyyy"));
    }
    else
    {
        QItemDelegate::paint(painter, option, index);
    }
}

QWidget *OrdersRelationDelegate::createEditor(QWidget *aParent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const QSqlRelationalTableModel *sqlModel = qobject_cast<const QSqlRelationalTableModel *>(index.model());
    QSqlTableModel *childModel = sqlModel ? sqlModel->relationModel(index.column()) : 0;
    if (!childModel)
    {
        if (CreateTournamentOrdersDialog::m_record.fieldName(index.column()).contains("DATE", Qt::CaseSensitive))
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
        if (CreateTournamentOrdersDialog::m_record.fieldName(index.column()) == "REGION_FK")
        {
            int countryColumn = -1;
            for (int i = 0; i < CreateTournamentOrdersDialog::m_record.count(); ++i)
            {
                if (CreateTournamentOrdersDialog::m_record.fieldName(i) == "COUNTRY_FK")
                {
                    countryColumn = i;
                }
            }
            QModelIndex countryIndex = sqlModel->index(index.row(), countryColumn);
            QString countryName = countryIndex.data(Qt::DisplayRole).toString();

            QString countryFK = "";
            QSqlQuery query;
            query.prepare("SELECT * FROM COUNTRIES WHERE NAME = ?");
            query.bindValue(0, countryName);
            if (query.exec() && query.next())
            {
                countryFK = query.value("UID").toString();
            }
            query.clear();

            QComboBox *combo = new QComboBox(aParent);
            query.prepare("SELECT * REGIONS WHERE COUNTRY_FK = " + countryFK);
            QSqlTableModel* regionModel = new QSqlTableModel;
            regionModel->setTable("REGIONS");
            regionModel->setFilter("COUNTRY_FK = " + countryFK);
            regionModel->select();
            combo->setModel(regionModel);
            combo->setModelColumn(regionModel->fieldIndex("NAME"));
            combo->installEventFilter(const_cast<OrdersRelationDelegate *>(this));

            return combo;
        }
        else if (CreateTournamentOrdersDialog::m_record.fieldName(index.column()) == "REGION_UNIT_FK")
        {
            int regionColumn = -1;
            for (int i = 0; i < CreateTournamentOrdersDialog::m_record.count(); ++i)
            {
                if (CreateTournamentOrdersDialog::m_record.fieldName(i) == "REGION_FK")
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
            combo->installEventFilter(const_cast<OrdersRelationDelegate *>(this));

            return combo;
        }
        else
        {
            QComboBox *combo = new QComboBox(aParent);
            combo->setModel(childModel);
            combo->setModelColumn(childModel->fieldIndex(sqlModel->relation(index.column()).displayColumn()));
            combo->installEventFilter(const_cast<OrdersRelationDelegate *>(this));

            return combo;
        }
    }
}

void OrdersRelationDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (!index.isValid())
        return;

    QSqlRelationalTableModel *sqlModel = qobject_cast<QSqlRelationalTableModel *>(model);
    QSqlTableModel *childModel = sqlModel ? sqlModel->relationModel(index.column()) : 0;
    QComboBox *combo = qobject_cast<QComboBox *>(editor);

    if (CreateTournamentOrdersDialog::m_record.fieldName(index.column()) == "REGION_FK")
    {
        childModel = qobject_cast<QSqlTableModel *>(combo->model());
    }
    else if (CreateTournamentOrdersDialog::m_record.fieldName(index.column()) == "REGION_UNIT_FK")
    {
        childModel = qobject_cast<QSqlTableModel *>(combo->model());
    }

    if (!sqlModel || !childModel || !combo) {
        if (CreateTournamentOrdersDialog::m_record.fieldName(index.column()).contains("IS_", Qt::CaseSensitive))
        {
            QCheckBox * checkBox = qobject_cast<QCheckBox *>(editor);
            sqlModel->setData(index, checkBox->isChecked(), Qt::DisplayRole);
            sqlModel->setData(index, checkBox->isChecked(), Qt::EditRole);
            return;
        }
        else if (CreateTournamentOrdersDialog::m_record.fieldName(index.column()).contains("DATE_", Qt::CaseSensitive))
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
