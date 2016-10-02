#include "fighting_pairs.h"
#include "ui_fighting_pairs.h"


#include "db_utils.h"
#include "excel_utils.h"
#include "renderareawidget.h"
#include "dialogchosedata.h"

#include <QLabel>
#include <QGridLayout>
#include <QListWidget>
#include <QDebug>
#include <algorithm>
#include <QAxWidget>
#include <QAxObject>

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonValuePtr>
#include <QJsonValueRef>
#include <QJsonValueRefPtr>
#include <QVariantMap>
#include <QFileDialog>

#include <QSqlQuery>
#include <QSqlError>

#include <QMessageBox>

#include <algorithm>
#include <QThread>
#include "mythread.h"



FightingPairs::FightingPairs(long long _tournamentUID, QWidget* parent) :
    QDialog(parent),
    tournamentUID(_tournamentUID),
    ui(new Ui::FightingPairs)
{
    ui->setupUi(this);

    ui->qTableWidget->setColumnCount(4);
    ui->qTableWidget->setHorizontalHeaderLabels(QStringList({"", ""}));

    for(const QVector<DBUtils::Fighing>& x : DBUtils::getListsOfPairsForFighting(tournamentUID))
    {
        int count = 0;
        for (DBUtils::NodeOfTournirGrid f : DBUtils::getNodes(x[0].TOURNAMENT_CATEGORIES_FK))
            if (!f.isFighing)
                ++count;

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
        std::reverse(fights.begin(), fights.end());
        QString fightingDistib;
        for (int x : fights)
            fightingDistib = fightingDistib + " " + QString::number(x);


        ui->qTableWidget->setRowCount(ui->qTableWidget->rowCount() + 1);
        QTableWidgetItem *item;

        item = new QTableWidgetItem(DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", x[0].TOURNAMENT_CATEGORIES_FK));
        item->setData(Qt::UserRole, x[0].TOURNAMENT_CATEGORIES_FK);
        ui->qTableWidget->setItem(ui->qTableWidget->rowCount() - 1, 0, item);

        ui->qTableWidget->setItem(ui->qTableWidget->rowCount() - 1, 1, new QTableWidgetItem(QString::number(x.size())));
        ui->qTableWidget->setItem(ui->qTableWidget->rowCount() - 1, 2, new QTableWidgetItem(RenderAreaWidget::getNameOfLevel(x[0].VERTEX)));
        ui->qTableWidget->setItem(ui->qTableWidget->rowCount() - 1, 3, new QTableWidgetItem(fightingDistib));
    }

    ui->qTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->qTableWidget->setSelectionMode(QAbstractItemView::SelectionMode::MultiSelection);
    ui->qTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->qTableWidget->resizeColumnsToContents();



    setWindowFlags(windowFlags() | Qt::WindowMinMaxButtonsHint);

    connect(ui->qPushButton, SIGNAL(clicked()), SLOT(onGoPress()));
}

FightingPairs::~FightingPairs()
{
}

void FightingPairs::printInExcel(DialogChoseData& dlg, QAxObject *sheet, const QVector<DBUtils::Fighing>& fighting, int ring)
{

    int currentRow = 2;

    QMap<QString, QString> translations = dlg.getTranslations();

    ExcelUtils::setValue(sheet, currentRow, 1, dlg.getTitle());
    ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 3);
    ++currentRow;

    ExcelUtils::setValue(sheet, currentRow, 1, ui->qLineEdit->text());
    ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 3);
    ++currentRow;

    ExcelUtils::setValue(sheet, currentRow, 1, translations["Ринг"] + " #" + QString::number(ring));
    ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 3);
    ++currentRow;

    for (int i = 0, pair = 1; i < fighting.size(); ++i, ++pair)
    {
        DBUtils::Fighing f = fighting[i];
        if (i == 0 || f.TOURNAMENT_CATEGORIES_FK != fighting[i - 1].TOURNAMENT_CATEGORIES_FK)
        {
            ++currentRow;

            QString nameOfLevel = RenderAreaWidget::getNameOfLevel(f.VERTEX);
            if (translations.contains(nameOfLevel)) nameOfLevel = translations[nameOfLevel];

            ExcelUtils::setValue(sheet, currentRow, 1, nameOfLevel);
            ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 3);
            ExcelUtils::setFontBold(sheet, currentRow, 1, true);
            ++currentRow;

            ExcelUtils::setValue(sheet, currentRow, 1,
                                 DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK));
            ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 3);
            ++currentRow;
        }

        ExcelUtils::setValue(sheet, currentRow, 1, QString::number(pair));
        ExcelUtils::setValue(sheet, currentRow, 2,
                             DBUtils::getField("SECOND_NAME", "ORDERS", f.UID0) + " " +
                             DBUtils::getField("FIRST_NAME", "ORDERS", f.UID0) + " (" +
                             getTextLocal(f.UID0) +
                             ")");
        ExcelUtils::setValue(sheet, currentRow, 3, DBUtils::getField( "SECOND_NAME", "ORDERS", f.UID1) + " " +
                             DBUtils::getField("FIRST_NAME", "ORDERS", f.UID1) + " (" +
                             getTextLocal(f.UID1) +
                             ")");
        ExcelUtils::setBorder(sheet, currentRow, 1, currentRow, 3);
        ++currentRow;
    }

    for (int column = 1; column <= 3; ++column)
        ExcelUtils::setColumnAutoFit(sheet, column);



    ExcelUtils::setTournamentName(sheet, DBUtils::getTournamentNameAsHeadOfDocument(tournamentUID), 1, 1, 1, 3);

    ExcelUtils::setFooter(sheet, currentRow, 1, 3, 25, dlg.getJudges(), DBUtils::getJudges(tournamentUID));
}

void FightingPairs::printInJSON(const QVector<DBUtils::Fighing>& fighting, int ring, const QString& existingDirectory)
{
    QJsonArray arr;
    int fightingId = 1;
    for (const DBUtils::Fighing& f : fighting)
    {
        QJsonObject a = getQJsonObject(f, fightingId);
        arr.push_back(a);
        //
        ++fightingId;
    }

    const QString path = QDir(existingDirectory).filePath("ring " + QString::number(ring) + ".json");
    QFile saveFile(path);
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        qDebug() << saveFile.errorString();
        //qDebug() << path;
        return;
    }
    qDebug() << "writing: " << saveFile.write(QJsonDocument(arr).toJson()) << "БайТ";
    qDebug() << "writing in: " << path;
}




void FightingPairs::makeGridsForPointFighting(QString existingDirectory, QVector<long long> tournamentCategoryUIDs, const int delay, int countOfRings, QString stringDate)
{
    DialogChoseData dlg(DialogChoseData::Type::makeGridsForPointFighting);
    if (dlg.exec() != QDialog::Accepted)
        return;


    QVector<int> durationOfGrid;
    for (long long tcUID : tournamentCategoryUIDs)
        durationOfGrid << DBUtils::findDurationOfGrid(tcUID, delay);

    QVector<long long> constTournamentCategoryUIDs = tournamentCategoryUIDs;
    const std::vector<int> constDurationOfGrid(durationOfGrid.begin(), durationOfGrid.end());
    QVector<QVector<long long> > ansTournamentCategoryUIDs;


    QProgressDialog progress(this);
    progress.setWindowModality(Qt::WindowModal);
    progress.setMinimumDuration(500);
    progress.setMaximum(tournamentCategoryUIDs.size());

    QString message;
    int maxVal = (int)0;
    int minVal = (int)1e9;
    for (int ringCount = countOfRings, idRing = 1; 1 <= ringCount; --ringCount, ++idRing)
    {
        const int time = std::accumulate(durationOfGrid.begin(), durationOfGrid.end(), 0) / ringCount;
        int curTime = 0;
        ansTournamentCategoryUIDs << QVector<long long>();
        while ( tournamentCategoryUIDs.size() &&
                (
                    ringCount == 1 ||
                    curTime + durationOfGrid.first() <= time ||
                    (curTime < time && ((double)durationOfGrid.first()) / time <= 0.10)
                    )
                ){
            curTime += durationOfGrid.takeFirst();
            ansTournamentCategoryUIDs.back() << tournamentCategoryUIDs.takeFirst();
        }
        maxVal = qMax(maxVal, curTime);
        minVal = qMin(minVal, curTime);
        message += QString::number(curTime/3600) + ":" + QString("%1").arg(curTime/60%60, 2, 10, QChar('0')) + ", ";
    }




    QString messageThread;
    //MyThread *myThread = new MyThread(constDurationOfGrid, countOfRings, maxVal, minVal);
    MyThread *myThread = new MyThread(constDurationOfGrid, countOfRings, 1e9, 1e9);
    myThread->start();
    if (!myThread->wait(60 * 1000))
    {
        myThread->setStop();
        myThread->wait();
    }

    QString messageDisplay = message;
    std::vector<int> data = myThread->ans;
    if (data.size() && (maxVal > myThread->maxSumSeg || (maxVal == myThread->maxSumSeg && minVal < myThread->minSumSeg)))
    {
        qDebug() << "find better";
        ansTournamentCategoryUIDs.clear();
        for (int cnt : data)
        {
            ansTournamentCategoryUIDs << QVector<long long>();
            int time = 0;
            for (int iter = 0; iter < cnt; ++iter)
            {
                time += DBUtils::findDurationOfGrid(constTournamentCategoryUIDs.first(), delay);
                ansTournamentCategoryUIDs.back() << constTournamentCategoryUIDs.takeFirst();
            }
            messageThread += QString::number(time/3600) + ":" + QString("%1").arg(time/60%60, 2, 10, QChar('0')) + ", ";
        }
        messageDisplay = messageThread;
    }
    else
    {
        qDebug() << "don't find better";
    }
    delete myThread;



    qDebug() << message       << "  delta: " + QString::number((maxVal - minVal)/60);
    qDebug() << messageThread << "  delta: " + QString::number((myThread->maxSumSeg - myThread->minSumSeg)/60);


    QAxWidget excel("Excel.Application");
    QAxObject *workbooks = excel.querySubObject("WorkBooks");

    int idRing = 1;
    for (QVector<long long> uids : ansTournamentCategoryUIDs)
    {
        QVector<QVector<int> > fightNumber;  // fightNumber[tree][vertex] = orderFightNumber
        {
            QVector<std::pair<int, int> > orderOfFights;
            for (int i = 0; i < uids.size(); ++i)
            {
                QVector<DBUtils::NodeOfTournirGrid> nodes = DBUtils::getNodes(uids[i]);
                std::reverse(nodes.begin(), nodes.end());
                fightNumber << QVector<int>(nodes.size() + 1);
                for (DBUtils::NodeOfTournirGrid node : nodes)
                    if (node.isFighing)
                    {
                        orderOfFights << std::make_pair(i, node.v);
                        //qDebug() << "orderOfFights:" << i << node.v;
                    }
            }
            for (int i = 0; i < orderOfFights.size(); ++i)
            {
                std::pair<int, int> v = orderOfFights[i];
                if (fightNumber[v.first][v.second] == 0)
                {
                    fightNumber[v.first][v.second] = i + 1;
                    if (i + 1 != orderOfFights.size() &&
                        2 * v.second < fightNumber[v.first].size() &&
                        fightNumber[v.first][2 * v.second] != 0 &&
                        fightNumber[v.first][v.second] == fightNumber[v.first][2 * v.second] + 1)
                    {
                        fightNumber[v.first][v.second] = i + 2;
                        std::pair<int, int> nextV = orderOfFights[i + 1];
                        fightNumber[nextV.first][nextV.second] = i + 1;
                    }
                }
            }
        }


        QVector<QJsonObject> jsonObjects;
        for (int i = 0; i < uids.size(); ++i)
        {
            workbooks->dynamicCall("Add");
            QAxObject *workbook = excel.querySubObject("ActiveWorkBook");
            RenderAreaWidget::printTableGridInExcel(
                        workbook, dlg, uids[i], true,
                        existingDirectory, fightNumber[i], stringDate,
                        dlg.getTranslations()["Татами"] + " " +  QString("%1 (%2)").arg(idRing, 2, 10, QChar('0')).arg(i + 1, 2, 10, QChar('0')));
            workbook->dynamicCall("Close()");
            delete workbook;

            progress.setValue(progress.value() + 1);

            QVector<DBUtils::Fighing> fightingNodes = DBUtils::getListOfPairsForFightingForPointFighting(uids[i]);
            std::reverse(fightingNodes.begin(), fightingNodes.end());
            for (int j = 0; j < fightingNodes.size(); ++j)
            {

                DBUtils::Fighing f = fightingNodes[j];
                QJsonObject a = getQJsonObject(f, fightNumber[i][f.VERTEX]);
                jsonObjects << a;
            }
            /**/
        }


        qSort(jsonObjects.begin(), jsonObjects.end(), [](const QJsonObject & x, const QJsonObject & y){
            return x["fightId"].toInt() < y["fightId"].toInt();
        });

        QJsonArray arr;
        for(QJsonObject x : jsonObjects) arr << x;
        const QString path =  QDir(existingDirectory).filePath("ring " + QString::number(idRing) + ".json");
        QFile saveFile(path);
        if (!saveFile.open(QIODevice::WriteOnly)) {
            qWarning("Couldn't open save file.");
            qDebug() << saveFile.errorString();
            return;
        }
        qDebug() << "writing: " << saveFile.write(QJsonDocument(arr).toJson()) << "БайТ in " << path;
        /**/

        ++idRing;
    }
    delete workbooks;
    excel.dynamicCall("Quit()");

    QMessageBox::information(0, "Расчётное время по рингам", messageDisplay);
    /**/
}

QString FightingPairs::getTextLocal(long long orderUID)
{
    if (ui->radioTextCountry->isChecked()) return DBUtils::getField("NAME", "COUNTRIES"   , DBUtils::getField("COUNTRY_FK"    , "ORDERS", orderUID));
    if (ui->radioTextRegion ->isChecked()) return DBUtils::getField("NAME", "REGIONS"     , DBUtils::getField("REGION_FK"     , "ORDERS", orderUID));
    if (ui->radioTextCity   ->isChecked()) return DBUtils::getField("NAME", "REGION_UNITS", DBUtils::getField("REGION_UNIT_FK", "ORDERS", orderUID));
    if (ui->radioTextClub   ->isChecked()) return DBUtils::getField("NAME", "CLUBS"       , DBUtils::getField("CLUB_FK"       , "ORDERS", orderUID));
    return "";
}

QString FightingPairs::getFlagImage(long long orderUID)
{
    if (ui->radioFlagCountry->isChecked()) return DBUtils::getField("FLAG", "COUNTRIES"   , DBUtils::getField("COUNTRY_FK"    , "ORDERS", orderUID));
    if (ui->radioFlagRegion ->isChecked()) return DBUtils::getField("FLAG", "REGIONS"     , DBUtils::getField("REGION_FK"     , "ORDERS", orderUID));
    if (ui->radioFlagCity   ->isChecked()) return DBUtils::getField("FLAG", "REGION_UNITS", DBUtils::getField("REGION_UNIT_FK", "ORDERS", orderUID));
    if (ui->radioFlagClub   ->isChecked()) return DBUtils::getField("FLAG", "CLUBS"       , DBUtils::getField("CLUB_FK"       , "ORDERS", orderUID));
    return "";
}

QJsonObject FightingPairs::getQJsonObject(const DBUtils::Fighing& f, const int fightingId)
{
    QJsonObject a;
    a["nameOfLeftFighter" ] = DBUtils::getField("SECOND_NAME", "ORDERS", f.UID0) + " " + DBUtils::getField("FIRST_NAME", "ORDERS", f.UID0);
    a["nameOfRightFighter"] = DBUtils::getField("SECOND_NAME", "ORDERS", f.UID1) + " " + DBUtils::getField("FIRST_NAME", "ORDERS", f.UID1);

    a["fightId"] = fightingId;

    a["categoryOfFighting"]      = DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK);
    a["categoryOfFightingShort"] = DBUtils::getWeightAsOneNumberPlusMinus(f.TOURNAMENT_CATEGORIES_FK);

    a["countOfRounds"  ] = DBUtils::getField("ROUND_COUNT"     , "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK);
    a["durationOfRound"] = DBUtils::getField("DURATION_FIGHING", "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK);
    a["durationOfBreak"] = DBUtils::getField("DURATION_BREAK"  , "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK);

    a["regionOfLeftFighter" ] = getTextLocal(f.UID0);
    a["regionOfRightFighter"] = getTextLocal(f.UID1);

    a["leftFlag" ] = getFlagImage(f.UID0);
    a["rightFlag"] = getFlagImage(f.UID1);

    a["TOURNAMENT_CATEGORIES_FK"] = f.TOURNAMENT_CATEGORIES_FK;
    a["VERTEX"] = f.VERTEX;
    a["orderUID_left"] = f.UID0;
    a["orderUID_right"] = f.UID1;

    a["IN_CASE_TIE"         ] = DBUtils::getField("IN_CASE_TIE"         , "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK).toInt();
    a["DURATION_EXTRA_ROUND"] = DBUtils::getField("DURATION_EXTRA_ROUND", "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK).toInt();
    return a;
}

void FightingPairs::onGoPress()
{
    //
    QString existingDirectory = QFileDialog::getExistingDirectory(this);
    if (existingDirectory.isEmpty()) return;
    const int delay = ui->spinBoxDelay->value();

    QVector<QVector<DBUtils::Fighing> > listsOfPairs;
    for(QModelIndex index : ui->qTableWidget->selectionModel()->selectedRows())
    {
        long long tourCatUID = ui->qTableWidget->item(index.row(), 0)->data(Qt::UserRole).toLongLong();
        //qDebug() << "row: " << row;
        listsOfPairs << DBUtils::getListOfPairsForFighting(tourCatUID);
    }

    std::random_shuffle(listsOfPairs.begin(), listsOfPairs.end());
    std::sort(listsOfPairs.begin(), listsOfPairs.end(),
              [this] (const QVector<DBUtils::Fighing>& lhs, const QVector<DBUtils::Fighing>& rhs) {
        for (QString field : {"AGE_FROM", "AGE_TILL", "TYPE_FK", "SEX_FK", "WEIGHT_FROM", "WEIGHT_TILL"})
        {
            double a = DBUtils::getField(field, "TOURNAMENT_CATEGORIES", lhs[0].TOURNAMENT_CATEGORIES_FK).toDouble();
            double b = DBUtils::getField(field, "TOURNAMENT_CATEGORIES", rhs[0].TOURNAMENT_CATEGORIES_FK).toDouble();
            if (1e-7 < qAbs(a - b))
                return a < b;
        }
        return false;
    });

    if (ui->radioButtonCube->isChecked())
    {
        QVector<long long> tournamentCategoryUIDs;
        for (QVector<DBUtils::Fighing> x : listsOfPairs) tournamentCategoryUIDs << x[0].TOURNAMENT_CATEGORIES_FK;
        makeGridsForPointFighting(existingDirectory, tournamentCategoryUIDs, delay, ui->ringSpinBox->value(), ui->qLineEdit->text());
        return;
    }


    DialogChoseData dlg(DialogChoseData::Type::fighting_pair);
    if (dlg.exec() != QDialog::Accepted)
        return;


    QVector<DBUtils::Fighing> fighing;
    QVector<DBUtils::Fighing> fighing2;
    std::vector<int> durationsOfPairs;
    for (QVector<DBUtils::Fighing>& a : listsOfPairs)
    {
        std::random_shuffle(a.begin(), a.end());
        std::sort(a.begin(), a.end(), [] (const DBUtils::Fighing& lhs, const DBUtils::Fighing& rhs) {
            return lhs.VERTEX > rhs.VERTEX;
        });
        fighing << a;
        fighing2 << a;
        for(DBUtils::Fighing f : a) durationsOfPairs.push_back(DBUtils::findDurationOfFightinPair(f.TOURNAMENT_CATEGORIES_FK) + delay);
    }

    QString message;
    int minVal = (int)1e9;
    int maxVal = 0;

    QVector<QVector<DBUtils::Fighing> > ansFightings;
    for (int ringCount = ui->ringSpinBox->value(), idRing = 1; 1 <= ringCount; --ringCount, ++idRing)
    {
        int time = 0;
        for (const DBUtils::Fighing& f : fighing)
        {
            time += DBUtils::findDurationOfFightinPair(f.TOURNAMENT_CATEGORIES_FK) + delay;
        }
        time /= ringCount;

        ansFightings << QVector<DBUtils::Fighing>();
        int curTime = 0;
        QVector<DBUtils::Fighing> curFighing;
        while (fighing.size())
        {
            DBUtils::Fighing f = fighing.takeFirst();
            curTime += DBUtils::findDurationOfFightinPair(f.TOURNAMENT_CATEGORIES_FK) + delay;
            curFighing += f;
            ansFightings.back() << f;
            if (time <= curTime && 2 <= ringCount)
                break;
        }
        minVal = qMin(minVal, curTime);
        maxVal = qMax(maxVal, curTime);
        message += QString::number(curTime/3600) + ":" + QString("%1").arg(curTime/60%60, 2, 10, QChar('0')) + ", ";
    }



    QString messageThread;
    QString messageDisplay = message;
    MyThread *myThread = new MyThread(durationsOfPairs, ui->ringSpinBox->value(), maxVal, minVal);
    myThread->start();
    if (!myThread->wait(60 * 1000))
    {
        myThread->setStop();
        myThread->wait();
    }


    std::vector<int> data = myThread->ans;
    if (data.size() && (maxVal > myThread->maxSumSeg || (maxVal == myThread->maxSumSeg && minVal < myThread->minSumSeg)))
    {
        qDebug() << "find better";
        ansFightings.clear();
        for (int cnt : data)
        {
            ansFightings << QVector<DBUtils::Fighing>();
            int time = 0;
            for (int iter = 0; iter < cnt; ++iter)
            {
                time += DBUtils::findDurationOfFightinPair(fighing2.first().TOURNAMENT_CATEGORIES_FK) + delay;
                ansFightings.back() << fighing2.takeFirst();
            }
            messageThread += QString::number(time/3600) + ":" + QString("%1").arg(time/60%60, 2, 10, QChar('0')) + ", ";
        }
        messageDisplay = messageThread;
    }
    else
    {
        qDebug() << "don't find better";
    }
    delete myThread;

    qDebug() << message;
    qDebug() << messageThread;

    QAxWidget excel("Excel.Application");
    excel.setProperty("Visible", true);
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
    workbooks->dynamicCall("Add");
    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");
    QAxObject *sheets = workbook->querySubObject("WorkSheets");

    {
        int idRing = 1;
        for (QVector<DBUtils::Fighing> curFighing : ansFightings)
        {
            QAxObject *sheet = ExcelUtils::addNewSheet(sheets);
            sheet->setProperty("Name", dlg.getTranslations()["Ринг"] + " " + QString::number(idRing));
            printInExcel(dlg,  sheet, curFighing, idRing);
            printInJSON(curFighing, idRing, existingDirectory);

            ExcelUtils::setPageOrientation(sheet, 1);
            ExcelUtils::setFitToPagesWide(sheet);
            ExcelUtils::setCenterHorizontally(sheet, true);
            delete sheet;
            ++idRing;
        }
    }

    ExcelUtils::saveAsFile(workbook, existingDirectory, "Состав пар");
    delete sheets;
    delete workbook;
    delete workbooks;
    excel.dynamicCall("Quit()");

    QMessageBox::information(this, "Расчётное время по рингам", messageDisplay);
}


