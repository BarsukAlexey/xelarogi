#include "dialogschedule2.h"
#include "ui_dialogschedule2.h"

Dialogschedule2::Dialogschedule2(int tournamentUID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogschedule2),
    tournamentUID(tournamentUID)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window);
    ui->splitter->setStretchFactor(0, 30);
    ui->splitter->setStretchFactor(1, 70);

    QSettings settings;
    ui->spinBoxDelay->setValue(settings.value("spinBoxDelay", ui->spinBoxDelay->value()).toInt());

    ui->labelContest->setText(DBUtils::getField("NAME", "TOURNAMENTS", tournamentUID));
    ui->comboBoxDay->addItems(DBUtils::get_DAYS_FROM_TOURNAMENTS(tournamentUID));

    updateTree();
    onDateChanged();



    connect(ui->spinBoxRing, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &Dialogschedule2::onCountOfRingsChanged);
    connect(ui->spinBoxDelay, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &Dialogschedule2::onDateChanged);
    connect(ui->tableWidget, &Dialogschedule2TableWidget::ohDrop, this, &Dialogschedule2::onOhDrop);
    connect(ui->comboBoxDay, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &Dialogschedule2::onDateChanged);

    ui->tableWidget->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
    connect(ui->tableWidget, &Dialogschedule2TableWidget::customContextMenuRequested, [this] (const QPoint& pos)
    {
        QModelIndex index = ui->tableWidget->indexAt(pos);
        //qDebug() << pos << index;
        if (!index.isValid() || !ui->tableWidget->item(index.row(), index.column()))
            return;

        QMenu menu;
        QAction deleteAction("Удалить", &menu);
        connect(&deleteAction, &QAction::triggered, [this, &pos] ()
        {
            QModelIndex index = ui->tableWidget->indexAt(pos);
            int ring = index.column();

            int maxOrder = -1;
            for (int r = 0; r < ui->tableWidget->rowCount(); ++r)
                if (ui->tableWidget->item(r, ring))
                    maxOrder = ui->tableWidget->item(r, ring)->data(Qt::UserRole).toInt();

            int currnetOrder = ui->tableWidget->item(index.row(), index.column())->data(Qt::UserRole).toInt();

            DBUtils::deleteInSchedule(this->tournamentUID, ui->comboBoxDay->currentIndex(), ring, currnetOrder);
            for (int order = currnetOrder + 1; order <= maxOrder; ++order)
                DBUtils::updateSchedule(this->tournamentUID, ui->comboBoxDay->currentIndex(), ring, order, order - 1);

            //qDebug() << pos << index;
            this->updateRowsInTable();
            this->updateTree();
        });
        menu.addAction(&deleteAction);
        menu.exec(ui->tableWidget->viewport()->mapToGlobal(pos));
    });

    connect(ui->pushButtonListOfPairs, &QPushButton::clicked, this, &Dialogschedule2::onPushButtonListOfPairs);
}

Dialogschedule2::~Dialogschedule2()
{
    QSettings settings;
    settings.setValue("spinBoxDelay", ui->spinBoxDelay->value());
    delete ui;
}



void Dialogschedule2::onCountOfRingsChanged()
{
    const int maxCountOfDays = DBUtils::getMaxCountOfDays(tournamentUID, ui->comboBoxDay->currentIndex());
    if (ui->spinBoxRing->value() < maxCountOfDays)
    {
        ui->spinBoxRing->setValue(maxCountOfDays);
        ui->tableWidget->setColumnCount(maxCountOfDays);
    }
    else
    {
        ui->tableWidget->setColumnCount(ui->spinBoxRing->value());
    }
}

void Dialogschedule2::onDateChanged()
{
    ui->spinBoxRing->setValue(DBUtils::getMaxCountOfDays(tournamentUID, ui->comboBoxDay->currentIndex()));
    onCountOfRingsChanged();
    updateRowsInTable();
}

void Dialogschedule2::onOhDrop(QStringList str, const int currentRow, const int ring)
{
    int maxOrder = -1;
    for (int r = 0; r < ui->tableWidget->rowCount(); ++r)
        if (ui->tableWidget->item(r, ring))
            maxOrder = ui->tableWidget->item(r, ring)->data(Qt::UserRole).toInt();

    int currentOrder = maxOrder + 1;
    if (ui->tableWidget->item(currentRow, ring))
        currentOrder = ui->tableWidget->item(currentRow, ring)->data(Qt::UserRole).toInt();

    if (str[0].toInt() == -1 || str[0].toInt() == -2)
    {
        Dialogschedule2InputType dlg(this, str[0] == "-1"? "Сон" : "", 60, str[0] != "-1");
        if (dlg.exec() == QDialog::Accepted)
        {
            str[1] = QString::number(dlg.getDurationInSeconds());
            str[2] = dlg.getText();
        }
        else
            return;
    }

    for (int i = maxOrder; currentOrder <= i; --i)
        DBUtils::updateSchedule(
                    tournamentUID,
                    ui->comboBoxDay->currentIndex(),
                    ring,
                    i,
                    i + 1);

    DBUtils::insertInSchedule(
                tournamentUID,
                ui->comboBoxDay->currentIndex(),
                ring,
                currentOrder,
                str[0].toInt(),
                str[1].toInt(),
                str[2]);

    updateRowsInTable();
}

void Dialogschedule2::updateRowsInTable()
{
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setRowCount(24 * 60 * 60 / durationOfRow);
    ui->tableWidget->resizeRowsToContents();
    for (int time = 0, row = 0; time < 24 * 60 * 60; time += durationOfRow, ++row)
    {
        QString text = QString("%1").arg(time / 60 / 60, 2, 10, QChar('0')) +
                       ":" +
                       QString("%1").arg(time / 60 % 60, 2, 10, QChar('0'));
        QTableWidgetItem* item = new QTableWidgetItem(text);
        ui->tableWidget->setVerticalHeaderItem(row, item);
    }
    ui->tableWidget->resizeRowsToContents();


    for (int ring = 0; ring < ui->tableWidget->columnCount(); ++ring)
    {
        int currentTime = 0;
        int currentRow = 0;
        QSqlQuery* schelder = DBUtils::getSchelder(tournamentUID, ui->comboBoxDay->currentIndex(), ring);
        while (schelder->next())
        {
            int uid = schelder->value("UID").toInt();
            int order = schelder->value("ORDER_NUMBER").toInt();
            int uidTC = schelder->value("TOURNAMENT_CATEGORY_FK").toInt();
            int level = schelder->value("LEVEL").toInt();

            int duration;
            QString name;
            QString stringLevel;

            if (uidTC == -1)
            {
                duration = level;
                name = DBUtils::getField("NAME", "SCHEDULES", uid);
            }
            else if (uidTC == -2)
            {
                duration = level;
                name = DBUtils::getField("NAME", "SCHEDULES", uid);
            }
            else if (level == -1)
            {
                duration = DBUtils::getDurationOfGrid(uidTC, ui->spinBoxDelay->value());
                name = DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", uidTC);
                stringLevel = "Все круги";
            }
            else
            {
                duration = 0;
                QVector<QVector<DBUtils::NodeOfTournirGrid> > arr = DBUtils::getNodesAsLevelListOfList(uidTC);
                if (0 <= level && level < arr.size())
                {
                    const int durationPair = DBUtils::getDurationOfFightinPair(uidTC);
                    for (const DBUtils::NodeOfTournirGrid& node : arr[level])
                        if (node.isFight && node.UID <= 0)
                            duration += durationPair +
                                        ui->spinBoxDelay->value();
                }
                else
                    qDebug() << "Fuck:" << "uidTC, level: " << uidTC << level;

                name = DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", uidTC);
                stringLevel = (level == 0? "Финал" : level == 1? "Полуфинал" : "1 / " + QString::number(1 << level));
            }

            const int timeEnd = currentTime + duration;

            int cntOccurRows = 1;
            while ((currentRow + cntOccurRows + 1) * durationOfRow <= timeEnd)
                ++cntOccurRows;

            QTableWidgetItem* item = new QTableWidgetItem;
            item->setTextAlignment(Qt::AlignHCenter | Qt::AlignTop);
            item->setText(name +
                          (stringLevel.isEmpty()? "" : "\n" + stringLevel) +
                          "\n" +
                          Utils::getTime(currentTime) +
                          "-" +
                          Utils::getTime(timeEnd) +
                          " (" +
                          Utils::getTime(duration) +
                          ")"
                          );

            item->setData(Qt::UserRole, order);
            if (uidTC == -1)
                item->setBackgroundColor(QColor(Qt::darkGray));
            else if (uidTC == -2)
                item->setBackgroundColor(QColor(Qt::darkMagenta));
            else if (level == -1)
                item->setBackgroundColor(QColor(Qt::darkBlue));
            else
                item->setBackgroundColor(QColor("#ff7b6d"));
            item->setForeground(QBrush(Qt::white));

            ui->tableWidget->setItem(currentRow, ring, item);
            if (cntOccurRows != 1)
            {
                for (int i = 1; i < cntOccurRows; ++i)
                {
                    QTableWidgetItem* item = new QTableWidgetItem;
                    item->setData(Qt::UserRole, order);
                    ui->tableWidget->setItem(currentRow + i, ring, item);
                }
                ui->tableWidget->setSpan(currentRow, ring, cntOccurRows, 1);
            }


            currentRow += cntOccurRows;
            currentTime += duration;
        }

        delete schelder;
    }

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();

}

void Dialogschedule2::updateTree()
{
    QTime time;
    time.start();

    QStringList days = DBUtils::get_DAYS_FROM_TOURNAMENTS(tournamentUID);
    int maxCountOfDays = DBUtils::getMaxCountOfDays(tournamentUID, ui->comboBoxDay->currentIndex());
    for (int i = days.size(); i < maxCountOfDays; ++i)
        days << "День #" + QString::number(i + 1);

    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, "Сон");
        item->setData(0, Qt::UserRole, QStringList()
                      << "-1"
                      << "-1"
                      << "Сон");
        ui->treeWidget->addTopLevelItem(item);
    }
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, "Перерыв, обед, шоу...");
        item->setData(0, Qt::UserRole, QStringList()
                      << "-2"
                      << "-1"
                      << "Перерыв, обед, шоу...");
        ui->treeWidget->addTopLevelItem(item);
    }

    for (const int tournamentCategoryUID : DBUtils::get_UIDs_of_TOURNAMENT_CATEGORIES(tournamentUID))
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", tournamentCategoryUID));

        QVector<QVector<DBUtils::NodeOfTournirGrid> > nodes = DBUtils::getNodesAsLevelListOfList(tournamentCategoryUID);
        for (int level = nodes.size() - 1; 0 <= level; --level)
        {
            int countOfNotPlayedFights = 0;
            int countOfFights = 0;
            for (const DBUtils::NodeOfTournirGrid& node : nodes[level])
            {
                if (node.isFight)
                {
                    if(node.UID <= 0)
                        ++countOfNotPlayedFights;
                    ++countOfFights;
                }
            }
            if (0 < countOfFights && 0 < countOfNotPlayedFights)
            {
                QTreeWidgetItem* child = new QTreeWidgetItem();
                child->setData(0, Qt::UserRole, QStringList()
                               << QString::number(tournamentCategoryUID)
                               << QString::number(level)
                               << "Уровень турнирной категориии");
                if (countOfNotPlayedFights != countOfFights)
                    child->setText(1,
                                   QString::number(countOfNotPlayedFights) +
                                   "(из " +
                                   QString::number(countOfFights) +
                                   ")");
                else
                    child->setText(1, QString::number(countOfNotPlayedFights));
                QSqlQuery* dateRingOrderFromSchedule =
                        DBUtils::getDateRingOrderFromSchedule(tournamentCategoryUID, level);
                if (dateRingOrderFromSchedule->next())
                {
                    child->setText(2, days[dateRingOrderFromSchedule->value("DAY").toInt()]);
                    child->setText(3, QString::number(1 + dateRingOrderFromSchedule->value("RING").toInt()));
                    child->setText(4, QString::number(1 + dateRingOrderFromSchedule->value("ORDER_NUMBER").toInt()));
                }
                delete dateRingOrderFromSchedule;

                QString str;
                if (level == 0) str = "Финал";
                else if (level == 1) str = "Полуфинал";
                else str = "1 / " + QString::number(1 << level);
                child->setText(0, str);
                item->addChild(child);
            }
        }


        if (item->childCount())
        {
            item->setData(0, Qt::UserRole,
                          QStringList()
                          << QString::number(tournamentCategoryUID)
                          << "-1"
                          << "Вся сетка");
            QSqlQuery* dateRingOrderFromSchedule = DBUtils::getDateRingOrderFromSchedule(tournamentCategoryUID);
            if (dateRingOrderFromSchedule->next())
            {
                item->setText(2, days[dateRingOrderFromSchedule->value("DAY").toInt()]);
                item->setText(3, QString::number(1 + dateRingOrderFromSchedule->value("RING").toInt()));
                item->setText(4, QString::number(1 + dateRingOrderFromSchedule->value("ORDER_NUMBER").toInt()));
            }
            delete dateRingOrderFromSchedule;
            ui->treeWidget->addTopLevelItem(item);
            item->setExpanded(true);
        }
    }
    for (int column = 0; column < ui->treeWidget->columnCount(); ++column)
        ui->treeWidget->resizeColumnToContents(column);

    qDebug() << __PRETTY_FUNCTION__ << time.elapsed();
}

void Dialogschedule2::onPushButtonListOfPairs()
{
    QString existingDirectory = QFileDialog::getExistingDirectory(this);
    if (existingDirectory.isEmpty())
        return;

    DialogChoseData dlg(DialogChoseData::Type::makeGridsForPointFighting);
    if (dlg.exec() != QDialog::Accepted)
        return;

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




    for (int ring = 0; ring < ui->tableWidget->columnCount(); ++ring)
    {
        QVector<long long> uidTCs_forTournament;
        QVector<long long> uidTCs_forCub;

        QSqlQuery* schelder = DBUtils::getSchelder(tournamentUID, ui->comboBoxDay->currentIndex(), ring);
        while (schelder->next())
        {
            const int uidTC = schelder->value("TOURNAMENT_CATEGORY_FK").toInt();
            if (uidTC <= 0) continue;
            int level = schelder->value("LEVEL").toInt();
            if (level == -1)
                uidTCs_forCub << uidTC;
            else
                uidTCs_forTournament << uidTC;
        }
        delete schelder;

        if (!uidTCs_forTournament.isEmpty())
        {
        }

        if (!uidTCs_forCub.isEmpty())
        {
            QAxWidget excel("Excel.Application");
            QAxObject *workbooks = excel.querySubObject("WorkBooks");
            FightingPairs::writeGridsForPointFighting(
                        existingDirectory,
                        uidTCs_forCub,
                        workbooks,
                        excel,
                        ring + 1,
                        ui->comboBoxDay->currentText(),
                        dlg,
                        typeText,
                        typeFlag
                        );
            delete workbooks;
            excel.dynamicCall("Quit()");
        }
    }
}




