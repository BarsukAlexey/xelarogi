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
    heads << "Место" << "Фамилия, Имя" << "Разряд" << "Регион";




    for(const std::tuple<long long, int, int, long long>& x : DBUtils::get_distinct_TYPE_FK_AgeFrom_AgeTill(database, tournamentUID))
    {

        const long long type_fk = std::get<0>(x);
        const int age_from      = std::get<1>(x);
        const int age_till      = std::get<2>(x);
        const int sex_fk        = std::get<3>(x);

        std::map<QString, QVector<long long> > stdMap = DBUtils::get_weight_and_orderUIDs(database, tournamentUID, type_fk, age_from, age_till, sex_fk).toStdMap();
        if (stdMap.empty()) continue;
        qDebug() << type_fk << age_from << age_till << sex_fk;

        int currentRow = 1;

        sheets->querySubObject("Add");
        QAxObject *sheet = sheets->querySubObject( "Item( int )", 1);

        ExcelUtils::setValue     (sheet, currentRow, 1, DBUtils::getField(database, "NAME", "TOURNAMENTS", tournamentUID));
        ExcelUtils::setWrapText  (sheet, currentRow, 1);
        //ExcelUtils::setRowAutoFit(sheet, currentRow);
        ExcelUtils::uniteRange   (sheet, currentRow, 1, currentRow, heads.size());
        //ExcelUtils::setRowAutoFit(sheet, currentRow);
        ExcelUtils::setRowHeight(sheet, currentRow, 30);
        ++currentRow;

        ExcelUtils::setValue     (sheet, currentRow, 1, "Список презёров");
        ExcelUtils::uniteRange   (sheet, currentRow, 1, currentRow, heads.size());
        ++currentRow;

        ExcelUtils::setValue     (sheet, currentRow, 1, DBUtils::getField(database, "NAME", "TYPES", type_fk));
        ExcelUtils::uniteRange   (sheet, currentRow, 1, currentRow, heads.size());
        ++currentRow;

        ExcelUtils::setValue     (sheet, currentRow, 1, DBUtils::getField(database, "SHORTNAME", "SEXES", sex_fk) + ", возраст: " + QString::number(age_from) + " - " + QString::number(age_till));
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

            ExcelUtils::setValue     (sheet, currentRow, 1, weight + " кг");
            ExcelUtils::uniteRange   (sheet, currentRow, 1, currentRow, heads.size());
            ++currentRow;
            qDebug() << "\t" << weight;

            int place = 1;
            for (const long long orderUID : val.second)
            {
                ExcelUtils::setValue(sheet, currentRow, 1, QString::number(place));
                if (orderUID != 0)
                {
                    ExcelUtils::setValue(sheet, currentRow, 2, DBUtils::getField(database, "SECOND_NAME", "ORDERS", orderUID) + " " + DBUtils::getField(database, "FIRST_NAME", "ORDERS", orderUID));
                    ExcelUtils::setValue(sheet, currentRow, 3, DBUtils::getField(database, "SHORTNAME", "SPORT_CATEGORIES", DBUtils::getField(database, "SPORT_CATEGORY_FK", "ORDERS", orderUID)));
                    ExcelUtils::setValue(sheet, currentRow, 4,  DBUtils::getField(database, "NAME", "REGIONS", DBUtils::getField(database, "REGION_FK", "ORDERS", orderUID)));
                }
                ExcelUtils::setBorder(sheet, currentRow, 1, currentRow, heads.size());
                place = qMin(3, place + 1);
                ++currentRow;
            }
        }

        for (int column = 1; column <= heads.size(); ++column)
            ExcelUtils::setColumnAutoFit(sheet, column);


        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, heads.size());
        ExcelUtils::setValue(sheet, currentRow, 1, "Главный судья: " + DBUtils::get_MAIN_JUDGE(database, tournamentUID), 0);
        ++currentRow;

        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, heads.size());
        ExcelUtils::setValue(sheet, currentRow, 1, "Главный секретарь: " + DBUtils::get_MAIN_SECRETARY(database, tournamentUID), 0);
        ++currentRow;

        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow,  heads.size());
        ExcelUtils::setValue(sheet, currentRow, 1, "Заместитель главного судьи: " + DBUtils::get_ASSOCIATE_MAIN_JUDGE(database, tournamentUID), 0);
        ++currentRow;

        ExcelUtils::setPageOrientation(sheet, 1);

        delete sheet;
    }

    delete sheets;
    delete workbook;
    delete workbooks;
}

