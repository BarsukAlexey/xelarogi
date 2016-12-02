#include "createtournamentordersdialog.h"
#include "ui_createtournamentordersdialog.h"




CreateTournamentOrdersDialog::CreateTournamentOrdersDialog(
        int tournamentUID,
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
    ui->widget->setSqlTable("ORDERS", where);
    ui->widget->setFilter("SECOND_NAME", filterSecondName);
    ui->widget->setFilter("FIRST_NAME", filterFirstName);

    connect(ui->pushButtonLoad, &QPushButton::clicked, this, &CreateTournamentOrdersDialog::loadFromExcel);

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

}

CreateTournamentOrdersDialog::~CreateTournamentOrdersDialog()
{
    delete ui;
}

void CreateTournamentOrdersDialog::loadFromExcel()
{
    if (ExcelUtils::checkExcel()) return;
    QString filePath = QFileDialog::getOpenFileName(this, tr("Выберите файл, в котором содержатся заявки"),
                                                    "", tr("Excel/Excel 97(*.xlsx *.xls);;Все файлы (*.*)"));
    //QString filePath = "D:\\Barnaul.xlsx";
    if (filePath.isEmpty()) return;


    QAxObject* excel = new QAxObject("Excel.Application", this);
    //excel->setProperty("Visible", true);
    QAxObject* workbooks = excel->querySubObject("Workbooks");
    QAxObject* workbook = workbooks->querySubObject("Open(const QString&)", filePath);

    QAxObject* sheets = workbook->querySubObject("Sheets");
    int sheetCount = sheets->dynamicCall("Count()").toInt();

    int totalOrders = 0;
    int addOrders = 0;
    int duplicateOrders = 0;
    int noUIDsOrders = 0;
    int errorOrders = 0;

    QMap<QString, QString> types;
    QMap<QString, QString> countries;
    QMap<QString, QString> regions;
    QMap<QString, QString> cities;
    QMap<QString, QString> clubs;
    QMap<QString, QString> sportKinds;
    QMap<QString, QString> coachs;

    QStringList errors;
    bool fuckOff = false;
    const QDate DATE_WEIGHTING = DBUtils::get("DATE_WEIGHTING", "TOURNAMENTS", tournamentUID).toDate();
    for (int sheetNumber = 1; sheetNumber <= sheetCount && !fuckOff; ++sheetNumber)
    {

        QAxObject* sheet = sheets->querySubObject("Item(int)", sheetNumber);
        //ExcelUtils::generateDocumentation(sheet, "sheet");

        QString countryName = ExcelUtils::getValue(sheet, 7, 2);
        if (countryName.isEmpty())
        {
            errors << "На листе \"" +  sheet->property("Name").toString() + "\" не указана страна";
            continue;
        }
        const int countryUID = getUID(countryName, "COUNTRIES", countries);
        if (countryUID == -1)
        {
            break;
        }
        ExcelUtils::setValue(sheet, 7, 2, countryName);

        QString regionName = ExcelUtils::getValue(sheet, 8, 2);
        if (regionName.isEmpty())
        {
            errors << "На листе \"" +  sheet->property("Name").toString() + "\" не указан регион";
            continue;
        }
        int regionUID;
        {
            QMap<QString, QVariant> map;
            map["COUNTRY_FK"] = countryUID;
            regionUID = getUID(regionName, "REGIONS", regions, map);
            if (regionUID == -1)
            {
                break;
            }
        }
        ExcelUtils::setValue(sheet, 8, 2, regionName);

        for (int row = 14; !fuckOff; ++row) {
            QString currentErrror;

            QString secondName = ExcelUtils::getValue(sheet, row, 1);
            if (secondName.isEmpty()) break;
            QString firstName  = ExcelUtils::getValue(sheet, row, 2);
            QString patronymic = ExcelUtils::getValue(sheet, row, 3);
            QDate birthday = ExcelUtils::get(sheet, row, 4).toDate();
            if (!birthday.isValid()) birthday = QDate::fromString(ExcelUtils::getValue(sheet, row, 4), "d.M.yyyy");
            bool weightIsCorrect;
            double weight = ExcelUtils::get(sheet, row, 5).toDouble(&weightIsCorrect);
//            qDebug() << ExcelUtils::get(sheet, row, 5)
//                     << ExcelUtils::get(sheet, row, 5).toDouble();
            QString gender = ExcelUtils::getValue(sheet, row, 6);
            QString type = ExcelUtils::getValue(sheet, row, 7);
            QString regionUnitName = ExcelUtils::getValue(sheet, row, 8);
            QString clubName = ExcelUtils::getValue(sheet, row, 9);
            QString sportKind = ExcelUtils::getValue(sheet, row, 10);
            QString coachName = ExcelUtils::getValue(sheet, row, 11);

            if (firstName.isEmpty())
            {
                currentErrror += "\t\tНе указано имя\n";
            }

            int age = -1;
            if (!birthday.isValid())
            {
                currentErrror += "\t\tНе возможно распознать дату: " + ExcelUtils::get(sheet, row, 4).toString() + "\n";
            }
            else
            {
                age = Utils::getAge(birthday, DATE_WEIGHTING);
            }

            if (!weightIsCorrect)
            {
                currentErrror += "\t\tНе возможно распознать вес: " + ExcelUtils::get(sheet, row, 5).toString() + "\n";
            }

            int genderUID = -1;
            if (gender.isEmpty())
            {
                currentErrror += "\t\tНе указан пол\n";
            }
            else
            {
                genderUID = getGenderUID(gender);
                if (genderUID == -1)
                {
                   fuckOff = true;
                   break;
                }
            }


            int typeUID = -1;
            if (type.isEmpty())
            {
                 currentErrror += "\t\tНе заполнен раздел\n";
            }
            else
            {
                typeUID = getUID(type, "TYPES", types, QMap<QString, QVariant>(), false);
                if (typeUID == -1)
                {
                   fuckOff = true;
                   break;
                }
            }


            int tournamentCategoryUID = -1;
            if (currentErrror.isEmpty())
            {
                tournamentCategoryUID = DBUtils::findUidToutnamentCategory(
                                            tournamentUID,
                                            birthday,
                                            genderUID,
                                            weight,
                                            typeUID);
                if (tournamentCategoryUID == -1)
                {
                    currentErrror += "\t\tНет подходящей категории для:\n"
                                     "\t\t           возрас: " + QString::number(age) + "\n" +
                                     "\t\t           вес: " + DBUtils::roundDouble(weight, 3) + "\n" +
                                     "\t\t           пол: " + gender + "\n" +
                                     "\t\t           раздел: " + type + "\n";
                }
            }

            int cityUID = -1;
            if (regionUnitName.isEmpty())
            {
                currentErrror += "\t\tНе указан город\n";
            }
            else
            {
                QMap<QString, QVariant> map;
                map["COUNTRY_FK"] = countryUID;
                map["REGION_FK"] = regionUID;
                cityUID = getUID(regionUnitName, "REGION_UNITS", cities, map);
                if (cityUID == -1)
                {
                    fuckOff = true;
                    break;
                }
            }

            int clubUID = -1;
            if (clubName.isEmpty())
            {
                currentErrror += "\t\tНе указан клуб\n";
            }
            else if (cityUID != -1)
            {
                QMap<QString, QVariant> map;
                map["COUNTRY_FK"] = countryUID;
                map["REGION_FK"] = regionUID;
                map["REGION_UNIT_FK"] = cityUID;
                clubUID = getUID(clubName, "CLUBS", clubs, map);
                if (clubUID == -1)
                {
                    fuckOff = true;
                    break;
                }
            }

            QVariant sportCategoryUID(QVariant::Int);
            if (!sportKind.isEmpty())
            {
                sportCategoryUID = getUID(sportKind, "SPORT_CATEGORIES", sportKinds);
                if (sportCategoryUID.toInt() == -1)
                {
                    fuckOff = true;
                    break;
                }
            }


            QVariant coachUID(QVariant::Int);
            if (!coachName.isEmpty() && clubUID != -1)
            {
                QMap<QString, QVariant> map;
                map["CLUB_FK"] = clubUID;
                coachUID = getUID(coachName, "COACHS", coachs, map);
                if (coachUID.toInt() == -1)
                {
                    fuckOff = true;
                    break;
                }
            }



            ExcelUtils::setValue(sheet, row,  7, type);
            ExcelUtils::setValue(sheet, row,  8, regionUnitName);
            ExcelUtils::setValue(sheet, row,  9, clubName);
            ExcelUtils::setValue(sheet, row, 10, sportKind);
            ExcelUtils::setValue(sheet, row, 11, coachName);

            totalOrders++;

            if (!currentErrror.isEmpty())
            {
                errors << "Лист \"" +  sheet->property("Name").toString() + "\" строка " + QString::number(row) + "\n" +
                          "Спортсмен: " + secondName + " " + firstName + " " + patronymic + "\n" +
                          currentErrror;
                noUIDsOrders++;
            }
            else
            {
                QSqlQuery findQuery;
                if (!findQuery.prepare(
                        "SELECT * FROM ORDERS "
                        "WHERE "
                        "   FIRST_NAME = ? AND SECOND_NAME = ? AND "
                        "   (IFNULL(PATRONYMIC, ?) IS NULL OR PATRONYMIC = ?) AND "
                        "   COUNTRY_FK = ? AND REGION_FK = ? AND REGION_UNIT_FK = ? AND "
                        "   BIRTHDATE = ? AND WEIGHT = ? AND SEX_FK = ? AND "
                        "   TOURNAMENT_CATEGORY_FK = ? AND TYPE_FK = ? AND "
                        "   CLUB_FK = ? AND "
                        "   (IFNULL(COACH_FK, ?) IS NULL OR COACH_FK = ?) AND "
                        "   (IFNULL(SPORT_CATEGORY_FK, ?) IS NULL OR SPORT_CATEGORY_FK = ?) "
                        ))
                    qDebug() << findQuery.lastError();
                findQuery.addBindValue(firstName);
                findQuery.addBindValue(secondName);

                findQuery.addBindValue(patronymic);
                findQuery.addBindValue(patronymic);

                findQuery.addBindValue(countryUID);
                findQuery.addBindValue(regionUID);
                findQuery.addBindValue(cityUID);
                findQuery.addBindValue(birthday);
                findQuery.addBindValue(weight);
                findQuery.addBindValue(genderUID);
                findQuery.addBindValue(tournamentCategoryUID);
                findQuery.addBindValue(typeUID);
                findQuery.addBindValue(clubUID);

                findQuery.addBindValue(coachUID);
                findQuery.addBindValue(coachUID);

                findQuery.addBindValue(sportCategoryUID);
                findQuery.addBindValue(sportCategoryUID);
                if (!findQuery.exec())
                    qDebug() << findQuery.lastError();
                if (findQuery.next())
                {
                    duplicateOrders++;
                }
                else
                {
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
                    query.addBindValue(firstName);
                    query.addBindValue(secondName);
                    query.addBindValue(patronymic);
                    query.addBindValue(countryUID);
                    query.addBindValue(regionUID);
                    query.addBindValue(cityUID);
                    query.addBindValue(birthday);
                    query.addBindValue(weight);
                    query.addBindValue(genderUID);
                    query.addBindValue(tournamentCategoryUID);
                    query.addBindValue(typeUID);
                    query.addBindValue(clubUID);
                    query.addBindValue(coachUID);
                    query.addBindValue(sportCategoryUID);

                    if (query.exec())
                        addOrders++;
                    else
                    {
                        qDebug() << query.lastError();
                        errors << "Неизвестна ошибка добавления в БД: (Спортсмен: " + secondName + " " + firstName + " " + patronymic + ") Лист " +  sheet->property("Name").toString() + " строка " + QString::number(row) + "\n";
                        errorOrders++;
                    }
                }
            }
        }
        delete sheet;
    }

    delete sheets;
    workbook->dynamicCall("Save()");
    workbook->dynamicCall("Close()");
    delete workbook;
    delete workbooks;
    excel->dynamicCall("Quit()");
    delete excel;

    if (errors.size() > 0)
    {
        errors.push_front(filePath + "\n");
        //qDebug() << errors.size() << " errors";
        ErrorMessagesDialog dlg(errors, this);
        dlg.exec();
    }

    QMessageBox::information(
                this,
                "Добавление заявок выполнено",
                "Всего распознано заявок: " + QString::number(totalOrders) + "\n" +
                "Добавлено заявок: " + QString::number(addOrders) + "\n" +
                "Не добавлены (нет категории или что-то не заполнено): " + QString::number(noUIDsOrders) + "\n" +
                "Проигнорированы (уже содержатся в базе): " + QString::number(duplicateOrders) + "\n" +
                "Не добавлены (ошибка при добавлении заявок в базу данных): " + QString::number(errorOrders));

    ui->widget->updateMyData();
}


int CreateTournamentOrdersDialog::getGenderUID(const QString& gender)
{
    QSqlQuery query;
    if (!query.prepare("SELECT * FROM SEXES"))
        qDebug() << query.lastError().text();
    if (!query.exec())
        qDebug() << query.lastError().text();
    while (query.next())
    {
        QString name = query.value("NAME").toString().trimmed();
        if ((!name.isEmpty() && !gender.isEmpty() &&
             name.left(1).toUpper() == gender.left(1).toUpper()))
            return query.value("UID").toLongLong();
    }
    return -1;
}

int CreateTournamentOrdersDialog::getUID(
        QString& name,
        const QString& table,
        QMap<QString, QString>& mapNames,
        const QMap<QString, QVariant>& map,
        bool showAddAsIs)
{
    if (mapNames.contains(name))
        name = mapNames[name];

    QSqlQuery query;
    QString where = "";
    for (const QString key : map.keys())
    {
        if (!where.isEmpty()) where += " AND ";
        where += key + " = " + map[key].toString();
    }
    if (!query.prepare("SELECT * FROM " + table + (where.isEmpty()? "" : " WHERE " + where)))
        qDebug() << query.lastError();
    if (!query.exec())
        qDebug() << query.lastError();
    while (query.next())
    {
        QString curName = query.value("NAME").toString();
        if (curName.trimmed().toUpper() == name.trimmed().toUpper())
        {
            return query.value("UID").toInt();
        }
    }
    DialogSqlTableManager dlg(this, table, "", map);
    //DialogSqlTableManager dlg(0, table, "", map);
    dlg.setModal(true);
    QString message;
    if (table == "TYPES" || table == "SPORT_CATEGORIES" || table == "COUNTRIES")
    {
        message = "Нет такой записи:\n" +
                  name;
    }
    else if (table == "REGIONS")
    {
        message =
                "В стране " + DBUtils::getField("NAME", "COUNTRIES", map["COUNTRY_FK"].toString()) +
                " нет такого региона:\n" +
                name;
    }
    else if (table == "REGION_UNITS")
    {
        message =
                "В стране " + DBUtils::getField("NAME", "COUNTRIES", map["COUNTRY_FK"].toString()) +
                " в регионе " + DBUtils::getField("NAME", "REGIONS", map["REGION_FK"].toString()) +
                " нет населённого пункта:\n" +
                name;
    }
    else if (table == "CLUBS")
    {
        message =
                "В стране " + DBUtils::getField("NAME", "COUNTRIES", map["COUNTRY_FK"].toString()) +
                " в регионе " + DBUtils::getField("NAME", "REGIONS", map["REGION_FK"].toString()) +
                " в населённом пункте " + DBUtils::getField("NAME", "REGION_UNITS", map["REGION_UNIT_FK"].toString()) +
                " нет такого клуба:\n" +
                name;
    }
    else if (table == "COACHS")
    {
        int clubUID = map["CLUB_FK"].toInt();
        message =
                "В стране "             + DBUtils::getField("NAME", "COUNTRIES"   , DBUtils::get("COUNTRY_FK"    , "CLUBS", clubUID).toString()) +
                " в регионе "           + DBUtils::getField("NAME", "REGIONS"     , DBUtils::get("REGION_FK"     , "CLUBS", clubUID).toString()) +
                " в населённом пункте " + DBUtils::getField("NAME", "REGION_UNITS", DBUtils::get("REGION_UNIT_FK", "CLUBS", clubUID).toString()) +
                " в клубе "             + DBUtils::getField("NAME", "CLUBS", clubUID) +
                " нет такого тренера:\n"  +
                name;
    }

    dlg.setVisibleShit(message, name, showAddAsIs);
    dlg.showMaximized();
    if (dlg.exec() == QDialog::Rejected)
        return -1;
    int uid = dlg.getUID();
    name = mapNames[name] = DBUtils::get("NAME", table, uid).toString();
    return uid;
}


