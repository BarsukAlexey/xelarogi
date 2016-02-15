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

        long long countryUID = getCountryUID(countryName);
        long long regionUID = getRegionUID(regionName, countryUID);

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

            long long unitUID = getRegionUnitUID(regionUnitName, regionUID, countryUID);
            long long clubUID = getClubUID(clubName, countryUID, regionUID, unitUID);
            QStringList coachNameArgs = coachName.split(" ");
            coachName = "";
            for (const QString& arg: coachNameArgs)
            {
                if (arg.isEmpty()) continue;
                if (coachName.isEmpty() == false)
                {
                    coachName += " ";
                }
                coachName += arg;
            }

            // TODO check if exist
            QSqlQuery query;
            query.prepare(  "INSERT INTO ORDERS(FIRSTNAME, LASTNAME, PATRONYMIC, COUNTRY_FK, REGION_FK, REGION_UNIT_FK, BIRTHDAY, WEIGHT, SEX_FK, TOURNAMENT_CATEGORY_FK, TYPE_FK, CLUB_FK, COACH_FK) "
                            "VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"
                            );
            query.bindValue(0, firstName);
            query.bindValue(1, secondName);
            query.bindValue(2, patronymic);
            query.bindValue(3, countryUID);
            query.bindValue(4, regionUID);
            query.bindValue(5, unitUID);
            query.bindValue(6, QDate::fromString(birthday, "dd.MM.YYYY").toString("yyyy-MM-dd"));
            query.bindValue(7, weight.toDouble());
            query.bindValue(8, getGenderUID(gender));
            query.bindValue(9, getCategoryUID(category));
            query.bindValue(10, getTypeUID(sportKind));
            query.bindValue(11, clubUID);
            query.bindValue(12, getCoachUID(coachName, clubUID));

            if (query.exec()) ;
            else qDebug() << query.lastError().text();
        }
    }

    // clean up and close up
    workbook->dynamicCall("Close()");
    delete workbook;
    excel->dynamicCall("Quit()");
    delete excel;
}

long long CreateTournamentOrdersDialog::getCountryUID(QString countryName)
{
    QSqlQuery query;
    query.prepare("SELECT UID FROM COUNTRIES WHERE NAME = ?");
    query.bindValue(0, countryName);
    bool isFind = ( query.exec() && query.next() );
    if (isFind)
    {
        return query.value("UID").toLongLong();
    }
    else
    {
        query.clear();
        query.prepare("INSERT INTO COUNTRIES(NAME) VALUES(?)");
        query.bindValue(0, countryName);

        if (query.exec())
        {
            query.clear();
            return getCountryUID(countryName);
        }
        else
        {
            qDebug() << query.lastError().text();
            return -100;
        }
    }
}

long long CreateTournamentOrdersDialog::getRegionUID(QString regionName, long long countryUID)
{
    QSqlQuery query;
    query.prepare("SELECT UID FROM REGIONS WHERE NAME = ? AND COUNTRY_FK = ?");
    query.bindValue(0, regionName);
    query.bindValue(1, countryUID);
    bool isFind = ( query.exec() && query.next() );
    if (isFind)
    {
        return query.value("UID").toLongLong();
    }
    else
    {
        query.clear();
        query.prepare("INSERT INTO REGIONS(NAME, COUNTRY_FK) VALUES(?, ?)");
        query.bindValue(0, regionName);
        query.bindValue(1, countryUID);

        if (query.exec())
        {
            query.clear();
            return getRegionUID(regionName, countryUID);
        }
        else
        {
            qDebug() << query.lastError().text();
            return -100;
        }
    }
}

long long CreateTournamentOrdersDialog::getRegionUnitUID(QString unitName, long long regionUID, long long countryUID)
{
    QSqlQuery query;
    query.prepare("SELECT UID FROM REGION_UNITS WHERE NAME = ? AND REGION_FK = ?");
    query.bindValue(0, unitName);
    query.bindValue(1, regionUID);
    bool isFind = ( query.exec() && query.next() );
    if (isFind)
    {
        return query.value("UID").toLongLong();
    }
    else
    {
        query.clear();
        query.prepare("INSERT INTO REGION_UNITS(NAME, REGION_FK, COUNRY_FK) VALUES(?, ?, ?)");
        query.bindValue(0, unitName);
        query.bindValue(1, regionUID);
        query.bindValue(2, countryUID);

        if (query.exec())
        {
            query.clear();
            return getRegionUnitUID(unitName, regionUID, countryUID);
        }
        else
        {
            qDebug() << query.lastError().text();
            return -100;
        }
    }
}

long long CreateTournamentOrdersDialog::getGenderUID(QString genderName)
{
    QSqlQuery query;
    query.prepare("SELECT UID FROM SEXES WHERE NAME = ?");
    query.bindValue(0, genderName);
    bool isFind = ( query.exec() && query.next() );
    if (isFind)
    {
        return query.value("UID").toLongLong();
    }
    else
    {
        query.clear();
        query.prepare("INSERT INTO SEXES(NAME, SHORTNAME) VALUES(?, ?)");
        query.bindValue(0, genderName);
        query.bindValue(1, genderName.left(1).toUpper());

        if (query.exec())
        {
            query.clear();
            return getGenderUID(genderName);
        }
        else
        {
            qDebug() << query.lastError().text();
            return -100;
        }
    }
}

long long CreateTournamentOrdersDialog::getCategoryUID(QString categoryName)
{
    QSqlQuery query;
    query.prepare("SELECT UID FROM TOUNRAMENT_CATEGORIES WHERE NAME = ?");
    query.bindValue(0, categoryName);
    bool isFind = ( query.exec() && query.next() );
    if (isFind)
    {
        return query.value("UID").toLongLong();
    }
    else
    {
        query.clear();
        query.prepare("INSERT INTO TOURNAMENT_CATEGORIES(NAME, TOURNAMENT_FK) VALUES(?, ?)");
        query.bindValue(0, categoryName);
        query.bindValue(1, mTournamentUID);

        // TODO запросить диапазон возраста и веса ( + пол ? )

        if (query.exec())
        {
            query.clear();
            return getCategoryUID(categoryName);
        }
        else
        {
            qDebug() << query.lastError().text();
            return -100;
        }
    }
}

long long CreateTournamentOrdersDialog::getTypeUID(QString typeName)
{
    QSqlQuery query;
    query.prepare("SELECT UID FROM TYPES WHERE NAME = ?");
    query.bindValue(0, typeName);
    bool isFind = ( query.exec() && query.next() );
    if (isFind)
    {
        return query.value("UID").toLongLong();
    }
    else
    {
        query.clear();
        query.prepare("INSERT INTO TYPES(NAME) VALUES(?)");
        query.bindValue(0, typeName);

        if (query.exec())
        {
            query.clear();
            return getTypeUID(typeName);
        }
        else
        {
            qDebug() << query.lastError().text();
            return -100;
        }
    }
}

long long CreateTournamentOrdersDialog::getClubUID(QString clubName, long long coutryUID, long long regionUID, long long unitUID)
{
    QSqlQuery query;
    query.prepare("SELECT UID FROM CLUBS WHERE NAME = ? AND COUNTRY_FK = ? AND REGION_FK = ? AND REGION_UNIT = ?");
    query.bindValue(0, clubName);
    query.bindValue(1, coutryUID);
    query.bindValue(2, regionUID);
    query.bindValue(3, unitUID);
    bool isFind = ( query.exec() && query.next() );
    if (isFind)
    {
        return query.value("UID").toLongLong();
    }
    else
    {
        query.clear();
        query.prepare("INSERT INTO CLUBS(NAME, COUNTRY_FK, REGION_FK, REGION_UNIT_FK) VALUES(?, ?, ?, ?)");
        query.bindValue(0, clubName);
        query.bindValue(1, coutryUID);
        query.bindValue(2, regionUID);
        query.bindValue(3, unitUID);

        if (query.exec())
        {
            query.clear();
            return getClubUID(clubName, coutryUID, regionUID, unitUID);
        }
        else
        {
            qDebug() << query.lastError().text();
            return -100;
        }
    }
}

long long CreateTournamentOrdersDialog::getCoachUID(QString coachName, long long clubUID)
{
    QSqlQuery query;
    query.prepare("SELECT UID FROM COACHS WHERE NAME = ? AND CLUB_FK = ?");
    query.bindValue(0, coachName);
    query.bindValue(1, clubUID);
    bool isFind = ( query.exec() && query.next() );
    if (isFind)
    {
        return query.value("UID").toLongLong();
    }
    else
    {
        query.clear();
        query.prepare("INSERT INTO COACHS(NAME, CLUB_FK");
        query.bindValue(0, coachName);
        query.bindValue(1, clubUID);

        if (query.exec())
        {
            query.clear();
            return getCoachUID(coachName, clubUID);
        }
        else
        {
            qDebug() << query.lastError().text();
            return -100;
        }
    }
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
