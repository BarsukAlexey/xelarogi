#include "mainwindow.h"
#include <QApplication>

#include "fighting_pairs.h"
#include "fiting_distribution.h"
#include "mythread.h"
#include "tournamentgriddialog2.h"
#include <vector>
#include <QFontDialog>
#include "formdipl.h"
#include "dialogselectfieldsfordimloma.h"
#include "formdipl.h"
#include "dialogchosedata.h"
#include "ebnutvbazu.h"
#include "weighing_protocol.h"
#include "winner_report.h"

#include <QProgressDialog>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
//    w.show();

    FightingPairs f(18);
    f.show();


//    TournamentGridDialog2 dlg(18);
//    dlg.show();


//    WeighingProtocol d(18); return 228;


//    FitingDistribution d(18); return 228;



//    WinnerReport dlf(18); return 228;
//    DBUtils::getPlace(10745);


//    EbnutVBazu::setRandomWinner();



//    TournamentGridDialog2 dlg(18);
//    dlg.show();


//    GenerateTournamentCategoriesDialog dkl(18);
//    dkl.show();

//    DialogChoseData dlg(DialogChoseData::Type::lol);
//    dlg.show();


//    FormDipl d(18);
//    d.show();

//    FightingPairs p(18, 0);
//    p.show();
    //return 0;

//    FormDipl d(18); return 0;
    //d.show();

//    DialogSelectFieldsForDimloma dlg;
//    dlg.exec(); return 0;





    return a.exec();
}
