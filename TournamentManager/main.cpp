#include "mainwindow.h"
#include <QApplication>

#include "fighting_pairs.h"
#include "mythread.h"
#include <vector>
#include <QFontDialog>
#include "formdipl.h"
#include "dialogselectfieldsfordimloma.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    DialogDiploma().exec();
//    return 0;

    MainWindow w;
    w.show();
//    FightingPairs p(18, 0);
//    p.show();
    //return 0;

//    FormDipl d(18); return 0;
    //d.show();

//    DialogSelectFieldsForDimloma dlg;
//    dlg.exec();





    return a.exec();
}
