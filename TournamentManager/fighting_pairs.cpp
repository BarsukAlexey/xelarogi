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
                 if (node.isFighing)
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

void FightingPairs::printListOfPairsInExcel(DialogChoseData& dlg, QAxObject *sheet,
                                 const QVector<DBUtils::NodeOfTournirGrid>& pairs, int ring)
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

    for (int i = 0, pair = 1; i < pairs.size(); ++i, ++pair)
    {
        const DBUtils::NodeOfTournirGrid& f = pairs[i];
        if (i == 0 || pairs[i].tournamentCategory != pairs[i - 1].tournamentCategory)
        {
            ++currentRow;

            QString nameOfLevel = RenderAreaWidget::getNameOfLevel(f.v);
            if (translations.contains(nameOfLevel)) nameOfLevel = translations[nameOfLevel];

            ExcelUtils::setValue(sheet, currentRow, 1, nameOfLevel);
            ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 3);
            ExcelUtils::setFontBold(sheet, currentRow, 1, true);
            ++currentRow;

            ExcelUtils::setValue(sheet, currentRow, 1,
                                 DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", f.tournamentCategory));
            ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 3);
            ++currentRow;
        }

        ExcelUtils::setValue(sheet, currentRow, 1, QString::number(pair));
        ExcelUtils::setValue(sheet, currentRow, 2,
                             f.leftUID <= 0? f.leftName :
                                             DBUtils::getField("SECOND_NAME", "ORDERS", f.leftUID) + " " +
                                             DBUtils::getField("FIRST_NAME" , "ORDERS", f.leftUID) + " (" +
                                             getTextLocal(f.leftUID) +
                                             ")");
        ExcelUtils::setValue(sheet, currentRow, 3,
                             f.rightUID <= 0? f.rightName :
                                              DBUtils::getField("SECOND_NAME", "ORDERS", f.rightUID) + " " +
                                              DBUtils::getField("FIRST_NAME" , "ORDERS", f.rightUID) + " (" +
                                              getTextLocal(f.rightUID) +
                                              ")");
        ExcelUtils::setBorder(sheet, currentRow, 1, currentRow, 3);
        ++currentRow;
    }

    for (int column = 1; column <= 3; ++column)
        ExcelUtils::setColumnAutoFit(sheet, column);



    ExcelUtils::setTournamentName(sheet, DBUtils::getTournamentNameAsHeadOfDocument(tournamentUID), 1, 1, 1, 3);

    ExcelUtils::setFooter(sheet, currentRow, 1, 3, 25, dlg.getJudges(), DBUtils::getJudges(tournamentUID));
}

void FightingPairs::printListOfPairsInJSON(const QVector<DBUtils::NodeOfTournirGrid>& pairs, int ring, const QString& existingDirectory)
{
    QJsonArray arr;
    int fightingId = 1;
    for (const DBUtils::NodeOfTournirGrid& f : pairs)
    {
        QJsonObject a = getQJsonObject(f, fightingId);
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
}


void FightingPairs::makeGridsForPointFighting(QString existingDirectory, QVector<long long> tournamentCategoryUIDs)
{
    DialogChoseData dlg(DialogChoseData::Type::makeGridsForPointFighting);
    if (dlg.exec() != QDialog::Accepted)
        return;


    QVector<int> durationOfGrid;
    for (const long long tcUID : tournamentCategoryUIDs)
        durationOfGrid << DBUtils::findDurationOfGrid(tcUID, ui->spinBoxDelay->value());

    QVector<long long> constTournamentCategoryUIDs = tournamentCategoryUIDs;
    const std::vector<int> constDurationOfGrid(durationOfGrid.begin(), durationOfGrid.end());
    QVector<QVector<long long>> ansTournamentCategoryUIDs;



    QProgressDialog progress(this);
    progress.setWindowModality(Qt::WindowModal);
    progress.setMinimumDuration(0);
    progress.setMaximum(tournamentCategoryUIDs.size());


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
        if (progress.wasCanceled())
            break;

        QVector<QVector<int> > fightNumber;  // fightNumber[tree][vertex] = orderFightNumber
        {
            QVector<std::pair<int, int> > orderOfFights;  // pair(idTree, node.v)
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
                        existingDirectory, fightNumber[i], ui->qLineEdit->text(),
                        dlg.getTranslations()["Татами"] + " " +  QString("%1 (%2)").arg(idRing, 2, 10, QChar('0')).arg(i + 1, 2, 10, QChar('0')));
            workbook->dynamicCall("Close()");
            delete workbook;

            progress.setValue(progress.value() + 1);


            QVector<DBUtils::NodeOfTournirGrid> fightingNodes;
            for (DBUtils::NodeOfTournirGrid node : DBUtils::getNodes(uids[i]))
                if (node.isFighing)
                    fightingNodes << node;
            std::reverse(fightingNodes.begin(), fightingNodes.end());
            for (int j = 0; j < fightingNodes.size(); ++j)
            {
                const DBUtils::NodeOfTournirGrid f = fightingNodes[j];
                QJsonObject a = getQJsonObject(f, fightNumber[i][f.v]);
                jsonObjects << a;
            }
        }

        qSort(jsonObjects.begin(), jsonObjects.end(), [](const QJsonObject & x, const QJsonObject & y){
            return x["fightId"].toInt() < y["fightId"].toInt();
        });

        QJsonArray arr;
        for(QJsonObject x : jsonObjects) arr << x;
        const QString path =  QDir(existingDirectory).filePath("ring " + QString::number(idRing) + ".json");
        QFile saveFile(path);
        if (!saveFile.open(QIODevice::WriteOnly))
        {
            QMessageBox::warning(0, "", "Невозможно сохранить файл " + path);
        }
        else {
            qint64 localWrite = saveFile.write(QJsonDocument(arr).toJson());
            qDebug() << "writing: " << localWrite << "БайТ in " << path;
        }

        ++idRing;
    }
    delete workbooks;
    excel.dynamicCall("Quit()");

    QMessageBox::information(0, "", myThread->reportMessage);

    delete myThread;
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

QJsonObject FightingPairs::getQJsonObject(const DBUtils::NodeOfTournirGrid& f, const int fightingId)
{
    QJsonObject a;
    a["nameOfLeftFighter" ] = f.leftUID  <= 0? f.leftName  : DBUtils::getField("SECOND_NAME", "ORDERS", f.leftUID ) + " " + DBUtils::getField("FIRST_NAME", "ORDERS", f.leftUID );
    a["nameOfRightFighter"] = f.rightUID <= 0? f.rightName : DBUtils::getField("SECOND_NAME", "ORDERS", f.rightUID) + " " + DBUtils::getField("FIRST_NAME", "ORDERS", f.rightUID);

    a["fightId"] = fightingId;

    a["categoryOfFighting"]      = DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", f.tournamentCategory);
    a["categoryOfFightingShort"] = DBUtils::getWeightAsOneNumberPlusMinus(f.tournamentCategory);

    a["countOfRounds"  ] = DBUtils::getField("ROUND_COUNT"     , "TOURNAMENT_CATEGORIES", f.tournamentCategory);
    a["durationOfRound"] = DBUtils::getField("DURATION_FIGHING", "TOURNAMENT_CATEGORIES", f.tournamentCategory);
    a["durationOfBreak"] = DBUtils::getField("DURATION_BREAK"  , "TOURNAMENT_CATEGORIES", f.tournamentCategory);

    a["regionOfLeftFighter" ] = getTextLocal(f.leftUID );
    a["regionOfRightFighter"] = getTextLocal(f.rightUID);

    a["leftFlag" ] = getFlagImage(f.leftUID );
    a["rightFlag"] = getFlagImage(f.rightUID);

    a["TOURNAMENT_CATEGORIES_FK"] = f.tournamentCategory;
    a["VERTEX"] = f.v;

    a["orderUID_left" ] = f.leftUID ;
    a["orderUID_right"] = f.rightUID;

    a["IN_CASE_TIE"         ] = DBUtils::getField("IN_CASE_TIE"         , "TOURNAMENT_CATEGORIES", f.tournamentCategory).toInt();
    a["DURATION_EXTRA_ROUND"] = DBUtils::getField("DURATION_EXTRA_ROUND", "TOURNAMENT_CATEGORIES", f.tournamentCategory).toInt();
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
                if (node.isFighing && node.UID <= 0)
                {
                    currentDuration += DBUtils::findDurationOfFightinPair(tournamentCategoryUIDs[selectedRow]) +
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
        QVector<DBUtils::NodeOfTournirGrid> pairs;
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
                    for (int j = grid[turn].size() - 1; 0 <= j; --j)
                    {
                        DBUtils::NodeOfTournirGrid& node = grid[turn][j];
                        if (node.isFighing && node.UID <= 0)
                        {
                            node.name      = "Winner # " + QString::number(pairs.size() + 1);
                            node.leftUID   = grid[turn + 1][2 * j + 1].UID;
                            node.leftName  = grid[turn + 1][2 * j + 1].name;
                            node.rightUID  = grid[turn + 1][2 * j    ].UID;
                            node.rightName = grid[turn + 1][2 * j    ].name;

                            time += DBUtils::findDurationOfFightinPair(node.tournamentCategory) +
                                    ui->spinBoxDelay->value();
                            //qDebug() << "After: " << node.v << node.tournamentCategory
                            //         << DBUtils::findDurationOfFightinPair(node.tournamentCategory) + ui->spinBoxDelay->value();

                            pairs << node;
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

        QAxObject *sheet = ExcelUtils::addNewSheet(sheets);
        sheet->setProperty("Name", dlg.getTranslations()["Ринг"] + " " + QString::number(idRing + 1));

        printListOfPairsInExcel(dlg, sheet, pairs, idRing + 1);
        printListOfPairsInJSON (pairs, idRing + 1, existingDirectory);

        ExcelUtils::setPageOrientation(sheet, 1);
        ExcelUtils::setFitToPagesWide(sheet);
        ExcelUtils::setCenterHorizontally(sheet, true);
        delete sheet;

        if (progress.wasCanceled())
            break;
    }
    progress.setMaximum(selectedRows.length());

    ExcelUtils::saveAsFile(workbook, existingDirectory, "Состав пар");
    delete sheets;
    delete workbook;
    delete workbooks;
    excel.dynamicCall("Quit()");

    qDebug() << message;
    QMessageBox::information(this, "", myThread->reportMessage);

    delete myThread;
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
            sum += DBUtils::findDurationOfGrid(tournamentCategoryUID, ui->spinBoxDelay->value());
        }
    }
    sum = (sum + ui->ringSpinBox->value() - 1) / ui->ringSpinBox->value();

    ui->labelAverageTime->setText(" ~ " + QString::number(sum / 3600) + " ч. " + QString("%1").arg(sum / 60%60, 2, 10, QChar('0')) + " м.");
}

