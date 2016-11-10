#include "createtournamentordersdialog.h"
#include "ui_createtournamentordersdialog.h"




CreateTournamentOrdersDialog::CreateTournamentOrdersDialog(
        long long tournamentUID,
        QWidget *parent,
        QString filterSecondName,
        QString filterFirstName):
    QDialog(parent),
    ui(new Ui::CreateTournamentOrdersDialog),
    tournamentUID(tournamentUID)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window);


    QString where;
    for (int id : DBUtils::getTournamentCategoryUIDs(tournamentUID))
    {
        if (!where.isEmpty()) where += ", ";
        where += QString::number(id);
    }
    where = "TOURNAMENT_CATEGORY_FK IN (" + where + ")";

    connect(ui->loadBtn, &QPushButton::clicked, this, &CreateTournamentOrdersDialog::loadFromExcel);
    ui->widget->setSqlTable("ORDERS", where);

    connect(ui->pushButtonChangeCategory, &QPushButton::clicked, [this](){
        QModelIndex index = ui->widget->getUidIndexOfSelectedRow();
        if (!index.isValid()) return;
        DialogChangeCategory dlg(index.data().toInt(), this);
        dlg.resize(800, 600);
        dlg.exec();


        QTime t; t.start();
        ui->widget->updateMyData(index.row());
        qDebug("Time elapsed: %d ms", t.elapsed());
    });

    connect(ui->pushButtonShowGrid, &QPushButton::clicked, [this](){
        QModelIndex index = ui->widget->getUidIndexOfSelectedRow();
        if (!index.isValid()) return;

        QString uidTC = DBUtils::getField("TOURNAMENT_CATEGORY_FK", "ORDERS", index.data().toInt());
        QString filter = DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", uidTC);

        DialogTournamentGrid dlg(this, filter, this->tournamentUID);
        dlg.showMaximized();
        dlg.exec();

        ui->widget->updateMyData(index.row());
    });


//    //
//    ui->filterSecondNameLE->setText(filterSecondName);
//    ui->filterFirstNameLE->setText(filterFirstName);
//    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);
//    if (parent == 0)
//        setWindowFlags(windowFlags() | Qt::WindowMinMaxButtonsHint);
}

CreateTournamentOrdersDialog::~CreateTournamentOrdersDialog()
{
    delete ui;
}

void CreateTournamentOrdersDialog::loadFromExcel()
{
//    QString filePath = QFileDialog::getOpenFileName(this, tr("Выберите файл, в котором содержатся заявки"),
//                                                    "", tr("Excel/Excel 97(*.xlsx *.xls);;Все файлы (*.*)"));
//    if (filePath.isEmpty()) return;


//    QAxObject* excel = new QAxObject("Excel.Application", this);
//    //excel->setProperty("Visible", true);
//    QAxObject* workbooks = excel->querySubObject( "Workbooks" );
//    QAxObject* workbook = workbooks->querySubObject( "Open(const QString&)", filePath );

//    QAxObject* sheets = workbook->querySubObject( "Sheets" );
//    int sheetCount = sheets->dynamicCall("Count()").toInt();

//    int totalOrders = 0;
//    int addOrders = 0;
//    int duplicateOrders = 0;
//    int noUIDsOrders = 0;
//    int errorOrders = 0;

//    QStringList errors;
//    for (int sheetNumber = 1; sheetNumber <= sheetCount; ++sheetNumber)
//    {
//        QAxObject* sheet = sheets->querySubObject( "Item( int )", sheetNumber );
//        ExcelUtils::generateDocumentation(sheet, "sheet");

//        QString countryName = ExcelUtils::getValue(sheet, 7, 2);
//        long long countryUID = getCountryUID(countryName);
//        if (ExcelUtils::getValue(sheet, 7, 2) != DBUtils::getField("NAME", "COUNTRIES", countryUID, __PRETTY_FUNCTION__))
//            ExcelUtils::setValue(sheet, 7, 2,    DBUtils::getField("NAME", "COUNTRIES", countryUID, __PRETTY_FUNCTION__));

//        QString regionName = ExcelUtils::getValue(sheet, 8, 2);
//        long long regionUID = getRegionUID(regionName, countryUID);
//        if (ExcelUtils::getValue(sheet, 8, 2) != DBUtils::getField("NAME", "REGIONS", regionUID, __PRETTY_FUNCTION__))
//            ExcelUtils::setValue(sheet, 8, 2,    DBUtils::getField("NAME", "REGIONS", regionUID, __PRETTY_FUNCTION__));

//        for (int row = 14; ; ++row) {
//            mGlobalError = "";

//            QString firstName  = ExcelUtils::getValue(sheet, row, 2);
//            QString secondName = ExcelUtils::getValue(sheet, row, 1);
//            if (secondName.trimmed().isEmpty()) break;
//            QString patronymic = ExcelUtils::getValue(sheet, row, 3);

//            QString birthday = ExcelUtils::getValue(sheet, row, 4);
//            //qDebug() << birthday;
//            QDate birthdayDate = QDate::fromString(birthday, "yyyy-MM-dd'T00:00:00'");
//            if (!birthdayDate.isValid()) birthdayDate = QDate::fromString(birthday, "dd.MM.yyyy");
//            double age = -100;
//            if (birthdayDate.isValid())
//            {
//                birthday = birthdayDate.toString("dd.MM.yyyy");
//                QDate DATE_WEIGHTING = QDate::fromString(DBUtils::getFieldDate("DATE_WEIGHTING", "TOURNAMENTS", mTournamentUID), "dd.MM.yyyy");
//                age = getAge(birthdayDate, DATE_WEIGHTING);
////                age = DATE_WEIGHTING.year() - birthdayDate.year();
////                if ( DATE_WEIGHTING.month() <  birthdayDate.month() ||
////                    (DATE_WEIGHTING.month() == birthdayDate.month() && DATE_WEIGHTING.day() < birthdayDate.day()))
////                {
////                    --age;
////                }
//                //qDebug() << "I read from excel birthdate as " << birthday << " age: " << age;
//            }
//            else
//            {
//                qDebug() << "Can't read data: " << birthday;
//                mGlobalError += "      Невозможно распознать дату " + birthday + "\n";
//            }

//            QString weight = ExcelUtils::getValue(sheet, row, 5).replace(",", ".");
//            QString gender = ExcelUtils::getValue(sheet, row, 6);
//            QString type = ExcelUtils::getValue(sheet, row, 7);
//            QString regionUnitName = ExcelUtils::getValue(sheet, row, 8);
//            QString clubName = ExcelUtils::getValue(sheet, row, 9);
//            QString sportKind = ExcelUtils::getValue(sheet, row, 10);
//            QString coachName = ExcelUtils::getValue(sheet, row, 11);

//            long long genderUID = getGenderUID(gender);
//            long long typeUID = getTypeUID(type);
//            long long tournamentCategoryUID = -100;
//            long long unitUID = getRegionUnitUID(regionUnitName, regionUID, countryUID);
//            long long clubUID = getClubUID(clubName, countryUID, regionUID, unitUID);
//            long long coachUID = getCoachUID(coachName, clubUID);
//            long long sportCategoryUID = getSportCategoryUID(sportKind);

//            if (type != DBUtils::getField("NAME", "TYPES", typeUID, __PRETTY_FUNCTION__))
//                ExcelUtils::setValue(sheet, row, 7,    DBUtils::getField("NAME", "TYPES", typeUID, __PRETTY_FUNCTION__));

//            if (genderUID <= 0) mGlobalError += "   Нет или неправильно указан пол\n";
//            if (weight.toDouble() == 0.0) mGlobalError += "   Неправильно указан вес\n";
//            if (mGlobalError.isEmpty())
//                tournamentCategoryUID = getTournamentCategoryUID(genderUID, age, weight.toDouble(), typeUID, gender, type);

//            totalOrders++;

//            if (!mGlobalError.isEmpty())
//            {
//                errors << mGlobalError + "(Спортсмен: " + secondName + " " + firstName + " " + patronymic + ") Лист " +  sheet->property("Name").toString() + " строка " + QString::number(row) + "\n";
//                noUIDsOrders++;
//            }
//            else
//            {
//                QSqlQuery findQuery;
//                if (!findQuery.prepare("SELECT * FROM ORDERS "
//                                     "WHERE "
//                                     " FIRST_NAME = ? AND SECOND_NAME = ? AND PATRONYMIC = ? AND "
//                                     " COUNTRY_FK = ? AND REGION_FK = ? AND REGION_UNIT_FK = ? AND "
//                                     " BIRTHDATE = ? AND WEIGHT = ? AND SEX_FK = ? AND "
//                                     " TOURNAMENT_CATEGORY_FK = ? AND TYPE_FK = ? AND "
//                                     " CLUB_FK = ? AND COACH_FK = ? AND "
//                                     " SPORT_CATEGORY_FK = ? "
//                                ))
//                    qDebug() << findQuery.lastError();
//                findQuery.bindValue(0, firstName);
//                findQuery.bindValue(1, secondName);
//                findQuery.bindValue(2, patronymic);
//                findQuery.bindValue(3, countryUID);
//                findQuery.bindValue(4, regionUID);
//                findQuery.bindValue(5, unitUID);
//                findQuery.bindValue(6, birthdayDate);
//                findQuery.bindValue(7, weight);
//                findQuery.bindValue(8, genderUID);
//                findQuery.bindValue(9, tournamentCategoryUID);
//                findQuery.bindValue(10, typeUID);
//                findQuery.bindValue(11, clubUID);
//                findQuery.bindValue(12, coachUID);
//                findQuery.bindValue(13, sportCategoryUID);

//                if (findQuery.exec() && findQuery.next())
//                {
//                    duplicateOrders++;
//                    //qDebug() << "дубликат (Спортсмен: " + secondName + " " + firstName + " " + patronymic + ") Лист " +  sheet->property("Name").toString() + " строка " + QString::number(row) ;
//                }
//                else
//                {
//                    //qDebug() << __LINE__ << __PRETTY_FUNCTION__ << findQuery.lastError();

//                    QSqlQuery query;
//                    if (!query.prepare(  "INSERT INTO ORDERS("
//                                         "FIRST_NAME, SECOND_NAME, PATRONYMIC, "
//                                         "COUNTRY_FK, REGION_FK, REGION_UNIT_FK, "
//                                         "BIRTHDATE, WEIGHT, SEX_FK, "
//                                         "TOURNAMENT_CATEGORY_FK, TYPE_FK, "
//                                         "CLUB_FK, COACH_FK, "
//                                         "SPORT_CATEGORY_FK) "
//                                    "VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"
//                                    ))
//                        qDebug() << query.lastError();
//                    query.bindValue(0, firstName);
//                    query.bindValue(1, secondName);
//                    query.bindValue(2, patronymic);
//                    query.bindValue(3, countryUID);
//                    query.bindValue(4, regionUID);
//                    query.bindValue(5, unitUID);
//                    query.bindValue(6, birthdayDate);
//                    query.bindValue(7, weight);
//                    query.bindValue(8, genderUID);
//                    query.bindValue(9, tournamentCategoryUID);
//                    query.bindValue(10, typeUID);
//                    query.bindValue(11, clubUID);
//                    query.bindValue(12, coachUID);
//                    query.bindValue(13, sportCategoryUID);

//                    if (query.exec())
//                        addOrders++;
//                    else
//                    {
//                        qDebug() << query.lastError();
//                        errors << "\n\nНеизвестна ошибка добавления в БД: (Спортсмен: " + secondName + " " + firstName + " " + patronymic + ") Лист " +  sheet->property("Name").toString() + " строка " + QString::number(row) + "\n\n";
//                        errorOrders++;
//                    }
//                }
//            }
//        }
//    }

//    workbook->dynamicCall("Save()");
//    workbook->dynamicCall("Close()");
//    delete workbook;
//    excel->dynamicCall("Quit()");
//    delete excel;

//    if (errors.size() > 0)
//    {
//        qDebug() << errors.size() << " errors";
//        ErrorMessagesDialog dlg(errors, this);
//        dlg.exec();
//    }

//    QMessageBox::information(this, "Добавление заявок выполнено", "Всего распознано заявок: " + QString::number(totalOrders) + "\n"
//                                                                  "Добавлено заявок: " + QString::number(addOrders) + "\n"
//                                                                  "Не добавлены (нет категории): " + QString::number(noUIDsOrders) + "\n"
//                                                                  "Проигнорированы (уже содержатся в базе): " + QString::number(duplicateOrders) + "\n"
//                                                                  "Произошла ошибка при добавлении заявок: " + QString::number(errorOrders));

//    QSqlRelationalTableModel* model = dynamic_cast<QSqlRelationalTableModel*>(ui->tableView->model());
//    model->select();
//    ui->tableView->resizeColumnsToContents();
}


int CreateTournamentOrdersDialog::getGenderUID(QString genderName)
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

int CreateTournamentOrdersDialog::getTypeUID(QString typeName)
{
    return -1;
//    if (mType.contains(typeName))
//        typeName = mType[typeName];

//    QSqlQuery query;
//    QStringList allNames;
//    if (query.prepare("SELECT * FROM TYPES") && query.exec())
//    {
//        while (query.next())
//        {
//            QString name = query.value("NAME").toString();
//            allNames << name;
//            if (name.trimmed().toUpper() == typeName.trimmed().toUpper())
//            {
//                return query.value("UID").toLongLong();
//            }
//        }
//    }
//    else
//    {
//        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
//    }

//    DialogInsertDataInDatabase dialog(this, typeName, allNames, "Нет такой категории");
//    int done = dialog.exec();
//    typeName = mType[typeName] = dialog.getText();


//    if (done == -1)
//    {
//        query.clear();
//        if (!query.prepare("INSERT INTO TYPES(NAME) VALUES(?)"))
//            qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
//        query.bindValue(0, typeName);

//        if (query.exec())
//        {
//            query.clear();
//            return getTypeUID(typeName);
//        }
//        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
//        return -100;
//    }
//    return getTypeUID(typeName);
}



QVariant CreateTournamentOrdersDialog::getSportCategoryUID(QString categoryName)
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

QVariant CreateTournamentOrdersDialog::getCountryUID(QString countryName)
{
    return -1;
}

QVariant CreateTournamentOrdersDialog::getRegionUID(QString regionName, long long countryUID)
{
    return -1;
//    if (mRegion.contains(regionName))
//    {
//        regionName = mRegion[regionName];
//    }

//    QSqlQuery query;
//    QStringList allNames;
//    if (!query.prepare("SELECT * FROM REGIONS WHERE COUNTRY_FK = ?"))
//        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
//    query.bindValue(0, countryUID);

//    if (query.exec())
//    {
//        while (query.next())
//        {
//            QString region = query.value("NAME").toString();
//            allNames << region;
//            if (region.trimmed().toUpper() == regionName.trimmed().toUpper())
//            {
//                return query.value("UID").toLongLong();
//            }
//        }
//    }
//    else
//    {
//        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
//    }

//    DialogInsertDataInDatabase dialog(this, regionName, allNames, "В стране " + DBUtils::getField("NAME","COUNTRIES", countryUID, __PRETTY_FUNCTION__) + " нет такого региона");
//    int done = dialog.exec();
//    regionName = mRegion[regionName] = dialog.getText();

//    if (done == -1)
//    {
//        query.clear();
//        if (!query.prepare("INSERT INTO REGIONS(NAME, COUNTRY_FK) VALUES(?, ?)"))
//            qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
//        query.bindValue(0, regionName);
//        query.bindValue(1, countryUID);

//        if (query.exec())
//            return getRegionUID(regionName, countryUID);
//        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
//        return -100;
//    }
//    return getRegionUID(regionName, countryUID);
}

QVariant CreateTournamentOrdersDialog::getRegionUnitUID(QString unitName, long long regionUID, long long countryUID)
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




QVariant CreateTournamentOrdersDialog::getClubUID(QString clubName, long long coutryUID, long long regionUID, long long unitUID)
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

QVariant CreateTournamentOrdersDialog::getCoachUID(QString coachName, long long clubUID)
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


