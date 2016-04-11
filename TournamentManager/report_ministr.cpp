#include "report_ministr.h"
#include "excel_utils.h"
#include "db_utils.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

#include <QAxWidget>
#include <QAxObject>
#include <algorithm>
#include <functional>
#include <iostream>
#include <utility>

ReporMinistr::ReporMinistr(const long long tournamentUID)
{
    QAxWidget excel("Excel.Application");
    excel.setProperty("Visible", true);
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
    workbooks->dynamicCall("Add");
    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");
    QAxObject *sheets = workbook->querySubObject("WorkSheets");


    //
    {
        sheets->querySubObject("Add");
        QAxObject *sheet = sheets->querySubObject( "Item( int )", 1);
        sheet->setProperty("Name", "Количество участников");
        QSqlQuery query;
        query = QSqlQuery(
            "SELECT REGIONS.UID "
            "FROM ORDERS "
                "INNER JOIN REGIONS               ON ORDERS.REGION_FK              = REGIONS.UID "
                "INNER JOIN TOURNAMENT_CATEGORIES ON ORDERS.TOURNAMENT_CATEGORY_FK = TOURNAMENT_CATEGORIES.UID "
            "WHERE "
                "TOURNAMENT_CATEGORIES.TOURNAMENT_FK = ? "
            "GROUP BY "
                "REGIONS.UID "
            "ORDER BY "
                "MAX(REGIONS.NAME)  "
        );
        query.bindValue(0, tournamentUID);
        if (!query.exec())
        {
            qDebug() << __PRETTY_FUNCTION__  << query.lastError() << query.lastQuery();
        }
        else
        {
            //ExcelUtils::setValue(sheet, currentRow, 1, "Всего участников соревнований " + query.value("CNT").toString(), 0);
            QVector<int> uidsOfRegions;
            while (query.next())
                uidsOfRegions.push_back(query.value("UID").toLongLong());
            //qDebug() << "uidsOfRegions: " << uidsOfRegions;
            for (int i = 0; i < uidsOfRegions.size(); ++i)
            {
                ExcelUtils::setValue(sheet, 3 + i, 1, QString::number(i + 1));
                ExcelUtils::setValue(sheet, 3 + i, 2, DBUtils::getField("NAME", "REGIONS", uidsOfRegions[i]));

                QSqlQuery queryMan(
                    "SELECT COUNT(*) AS CNT "
                    "FROM ORDERS "
                         "INNER JOIN REGIONS               ON ORDERS.REGION_FK              = REGIONS.UID "
                         "INNER JOIN TOURNAMENT_CATEGORIES ON ORDERS.TOURNAMENT_CATEGORY_FK = TOURNAMENT_CATEGORIES.UID "
                    "WHERE "
                         "TOURNAMENT_CATEGORIES.TOURNAMENT_FK = ? AND ORDERS.SEX_FK = 1 AND REGIONS.UID = ? "
                    "GROUP BY "
                          "REGIONS.UID "
                );
                queryMan.bindValue(0, tournamentUID);
                queryMan.bindValue(1, uidsOfRegions[i]);
                int cntMan = 0;
                if (!queryMan.exec())
                    qDebug() << __PRETTY_FUNCTION__  << queryMan.lastError() << queryMan.lastQuery();
                else if (queryMan.next())
                {
                    ExcelUtils::setValue(sheet, 3 + i, 3, queryMan.value("CNT").toString());
                    cntMan = queryMan.value("CNT").toInt();
                }


                QSqlQuery queryGirl(
                    "SELECT COUNT(*) AS CNT "
                    "FROM ORDERS "
                         "INNER JOIN REGIONS               ON ORDERS.REGION_FK              = REGIONS.UID "
                         "INNER JOIN TOURNAMENT_CATEGORIES ON ORDERS.TOURNAMENT_CATEGORY_FK = TOURNAMENT_CATEGORIES.UID "
                    "WHERE "
                         "TOURNAMENT_CATEGORIES.TOURNAMENT_FK = ? AND ORDERS.SEX_FK = 2 AND REGIONS.UID = ? "
                    "GROUP BY "
                          "REGIONS.UID "
                );
                queryGirl.bindValue(0, tournamentUID);
                queryGirl.bindValue(1, uidsOfRegions[i]);
                int cntGirl = 0;
                if (!queryGirl.exec())
                    qDebug() << __PRETTY_FUNCTION__  << queryGirl.lastError() << queryGirl.lastQuery();
                else if (queryGirl.next())
                {
                    ExcelUtils::setValue(sheet, 3 + i, 4, queryGirl.value("CNT").toString());
                    cntGirl = queryGirl.value("CNT").toInt();
                }

                ExcelUtils::setValue(sheet, 3 + i, 5, QString::number(cntMan + cntGirl));



                QSqlQuery queryCoach(
                    "SELECT COUNT(*) AS CNT "
                    "FROM ORDERS "
                         "INNER JOIN REGIONS               ON ORDERS.REGION_FK              = REGIONS.UID "
                         "INNER JOIN TOURNAMENT_CATEGORIES ON ORDERS.TOURNAMENT_CATEGORY_FK = TOURNAMENT_CATEGORIES.UID "
                    "WHERE "
                         "TOURNAMENT_CATEGORIES.TOURNAMENT_FK = ? AND REGIONS.UID = ? "
                    "GROUP BY "
                          "ORDERS.COACH_FK "
                );
                queryCoach.bindValue(0, tournamentUID);
                queryCoach.bindValue(1, uidsOfRegions[i]);
                int cntCoach = 0;
                if (!queryCoach.exec())
                    qDebug() << __PRETTY_FUNCTION__  << queryCoach.lastError() << queryCoach.lastQuery();
                else if (queryCoach.next())
                {
                    ExcelUtils::setValue(sheet, 3 + i, 6, queryCoach.value("CNT").toString());
                    cntCoach = queryCoach.value("CNT").toInt();
                }

                ExcelUtils::setValue(sheet, 3 + i, 7, QString::number(cntMan + cntGirl + cntCoach));
            }

            ExcelUtils::uniteRange(sheet, 1, 1, 2, 1);
            ExcelUtils::setValue(sheet, 1, 1, "#");

            ExcelUtils::uniteRange(sheet, 1, 2, 2, 2);
            ExcelUtils::setValue(sheet, 1, 2, "Команда");

            ExcelUtils::uniteRange(sheet, 1, 3, 1, 5);
            ExcelUtils::setValue(sheet, 1, 3, "Спортсмены");

            ExcelUtils::setValue(sheet, 2, 3, "Мужчины");
            ExcelUtils::setValue(sheet, 2, 4, "Женщины");
            ExcelUtils::setValue(sheet, 2, 5, "Всего");

            ExcelUtils::uniteRange(sheet, 1, 6, 2, 6);
            ExcelUtils::setValue(sheet, 1, 6, "Тренеры");

            ExcelUtils::uniteRange(sheet, 1, 7, 2, 7);
            ExcelUtils::setValue(sheet, 1, 7, "Всего");

            for (int i = 1; i <= 7; ++i)
                ExcelUtils::setColumnAutoFit(sheet, i);
            ExcelUtils::setBorder(sheet, 1, 1, 2 + uidsOfRegions.size(), 7);
        }
        delete sheet;
    }
    /**/

    {
        sheets->querySubObject("Add");
        QAxObject *sheet = sheets->querySubObject( "Item( int )", 1);
        sheet->setProperty("Name", "Подготовка спортсменов");
        ReporMinistr::f2(sheet, tournamentUID);
        delete sheet;
    }


    {
        sheets->querySubObject("Add");
        QAxObject *sheet = sheets->querySubObject( "Item( int )", 1);
        sheet->setProperty("Name", "Медали");
        ReporMinistr::f3(sheet, tournamentUID);
        delete sheet;
    }


    delete sheets;
    delete workbook;
    delete workbooks;
}

void ReporMinistr::f2(QAxObject *sheet, const long long tournamentUID)
{
    QVector<long long> sportCat;
    {
        QSqlQuery querySC("SELECT * FROM SPORT_CATEGORIES ORDER BY NAME");
        if (!querySC.exec())
        {
            qDebug() << __PRETTY_FUNCTION__  << querySC.lastError() << querySC.lastQuery();
            return;
        }
        while (querySC.next()) sportCat << querySC.value("UID").toLongLong();
    }
    for (int i = 0; i < sportCat.size(); ++i)
        ExcelUtils::setValue(sheet, i + 1, 1, DBUtils::getField("NAME", "SPORT_CATEGORIES", sportCat[i]));

    QSqlQuery queryCat(
        "SELECT "
            "SEX_FK, AGE_FROM, AGE_TILL, AGE_CATEGORY_FK "
        "FROM "
            "TOURNAMENT_CATEGORIES "
        "WHERE "
            "TOURNAMENT_FK = ? "
        "GROUP BY "
            "SEX_FK, AGE_FROM, AGE_TILL, AGE_CATEGORY_FK "
        "ORDER BY "
            "SEX_FK, AGE_FROM, AGE_TILL, AGE_CATEGORY_FK "
    );
    queryCat.bindValue(0, tournamentUID);
    if (!queryCat.exec())
    {
        qDebug() << __PRETTY_FUNCTION__  << queryCat.lastError() << queryCat.lastQuery();
        return;
    }

    int column = 2;
    QVector<int> totalCountOfOrders(sportCat.size());
    while (queryCat.next())
    {
        QString sexUID = queryCat.value("SEX_FK").toString();
        QString ageFrom = queryCat.value("AGE_FROM").toString();
        QString ageTill = queryCat.value("AGE_TILL").toString();
        QString ageCatUID = queryCat.value("AGE_CATEGORY_FK").toString();
        ExcelUtils::setValue(sheet, 1, column, DBUtils::getField("NAME", "AGE_CATEGORIES", ageCatUID) + "(" + ageFrom + "-" + ageTill + ")");


        for (int i = 0; i < sportCat.size(); ++i)
        {
            QSqlQuery queryOrder;
            queryOrder.prepare(
                "SELECT COUNT(*) AS CNT "
                "FROM ORDERS "
                    "INNER JOIN TOURNAMENT_CATEGORIES ON TOURNAMENT_CATEGORIES.UID = ORDERS.TOURNAMENT_CATEGORY_FK "
                "WHERE "
                    "TOURNAMENT_CATEGORIES.TOURNAMENT_FK  = ? AND "

                    "ORDERS.SPORT_CATEGORY_FK = ? AND "

                    "TOURNAMENT_CATEGORIES.SEX_FK   = ? AND "
                    "TOURNAMENT_CATEGORIES.AGE_FROM = ? AND "
                    "TOURNAMENT_CATEGORIES.AGE_TILL = ?  AND "
                    "TOURNAMENT_CATEGORIES.AGE_CATEGORY_FK = ? "
            );
            queryOrder.addBindValue(tournamentUID);
            queryOrder.addBindValue(sportCat[i]);
            queryOrder.addBindValue(sexUID);
            queryOrder.addBindValue(ageFrom);
            queryOrder.addBindValue(ageTill);
            queryOrder.addBindValue(ageCatUID);

            if (!queryOrder.exec())
            {
                qDebug() << __PRETTY_FUNCTION__  << queryOrder.lastError() << queryOrder.lastQuery();
                return;
            }
            int countOfOrders = 0;
            if (queryOrder.next()) countOfOrders = queryOrder.value("CNT").toInt();
            if (0 < countOfOrders)
                ExcelUtils::setValue(sheet, i + 2, column, QString::number(countOfOrders));
            totalCountOfOrders[i] += countOfOrders;
        }
        ++column;
    }

    ExcelUtils::setValue(sheet, 1, column, "Итого");
    for (int i = 0; i < totalCountOfOrders.size(); ++i)
        ExcelUtils::setValue(sheet, i + 2, column, QString::number(totalCountOfOrders[i]));
    ++column;

    for (int j = 1; j <= column; ++j)
    {
        ExcelUtils::setColumnAutoFit(sheet, j);
    }

    ExcelUtils::setBorder(sheet, 1, 1, sportCat.size() + 1, column - 1);

}

void ReporMinistr::f3(QAxObject* sheet, const long long tournamentUID)
{
    std::map<long long,  QVector<int> > regionAnsCntMedal;

    QSqlQuery query(
        "SELECT "
            "UID "
        "FROM "
            "TOURNAMENT_CATEGORIES "
        "WHERE "
            "TOURNAMENT_CATEGORIES.TOURNAMENT_FK = ? "
    );
    query.bindValue(0, tournamentUID);
    if (!query.exec())
    {
        qDebug() << __PRETTY_FUNCTION__  << query.lastError() << query.lastQuery();
        return;
    }

    while (query.next())
    {
        QString TOURNAMENT_CATEGORY = query.value("UID").toString();
        QVector<DBUtils::NodeOfTournirGrid> nodes = DBUtils::getNodes(TOURNAMENT_CATEGORY.toLongLong());
        for (int iter = 0; iter < 4 && !nodes.empty(); ++iter)
        {
            long long orderUID = nodes[0].UID;
            if (orderUID == 0)
                break;
            long long region = DBUtils::getField("REGION_FK", "ORDERS", orderUID).toLongLong();
            if (regionAnsCntMedal.count(region) == 0)
                regionAnsCntMedal[region] = QVector<int>(3, 0);
            ++regionAnsCntMedal[region][qMin(iter, 2)];
            for (int i = 0; i < nodes.size(); ++i)
                while (i < nodes.size() && nodes[i].UID == orderUID)
                    nodes.remove(i);
        }
    }

    QVector <std::pair<long long, QVector<int>>> res;
    for (auto it = regionAnsCntMedal.begin(); it != regionAnsCntMedal.end(); ++it )
        res.push_back(*it);

    std::sort(res.begin(), res.end(),
        [](const std::pair<long long, QVector<int>>& lhs, const std::pair<long long, QVector<int>>& rhs)  -> bool
    {
        return lhs.second[0] + lhs.second[1] + lhs.second[2] > rhs.second[0] + rhs.second[1] + rhs.second[2];
    });


    for (int i = 0; i < res.size(); ++i)
    {
        ExcelUtils::setValue(sheet, 3 + i, 1, QString::number(i + 1));
        ExcelUtils::setValue(sheet, 3 + i, 2, DBUtils::getField("NAME", "REGIONS", res[i].first));
        int sum = 0;
        for (int j = 0; j < 3; ++j)
        {
            if (res[i].second[j] != 0)
                ExcelUtils::setValue(sheet, 3 + i, 3 + j, QString::number(res[i].second[j]));
            sum += res[i].second[j];
        }
        ExcelUtils::setValue(sheet, 3 + i, 6, QString::number(sum));
    }

    ExcelUtils::uniteRange(sheet, 1, 1, 2, 1);
    ExcelUtils::setValue(sheet, 1, 1, "#");

    ExcelUtils::uniteRange(sheet, 1, 2, 2, 2);
    ExcelUtils::setValue(sheet, 1, 2, "Команда");

    ExcelUtils::setValue(sheet, 2, 3, "Золото");
    ExcelUtils::setValue(sheet, 2, 4, "Серебро");
    ExcelUtils::setValue(sheet, 2, 5, "Бронза");

    ExcelUtils::uniteRange(sheet, 1, 3, 1, 5);
    ExcelUtils::setValue(sheet, 1, 3, "Количество медалей");

    ExcelUtils::uniteRange(sheet, 1, 6, 2, 6);
    ExcelUtils::setValue(sheet, 1, 6, "Итого");

    ExcelUtils::setBorder(sheet, 1, 1, res.size() + 2, 6);

    for (int j = 1; j <= 6; ++j)
    {
        ExcelUtils::setColumnAutoFit(sheet, j);
    }

}
