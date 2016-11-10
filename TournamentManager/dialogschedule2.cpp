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
    connect(ui->tableWidget, &Dialogschedule2TableWidget::dataIsDropped, this, &Dialogschedule2::onDataIsDropped);
    connect(ui->comboBoxDay, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &Dialogschedule2::onDateChanged);

    ui->tableWidget->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
    connect(ui->tableWidget, &Dialogschedule2TableWidget::customContextMenuRequested, this, &Dialogschedule2::onCustomContextMenuRequested);

    connect(ui->pushButtonListOfPairs, &QPushButton::clicked, this, &Dialogschedule2::onPushButtonListOfPairs);
    connect(ui->pushButtonSaveSchelder, &QPushButton::clicked, this, &Dialogschedule2::onPushButtonSaveSchelderClicked);
}

Dialogschedule2::~Dialogschedule2()
{
    QSettings settings;
    settings.setValue("spinBoxDelay", ui->spinBoxDelay->value());
    delete ui;
}

QVector<std::tuple<int, QString, QColor>> Dialogschedule2::getInfoForRing(const int tournamentUID, const int day, const int ring, const int delay)
{
    QVector<std::tuple<int, QString, QColor>> arr;
    int currentTime = 0;
    int currentRow = 0;
    QSqlQuery* schelder = DBUtils::getSchelder(tournamentUID, day, ring);
    while (schelder->next())
    {
        int uid = schelder->value("UID").toInt();
        //int order = schelder->value("ORDER_NUMBER").toInt();
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
            duration = DBUtils::getDurationOfGrid(uidTC, delay);
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
                        duration += durationPair + delay;
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


        QString text = name +
                       (stringLevel.isEmpty()? "" : "\n" + stringLevel) +
                       "\n" +
                       Utils::getTime(currentTime) +
                       "-" +
                       Utils::getTime(timeEnd) +
                       " (" +
                       Utils::getTime(duration) +
                       ")";


        QColor color;
        if (uidTC == -1)
            color = QColor(Qt::darkGray);
        else if (uidTC == -2)
            color = QColor(Qt::darkMagenta);
        else if (level == -1)
            color = QColor(Qt::darkBlue);
        else
            color = QColor("#ff7b6d");

        arr << std::make_tuple(cntOccurRows, text, color);

        currentRow += cntOccurRows;
        currentTime += duration;
    }
    delete schelder;
    return arr;
}



void Dialogschedule2::onCountOfRingsChanged()
{
    const int maxCountOfDays = DBUtils::getMaxCountOfRings(tournamentUID, ui->comboBoxDay->currentIndex());
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
    ui->spinBoxRing->setValue(DBUtils::getMaxCountOfRings(tournamentUID, ui->comboBoxDay->currentIndex()));
    onCountOfRingsChanged();
    updateRowsInTable();
}

void Dialogschedule2::onDataIsDropped(QStringList str, const int currentRow, const int ring)
{
    if (str.size() != 3 || !(0<=currentRow && currentRow < ui->tableWidget->rowCount()))
    {
        qDebug() << "FUCK" << __LINE__ << __PRETTY_FUNCTION__ << str << currentRow;
        return;
    }

    int maxOrder = -1;
    for (int r = 0; r < ui->tableWidget->rowCount(); ++r)
        if (ui->tableWidget->item(r, ring))
            maxOrder = ui->tableWidget->item(r, ring)->data(Qt::UserRole).toInt();

    int currentOrder = maxOrder + 1;
    if (ui->tableWidget->item(currentRow, ring))
        currentOrder = ui->tableWidget->item(currentRow, ring)->data(Qt::UserRole).toInt();

    if (str[0].toInt() == -1)
    {
        QSqlQuery* schelder = DBUtils::getSchelder(tournamentUID, ui->comboBoxDay->currentIndex(), ring);
        if (schelder->next())
        {
            if (schelder->value("TOURNAMENT_CATEGORY_FK").toInt() == -1)
            {
                QMessageBox::warning(this, "", "На одном ринге может быть только \"один сон\".\n"
                                                      "Удалите существующий сон и вставьте новый.");
                delete schelder;
                return ;
            }
        }

        if (currentOrder != 0)
        {
            QMessageBox::warning(this, "", "Сон может быть только на первом месте.");
            delete schelder;
            return ;
        }
        delete schelder;
    } else
    {
        if (currentRow == 0)
        {
            QSqlQuery* schelder = DBUtils::getSchelder(tournamentUID, ui->comboBoxDay->currentIndex(), ring);
            if (schelder->next())
            {
                if (schelder->value("TOURNAMENT_CATEGORY_FK").toInt() == -1)
                {
                    QMessageBox::warning(this, "", "Нельзя ничего вставлять перед сном.");
                    delete schelder;
                    return ;
                }
            }
            delete schelder;
        }

        if (0 < str[0].toInt())
        {
            const int uidTC = str[0].toInt();
            const int level = str[1].toInt();
            QVector<QVector<DBUtils::NodeOfTournirGrid> > grid = DBUtils::getNodesAsLevelListOfList(uidTC);
            const int levelCount = grid.size();


            std::tuple<int, int, int> dayRingOrder = DBUtils::getDayRingOrder(uidTC, level);
            if (std::get<0>(dayRingOrder) != -1)
            {
                QMessageBox::warning(this, "",  "Такая сетка уже есть.");
                return ;
            }

            if (level == -1)
            {
                for (int i = 0; i < levelCount; ++i)
                {
                    std::tuple<int, int, int> dayRingOrder = DBUtils::getDayRingOrder(uidTC, i);
                    if (std::get<0>(dayRingOrder) != -1)
                    {
                        QMessageBox::warning(this, "",
                                             "Один из кругов этой сетки уже в расписании.\n"
                                             "Удалите этот круг. И киньте эту сетку целиком ещё раз."
                                             );
                        return ;
                    }
                }
            }
            else
            {
                if (std::get<0>(DBUtils::getDayRingOrder(uidTC, -1)) != -1)
                {
                    QMessageBox::warning(this, "",
                                         "Вы уже кинули всю сетку целиком.\n"
                                         "Удалите эту сетку. И киньте этот круг ещё раз."
                                         );
                    return ;
                }


                if (level + 1 != levelCount)
                {
                    std::tuple<int, int, int> dayRingOrder = DBUtils::getDayRingOrder(uidTC, level + 1);

                    int countOfNotPlayedFights = 0;
                    for (const DBUtils::NodeOfTournirGrid& node : grid[level + 1])
                    {
                        if (node.isFight && node.UID <= 0)
                        {
                            ++countOfNotPlayedFights;
                        }
                    }

                    if (0 < countOfNotPlayedFights && std::get<0>(dayRingOrder) == -1)
                    {
                        QMessageBox::warning(this, "", "Вставьте предыдущий круг турнирной сетки в расписание");
                        return ;
                    }

                    if (std::get<0>(dayRingOrder) != -1 && ui->comboBoxDay->currentIndex() < std::get<0>(dayRingOrder))
                    {
                        QMessageBox::warning(this, "", "См. на дату предыдущего круга");
                        return ;
                    }
                }

                int anotherRing = DBUtils::getAnotherRing(uidTC, ui->comboBoxDay->currentIndex(), ring);
                if (anotherRing != -1)
                {
                    qDebug() << "anotherRing:" << anotherRing;
                    QMessageBox::warning(this, "", "В этот день данную турнирную категорию можно "
                                                   "проводить только на ринге #" + QString::number(anotherRing + 1));
                    return ;
                }

                if (level + 1 != levelCount)
                {

                    if (std::get<2>(dayRingOrder) != -1 && currentOrder <= std::get<2>(dayRingOrder))
                    {
                        QMessageBox::warning(this, "", "На данном ринге вначале должен идти предудущий круг,"
                                                       " а затем текущий");
                        return ;
                    }
                }

            }
        }
    }


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
    updateTree();
}

void Dialogschedule2::onCustomContextMenuRequested(const QPoint& pos)
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


        QSqlQuery* schelder =
                DBUtils::getSchelder(tournamentUID, ui->comboBoxDay->currentIndex(), ring);
        for(int i = 0; i <= currnetOrder; ++i)
            schelder->next();
        const int uidTC = schelder->value("TOURNAMENT_CATEGORY_FK").toInt();
        const int level = schelder->value("LEVEL").toInt();
        delete schelder;
        if (1 <= level && std::get<0>(DBUtils::getDayRingOrder(uidTC, level - 1)) != -1)
        {
            QMessageBox::warning(this, "", "Удалите сначала \"" +
                                 (level-1==0?"ФИНАЛ":level-1==1?"ПОЛУФИНАЛ":"1/"+QString::number(1<<(level-1))) +
                                 "\" взятой турнирной категории из расписания");
            return;
        }

        DBUtils::deleteInSchedule(this->tournamentUID, ui->comboBoxDay->currentIndex(), ring, currnetOrder);
        for (int order = currnetOrder + 1; order <= maxOrder; ++order)
            DBUtils::updateSchedule(this->tournamentUID, ui->comboBoxDay->currentIndex(), ring, order, order - 1);

        //qDebug() << pos << index;
        this->updateRowsInTable();
        this->updateTree();
    });
    menu.addAction(&deleteAction);
    menu.exec(ui->tableWidget->viewport()->mapToGlobal(pos));
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
        QVector<std::tuple<int, QString, QColor> > infoForRing =
                getInfoForRing(tournamentUID, ui->comboBoxDay->currentIndex(), ring, ui->spinBoxDelay->value());
        for (int order = 0, currentRow = 0; order < infoForRing.size(); ++order)
        {
            int cntOccurRows = std::get<0>(infoForRing[order]);
            QString text = std::get<1>(infoForRing[order]);
            QColor color = std::get<2>(infoForRing[order]);

            QTableWidgetItem* item = new QTableWidgetItem;
            item->setTextAlignment(Qt::AlignHCenter | Qt::AlignTop);
            item->setText(text);

            item->setData(Qt::UserRole, order);
            item->setBackgroundColor(color);
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
        }
    }

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();

}

void Dialogschedule2::updateTree()
{
    QTime time;
    time.start();

    ui->treeWidget->clear();
    QStringList days = DBUtils::get_DAYS_FROM_TOURNAMENTS(tournamentUID);
    int maxCountOfDays = DBUtils::getMaxCountOfRings(tournamentUID, ui->comboBoxDay->currentIndex());
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

    for (const int tournamentCategoryUID : DBUtils::getTournamentCategoryUIDs(tournamentUID))
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
    QString mainDirectory = QFileDialog::getExistingDirectory(this);
    if (mainDirectory.isEmpty())
        return;

    QString pathCube = QDir(mainDirectory).filePath("Cube");
    QString pathTournament = QDir(mainDirectory).filePath("Tournament");

    QDir(pathCube).removeRecursively();
    QDir(pathTournament).removeRecursively();

    QDir(mainDirectory).mkpath("Cube");
    QDir(mainDirectory).mkpath("Tournament");


    DialogChoseData dlgTournament(DialogChoseData::Type::fighting_pair);
    if (dlgTournament.exec() != QDialog::Accepted)
        return;

    DialogChoseData dlgCube(DialogChoseData::Type::makeGridsForPointFighting);
    if (dlgCube.exec() != QDialog::Accepted)
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
        QVector<std::pair<int, int>> uidTCs_forTournament;
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
                uidTCs_forTournament << std::make_pair(uidTC, level);
        }
        delete schelder;

        if (!uidTCs_forTournament.isEmpty())
        {
            QStringList errors;
            {
                QSet<int> set;
                for (std::pair<int, int> pair : uidTCs_forTournament)
                {
                    const int uidTC = pair.first;
                    const int level = pair.second;
                    if (!set.contains(uidTC))
                    {
                        set << uidTC;
                        QVector<QVector<DBUtils::NodeOfTournirGrid> > grid =
                                DBUtils::getNodesAsLevelListOfList(uidTC);
                        if (level + 1 != grid.size())
                        {
                            for (const DBUtils::NodeOfTournirGrid& node : grid[level + 1])
                            {
                                if (node.isFight && node.UID <= 0)
                                {
                                    errors
                                            << "Не заполнен круг: " + RenderAreaWidget::getNameOfLevel(node.v)
                                            << "для сетки " +
                                               DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", node.tournamentCategory)
                                            << ""
                                            << "";
                                    break;
                                }
                            }
                        }
                    }
                }
            }

            if (!errors.isEmpty())
            {
                errors.push_front("Проблема на ринге #" + QString::number(ring + 1) + "\n");
                ErrorMessagesDialog dlg(errors, this);
                dlg.exec();
            }
            else
            {
                QAxWidget excel("Excel.Application");
                QAxObject *workbooks = excel.querySubObject("WorkBooks");
                workbooks->dynamicCall("Add");
                QAxObject *workbook = excel.querySubObject("ActiveWorkBook");
                QAxObject *sheets = workbook->querySubObject("WorkSheets");

                FightingPairs::writeListOfPairs(
                            uidTCs_forTournament,
                            sheets,
                            dlgTournament,
                            ring + 1,
                            typeText,
                            typeFlag,
                            ui->comboBoxDay->currentText(),
                            pathTournament,
                            tournamentUID
                            );

                ExcelUtils::saveAsFile(workbook, pathTournament, "Состав пар Ринг " + QString::number(ring + 1));
                workbook->dynamicCall("Close (Boolean)", true);
                excel.dynamicCall("Quit()");
                delete sheets;
                delete workbook;
                delete workbooks;
            }
        }

        if (!uidTCs_forCub.isEmpty())
        {
            QAxWidget excel("Excel.Application");
            QAxObject *workbooks = excel.querySubObject("WorkBooks");
            FightingPairs::writeGridsForPointFighting(
                        pathCube,
                        uidTCs_forCub,
                        workbooks,
                        excel,
                        ring + 1,
                        ui->comboBoxDay->currentText(),
                        dlgCube,
                        typeText,
                        typeFlag
                        );
            delete workbooks;
            excel.dynamicCall("Quit()");
        }
    }
}

void Dialogschedule2::onPushButtonSaveSchelderClicked()
{
    QAxWidget excel("Excel.Application", this);
    excel.setProperty("Visible", true);
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
    workbooks->dynamicCall("Add");
    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");
    QAxObject *sheets = workbook->querySubObject("WorkSheets");
    QAxObject* sheet = ExcelUtils::addNewSheet(sheets);

    QVector<QVector<std::tuple<int, QString, QColor>>> infoForRings;
    int minCntOccurSleep = 0;
    for (int ring = 0; ring < ui->tableWidget->columnCount(); ++ring)
    {
        const QVector<std::tuple<int, QString, QColor>> infoForRing =
                getInfoForRing(tournamentUID, ui->comboBoxDay->currentIndex(), ring, ui->spinBoxDelay->value());
        infoForRings << infoForRing;
        if (!infoForRing.isEmpty())
        {
            int cntOccurRows = std::get<0>(infoForRing[0]);
            QString text = std::get<1>(infoForRing[0]);
            if (text.startsWith("Сон"))
            {
                minCntOccurSleep = minCntOccurSleep == 0? cntOccurRows : qMin(minCntOccurSleep, cntOccurRows);
            }
        }
    }

    for (int ring = 0; ring <= ui->tableWidget->columnCount(); ++ring)
        ExcelUtils::setColumnWidth(sheet, ring + 1, 50);

    const int offset = 5;
    int maxRow = offset + 1;
    for (int ring = 0; ring < ui->tableWidget->columnCount(); ++ring)
    {
        ExcelUtils::setValue  (sheet, offset - 1, ring + 2, "Ринг" " #" + QString::number(ring + 1));
        const QVector<std::tuple<int, QString, QColor>>& infoForRing = infoForRings[ring];
        for (int order = 0, currentRow = offset; order < infoForRing.size(); ++order)
        {
            int cntOccurRows = std::get<0>(infoForRing[order]);
            QString text = std::get<1>(infoForRing[order]);
            //QColor color = std::get<2>(infoForRing[order]);
            if (text.startsWith("Сон"))
            {
                cntOccurRows -= minCntOccurSleep;
                text = "";
            }

            if (cntOccurRows)
            {
                ExcelUtils::uniteRange(sheet, currentRow, ring + 2, currentRow + cntOccurRows - 1, ring + 2);
                ExcelUtils::setValue  (sheet, currentRow, ring + 2, text, 1, 0);
            }

            currentRow += cntOccurRows;
            maxRow = qMax(maxRow, currentRow);
        }
    }
    ExcelUtils::setBorder(sheet, offset - 1, 1, maxRow - 1, ui->tableWidget->columnCount() + 1);

    for (int row = offset; row < maxRow; ++row)
    {
        ExcelUtils::setValue(sheet, row, 1, Utils::getTime(durationOfRow * (row - offset + minCntOccurSleep)),  0);
    }


    for (int ring = 0; ring <= ui->tableWidget->columnCount(); ++ring)
        ExcelUtils::setColumnAutoFit(sheet, ring + 1);

    ExcelUtils::setTournamentName(
                sheet,
                DBUtils::getTournamentNameAsHeadOfDocument(tournamentUID),
                1, 1, 1, ui->tableWidget->columnCount() + 1);
    ExcelUtils::setValue(sheet, 2, 1, "Расписание");
    ExcelUtils::uniteRange(sheet, 2, 1, 2, ui->tableWidget->columnCount() + 1);
    ExcelUtils::setValue(sheet, 3, 1, ui->comboBoxDay->currentText());
    ExcelUtils::uniteRange(sheet, 3, 1, 3, ui->tableWidget->columnCount() + 1);



    delete sheet;
    delete sheets;
    delete workbook;
    delete workbooks;
    //excel.dynamicCall("Quit()");
}




