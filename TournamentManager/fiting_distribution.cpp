#include "fiting_distribution.h"
#include "tournamentgriddialog2.h"
#include <QAxObject>
#include <QAxWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QDate>





FitingDistribution::FitingDistribution(const QSqlDatabase &database, long long tournamentUID)
{
    ///TournamentGridDialog2(database, tournamentUID, 0).ebnutVBazyGovno();


    QAxObject* excel = new QAxObject( "Excel.Application", 0 );
    QAxObject* workbooks = excel->querySubObject( "Workbooks" );
    QAxObject* workbook = workbooks->querySubObject( "Open(const QString&)", "C:/code/xelarogi/Пример заявления.xlsx" );

    QAxObject* sheets = workbook->querySubObject( "Sheets" );
    int sheetCount = sheets->dynamicCall("Count()").toInt();

    QAxObject* sheet = sheets->querySubObject( "Item( int )", 1 );

    for(int row = 14; row <= 15; ++row)
    {
        for(int column = 1; column <= 11; ++column)
            if (column == 4)
                qDebug() << sheet->querySubObject("Cells( int, int )", row, column)->dynamicCall("Value()").toDate();
            else
                qDebug() << sheet->querySubObject("Cells( int, int )", row, column)->dynamicCall("Value()").toString();
        qDebug() << "";
    }




    //    QAxObject* excel = new QAxObject("Excel.Application", this);
    //    excel->setProperty("Visible", true);
    //    QAxObject* workbooks = excel->querySubObject("Workbooks");
    //    QAxObject* workbook = workbooks->querySubObject("Open(const QString&)", "D:/test_t.xlsx");

    //    QAxObject* sheets = workbook->querySubObject( "Sheets" );
    //    int sheetNumber = 1;
    //    QAxObject* sheet = sheets->querySubObject( "Item( int )", sheetNumber );




    //    workbook->dynamicCall("Close()");
    //    delete sheet;
    //    delete sheets;
    //    delete workbook;
    //    delete workbooks;
    //    excel->dynamicCall("Quit()");
    //    delete excel;

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
