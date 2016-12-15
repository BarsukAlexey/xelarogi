#include "dialogtournamentgrid.h"
#include "ui_dialogtournamentgrid.h"

DialogTournamentGrid::DialogTournamentGrid(QWidget *parent, QString filter, long long tournamentUID) :
    QDialog(parent),
    ui(new Ui::DialogTournamentGrid),
    tournamentUID(tournamentUID)
    //specialGroup(QVector<int>(4, false))
{
    ui->setupUi(this);
    ui->filterCategoriesLE->setText(filter);
    ui->tableWidgetOrders->setContextMenuPolicy(Qt::CustomContextMenu);
    setWindowFlags(Qt::Window);

    QSettings settings;
    settings.beginGroup("DialogTournamentGrid");
    ui->spinBoxFontSizeOfTC->setValue(settings.value("spinBoxFontSizeOfTC",ui->spinBoxFontSizeOfTC->value()).toInt());
    ui->spinBoxFontSizeOfOrders->setValue(settings.value("spinBoxFontSizeOfOrders",ui->spinBoxFontSizeOfOrders->value()).toInt());
    ui->spinBoxFontSizeOfNodeOfGrid->setValue(settings.value("spinBoxFontSizeOfNodeOfGrid",ui->spinBoxFontSizeOfNodeOfGrid->value()).toInt());
    ui->spinBoxWidth->setValue(settings.value("spinBoxWidth", ui->spinBoxWidth->value()).toInt());
    ui->spinBoxHeight->setValue(settings.value("spinBoxHeight", ui->spinBoxHeight->value()).toInt());
    ui->spinBoxFontSizeOfListOfPairs->setValue(settings.value("spinBoxFontSizeOfListOfPairs", ui->spinBoxFontSizeOfListOfPairs->value()).toInt());

    ui->checkBoxCountry->setChecked(settings.value("checkBoxCountry").toBool());
    ui->checkBoxRegion->setChecked(settings.value("checkBoxRegion").toBool());
    ui->checkBoxCity->setChecked(settings.value("checkBoxCity").toBool());
    ui->checkBoxClub->setChecked(settings.value("checkBoxClub").toBool());

    ui->splitter->restoreState(settings.value("splitterSizes").toByteArray());

    ui->radioButtonSeparateCountry->setChecked(settings.value("radioButtonSeparateCountry").toBool());
    ui->radioButtonSeparateRegion ->setChecked(settings.value("radioButtonSeparateRegion").toBool());
    ui->radioButtonSeparateCity   ->setChecked(settings.value("radioButtonSeparateCity").toBool());
    ui->radioButtonSeparateClub   ->setChecked(settings.value("radioButtonSeparateClub").toBool());


    onSpinBoxFontSizeChangedOfTournamentCategory(ui->spinBoxFontSizeOfTC->value());
    onSpinBoxFontSizeChangedOfListOfOrders(ui->spinBoxFontSizeOfOrders->value());
    ui->pRenderArea->widthChanged(ui->spinBoxWidth->value());
    ui->pRenderArea->heightChanged(ui->spinBoxHeight->value());
    onSpinBoxFontSizeChangedOfListOfPairs(ui->spinBoxFontSizeOfListOfPairs->value());

    fillCategoryCombobox(filter);
    onActivatedCategory();
    onCheckBoxesChangeState();
    ui->pRenderArea->onFontSizeChanged(ui->spinBoxFontSizeOfNodeOfGrid->value());


    connect(ui->buttonGenerate, SIGNAL(clicked(bool)), SLOT(onButtonGenerateGrid()));
    connect(ui->buttonGenerateAll, &QPushButton::clicked, this, &DialogTournamentGrid::onButtonGenerateAll);
    connect(ui->buttonDelete, QPushButton::clicked, this, &DialogTournamentGrid::onDeleteGrid);
    connect(ui->buttonDeleteAll, &QPushButton::clicked, this, &DialogTournamentGrid::deleteAllGrids);
    connect(ui->buttonSave, SIGNAL(clicked()), ui->pRenderArea, SLOT(onSaveInExcel()));
    connect(ui->buttonSaveAll, &QPushButton::clicked, this, &DialogTournamentGrid::saveAllGridsInExcel);

    connect(ui->checkBoxCountry, &QCheckBox::toggled, this, &DialogTournamentGrid::onCheckBoxesChangeState);
    connect(ui->checkBoxRegion, &QCheckBox::toggled, this, &DialogTournamentGrid::onCheckBoxesChangeState);
    connect(ui->checkBoxCity, &QCheckBox::toggled, this, &DialogTournamentGrid::onCheckBoxesChangeState);
    connect(ui->checkBoxClub, &QCheckBox::toggled, this, &DialogTournamentGrid::onCheckBoxesChangeState);

    connect(ui->filterCategoriesLE, &QLineEdit::textChanged, this, &DialogTournamentGrid::fillCategoryCombobox);

    connect(ui->pRenderArea, &RenderAreaWidget::iChangeToutGrid, this, &DialogTournamentGrid::fillListOfPairs);

    connect(ui->qComboBoxSelectCategory, SIGNAL(activated(int)), this, SLOT(onActivatedCategory()));

    connect(ui->tableWidgetOrders, &QTableView::customContextMenuRequested, this, &DialogTournamentGrid::onCustomContextMenuRequested);

    connect(ui->radioButtonAll        , &QRadioButton::clicked, [this] (){fillCategoryCombobox(ui->filterCategoriesLE->text());});
    connect(ui->radioButtonLonly      , &QRadioButton::clicked, [this] (){fillCategoryCombobox(ui->filterCategoriesLE->text());});
    connect(ui->radioButtonInvalid    , &QRadioButton::clicked, [this] (){fillCategoryCombobox(ui->filterCategoriesLE->text());});
    connect(ui->radioButtonInvalidTurn, &QRadioButton::clicked, [this] (){fillCategoryCombobox(ui->filterCategoriesLE->text());});

    connect(ui->spinBoxFontSizeOfTC, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &DialogTournamentGrid::onSpinBoxFontSizeChangedOfTournamentCategory);
    connect(ui->spinBoxFontSizeOfOrders, SIGNAL(valueChanged(int)), this, SLOT(onSpinBoxFontSizeChangedOfListOfOrders(int)));
    connect(ui->spinBoxFontSizeOfNodeOfGrid, SIGNAL(valueChanged(int)), ui->pRenderArea, SLOT(onFontSizeChanged(int)));
    connect(ui->spinBoxHeight, SIGNAL(valueChanged(int)), ui->pRenderArea, SLOT(heightChanged(int)));
    connect(ui->spinBoxWidth, SIGNAL(valueChanged(int)), ui->pRenderArea, SLOT(widthChanged(int)));
    connect(ui->spinBoxFontSizeOfListOfPairs, SIGNAL(valueChanged(int)), this, SLOT(onSpinBoxFontSizeChangedOfListOfPairs(int)));

    connect(ui->tableWidgeRight, SIGNAL(cellClicked(int,int)), SLOT(onCellClickedOntableGrid(int, int)));
}

DialogTournamentGrid::~DialogTournamentGrid()
{
    QSettings settings;

    settings.beginGroup("DialogTournamentGrid");

    settings.setValue("spinBoxFontSizeOfTC",ui->spinBoxFontSizeOfTC->value());
    settings.setValue("spinBoxFontSizeOfOrders",ui->spinBoxFontSizeOfOrders->value());
    settings.setValue("spinBoxFontSizeOfNodeOfGrid",ui->spinBoxFontSizeOfNodeOfGrid->value());
    settings.setValue("spinBoxWidth",ui->spinBoxWidth->value());
    settings.setValue("spinBoxHeight",ui->spinBoxHeight->value());
    settings.setValue("spinBoxFontSizeOfListOfPairs",ui->spinBoxFontSizeOfListOfPairs->value());


    settings.setValue("checkBoxCountry", ui->checkBoxCountry->isChecked());
    settings.setValue("checkBoxRegion", ui->checkBoxRegion->isChecked());
    settings.setValue("checkBoxCity", ui->checkBoxCity->isChecked());
    settings.setValue("checkBoxClub", ui->checkBoxClub->isChecked());

    settings.setValue("splitterSizes", ui->splitter->saveState());

    settings.setValue("radioButtonSeparateCountry", ui->radioButtonSeparateCountry->isChecked());
    settings.setValue("radioButtonSeparateRegion" , ui->radioButtonSeparateRegion ->isChecked());
    settings.setValue("radioButtonSeparateCity"   , ui->radioButtonSeparateCity->isChecked());
    settings.setValue("radioButtonSeparateClub"   , ui->radioButtonSeparateClub->isChecked());

    settings.endGroup();

    delete ui;
}

void DialogTournamentGrid::generatGrid(const long long tournamentUID,
                                       const long long tournamentCaterotyUID,
                                       QVector<long long> bestUID,
                                       const int separate)
{
    //QTime time; time.start();

    {
        // удалим старую сетку
        //DBUtils::dele
        QSqlQuery query("DELETE FROM GRIDS WHERE TOURNAMENT_CATEGORIES_FK = ? ");
        query.addBindValue(tournamentCaterotyUID);
        if (!query.exec())
        {
            qDebug() << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
            return;
        }
    }



    int countOrderUid = 0;

    QVector<int> dayFight;  // dayFight[levelGrid]
    QVector<int> timeFight; // dayFight[levelGrid]
    {
        QSqlQuery queryCOUNT("SELECT count() AS COUNT "
                             "FROM ORDERS "
                             "WHERE TOURNAMENT_CATEGORY_FK = ? "
                             "GROUP BY TOURNAMENT_CATEGORY_FK");
        queryCOUNT.addBindValue(tournamentCaterotyUID);
        if (!queryCOUNT.exec())
        {
            qDebug() << __PRETTY_FUNCTION__ << queryCOUNT.lastError();
            return;
        }
        if (queryCOUNT.next())
            countOrderUid = queryCOUNT.value("COUNT").toInt();
        if (!countOrderUid)
            return;

        const QStringList days = DBUtils::get_DAYS_FROM_TOURNAMENTS(tournamentUID);
        int countTurns = 0;
        for (int fight = 1; ; fight *= 2)
        {
            if (countOrderUid < 2 * fight)
            {
                if (0 < countOrderUid - fight) ++countTurns;
                break;
            }
            else
                ++countTurns;
        }

        if (3 * days.size() < countTurns)
        {
//            QMessageBox::warning(0, QString("Проблема"),
//                                 QString("Для сетки \"%1\" необходимо %2 круга (кругов), "
//                                         "но имеется только %3 день (дня, дней)")
//                                 .arg(DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", tournamentCaterotyUID))
//                                 .arg(countTurns)
//                                 .arg(days.size()));
            for (int day = 0, turn = 0; turn < countTurns; ++day)
            {
                for (int time = 0; time < 3 && turn < countTurns; ++time, ++turn)
                {
                    dayFight .push_front(day);
                    timeFight.push_front(time);
                }
            }
        }
        else
        {
            const int onOneDay = countTurns / days.size();
            int rest = countTurns % days.size();
            for (int d = qMax(0, days.size() - countTurns); d < days.size(); ++d)
            {
                for (int f = 0; f < onOneDay + (0 < rest? 1 : 0); ++f)
                {
                    if (countTurns)
                    {
                        dayFight .push_front(d);
                        timeFight.push_front(f);
                        --countTurns;
                    }
                }
                if (0 < rest) --rest;
            }
        }
    }


    SuperStruct super(separate);
    {
        QSqlQuery query("SELECT * "
                        "FROM ORDERS "
                        "WHERE TOURNAMENT_CATEGORY_FK = ? "
                        "ORDER BY SECOND_NAME, FIRST_NAME");
        query.addBindValue(tournamentCaterotyUID);
        if (!query.exec())
        {
            qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
            return;
        }
        while (query.next())
        {
            long long orderUID = query.value("UID").toLongLong();
            if (!bestUID.contains(orderUID))
                super.add(orderUID);
        }
    }



    QVector<bool> isLeaf(2);
    {
        QQueue<int> queue;
        int cnt = 1;
        isLeaf[1] = true;
        queue.enqueue(1);
        while (cnt < countOrderUid)
        {
            int v = queue.dequeue();
            isLeaf[v] = false;
            isLeaf.push_back(true); // то же самое что и isLeaf[2 * v    ] = true
            isLeaf.push_back(true); // то же самое что и isLeaf[2 * v + 1] = true
            queue.enqueue(2 * v);
            queue.enqueue(2 * v + 1);
            cnt = cnt - 1 + 2;
        }
    }
    const int maxVertex = isLeaf.size() - 1;


    QSqlDatabase::database().transaction();

    for (int v = maxVertex;  1 <= v; --v)
    {
        if (isLeaf[v]) continue;

        QSqlQuery query("INSERT INTO GRIDS VALUES (?,?,?,   ?,?,   ?,?)");
        query.addBindValue(tournamentCaterotyUID);
        query.addBindValue(v);
        query.addBindValue(1);

        query.addBindValue(QVariant());
        query.addBindValue(QVariant());

        query.addBindValue(dayFight [Utils::log2(v)]);
        query.addBindValue(timeFight[Utils::log2(v)]);
        if (!query.exec())
            qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
    }


    QVector<bool> isUsedLeaf(maxVertex + 1);
    QVector<long long> orderUID(maxVertex + 1);
    //QVector<int> vertexOfBest;
    if (!bestUID.isEmpty())
    {
        QVector<int> sizeTree(maxVertex + 1);
        for (int v = maxVertex; 1 <= v; --v)
        {
            if (isLeaf[v])
                sizeTree[v] = 1;
            else
                sizeTree[v] = sizeTree[2 * v + 1] + sizeTree[2 * v];
        }

        QQueue<std::pair<int, QVector<long long>>> queue;
        queue.enqueue(std::make_pair(1, bestUID));
        while (!queue.isEmpty())
        {
            int v = queue.head().first;
            QVector<long long> curBestUID = queue.head().second;
            queue.dequeue();

            if (isLeaf[v])
            {
                assert(curBestUID.size() <= 1);

                if (!curBestUID.isEmpty())
                {
                    isUsedLeaf[v] = true;
                    orderUID[v] = curBestUID[0];
                    DBUtils::insertLeafOfGrid(tournamentCaterotyUID, v, curBestUID[0]);
                }
            }
            else
            {
                QVector<long long> left;
                QVector<long long> right;

                for (int i = 0, iter = 0; i < curBestUID.size() && iter < sizeTree[2 * v + 1]; i += 2, ++iter)
                {
                    left << curBestUID[i];
                }
                for (int orderUID : curBestUID)
                    if (!left.contains(orderUID))
                        right << orderUID;

                queue.enqueue(std::make_pair(2 * v + 1, left ));
                queue.enqueue(std::make_pair(2 * v    , right));
            }
        }

//        QVector<QString> pref;
//        if (bestUID.size() == 1) pref << "1";
//        if (bestUID.size() == 2) pref << "11" << "10";
//        if (bestUID.size() == 3) pref << "11" << "101" << "100";
//        if (bestUID.size() == 4) pref << "111" << "101" << "110" << "100";
//        for (int i = 0; i < bestUID.size(); ++i)
//        {
//            int v = pref[i].toInt(0, 2);
//            while (!isLeaf[v]) v = 2 * v + 1;
//            vertexOfBest << v;

//            isUsedLeaf[v] = true;
//            orderUID[v] = bestUID[i];

//            DBUtils::insertLeafOfGrid(tournamentCaterotyUID, v, bestUID[i]);
//        }
    }

    // находим пару для тех бойцов, для которые без пары
    for (int v = 1; v <= maxVertex; ++v)
    {
        int anotherVetex = v ^ 1;
        if (!(1 <= anotherVetex && anotherVetex <= maxVertex)) continue;
        if (isLeaf[v] && !isUsedLeaf[v] && isLeaf[anotherVetex] && isUsedLeaf[anotherVetex])
        {
            orderUID[v] = super.pollOrderUid(orderUID[anotherVetex]);
            DBUtils::insertLeafOfGrid(tournamentCaterotyUID, v, orderUID[v]);
            isUsedLeaf[v] = true;
        }
    }

    QVector<std::pair<int, int> > freePairsOfLeafs;
    for (int v = 1; v <= maxVertex; ++v)
    {
        int a = 2 * v + 1;
        int b = 2 * v;
        if (!isLeaf[v] && isLeaf[a] && isLeaf[b] && !isUsedLeaf[a] && !isUsedLeaf[b])
        {
            freePairsOfLeafs << (rand() & 1? std::make_pair(a, b) : std::make_pair(b, a));
        }
    }
    std::random_shuffle(freePairsOfLeafs.begin(), freePairsOfLeafs.end());


//    qDebug() << super.getAllOrderUIDs();
//    super.updataRndAndLocation();
//    qDebug() << super.getAllOrderUIDs();
//    return;

    // просто берем пары
    while (!freePairsOfLeafs.isEmpty())
    {
        const std::pair<int, int> pair = freePairsOfLeafs.takeLast();
//        qDebug() << pair << super.getAllOrderUIDs();

        int orderUID0 = -1;
        int orderUID1 = -1;
        super.pollTwoOrders(orderUID0, orderUID1);
//        qDebug() << "\t" << orderUID0 << orderUID1;

        DBUtils::insertLeafOfGrid(tournamentCaterotyUID, pair.first , orderUID0);
        DBUtils::insertLeafOfGrid(tournamentCaterotyUID, pair.second, orderUID1);

        isUsedLeaf[pair.first ] = true;
        isUsedLeaf[pair.second] = true;
        orderUID  [pair.first ] = orderUID0;
        orderUID  [pair.second] = orderUID1;
    }


    // одна такая вершина, которая "на стыке уровней"
    for (int v = 1; v <= maxVertex; ++v)
    {
        if (isLeaf[v] && !isUsedLeaf[v])
        {
            int orderUID = super.pollLastOrder();

            DBUtils::insertLeafOfGrid(tournamentCaterotyUID, v, orderUID);
            break;
        }
    }

    assert (super.getAllOrderUIDs().isEmpty());
    QSqlDatabase::database().commit();

    //qDebug() << "time.elapsed():" << time.elapsed();
}

void DialogTournamentGrid::deleteGrid(const long long uidTC)
{
    // проверяем есть ли турнирная сетка, если есть, то задаём вопрос
    QSqlQuery query("SELECT * FROM GRIDS WHERE TOURNAMENT_CATEGORIES_FK = ? ");
    query.addBindValue(uidTC);
    if (!query.exec())
        qDebug() << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();

    if (!query.next())
    {
        return ;
    }
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(0, "",
                                  "При удалении сетки, она удаляется из расписания.\n"
                                  "Удалить сетку " +
                                  DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", uidTC) +
                                  "?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No)
        return ;

    DBUtils::deleteGrid(uidTC);
}

QString DialogTournamentGrid::getLocation(const int orderUID)
{
    return DBUtils::get(getLocationData(), orderUID);
}

QVector<std::pair<DBUtils::TypeField, QString> > DialogTournamentGrid::getLocationData()
{
    QVector<std::pair<DBUtils::TypeField, QString>> res;

    if (ui->checkBoxCountry->isChecked())
    {
        if (!res.isEmpty()) res += std::make_pair(DBUtils::TypeField::PlainText, " / ");
        res += std::make_pair(DBUtils::TypeField::country, "");
    }
    if (ui->checkBoxRegion->isChecked())
    {
        if (!res.isEmpty()) res += std::make_pair(DBUtils::TypeField::PlainText, " / ");
        res += std::make_pair(DBUtils::TypeField::region, "");
    }
    if (ui->checkBoxCity->isChecked())
    {
        if (!res.isEmpty()) res += std::make_pair(DBUtils::TypeField::PlainText, " / ");
        res += std::make_pair(DBUtils::TypeField::city, "");
    }
    if (ui->checkBoxClub->isChecked())
    {
        if (!res.isEmpty()) res += std::make_pair(DBUtils::TypeField::PlainText, " / ");
        res += std::make_pair(DBUtils::TypeField::club, "");
    }
    return res;
}

void DialogTournamentGrid::fillListOfOrders()
{
    ui->tableWidgetOrders->setRowCount(0);
    QSqlQuery query("SELECT * FROM ORDERS WHERE TOURNAMENT_CATEGORY_FK = ? ORDER BY SECOND_NAME, FIRST_NAME");
    query.addBindValue(ui->qComboBoxSelectCategory->currentData(Qt::UserRole).toInt());
    query.exec();
    while (query.next())
    {
        int orderUID = query.value("UID").toInt();
        QString name = query.value("SECOND_NAME").toString() + " " + query.value("FIRST_NAME").toString();
        QString location = getLocation(orderUID);

        ui->tableWidgetOrders->setRowCount(ui->tableWidgetOrders->rowCount() + 1);
        QTableWidgetItem *item;

        item = new QTableWidgetItem(name);
        item->setData(Qt::UserRole, orderUID);

        int row = ui->tableWidgetOrders->rowCount() - 1;

        ui->tableWidgetOrders->setItem(row, 0, item);

        ui->tableWidgetOrders->setItem(row, 1, new QTableWidgetItem(location));

        QSpinBox *spinBox = new QSpinBox;
        spinBox->setRange(0, 100500);
        spinBox->setSpecialValueText("Нет");
        spinBox->setValue(DBUtils::get("PRIORITY", "ORDERS", orderUID).toInt());
        ui->tableWidgetOrders->setCellWidget(row, 2, spinBox);
        connect(spinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                [orderUID](const int prioriry){
            //QTime time; time.start();
            DBUtils::set("PRIORITY", "ORDERS", orderUID, prioriry);
            //qDebug() << "time: " << time.elapsed() << orderUID;
        });

        ui->tableWidgetOrders->setItem(row, 3, new QTableWidgetItem(DBUtils::getField("NAME", "SPORT_CATEGORIES", query.value("SPORT_CATEGORY_FK").toString())));
    }
    ui->tableWidgetOrders->resizeColumnsToContents();
    ui->tableWidgetOrders->resizeRowsToContents();
}

void DialogTournamentGrid::onActivatedCategory()
{
    const int id = ui->qComboBoxSelectCategory->currentIndex();
    if (!(0 <= id && id < ui->qComboBoxSelectCategory->count()))
    {
        ui->tableWidgetOrders->setRowCount(0);
        ui->tableWidgeRight->setRowCount(0);
        ui->pRenderArea->tournamentCategoryIsChanged(-1);
        return;
    }

    ui->pRenderArea->tournamentCategoryIsChanged(ui->qComboBoxSelectCategory->currentData(Qt::UserRole).toInt());

    fillListOfOrders();
    fillListOfPairs();
}

void DialogTournamentGrid::onButtonGenerateGrid()
{
    {
        // проверяем есть ли турнирная сетка, если есть, то задаём вопрос
        QSqlQuery query("SELECT * FROM GRIDS WHERE TOURNAMENT_CATEGORIES_FK = ? ");
        query.addBindValue(ui->qComboBoxSelectCategory->currentData(Qt::UserRole).toInt());
        if (query.exec())
        {
            if (query.next())
            {
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(
                            this, "",
                            "Новая генерация сетки приведет к потере старой сетки,\n"
                            "а также к удалению данной сетки из расписания.\n"
                            "Продолжить?", QMessageBox::Yes | QMessageBox::No);
                if (reply == QMessageBox::No)
                    return;
            }
        }
        else
        {
            qDebug() << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
            return;
        }
    }
    /* */

    selectedRowOfRableGrid = -1;
    selectedColumnOfRableGrid = -1;
    ui->pRenderArea->clearSelection();



    QVector<std::pair<int, long long>> bestFighters;
    for (int row = 0; row < ui->tableWidgetOrders->rowCount(); ++row)
    {
        long long orderUID = ui->tableWidgetOrders->item(row, 0)->data(Qt::UserRole).toLongLong();
        QSpinBox* spinBox = qobject_cast<QSpinBox*> (ui->tableWidgetOrders->cellWidget(row, 2));
        int priority = spinBox->value();
        if (priority != 0)
        {
            bestFighters << std::make_pair(priority, orderUID);
        }
    }
    std::random_shuffle(bestFighters.begin(), bestFighters.end());
    qSort(bestFighters.begin(), bestFighters.end(), [](const std::pair<int, long long> a, const std::pair<int, long long> b){
        return a.first < b.first;
    });
    QVector<long long> bestUID;
    for (std::pair<int, long long> f : bestFighters)
        bestUID << f.second;

    generatGrid(tournamentUID, ui->qComboBoxSelectCategory->currentData(Qt::UserRole).toInt(), bestUID,
                getLocationForSeparate());

    ui->pRenderArea->tournamentCategoryIsChanged(ui->qComboBoxSelectCategory->currentData(Qt::UserRole).toInt());
    fillListOfPairs();
}

void DialogTournamentGrid::saveAllGridsInExcel()
{
    DialogChoseData dlg(DialogChoseData::Type::grids);
    if (dlg.exec() != QDialog::Accepted)
        return;

    QString directoryPath = QFileDialog::getExistingDirectory(this, tr("Выберите папку"), NULL, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (directoryPath.isNull()) return;



    QTime timer;
    timer.start();

    QVector<long long> UID_TCs = DBUtils::getTournamentCategoryUIDs(tournamentUID);

    QProgressDialog progress(this);
    progress.setWindowModality(Qt::WindowModal);
    progress.setMinimumDuration(0);
    progress.setMaximum(UID_TCs.size());
    progress.setValue(0);

    QAxWidget excel("Excel.Application");
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
    int cntNotEmpty = 0;
    for (const long long tcUID : UID_TCs)
    {
        if (DBUtils::getNodes(tcUID).isEmpty())
        {
            progress.setValue(progress.value() + 1);
            if (progress.wasCanceled())
                break;
        }
        else
        {
            ++cntNotEmpty;
            progress.setLabelText("Save: " + DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", tcUID));

            //QTime timer1;
            //timer1.start();
            workbooks->dynamicCall("Add");
            QAxObject *workbook = excel.querySubObject("ActiveWorkBook");
            //long long time11 = timer1.elapsed();

            //QTime timer2;
            //timer2.start();
            RenderAreaWidget::printTableGridInExcel(workbook, dlg, tcUID, false, directoryPath, QVector<int>(), "", "");
            //int time222 = timer2.elapsed();

            progress.setValue(progress.value() + 1);
            if (progress.wasCanceled())
                break;


            //QTime timer3;
            //timer3.start();
            workbook->dynamicCall("Close()");
            delete workbook;
            //long long time3 = timer3.elapsed();
            //qDebug() << "timer"
            //         << QString("%1").arg(DBUtils::getNodes(tcUID).size(), 2, 10)
            //         << QString("%1").arg(time11 , 6, 10)
            //         << QString("%1").arg(time222, 6, 10)
            //         << QString("%1").arg(time3  , 6, 10);
        }
    }
    delete workbooks;
    excel.dynamicCall("Quit()");

    //int localElapsed = timer.elapsed();
    //qDebug() << "All" << cntNotEmpty << "grids:" << localElapsed / 1000 / 60 << " m" << localElapsed / 1000 % 60 << " s";
}

void DialogTournamentGrid::deleteAllGrids()
{
    for (int i = 0; i < 4; ++i)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(0, "",
                                      QString() +
                                      "При удалении сетки, она удаляется из расписания.\n"
                                      "Удалить ВСЕ сетки?\n" +
                                      (i == 0? "" : i == 1? "Вы уверены?" : i == 2? "Точно?" : "Удаляю..."),
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No)
            return ;
    }
    QProgressDialog progress("", "Cancel", 0, ui->qComboBoxSelectCategory->count(), this);
    progress.setWindowModality(Qt::ApplicationModal);
    progress.setMinimumDuration(0);
    for (int i = 0; i < ui->qComboBoxSelectCategory->count(); ++i)
    {
        if (progress.wasCanceled())
            break;
        progress.setValue(i);
        QApplication::processEvents();
        DBUtils::deleteGrid(ui->qComboBoxSelectCategory->itemData(i, Qt::UserRole).toInt());
    }
    ui->pRenderArea->tournamentCategoryIsChanged(ui->qComboBoxSelectCategory->currentData(Qt::UserRole).toInt());
    fillListOfPairs();
}

void DialogTournamentGrid::onDeleteGrid()
{
    deleteGrid(ui->qComboBoxSelectCategory->currentData(Qt::UserRole).toInt());
    ui->pRenderArea->tournamentCategoryIsChanged(ui->qComboBoxSelectCategory->currentData(Qt::UserRole).toInt());
    fillListOfPairs();
}

void DialogTournamentGrid::fillCategoryCombobox(QString filterStr)
{
    //QTime time;
    //time.start();

    ui->qComboBoxSelectCategory->clear();

    QStringList filters = filterStr.split(" ", QString::SkipEmptyParts);
    QString whereStatement("");
    for (int i = 0; i < filters.size(); ++i)
    {
        whereStatement += " AND NAME LIKE '%' || ? || '%' ";
    }

    QSqlQuery query;
    query.prepare(
                "SELECT * "
                "FROM TOURNAMENT_CATEGORIES "
                "WHERE TOURNAMENT_FK = ? " + whereStatement +
                "ORDER BY TYPE_FK, AGE_FROM, AGE_TILL, SEX_FK, WEIGHT_FROM, WEIGHT_TILL ");
    if (query.lastError().isValid())
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
        return;
    }
    query.addBindValue(tournamentUID);
    for (const QString& filter: filters)
    {
        query.addBindValue(filter);
    }
    query.exec();
    if (query.lastError().isValid())
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
        return;
    }
    else
    {
        while (query.next())
        {
            int categoryUID = query.value("UID").toInt();
            QString categoryName = query.value("NAME").toString();

            QVector<int> mansFromOrder = DBUtils::getOrderUIDsInTournamentCategory(categoryUID);
            qSort(mansFromOrder);

            QVector<int> mansFromGrig;
            bool haveSomePeopleInGridOrInOrder = 0 < mansFromOrder.size();
            for(const DBUtils::NodeOfTournirGrid& it : DBUtils::getNodes(categoryUID))
            {
                haveSomePeopleInGridOrInOrder = true;
                if (!it.isFight)
                    mansFromGrig << it.UID;
            }
            qSort(mansFromGrig);


            bool havePartiallyFilledLevel = false;
            {
                QVector<QVector<DBUtils::NodeOfTournirGrid> > grid =
                        DBUtils::getNodesAsLevelListOfList(categoryUID);
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
                            if (0 < node.UID &&
                                node.UID != grid[i + 1][2 * j].UID &&
                                node.UID != grid[i + 1][2 * j + 1].UID
                                )
                            {
                                havePartiallyFilledLevel = true;
                            }
                        }
                    }
                    if (countFilled != 0 && countFilled != countOfFights)
                    {
                        havePartiallyFilledLevel = true;
                        break;
                    }
                }
            }

            //qDebug() << ui->radioButtonInvalid->isChecked() << mansFromOrder << mansFromGrig;

            if (
                (ui->radioButtonAll->isChecked() && haveSomePeopleInGridOrInOrder) ||
                (ui->radioButtonLonly->isChecked() && mansFromOrder.size() == 1) ||
                (ui->radioButtonInvalid->isChecked() && mansFromOrder != mansFromGrig) ||
                (ui->radioButtonInvalidTurn->isChecked() && havePartiallyFilledLevel)
                )
            {
                ui->qComboBoxSelectCategory->addItem(categoryName, categoryUID);
            }
        }
    }

    onActivatedCategory();

    //qDebug() << __LINE__ << __PRETTY_FUNCTION__ << "Time:" << time.elapsed();
}

void DialogTournamentGrid::onCellClickedOntableGrid(int row, int column)
{
    if (ui->tableWidgeRight->item(row, column)->data(Qt::UserRole).toInt() <= 0)
    {
        ui->tableWidgeRight->clearSelection();
        ui->tableWidgeRight->clearFocus();
        selectedRowOfRableGrid = -1;
        selectedColumnOfRableGrid = -1;
        return;
    }

    if (selectedRowOfRableGrid == -1 || selectedColumnOfRableGrid == -1)
    {
        selectedRowOfRableGrid = row;
        selectedColumnOfRableGrid = column;
        QModelIndex i = ui->tableWidgeRight->model()->index(row, column ^ 1);
        ui->tableWidgeRight->selectionModel()->select(i, QItemSelectionModel::Select);
    }
    else
    {
        int vertexA = ui->tableWidgeRight->item(row, column)->data(Qt::UserRole).toInt();
        int vertexB = ui->tableWidgeRight->item(selectedRowOfRableGrid, selectedColumnOfRableGrid)->data(Qt::UserRole).toInt();
        //qDebug() << vertexA << vertexB;
        if (0 < vertexA && 0 < vertexB)
        {
            DBUtils::swapNodesOfGrid(ui->qComboBoxSelectCategory->currentData(Qt::UserRole).toInt(), vertexA, vertexB);
            //qDebug() << "DONE!";
        }
        fillListOfPairs();

        ui->tableWidgeRight->clearSelection();
        ui->tableWidgeRight->clearFocus();
        selectedRowOfRableGrid = -1;
        selectedColumnOfRableGrid = -1;
    }
}

void DialogTournamentGrid::onButtonGenerateAll()
{
    QProgressDialog progress(this);
    progress.setWindowModality(Qt::WindowModal);
    progress.setMinimumDuration(500);
    {
        QSqlQuery query("SELECT COUNT(*) AS CNT FROM TOURNAMENT_CATEGORIES WHERE TOURNAMENT_FK = ? ");
        query.addBindValue(tournamentUID);
        if (query.exec() && query.next())
            progress.setMaximum(query.value("CNT").toInt());
        else
            progress.setMaximum(0);
    }

    QSqlQuery query("SELECT * FROM TOURNAMENT_CATEGORIES WHERE TOURNAMENT_FK = ? ORDER BY SEX_FK, TYPE_FK, AGE_FROM, AGE_TILL, WEIGHT_FROM, WEIGHT_TILL ");
    query.bindValue(0, tournamentUID);
    if (!query.exec())
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
        return;
    }
    while (query.next())
    {
        qlonglong tcUID = query.value("UID").toLongLong();
        QVector<long long> bestUID; // TODO доделать это получить с БД

        //        QSqlQuery queryOrder("SELECT * FROM ORDERS WHERE TOURNAMENT_CATEGORIES = ? ");
        //        queryOrder.bindValue(0, tcUID);
        //        queryOrder.exec();
        //        while (queryOrder.next()) bestUID << queryOrder.value("UID").toLongLong();
        //        std::random_shuffle(bestUID.begin(), bestUID.end());
        //        bestUID.resize(qMin(bestUID.size(), sz));

        if (DBUtils::getNodes(tcUID).isEmpty())
            generatGrid(tournamentUID, tcUID, bestUID, getLocationForSeparate());

        progress.setValue(progress.value() + 1);
        if (progress.wasCanceled())
            break;

    }

    ui->pRenderArea->tournamentCategoryIsChanged(ui->qComboBoxSelectCategory->currentData(Qt::UserRole).toInt());
    fillListOfPairs();
}

void DialogTournamentGrid::onCustomContextMenuRequested(const QPoint& pos)
{
    QMenu contextMenu;
    QModelIndex index = ui->tableWidgetOrders->indexAt(pos);
    qDebug() << "index: " << index;

    QAction* restrictAction = new QAction("Заявки спортсмена...", &contextMenu);
    if (index.isValid())
    {
        contextMenu.addAction(restrictAction);
        connect(restrictAction, &QAction::triggered, [this, &index] ()
        {
            int orderUID = index.model()->index(index.row(), 0).data(Qt::UserRole).toInt();
            //long long orderUID = index.data(Qt::UserRole).toLongLong();
            qDebug() << orderUID
                     << DBUtils::getField("SECOND_NAME", "ORDERS", orderUID)
                     << DBUtils::getField("FIRST_NAME", "ORDERS", orderUID);
            CreateTournamentOrdersDialog dlg(this->tournamentUID, this,
                                         DBUtils::getField("SECOND_NAME", "ORDERS", orderUID),
                                         DBUtils::getField("FIRST_NAME", "ORDERS", orderUID)
                                         );
            dlg.showMaximized(); // НИХУЯ не работает TODO
            dlg.exec();
            onActivatedCategory();
        });
    }

    QAction delAction("Все заявки...", &contextMenu);
    contextMenu.addAction(&delAction);
    connect(&delAction, &QAction::triggered, [this] ()
    {
        CreateTournamentOrdersDialog(this->tournamentUID, this).exec();
        onActivatedCategory();
    });

    contextMenu.exec(ui->tableWidgetOrders->viewport()->mapToGlobal(pos));
    delete restrictAction;
}

void DialogTournamentGrid::fillListOfPairs()
{
    selectedRowOfRableGrid = -1;
    selectedColumnOfRableGrid = -1;
    QVector<DBUtils::NodeOfTournirGrid> nodes =
            DBUtils::getNodes(ui->qComboBoxSelectCategory->currentData(Qt::UserRole).toInt());
    {
        QVector<DBUtils::NodeOfTournirGrid> leafs;
        for (DBUtils::NodeOfTournirGrid node : nodes)
            if (!node.isFight)
            {
                leafs << node;
            }
        nodes = leafs;
    }
    std::random_shuffle(nodes.begin(), nodes.end());
    std::sort(nodes.begin(), nodes.end(),
              [this] (const DBUtils::NodeOfTournirGrid& lhs, const DBUtils::NodeOfTournirGrid& rhs) {
        QString a = QString::number(lhs.v, 2);
        QString b = QString::number(rhs.v, 2);
        if (a.size() != b.size()) return a.size() < b.size();
        return lhs.v > rhs.v;
    });

    for (int i = 0; i < ui->tableWidgeRight->rowCount(); ++i)
    {
        QAbstractItemDelegate* delegate = ui->tableWidgeRight->itemDelegateForRow(i);
        if (delegate)
        {
            ui->tableWidgeRight->setItemDelegateForRow(i, 0);
            delete delegate;
        }
    }

    ui->tableWidgeRight->setRowCount(0);
    bool findCenter = false;
    for (const DBUtils::NodeOfTournirGrid& node : nodes)
    {
        if ((node.v & 1) == 0) continue;

        ui->tableWidgeRight->setRowCount(ui->tableWidgeRight->rowCount() + 1);

        QTableWidgetItem *item;

        item = new QTableWidgetItem(DBUtils::getSecondNameAndFirstName(node.UID));
        item->setData(Qt::UserRole, node.v);
        ui->tableWidgeRight->setItem(ui->tableWidgeRight->rowCount() - 1, 0, item);

        item = new QTableWidgetItem(getLocation(node.UID));
        item->setData(Qt::UserRole, node.v);
        ui->tableWidgeRight->setItem(ui->tableWidgeRight->rowCount() - 1, 1, item);

        item = new QTableWidgetItem();
        item->setData(Qt::UserRole, 0);
        ui->tableWidgeRight->setItem(ui->tableWidgeRight->rowCount() - 1, 2, item);
        item = new QTableWidgetItem();
        item->setData(Qt::UserRole, 0);
        ui->tableWidgeRight->setItem(ui->tableWidgeRight->rowCount() - 1, 3, item);
        for (const DBUtils::NodeOfTournirGrid& node2 : nodes)
        {
            if (node2.v != (node.v ^ 1)) continue;
            item = new QTableWidgetItem(DBUtils::getSecondNameAndFirstName(node2.UID));
            item->setData(Qt::UserRole, node2.v);
            ui->tableWidgeRight->setItem(ui->tableWidgeRight->rowCount() - 1, 2, item);
            item = new QTableWidgetItem(getLocation(node2.UID));
            item->setData(Qt::UserRole, node2.v);
            ui->tableWidgeRight->setItem(ui->tableWidgeRight->rowCount() - 1, 3, item);
            break;
        }

        item = new QTableWidgetItem(RenderAreaWidget::getNameOfLevel(node.v / 2));
        ui->tableWidgeRight->setItem(ui->tableWidgeRight->rowCount() - 1, 4, item);

        if(!findCenter && QString::number(node.v, 2).startsWith("10"))
        {
            findCenter = true;
            ui->tableWidgeRight->setItemDelegateForRow(ui->tableWidgeRight->rowCount() - 1, new DrawBorderDelegate(this));
        }
    }
    ui->tableWidgeRight->resizeColumnsToContents();
    ui->tableWidgeRight->resizeRowsToContents();
    ui->tableWidgeRight->clearSelection();
    ui->tableWidgeRight->clearFocus();
}

int DialogTournamentGrid::getLocationForSeparate()
{
    if (ui->radioButtonSeparateCountry->isChecked()) return 0;
    if (ui->radioButtonSeparateRegion ->isChecked()) return 1;
    if (ui->radioButtonSeparateCity   ->isChecked()) return 2;
    if (ui->radioButtonSeparateClub   ->isChecked()) return 3;
    return -1;
}

void DialogTournamentGrid::onSpinBoxFontSizeChangedOfListOfOrders(int sizeFont)
{
    QFont font = ui->tableWidgetOrders->font();
    font.setPointSize(sizeFont);
    ui->tableWidgetOrders->setFont(font);
    ui->tableWidgetOrders->resizeColumnsToContents();
    ui->tableWidgetOrders->resizeRowsToContents();
}

//void DialogTournamentGrid::onSpinBoxFontSizeChangedOfNodeOfGrid(const int sizeFont)
//{
//    QFont localFont = ui->pRenderArea->font();
//    localFont.setPointSize(sizeFont);
//    ui->pRenderArea->setFont(localFont);
//    ui->pRenderArea->repaint();
//}

void DialogTournamentGrid::onSpinBoxFontSizeChangedOfListOfPairs(int sizeFont)
{
    QFont font = ui->tableWidgeRight->font();
    font.setPointSize(sizeFont);
    ui->tableWidgeRight->setFont(font);
    ui->tableWidgeRight->resizeColumnsToContents();
    ui->tableWidgeRight->resizeRowsToContents();
}

void DialogTournamentGrid::onSpinBoxFontSizeChangedOfTournamentCategory(const int sizeFont)
{
    QFont font = ui->qComboBoxSelectCategory->font();
    font.setPointSize(sizeFont);
    ui->qComboBoxSelectCategory->setFont(font);
}

void DialogTournamentGrid::onCheckBoxesChangeState()
{
    fillListOfOrders();
    fillListOfPairs();
    ui->pRenderArea->onLocationDataIsChanged(getLocationData());
}






void DialogTournamentGrid::on_pushButtonShowHide_clicked(bool checked)
{
    //qDebug() << "checked:" << checked;
    ui->widgetSettings->setVisible(!checked);
}
