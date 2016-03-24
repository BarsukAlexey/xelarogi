#include "report_manda.h"
#include "excel_utils.h"
#include "db_utils.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

#include <QAxWidget>
#include <QAxObject>

ReportManda::ReportManda(const QSqlDatabase& database, const long long tournamentUID)
{
    QSqlQuery queryCategory(
                "SELECT SEX_FK, TYPE_FK, AGE_FROM, AGE_TILL "
                "FROM TOURNAMENT_CATEGORIES "
                "WHERE TOURNAMENT_FK = ? "
                "GROUP BY SEX_FK, TYPE_FK, AGE_FROM, AGE_TILL "
                "ORDER BY SEX_FK, TYPE_FK, AGE_FROM, AGE_TILL "
        ,database);
    queryCategory.bindValue(0, tournamentUID);
    if (!queryCategory.exec())
    {
        qDebug() << "\n" << __PRETTY_FUNCTION__ << "\n" << queryCategory.lastError().text() << "\n" << queryCategory.lastQuery() << "\n";
        return;
    }

    QAxWidget excel("Excel.Application");
    excel.setProperty("Visible", true);
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
    workbooks->dynamicCall("Add");
    ExcelUtils::generateDocumentation(workbooks, "workbooks");

    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");
    QAxObject *sheets = workbook->querySubObject("WorkSheets");

    while (queryCategory.next())
    {
        QString SEX_FK  = queryCategory.value("SEX_FK").toString();
        QString TYPE_FK  = queryCategory.value("TYPE_FK").toString();
        QString AGE_FROM = queryCategory.value("AGE_FROM").toString();
        QString AGE_TILL = queryCategory.value("AGE_TILL").toString();

        QSqlQuery queryClubs(
            "SELECT CLUBS.UID AS clubid12 "
            "FROM ORDERS "
                "INNER JOIN CLUBS ON CLUBS.UID = ORDERS.CLUB_FK "
                "INNER JOIN TOURNAMENT_CATEGORIES ON TOURNAMENT_CATEGORIES.UID = ORDERS.TOURNAMENT_CATEGORY_FK "
            "WHERE "
                "TOURNAMENT_CATEGORIES.SEX_FK   = ? AND "
                "TOURNAMENT_CATEGORIES.TYPE_FK  = ? AND "
                "TOURNAMENT_CATEGORIES.AGE_FROM = ? AND "
                "TOURNAMENT_CATEGORIES.AGE_TILL = ? AND "
                "ORDERS.IS_VALID = 1 "
            "GROUP BY CLUBS.UID"
            ,database);
        queryClubs.bindValue(0, SEX_FK);
        queryClubs.bindValue(1, TYPE_FK);
        queryClubs.bindValue(2, AGE_FROM);
        queryClubs.bindValue(3, AGE_TILL);
        if (!queryClubs.exec())
        {
            qDebug() << "\n" << __PRETTY_FUNCTION__ << "\n" << queryClubs.lastError().text() << "\n" << queryClubs.lastQuery() << "\n";
            continue;
        }
        QVector<QString> uidsOfClubs;
        while (queryClubs.next()) uidsOfClubs << queryClubs.value("clubid12").toString();
        QVector<int> sumOfRow(uidsOfClubs.size());
        //qDebug() << DBUtils::getField(database, "NAME", "TYPES", TYPE_FK) << AGE_FROM << AGE_TILL << uidsOfClubs;

        if (uidsOfClubs.isEmpty()) continue;

        sheets->querySubObject("Add");
        QAxObject *sheet = sheets->querySubObject( "Item( int )", 1);
        const int startRow = 7;
        for (int i = 0; i < uidsOfClubs.size(); ++i)
        {
            ExcelUtils::setValue(sheet, startRow + i, 1, QString::number(i + 1));
            ExcelUtils::setValue(sheet, startRow + i, 2, DBUtils::getField(database, "NAME", "CLUBS", uidsOfClubs[i]) + ", " + DBUtils::getField(database, "NAME", "REGIONS", DBUtils::getField(database, "REGION_FK", "CLUBS", uidsOfClubs[i])));
        }
        ExcelUtils::setBorder (sheet, startRow, 1, startRow + uidsOfClubs.size() - 1, 2);
        ExcelUtils::setBorder (sheet, startRow, 1, startRow + uidsOfClubs.size() - 1, 2, 3, ExcelUtils::Border::xlEdgeTop);
        ExcelUtils::setBorder (sheet, startRow, 1, startRow + uidsOfClubs.size() - 1, 2, 3, ExcelUtils::Border::xlEdgeBottom);
        ExcelUtils::setBorder (sheet, startRow, 1, startRow + uidsOfClubs.size() - 1, 1, 3, ExcelUtils::Border::xlEdgeLeft);
        ExcelUtils::setBorder (sheet, startRow, 2, startRow + uidsOfClubs.size() - 1, 2, 3, ExcelUtils::Border::xlEdgeLeft);

        QSqlQuery queryWEIGHTS(
            "SELECT WEIGHT_FROM, WEIGHT_TILL "
            "FROM ORDERS "
                "INNER JOIN CLUBS ON CLUBS.UID = ORDERS.CLUB_FK "
                "INNER JOIN TOURNAMENT_CATEGORIES ON TOURNAMENT_CATEGORIES.UID = ORDERS.TOURNAMENT_CATEGORY_FK "
            "WHERE "
                "TOURNAMENT_CATEGORIES.SEX_FK   = ? AND "
                "TOURNAMENT_CATEGORIES.TYPE_FK  = ? AND "
                "TOURNAMENT_CATEGORIES.AGE_FROM = ? AND "
                "TOURNAMENT_CATEGORIES.AGE_TILL = ? AND "
                "ORDERS.IS_VALID = 1 "
            "GROUP BY WEIGHT_FROM, WEIGHT_TILL "
            "ORDER BY WEIGHT_FROM, WEIGHT_TILL "
            ,database);

        queryWEIGHTS.bindValue(0, SEX_FK);
        queryWEIGHTS.bindValue(1, TYPE_FK);
        queryWEIGHTS.bindValue(2, AGE_FROM);
        queryWEIGHTS.bindValue(3, AGE_TILL);
        if (!queryWEIGHTS.exec())
        {
            qDebug() << "\n" << __PRETTY_FUNCTION__ << "\n" << queryWEIGHTS.lastError().text() << "\n" << queryWEIGHTS.lastQuery() << "\n";
            continue;
        }

        int currentColumns = 3;
        while (queryWEIGHTS.next())
        {
            QString WEIGHT_FROM = queryWEIGHTS.value("WEIGHT_FROM").toString();
            QString WEIGHT_TILL = queryWEIGHTS.value("WEIGHT_TILL").toString();
            //qDebug() << "\t" << WEIGHT_FROM << WEIGHT_TILL;

            QSqlQuery querySPORT_CATEGORIES(
                "SELECT SPORT_CATEGORIES.UID AS UID_SC "
                "FROM ORDERS "
                    "INNER JOIN CLUBS                 ON CLUBS.UID                 = ORDERS.CLUB_FK "
                    "INNER JOIN TOURNAMENT_CATEGORIES ON TOURNAMENT_CATEGORIES.UID = ORDERS.TOURNAMENT_CATEGORY_FK "
                    "INNER JOIN SPORT_CATEGORIES      ON SPORT_CATEGORIES.UID      = ORDERS.SPORT_CATEGORY_FK "
                "WHERE "
                    "TOURNAMENT_CATEGORIES.SEX_FK      = ? AND "
                    "TOURNAMENT_CATEGORIES.TYPE_FK     = ? AND "
                    "TOURNAMENT_CATEGORIES.AGE_FROM    = ? AND "
                    "TOURNAMENT_CATEGORIES.AGE_TILL    = ? AND "
                    "TOURNAMENT_CATEGORIES.WEIGHT_FROM = ? AND "
                    "TOURNAMENT_CATEGORIES.WEIGHT_TILL = ? AND "
                    "ORDERS.IS_VALID = 1 AND "
                    "1 <= LENGTH(SPORT_CATEGORIES.NAME)"
                "GROUP BY "
                    "UID_SC "
                "ORDER BY "
                    "max(SPORT_CATEGORIES.PRIORITY) "
                ,database);
            querySPORT_CATEGORIES.bindValue(0, SEX_FK);
            querySPORT_CATEGORIES.bindValue(1, TYPE_FK);
            querySPORT_CATEGORIES.bindValue(2, AGE_FROM);
            querySPORT_CATEGORIES.bindValue(3, AGE_TILL);
            querySPORT_CATEGORIES.bindValue(4, WEIGHT_FROM);
            querySPORT_CATEGORIES.bindValue(5, WEIGHT_TILL);
            if (!querySPORT_CATEGORIES.exec())
            {
                qDebug() << "\n" << __PRETTY_FUNCTION__ << "\n" << querySPORT_CATEGORIES.lastError().text() << "\n" << querySPORT_CATEGORIES.lastQuery() << "\n";
                continue;
            }


            int countSPORT_CATEGORIES = 0;
            int sumOfValuesForWeight = 0;
            while (querySPORT_CATEGORIES.next())
            {
                QString SPORT_CATEGORY = querySPORT_CATEGORIES.value("UID_SC").toString();
                //qDebug() << "\t\t" << DBUtils::getField(database, "NAME", "SPORT_CATEGORIES", SPORT_CATEGORY);
                ++countSPORT_CATEGORIES;
                int sumOfValuesForWeightAndSportCategory = 0;

                ExcelUtils::setValue(sheet, startRow - 1, currentColumns, DBUtils::getField(database, "NAME", "SPORT_CATEGORIES", SPORT_CATEGORY));

                for (int i = 0; i < uidsOfClubs.size(); ++i)
                {
                    QSqlQuery query(
                        "SELECT COUNT(*) AS CNT "
                        "FROM ORDERS "
                            "INNER JOIN CLUBS                 ON CLUBS.UID                 = ORDERS.CLUB_FK "
                            "INNER JOIN TOURNAMENT_CATEGORIES ON TOURNAMENT_CATEGORIES.UID = ORDERS.TOURNAMENT_CATEGORY_FK "
                            "INNER JOIN SPORT_CATEGORIES      ON SPORT_CATEGORIES.UID      = ORDERS.SPORT_CATEGORY_FK "
                        "WHERE "
                            "TOURNAMENT_CATEGORIES.SEX_FK      = ? AND "
                            "TOURNAMENT_CATEGORIES.TYPE_FK     = ? AND "
                            "TOURNAMENT_CATEGORIES.AGE_FROM    = ? AND "
                            "TOURNAMENT_CATEGORIES.AGE_TILL    = ? AND "
                            "TOURNAMENT_CATEGORIES.WEIGHT_FROM = ? AND "
                            "TOURNAMENT_CATEGORIES.WEIGHT_TILL = ? AND "
                            "ORDERS.IS_VALID = 1                   AND "
                            "1 <= LENGTH(SPORT_CATEGORIES.NAME)    AND "
                            "SPORT_CATEGORIES.UID = ?              AND "
                            "CLUBS.UID = ? "
                        ,database);
                    query.bindValue(0, SEX_FK);
                    query.bindValue(1, TYPE_FK);
                    query.bindValue(2, AGE_FROM);
                    query.bindValue(3, AGE_TILL);
                    query.bindValue(4, WEIGHT_FROM);
                    query.bindValue(5, WEIGHT_TILL);
                    query.bindValue(6, SPORT_CATEGORY);
                    query.bindValue(7, uidsOfClubs[i]);

                    if (!query.exec() || !query.next())
                    {
                        qDebug() << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
                        continue;
                    }
                    if (query.value("CNT").toString() != "0")
                    {
                        ExcelUtils::setValue(sheet, startRow + i, currentColumns, query.value("CNT").toString());
                        sumOfValuesForWeight                 += query.value("CNT").toInt();
                        sumOfValuesForWeightAndSportCategory += query.value("CNT").toInt();
                        sumOfRow[i]                          += query.value("CNT").toInt();
                    }
                }

                ExcelUtils::setValue(sheet, startRow + uidsOfClubs.size(), currentColumns, QString::number(sumOfValuesForWeightAndSportCategory));
                //
                ++currentColumns;
            }
            if (0 < countSPORT_CATEGORIES)
            {
                ExcelUtils::uniteRange(sheet, startRow - 2, currentColumns - countSPORT_CATEGORIES, startRow - 2, currentColumns - 1);
                ExcelUtils::setValue  (sheet, startRow - 2, currentColumns - countSPORT_CATEGORIES, DBUtils::getNormanWeightRange(WEIGHT_FROM.toDouble(), WEIGHT_TILL.toDouble()));

                ExcelUtils::uniteRange(sheet, startRow + uidsOfClubs.size() + 1, currentColumns - countSPORT_CATEGORIES, startRow + uidsOfClubs.size() + 1, currentColumns - 1);
                ExcelUtils::setValue  (sheet, startRow + uidsOfClubs.size() + 1, currentColumns - countSPORT_CATEGORIES, QString::number(sumOfValuesForWeight));

                ExcelUtils::setBorder (sheet, startRow - 2, currentColumns - countSPORT_CATEGORIES, startRow + uidsOfClubs.size() + 1, currentColumns - 1, 2, ExcelUtils::Border::all);

                ExcelUtils::setBorder (sheet, startRow - 2, currentColumns - countSPORT_CATEGORIES, startRow + uidsOfClubs.size() + 1, currentColumns - 1, 3, ExcelUtils::Border::xlEdgeTop);
                ExcelUtils::setBorder (sheet, startRow - 2, currentColumns - countSPORT_CATEGORIES, startRow + uidsOfClubs.size() + 1, currentColumns - 1, 3, ExcelUtils::Border::xlEdgeBottom);
                ExcelUtils::setBorder (sheet, startRow - 2, currentColumns - countSPORT_CATEGORIES, startRow + uidsOfClubs.size() + 1, currentColumns - 1, 3, ExcelUtils::Border::xlEdgeLeft);
                ExcelUtils::setBorder (sheet, startRow - 2, currentColumns - countSPORT_CATEGORIES, startRow + uidsOfClubs.size() + 1, currentColumns - 1, 3, ExcelUtils::Border::xlEdgeRight);

                ExcelUtils::setBorder (sheet, startRow - 1, currentColumns - countSPORT_CATEGORIES, startRow - 1, currentColumns - 1, 3, ExcelUtils::Border::xlEdgeBottom);
                ExcelUtils::setBorder (sheet, startRow + uidsOfClubs.size()    , currentColumns - countSPORT_CATEGORIES, startRow + uidsOfClubs.size()    , currentColumns - 1, 3, ExcelUtils::Border::xlEdgeBottom);
                ExcelUtils::setBorder (sheet, startRow + uidsOfClubs.size() - 1, currentColumns - countSPORT_CATEGORIES, startRow + uidsOfClubs.size() - 1, currentColumns - 1, 3, ExcelUtils::Border::xlEdgeBottom);
            }
        }

        ExcelUtils::uniteRange(sheet, startRow - 2, currentColumns, startRow - 1, currentColumns);
        ExcelUtils::setValue(sheet, startRow - 2, currentColumns, "Всего");
        for (int i = 0; i < uidsOfClubs.size(); ++i)
            ExcelUtils::setValue(sheet, startRow + i, currentColumns, QString::number(sumOfRow[i]));
        ExcelUtils::uniteRange(sheet, startRow + uidsOfClubs.size(), currentColumns, startRow + uidsOfClubs.size() + 1, currentColumns);
        ExcelUtils::setValue(sheet, startRow + uidsOfClubs.size(), currentColumns, QString::number(std::accumulate(sumOfRow.begin(), sumOfRow.end(), 0)));
        ++currentColumns;

        ExcelUtils::setBorder (sheet, startRow - 2, currentColumns - 1, startRow + uidsOfClubs.size() + 1, currentColumns - 1, 2, ExcelUtils::Border::all);

        ExcelUtils::setBorder (sheet, startRow - 2, currentColumns - 1, startRow + uidsOfClubs.size() + 1, currentColumns - 1, 3, ExcelUtils::Border::xlEdgeTop);
        ExcelUtils::setBorder (sheet, startRow - 2, currentColumns - 1, startRow + uidsOfClubs.size() + 1, currentColumns - 1, 3, ExcelUtils::Border::xlEdgeBottom);
        ExcelUtils::setBorder (sheet, startRow - 2, currentColumns - 1, startRow + uidsOfClubs.size() + 1, currentColumns - 1, 3, ExcelUtils::Border::xlEdgeLeft);
        ExcelUtils::setBorder (sheet, startRow - 2, currentColumns - 1, startRow + uidsOfClubs.size() + 1, currentColumns - 1, 3, ExcelUtils::Border::xlEdgeRight);

        ExcelUtils::setBorder (sheet, startRow - 1, currentColumns - 1, startRow - 1, currentColumns - 1, 3, ExcelUtils::Border::xlEdgeBottom);
        ExcelUtils::setBorder (sheet, startRow + uidsOfClubs.size()    , currentColumns - 1, startRow + uidsOfClubs.size()    , currentColumns - 1, 3, ExcelUtils::Border::xlEdgeBottom);
        ExcelUtils::setBorder (sheet, startRow + uidsOfClubs.size() - 1, currentColumns - 1, startRow + uidsOfClubs.size() - 1, currentColumns - 1, 3, ExcelUtils::Border::xlEdgeBottom);

        for (int i = 1; i <= currentColumns; ++i)
            ExcelUtils::setColumnAutoFit(sheet, i);

        ExcelUtils::setTournamentName(sheet, DBUtils::getTournamentNameAsHeadOfDocument(database, tournamentUID), 1, 1, 1, currentColumns - 1);

        ExcelUtils::uniteRange(sheet, 2, 1, 2, currentColumns - 1);
        ExcelUtils::setValue(sheet, 2, 1, "Протокол мандатной комиссии");


        ExcelUtils::setValue(sheet, startRow - 5, 1, "Раздел: " + DBUtils::getField(database, "NAME", "TYPES", TYPE_FK), 0);
        ExcelUtils::setValue(sheet, startRow - 4, 1, "Возрастная категория: " + AGE_FROM + " - " + AGE_TILL + " лет", 0);
        ExcelUtils::setValue(sheet, startRow - 3, 1, "Пол: " + DBUtils::getField(database, "SHORTNAME", "SEXES", SEX_FK), 0);

        sheet->setProperty("Name", (DBUtils::getField(database, "SHORTNAME", "SEXES", SEX_FK) + " " + DBUtils::getField(database, "NAME", "TYPES", TYPE_FK) + " " + AGE_FROM + "-" + AGE_TILL + "лет").left(31));

        int maxRow = startRow + uidsOfClubs.size() + 3;
        ExcelUtils::uniteRange(sheet, maxRow, 1, maxRow, 2);
        ExcelUtils::setRowHeight(sheet, maxRow, 25);
        ExcelUtils::setValue(sheet, maxRow, 1, "Главный судья: ", 0);
        ExcelUtils::setValue(sheet, maxRow, 3, DBUtils::get_MAIN_JUDGE(database, tournamentUID), 0);
        ++maxRow;

        ExcelUtils::uniteRange(sheet, maxRow, 1, maxRow, 2);
        ExcelUtils::setRowHeight(sheet, maxRow, 25);
        ExcelUtils::setValue(sheet, maxRow, 1, "Главный секретарь: ", 0);
        ExcelUtils::setValue(sheet, maxRow, 3, DBUtils::get_MAIN_SECRETARY(database, tournamentUID), 0);
        ++maxRow;

        ExcelUtils::uniteRange(sheet, maxRow, 1, maxRow, 2);
        ExcelUtils::setRowHeight(sheet, maxRow, 25);
        ExcelUtils::setValue(sheet, maxRow, 1, "Зам. главного судьи: ", 0);
        ExcelUtils::setValue(sheet, maxRow, 3, DBUtils::get_ASSOCIATE_MAIN_JUDGE(database, tournamentUID), 0);
        ++maxRow;


        ExcelUtils::setPageOrientation(sheet, 2);
        ExcelUtils::setCenterHorizontally(sheet, true);
        ExcelUtils::setFitToPagesWide(sheet, 2);
        //return;
        delete sheet;
    }

    delete sheets;
    delete workbook;
    delete workbooks;
}

