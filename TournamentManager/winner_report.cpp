#include "winner_report.h"
#include "db_utils.h"
#include "excel_utils.h"

#include <QAxWidget>
#include <QAxObject>
#include <QDebug>

WinnerReport::WinnerReport(const QSqlDatabase& database, const long long tournamentUID, QObject* parent)
    : QObject(parent)
{
    QAxWidget excel("Excel.Application");
    excel.setProperty("Visible", true);
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
    workbooks->dynamicCall("Add");
    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");
    QAxObject *sheets = workbook->querySubObject("WorkSheets");

    QStringList heads;
    heads << "Место" << "Фамилия, Имя" << "Разряд" << "Регион" << "Тренер";




    for(const std::tuple<long long, int, int, long long>& x : DBUtils::get_distinct_TYPE_FK_AgeFrom_AgeTill(tournamentUID))
    {

        const long long type_fk = std::get<0>(x);
        const int age_from      = std::get<1>(x);
        const int age_till      = std::get<2>(x);
        const int sex_fk        = std::get<3>(x);

        std::map<QString, QVector<long long> > stdMap = DBUtils::get_weight_and_orderUIDs(tournamentUID, type_fk, age_from, age_till, sex_fk).toStdMap();
        if (stdMap.empty()) continue;
        //qDebug() << type_fk << age_from << age_till << sex_fk;

        int currentRow = 1;

        sheets->querySubObject("Add");
        QAxObject *sheet = sheets->querySubObject( "Item( int )", 1);

        QString sheetName = DBUtils::getField("SHORTNAME", "SEXES", sex_fk);
        sheetName += "," + DBUtils::getField("NAME", "TYPES", type_fk);
        sheetName += "," + QString::number(age_from) + "-" + QString::number(age_till) + "лет";
        sheet->setProperty("Name", sheetName.left(31));


        ExcelUtils::setTournamentName(sheet, DBUtils::getTournamentNameAsHeadOfDocument(database, tournamentUID), currentRow, 1, currentRow, heads.size());
//        ExcelUtils::setValue     (sheet, currentRow, 1, DBUtils::getField("NAME", "TOURNAMENTS", tournamentUID));
//        ExcelUtils::setFontBold(sheet, currentRow, 1, true);
//        ExcelUtils::setWrapText  (sheet, currentRow, 1);
//        ExcelUtils::uniteRange   (sheet, currentRow, 1, currentRow, heads.size());
//        ExcelUtils::setRowHeight(sheet, currentRow, 30);

        ++currentRow;

        ExcelUtils::setValue     (sheet, currentRow, 1, "Список призёров");
        ExcelUtils::uniteRange   (sheet, currentRow, 1, currentRow, heads.size());
        ++currentRow;

        ExcelUtils::setValue     (sheet, currentRow, 1, DBUtils::getField("NAME", "TYPES", type_fk));
        ExcelUtils::uniteRange   (sheet, currentRow, 1, currentRow, heads.size());
        ++currentRow;

        ExcelUtils::setValue     (sheet, currentRow, 1, DBUtils::getField("SHORTNAME", "SEXES", sex_fk) + ", возраст: " + QString::number(age_from) + " - " + QString::number(age_till));
        ExcelUtils::uniteRange   (sheet, currentRow, 1, currentRow, heads.size());
        ++currentRow;

        {
            int  column = 1;
            for (const QString& s : heads)
            {
                ExcelUtils::setValue(sheet, currentRow, column, s);
                ExcelUtils::setBorder(sheet, currentRow, column, currentRow, column);
                ++column;
            }
            ++currentRow;
        }

        for (const auto & val : stdMap)
        {
            const QString& weight = val.first;

            ExcelUtils::setValue     (sheet, currentRow, 1, weight);
            ExcelUtils::uniteRange   (sheet, currentRow, 1, currentRow, heads.size());
            ++currentRow;
            //qDebug() << "\t" << weight;

            int place = 1;
            for (const long long orderUID : val.second)
            {
                ExcelUtils::setValue(sheet, currentRow, 1, QString::number(place));
                if (orderUID == 0)
                    break;
                ExcelUtils::setValue(sheet, currentRow, 2, DBUtils::getField("SECOND_NAME", "ORDERS", orderUID) + " " + DBUtils::getField("FIRST_NAME", "ORDERS", orderUID));
                ExcelUtils::setValue(sheet, currentRow, 3, DBUtils::getField("NAME", "SPORT_CATEGORIES", DBUtils::getField("SPORT_CATEGORY_FK", "ORDERS", orderUID)));
                ExcelUtils::setValue(sheet, currentRow, 4, DBUtils::getField("NAME", "REGIONS", DBUtils::getField("REGION_FK", "ORDERS", orderUID)));
                ExcelUtils::setValue(sheet, currentRow, 5, DBUtils::getField("NAME", "COACHS", DBUtils::getField("COACH_FK", "ORDERS", orderUID)));

                ExcelUtils::setBorder(sheet, currentRow, 1, currentRow, heads.size());
                place = qMin(3, place + 1);
                ++currentRow;
            }
        }

        for (int column = 1; column <= heads.size(); ++column)
            ExcelUtils::setColumnAutoFit(sheet, column);


        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 2);
        ExcelUtils::setRowHeight(sheet, currentRow, 25);
        ExcelUtils::setValue(sheet, currentRow, 1, "Главный судья: ", 0);
        ExcelUtils::setValue(sheet, currentRow, 4, DBUtils::get_MAIN_JUDGE(database, tournamentUID), 0);
        ++currentRow;

        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 2);
        ExcelUtils::setRowHeight(sheet, currentRow, 25);
        ExcelUtils::setValue(sheet, currentRow, 1, "Главный секретарь: ", 0);
        ExcelUtils::setValue(sheet, currentRow, 4, DBUtils::get_MAIN_SECRETARY(database, tournamentUID), 0);
        ++currentRow;

        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 2);
        ExcelUtils::setRowHeight(sheet, currentRow, 25);
        ExcelUtils::setValue(sheet, currentRow, 1, "Зам. главного судьи: ", 0);
        ExcelUtils::setValue(sheet, currentRow, 4, DBUtils::get_ASSOCIATE_MAIN_JUDGE(database, tournamentUID), 0);
        ++currentRow;

        ExcelUtils::setPageOrientation(sheet, 1);
        ExcelUtils::setCenterHorizontally(sheet, true);

        delete sheet;
    }

    delete sheets;
    delete workbook;
    delete workbooks;
}

