#include "report_manda.h"

void ReportManda::report(const long long tournamentUID)
{
    DialogChoseData dlg(DialogChoseData::Type::ReportManda);
    if (dlg.exec() != QDialog::Accepted)
        return;
    QMap<QString, QString> translations = dlg.getTranslations();

    QSqlQuery queryCategory;
    if (!queryCategory.prepare(
            "SELECT SEX_FK, AGE_CATEGORY_FK, TYPE_FK, AGE_FROM, AGE_TILL, MAX(AGE) AS AGE "
            "FROM TOURNAMENT_CATEGORIES "
            "WHERE TOURNAMENT_FK = ? "
            "GROUP BY SEX_FK, AGE_CATEGORY_FK, TYPE_FK, AGE_FROM, AGE_TILL "
            "ORDER BY SEX_FK, AGE_CATEGORY_FK, TYPE_FK, AGE_FROM, AGE_TILL "))
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << queryCategory.lastError() << queryCategory.lastQuery();
        return;
    }
    queryCategory.addBindValue(tournamentUID);
    if (!queryCategory.exec())
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << queryCategory.lastError() << queryCategory.lastQuery();
        return;
    }

    QAxWidget excel("Excel.Application");
    excel.setProperty("Visible", true);
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
    workbooks->dynamicCall("Add");
    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");
    QAxObject *sheets = workbook->querySubObject("WorkSheets");

    while (queryCategory.next())
    {
        QString SEX_FK    = queryCategory.value("SEX_FK").toString();
        QString TYPE_FK   = queryCategory.value("TYPE_FK").toString();
        QString AGE_FROM  = queryCategory.value("AGE_FROM").toString();
        QString AGE_TILL  = queryCategory.value("AGE_TILL").toString();
        QString ageCatUID = queryCategory.value("AGE_CATEGORY_FK").toString();
        QString age       = queryCategory.value("AGE").toString();

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
                    "TOURNAMENT_CATEGORIES.TOURNAMENT_FK = ? "
                    "GROUP BY CLUBS.UID");
        queryClubs.bindValue(0, SEX_FK);
        queryClubs.bindValue(1, TYPE_FK);
        queryClubs.bindValue(2, AGE_FROM);
        queryClubs.bindValue(3, AGE_TILL);
        queryClubs.bindValue(4, tournamentUID);
        if (!queryClubs.exec())
        {
            qDebug() << __LINE__ << __PRETTY_FUNCTION__ << queryClubs.lastError() << queryClubs.lastQuery();
            continue;
        }
        QVector<QString> uidsOfClubs;
        while (queryClubs.next()) uidsOfClubs << queryClubs.value("clubid12").toString();
        QVector<int> sumOfRow(uidsOfClubs.size());
        //qDebug() << DBUtils::getField("NAME", "TYPES", TYPE_FK) << AGE_FROM << AGE_TILL << uidsOfClubs;

        if (uidsOfClubs.isEmpty()) continue;


        QAxObject *sheet = ExcelUtils::addNewSheet(sheets);
        const int startRow = 7;
        for (int i = 0; i < uidsOfClubs.size(); ++i)
        {
            ExcelUtils::setValue(sheet, startRow + i, 1, QString::number(i + 1));
            ExcelUtils::setValue(sheet, startRow + i, 2, DBUtils::getField("NAME", "CLUBS", uidsOfClubs[i]) + ", " + DBUtils::getField("NAME", "REGIONS", DBUtils::getField("REGION_FK", "CLUBS", uidsOfClubs[i])));
        }
        ExcelUtils::setBorder (sheet, startRow, 1, startRow + uidsOfClubs.size() - 1, 2);
        ExcelUtils::setBorder (sheet, startRow, 1, startRow + uidsOfClubs.size() - 1, 2, 3, ExcelUtils::Border::xlEdgeTop);
        ExcelUtils::setBorder (sheet, startRow, 1, startRow + uidsOfClubs.size() - 1, 2, 3, ExcelUtils::Border::xlEdgeBottom);
        ExcelUtils::setBorder (sheet, startRow, 1, startRow + uidsOfClubs.size() - 1, 1, 3, ExcelUtils::Border::xlEdgeLeft);
        ExcelUtils::setBorder (sheet, startRow, 2, startRow + uidsOfClubs.size() - 1, 2, 3, ExcelUtils::Border::xlEdgeLeft);

        ExcelUtils::setValue(sheet, startRow - 1, 1, translations["#"]);
        ExcelUtils::setValue(sheet, startRow - 1, 2, translations["Команда"]);
        ExcelUtils::setBorder (sheet, startRow - 2, 1, startRow - 1, 2, 3);
        ExcelUtils::uniteRange(sheet, startRow - 2, 1, startRow - 1, 1);
        ExcelUtils::uniteRange(sheet, startRow - 2, 2, startRow - 1, 2);

        //return;

        ExcelUtils::setBorder (sheet, startRow + uidsOfClubs.size(), 1, startRow + uidsOfClubs.size() + 1, 2, 3);
        ExcelUtils::uniteRange(sheet, startRow + uidsOfClubs.size(), 1, startRow + uidsOfClubs.size() + 1, 2);
        ExcelUtils::setValue  (sheet, startRow + uidsOfClubs.size(), 1, translations["Всего"]);

        QSqlQuery queryWEIGHTS(
                    "SELECT WEIGHT_FROM, WEIGHT_TILL, MAX(TOURNAMENT_CATEGORIES.WEIGHT) AS WEIGHT "
                    "FROM ORDERS "
                    "INNER JOIN CLUBS ON CLUBS.UID = ORDERS.CLUB_FK "
                    "INNER JOIN TOURNAMENT_CATEGORIES ON TOURNAMENT_CATEGORIES.UID = ORDERS.TOURNAMENT_CATEGORY_FK "
                    "WHERE "
                    "TOURNAMENT_CATEGORIES.SEX_FK   = ? AND "
                    "TOURNAMENT_CATEGORIES.TYPE_FK  = ? AND "
                    "TOURNAMENT_CATEGORIES.AGE_FROM = ? AND "
                    "TOURNAMENT_CATEGORIES.AGE_TILL = ? AND "
                    "TOURNAMENT_CATEGORIES.TOURNAMENT_FK = ? "
                    "GROUP BY WEIGHT_FROM, WEIGHT_TILL "
                    "ORDER BY WEIGHT_FROM, WEIGHT_TILL ");

        queryWEIGHTS.bindValue(0, SEX_FK);
        queryWEIGHTS.bindValue(1, TYPE_FK);
        queryWEIGHTS.bindValue(2, AGE_FROM);
        queryWEIGHTS.bindValue(3, AGE_TILL);
        queryWEIGHTS.bindValue(4, tournamentUID);
        if (!queryWEIGHTS.exec())
        {
            qDebug() << __LINE__ << __PRETTY_FUNCTION__ << queryWEIGHTS.lastError() << queryWEIGHTS.lastQuery();
            continue;
        }

        int currentColumns = 3;
        while (queryWEIGHTS.next())
        {
            QString WEIGHT_FROM = queryWEIGHTS.value("WEIGHT_FROM").toString();
            QString WEIGHT_TILL = queryWEIGHTS.value("WEIGHT_TILL").toString();
            QString weight      = queryWEIGHTS.value("WEIGHT").toString();
            //qDebug() << "\t" << WEIGHT_FROM << WEIGHT_TILL;

            QSqlQuery querySPORT_CATEGORIES;
            if (!querySPORT_CATEGORIES.prepare(
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
                    "TOURNAMENT_CATEGORIES.TOURNAMENT_FK = ? "
                    "GROUP BY "
                    "UID_SC "
                    //                "ORDER BY "
                    //                    "max(SPORT_CATEGORIES.PRIORITY) "
                    ))
            {
                qDebug() << __LINE__ << __PRETTY_FUNCTION__ << querySPORT_CATEGORIES.lastError() << querySPORT_CATEGORIES.lastQuery();
                return;
            }
            querySPORT_CATEGORIES.addBindValue(SEX_FK);
            querySPORT_CATEGORIES.addBindValue(TYPE_FK);
            querySPORT_CATEGORIES.addBindValue(AGE_FROM);
            querySPORT_CATEGORIES.addBindValue(AGE_TILL);
            querySPORT_CATEGORIES.addBindValue(WEIGHT_FROM);
            querySPORT_CATEGORIES.addBindValue(WEIGHT_TILL);
            querySPORT_CATEGORIES.addBindValue(tournamentUID);
            if (!querySPORT_CATEGORIES.exec())
            {
                qDebug() << __LINE__ << __PRETTY_FUNCTION__ << querySPORT_CATEGORIES.lastError() << querySPORT_CATEGORIES.lastQuery();
                return;
            }


            int countSPORT_CATEGORIES = 0;
            int sumOfValuesForWeight = 0;
            while (querySPORT_CATEGORIES.next())
            {
                QString SPORT_CATEGORY = querySPORT_CATEGORIES.value("UID_SC").toString();
                //qDebug() << "\t\t" << DBUtils::getField("NAME", "SPORT_CATEGORIES", SPORT_CATEGORY);
                ++countSPORT_CATEGORIES;
                int sumOfValuesForWeightAndSportCategory = 0;

                ExcelUtils::setValue(sheet, startRow - 1, currentColumns, DBUtils::getField("NAME", "SPORT_CATEGORIES", SPORT_CATEGORY));

                for (int i = 0; i < uidsOfClubs.size(); ++i)
                {
                    QSqlQuery query(
                                "SELECT COUNT(*) AS CNT "
                                "FROM ORDERS "
                                "INNER JOIN CLUBS                 ON CLUBS.UID                 = ORDERS.CLUB_FK "
                                "INNER JOIN TOURNAMENT_CATEGORIES ON TOURNAMENT_CATEGORIES.UID = ORDERS.TOURNAMENT_CATEGORY_FK "
                                "INNER JOIN SPORT_CATEGORIES      ON SPORT_CATEGORIES.UID      = ORDERS.SPORT_CATEGORY_FK "
                                "WHERE "
                                "TOURNAMENT_CATEGORIES.SEX_FK        = ? AND "
                                "TOURNAMENT_CATEGORIES.TYPE_FK       = ? AND "
                                "TOURNAMENT_CATEGORIES.AGE_FROM      = ? AND "
                                "TOURNAMENT_CATEGORIES.AGE_TILL      = ? AND "
                                "TOURNAMENT_CATEGORIES.WEIGHT_FROM   = ? AND "
                                "TOURNAMENT_CATEGORIES.WEIGHT_TILL   = ? AND "
                                "SPORT_CATEGORIES.UID                = ? AND "
                                "CLUBS.UID                           = ? AND "
                                "TOURNAMENT_CATEGORIES.TOURNAMENT_FK = ?");
                    query.bindValue(0, SEX_FK);
                    query.bindValue(1, TYPE_FK);
                    query.bindValue(2, AGE_FROM);
                    query.bindValue(3, AGE_TILL);
                    query.bindValue(4, WEIGHT_FROM);
                    query.bindValue(5, WEIGHT_TILL);
                    query.bindValue(6, SPORT_CATEGORY);
                    query.bindValue(7, uidsOfClubs[i]);
                    query.bindValue(8, tournamentUID);

                    if (!query.exec() || !query.next())
                    {
                        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
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
                ExcelUtils::setValue  (sheet, startRow - 2, currentColumns - countSPORT_CATEGORIES, weight);

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
        ExcelUtils::setValue(sheet, startRow - 2, currentColumns, translations["Всего"]);
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

        ExcelUtils::setTournamentName(sheet, DBUtils::getTournamentNameAsHeadOfDocument(tournamentUID), 1, 1, 1, currentColumns - 1);

        ExcelUtils::uniteRange(sheet, 2, 1, 2, currentColumns - 1);
        ExcelUtils::setValue  (sheet, 2, 1, dlg.getTitle());

        ExcelUtils::setValue  (sheet, 4, 1, DBUtils::getField("NAME", "TYPES", TYPE_FK) + ", " + DBUtils::getField("NAME", "AGE_CATEGORIES", ageCatUID) + ", " + age, 0);

        sheet->setProperty("Name", (DBUtils::getField("SHORTNAME", "SEXES", SEX_FK) + ", " +
                                    age + ", " +
                                    DBUtils::getField("NAME", "TYPES", TYPE_FK)
                                    ).left(31));


        int maxRow = startRow + uidsOfClubs.size() + 2;

        ExcelUtils::setFooter(sheet, maxRow, 1, 3, 25, dlg.getJudges(), DBUtils::getJudges(tournamentUID));


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
