#include "fiting_distribution.h"
#include "tournamentgriddialog2.h"
#include "bd_utils.h"
#include <QAxObject>
#include <QAxWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QDate>





FitingDistribution::FitingDistribution(const QSqlDatabase &database, const long long tournamentUID)
{
    TournamentGridDialog2(database, tournamentUID, 0).ebnutVBazyGovno();

    QAxWidget excel("Excel.Application");
    excel.setProperty("Visible", true);
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
    workbooks->dynamicCall("Add");
    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");
    QAxObject *sheets = workbook->querySubObject("WorkSheets");


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

        sheets->querySubObject("Add");
        QAxObject *sheet = sheets->querySubObject( "Item( int )", 1);
        int currentRow = 2;

        QAxObject *cell;

        cell = sheet->querySubObject( "Cells( int, int )", currentRow++, 1);
        cell->setProperty("Value", BDUtils::getNameTournamentByUID(database, tournamentUID));
        delete cell;

        cell = sheet->querySubObject( "Cells( int, int )", currentRow++, 1);
        cell->setProperty("Value", "Раздел: " + BDUtils::getTypeNameByUID(database, TYPE_FK));
        delete cell;

        cell = sheet->querySubObject( "Cells( int, int )", currentRow++, 1);
        cell->setProperty("Value", "Возраст от " + AGE_FROM + " до " + queryTYPE_FK_AGE_FROM.value("AGE_TILL").toString());
        delete cell;

        initTableHeads(sheet, currentRow++);


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
            QSqlQuery queryWEIGHT_FROM("SELECT DISTINCT WEIGHT_FROM FROM TOURNAMENT_CATEGORIES WHERE TOURNAMENT_FK = ? AND TYPE_FK = ?  AND AGE_FROM = ? AND SEX_FK = ? ORDER BY WEIGHT_FROM", database);
            queryWEIGHT_FROM.bindValue(0, tournamentUID);
            queryWEIGHT_FROM.bindValue(1, TYPE_FK);
            queryWEIGHT_FROM.bindValue(2, AGE_FROM);
            queryWEIGHT_FROM.bindValue(3, SEX_FK);
            if (!queryWEIGHT_FROM.exec())
            {
                qDebug() << __LINE__ << __PRETTY_FUNCTION__ << queryWEIGHT_FROM.lastError().text() << " " << queryWEIGHT_FROM.lastQuery();
                return;
            }

            cell = sheet->querySubObject( "Cells( int, int )", currentRow++, 1);
            cell->setProperty("Value", BDUtils::get_SHORTNAME_FROM_SEXES(database, SEX_FK));
            delete cell;

            while (queryWEIGHT_FROM.next())
            {
                QString WEIGHT_FROM = queryWEIGHT_FROM.value("WEIGHT_FROM").toString();

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

                QSqlQuery queryCOUNT("SELECT count() AS COUNT FROM ORDERS WHERE TOURNAMENT_CATEGORY_FK = ? AND IS_WEIGHTED = ? GROUP BY TOURNAMENT_CATEGORY_FK", database);
                queryCOUNT.bindValue(0, UID_TOURNAMENT_CATEGORY);
                queryCOUNT.bindValue(1, "true");
                if (!queryCOUNT.exec())
                {
                    qDebug() << __LINE__ << __PRETTY_FUNCTION__ << queryCOUNT.lastError().text() << " " << queryCOUNT.lastQuery();
                    return;
                }
                int count = 0;
                if (queryCOUNT.next())
                    count = queryCOUNT.value("COUNT").toInt();
                qDebug() << TYPE_FK << AGE_FROM << SEX_FK << WEIGHT_FROM << UID_TOURNAMENT_CATEGORY << ": " << count;
            }
        }
        /**/
    }









    /*/
    QAxWidget excel("Excel.Application");
    excel.setProperty("Visible", true);

    QAxObject *workbooks = excel.querySubObject("WorkBooks");
    workbooks->dynamicCall("Add");

    QAxObject * workbook = excel.querySubObject("ActiveWorkBook");

    QAxObject * sheets = workbook->querySubObject("WorkSheets");
    sheets->querySubObject("Add");
    sheets->querySubObject("Add");
    sheets->querySubObject("Add");

    QAxObject* sheet = sheets->querySubObject( "Item( int )", 2);

    QAxObject * cell = sheet->querySubObject( "Cells( int, int )", 3, 5);
    cell->setProperty("Value", "Я ебу");
    QAxObject *border = cell->querySubObject("Borders()");
    border->setProperty("LineStyle", 1);
    border->setProperty("Weight", 2);
    delete cell;
            //    excel_1.setProperty("DisplayAlerts", 0);
            //    workbook_1->dynamicCall("SaveAs (const QString&)", QString("D:\\Temp\\test_1.xls"));
            //    workbook_1->dynamicCall("Close (Boolean)", false);
            //    excel_1.setProperty("DisplayAlerts", 1);
            //    excel_1.dynamicCall("Quit (void)");
    /**/

    //    QSqlQuery queryTournamentCategories("SELECT * FROM TOURNAMENT_CATEGORIES WHERE TOURNAMENT_FK = ? ", database);
    //    queryTournamentCategories.bindValue(0, tournamentUID);
    //    if (queryTournamentCategories.exec())
    //    {
    //        while (queryTournamentCategories.next())
    //        {
    //            long long UIDTournamentCategory = queryTournamentCategories.value("UID").toLongLong();



    //        }
    //    }
    //    else
    //    {
    //        qDebug() << __PRETTY_FUNCTION__ << " " << queryTournamentCategories.lastError().text() << " " << queryTournamentCategories.lastQuery();
    //    }
}

void FitingDistribution::initTableHeads(QAxObject* sheet, int& currentRow)
{
    QAxObject *cell;

    cell = sheet->querySubObject( "Cells( int, int )", currentRow, 1);
    cell->setProperty("Value", "Вес");
    delete cell;

    cell = sheet->querySubObject( "Cells( int, int )", currentRow, 2);
    cell->setProperty("Value", "Кол-во\n\rчеловек");
    delete cell;

    ++currentRow;
}



