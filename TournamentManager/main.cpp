#include "mainwindow.h"

#include <vector>

#include <QApplication>
#include <QFontDialog>
#include <QProgressDialog>

#include "ebnutvbazu.h"
#include "dialogchosedata.h"
#include "dialogselectfieldsfordimloma.h"
#include "fighting_pairs.h"
#include "fiting_distribution.h"
#include "formdipl.h"
#include "mythread.h"
#include "report_manda.cpp"
#include "tournamentgriddialog2.h"
#include "weighing_protocol.h"
#include "winner_report.h"

#include <QDateTime>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

//    int cntIter =   20;
//    {
//        QAxWidget excel("Excel.Application");
//        long long tBeg = QDateTime::currentMSecsSinceEpoch();
//        QAxObject *workbooks = excel.querySubObject("WorkBooks");
//        for (int i = 0; i < cntIter; ++i)
//        {
//            workbooks->dynamicCall("Add");
//            QAxObject *workbook = excel.querySubObject("ActiveWorkBook");
//            QAxObject *sheets   = workbook->querySubObject("WorkSheets");
//            QAxObject *sheet    = sheets->querySubObject( "Item( int )", 1);

//            delete sheet;
//            delete sheets;
//            workbook->dynamicCall("Close()");
//            delete workbook;
//        }
//        delete workbooks;
//        excel.dynamicCall("Quit()");
//        qDebug() << (QDateTime::currentMSecsSinceEpoch() - tBeg);
//    }

    return a.exec();
}
