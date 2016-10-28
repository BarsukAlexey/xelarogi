#include "fighting_pairs.h"
#include "ui_fighting_pairs.h"

#include "dialogchosedata.h"
#include "db_utils.h"
#include "excel_utils.h"
#include "mythread.h"
#include "renderareawidget.h"

#include <QDebug>
#include <QLabel>
#include <QGridLayout>
#include <QListWidget>
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
#include <QThread>

#include <algorithm>


FightingPairs::FightingPairs(long long _tournamentUID, QWidget* parent) :
    QDialog(parent),
    tournamentUID(_tournamentUID),
    ui(new Ui::FightingPairs)
{
    ui->setupUi(this);

    for (const long long tournamentCategotyUID : DBUtils::get_UIDs_of_TOURNAMENT_CATEGORIES(tournamentUID))
    {
         QVector<QVector<DBUtils::NodeOfTournirGrid> > grid =
                 DBUtils::getNodesAsLevelListOfList(tournamentCategotyUID);
         QString stringColumn2("");
         int countOfTurns = 0;
         for (int i = 0; i < grid.size(); ++i)
         {
             int countFilled = 0;
             int countOfFights = 0;
             for (int j = 0; j < grid[i].size(); ++j)
             {
                 const DBUtils::NodeOfTournirGrid& node = grid[i][j];
                 if (node.isFight)
                 {
                     ++countOfFights;
                     if (0 < node.UID)
                     {
                         ++countFilled;
                     }
                 }
             }
             if (countFilled == countOfFights)
             {
                  break;
             }
             else
             {
                 if (countFilled != 0)
                 {
                    stringColumn2 = QString::number(countOfFights - countFilled) +
                                    "(из " +
                                    QString::number(countOfFights) +
                                    ") " +
                                    stringColumn2;
                 }
                 else
                 {
                    stringColumn2 = QString::number(countOfFights - countFilled) + " " + stringColumn2;
                 }
                 ++countOfTurns;
             }
         }

         if (!stringColumn2.isEmpty())
         {

            ui->qTableWidget->setRowCount(ui->qTableWidget->rowCount() + 1);

            ui->qTableWidget->setItem(ui->qTableWidget->rowCount() - 1, 0, new QTableWidgetItem(
                                          DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", tournamentCategotyUID)));

            ui->qTableWidget->setItem(ui->qTableWidget->rowCount() - 1, 1, new QTableWidgetItem(stringColumn2));

            QSpinBox *spinBoxCountOfTurns = new QSpinBox();
            spinBoxCountOfTurns->setFocusPolicy(Qt::FocusPolicy::NoFocus);
            spinBoxCountOfTurns->setMinimum(1);
            spinBoxCountOfTurns->setMaximum(countOfTurns);
            ui->qTableWidget->setCellWidget(ui->qTableWidget->rowCount() - 1, 2, spinBoxCountOfTurns);


            tournamentCategoryUIDs << tournamentCategotyUID;
            grids << grid;
            spinBoxes << spinBoxCountOfTurns;
         }
    }

    ui->qTableWidget->resizeColumnsToContents();
    ui->qTableWidget->resizeRowsToContents();

    setWindowFlags(windowFlags() | Qt::WindowMinMaxButtonsHint);

    connect(ui->qPushButton, SIGNAL(clicked()), SLOT(onGoPress()));

    connect(ui->qTableWidget, &QTableWidget::itemSelectionChanged, this, &FightingPairs::onItemSelectionChanged);
    connect(ui->ringSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &FightingPairs::onItemSelectionChanged);
    connect(ui->spinBoxDelay, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &FightingPairs::onItemSelectionChanged);
    connect(ui->radioButtonChampionship, &QRadioButton::clicked, this, &FightingPairs::onItemSelectionChanged);
    connect(ui->radioButtonCube, &QRadioButton::clicked, this, &FightingPairs::onItemSelectionChanged);
    for (QSpinBox* spinBox : spinBoxes)
    {
        connect(spinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &FightingPairs::onItemSelectionChanged);
    }
}

FightingPairs::~FightingPairs()
{
}

void FightingPairs::printListOfPairsInExcel(
        DialogChoseData& dlg,
        QAxObject *sheet,
        const QVector<NodeOfGridWithNames>& pairs,
        int ring,
        int typeText,
        QString stringDate,
        int tournamentUID
        )
{
    //

    int currentRow = 2;

    QMap<QString, QString> translations = dlg.getTranslations();

    ExcelUtils::setValue(sheet, currentRow, 1, dlg.getTitle());
    ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 3);
    ++currentRow;

    ExcelUtils::setValue(sheet, currentRow, 1, stringDate);
    ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 3);
    ++currentRow;

    ExcelUtils::setValue(sheet, currentRow, 1, translations["Ринг"] + " #" + QString::number(ring));
    ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 3);
    ++currentRow;

    for (int i = 0, pair = 1; i < pairs.size(); ++i, ++pair)
    {
        const NodeOfGridWithNames& f = pairs[i];
        if (i == 0 || pairs[i].node.tournamentCategory != pairs[i - 1].node.tournamentCategory)
        {
            ++currentRow;

            QString nameOfLevel = RenderAreaWidget::getNameOfLevel(f.node.v);
            if (translations.contains(nameOfLevel)) nameOfLevel = translations[nameOfLevel];

            ExcelUtils::setValue(sheet, currentRow, 1, nameOfLevel);
            ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 3);
            ExcelUtils::setFontBold(sheet, currentRow, 1, true);
            ++currentRow;

            ExcelUtils::setValue(sheet, currentRow, 1,
                                 DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", f.node.tournamentCategory));
            ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 3);
            ++currentRow;
        }

        ExcelUtils::setValue(sheet, currentRow, 1, QString::number(pair));
        ExcelUtils::setValue(sheet, currentRow, 2,
                             f.leftUID <= 0? f.leftName :
                                             DBUtils::getField("SECOND_NAME", "ORDERS", f.leftUID) + " " +
                                             DBUtils::getField("FIRST_NAME" , "ORDERS", f.leftUID) + " (" +
                                             getTextLocal(f.leftUID, typeText) +
                                             ")");
        ExcelUtils::setValue(sheet, currentRow, 3,
                             f.rightUID <= 0? f.rightName :
                                              DBUtils::getField("SECOND_NAME", "ORDERS", f.rightUID) + " " +
                                              DBUtils::getField("FIRST_NAME" , "ORDERS", f.rightUID) + " (" +
                                              getTextLocal(f.rightUID, typeText) +
                                              ")");
        ExcelUtils::setBorder(sheet, currentRow, 1, currentRow, 3);
        ++currentRow;
    }

    for (int column = 1; column <= 3; ++column)
        ExcelUtils::setColumnAutoFit(sheet, column);



    ExcelUtils::setTournamentName(sheet, DBUtils::getTournamentNameAsHeadOfDocument(tournamentUID), 1, 1, 1, 3);

    ExcelUtils::setFooter(sheet, currentRow, 1, 3, 25, dlg.getJudges(), DBUtils::getJudges(tournamentUID));
    /**/
}

void FightingPairs::printListOfPairsInJSON(
        const QVector<NodeOfGridWithNames>& pairs,
        int ring,
        const QString& existingDirectory,
        int typeText,
        int typeFlag)
{
    //
    QJsonArray arr;
    int fightingId = 1;
    for (const NodeOfGridWithNames f : pairs)
    {
        QJsonObject a = getQJsonObject(f, fightingId, typeText, typeFlag);
        arr << a;
        //
        ++fightingId;
    }

    const QString path = QDir(existingDirectory).filePath("ring " + QString::number(ring) + ".json");
    QFile saveFile(path);
    if (!saveFile.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(0, "", "Невозможно сохранить файл " + path);
        return;
    }
    qDebug() << "writing: " << saveFile.write(QJsonDocument(arr).toJson()) << "БайТ in" << path;
    /**/
}


void FightingPairs::makeGridsForPointFighting(QString existingDirectory, QVector<long long> tournamentCategoryUIDs)
{
    const int typeText =
            ui->radioTextCountry->isChecked()? 0 :
            ui->radioTextRegion ->isChecked()? 1 :
            ui->radioTextCity   ->isChecked()? 2 :
            ui->radioTextClub   ->isChecked()? 3 : -1;
    const int typeFlag =
            ui->radioFlagCountry->isChecked()? 0 :
            ui->radioFlagRegion ->isChecked()? 1 :
            ui->radioFlagCity   ->isChecked()? 2 :
            ui->radioFlagClub   ->isChecked()? 3 : -1;

    DialogChoseData dlg(DialogChoseData::Type::makeGridsForPointFighting);
    if (dlg.exec() != QDialog::Accepted)
        return;


    QVector<int> durationOfGrid;
    for (const long long tcUID : tournamentCategoryUIDs)
        durationOfGrid << DBUtils::getDurationOfGrid(tcUID, ui->spinBoxDelay->value());

    QVector<long long> constTournamentCategoryUIDs = tournamentCategoryUIDs;
    const std::vector<int> constDurationOfGrid(durationOfGrid.begin(), durationOfGrid.end());
    QVector<QVector<long long>> ansTournamentCategoryUIDs;



//    QProgressDialog progress(this);
//    progress.setWindowModality(Qt::WindowModal);
//    progress.setMinimumDuration(0);
//    progress.setMaximum(tournamentCategoryUIDs.size());


    MyThread *myThread = new MyThread(constDurationOfGrid, ui->ringSpinBox->value());
    myThread->start();
    if (!myThread->wait(60 * 1000))
    {
        myThread->setStop();
        myThread->wait();
    }

    std::vector<int> data = myThread->ans;

    for (int cnt : data)
    {
        ansTournamentCategoryUIDs << QVector<long long>();
        for (int iter = 0; iter < cnt; ++iter)
        {
            ansTournamentCategoryUIDs.back() << constTournamentCategoryUIDs.takeFirst();
        }
    }


    QAxWidget excel("Excel.Application");
    QAxObject *workbooks = excel.querySubObject("WorkBooks");

    int idRing = 1;
    for (QVector<long long> uids : ansTournamentCategoryUIDs)
    {
//        if (progress.wasCanceled())
//            break;

        writeGridsForPointFighting(existingDirectory,
                                   uids,
                                   workbooks,
                                   excel,
                                   idRing,
                                   ui->qLineEdit->text(),
                                   dlg,
                                   typeText,
                                   typeFlag);

        ++idRing;
    }
    delete workbooks;
    excel.dynamicCall("Quit()");

    QMessageBox::information(0, "", myThread->reportMessage);

    delete myThread;
    /**/
}

void FightingPairs::writeGridsForPointFighting(
        QString existingDirectory,
        QVector<long long> uids,
        QAxObject *workbooks,
        QAxWidget& excel,
        const int numberRing,
        const QString date,
        DialogChoseData& dlg,
        const int typeText,
        const int typeFlag
        )
{
    QVector<QVector<int> > fightNumber;  // fightNumber[tree][vertex] = orderFightNumber
    {
        QVector<std::pair<int, int> > orderOfFights;  // pair(idTree, node.v)
        for (int i = 0; i < uids.size(); ++i)
        {
            QVector<DBUtils::NodeOfTournirGrid> nodes = DBUtils::getNodes(uids[i]);
            std::reverse(nodes.begin(), nodes.end());
            fightNumber << QVector<int>(nodes.size() + 1);
            for (DBUtils::NodeOfTournirGrid node : nodes)
                if (node.isFight)
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
                    existingDirectory, fightNumber[i], date,
                    dlg.getTranslations()["Татами"] + " " +  QString("%1 (%2)").arg(numberRing, 2, 10, QChar('0')).arg(i + 1, 2, 10, QChar('0')));
        workbook->dynamicCall("Close()");
        delete workbook;

        QVector<DBUtils::NodeOfTournirGrid> fightingNodes;
        for (DBUtils::NodeOfTournirGrid node : DBUtils::getNodes(uids[i]))
            if (node.isFight)
                fightingNodes << node;
        std::reverse(fightingNodes.begin(), fightingNodes.end());
        for (int j = 0; j < fightingNodes.size(); ++j)
        {
            const DBUtils::NodeOfTournirGrid f = fightingNodes[j];
            QJsonObject a = getQJsonObject(f, fightNumber[i][f.v], typeText, typeFlag);
            jsonObjects << a;
        }
    }

    qSort(jsonObjects.begin(), jsonObjects.end(), [](const QJsonObject & x, const QJsonObject & y){
        return x["fightId"].toInt() < y["fightId"].toInt();
    });

    QJsonArray arr;
    for(QJsonObject x : jsonObjects) arr << x;
    const QString path =  QDir(existingDirectory).filePath("ring " + QString::number(numberRing) + ".json");
    QFile saveFile(path);
    if (!saveFile.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(0, "", "Невозможно сохранить файл " + path);
    }
    else {
        qint64 localWrite = saveFile.write(QJsonDocument(arr).toJson());
        qDebug() << "writing: " << localWrite << "БайТ in " << path;
    }
    /**/
}



QString FightingPairs::getTextLocal(long long orderUID, int type)
{
    if (type == 0) return DBUtils::getField("NAME", "COUNTRIES"   , DBUtils::getField("COUNTRY_FK"    , "ORDERS", orderUID));
    if (type == 1) return DBUtils::getField("NAME", "REGIONS"     , DBUtils::getField("REGION_FK"     , "ORDERS", orderUID));
    if (type == 2) return DBUtils::getField("NAME", "REGION_UNITS", DBUtils::getField("REGION_UNIT_FK", "ORDERS", orderUID));
    if (type == 3) return DBUtils::getField("NAME", "CLUBS"       , DBUtils::getField("CLUB_FK"       , "ORDERS", orderUID));
    return "";
}

QString FightingPairs::getFlagImage(long long orderUID, int type)
{
    if (type == 0) return DBUtils::getField("FLAG", "COUNTRIES"   , DBUtils::getField("COUNTRY_FK"    , "ORDERS", orderUID));
    if (type == 1) return DBUtils::getField("FLAG", "REGIONS"     , DBUtils::getField("REGION_FK"     , "ORDERS", orderUID));
    if (type == 2) return DBUtils::getField("FLAG", "REGION_UNITS", DBUtils::getField("REGION_UNIT_FK", "ORDERS", orderUID));
    if (type == 3) return DBUtils::getField("FLAG", "CLUBS"       , DBUtils::getField("CLUB_FK"       , "ORDERS", orderUID));
    return "";
}

QJsonObject FightingPairs::getQJsonObject(const NodeOfGridWithNames& f, const int fightingId, int typeText, int typeFlag)
{
    QJsonObject a;
    a["nameOfLeftFighter" ] = f.leftUID  <= 0? f.leftName  : DBUtils::getField("SECOND_NAME", "ORDERS", f.leftUID ) + " " + DBUtils::getField("FIRST_NAME", "ORDERS", f.leftUID );
    a["nameOfRightFighter"] = f.rightUID <= 0? f.rightName : DBUtils::getField("SECOND_NAME", "ORDERS", f.rightUID) + " " + DBUtils::getField("FIRST_NAME", "ORDERS", f.rightUID);

    a["fightId"] = fightingId;

    a["categoryOfFighting"]      = DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", f.node.tournamentCategory);
    a["categoryOfFightingShort"] = DBUtils::getWeightAsOneNumberPlusMinus(f.node.tournamentCategory);

    a["countOfRounds"  ] = DBUtils::getField("ROUND_COUNT"     , "TOURNAMENT_CATEGORIES", f.node.tournamentCategory);
    a["durationOfRound"] = DBUtils::getField("DURATION_FIGHING", "TOURNAMENT_CATEGORIES", f.node.tournamentCategory);
    a["durationOfBreak"] = DBUtils::getField("DURATION_BREAK"  , "TOURNAMENT_CATEGORIES", f.node.tournamentCategory);

    a["regionOfLeftFighter" ] = getTextLocal(f.leftUID , typeText);
    a["regionOfRightFighter"] = getTextLocal(f.rightUID, typeText);

    a["leftFlag" ] = getFlagImage(f.leftUID , typeFlag);
    a["rightFlag"] = getFlagImage(f.rightUID, typeFlag);

    a["TOURNAMENT_CATEGORIES_FK"] = f.node.tournamentCategory;
    a["VERTEX"] = f.node.v;

    a["orderUID_left" ] = f.leftUID ;
    a["orderUID_right"] = f.rightUID;

    a["IN_CASE_TIE"         ] = DBUtils::getField("IN_CASE_TIE"         , "TOURNAMENT_CATEGORIES", f.node.tournamentCategory).toInt();
    a["DURATION_EXTRA_ROUND"] = DBUtils::getField("DURATION_EXTRA_ROUND", "TOURNAMENT_CATEGORIES", f.node.tournamentCategory).toInt();
    return a;
}

std::vector<int> FightingPairs::getDurationsOfFightsForChampionship(const QVector<int>& selectedRows)
{
    std::vector<int> durationsOfFights;
    for (const int selectedRow : selectedRows)
    {
        int currentDuration = 0;
        for (int turn = spinBoxes[selectedRow]->maximum() - 1;
             spinBoxes[selectedRow]->maximum() - spinBoxes[selectedRow]->value()  <= turn;
             --turn)
        {
            const QVector<QVector<DBUtils::NodeOfTournirGrid>>& grid = grids[selectedRow];
            for (int j = grid[turn].size() - 1; 0 <= j; --j)
            {
                const DBUtils::NodeOfTournirGrid& node = grid[turn][j];
                if (node.isFight && node.UID <= 0)
                {
                    currentDuration += DBUtils::getDurationOfFightinPair(tournamentCategoryUIDs[selectedRow]) +
                                       ui->spinBoxDelay->value();
                    //qDebug() << "Befor: " << node.v << node.tournamentCategory
                    //         << DBUtils::findDurationOfFightinPair(tournamentCategoryUIDs[selectedRow]) + ui->spinBoxDelay->value()
                    //         << DBUtils::findDurationOfFightinPair(node.tournamentCategory) + ui->spinBoxDelay->value();
                }
            }
        }
        durationsOfFights.push_back(currentDuration);
    }
    return durationsOfFights;
}

void FightingPairs::onGoPress()
{
    const int typeText =
            ui->radioTextCountry->isChecked()? 0 :
            ui->radioTextRegion ->isChecked()? 1 :
            ui->radioTextCity   ->isChecked()? 2 :
            ui->radioTextClub   ->isChecked()? 3 : -1;
    const int typeFlag =
            ui->radioFlagCountry->isChecked()? 0 :
            ui->radioFlagRegion ->isChecked()? 1 :
            ui->radioFlagCity   ->isChecked()? 2 :
            ui->radioFlagClub   ->isChecked()? 3 : -1;

    QString existingDirectory = QFileDialog::getExistingDirectory(this);
    if (existingDirectory.isEmpty())
        return;

    QVector<int> selectedRows;
    for(QModelIndex index : ui->qTableWidget->selectionModel()->selectedRows())
    {
        selectedRows << index.row();
    }

    QVector<int> countsOfTakenTurns;
    QVector<int> maxCountsOfTurns;
    for (int i = 0; i < spinBoxes.size(); ++i)
    {
        countsOfTakenTurns << spinBoxes[i]->value();
        maxCountsOfTurns   << spinBoxes[i]->maximum();
    }

    if (ui->radioButtonCube->isChecked())
    {
        QVector<long long> tournamentCategoryUIDs;
        for (const int selectedRow : selectedRows)
        {
            tournamentCategoryUIDs << grids[selectedRow][0][0].tournamentCategory;
        }
        makeGridsForPointFighting(existingDirectory, tournamentCategoryUIDs);
        return;
    }


    DialogChoseData dlg(DialogChoseData::Type::fighting_pair);
    if (dlg.exec() != QDialog::Accepted)
        return;

    std::vector<int> durationsOfFights = getDurationsOfFightsForChampionship(selectedRows);


    MyThread *myThread = new MyThread(durationsOfFights, ui->ringSpinBox->value());
    myThread->start();
    if (!myThread->wait(60 * 1000))
    {
        myThread->setStop();
        myThread->wait();
    }

    std::vector<int> countOfGrids = myThread->ans; // countOfGrids[idRing] = кол-во сеток на ринге #idRing


    QProgressDialog progress(this);
    progress.setWindowModality(Qt::WindowModal);
    progress.setMinimumDuration(0);
    progress.setMaximum(selectedRows.length());


    QAxWidget excel("Excel.Application");
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
    workbooks->dynamicCall("Add");
    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");
    QAxObject *sheets = workbook->querySubObject("WorkSheets");
    QString message;
    for (int idRing = 0; idRing < ui->ringSpinBox->value() && !selectedRows.isEmpty(); ++idRing)
    {
        QVector<int> selectedRowsForCurrentRing;
        for (int i = 0; i < countOfGrids[idRing]; ++i){
            selectedRowsForCurrentRing << selectedRows.takeFirst();
            progress.setValue(progress.value() + 1);
        }

        int time = 0;
        QVector<std::pair<int, int>> uidTC_Level;
        while (true)
        {
            bool doSomeThing = false;
            for (const int selectedRowForCurrentRing : selectedRowsForCurrentRing)
            {
                if (0 < countsOfTakenTurns[selectedRowForCurrentRing])
                {
                    doSomeThing = true;
                    QVector<QVector<DBUtils::NodeOfTournirGrid>>& grid = grids[selectedRowForCurrentRing];
                    const int turn = maxCountsOfTurns[selectedRowForCurrentRing] - 1;
                    uidTC_Level << std::make_pair(grid[0][0].tournamentCategory, turn);
                    for (int j = grid[turn].size() - 1; 0 <= j; --j)
                    {
                        DBUtils::NodeOfTournirGrid& node = grid[turn][j];
                        if (node.isFight && node.UID <= 0)
                        {
                            time += DBUtils::getDurationOfFightinPair(node.tournamentCategory) +
                                    ui->spinBoxDelay->value();
                        }
                    }
                    --countsOfTakenTurns[selectedRowForCurrentRing];
                    --maxCountsOfTurns[selectedRowForCurrentRing];
                }
            }
            if (!doSomeThing)
                break;
        }
        message += " " + QString::number(time / 3600) + " ч. " + QString("%1").arg(time / 60%60, 2, 10, QChar('0')) + " м.";

        writeListOfPairs(uidTC_Level, sheets, dlg, idRing + 1, typeText, typeFlag, ui->qLineEdit->text(),
                         existingDirectory,
                         tournamentUID);

        if (progress.wasCanceled())
            break;
    }
    progress.setMaximum(selectedRows.length());

    ExcelUtils::saveAsFile(workbook, existingDirectory, "Состав пар");
    workbook->dynamicCall("Close (Boolean)", true);
    excel.dynamicCall("Quit()");
    delete sheets;
    delete workbook;
    delete workbooks;


    qDebug() << message;
    QMessageBox::information(this, "", myThread->reportMessage);

    delete myThread;
}


void FightingPairs::writeListOfPairs(
        const QVector<std::pair<int, int>>& uidTC_Level,
        QAxObject *sheets,
        DialogChoseData& dlg,
        int ringNumber,
        int typeText,
        int typeFlag,
        QString stringDate,
        QString existingDirectory,
        int tournamentUID
        )
{
    QVector<NodeOfGridWithNames> pairs;
    {
        QMap<int, QVector<QVector<NodeOfGridWithNames>>> map;
        for (std::pair<int, int> it : uidTC_Level)
        {
            if (!map.contains(it.first))
            {
                QVector<QVector<DBUtils::NodeOfTournirGrid>> grid = DBUtils::getNodesAsLevelListOfList(it.first);
                QVector<QVector<NodeOfGridWithNames>> gridWithNames(grid.size());
                for (int i = 0; i < grid.size(); ++i)
                {
                    gridWithNames[i].resize(grid[i].size());
                    for (int j = 0; j < grid[i].size(); ++j)
                    {
                        gridWithNames[i][j] = NodeOfGridWithNames(grid[i][j]);
                    }
                }
                map[it.first] = gridWithNames;
            }
        }
        for (int i = 0; i < uidTC_Level.size(); ++i)
        {
            int uidTC = uidTC_Level[i].first;
            int turn  = uidTC_Level[i].second;
            QVector<QVector<NodeOfGridWithNames>>& grid = map[uidTC];
            for (int j = grid[turn].size() - 1; 0 <= j; --j)
            {
                NodeOfGridWithNames& node = grid[turn][j];
                if (node.node.isFight && node.node.UID <= 0)
                {
                    node.name      = "Winner # " + QString::number(pairs.size() + 1);
                    node.leftUID   = grid[turn + 1][2 * j + 1].node.UID;
                    node.leftName  = grid[turn + 1][2 * j + 1].name;
                    node.rightUID  = grid[turn + 1][2 * j    ].node.UID;
                    node.rightName = grid[turn + 1][2 * j    ].name;

                    pairs << node;
                }
            }
        }
    }


    QAxObject *sheet = ExcelUtils::addNewSheet(sheets);
    sheet->setProperty("Name", dlg.getTranslations()["Ринг"] + " " + QString::number(ringNumber));

    printListOfPairsInExcel(dlg, sheet, pairs, ringNumber, typeText, stringDate, tournamentUID);
    printListOfPairsInJSON (pairs, ringNumber, existingDirectory, typeText, typeFlag);

    ExcelUtils::setPageOrientation(sheet, 1);
    ExcelUtils::setFitToPagesWide(sheet);
    ExcelUtils::setCenterHorizontally(sheet, true);
    delete sheet;
}


void FightingPairs::onItemSelectionChanged()
{
    QVector<int> selectedRows;
    for(QModelIndex index : ui->qTableWidget->selectionModel()->selectedRows())
    {
        selectedRows << index.row();
    }

    int sum = 0;
    if (ui->radioButtonChampionship->isChecked())
    {
        for (const int duraton : getDurationsOfFightsForChampionship(selectedRows))
        {
            sum += duraton;
        }
    }
    else
    {
        for (const int selectedRow : selectedRows)
        {
            long long tournamentCategoryUID = grids[selectedRow][0][0].tournamentCategory;
            sum += DBUtils::getDurationOfGrid(tournamentCategoryUID, ui->spinBoxDelay->value());
        }
    }
    sum = (sum + ui->ringSpinBox->value() - 1) / ui->ringSpinBox->value();

    ui->labelAverageTime->setText(" ~ " + QString::number(sum / 3600) + " ч. " + QString("%1").arg(sum / 60%60, 2, 10, QChar('0')) + " м.");
}

