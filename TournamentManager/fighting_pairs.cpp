#include "fighting_pairs.h"
#include "db_utils.h"
#include "excel_utils.h"
#include "renderareawidget.h"

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
    tournamentUID(_tournamentUID)
{
    qTableWidget = new QTableWidget();
    qTableWidget->setColumnCount(4);
    qTableWidget->setHorizontalHeaderLabels(QStringList({"Категория", "Кол-во пар", "Уровень", "Бои"}));

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


        qTableWidget->setRowCount(qTableWidget->rowCount() + 1);
        QTableWidgetItem *item;

        item = new QTableWidgetItem(DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", x[0].TOURNAMENT_CATEGORIES_FK));
        item->setData(Qt::UserRole, x[0].TOURNAMENT_CATEGORIES_FK);
        qTableWidget->setItem(qTableWidget->rowCount() - 1, 0, item);

        qTableWidget->setItem(qTableWidget->rowCount() - 1, 1, new QTableWidgetItem(QString::number(x.size())));
        qTableWidget->setItem(qTableWidget->rowCount() - 1, 2, new QTableWidgetItem(RenderAreaWidget::getNameOfLevel(x[0].VERTEX)));
        qTableWidget->setItem(qTableWidget->rowCount() - 1, 3, new QTableWidgetItem(fightingDistib));
    }

    qTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    qTableWidget->setSelectionMode(QAbstractItemView::SelectionMode::MultiSelection);
    qTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    qTableWidget->resizeColumnsToContents();





    ringSpinBox = new QSpinBox;
    ringSpinBox->setMaximum(100);
    ringSpinBox->setMinimum(1);
    ringSpinBox->setValue(1);

    spinBoxDelay = new QSpinBox;
    spinBoxDelay->setMaximum(1000000);
    spinBoxDelay->setMinimum(1);
    spinBoxDelay->setValue(60);


    QGroupBox *groupBoxText = new QGroupBox("Текст");
    radioTextCountry = new QRadioButton("Страна");
    radioTextRegion  = new QRadioButton("Регион");
    radioTextCity    = new QRadioButton("Город");
    radioTextClub    = new QRadioButton("Клуб");
    {
        QHBoxLayout *hbox = new QHBoxLayout;
        hbox->addWidget(radioTextCountry);
        hbox->addWidget(radioTextRegion);
        hbox->addWidget(radioTextCity);
        hbox->addWidget(radioTextClub);
        hbox->addStretch(1);
        groupBoxText->setLayout(hbox);
    }
    radioTextRegion->setChecked(true);


    QGroupBox *groupBoxFlag = new QGroupBox("Флаг");
    radioFlagCountry = new QRadioButton("Страна");
    radioFlagRegion  = new QRadioButton("Регион");
    radioFlagCity    = new QRadioButton("Город");
    radioFlagClub    = new QRadioButton("Клуб");
    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(radioFlagCountry);
    hbox->addWidget(radioFlagRegion);
    hbox->addWidget(radioFlagCity);
    hbox->addWidget(radioFlagClub);
    hbox->addStretch(1);
    groupBoxFlag->setLayout(hbox);
    radioFlagRegion->setChecked(true);



    qPushButton = new QPushButton("GO!");


    QGridLayout *qGridLayout = new QGridLayout;
    qGridLayout->addWidget(qTableWidget, 0, 0, 1, 2);

    qGridLayout->addWidget(new QLabel(QString("Кол-во рингов:")), 1, 0, Qt::AlignRight);
    qGridLayout->addWidget(ringSpinBox, 1, 1);

    qGridLayout->addWidget(new QLabel(QString("Дата + {утро, день, вечер}:")), 2, 0, Qt::AlignRight);
    qGridLayout->addWidget(qLineEdit = new QLineEdit(), 2, 1);

    qGridLayout->addWidget(new QLabel("Временная задержка при смене пар на ринге (в секундах)"), 3, 0, Qt::AlignRight);
    qGridLayout->addWidget(spinBoxDelay, 3, 1, Qt::AlignLeft);

    qGridLayout->addWidget(checkBoxPointfighting = new QCheckBox("Сетки для поинтфайтинга"), 4, 0, 1, 2, Qt::AlignCenter);
//    checkBoxPointfighting->setChecked(true);

    qGridLayout->addWidget(groupBoxText, 5, 0, 1, 2);

    qGridLayout->addWidget(groupBoxFlag, 6, 0, 1, 2);

    qGridLayout->addWidget(qPushButton, 7, 0, 1, 2);

    setLayout(qGridLayout);

    resize(800, 600);
    setWindowFlags(windowFlags() | Qt::WindowMinMaxButtonsHint);

    connect(qPushButton, SIGNAL(clicked()), SLOT(onGoPress()));
}

FightingPairs::~FightingPairs()
{

}

void FightingPairs::printInExcel(QAxObject *sheet, const QVector<DBUtils::Fighing>& fighting, int ring)
{


    int currentRow = 2;


    ExcelUtils::setValue(sheet, currentRow, 1, "Состав пар");
    ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 3);
    ++currentRow;

    ExcelUtils::setValue(sheet, currentRow, 1, qLineEdit->text());
    ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 3);
    ++currentRow;

    ExcelUtils::setValue(sheet, currentRow, 1, "Ринг #" + QString::number(ring));
    ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 3);
    ++currentRow;

    for (int i = 0, pair = 1; i < fighting.size(); ++i, ++pair)
    {
        DBUtils::Fighing f = fighting[i];
        if (i == 0 || f.TOURNAMENT_CATEGORIES_FK != fighting[i - 1].TOURNAMENT_CATEGORIES_FK)
        {
            ++currentRow;

            ExcelUtils::setValue(sheet, currentRow, 1, RenderAreaWidget::getNameOfLevel(f.VERTEX));
            ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 3);
            ExcelUtils::setFontBold(sheet, currentRow, 1, true);
            ++currentRow;

            ExcelUtils::setValue(sheet, currentRow, 1, DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK)
                                 // + " " + DBUtils::getField("AGE_FROM", "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK) + "-" + DBUtils::getField("AGE_TILL", "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK)
                                 );
            ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 3);
            ++currentRow;
        }

        ExcelUtils::setValue(sheet, currentRow, 1, QString::number(pair));
        ExcelUtils::setValue(sheet, currentRow, 2, DBUtils::getField("SECOND_NAME", "ORDERS", f.UID0) + " " + DBUtils::getField("FIRST_NAME", "ORDERS", f.UID0) + " (" +
                             DBUtils::getField("NAME", "REGIONS", DBUtils::getField("REGION_FK", "ORDERS", f.UID0)) +
                             ")");
        ExcelUtils::setValue(sheet, currentRow, 3, DBUtils::getField( "SECOND_NAME", "ORDERS", f.UID1) + " " + DBUtils::getField("FIRST_NAME", "ORDERS", f.UID1) + " (" +
                             DBUtils::getField("NAME", "REGIONS", DBUtils::getField("REGION_FK", "ORDERS", f.UID1)) +
                             ")");
        ExcelUtils::setBorder(sheet, currentRow, 1, currentRow, 3);
        ++currentRow;
    }

    for (int column = 1; column <= 3; ++column)
        ExcelUtils::setColumnAutoFit(sheet, column);



    ExcelUtils::setTournamentName(sheet, DBUtils::getTournamentNameAsHeadOfDocument(tournamentUID), 1, 1, 1, 3);

    ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 2);
    ExcelUtils::setRowHeight(sheet, currentRow, 25);
    ExcelUtils::setValue(sheet, currentRow, 1, "Главный судья: ", 0);
//    ExcelUtils::setValue(sheet, currentRow, 3, DBUtils::get_MAIN_JUDGE(QSqlDatabase::database(), tournamentUID), 0);
    ++currentRow;

    ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 2);
    ExcelUtils::setRowHeight(sheet, currentRow, 25);
    ExcelUtils::setValue(sheet, currentRow, 1, "Главный секретарь: ", 0);
//    ExcelUtils::setValue(sheet, currentRow, 3, DBUtils::get_MAIN_SECRETARY(QSqlDatabase::database(), tournamentUID), 0);
    ++currentRow;

    ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 2);
    ExcelUtils::setRowHeight(sheet, currentRow, 25);
    ExcelUtils::setValue(sheet, currentRow, 1, "Зам. главного судьи: ", 0);
//    ExcelUtils::setValue(sheet, currentRow, 3, DBUtils::get_ASSOCIATE_MAIN_JUDGE(QSqlDatabase::database(), tournamentUID), 0);
    ++currentRow;
}

void FightingPairs::printInJSON(const QVector<DBUtils::Fighing>& fighting, int ring, const QString& existingDirectory)
{
    QJsonArray arr;
    int fightingId = 1;
    for (const DBUtils::Fighing& f : fighting)
    {
        QJsonObject a;
        a["nameOfLeftFighter" ] = DBUtils::getField("SECOND_NAME", "ORDERS", f.UID0) + " " + DBUtils::getField("FIRST_NAME", "ORDERS", f.UID0);
        a["nameOfRightFighter"] = DBUtils::getField("SECOND_NAME", "ORDERS", f.UID1) + " " + DBUtils::getField("FIRST_NAME", "ORDERS", f.UID1);

        a["fightId"] = fightingId;
        a["categoryOfFighting"] = DBUtils::getWeightAsOneNumberPlusMinus(f.TOURNAMENT_CATEGORIES_FK);

        a["countOfRounds"  ] = DBUtils::getField("ROUND_COUNT"     , "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK);
        a["durationOfRound"] = DBUtils::getField("DURATION_FIGHING", "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK);
        a["durationOfBreak"] = DBUtils::getField("DURATION_BREAK"  , "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK);

        a["countryOfLeftFighter" ] = getTextLocal(f.UID0);
        a["countryOfRightFighter"] = getTextLocal(f.UID1);

        a["leftFlag" ] = getFlagImage(f.UID0);
        a["rightFlag"] = getFlagImage(f.UID1);

        a["TOURNAMENT_CATEGORIES_FK"] = f.TOURNAMENT_CATEGORIES_FK;
        a["VERTEX"] = f.VERTEX;
        a["orderUID_left"] = f.UID0;
        a["orderUID_right"] = f.UID1;

        a["IN_CASE_TIE"         ] = DBUtils::getField("IN_CASE_TIE"         , "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK).toInt();
        a["DURATION_EXTRA_ROUND"] = DBUtils::getField("DURATION_EXTRA_ROUND", "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK).toInt();

        arr.push_back(a);
        //
        ++fightingId;
    }

    const QString path = QDir(existingDirectory).filePath("ring " + QString::number(ring) + "(kickboxing).json");
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
    QVector<int> durationOfGrid;
    for (long long tcUID : tournamentCategoryUIDs)
        durationOfGrid << DBUtils::findDurationOfGrid(tcUID, delay);

    QVector<long long> constTournamentCategoryUIDs = tournamentCategoryUIDs;
    const std::vector<int> constDurationOfGrid(durationOfGrid.begin(), durationOfGrid.end());
    QVector<QVector<long long> > ansTournamentCategoryUIDs;

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
                    curTime < time && ((double)durationOfGrid.first()) / time <= 0.10
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
    if (data.size() && (maxVal > myThread->maxSumSeg || maxVal == myThread->maxSumSeg && minVal < myThread->minSumSeg))
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
                        qDebug() << "orderOfFights:" << i << node.v;
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
            RenderAreaWidget::printTableGridInExcel(uids[i], true,
                existingDirectory, fightNumber[i], stringDate,
                "Татами " +  QString("%1 (%2)").arg(idRing, 2, 10, QChar('0')).arg(i + 1, 2, 10, QChar('0')));

            //
            QVector<DBUtils::Fighing> fightingNodes = DBUtils::getListOfPairsForFightingForPointFighting(uids[i]);
            std::reverse(fightingNodes.begin(), fightingNodes.end());
            for (int j = 0; j < fightingNodes.size(); ++j)
            {

                DBUtils::Fighing f = fightingNodes[j];
                QJsonObject a;
                a["nameOfLeftFighter" ] = DBUtils::getField("SECOND_NAME", "ORDERS", f.UID0) + " " + DBUtils::getField("FIRST_NAME", "ORDERS", f.UID0);
                a["nameOfRightFighter"] = DBUtils::getField("SECOND_NAME", "ORDERS", f.UID1) + " " + DBUtils::getField("FIRST_NAME", "ORDERS", f.UID1);


                a["fightId"] = fightNumber[i][f.VERTEX];

                a["categoryOfFighting"] = DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK);

                a["countOfRounds"  ] = DBUtils::getField("ROUND_COUNT"     , "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK);
                a["durationOfRound"] = DBUtils::getField("DURATION_FIGHING", "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK);
                a["durationOfBreak"] = DBUtils::getField("DURATION_BREAK"  , "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK);

                a["countryOfLeftFighter" ] = DBUtils::getField("NAME", "COUNTRIES", DBUtils::getField("COUNTRY_FK", "ORDERS", f.UID0));
                a["countryOfRightFighter"] = DBUtils::getField("NAME", "COUNTRIES", DBUtils::getField("COUNTRY_FK", "ORDERS", f.UID1));

                a["regionOfLeftFighter" ] = getTextLocal(f.UID0);
                a["regionOfRightFighter"] = getTextLocal(f.UID1);

                a["TOURNAMENT_CATEGORIES_FK"] = f.TOURNAMENT_CATEGORIES_FK;
                a["VERTEX"] = f.VERTEX;
                a["orderUID_left"] = f.UID0;
                a["orderUID_right"] = f.UID1;

                a["leftFlag" ] = getFlagImage(f.UID0);
                a["rightFlag"] = getFlagImage(f.UID1);

                a["IN_CASE_TIE"         ] = DBUtils::getField("IN_CASE_TIE"         , "TOURNAMENT_CATEGORIES", uids[i]).toInt();
                a["DURATION_EXTRA_ROUND"] = DBUtils::getField("DURATION_EXTRA_ROUND", "TOURNAMENT_CATEGORIES", uids[i]).toInt();

                jsonObjects << a;
                qDebug() << a["IN_CASE_TIE"         ] << a["DURATION_EXTRA_ROUND"];
            }
            /**/
        }


        qSort(jsonObjects.begin(), jsonObjects.end(), [](const QJsonObject & x, const QJsonObject & y){
            return x["fightId"].toInt() < y["fightId"].toInt();
        });

        QJsonArray arr;
        for(QJsonObject x : jsonObjects) arr << x;
        const QString path =  QDir(existingDirectory).filePath("ring " + QString::number(idRing) + "(pointfighting).json");
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


    QMessageBox::information(0, "Расчётное время по рингам", messageDisplay);
    /**/
}

QString FightingPairs::getTextLocal(long long orderUID)
{
    if (radioTextCountry->isChecked()) return DBUtils::getField("NAME", "COUNTRIES"   , DBUtils::getField("COUNTRY_FK"    , "ORDERS", orderUID));
    if (radioTextRegion ->isChecked()) return DBUtils::getField("NAME", "REGIONS"     , DBUtils::getField("REGION_FK"     , "ORDERS", orderUID));
    if (radioTextCity   ->isChecked()) return DBUtils::getField("NAME", "REGION_UNITS", DBUtils::getField("REGION_UNIT_FK", "ORDERS", orderUID));
    if (radioTextClub   ->isChecked()) return DBUtils::getField("NAME", "CLUBS"       , DBUtils::getField("CLUB_FK"       , "ORDERS", orderUID));
    return "";
}

QString FightingPairs::getFlagImage(long long orderUID)
{
    if (radioFlagCountry->isChecked()) return DBUtils::getField("FLAG", "COUNTRIES"   , DBUtils::getField("COUNTRY_FK"    , "ORDERS", orderUID));
    if (radioFlagRegion ->isChecked()) return DBUtils::getField("FLAG", "REGIONS"     , DBUtils::getField("REGION_FK"     , "ORDERS", orderUID));
    if (radioFlagCity   ->isChecked()) return DBUtils::getField("FLAG", "REGION_UNITS", DBUtils::getField("REGION_UNIT_FK", "ORDERS", orderUID));
    if (radioFlagClub   ->isChecked()) return DBUtils::getField("FLAG", "CLUBS"       , DBUtils::getField("CLUB_FK"       , "ORDERS", orderUID));
    return "";
}

void FightingPairs::onGoPress()
{
    QString existingDirectory = QFileDialog::getExistingDirectory(this);
    if (existingDirectory.isEmpty()) return;
    const int delay = spinBoxDelay->value();

    QVector<QVector<DBUtils::Fighing> > listsOfPairs;
    for(QModelIndex index : qTableWidget->selectionModel()->selectedRows())
    {
        long long tourCatUID = qTableWidget->item(index.row(), 0)->data(Qt::UserRole).toLongLong();
        //qDebug() << "row: " << row;
        listsOfPairs << DBUtils::getListOfPairsForFighting(tourCatUID);
    }

    std::random_shuffle(listsOfPairs.begin(), listsOfPairs.end());
    std::sort(listsOfPairs.begin(), listsOfPairs.end(),
              [this] (const QVector<DBUtils::Fighing>& lhs, const QVector<DBUtils::Fighing>& rhs) {
        for (QString field : {"AGE_FROM", "AGE_TILL", "WEIGHT_FROM", "WEIGHT_TILL", "SEX_FK"})
        {
            double a = DBUtils::getField(field, "TOURNAMENT_CATEGORIES", lhs[0].TOURNAMENT_CATEGORIES_FK).toDouble();
            double b = DBUtils::getField(field, "TOURNAMENT_CATEGORIES", rhs[0].TOURNAMENT_CATEGORIES_FK).toDouble();
            if (1e-7 < qAbs(a - b))
                return a < b;
        }
        return false;
    });

    if (checkBoxPointfighting->isChecked())
    {
        QVector<long long> tournamentCategoryUIDs;
        for (QVector<DBUtils::Fighing> x : listsOfPairs) tournamentCategoryUIDs << x[0].TOURNAMENT_CATEGORIES_FK;
        makeGridsForPointFighting(existingDirectory, tournamentCategoryUIDs, delay, ringSpinBox->value(), qLineEdit->text());
        return;
    }



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
    for (int ringCount = ringSpinBox->value(), idRing = 1; 1 <= ringCount; --ringCount, ++idRing)
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
    MyThread *myThread = new MyThread(durationsOfPairs, ringSpinBox->value(), maxVal, minVal);
    myThread->start();
    if (!myThread->wait(60 * 1000))
    {
        myThread->setStop();
        myThread->wait();
    }


    std::vector<int> data = myThread->ans;
    if (data.size() && (maxVal > myThread->maxSumSeg || maxVal == myThread->maxSumSeg && minVal < myThread->minSumSeg))
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
            sheets->querySubObject("Add");
            QAxObject *sheet = sheets->querySubObject( "Item( int )", 1);
            sheet->setProperty("Name", "Ринг " + QString::number(idRing));
            printInExcel(sheet, curFighing, idRing);
            printInJSON(curFighing, idRing, existingDirectory);

            ExcelUtils::setPageOrientation(sheet, 1);
            ExcelUtils::setFitToPagesWide(sheet);
            ExcelUtils::setCenterHorizontally(sheet, true);
            delete sheet;
            ++idRing;
        }
    }

    delete sheets;
    delete workbook;
    delete workbooks;

    QMessageBox::information(this, "Расчётное время по рингам", messageDisplay);
}


