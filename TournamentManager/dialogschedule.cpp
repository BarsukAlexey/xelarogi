#include "dialogschedule.h"
#include "ui_dialogschedule.h"

DialogSchedule::DialogSchedule(QWidget *parent, long long tournamentUID) :
    QDialog(parent),
    ui(new Ui::DialogSchedule),
    tournamentUID(tournamentUID),
    selectedRow(-1),
    selectedColumn(-1),
    prevUidList(-1)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window);

    modelList = new QSqlRelationalTableModel(this);
    modelList->setTable("RING_TATAMI_LISTS");
    modelList->setFilter("TOURNAMENT_FK = " + QString::number(tournamentUID));
    modelList->select();

    ui->comboBoxList->setModel(modelList);
    ui->comboBoxList->setModelColumn(modelList->fieldIndex("NAME"));

    connect(ui->pushButtonLists, &QPushButton::clicked, [this, tournamentUID](){
        QString text = this->ui->comboBoxList->currentText();
        DialogScheduleSettingLists dlg(this, tournamentUID);
        dlg.exec();
        this->modelList->select();
        this->ui->comboBoxList->setCurrentIndex(this->ui->comboBoxList->findText(text));
    });
    connect(ui->pushButtonSaveExcel, &QPushButton::clicked, this, &DialogSchedule::onSaveExcel);


    void (QComboBox:: *indexChangedSignal)(int) = &QComboBox::currentIndexChanged;
    connect(ui->comboBoxList, indexChangedSignal, this, &DialogSchedule::onListChanged);

    onListChanged();

    connect(ui->tableWidget, &QTableWidget::cellClicked, this, &DialogSchedule::onCellClicked);

    connect(ui->spinBoxRing, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &DialogSchedule::onListChanged);
    connect(ui->spinBoxDelay, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &DialogSchedule::onListChanged);
}

DialogSchedule::~DialogSchedule()
{
    delete ui;
}



void DialogSchedule::onListChanged()
{
    //QTime t;
    //t.start();

    int indexComboBox = ui->comboBoxList->currentIndex();
    if (indexComboBox == -1)
    {
        prevUidList = -1;

        ui->tableWidget->setRowCount(0);
        ui->tableWidget->setColumnCount(0);
        levels.clear();
        return;
    }

    const int uidList = modelList->record(indexComboBox).value("UID").toInt();
    const int scrollBarValue       = prevUidList == uidList? ui->tableWidget->verticalScrollBar()->value()   : 0;
    const int maxscrollBarMaxValue = prevUidList == uidList? ui->tableWidget->verticalScrollBar()->maximum() : 0;
    prevUidList = uidList;

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
    levels.clear();

    QStringList days = DBUtils::get_DAYS_FROM_TOURNAMENTS(tournamentUID);

    const int maxCountColumns = 1 + 3 * qMax(
                                    days.size(),
                                    DBUtils::getMaxDayFromGrids(tournamentUID));
    ui->tableWidget->setColumnCount(maxCountColumns);

    QVector<int> durations(maxCountColumns);

    //qDebug() << "onListChanged; List" << uidList;

    int currentRow = 0;
    QTableWidgetItem *it;
    QSqlQuery* model = DBUtils::get___TYPE_FK___AGE_FROM___AGE_TILL(uidList);
    while (model->next())
    {
        const int TYPE_FK    = model->value("TYPE_FK" ).toInt();
        const int AGE_FROM   = model->value("AGE_FROM").toInt();
        const int AGE_TILL   = model->value("AGE_TILL").toInt();
        const int MAX_UID_TC = model->value("MAX_UID_TC").toInt();

        ui->tableWidget->setRowCount(currentRow + 1);
        ui->tableWidget->setSpan(currentRow, 0, 1, maxCountColumns);
        it = new QTableWidgetItem(DBUtils::getField("NAME", "TYPES", TYPE_FK) +
                                  ", " +
                                  DBUtils::getField("AGE", "TOURNAMENT_CATEGORIES", MAX_UID_TC)
                                  );
        it->setTextAlignment(Qt::AlignCenter);
        QFont font = it->font();
        font.setBold(true);
        if (font.pointSize() != -1) font.setPointSize(font.pointSize() + 3);
        it->setFont(font);
        ui->tableWidget->setItem(currentRow, 0, it);
        ++currentRow;

        QSqlQuery* modelAGE_CATEGORY_FK___SEX_FK =
                DBUtils::get___AGE_CATEGORY_FK___SEX_FK(tournamentUID, TYPE_FK, AGE_FROM, AGE_TILL);
        while (modelAGE_CATEGORY_FK___SEX_FK->next())
        {
            int SEX_FK    = modelAGE_CATEGORY_FK___SEX_FK->value("SEX_FK").toInt();
            int ageCatUID = modelAGE_CATEGORY_FK___SEX_FK->value("AGE_CATEGORY_FK").toInt();

            ui->tableWidget->setRowCount(currentRow + 1);
            ui->tableWidget->setSpan(currentRow, 0, 1, maxCountColumns);
            it = new QTableWidgetItem(DBUtils::getField("NAME", "AGE_CATEGORIES", ageCatUID));
            it->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(currentRow, 0, it);
            ++currentRow;

            QSqlQuery* modelWEIGHTS =
                    DBUtils::get___WEIGHT_FROM___WEIGHT_TILL(tournamentUID, TYPE_FK, AGE_FROM, AGE_TILL, SEX_FK, ageCatUID);

            while (modelWEIGHTS->next())
            {
                int WEIGHT_FROM = modelWEIGHTS->value("WEIGHT_FROM").toInt();
                int WEIGHT_TILL = modelWEIGHTS->value("WEIGHT_TILL").toInt();

                QSqlQuery* modelUidTc = DBUtils::get___TC_UIDS(tournamentUID, TYPE_FK, AGE_FROM, AGE_TILL, SEX_FK, ageCatUID, WEIGHT_FROM, WEIGHT_TILL);
                while (modelUidTc->next())
                {

                    long long UID_TOURNAMENT_CATEGORY = modelUidTc->value("UID").toLongLong();

                    ui->tableWidget->setRowCount(currentRow + 1);
                    ui->tableWidget->setItem(currentRow, 0, new QTableWidgetItem(
                                DBUtils::getField("WEIGHT", "TOURNAMENT_CATEGORIES", UID_TOURNAMENT_CATEGORY)));

                    QVector<std::map<int, int>> countFights(maxCountColumns - 1);
                    QVector<std::map<int, int>> targetFights(maxCountColumns - 1);


                    QSqlQuery* queryOrders = DBUtils::getFightNodes(UID_TOURNAMENT_CATEGORY);
                    const int durationOnePairOnRing = DBUtils::getDurationOfFightinPair(UID_TOURNAMENT_CATEGORY) +
                                                      ui->spinBoxDelay->value();
                    while (queryOrders->next())
                    {
                        int t = 3 *
                                queryOrders->value("DAY_FIGHT").toInt() +
                                queryOrders->value("TIME_FIGHT").toInt();
                        int winner = queryOrders->value("ORDER_FK").toInt();
                        int v = queryOrders->value("VERTEX").toInt();
                        if (winner <= 0)
                        {
                            ++countFights[t][Utils::log2(v)];
                        }
                        ++targetFights[t][Utils::log2(v)];
                        durations[t] += durationOnePairOnRing;
                    }
                    delete queryOrders;


                    for (int i = 0; i < countFights.size(); ++i){
                        if (countFights[i].size())
                        {
                            QString str;
                            for (auto it = countFights[i].rbegin(); it != countFights[i].rend(); ++it)
                            {
                                if (!str.isEmpty()) str += ", ";
                                str += QString::number(it->second);
                                if (it->second != targetFights[i][it->first])
                                {
                                    str += "(из " + QString::number(targetFights[i][it->first]) + ")";
                                }
                                levels.resize(currentRow + 1);
                                levels[currentRow].resize(i + 1 + 1);
                                levels[currentRow][i + 1] << it->first;
                                tournamentCategories.resize(currentRow + 1);
                                tournamentCategories[currentRow] = UID_TOURNAMENT_CATEGORY;
                            }
                            ui->tableWidget->setItem(currentRow, i + 1, new QTableWidgetItem(str));
                        }
                    }
                    ++currentRow;
                }
                delete modelUidTc;
            }
            delete modelWEIGHTS;
        }
        delete modelAGE_CATEGORY_FK___SEX_FK;
    }
    delete model;
    ui->tableWidget->verticalScrollBar()->setMaximum(maxscrollBarMaxValue);
    ui->tableWidget->verticalScrollBar()->setValue(scrollBarValue);

    levels.resize(ui->tableWidget->rowCount());
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
        levels[i].resize(ui->tableWidget->columnCount());
    tournamentCategories.resize(ui->tableWidget->rowCount());

    if (selectedRow != -1)
    {
        QTableWidgetItem* item = ui->tableWidget->item(selectedRow, selectedColumn);
        item->setBackgroundColor(Qt::green);
    }

    ui->tableWidget->setItemDelegate(new StyledItemDelegateDraw3thVerticalLine(this));




    QStringList heads;
    for (int i = 0; i < ui->tableWidget->columnCount(); ++i)
    {
        QString head = "";
        if (i == 0){}
        else if (i - 1 < 3 * days.size())
        {
            head = days[(i - 1) / 3] + "\n";
        }
        else
        {
            head = "Колонка #" + QString::number(i + 1) + "\n";
        }

        if      (i % 3 == 1) head += "Утро";
        else if (i % 3 == 2) head += "День";
        else                 head += "Вечер";
        head += "\n";

        if (0 < i && durations[i - 1] != 0)
        {
            int time = durations[i - 1] / ui->spinBoxRing->value();
            head += QString::number(time / 3600) + " ч. " +
                    QString("%1").arg(time / 60 % 60, 2, 10, QChar('0')) + " м.";
        }
        heads << head;
        //qDebug() << i << head;
    }
    ui->tableWidget->setHorizontalHeaderLabels(heads);


    //qDebug("Time elapsed: %d ms", t.elapsed());
}

void DialogSchedule::onCellClicked(int currentRow, int currentColumn)
{
    //qDebug() << currentRow << currentColumn << selectedRow << selectedColumn;

    if (selectedRow == -1)
    {
        if (levels[currentRow][currentColumn].isEmpty())
        {
            selectedRow    = -1;
            selectedColumn = -1;
        }
        else
        {
            selectedRow    = currentRow;
            selectedColumn = currentColumn;
        }
    }
    else
    {
        if (currentRow == selectedRow)
        {
            bool ok = true;
            for (int i = 1 + qMin(currentColumn, selectedColumn); i < qMax(currentColumn, selectedColumn); ++i)
                ok &= levels[currentRow][i].isEmpty();
            if (ok)
            {
                int level;
                if (selectedColumn < currentColumn)
                    level = levels[currentRow][selectedColumn].last();
                else
                    level = levels[currentRow][selectedColumn].first();
                int cnt = 0;
                for (const DBUtils::NodeOfTournirGrid& node : DBUtils::getNodes(tournamentCategories[currentRow]))
                {
                    if (Utils::log2(node.v) == level &&
                        node.isFight &&
                        DBUtils::updateLevelOfNodeOfGrid(node.tournamentCategory, node.v, (currentColumn - 1) / 3, (currentColumn - 1) % 3))
                    {
                        ++cnt;
                    }
                }
                //QMessageBox::information(this, "", QString::number(cnt));
            }
        }
        selectedRow    = -1;
        selectedColumn = -1;
    }
    onListChanged();
}

void DialogSchedule::onSaveExcel()
{
    FitingDistribution(tournamentUID, this);
}


