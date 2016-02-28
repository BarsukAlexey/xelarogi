#include "fiting_distribution.h"
#include "tournamentgriddialog2.h"
#include "db_utils.h"
#include "excel_utils.h"


#include <QAxObject>
#include <QAxWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QDate>





FitingDistribution::FitingDistribution(const QSqlDatabase &database, const long long tournamentUID)
{

    QAxWidget excel("Excel.Application");
    excel.setProperty("Visible", true);
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
    workbooks->dynamicCall("Add");
    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");
    QAxObject *sheets = workbook->querySubObject("WorkSheets");

    QStringList days = DBUtils::get_DAYS_FROM_TOURNAMENTS(database, tournamentUID);


    QSqlQuery queryTYPE_FK_AGE_FROM("SELECT * FROM TOURNAMENT_CATEGORIES WHERE TOURNAMENT_FK = ? GROUP BY TYPE_FK, AGE_FROM, AGE_TILL ORDER BY TYPE_FK, AGE_FROM", database);
    queryTYPE_FK_AGE_FROM.bindValue(0, tournamentUID);
    if (!queryTYPE_FK_AGE_FROM.exec())
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << queryTYPE_FK_AGE_FROM.lastError().text() << queryTYPE_FK_AGE_FROM.lastQuery();
        return ;
    }
    while (queryTYPE_FK_AGE_FROM.next())
    {
        long long TYPE_FK = queryTYPE_FK_AGE_FROM.value("TYPE_FK").toLongLong();
        QString AGE_FROM = queryTYPE_FK_AGE_FROM.value("AGE_FROM").toString();
        QVector<int> totalSum(3 * days.size());
        int totalPeople = 0;

        sheets->querySubObject("Add");
        QAxObject *sheet = sheets->querySubObject( "Item( int )", 1);
        int currentRow = 2;


        ExcelUtils::setValue  (sheet, currentRow, 1, DBUtils::getNameTournamentByUID(database, tournamentUID));
        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 2 + 3 * days.size());
        ++currentRow;
        ExcelUtils::setValue  (sheet, currentRow, 1, "Раздел: " + DBUtils::getTypeNameByUID(database, TYPE_FK));
        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 2 + 3 * days.size());
        ++currentRow;
        ExcelUtils::setValue  (sheet, currentRow, 1, "Возраст от " + AGE_FROM + " до " + queryTYPE_FK_AGE_FROM.value("AGE_TILL").toString());
        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 2 + 3 * days.size());
        ++currentRow;


        initTableHeads(sheet, currentRow, days);


        QSqlQuery querySEX_FK("SELECT DISTINCT SEX_FK FROM TOURNAMENT_CATEGORIES WHERE TOURNAMENT_FK = ? AND TYPE_FK = ? AND AGE_FROM = ? ORDER BY SEX_FK", database);
        querySEX_FK.bindValue(0, tournamentUID);
        querySEX_FK.bindValue(1, TYPE_FK);
        querySEX_FK.bindValue(2, AGE_FROM);
        if (!querySEX_FK.exec())
        {
            qDebug() << __LINE__ << __PRETTY_FUNCTION__ << querySEX_FK.lastError().text() << " " << querySEX_FK.lastQuery();
            return;
        }
        while (querySEX_FK.next())
        {
            long long SEX_FK = querySEX_FK.value("SEX_FK").toLongLong();

            ExcelUtils::setValue  (sheet, currentRow, 1, DBUtils::get_SHORTNAME_FROM_SEXES(database, SEX_FK), 0);
            ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 2 + 3 * days.size());
            ++currentRow;

            QSqlQuery queryWEIGHT_FROM("SELECT WEIGHT_FROM, WEIGHT_TILL FROM TOURNAMENT_CATEGORIES WHERE TOURNAMENT_FK = ? AND TYPE_FK = ?  AND AGE_FROM = ? AND SEX_FK = ? GROUP BY WEIGHT_FROM, WEIGHT_TILL ORDER BY WEIGHT_FROM", database);
            queryWEIGHT_FROM.bindValue(0, tournamentUID);
            queryWEIGHT_FROM.bindValue(1, TYPE_FK);
            queryWEIGHT_FROM.bindValue(2, AGE_FROM);
            queryWEIGHT_FROM.bindValue(3, SEX_FK);
            if (!queryWEIGHT_FROM.exec())
            {
                qDebug() << __LINE__ << __PRETTY_FUNCTION__ << queryWEIGHT_FROM.lastError().text() << " " << queryWEIGHT_FROM.lastQuery();
                return;
            }



            while (queryWEIGHT_FROM.next())
            {
                QString WEIGHT_FROM = queryWEIGHT_FROM.value("WEIGHT_FROM").toString();
                QString WEIGHT_TILL = queryWEIGHT_FROM.value("WEIGHT_TILL").toString();

                ExcelUtils::setValue(sheet, currentRow, 1, WEIGHT_FROM + " - " + WEIGHT_TILL + " кг");
                ExcelUtils::setBorder(sheet, currentRow, 1, currentRow, 2 + 3 * days.size());


                QSqlQuery queryTOURNAMENT_CATEGORIES_UID("SELECT * FROM TOURNAMENT_CATEGORIES WHERE TOURNAMENT_FK = ? AND TYPE_FK = ? AND SEX_FK = ? AND AGE_FROM = ? AND WEIGHT_FROM = ?", database);
                queryTOURNAMENT_CATEGORIES_UID.bindValue(0, tournamentUID);
                queryTOURNAMENT_CATEGORIES_UID.bindValue(1, TYPE_FK);
                queryTOURNAMENT_CATEGORIES_UID.bindValue(2, SEX_FK);
                queryTOURNAMENT_CATEGORIES_UID.bindValue(3, AGE_FROM);
                queryTOURNAMENT_CATEGORIES_UID.bindValue(4, WEIGHT_FROM);
                if (!queryTOURNAMENT_CATEGORIES_UID.exec() || !queryTOURNAMENT_CATEGORIES_UID.next()){
                    qDebug() << __LINE__ << __PRETTY_FUNCTION__ << queryTOURNAMENT_CATEGORIES_UID.lastError().text() << " " << queryTOURNAMENT_CATEGORIES_UID.lastQuery();
                    return;
                }

                long long UID_TOURNAMENT_CATEGORY = queryTOURNAMENT_CATEGORIES_UID.value("UID").toLongLong();

                QSqlQuery queryCOUNT("SELECT count() AS COUNT FROM ORDERS WHERE TOURNAMENT_CATEGORY_FK = ? AND IS_VALID = ? GROUP BY TOURNAMENT_CATEGORY_FK", database);
                queryCOUNT.bindValue(0, UID_TOURNAMENT_CATEGORY);
                queryCOUNT.bindValue(1, 1);
                if (!queryCOUNT.exec())
                {
                    qDebug() << __LINE__ << __PRETTY_FUNCTION__ << queryCOUNT.lastError().text() << " " << queryCOUNT.lastQuery();
                    return;
                }
                int count = 0;
                if (queryCOUNT.next())
                    count = queryCOUNT.value("COUNT").toInt();
                //qDebug() << TYPE_FK << AGE_FROM << SEX_FK << WEIGHT_FROM << UID_TOURNAMENT_CATEGORY << ": " << count;

                ExcelUtils::setValue(sheet, currentRow, 2, QString::number(count));
                totalPeople += count;


                if (0 < count)
                {
                    QVector<int> fights;
                    for (int fight = 1; ; fight *= 2)
                    {
                        if (count < 2 * fight)
                        {
                            if (0 < count - fight) fights.push_back(count - fight);
                            break;
                        }
                        else
                            fights.push_back(fight);
                    }

                    if (fights.size() <= 3 * fights.size() )
                    {
                        const int onOneDay = fights.size() / days.size();
                        int rest = fights.size() % days.size();
                        for (int d = qMax(0, days.size() - fights.size()); d < days.size(); ++d)
                        {
                            for (int f = 0; f < onOneDay + (0 < rest? 1 : 0); ++f)
                            {
                                if (!fights.empty())
                                {
                                    ExcelUtils::setValue(sheet, currentRow, 3 + 3 * d + f, QString::number(fights.back()));
                                    totalSum[3 * d + f] += fights.back();
                                    fights.pop_back();
                                }
                            }
                            if (0 < rest) --rest;
                        }
                    }
                }
                ++currentRow;
            }
        }

        ExcelUtils::setValue(sheet, currentRow, 1, "Всего:");
        ExcelUtils::setValue(sheet, currentRow, 2, QString::number(totalPeople));
        ExcelUtils::setBorder(sheet, currentRow, 1, currentRow, 2 + 3 * days.size());


        for (int i = 0; i < totalSum.size(); ++i)
            if (totalSum[i])
                ExcelUtils::setValue(sheet, currentRow, 3 + i, QString::number(totalSum[i]));
        ++currentRow;
        ++currentRow;

        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 2 + 3 * days.size());
        ExcelUtils::setValue(sheet, currentRow, 1, "Главный судья: " + DBUtils::get_MAIN_JUDGE(database, tournamentUID), 0);
        ++currentRow;

        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 2 + 3 * days.size());
        ExcelUtils::setValue(sheet, currentRow, 1, "Главный секретарь: " + DBUtils::get_MAIN_SECRETARY(database, tournamentUID), 0);
        ++currentRow;

        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 2 + 3 * days.size());
        ExcelUtils::setValue(sheet, currentRow, 1, "Зам. главного судьи: " + DBUtils::get_ASSOCIATE_MAIN_JUDGE(database, tournamentUID), 0);
        ++currentRow;

        ExcelUtils::setPageOrientation(sheet, 2);

        delete sheet;
    }


    delete sheets;
    delete workbook;
    delete workbooks;
}

void FitingDistribution::initTableHeads(QAxObject* sheet, int& currentRow, const QStringList& days)
{

    ExcelUtils::setBorder(sheet, currentRow, 1, currentRow + 1, 2 + 3 * days.size());

    ExcelUtils::setValue(sheet, currentRow, 1, "Вес");
    ExcelUtils::setValue(sheet, currentRow, 2, "Кол-во\n\rчеловек");
    ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow + 1, 1);
    ExcelUtils::uniteRange(sheet, currentRow, 2, currentRow + 1, 2);

    for (int column = 3, i = 0; i < days.size(); ++i, column += 3)
    {
        ExcelUtils::uniteRange(sheet, currentRow, column, currentRow, column + 2);
        ExcelUtils::setValue(sheet, currentRow, column, days[i]);

        int shift = 0;
        for(const QString& s : {"Утро", "День", "Вечер"})
        {
            ExcelUtils::setValue(sheet, currentRow + 1, column + shift, s);
            ++shift;
        }
    }

    currentRow += 2;
}



