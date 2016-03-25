#include "trophygenerator.h"

TrophyGenerator::TrophyGenerator(const QSqlDatabase& database, const long long tournamentUID, QObject *parent) :
    QObject(parent),
    mTournamentUID(tournamentUID)
{
    QString filePath = QFileDialog::getOpenFileName(NULL, tr("Выберите файл, в котором содержится шаблон для формирования грамот"),
                                                    "./", tr("Excel (*.xlsx);;Excel 97 (*.xls)"));


    if (filePath.isEmpty() == false)
    {
        QAxWidget excel("Excel.Application");
        excel.setProperty("Visible", true);
        QAxObject *workbooks = excel.querySubObject("WorkBooks");
        QAxObject *workbook = workbooks->querySubObject("Open(const QString&)", filePath);
        QAxObject *sheets = workbook->querySubObject("Sheets");

        for(const std::tuple<long long, int, int, long long>& x : DBUtils::get_distinct_TYPE_FK_AgeFrom_AgeTill(tournamentUID))
        {

            const long long type_fk = std::get<0>(x);
            const int age_from      = std::get<1>(x);
            const int age_till      = std::get<2>(x);
            const int sex_fk        = std::get<3>(x);

            std::map<QString, QVector<long long> > stdMap = DBUtils::get_weight_and_orderUIDs(tournamentUID, type_fk, age_from, age_till, sex_fk).toStdMap();
            if (stdMap.empty()) continue;

            QString tournamentName = DBUtils::getField("NAME", "TOURNAMENTS", tournamentUID);
            QString genderName = DBUtils::getField("NAME", "SEXES", sex_fk);
            QString genderShortName = DBUtils::getField("SHORTNAME", "SEXES", sex_fk);
            QString typeName = DBUtils::getField("NAME", "TYPES", type_fk);
            QString ageFrom = QString::number(age_from);
            QString ageTill = QString::number(age_till);
            QString ageInterval = ageFrom + "-"  + ageTill + " лет";

            for (const auto & val : stdMap)
            {
                const QString weightInterval = val.first;

                int place = 1;
                for (const long long orderUID : val.second)
                {
                    if (orderUID != 0)
                    {
                        int sheetCount = sheets->dynamicCall("Count()").toInt();
                        QAxObject *sheetToCopy  = sheets->querySubObject( "Item( int )", sheetCount);
                        QString newSheetName = sheetToCopy->property("Name").toString() + " (2)";
                        sheetToCopy->dynamicCall("Copy(const QVariant&)", sheetToCopy->asVariant());
                        delete sheetToCopy;

                        QAxObject * newSheet = workbook->querySubObject("Worksheets(const QVariant&)", newSheetName);
                        newSheetName = QString::number(place) + "," + genderShortName + "," + typeName + "," + QString::number(rand()) + "," + ageInterval + "," + weightInterval;
                        newSheet->setProperty("Name", newSheetName.left(31));

                        QString secondName = DBUtils::getField("SECOND_NAME", "ORDERS", orderUID);
                        QString firstName = DBUtils::getField("FIRST_NAME", "ORDERS", orderUID);
                        QString fullName = secondName + " " + firstName;

                        QString weight = DBUtils::getField("WEIGHT", "ORDERS", orderUID);
                        QDate currentDate = QDate::currentDate();
                        QDate birthdate = QDate::fromString(DBUtils::getField("BIRTHDATE", "ORDERS", orderUID), "yyyy-MM-dd");
                        int age = currentDate.year() - birthdate.year();
                        if (currentDate.month() > birthdate.month())
                            age--;
                        else if (currentDate.month() == birthdate.month() &&
                                 currentDate.day() > birthdate.day())
                            age--;

                        QString sportCategoryName = DBUtils::getField("NAME", "SPORT_CATEGORIES", DBUtils::getField("SPORT_CATEGORY_FK", "ORDERS", orderUID));
                        QString regionName = DBUtils::getField("NAME", "REGIONS", DBUtils::getField("REGION_FK", "ORDERS", orderUID));

                        //ExcelUtils::setValue(sheet, currentRow, 4,  DBUtils::getField("NAME", "REGIONS", DBUtils::getField("REGION_FK", "ORDERS", orderUID)));

                        TrophyGeneratorSettingsDialog::ExcelPoint somePoint;
                        somePoint = TrophyGeneratorSettingsDialog::mFullName;
                        if (somePoint.isUsed)
                        {
                            ExcelUtils::setValue(newSheet, somePoint.row, somePoint.column, fullName);
                        }

                        somePoint = TrophyGeneratorSettingsDialog::mPlace;
                        if (somePoint.isUsed)
                        {
                            ExcelUtils::setValue(newSheet, somePoint.row, somePoint.column, QString::number(place));
                        }

                        somePoint = TrophyGeneratorSettingsDialog::mSportCategory;
                        if (somePoint.isUsed)
                        {
                            ExcelUtils::setValue(newSheet, somePoint.row, somePoint.column, sportCategoryName);
                        }

                        somePoint = TrophyGeneratorSettingsDialog::mRegion;
                        if (somePoint.isUsed)
                        {
                            ExcelUtils::setValue(newSheet, somePoint.row, somePoint.column, regionName);
                        }

                        somePoint = TrophyGeneratorSettingsDialog::mTournament;
                        if (somePoint.isUsed)
                        {
                            ExcelUtils::setValue(newSheet, somePoint.row, somePoint.column, tournamentName);
                        }

                        somePoint = TrophyGeneratorSettingsDialog::mType;
                        if (somePoint.isUsed)
                        {
                            ExcelUtils::setValue(newSheet, somePoint.row, somePoint.column, typeName);
                        }

                        somePoint = TrophyGeneratorSettingsDialog::mAge;
                        if (somePoint.isUsed)
                        {
                            ExcelUtils::setValue(newSheet, somePoint.row, somePoint.column, QString::number(age));
                        }

                        somePoint = TrophyGeneratorSettingsDialog::mAges;
                        if (somePoint.isUsed)
                        {
                            ExcelUtils::setValue(newSheet, somePoint.row, somePoint.column, ageInterval);
                        }

                        somePoint = TrophyGeneratorSettingsDialog::mWeight;
                        if (somePoint.isUsed)
                        {
                            ExcelUtils::setValue(newSheet, somePoint.row, somePoint.column, weight);
                        }

                        somePoint = TrophyGeneratorSettingsDialog::mWeights;
                        if (somePoint.isUsed)
                        {
                            ExcelUtils::setValue(newSheet, somePoint.row, somePoint.column, weightInterval);
                        }

                        delete newSheet;
                    }
                    else
                    {
                        break;
                    }


                    place = qMin(3, place + 1);
                    //++currentRow;
                }
            }
        }

        delete sheets;
        delete workbook;
        delete workbooks;
    }
}

