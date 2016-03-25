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
                "TOURNAMENT_CATEGORIES.TOURNAMENT_FK = ? AND IS_VALID = 1 "
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
                         "TOURNAMENT_CATEGORIES.TOURNAMENT_FK = ? AND IS_VALID = 1 AND ORDERS.SEX_FK = 1 AND REGIONS.UID = ? "
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
                         "TOURNAMENT_CATEGORIES.TOURNAMENT_FK = ? AND IS_VALID = 1 AND ORDERS.SEX_FK = 2 AND REGIONS.UID = ? "
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
                         "TOURNAMENT_CATEGORIES.TOURNAMENT_FK = ? AND IS_VALID = 1 AND REGIONS.UID = ? "
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
    QSqlQuery queryCat(
        "SELECT "
            "SEX_FK, AGE_FROM, AGE_TILL "
        "FROM "
            "TOURNAMENT_CATEGORIES "
        "WHERE "
            "TOURNAMENT_CATEGORIES.TOURNAMENT_FK = ? "
        "GROUP BY "
            "SEX_FK, AGE_FROM, AGE_TILL "
        "ORDER BY "
            "SEX_FK, AGE_FROM, AGE_TILL "
    );
    queryCat.bindValue(0, tournamentUID);
    if (!queryCat.exec())
    {
        qDebug() << __PRETTY_FUNCTION__  << queryCat.lastError() << queryCat.lastQuery();
        return;
    }

    QVector<QVector<QString > > cat;
    while (queryCat.next())
    {
        cat << (
            QVector<QString>()
                << queryCat.value("SEX_FK").toString()
                << queryCat.value("AGE_FROM").toString()
                << queryCat.value("AGE_TILL").toString()
        );
    }


    QSqlQuery querySC("SELECT UID, NAME FROM SPORT_CATEGORIES ");
    if (!querySC.exec())
    {
        qDebug() << __PRETTY_FUNCTION__  << queryCat.lastError() << queryCat.lastQuery();
        return;
    }

    for (int j = 0; j < cat.size(); ++j)
    {
        ExcelUtils::setValue(sheet, 1, j + 2, DBUtils::getField("SHORTNAME", "SEXES",  cat[j][0]) + " " + cat[j][1] + "-" + cat[j][2] + "лет");
    }

    int currentRow = 2;
    while (querySC.next())
    {
        QString uidSportCat = querySC.value("UID").toString();
        ExcelUtils::setValue(sheet, currentRow, 1, querySC.value("NAME").toString());



        //
        ++currentRow;
    }

    for (int j = 1; j <= cat.size() + 1; ++j)
    {
        ExcelUtils::setColumnAutoFit(sheet, j);
    }

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
            long long region = DBUtils::getField("REGION_FK", "ORDERS", orderUID).toLongLong();
            if (regionAnsCntMedal.count(region) == 0)
                regionAnsCntMedal[region] = QVector<int>(3);
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
            ExcelUtils::setValue(sheet, 3 + i, 3 + j, QString::number(sum += res[i].second[j]));
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
