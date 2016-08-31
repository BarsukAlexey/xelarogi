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


using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
