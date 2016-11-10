#include "dialogtournamentgrid.h"
#include "ui_dialogtournamentgrid.h"

DialogTournamentGrid::DialogTournamentGrid(QWidget *parent, QString filter, long long tournamentUID) :
    QDialog(parent),
    ui(new Ui::DialogTournamentGrid),
    tournamentUID(tournamentUID),
    specialGroup(QVector<int>(4, false))
{
    ui->setupUi(this);
    ui->filterCategoriesLE->setText(filter);
    ui->qTableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    setWindowFlags(Qt::Window);

    QSettings settings;
    ui->spinBoxFontSizeOfTC->setValue(settings.value("spinBoxFontSizeOfTC",ui->spinBoxFontSizeOfTC->value()).toInt());
    ui->spinBoxFontSizeOfOrders->setValue(settings.value("spinBoxFontSizeOfOrders",ui->spinBoxFontSizeOfOrders->value()).toInt());
    ui->spinBoxFontSizeOfNodeOfGrid->setValue(settings.value("spinBoxFontSizeOfNodeOfGrid",ui->spinBoxFontSizeOfNodeOfGrid->value()).toInt());
    ui->spinBoxWidth->setValue(settings.value("spinBoxWidth", ui->spinBoxWidth->value()).toInt());
    ui->spinBoxHeight->setValue(settings.value("spinBoxHeight", ui->spinBoxHeight->value()).toInt());
    ui->spinBoxFontSizeOfListOfPairs->setValue(settings.value("spinBoxFontSizeOfListOfPairs", ui->spinBoxFontSizeOfListOfPairs->value()).toInt());

    ui->checkBoxCountry->setChecked(settings.value("DialogTournamentGrid/checkBoxCountry").toBool());
    ui->checkBoxRegion->setChecked(settings.value("DialogTournamentGrid/checkBoxRegion").toBool());
    ui->checkBoxCity->setChecked(settings.value("DialogTournamentGrid/checkBoxCity").toBool());
    ui->checkBoxClub->setChecked(settings.value("DialogTournamentGrid/checkBoxClub").toBool());

    ui->splitter->restoreState(settings.value("DialogTournamentGrid/splitterSizes").toByteArray());


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

    connect(ui->qTableWidget, &QTableView::customContextMenuRequested, this, &DialogTournamentGrid::onCustomContextMenuRequested);
    connect(ui->qTableWidget, SIGNAL(cellClicked(int,int)), SLOT(onCellCLickedForChangePrioritet(int, int)));

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

    settings.setValue("spinBoxFontSizeOfTC",ui->spinBoxFontSizeOfTC->value());
    settings.setValue("spinBoxFontSizeOfOrders",ui->spinBoxFontSizeOfOrders->value());
    settings.setValue("spinBoxFontSizeOfNodeOfGrid",ui->spinBoxFontSizeOfNodeOfGrid->value());
    settings.setValue("spinBoxWidth",ui->spinBoxWidth->value());
    settings.setValue("spinBoxHeight",ui->spinBoxHeight->value());
    settings.setValue("spinBoxFontSizeOfListOfPairs",ui->spinBoxFontSizeOfListOfPairs->value());


    settings.setValue("DialogTournamentGrid/checkBoxCountry", ui->checkBoxCountry->isChecked());
    settings.setValue("DialogTournamentGrid/checkBoxRegion", ui->checkBoxRegion->isChecked());
    settings.setValue("DialogTournamentGrid/checkBoxCity", ui->checkBoxCity->isChecked());
    settings.setValue("DialogTournamentGrid/checkBoxClub", ui->checkBoxClub->isChecked());

    settings.setValue("DialogTournamentGrid/splitterSizes", ui->splitter->saveState());

    delete ui;
}

void DialogTournamentGrid::generatGrid(const long long tournamentUID, const long long tournamentCaterotyUID, QVector<long long> bestUID)
{
    {
        // удалим старую сетку
        QSqlQuery query("DELETE FROM GRID WHERE TOURNAMENT_CATEGORIES_FK = ? ");
        query.addBindValue(tournamentCaterotyUID);
        if (!query.exec())
        {
            qDebug() << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
            return;
        }
    }

    QVector<int> dayFight; // dayFight[levelGrid]
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
        int count = 0;
        if (queryCOUNT.next())
            count = queryCOUNT.value("COUNT").toInt();

        const QStringList days = DBUtils::get_DAYS_FROM_TOURNAMENTS(tournamentUID);
        int countTurns = 0;
        for (int fight = 1; ; fight *= 2)
        {
            if (count < 2 * fight)
            {
                if (0 < count - fight) ++countTurns;
                break;
            }
            else
                ++countTurns;
        }

        if (3 * days.size() < countTurns)
        {
            QMessageBox::warning(0, QString("Проблема"),
                                 QString("Для сетки \"%1\" необходимо %2 круга (кругов), "
                                         "но имеется только %3 день (дня, дней)")
                                 .arg(DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", tournamentCaterotyUID))
                                 .arg(countTurns)
                                 .arg(days.size()));
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


    int n = 0;
    std::set<RegionRandomOrders> notUsedFighters; // всех простых бойцов из another  кидаем в notUsedFighters
    {
        QHash<long long, QVector<long long>> usualFighters;

        QSqlQuery query("SELECT * FROM ORDERS WHERE TOURNAMENT_CATEGORY_FK = ? ORDER BY SECOND_NAME, FIRST_NAME");
        query.addBindValue(tournamentCaterotyUID);
        if (!query.exec())
        {
            qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
            return;
        }
        while (query.next())
        {
            ++n;
            long long orderUID = query.value("UID").toLongLong();
            long long region   = query.value("REGION_FK").toLongLong();;
            if (!bestUID.contains(orderUID))
                usualFighters[region].push_back(orderUID);
        }

        for (auto it = usualFighters.begin(); it != usualFighters.end(); ++it)
        {
            std::random_shuffle(it.value().begin(), it.value().end());
            notUsedFighters.insert(RegionRandomOrders({it.key(), rand(), it.value()}));
        }
    }
    if (n <= 0) return;


    QVector<bool> isLeaf(2);
    {
        QQueue<int> queue;
        int cnt = 1;
        isLeaf[1] = true;
        queue.enqueue(1);
        while (cnt < n)
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

        QSqlQuery query("INSERT INTO GRID VALUES (?,?,?,   ?,?,   ?,?)");
        query.addBindValue(tournamentCaterotyUID);
        query.addBindValue(v);
        query.addBindValue(1);

        query.addBindValue(0);
        query.addBindValue("");

        query.addBindValue(dayFight [Utils::log2(v)]);
        query.addBindValue(timeFight[Utils::log2(v)]);
        if (!query.exec())
            qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
    }


    QVector<bool> isUsedLeaf(maxVertex + 1);
    QVector<long long> regionLeaf(maxVertex + 1);
    QVector<int> vertexOfBest;
    if (!bestUID.isEmpty())
    {
        QVector<QString> pref;
        if (bestUID.size() == 1) pref << "1";
        if (bestUID.size() == 2) pref << "11" << "10";
        if (bestUID.size() == 3) pref << "11" << "101" << "100";
        if (bestUID.size() == 4) pref << "111" << "101" << "110" << "100";
        for (int i = 0; i < bestUID.size(); ++i)
        {
            int v = pref[i].toInt(0, 2);
            while (!isLeaf[v]) v = 2 * v + 1;
            vertexOfBest << v;

            isUsedLeaf[v] = true;
            regionLeaf[v] = DBUtils::getField("REGION_FK", "ORDERS", bestUID[i]).toLongLong();

            DBUtils::insertLeafOfGrid(tournamentCaterotyUID, v, bestUID[i]);
        }
    }


    if (2 <= n)
    {
        // пытаемся сделать так, чтобы в правом и в левом подДеревьях было по одному представителю от каждого региона
        for (QString prefix : {"11", "10"})
        {
            QVector<int> vertex;
            QSet<long long> usedRegions;
            for (int v = 1; v <= maxVertex; ++v)
                if (isLeaf[v] && QString::number(v, 2).startsWith(prefix))
                {
                    if (regionLeaf[v] != 0)
                        usedRegions << regionLeaf[v];
                    else
                        vertex << v;
                }
            std::sort(vertex.begin(), vertex.end(), [](int a, int b){ return (a&1) > (b&1);});
            for (int v : vertexOfBest) // делаем так, чтобы вначале найти пару особым бойцам
                if (vertex.contains(v ^ 1))
                {
                    vertex.removeOne(v ^ 1);
                    vertex.push_front(v ^ 1);
                }
            //qDebug() << vertex;


            QVector<long long> orderUIDs;
            {
                QVector<RegionRandomOrders> arr;
                while (0 < notUsedFighters.size() && vertex.size() != orderUIDs.size())
                {
                    RegionRandomOrders cur = *notUsedFighters.begin();
                    notUsedFighters.erase(notUsedFighters.begin());
                    if (!usedRegions.contains(cur.region))
                        orderUIDs << cur.orderUIDs.takeLast();
                    if (cur.orderUIDs.size())
                    {
                        cur.random_number = rand();
                        arr << cur;
                    }
                }
                for (RegionRandomOrders x : arr) notUsedFighters.insert(x);
            }


            //qDebug() << "vertex: " << vertex;
            while (!vertex.isEmpty() && !orderUIDs.isEmpty())
            {
                long long orderUID_V = orderUIDs.takeFirst();
                int v = vertex.takeFirst();
                //qDebug() << orderUID_V << " v:" << v;
                DBUtils::insertLeafOfGrid(tournamentCaterotyUID, v, orderUID_V);
                isUsedLeaf[v] = true;
                regionLeaf[v] = DBUtils::getField("REGION_FK", "ORDERS", orderUID_V).toLongLong();
            }
        }
    }


    //

    // находим пару для тех бойцов, для которые без пары
    for (int v = 1; v <= maxVertex; ++v)
    {
        int anotherVetex = v ^ 1;
        if (!(1 <= anotherVetex && anotherVetex <= maxVertex)) continue;
        if (isLeaf[v] && !isUsedLeaf[v] && isLeaf[anotherVetex] && isUsedLeaf[anotherVetex])
        {
            const int regionAnother = regionLeaf[anotherVetex];
            long long orderUID_V;

            RegionRandomOrders a = *notUsedFighters.begin();
            notUsedFighters.erase(notUsedFighters.begin());
            if (!notUsedFighters.empty() && a.region == regionAnother)
            {
                RegionRandomOrders b = *notUsedFighters.begin();
                notUsedFighters.erase(notUsedFighters.begin());
                orderUID_V = b.orderUIDs.takeLast();

                if (!b.orderUIDs.empty())
                {
                    b.random_number = rand();
                    notUsedFighters.insert(b);
                }
            }
            else
                orderUID_V = a.orderUIDs.takeLast();

            if (!a.orderUIDs.empty())
            {
                a.random_number = rand();
                notUsedFighters.insert(a);
            }

            DBUtils::insertLeafOfGrid(tournamentCaterotyUID, v, orderUID_V);
            isUsedLeaf[v] = true;
            regionLeaf[v] = DBUtils::getField("REGION_FK", "ORDERS", orderUID_V).toLongLong();
            //qDebug() << v << "cur: " << DBUtils::getField("REGION_FK", "ORDERS", orderUID_V).toLongLong() <<  "regionAnother: " << regionAnother;
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


    // просто берем пары
    while (!freePairsOfLeafs.isEmpty())
    {
        const std::pair<int, int> pair = freePairsOfLeafs.last();
        freePairsOfLeafs.pop_back();

        //for (auto it : notUsedFighters){ qDebug() << "region: " <<  DBUtils::getField("NAME", "REGIONS", it.region) << it.random_number << it.orderUIDs;}

        long long orderUID0;
        long long orderUID1;
        {
            RegionRandomOrders a = *notUsedFighters.begin();
            notUsedFighters.erase(notUsedFighters.begin());
            orderUID0 = a.orderUIDs.takeLast();
            if (notUsedFighters.empty()) // соединяем двух чуваков с одного региона; какая жалость
            {
                orderUID1 = a.orderUIDs.takeLast();
            }
            else
            {
                RegionRandomOrders b = *notUsedFighters.begin();
                notUsedFighters.erase(notUsedFighters.begin());
                orderUID1 = b.orderUIDs.takeLast();

                if (!b.orderUIDs.empty())
                {
                    b.random_number = rand();
                    notUsedFighters.insert(b);
                }
            }
            if (!a.orderUIDs.empty())
            {
                a.random_number = rand();
                notUsedFighters.insert(a);
            }
        }

        DBUtils::insertLeafOfGrid(tournamentCaterotyUID, pair.first , orderUID0);
        DBUtils::insertLeafOfGrid(tournamentCaterotyUID, pair.second, orderUID1);

        isUsedLeaf[pair.first ] = true;
        isUsedLeaf[pair.second] = true;
        regionLeaf[pair.first ] = DBUtils::getField("REGION_FK", "ORDERS", orderUID0).toLongLong();
        regionLeaf[pair.second] = DBUtils::getField("REGION_FK", "ORDERS", orderUID1).toLongLong();
        //qDebug() << pair.first << pair.second << DBUtils::getField("REGION_FK", "ORDERS", orderUID0) << DBUtils::getField("REGION_FK", "ORDERS", orderUID1);
    }


    // одна такая вершина, которая "на стыке уровней"
    for (int v = 1; v <= maxVertex; ++v)
    {
        if (isLeaf[v] && !isUsedLeaf[v])
        {
            RegionRandomOrders b = *notUsedFighters.begin();
            notUsedFighters.erase(notUsedFighters.begin());
            long long orderUID = b.orderUIDs.takeLast();

            if (!b.orderUIDs.empty())
            {
                b.random_number = rand();
                notUsedFighters.insert(b);
            }

            DBUtils::insertLeafOfGrid(tournamentCaterotyUID, v, orderUID);
            break;
        }
    }
    assert (notUsedFighters.empty());
    /**/
    QSqlDatabase::database().commit();
}

bool DialogTournamentGrid::deleteGrid(const long long uidTC)
{
    {
        // проверяем есть ли турнирная сетка, если есть, то задаём вопрос
        QSqlQuery query("SELECT * FROM GRID WHERE TOURNAMENT_CATEGORIES_FK = ? ");
        query.addBindValue(uidTC);
        if (query.exec())
        {
            if (query.next())
            {
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(0, "?", QString("Удалить сетку ") +
                                              DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", uidTC) +
                                              "?", QMessageBox::Yes | QMessageBox::No);
                if (reply == QMessageBox::No)
                    return false;
            }
        }
        else
        {
            qDebug() << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
            return true;
        }
    }
    QSqlQuery query("DELETE FROM GRID WHERE TOURNAMENT_CATEGORIES_FK = ?");
    query.addBindValue(uidTC);;
    if (!query.exec())
        qDebug() << __PRETTY_FUNCTION__ << " " << query.lastError().text() << " " << query.lastQuery();
    return true;
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
    ui->qTableWidget->setRowCount(0);
    QSqlQuery query("SELECT * FROM ORDERS WHERE TOURNAMENT_CATEGORY_FK = ? ORDER BY SECOND_NAME, FIRST_NAME");
    query.addBindValue(ui->qComboBoxSelectCategory->currentData(Qt::UserRole).toInt());
    query.exec();
    while (query.next())
    {
        int orderUID = query.value("UID").toInt();
        QString name = query.value("SECOND_NAME").toString() + " " + query.value("FIRST_NAME").toString();
        QString location = getLocation(orderUID);

        ui->qTableWidget->setRowCount(ui->qTableWidget->rowCount() + 1);
        QTableWidgetItem *item;

        item = new QTableWidgetItem(name);
        item->setData(Qt::UserRole, orderUID);
        ui->qTableWidget->setItem(ui->qTableWidget->rowCount() - 1, 0, item);

        ui->qTableWidget->setItem(ui->qTableWidget->rowCount() - 1, 1, new QTableWidgetItem(location));

        ui->qTableWidget->setItem(ui->qTableWidget->rowCount() - 1, 2, new QTableWidgetItem(no_special_group));

        ui->qTableWidget->setItem(ui->qTableWidget->rowCount() - 1, 3, new QTableWidgetItem(DBUtils::getField("NAME", "SPORT_CATEGORIES", query.value("SPORT_CATEGORY_FK").toString())));
    }
    ui->qTableWidget->resizeColumnsToContents();
    ui->qTableWidget->resizeRowsToContents();
}

void DialogTournamentGrid::onActivatedCategory()
{
    const int id = ui->qComboBoxSelectCategory->currentIndex();
    if (!(0 <= id && id < ui->qComboBoxSelectCategory->count()))
    {
        ui->qTableWidget->setRowCount(0);
        ui->tableWidgeRight->setRowCount(0);
        ui->pRenderArea->tournamentCategoryIsChanged(-1);
        return;
    }
    specialGroup = QVector<int>(4, false);

    ui->pRenderArea->tournamentCategoryIsChanged(ui->qComboBoxSelectCategory->currentData(Qt::UserRole).toInt());

    fillListOfOrders();
    fillListOfPairs();
}

void DialogTournamentGrid::onCellCLickedForChangePrioritet(int row, int)
{
    if (!(0 <= row && row < ui->qTableWidget->rowCount())) return;
    QString orderValue = ui->qTableWidget->item(row, 2)->data(Qt::DisplayRole).toString();
    if (orderValue == no_special_group)
    {
        for (int i = 1; i <= 3; ++i)
        {
            if ((i <= 2 && specialGroup[i] == 0) || (i == 3 && specialGroup[i] <= 1))
            {
                ui->qTableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(i)));
                ++specialGroup[i];
                break;
            }
        }
    }
    else
    {
        ui->qTableWidget->setItem(row, 2, new QTableWidgetItem(no_special_group));
        --specialGroup[orderValue.toInt()];
    }
}

void DialogTournamentGrid::onButtonGenerateGrid()
{
    //
    {
        // проверяем есть ли турнирная сетка, если есть, то задаём вопрос
        QSqlQuery query("SELECT * FROM GRID WHERE TOURNAMENT_CATEGORIES_FK = ? ");
        query.addBindValue(ui->qComboBoxSelectCategory->currentData(Qt::UserRole).toInt());
        if (query.exec())
        {
            if (query.next())
            {
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, "?", "Сетка уже есть. Новая генерация сетки приведет к потере старой сетки. Продолжить?", QMessageBox::Yes | QMessageBox::No);
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
    for (int row = 0; row < ui->qTableWidget->rowCount(); ++row)
    {
        long long orderUID = ui->qTableWidget->item(row, 0)->data(Qt::UserRole).toLongLong();
        QString special_group = ui->qTableWidget->item(row, 2)->data(Qt::DisplayRole).toString();
        if (special_group != no_special_group)
        {
            int priority = special_group.toInt();
            bestFighters << std::make_pair(priority, orderUID);
            //qDebug() << __LINE__ << __PRETTY_FUNCTION__ << orderUID << " " << priority << " " << region;
        }
    }
    std::random_shuffle(bestFighters.begin(), bestFighters.end());
    qSort(bestFighters.begin(), bestFighters.end(), [](const std::pair<int, long long> a, const std::pair<int, long long> b){
        return a.first < b.first;
    });
    QVector<long long> bestUID;
    for (std::pair<int, long long> f : bestFighters)
        bestUID << f.second;

    generatGrid(tournamentUID, ui->qComboBoxSelectCategory->currentData(Qt::UserRole).toInt(), bestUID);

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
    for (int i = 0; i < ui->qComboBoxSelectCategory->count(); ++i)
    {
        if (!deleteGrid(ui->qComboBoxSelectCategory->itemData(i, Qt::UserRole).toInt()))
        {
            break;
        }
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
    QTime time;
    time.start();

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
            QString categoryUID = query.value("UID").toString();
            QString categoryName = query.value("NAME").toString();

            std::set<long long> mansFromOrder;
            {
                QSqlQuery queryOrders("SELECT * FROM ORDERS WHERE TOURNAMENT_CATEGORY_FK = ? ");
                queryOrders.addBindValue(categoryUID);
                if (!queryOrders.exec())
                {
                    qDebug() << __PRETTY_FUNCTION__ << queryOrders.lastError() << queryOrders.lastQuery();
                    continue;
                }
                while (queryOrders.next())
                    mansFromOrder.insert(queryOrders.value("UID").toLongLong());
            }

            std::set<long long> mansFromGrig;
            bool haveSomePeopleInGridOrInOrder = 0 < mansFromOrder.size();
            for(const DBUtils::NodeOfTournirGrid& it : DBUtils::getNodes(categoryUID.toLongLong()))
            {
                haveSomePeopleInGridOrInOrder = true;
                if (0 < it.UID)
                    mansFromGrig.insert(it.UID);
            }


            bool havePartiallyFilledLevel = false;
            {
                QVector<QVector<DBUtils::NodeOfTournirGrid> > grid = DBUtils::getNodesAsLevelListOfList(categoryUID.toLongLong());
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



            if (
                (ui->radioButtonAll->isChecked() && haveSomePeopleInGridOrInOrder) ||
                (ui->radioButtonLonly->isChecked() && mansFromOrder.size() == 1) ||
                (ui->radioButtonInvalid->isChecked() && std::vector<int>(mansFromOrder.begin(), mansFromOrder.end()) != std::vector<int>(mansFromGrig.begin(), mansFromGrig.end())) ||
                (ui->radioButtonInvalidTurn->isChecked() && havePartiallyFilledLevel)
                ){
                ui->qComboBoxSelectCategory->addItem(categoryName, categoryUID);
            }
        }
    }

    onActivatedCategory();

    qDebug() << __LINE__ << __PRETTY_FUNCTION__ << "Time:" << time.elapsed();
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
        QVector<long long> bestUID;

        //        QSqlQuery queryOrder("SELECT * FROM ORDERS WHERE TOURNAMENT_CATEGORIES = ? ");
        //        queryOrder.bindValue(0, tcUID);
        //        queryOrder.exec();
        //        while (queryOrder.next()) bestUID << queryOrder.value("UID").toLongLong();
        //        std::random_shuffle(bestUID.begin(), bestUID.end());
        //        bestUID.resize(qMin(bestUID.size(), sz));

        if (DBUtils::getNodes(tcUID).isEmpty())
            generatGrid(tournamentUID, tcUID, bestUID);

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
    QModelIndex index = ui->qTableWidget->indexAt(pos);
    qDebug() << "index: " << index;

    QAction* restrictAction = new QAction("Заявки спортсмена...", &contextMenu);
    if (index.isValid())
    {
        contextMenu.addAction(restrictAction);
        connect(restrictAction, &QAction::triggered, [this, &index] ()
        {
            long long orderUID = index.data(Qt::UserRole).toLongLong();
            CreateTournamentOrdersDialog(this->tournamentUID, this,
                                         DBUtils::getField("SECOND_NAME", "ORDERS", orderUID),
                                         DBUtils::getField("FIRST_NAME", "ORDERS", orderUID)
                                         ).exec();
            onActivatedCategory();
        });
    }

    QAction delAction("Все заявки...", &contextMenu);
    contextMenu.addAction(&delAction);
    connect(&delAction, &QAction::triggered, [this, &pos] ()
    {
        CreateTournamentOrdersDialog(this->tournamentUID, this).exec();
        onActivatedCategory();
    });

    contextMenu.exec(ui->qTableWidget->viewport()->mapToGlobal(pos));
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

void DialogTournamentGrid::onSpinBoxFontSizeChangedOfListOfOrders(int sizeFont)
{
    QFont font = ui->qTableWidget->font();
    font.setPointSize(sizeFont);
    ui->qTableWidget->setFont(font);
    ui->qTableWidget->resizeColumnsToContents();
    ui->qTableWidget->resizeRowsToContents();
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



