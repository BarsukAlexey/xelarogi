#include "createtournamentordersdialog.h"
#include "ui_createtournamentordersdialog.h"
#include "excel_utils.h"
#include "db_utils.h"
#include <QSortFilterProxyModel>
#include "dialog_insert_data_in_database.h"
#include "dialog_change_category.h"

QSqlRecord CreateTournamentOrdersDialog::m_record;

CreateTournamentOrdersDialog::CreateTournamentOrdersDialog(const QSqlDatabase &database,
                                                           long long tournamentUID,
                                                           QWidget *parent,
                                                           QString filterSecondName,
                                                           QString filterFirstName
                                                           ):
    QDialog(parent),
    ui(new Ui::CreateTournamentOrdersDialog),
    m_database(database),
    mTournamentUID(tournamentUID)
{
    ui->setupUi(this);
    ui->label->setText(DBUtils::getField("NAME", "TOURNAMENTS", mTournamentUID, __PRETTY_FUNCTION__));

    QMap<QString, QString> rusFieldNames = DataBaseExpert::fieldTranslationMap(m_database);
    auto ralTablesForFields = DataBaseExpert::ralationTablesForFields(m_database);
    m_record = m_database.record("ORDERS");

    QSqlRelationalTableModel * model = new QSqlRelationalTableModel();
    model->setTable("ORDERS");
    model->setFilter("TOURNAMENT_CATEGORY_FK IN " + getAllowTournamentCategories());
    model->setSort(model->fieldIndex("SECOND_NAME"), Qt::AscendingOrder);
    ui->tableView->setModel(model);
    model->select();

    ui->tableView->setColumnHidden(model->fieldIndex("UID"), true);
//    ui->tableView->setColumnHidden(model->fieldIndex("COACH_FK"), true);
//    ui->tableView->setColumnHidden(model->fieldIndex("CLUB_FK"), true);
//    ui->tableView->setColumnHidden(model->fieldIndex("COUNTRY_FK"), true);
//    ui->tableView->setColumnHidden(model->fieldIndex("REGION_FK"), true);
//    ui->tableView->setColumnHidden(model->fieldIndex("BIRTHDATE"), true);
//    ui->tableView->setColumnHidden(model->fieldIndex("SEX_FK"), true);
//    ui->tableView->setColumnHidden(model->fieldIndex("SPORT_CATEGORY_FK"), true);
    for (int i = 0; i < m_record.count(); ++i)
    {
        QString fieldName = m_record.fieldName(i);
        if (fieldName.size() > 3 && fieldName.right(3) == "_FK")
        {
            model->setRelation(i, QSqlRelation(ralTablesForFields[fieldName], "UID", "NAME"));
        }
    }

    for (int i = 0; i < m_record.count(); ++i)
    {
        model->setHeaderData(i, Qt::Horizontal, rusFieldNames[m_record.fieldName(i)]);
    }
    model->select();

    connect(ui->btnExit, &QPushButton::clicked, [this]()
    {
        this->accept();
    });

    ui->tableView->resizeColumnsToContents();

    addContextMenu();

    connect(ui->loadBtn, &QPushButton::clicked, this, &CreateTournamentOrdersDialog::loadFromExcel);


    updateFillOrderWidget();
    setComboBoxDependencies();

    connect(ui->tableView, &QTableView::clicked, [this] (const QModelIndex& index)
    {
        if (index != QModelIndex())
        {
            ui->changeOrderBtn->setEnabled(true);

            QModelIndex ind = index.model()->index(index.row(), 0);
            long long uid = ind.data().toLongLong();
            updateFillOrderWidget(uid);
        }
    });

    addSearchFilters();

    connect(ui->addOrderBtn, &QPushButton::clicked, [this, model] ()
    {
        QString firstName = ui->firstNameLE->text();
        QString secondName = ui->secondNameLE->text();
        QString patronymic = ui->patronymicLE->text();
        QDate birthdate = ui->birthdayDE->date();
        double weight = ui->weightDSB->value();

        long long sexUID = ui->gendersCB->currentData(Qt::UserRole).toLongLong();
        long long sportCategoryUID = ui->sportCategoriesCB->currentData(Qt::UserRole).toLongLong();
        long long typeUID = ui->typesCB->currentData(Qt::UserRole).toLongLong();
        long long clubUID = ui->clubsCB->currentData(Qt::UserRole).toLongLong();
        long long coachUID = ui->coachsCB->currentData(Qt::UserRole).toLongLong();
        long long countryUID = ui->countriesCB->currentData(Qt::UserRole).toLongLong();
        long long regionUID = ui->regionsCB->currentData(Qt::UserRole).toLongLong();
        long long regionUnitUID = ui->regionUnitsCB->currentData(Qt::UserRole).toLongLong();
        long long tournamentCategoryUID = ui->tournamentCategoriesCB->currentData(Qt::UserRole).toLongLong();

        QString error = "";
        if (sexUID < 0 || ui->gendersCB->currentData(Qt::DisplayRole).toString().isEmpty())                     error += "пол, ";
        if (sportCategoryUID < 0 || ui->sportCategoriesCB->currentData(Qt::DisplayRole).toString().isEmpty())   error += "разряд, ";
        if (typeUID < 0 || ui->typesCB->currentData(Qt::DisplayRole).toString().isEmpty())                      error += "раздел, ";
        if (clubUID < 0 || ui->clubsCB->currentData(Qt::DisplayRole).toString().isEmpty())                      error += "клуб, ";
        if (coachUID < 0 || ui->coachsCB->currentData(Qt::DisplayRole).toString().isEmpty())                    error += "тренер, ";
        if (countryUID < 0 || ui->countriesCB->currentData(Qt::DisplayRole).toString().isEmpty())               error += "страна, ";
        if (regionUID < 0 || ui->regionsCB->currentData(Qt::DisplayRole).toString().isEmpty())                  error += "регион, ";
        if (regionUnitUID < 0 || ui->regionUnitsCB->currentData(Qt::DisplayRole).toString().isEmpty())          error += "населенный пункт, ";
        if (tournamentCategoryUID < 0 || ui->tournamentCategoriesCB->currentData(Qt::DisplayRole).toString().isEmpty()) error += "категория турнира, ";

        if (error.isEmpty())
        {
            QSqlQuery insertQuery;
            if (!insertQuery.prepare(
                    "INSERT INTO ORDERS("
                    " FIRST_NAME, SECOND_NAME, PATRONYMIC,"
                    " BIRTHDATE, WEIGHT, SEX_FK,"
                    " COUNTRY_FK, REGION_FK, REGION_UNIT_FK,"
                    " TOURNAMENT_CATEGORY_FK, TYPE_FK, "
                    " CLUB_FK, COACH_FK,"
                    " SPORT_CATEGORY_FK) "
                    "VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"
                    ))
                qDebug() << insertQuery.lastError().text();

            insertQuery.bindValue(0, firstName);
            insertQuery.bindValue(1, secondName);
            insertQuery.bindValue(2, patronymic);
            insertQuery.bindValue(3, birthdate.toString("yyyy-MM-dd"));
            insertQuery.bindValue(4, weight);
            insertQuery.bindValue(5, sexUID);
            insertQuery.bindValue(6, countryUID);
            insertQuery.bindValue(7, regionUID);
            insertQuery.bindValue(8, regionUnitUID);
            insertQuery.bindValue(9, tournamentCategoryUID);
            insertQuery.bindValue(10, typeUID);
            insertQuery.bindValue(11, clubUID);
            insertQuery.bindValue(12, coachUID);
            insertQuery.bindValue(13, sportCategoryUID);

            if (!insertQuery.exec())
                qDebug() << insertQuery.lastError().text();

            model->select();
            qDebug() << "added";
        }
        else
        {
            QMessageBox::warning(this, "Заполнены не все поля", "Вы не указали: " + error + " - заполните эти поля");
        }
    });

    connect(ui->changeOrderBtn, &QPushButton::clicked, [this, model] ()
    {
        QModelIndex index = ui->tableView->selectionModel()->currentIndex();
        if (index != QModelIndex())
        {
            QModelIndex ind = index.model()->index(index.row(), 0);
            long long uid = ind.data().toLongLong();

            QString firstName = ui->firstNameLE->text();
            QString secondName = ui->secondNameLE->text();
            QString patronymic = ui->patronymicLE->text();
            QDate birthdate = ui->birthdayDE->date();
            double weight = ui->weightDSB->value();

            long long sexUID = ui->gendersCB->currentData(Qt::UserRole).toLongLong();
            long long sportCategoryUID = ui->sportCategoriesCB->currentData(Qt::UserRole).toLongLong();
            long long typeUID = ui->typesCB->currentData(Qt::UserRole).toLongLong();
            long long clubUID = ui->clubsCB->currentData(Qt::UserRole).toLongLong();
            long long coachUID = ui->coachsCB->currentData(Qt::UserRole).toLongLong();
            long long countryUID = ui->countriesCB->currentData(Qt::UserRole).toLongLong();
            long long regionUID = ui->regionsCB->currentData(Qt::UserRole).toLongLong();
            long long regionUnitUID = ui->regionUnitsCB->currentData(Qt::UserRole).toLongLong();
            long long tournamentCategoryUID = ui->tournamentCategoriesCB->currentData(Qt::UserRole).toLongLong();

            QString error = "";
            if (sexUID < 0 || ui->gendersCB->currentData(Qt::DisplayRole).toString().isEmpty())                     error += "пол, ";
            if (sportCategoryUID < 0 || ui->sportCategoriesCB->currentData(Qt::DisplayRole).toString().isEmpty())   error += "разряд, ";
            if (typeUID < 0 || ui->typesCB->currentData(Qt::DisplayRole).toString().isEmpty())                      error += "раздел, ";
            if (clubUID < 0 || ui->clubsCB->currentData(Qt::DisplayRole).toString().isEmpty())                      error += "клуб, ";
            if (coachUID < 0 || ui->coachsCB->currentData(Qt::DisplayRole).toString().isEmpty())                    error += "тренер, ";
            if (countryUID < 0 || ui->countriesCB->currentData(Qt::DisplayRole).toString().isEmpty())               error += "страна, ";
            if (regionUID < 0 || ui->regionsCB->currentData(Qt::DisplayRole).toString().isEmpty())                  error += "регион, ";
            if (regionUnitUID < 0 || ui->regionUnitsCB->currentData(Qt::DisplayRole).toString().isEmpty())          error += "населенный пункт, ";
            if (tournamentCategoryUID < 0 || ui->tournamentCategoriesCB->currentData(Qt::DisplayRole).toString().isEmpty()) error += "категория турнира, ";

            if (error.isEmpty())
            {
                QSqlQuery updateQuery;
                if (!updateQuery.prepare(
                        "UPDATE ORDERS "
                        " SET "
                        " FIRST_NAME = ?, SECOND_NAME = ?, PATRONYMIC = ?,"
                        " BIRTHDATE = ?, WEIGHT = ?, SEX_FK = ?,"
                        " COUNTRY_FK = ?, REGION_FK = ?, REGION_UNIT_FK = ?,"
                        " TOURNAMENT_CATEGORY_FK = ?, TYPE_FK = ?, "
                        " CLUB_FK = ?, COACH_FK = ?,"
                        " SPORT_CATEGORY_FK = ? "
                        " WHERE UID = ? "
                        ))
                    qDebug() << updateQuery.lastError().text();

                updateQuery.bindValue(0, firstName);
                updateQuery.bindValue(1, secondName);
                updateQuery.bindValue(2, patronymic);
                updateQuery.bindValue(3, birthdate.toString("yyyy-MM-dd"));
                updateQuery.bindValue(4, weight);
                updateQuery.bindValue(5, sexUID);
                updateQuery.bindValue(6, countryUID);
                updateQuery.bindValue(7, regionUID);
                updateQuery.bindValue(8, regionUnitUID);
                updateQuery.bindValue(9, tournamentCategoryUID);
                updateQuery.bindValue(10, typeUID);
                updateQuery.bindValue(11, clubUID);
                updateQuery.bindValue(12, coachUID);
                updateQuery.bindValue(13, sportCategoryUID);
                updateQuery.bindValue(14, uid);

                if (!updateQuery.exec())
                    qDebug() << updateQuery.lastError().text();

                model->select();
                ui->tableView->setCurrentIndex(ui->tableView->model()->index(index.row(), 0));
                qDebug() << "changed";
            }
            else
            {
                QMessageBox::warning(this, "Заполнены не все поля", "Вы не указали: " + error + " - заполните эти поля");
            }
        }
    });

    connect(ui->pushButtonChangeCategory, &QPushButton::clicked, [this, model, tournamentUID] ()
    {
        QModelIndex index = ui->tableView->selectionModel()->currentIndex();
        if (index == QModelIndex()) return;

        long long uidOrder   = model->index(index.row(), model->fieldIndex("UID")).data().toLongLong();
        long long uidTC = DBUtils::getField("TOURNAMENT_CATEGORY_FK", "ORDERS", uidOrder).toLongLong();
        double w0 = DBUtils::getField("WEIGHT_FROM", "TOURNAMENT_CATEGORIES", uidTC).toDouble();
        double w1 = DBUtils::getField("WEIGHT_TILL", "TOURNAMENT_CATEGORIES", uidTC).toDouble();
        long long a0 = DBUtils::getField("AGE_FROM", "TOURNAMENT_CATEGORIES", uidTC).toLongLong();
        long long a1 = DBUtils::getField("AGE_TILL", "TOURNAMENT_CATEGORIES", uidTC).toLongLong();
        QVector<long long> arr;

        QSqlQuery query(
            "SELECT * "
            "FROM "
                "TOURNAMENT_CATEGORIES "
            "WHERE "
                "TOURNAMENT_FK = ? AND "
                "SEX_FK = ? "
            "ORDER BY "
                "TYPE_FK, AGE_FROM, AGE_TILL, WEIGHT_FROM, WEIGHT_TILL");
        query.addBindValue(tournamentUID);
        query.addBindValue(DBUtils::getField("SEX_FK", "ORDERS", uidOrder));
        if (!query.exec())
        {
            qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
            return;
        }
        while (query.next())
        {
            long long curUidTC = query.value("UID").toLongLong();
            if (curUidTC == uidTC) continue;
            double curw0 = DBUtils::getField("WEIGHT_FROM", "TOURNAMENT_CATEGORIES", curUidTC).toDouble();
            double curw1 = DBUtils::getField("WEIGHT_TILL", "TOURNAMENT_CATEGORIES", curUidTC).toDouble();
            long long cura0 = DBUtils::getField("AGE_FROM", "TOURNAMENT_CATEGORIES", curUidTC).toLongLong();
            long long cura1 = DBUtils::getField("AGE_TILL", "TOURNAMENT_CATEGORIES", curUidTC).toLongLong();
            double eps = 1e-7;

            QSet<long long > set = DBUtils::getSetOfOrdersInTournamentCategory(curUidTC);
            if (set.contains(uidOrder)) continue;
            if (
                0 < set.size() &&
                (qMax(w0, curw0) - eps <= qMin(w1, curw1) && qMax(a0, cura0) <= qMin(a1 + 1, cura1 + 1))
            ){
                arr << curUidTC;
            }
        }

        QDate DATE_WEIGHTING = QDate::fromString(DBUtils::getFieldDate("DATE_WEIGHTING", "TOURNAMENTS", mTournamentUID), "dd.MM.yyyy");
        QDate BIRTHDATE      = QDate::fromString(DBUtils::getFieldDate("BIRTHDATE", "ORDERS", uidOrder                ), "dd.MM.yyyy");
        QString title =
            DBUtils::getSecondNameAndOneLetterOfName(uidOrder) + ", " +
            DBUtils::getField("WEIGHT", "ORDERS", uidOrder) + " кг, " +
            QString::number(DBUtils::getAge(DATE_WEIGHTING, BIRTHDATE)) + " age";

        DialogChangeCategory dlg(title, arr, this);
        if (dlg.exec() == QDialog::Accepted)
        {
            QSqlQuery updateQuery(
                "UPDATE ORDERS "
                "SET "
                    "TOURNAMENT_CATEGORY_FK = ?, TYPE_FK = ? "
                "WHERE UID = ? ");
            updateQuery.addBindValue(dlg.uidCategory);
            updateQuery.addBindValue(DBUtils::getField("TYPE_FK", "TOURNAMENT_CATEGORIES", dlg.uidCategory));
            updateQuery.addBindValue(uidOrder);
            if (!updateQuery.exec())
                qDebug() << __LINE__ << __PRETTY_FUNCTION__ << updateQuery.lastError() << updateQuery.lastQuery();
        }

        model->select();
        ui->tableView->setCurrentIndex(ui->tableView->model()->index(index.row(), 0));
        updateFillOrderWidget(uidOrder);
        qDebug() << "changed category";
    });

    connect(ui->toExcelBtn, &QPushButton::clicked, this, &CreateTournamentOrdersDialog::saveToExcel);

    //
    ui->filterSecondNameLE->setText(filterSecondName);
    ui->filterFirstNameLE->setText(filterFirstName);
    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);
    if (parent == 0)
        setWindowFlags(windowFlags() | Qt::WindowMinMaxButtonsHint);
}

CreateTournamentOrdersDialog::~CreateTournamentOrdersDialog()
{
    delete ui;
}

void CreateTournamentOrdersDialog::loadFromExcel()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Выберите файл, в котором содержатся заявки"),
                                                    "", tr("Excel/Excel 97(*.xlsx *.xls);;Все файлы (*.*)"));
    if (filePath.isEmpty()) return;


    QAxObject* excel = new QAxObject("Excel.Application", this);
    //excel->setProperty("Visible", true);
    QAxObject* workbooks = excel->querySubObject( "Workbooks" );
    QAxObject* workbook = workbooks->querySubObject( "Open(const QString&)", filePath );

    QAxObject* sheets = workbook->querySubObject( "Sheets" );
    int sheetCount = sheets->dynamicCall("Count()").toInt();

    int totalOrders = 0;
    int addOrders = 0;
    int duplicateOrders = 0;
    int noUIDsOrders = 0;
    int errorOrders = 0;

    QStringList errors;
    for (int sheetNumber = 1; sheetNumber <= sheetCount; ++sheetNumber)
    {
        QAxObject* sheet = sheets->querySubObject( "Item( int )", sheetNumber );
        ExcelUtils::generateDocumentation(sheet, "sheet");

        QString countryName = ExcelUtils::getValue(sheet, 7, 2);
        long long countryUID = getCountryUID(countryName);
        if (ExcelUtils::getValue(sheet, 7, 2) != DBUtils::getField("NAME", "COUNTRIES", countryUID, __PRETTY_FUNCTION__))
            ExcelUtils::setValue(sheet, 7, 2,    DBUtils::getField("NAME", "COUNTRIES", countryUID, __PRETTY_FUNCTION__));

        QString regionName = ExcelUtils::getValue(sheet, 8, 2);
        long long regionUID = getRegionUID(regionName, countryUID);
        if (ExcelUtils::getValue(sheet, 8, 2) != DBUtils::getField("NAME", "REGIONS", regionUID, __PRETTY_FUNCTION__))
            ExcelUtils::setValue(sheet, 8, 2,    DBUtils::getField("NAME", "REGIONS", regionUID, __PRETTY_FUNCTION__));

        for (int row = 14; ; ++row) {
            mGlobalError = "";

            QString firstName  = ExcelUtils::getValue(sheet, row, 2);
            QString secondName = ExcelUtils::getValue(sheet, row, 1);
            if (secondName.trimmed().isEmpty()) break;
            QString patronymic = ExcelUtils::getValue(sheet, row, 3);

            QString birthday = ExcelUtils::getValue(sheet, row, 4);
            //qDebug() << birthday;
            QDate birthdayDate = QDate::fromString(birthday, "yyyy-MM-dd'T00:00:00'");
            if (!birthdayDate.isValid()) birthdayDate = QDate::fromString(birthday, "dd.MM.yyyy");
            double age = -100;
            if (birthdayDate.isValid())
            {
                birthday = birthdayDate.toString("dd.MM.yyyy");
                QDate DATE_WEIGHTING = QDate::fromString(DBUtils::getFieldDate("DATE_WEIGHTING", "TOURNAMENTS", mTournamentUID), "dd.MM.yyyy");
                age = DATE_WEIGHTING.year() - birthdayDate.year();
                if ( DATE_WEIGHTING.month() <  birthdayDate.month() ||
                    (DATE_WEIGHTING.month() == birthdayDate.month() && DATE_WEIGHTING.day() < birthdayDate.day()))
                {
                    --age;
                }
                //qDebug() << "I read from excel birthdate as " << birthday << " age: " << age;
            }
            else
            {
                qDebug() << "Can't read data: " << birthday;
                mGlobalError += "      Невозможно распознать дату " + birthday + "\n";
            }

            QString weight = ExcelUtils::getValue(sheet, row, 5).replace(",", ".");
            QString gender = ExcelUtils::getValue(sheet, row, 6);
            QString type = ExcelUtils::getValue(sheet, row, 7);
            QString regionUnitName = ExcelUtils::getValue(sheet, row, 8);
            QString clubName = ExcelUtils::getValue(sheet, row, 9);
            QString sportKind = ExcelUtils::getValue(sheet, row, 10);
            QString coachName = ExcelUtils::getValue(sheet, row, 11);

            long long genderUID = getGenderUID(gender);
            long long typeUID = getTypeUID(type);
            long long tournamentCategoryUID = -100;
            long long unitUID = getRegionUnitUID(regionUnitName, regionUID, countryUID);
            long long clubUID = getClubUID(clubName, countryUID, regionUID, unitUID);
            long long coachUID = getCoachUID(coachName, clubUID);
            long long sportCategoryUID = getSportCategoryUID(sportKind);

            if (type != DBUtils::getField("NAME", "TYPES", typeUID, __PRETTY_FUNCTION__))
                ExcelUtils::setValue(sheet, row, 7,    DBUtils::getField("NAME", "TYPES", typeUID, __PRETTY_FUNCTION__));

            if (genderUID <= 0) mGlobalError += "   Нет или неправильно указан пол\n";
            if (weight.toDouble() == 0.0) mGlobalError += "   Неправильно указан вес\n";
            if (mGlobalError.isEmpty())
                tournamentCategoryUID = getTournamentCategoryUID(genderUID, age, weight.toDouble(), typeUID, gender, type);

            totalOrders++;

            if (!mGlobalError.isEmpty())
            {
                errors << mGlobalError + "(Спортсмен: " + secondName + " " + firstName + " " + patronymic + ") Лист " +  sheet->property("Name").toString() + " строка " + QString::number(row) + "\n";
                noUIDsOrders++;
            }
            else
            {
                QSqlQuery findQuery;
                if (!findQuery.prepare("SELECT * FROM ORDERS "
                                     "WHERE "
                                     " FIRST_NAME = ? AND SECOND_NAME = ? AND PATRONYMIC = ? AND "
                                     " COUNTRY_FK = ? AND REGION_FK = ? AND REGION_UNIT_FK = ? AND "
                                     " BIRTHDATE = ? AND WEIGHT = ? AND SEX_FK = ? AND "
                                     " TOURNAMENT_CATEGORY_FK = ? AND TYPE_FK = ? AND "
                                     " CLUB_FK = ? AND COACH_FK = ? AND "
                                     " SPORT_CATEGORY_FK = ? "
                                ))
                    qDebug() << findQuery.lastError();
                findQuery.bindValue(0, firstName);
                findQuery.bindValue(1, secondName);
                findQuery.bindValue(2, patronymic);
                findQuery.bindValue(3, countryUID);
                findQuery.bindValue(4, regionUID);
                findQuery.bindValue(5, unitUID);
                findQuery.bindValue(6, birthdayDate);
                findQuery.bindValue(7, weight);
                findQuery.bindValue(8, genderUID);
                findQuery.bindValue(9, tournamentCategoryUID);
                findQuery.bindValue(10, typeUID);
                findQuery.bindValue(11, clubUID);
                findQuery.bindValue(12, coachUID);
                findQuery.bindValue(13, sportCategoryUID);

                if (findQuery.exec() && findQuery.next())
                {
                    duplicateOrders++;
                    //qDebug() << "дубликат (Спортсмен: " + secondName + " " + firstName + " " + patronymic + ") Лист " +  sheet->property("Name").toString() + " строка " + QString::number(row) ;
                }
                else
                {
                    //qDebug() << __LINE__ << __PRETTY_FUNCTION__ << findQuery.lastError();

                    QSqlQuery query;
                    if (!query.prepare(  "INSERT INTO ORDERS("
                                         "FIRST_NAME, SECOND_NAME, PATRONYMIC, "
                                         "COUNTRY_FK, REGION_FK, REGION_UNIT_FK, "
                                         "BIRTHDATE, WEIGHT, SEX_FK, "
                                         "TOURNAMENT_CATEGORY_FK, TYPE_FK, "
                                         "CLUB_FK, COACH_FK, "
                                         "SPORT_CATEGORY_FK) "
                                    "VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"
                                    ))
                        qDebug() << query.lastError();
                    query.bindValue(0, firstName);
                    query.bindValue(1, secondName);
                    query.bindValue(2, patronymic);
                    query.bindValue(3, countryUID);
                    query.bindValue(4, regionUID);
                    query.bindValue(5, unitUID);
                    query.bindValue(6, birthdayDate);
                    query.bindValue(7, weight);
                    query.bindValue(8, genderUID);
                    query.bindValue(9, tournamentCategoryUID);
                    query.bindValue(10, typeUID);
                    query.bindValue(11, clubUID);
                    query.bindValue(12, coachUID);
                    query.bindValue(13, sportCategoryUID);

                    if (query.exec())
                        addOrders++;
                    else
                    {
                        qDebug() << query.lastError();
                        errors << "\n\nНеизвестна ошибка добавления в БД: (Спортсмен: " + secondName + " " + firstName + " " + patronymic + ") Лист " +  sheet->property("Name").toString() + " строка " + QString::number(row) + "\n\n";
                        errorOrders++;
                    }
                }
            }
        }
    }

    workbook->dynamicCall("Save()");
    workbook->dynamicCall("Close()");
    delete workbook;
    excel->dynamicCall("Quit()");
    delete excel;

    if (errors.size() > 0)
    {
        qDebug() << errors.size() << " errors";
        ErrorMessagesDialog dlg(errors, this);
        dlg.exec();
    }

    QMessageBox::information(this, "Добавление заявок выполнено", "Всего распознано заявок: " + QString::number(totalOrders) + "\n"
                                                                  "Добавлено заявок: " + QString::number(addOrders) + "\n"
                                                                  "Не добавлены (нет категории): " + QString::number(noUIDsOrders) + "\n"
                                                                  "Проигнорированы (уже содержатся в базе): " + QString::number(duplicateOrders) + "\n"
                                                                  "Произошла ошибка при добавлении заявок: " + QString::number(errorOrders));

    QSqlRelationalTableModel* model = dynamic_cast<QSqlRelationalTableModel*>(ui->tableView->model());
    model->select();
    ui->tableView->resizeColumnsToContents();
}

void CreateTournamentOrdersDialog::saveToExcel()
{
    QAxWidget excel("Excel.Application");
    excel.setProperty("Visible", true);
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
    workbooks->dynamicCall("Add");
    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");
    QAxObject *sheets = workbook->querySubObject("WorkSheets");
    sheets->querySubObject("Add");
    QAxObject *sheet = sheets->querySubObject( "Item( int )", 1);

    QSqlRelationalTableModel* model = dynamic_cast<QSqlRelationalTableModel*>(ui->tableView->model());


    for (int column = 0; column < model->columnCount(); ++column)
        ExcelUtils::setValue(sheet, 1, column + 1, model->headerData(column, Qt::Horizontal, Qt::DisplayRole).toString());

    for (int row = 0; row < model->rowCount(); ++row)
    {
            for (int column = 0; column < model->columnCount(); ++column)
            {
                QModelIndex index = model->index(row, column);
                QString data = index.data().toString();

                if (model->headerData(column, Qt::Horizontal, Qt::DisplayRole).toString() != "Вес")
                {
                    QAxObject* cell = sheet->querySubObject( "Cells( int, int )", row + 2, column + 1 );
                    cell->setProperty("Value", QVariant(data));
                    delete cell;
                }
                else
                {
                    QAxObject* cell = sheet->querySubObject( "Cells( int, int )", row + 2, column + 1 );
                    cell->setProperty("Value", DBUtils::roundDouble(data.toDouble(), 4).replace(".", ","));
                    delete cell;
                }
            }
    }

    for (int column = 0; column < model->columnCount(); ++column)
        ExcelUtils::setColumnAutoFit(sheet, column + 1);

    delete sheet;
    delete sheets;
    delete workbook;
    delete workbooks;
}

void CreateTournamentOrdersDialog::updateFillOrderWidget(long long orderUID)
{
    long long sexUID = -1;
    long long countryUID = -1, regionUID = -1, regionUnitUID = -1;
    long long sportCategoryUID = -1;
    long long typeUID = -1;
    long long clubUID = -1, coachUID = -1;
    long long tournamentCategoryUID = -1;

    if (orderUID >= 0)
    {
        QSqlQuery query;
        if (!query.prepare("SELECT * FROM ORDERS WHERE UID = ?"))
            qDebug() << query.lastError().text();
        query.bindValue(0, orderUID);

        if (query.exec() && query.next())
        {
            QDate birthdate = QDate::fromString(query.value("BIRTHDATE").toString(), "yyyy-MM-dd");

            sexUID = query.value("SEX_FK").toLongLong();
            countryUID = query.value("COUNTRY_FK").toLongLong();
            regionUID = query.value("REGION_FK").toLongLong();
            regionUnitUID = query.value("REGION_UNIT_FK").toLongLong();
            sportCategoryUID = query.value("SPORT_CATEGORY_FK").toLongLong();
            typeUID = query.value("TYPE_FK").toLongLong();
            clubUID = query.value("CLUB_FK").toLongLong();
            coachUID = query.value("COACH_FK").toLongLong();
            tournamentCategoryUID = query.value("TOURNAMENT_CATEGORY_FK").toLongLong();


            ui->firstNameLE->setText(query.value("FIRST_NAME").toString());
            ui->secondNameLE->setText(query.value("SECOND_NAME").toString());
            ui->patronymicLE->setText(query.value("PATRONYMIC").toString());
            ui->birthdayDE->setDate(birthdate);
            ui->weightDSB->setValue(query.value("WEIGHT").toDouble());
        }
        else
        {
            qDebug() << query.lastError().text();
        }
    }

    updateSexComboBox(sexUID);
    updateCountryComboBox(countryUID);
    updateRegionComboBox(regionUID, countryUID);
    updateRegionUnitComboBox(regionUnitUID, regionUID);
    updateSportCategoryComboBox(sportCategoryUID);
    updateTypeComboBox(typeUID);
    updateClubComboBox(clubUID, regionUID);
    updateCoachComboBox(coachUID, clubUID);
    updateTournamentCategoriesComboBox(tournamentCategoryUID, sexUID, typeUID);
}

void CreateTournamentOrdersDialog::addContextMenu()
{
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->tableView, &QTableView::customContextMenuRequested, [this] (const QPoint& pos)
    {
        QMenu * contextMenu = new QMenu();

//        QAction* restrictAction = new QAction(tr("Отозвать заявку"), contextMenu);
//        contextMenu->addAction(restrictAction);
//        connect(restrictAction, &QAction::triggered, [this, &pos] ()
//        {
//            QModelIndex index = ui->tableView->indexAt(pos);

//            if (index != QModelIndex())
//            {
//                QSqlRelationalTableModel* model = dynamic_cast<QSqlRelationalTableModel*>(ui->tableView->model());

//                QModelIndex ind = index.model()->index(index.row(), 0);
//                long long orderUID = ind.data().toLongLong();

//                QSqlQuery updateQuery;
//                if (!updateQuery.prepare("UPDATE ORDERS SET IS_VALID = 0 WHERE UID = ?"))
//                    qDebug() << updateQuery.lastError().text();
//                updateQuery.bindValue(0, orderUID);
//                if (!updateQuery.exec())
//                    qDebug() << updateQuery.lastError().text();

//                model->select();
//            }
//        });

        QAction * delAction = new QAction(tr("Удалить выделенные"), contextMenu);
        contextMenu->addAction(delAction);
        connect(delAction, &QAction::triggered, [this, &pos] ()
        {
            QSqlRelationalTableModel* model = dynamic_cast<QSqlRelationalTableModel*>(ui->tableView->model());

            for(QModelIndex index : ui->tableView->selectionModel()->selectedRows())
            {
                model->removeRow(index.row());
            }
            model->submitAll();
            model->select();

//            QModelIndex index = ui->tableView->indexAt(pos);
//            model->removeRow(index.row());
//            model->submitAll();
//            model->select();
        });


        contextMenu->exec(ui->tableView->viewport()->mapToGlobal(pos));

    });
}

void CreateTournamentOrdersDialog::addSearchFilters()
{
    connect(ui->filterSecondNameLE, &QLineEdit::textChanged, [this] (const QString& secondNameMask)
    {
        QSqlRelationalTableModel* model = dynamic_cast<QSqlRelationalTableModel*>(ui->tableView->model());
        model->setFilter(QString("ORDERS.SECOND_NAME LIKE '%%1%' "
                                 "AND ORDERS.UID IN %2 "
                                 "AND ORDERS.FIRST_NAME LIKE '%%3%' "
                                 "AND ORDERS.UID IN %4 "
                                 "AND ORDERS.UID IN %5 "
                                 "AND ORDERS.UID IN %6 "
                                 "AND ORDERS.UID IN %7 "
                                 "AND ORDERS.UID IN %8 ")
                         .arg(secondNameMask, getAllowOrderUIDsByCoach(ui->filterCoachLE->text()),
                              ui->filterFirstNameLE->text(), getAllowOrderUIDsByRegion(ui->filterRegionLE->text()),
                              getAllowOrderUIDsByRegionUnit(ui->filterRegionUintLE->text()),
                              getAllowOrderUIDsByCountry(ui->filterCountryLE->text()),
                              getAllowOrderUIDsByGender(ui->filterSexLE->text()),
                              getAllowOrderUIDsbyTournamentCategory(ui->filterTournamentCategoriesLE->text())
                              )
                         );
        if (!model->select())
            qDebug() << model->lastError().text();
    });
    connect(ui->filterFirstNameLE, &QLineEdit::textChanged, [this] (const QString& firstNameMask)
    {
        QSqlRelationalTableModel* model = dynamic_cast<QSqlRelationalTableModel*>(ui->tableView->model());
        model->setFilter(QString("ORDERS.SECOND_NAME LIKE '%%1%' "
                                 "AND ORDERS.UID IN %2 "
                                 "AND ORDERS.FIRST_NAME LIKE '%%3%' "
                                 "AND ORDERS.UID IN %4 "
                                 "AND ORDERS.UID IN %5 "
                                 "AND ORDERS.UID IN %6 "
                                 "AND ORDERS.UID IN %7 "
                                 "AND ORDERS.UID IN %8 ")
                         .arg(ui->filterSecondNameLE->text(), getAllowOrderUIDsByCoach(ui->filterCoachLE->text()),
                              firstNameMask, getAllowOrderUIDsByRegion(ui->filterRegionLE->text()),
                              getAllowOrderUIDsByRegionUnit(ui->filterRegionUintLE->text()),
                              getAllowOrderUIDsByCountry(ui->filterCountryLE->text()),
                              getAllowOrderUIDsByGender(ui->filterSexLE->text()),
                              getAllowOrderUIDsbyTournamentCategory(ui->filterTournamentCategoriesLE->text())
                              )
                         );
        if (!model->select())
            qDebug() << model->lastError().text();
    });
    connect(ui->filterCoachLE, &QLineEdit::textChanged, [this] (const QString& coachNameMask)
    {
        QSqlRelationalTableModel* model = dynamic_cast<QSqlRelationalTableModel*>(ui->tableView->model());
        model->setFilter(QString("ORDERS.UID IN %1 "
                                 "AND ORDERS.SECOND_NAME LIKE '%%2%' "
                                 "AND ORDERS.FIRST_NAME LIKE '%%3%' "
                                 "AND ORDERS.UID IN %4 "
                                 "AND ORDERS.UID IN %5 "
                                 "AND ORDERS.UID IN %6 "
                                 "AND ORDERS.UID IN %7 "
                                 "AND ORDERS.UID IN %8 ")
                         .arg(getAllowOrderUIDsByCoach(coachNameMask), ui->filterSecondNameLE->text(),
                              ui->filterFirstNameLE->text(), getAllowOrderUIDsByRegion(ui->filterRegionLE->text()),
                              getAllowOrderUIDsByRegionUnit(ui->filterRegionUintLE->text()),
                              getAllowOrderUIDsByCountry(ui->filterCountryLE->text()),
                              getAllowOrderUIDsByGender(ui->filterSexLE->text()),
                              getAllowOrderUIDsbyTournamentCategory(ui->filterTournamentCategoriesLE->text())
                              )
                         );
        if (!model->select())
            qDebug() << model->lastError().text();
    });
    connect(ui->filterRegionLE, &QLineEdit::textChanged, [this] (const QString& regionNameMask)
    {
        QSqlRelationalTableModel* model = dynamic_cast<QSqlRelationalTableModel*>(ui->tableView->model());
        model->setFilter(QString("ORDERS.UID IN %1 "
                                 "AND ORDERS.SECOND_NAME LIKE '%%2%' "
                                 "AND ORDERS.FIRST_NAME LIKE '%%3%' "
                                 "AND ORDERS.UID IN %4 "
                                 "AND ORDERS.UID IN %5 "
                                 "AND ORDERS.UID IN %6 "
                                 "AND ORDERS.UID IN %7 "
                                 "AND ORDERS.UID IN %8 ")
                         .arg(getAllowOrderUIDsByCoach(ui->filterCoachLE->text()),
                              ui->filterSecondNameLE->text(), ui->filterFirstNameLE->text(),
                              getAllowOrderUIDsByRegion(regionNameMask),
                              getAllowOrderUIDsByRegionUnit(ui->filterRegionUintLE->text()),
                              getAllowOrderUIDsByCountry(ui->filterCountryLE->text()),
                              getAllowOrderUIDsByGender(ui->filterSexLE->text()),
                              getAllowOrderUIDsbyTournamentCategory(ui->filterTournamentCategoriesLE->text())
                              )
                         );
        if (!model->select())
            qDebug() << model->lastError().text();
    });
    connect(ui->filterRegionUintLE, &QLineEdit::textChanged, [this] (const QString& regionUnitNameMask)
    {
        QSqlRelationalTableModel* model = dynamic_cast<QSqlRelationalTableModel*>(ui->tableView->model());
        model->setFilter(QString("ORDERS.UID IN %1 "
                                 "AND ORDERS.SECOND_NAME LIKE '%%2%' "
                                 "AND ORDERS.FIRST_NAME LIKE '%%3%' "
                                 "AND ORDERS.UID IN %4 "
                                 "AND ORDERS.UID IN %5 "
                                 "AND ORDERS.UID IN %6 "
                                 "AND ORDERS.UID IN %7 "
                                 "AND ORDERS.UID IN %8 ")
                         .arg(getAllowOrderUIDsByCoach(ui->filterCoachLE->text()),
                              ui->filterSecondNameLE->text(), ui->filterFirstNameLE->text(),
                              getAllowOrderUIDsByRegion(ui->filterRegionLE->text()),
                              getAllowOrderUIDsByRegionUnit(regionUnitNameMask),
                              getAllowOrderUIDsByCountry(ui->filterCountryLE->text()),
                              getAllowOrderUIDsByGender(ui->filterSexLE->text()),
                              getAllowOrderUIDsbyTournamentCategory(ui->filterTournamentCategoriesLE->text())
                              )
                         );
        if (!model->select())
            qDebug() << model->lastError().text();
    });
    connect(ui->filterCountryLE, &QLineEdit::textChanged, [this] (const QString& countryNameMask)
    {
        QSqlRelationalTableModel* model = dynamic_cast<QSqlRelationalTableModel*>(ui->tableView->model());
        model->setFilter(QString("ORDERS.UID IN %1 "
                                 "AND ORDERS.SECOND_NAME LIKE '%%2%' "
                                 "AND ORDERS.FIRST_NAME LIKE '%%3%' "
                                 "AND ORDERS.UID IN %4 "
                                 "AND ORDERS.UID IN %5 "
                                 "AND ORDERS.UID IN %6 "
                                 "AND ORDERS.UID IN %7 "
                                 "AND ORDERS.UID IN %8 ")
                         .arg(getAllowOrderUIDsByCoach(ui->filterCoachLE->text()),
                              ui->filterSecondNameLE->text(), ui->filterFirstNameLE->text(),
                              getAllowOrderUIDsByRegion(ui->filterRegionLE->text()),
                              getAllowOrderUIDsByRegionUnit(ui->filterRegionUintLE->text()),
                              getAllowOrderUIDsByCountry(countryNameMask),
                              getAllowOrderUIDsByGender(ui->filterSexLE->text()),
                              getAllowOrderUIDsbyTournamentCategory(ui->filterTournamentCategoriesLE->text())
                              )
                         );
        if (!model->select())
            qDebug() << model->lastError().text();
    });
    connect(ui->filterSexLE, &QLineEdit::textChanged, [this] (const QString& genderNameMask)
    {
        QSqlRelationalTableModel* model = dynamic_cast<QSqlRelationalTableModel*>(ui->tableView->model());
        model->setFilter(QString("ORDERS.UID IN %1 "
                                 "AND ORDERS.SECOND_NAME LIKE '%%2%' "
                                 "AND ORDERS.FIRST_NAME LIKE '%%3%' "
                                 "AND ORDERS.UID IN %4 "
                                 "AND ORDERS.UID IN %5 "
                                 "AND ORDERS.UID IN %6 "
                                 "AND ORDERS.UID IN %7 "
                                 "AND ORDERS.UID IN %8 ")
                         .arg(getAllowOrderUIDsByCoach(ui->filterCoachLE->text()),
                              ui->filterSecondNameLE->text(), ui->filterFirstNameLE->text(),
                              getAllowOrderUIDsByRegion(ui->filterRegionLE->text()),
                              getAllowOrderUIDsByRegionUnit(ui->filterRegionUintLE->text()),
                              getAllowOrderUIDsByCountry(ui->filterCountryLE->text()),
                              getAllowOrderUIDsByGender(genderNameMask),
                              getAllowOrderUIDsbyTournamentCategory(ui->filterTournamentCategoriesLE->text())
                              )
                         );
        if (!model->select())
            qDebug() << model->lastError().text();
    });
    connect(ui->filterTournamentCategoriesLE, &QLineEdit::textChanged, [this] (const QString& tournamentCategoryNameMask)
    {
        QSqlRelationalTableModel* model = dynamic_cast<QSqlRelationalTableModel*>(ui->tableView->model());
        model->setFilter(QString("ORDERS.UID IN %1 "
                                 "AND ORDERS.SECOND_NAME LIKE '%%2%' "
                                 "AND ORDERS.FIRST_NAME LIKE '%%3%' "
                                 "AND ORDERS.UID IN %4 "
                                 "AND ORDERS.UID IN %5 "
                                 "AND ORDERS.UID IN %6 "
                                 "AND ORDERS.UID IN %7 "
                                 "AND ORDERS.UID IN %8 ")
                         .arg(getAllowOrderUIDsByCoach(ui->filterCoachLE->text()),
                              ui->filterSecondNameLE->text(), ui->filterFirstNameLE->text(),
                              getAllowOrderUIDsByRegion(ui->filterRegionLE->text()),
                              getAllowOrderUIDsByRegionUnit(ui->filterRegionUintLE->text()),
                              getAllowOrderUIDsByCountry(ui->filterCountryLE->text()),
                              getAllowOrderUIDsByGender(ui->filterSexLE->text()),
                              getAllowOrderUIDsbyTournamentCategory(tournamentCategoryNameMask)
                              )
                         );
        if (!model->select())
            qDebug() << model->lastError().text();
    });
}

void CreateTournamentOrdersDialog::setComboBoxDependencies()
{
    connect(ui->countriesCB, &QComboBox::currentTextChanged, [this] (const QString&)
    {
        long long coutryUID = ui->countriesCB->currentData(Qt::UserRole).toLongLong();
        updateRegionComboBox(-1, coutryUID);
    });
    connect(ui->regionsCB, &QComboBox::currentTextChanged, [this] (const QString&)
    {
        long long regionUID = ui->regionsCB->currentData(Qt::UserRole).toLongLong();
        updateRegionUnitComboBox(-1, regionUID);
        updateClubComboBox(-1, regionUID);
    });
    connect(ui->clubsCB, &QComboBox::currentTextChanged, [this] (const QString&)
    {
        long long clubUID = ui->clubsCB->currentData(Qt::UserRole).toLongLong();
        updateCoachComboBox(-1, clubUID);
    });
    connect(ui->gendersCB, &QComboBox::currentTextChanged, [this] (const QString&)
    {
        long long sexUID = ui->gendersCB->currentData(Qt::UserRole).toLongLong();
        long long typeUID = ui->typesCB->currentData(Qt::UserRole).toLongLong();
        updateTournamentCategoriesComboBox(-1, sexUID, typeUID);
    });
    connect(ui->typesCB, &QComboBox::currentTextChanged, [this] (const QString&)
    {
        long long sexUID = ui->gendersCB->currentData(Qt::UserRole).toLongLong();
        long long typeUID = ui->typesCB->currentData(Qt::UserRole).toLongLong();
        updateTournamentCategoriesComboBox(-1, sexUID, typeUID);
    });
}

QString CreateTournamentOrdersDialog::getAllowTournamentCategories()
{
    QString allowTournamentCategories = "(-100";
    QSqlQuery categoriesQouery("SELECT UID FROM TOURNAMENT_CATEGORIES WHERE TOURNAMENT_FK = " + QString::number(mTournamentUID));
    if (categoriesQouery.exec())
    {
        while (categoriesQouery.next())
        {
            allowTournamentCategories += ", " + categoriesQouery.value("UID").toString();
        }
    }
    allowTournamentCategories += ")";

    return allowTournamentCategories;
}

QString CreateTournamentOrdersDialog::getAllowOrderUIDsByCoach(const QString &coachNameMask)
{
    QString allowedOrders = "(-100";
    QSqlQuery query;
    if (!query.prepare("SELECT ORDERS.UID "
                       "FROM ORDERS "
                       "    LEFT JOIN COACHS ON COACHS.UID = ORDERS.COACH_FK "
                       "    LEFT JOIN TOURNAMENT_CATEGORIES ON TOURNAMENT_CATEGORIES.UID = ORDERS.TOURNAMENT_CATEGORY_FK "
                       "WHERE"
                       "    TOURNAMENT_CATEGORIES.TOURNAMENT_FK = ? AND "
                       "    COACHS.NAME LIKE '%" + coachNameMask + "%' "))
        qDebug() << query.lastError().text();
    query.bindValue(0, mTournamentUID);

    if (query.exec())
    {
        while (query.next())
        {
            allowedOrders += ", " + query.value(0).toString();
        }
    }
    else
        qDebug() << query.lastError().text();

    allowedOrders += ")";

    return allowedOrders;
}

QString CreateTournamentOrdersDialog::getAllowOrderUIDsByCountry(const QString &countryNameMask)
{
    QString allowedOrders = "(-100";
    QSqlQuery query;
    if (!query.prepare("SELECT ORDERS.UID "
                       "FROM ORDERS "
                       "    LEFT JOIN COUNTRIES ON COUNTRIES.UID = ORDERS.COUNTRY_FK "
                       "    LEFT JOIN TOURNAMENT_CATEGORIES ON TOURNAMENT_CATEGORIES.UID = ORDERS.TOURNAMENT_CATEGORY_FK "
                       "WHERE"
                       "    TOURNAMENT_CATEGORIES.TOURNAMENT_FK = ? AND "
                       "    COUNTRIES.NAME LIKE '%" + countryNameMask + "%' "))
        qDebug() << query.lastError().text();
    query.bindValue(0, mTournamentUID);

    if (query.exec())
    {
        while (query.next())
        {
            allowedOrders += ", " + query.value(0).toString();
        }
    }
    else
        qDebug() << query.lastError().text();

    allowedOrders += ")";

    return allowedOrders;
}

QString CreateTournamentOrdersDialog::getAllowOrderUIDsByRegion(const QString &regionNameMask)
{
    QString allowedOrders = "(-100";
    QSqlQuery query;
    if (!query.prepare("SELECT ORDERS.UID "
                       "FROM ORDERS "
                       "    LEFT JOIN REGIONS ON REGIONS.UID = ORDERS.REGION_FK "
                       "    LEFT JOIN TOURNAMENT_CATEGORIES ON TOURNAMENT_CATEGORIES.UID = ORDERS.TOURNAMENT_CATEGORY_FK "
                       "WHERE"
                       "    TOURNAMENT_CATEGORIES.TOURNAMENT_FK = ? AND "
                       "    REGIONS.NAME LIKE '%" + regionNameMask + "%' "))
        qDebug() << query.lastError().text();
    query.bindValue(0, mTournamentUID);

    if (query.exec())
    {
        while (query.next())
        {
            allowedOrders += ", " + query.value(0).toString();
        }
    }
    else
        qDebug() << query.lastError().text();

    allowedOrders += ")";

    return allowedOrders;
}

QString CreateTournamentOrdersDialog::getAllowOrderUIDsByRegionUnit(const QString &regionUnitNameMask)
{
    QString allowedOrders = "(-100";
    QSqlQuery query;
    if (!query.prepare("SELECT ORDERS.UID "
                       "FROM ORDERS "
                       "    LEFT JOIN REGION_UNITS ON REGION_UNITS.UID = ORDERS.REGION_UNIT_FK "
                       "    LEFT JOIN TOURNAMENT_CATEGORIES ON TOURNAMENT_CATEGORIES.UID = ORDERS.TOURNAMENT_CATEGORY_FK "
                       "WHERE"
                       "    TOURNAMENT_CATEGORIES.TOURNAMENT_FK = ? AND "
                       "    REGION_UNITS.NAME LIKE '%" + regionUnitNameMask + "%' "))
        qDebug() << query.lastError().text();
    query.bindValue(0, mTournamentUID);

    if (query.exec())
    {
        while (query.next())
        {
            allowedOrders += ", " + query.value(0).toString();
        }
    }
    else
        qDebug() << query.lastError().text();

    allowedOrders += ")";

    return allowedOrders;
}

QString CreateTournamentOrdersDialog::getAllowOrderUIDsByGender(const QString &genderMask)
{
    QString allowedOrders = "(-100";
    QSqlQuery query;
    if (!query.prepare("SELECT ORDERS.UID "
                       "FROM ORDERS "
                       "    LEFT JOIN SEXES ON SEXES.UID = ORDERS.SEX_FK "
                       "    LEFT JOIN TOURNAMENT_CATEGORIES ON TOURNAMENT_CATEGORIES.UID = ORDERS.TOURNAMENT_CATEGORY_FK "
                       "WHERE"
                       "    TOURNAMENT_CATEGORIES.TOURNAMENT_FK = ? AND "
                       "    SEXES.NAME LIKE '%" + genderMask + "%' "))
        qDebug() << query.lastError().text();
    query.bindValue(0, mTournamentUID);

    if (query.exec())
    {
        while (query.next())
        {
            allowedOrders += ", " + query.value(0).toString();
        }
    }
    else
        qDebug() << query.lastError().text();

    allowedOrders += ")";

    return allowedOrders;
}

QString CreateTournamentOrdersDialog::getAllowOrderUIDsbyTournamentCategory(const QString &tournamentCategoryMask)
{
    QString allowedOrders = "(-100";
    QSqlQuery query;
    if (!query.prepare("SELECT ORDERS.UID "
                       "FROM ORDERS "
                       "    LEFT JOIN TOURNAMENT_CATEGORIES ON TOURNAMENT_CATEGORIES.UID = ORDERS.TOURNAMENT_CATEGORY_FK "
                       "WHERE"
                       "    TOURNAMENT_CATEGORIES.TOURNAMENT_FK = ? AND "
                       "    TOURNAMENT_CATEGORIES.NAME LIKE '%" + tournamentCategoryMask + "%' "))
        qDebug() << query.lastError().text();
    query.bindValue(0, mTournamentUID);

    if (query.exec())
    {
        while (query.next())
        {
            allowedOrders += ", " + query.value(0).toString();
        }
    }
    else
        qDebug() << query.lastError().text();

    allowedOrders += ")";

    return allowedOrders;
}



long long CreateTournamentOrdersDialog::getCountryUID(QString countryName)
{
    if (mCountry.contains(countryName))
        countryName = mCountry[countryName];

    QSqlQuery query;
    QStringList allNames;
    if (!query.prepare("SELECT * FROM COUNTRIES"))
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
    if (query.exec())
    {
        while (query.next())
        {
            QString country = query.value("NAME").toString();
            allNames << country;
            if (country.trimmed().toUpper() == countryName.trimmed().toUpper())
            {
                return query.value("UID").toLongLong();
            }
        }
    }
    else
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
    }

    DialogInsertDataInDatabase dialog(this, countryName, allNames, "Нет в справочнике такой страны");
    int done = dialog.exec();
    countryName = mCountry[countryName] = dialog.getText();

    if (done == -1)
    {
        query.clear();
        if (!query.prepare("INSERT INTO COUNTRIES(NAME) VALUES(?)"))
            qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
        query.bindValue(0, countryName);

        if (query.exec())
            return getCountryUID(countryName);
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
        return -100;
    }
    return getCountryUID(countryName);
}

long long CreateTournamentOrdersDialog::getRegionUID(QString regionName, long long countryUID)
{
    if (mRegion.contains(regionName))
    {
        regionName = mRegion[regionName];
    }

    QSqlQuery query;
    QStringList allNames;
    if (!query.prepare("SELECT * FROM REGIONS WHERE COUNTRY_FK = ?"))
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
    query.bindValue(0, countryUID);

    if (query.exec())
    {
        while (query.next())
        {
            QString region = query.value("NAME").toString();
            allNames << region;
            if (region.trimmed().toUpper() == regionName.trimmed().toUpper())
            {
                return query.value("UID").toLongLong();
            }
        }
    }
    else
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
    }

    DialogInsertDataInDatabase dialog(this, regionName, allNames, "В стране " + DBUtils::getField("NAME","COUNTRIES", countryUID, __PRETTY_FUNCTION__) + " нет такого региона");
    int done = dialog.exec();
    regionName = mRegion[regionName] = dialog.getText();

    if (done == -1)
    {
        query.clear();
        if (!query.prepare("INSERT INTO REGIONS(NAME, COUNTRY_FK) VALUES(?, ?)"))
            qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
        query.bindValue(0, regionName);
        query.bindValue(1, countryUID);

        if (query.exec())
            return getRegionUID(regionName, countryUID);
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
        return -100;
    }
    return getRegionUID(regionName, countryUID);
}

long long CreateTournamentOrdersDialog::getRegionUnitUID(QString unitName, long long regionUID, long long countryUID)
{
    QSqlQuery query;
    if (!query.prepare("SELECT * FROM REGION_UNITS WHERE REGION_FK = ?"))
        qDebug() << query.lastError().text();
    query.bindValue(0, regionUID);

    if (query.exec())
    {
        while (query.next())
        {
            QString regionUnit = query.value("NAME").toString();
            if (regionUnit.trimmed().toUpper() == unitName.trimmed().toUpper())
            {
                return query.value("UID").toLongLong();
            }
        }
    }
    else
    {
        qDebug() << query.lastError().text();
    }

    query.clear();
    if (!query.prepare("INSERT INTO REGION_UNITS(NAME, REGION_FK, COUNTRY_FK) VALUES(?, ?, ?)"))
        qDebug() << query.lastError().text();
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

long long CreateTournamentOrdersDialog::getGenderUID(QString genderName)
{
    QSqlQuery query;
    if (!query.prepare("SELECT * FROM SEXES"))
        qDebug() << query.lastError().text();
    if (query.exec())
    {
        while (query.next())
        {
            QString name = query.value("NAME").toString().trimmed();
            genderName = genderName.trimmed();
            if ((!name    .isEmpty() && !genderName.isEmpty() && name    .left(1).toUpper() == genderName.left(1).toUpper()))
                return query.value("UID").toLongLong();
        }
    }
    else
    {
        qDebug() << query.lastError().text();
    }

    return -100;
}

long long CreateTournamentOrdersDialog::getTournamentCategoryUID(long long sexUID, double age, double weight, long long typeUID, const QString &sexName, const QString &typeName)
{
    QSqlQuery query;
    if (!query.prepare("SELECT * FROM TOURNAMENT_CATEGORIES WHERE SEX_FK = ? AND TOURNAMENT_FK = ? AND TYPE_FK = ?"))
        qDebug() << query.lastError().text();
    query.bindValue(0, sexUID);
    query.bindValue(1, mTournamentUID);
    query.bindValue(2, typeUID);

    bool isFind = false;
    if (query.exec())
    {
        while (query.next())
        {
            double ageFrom = query.value("AGE_FROM").toDouble();
            double ageTill = query.value("AGE_TILL").toDouble();
            double weightFrom = query.value("WEIGHT_FROM").toDouble();
            double weightTill = query.value("WEIGHT_TILL").toDouble();

            double eps = 1e-8;
            if (age > ageFrom - eps && age < ageTill + eps) // a <= b && b <= c
            {
                if (weight > weightFrom + eps && weight < weightTill + eps) // a < w <= b
                {
                    isFind = true;
                    return query.value("UID").toLongLong();
                }
            }
        }

        if (!isFind)
        {
            mGlobalError += "   Не обнаружена необходимая категория турнира для:\n"
                            "      Вес: " + QString::number(weight) + "\n"
                            "      Возраст: " + QString::number(age) + "\n"
                            "      Раздел: " + typeName + "\n"
                            "      Пол: " + sexName + "\n";
                            //"   Добавьте соответствующую категорию и повторите попытку\n";
        }
    }
    else
    {
        qDebug() << query.lastError().text();
        return -100;
    }

    return -100;
}

long long CreateTournamentOrdersDialog::getSportCategoryUID(QString categoryName)
{
    QSqlQuery query;
    if (!query.prepare("SELECT * FROM SPORT_CATEGORIES"))
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();

    if (query.exec())
    {
        while (query.next())
        {
            QString sportCategory = query.value("NAME").toString();
            if (sportCategory.trimmed().toUpper() == categoryName.trimmed().toUpper())
            {
                return query.value("UID").toLongLong();
            }
        }
    }
    else
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
    }

    query.clear();
    if (!query.prepare("INSERT INTO SPORT_CATEGORIES(NAME) VALUES(?)"))
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
    query.bindValue(0, categoryName);

    if (query.exec())
    {
        query.clear();
        return getSportCategoryUID(categoryName);
    }
    else
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
        return -100;
    }
}

long long CreateTournamentOrdersDialog::getTypeUID(QString typeName)
{
    if (mType.contains(typeName))
        typeName = mType[typeName];

    QSqlQuery query;
    QStringList allNames;
    if (query.prepare("SELECT * FROM TYPES") && query.exec())
    {
        while (query.next())
        {
            QString name = query.value("NAME").toString();
            allNames << name;
            if (name.trimmed().toUpper() == typeName.trimmed().toUpper())
            {
                return query.value("UID").toLongLong();
            }
        }
    }
    else
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
    }

    DialogInsertDataInDatabase dialog(this, typeName, allNames, "Нет такой категории");
    int done = dialog.exec();
    typeName = mType[typeName] = dialog.getText();


    if (done == -1)
    {
        query.clear();
        if (!query.prepare("INSERT INTO TYPES(NAME) VALUES(?)"))
            qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
        query.bindValue(0, typeName);

        if (query.exec())
        {
            query.clear();
            return getTypeUID(typeName);
        }
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
        return -100;
    }
    return getTypeUID(typeName);
}

long long CreateTournamentOrdersDialog::getClubUID(QString clubName, long long coutryUID, long long regionUID, long long unitUID)
{
    QSqlQuery query;
    if (!query.prepare("SELECT * FROM CLUBS WHERE COUNTRY_FK = ? AND REGION_FK = ? AND REGION_UNIT_FK = ?"))
        qDebug() << query.lastError().text();
    query.bindValue(0, coutryUID);
    query.bindValue(1, regionUID);
    query.bindValue(2, unitUID);

    if (query.exec())
    {
        while (query.next())
        {
            QString club = query.value("NAME").toString();
            if (club.trimmed().toUpper() == clubName.trimmed().toUpper())
            {
                return query.value("UID").toLongLong();
            }
        }
    }
    else
    {
        qDebug() << query.lastError().text();
    }

    query.clear();
    if (!query.prepare("INSERT INTO CLUBS(NAME, COUNTRY_FK, REGION_FK, REGION_UNIT_FK) VALUES(?, ?, ?, ?)"))
        qDebug() << query.lastError().text();
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

long long CreateTournamentOrdersDialog::getCoachUID(QString coachName, long long clubUID)
{
    QSqlQuery query;
    if (!query.prepare("SELECT * FROM COACHS WHERE CLUB_FK = ?"))
        qDebug() << query.lastError().text();
    query.bindValue(0, clubUID);

    if (query.exec())
    {
        while (query.next())
        {
            QString coach = query.value("NAME").toString();
            if (coach.trimmed().toUpper() == coachName.trimmed().toUpper())
            {
                return query.value("UID").toLongLong();
            }
        }
    }
    else
    {
        qDebug() << query.lastError().text();
    }

    query.clear();
    if (!query.prepare("INSERT INTO COACHS(NAME, CLUB_FK) VALUES(?, ?)"))
        qDebug() << query.lastError().text();
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

void CreateTournamentOrdersDialog::updateSexComboBox(long long currentUID)
{
    ui->gendersCB->clear();

    QSqlQuery query;
    if (!query.prepare("SELECT * FROM SEXES"))
        qDebug() << query.lastError().text();

    if (query.exec())
    {
       int index = 0;
       while (query.next())
       {
           ui->gendersCB->addItem(query.value("NAME").toString(), Qt::DisplayRole);
           ui->gendersCB->setItemData(index, query.value("UID"), Qt::UserRole);

           if (query.value("UID").toLongLong() == currentUID)
               ui->gendersCB->setCurrentIndex(index);

           ++index;
       }
    }
    else
    {
       qDebug() << query.lastError().text();
    }

    query.clear();
}

void CreateTournamentOrdersDialog::updateCountryComboBox(long long currentUID)
{
    ui->countriesCB->clear();

    QSqlQuery query;
    if (!query.prepare("SELECT * FROM COUNTRIES"))
        qDebug() << query.lastError().text();

    if (query.exec())
    {
       int index = 0;
       while (query.next())
       {
           ui->countriesCB->addItem(query.value("NAME").toString(), Qt::DisplayRole);
           ui->countriesCB->setItemData(index, query.value("UID"), Qt::UserRole);

           if (query.value("UID").toLongLong() == currentUID)
               ui->countriesCB->setCurrentIndex(index);

           ++index;
       }
    }
    else
    {
       qDebug() << query.lastError().text();
    }

    query.clear();
}

void CreateTournamentOrdersDialog::updateRegionComboBox(long long regionUID, long long countryUID)
{
    ui->regionsCB->clear();

    QSqlQuery query;
    if (!query.prepare("SELECT * FROM REGIONS WHERE COUNTRY_FK = ? ORDER BY NAME"))
        qDebug() << query.lastError().text();
    query.bindValue(0, countryUID);

    if (query.exec())
    {
       int index = 0;
       while (query.next())
       {
           ui->regionsCB->addItem(query.value("NAME").toString(), Qt::DisplayRole);
           ui->regionsCB->setItemData(index, query.value("UID"), Qt::UserRole);

           if (query.value("UID").toLongLong() == regionUID)
               ui->regionsCB->setCurrentIndex(index);

           ++index;
       }
    }
    else
    {
       qDebug() << query.lastError().text();
    }

    query.clear();
}

void CreateTournamentOrdersDialog::updateRegionUnitComboBox(long long regionUnitUID, long long regionUID)
{
    ui->regionUnitsCB->clear();

    QSqlQuery query;
    if (!query.prepare("SELECT * FROM REGION_UNITS WHERE REGION_FK = ? ORDER BY NAME"))
        qDebug() << query.lastError().text();
    query.bindValue(0, regionUID);

    if (query.exec())
    {
       int index = 0;
       while (query.next())
       {
           ui->regionUnitsCB->addItem(query.value("NAME").toString(), Qt::DisplayRole);
           ui->regionUnitsCB->setItemData(index, query.value("UID"), Qt::UserRole);

           if (query.value("UID").toLongLong() == regionUnitUID)
               ui->regionUnitsCB->setCurrentIndex(index);

           ++index;
       }
    }
    else
    {
       qDebug() << query.lastError().text();
    }

    query.clear();
}

void CreateTournamentOrdersDialog::updateSportCategoryComboBox(long long currentUID)
{
    ui->sportCategoriesCB->clear();

    QSqlQuery query;
    if (!query.prepare("SELECT * FROM SPORT_CATEGORIES ORDER BY NAME"))
        qDebug() << query.lastError().text();

    if (query.exec())
    {
       int index = 0;
       while (query.next())
       {
           ui->sportCategoriesCB->addItem(query.value("NAME").toString(), Qt::DisplayRole);
           ui->sportCategoriesCB->setItemData(index, query.value("UID"), Qt::UserRole);

           if (query.value("UID").toLongLong() == currentUID)
               ui->sportCategoriesCB->setCurrentIndex(index);

           ++index;
       }
    }
    else
    {
       qDebug() << query.lastError().text();
    }

    query.clear();
}

void CreateTournamentOrdersDialog::updateTypeComboBox(long long currentUID)
{
    ui->typesCB->clear();

    QSqlQuery query;
    if (!query.prepare("SELECT * FROM TYPES"))
        qDebug() << query.lastError().text();

    if (query.exec())
    {
       int index = 0;
       while (query.next())
       {
           ui->typesCB->addItem(query.value("NAME").toString(), Qt::DisplayRole);
           ui->typesCB->setItemData(index, query.value("UID"), Qt::UserRole);

           if (query.value("UID").toLongLong() == currentUID)
               ui->typesCB->setCurrentIndex(index);

           ++index;
       }
    }
    else
    {
       qDebug() << query.lastError().text();
    }

    query.clear();
}

void CreateTournamentOrdersDialog::updateClubComboBox(long long clubUID, long long regionUID)
{
    ui->clubsCB->clear();

    QSqlQuery query;
    if (!query.prepare("SELECT * FROM CLUBS WHERE REGION_FK = ?  ORDER BY NAME"))
        qDebug() << query.lastError().text();
    query.bindValue(0, regionUID);

    if (query.exec())
    {
       int index = 0;
       while (query.next())
       {
           ui->clubsCB->addItem(query.value("NAME").toString(), Qt::DisplayRole);
           ui->clubsCB->setItemData(index, query.value("UID"), Qt::UserRole);

           if (query.value("UID").toLongLong() == clubUID)
               ui->clubsCB->setCurrentIndex(index);

           ++index;
       }
    }
    else
    {
       qDebug() << query.lastError().text();
    }

    query.clear();
}

void CreateTournamentOrdersDialog::updateCoachComboBox(long long coachUID, long long clubUID)
{
    ui->coachsCB->clear();

    QSqlQuery query;
    if (!query.prepare("SELECT * FROM COACHS WHERE CLUB_FK = ?  ORDER BY NAME"))
        qDebug() << query.lastError().text();
    query.bindValue(0, clubUID);

    if (query.exec())
    {
       int index = 0;
       while (query.next())
       {
           ui->coachsCB->addItem(query.value("NAME").toString(), Qt::DisplayRole);
           ui->coachsCB->setItemData(index, query.value("UID"), Qt::UserRole);

           if (query.value("UID").toLongLong() == coachUID)
               ui->coachsCB->setCurrentIndex(index);

           ++index;
       }
    }
    else
    {
       qDebug() << query.lastError().text();
    }

    query.clear();
}

void CreateTournamentOrdersDialog::updateTournamentCategoriesComboBox(long long currentUID, long long sexUID, long long typeUID)
{
    ui->tournamentCategoriesCB->clear();

    QSqlQuery query;
    if (!query.prepare("SELECT * FROM TOURNAMENT_CATEGORIES WHERE TOURNAMENT_FK = ? AND SEX_FK = ? AND TYPE_FK = ? ORDER BY SEX_FK, TYPE_FK, AGE_FROM, AGE_TILL, WEIGHT_FROM, WEIGHT_TILL"))
        qDebug() << query.lastError().text();
    query.bindValue(0, mTournamentUID);
    query.bindValue(1, sexUID);
    query.bindValue(2, typeUID);

    if (query.exec())
    {
       int index = 0;
       while (query.next())
       {
           ui->tournamentCategoriesCB->addItem(query.value("NAME").toString(), Qt::DisplayRole);
           ui->tournamentCategoriesCB->setItemData(index, query.value("UID"), Qt::UserRole);

           if (query.value("UID").toLongLong() == currentUID)
               ui->tournamentCategoriesCB->setCurrentIndex(index);

           ++index;
       }
    }
    else
    {
       qDebug() << query.lastError().text();
    }

    query.clear();
}

void CreateTournamentOrdersDialog::fillNullString(QString& s)
{
    if (s.isEmpty() || s.isNull())
        s = " ";
}
