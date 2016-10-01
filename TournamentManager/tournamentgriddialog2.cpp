#include "tournamentgriddialog2.h"
#include "renderareawidget.h"
#include "createtournamentordersdialog.h"

#include <QScrollArea>
#include <QGridLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QSplitter>
#include <QWidget>
#include <QSpinBox>
#include <QLabel>
#include <QComboBox>
#include <QSqlQuery>
#include <QListWidgetItem>
#include <qDebug>
#include <QModelIndex>
#include <QApplication>
#include <QDebug>
#include <QAxObject>
#include <QAxBase>
#include <QSqlError>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QAbstractItemModel>
#include <QQueue>
#include <algorithm>
#include <time.h>
#include <set>
#include <QtGlobal>
#include <QDate>
#include <assert.h>
#include <string>
#include <QTabWidget>
#include <utility>
#include <iostream>
#include <QMenu>
#include <QHeaderView>


TournamentGridDialog2::TournamentGridDialog2(long long _tournamentUID, QWidget *_parent)
    : QDialog(_parent),
      tournamentUID(_tournamentUID)
{
    tournamentCategories = -1;
    specialGroup = QVector<int>(4, false);

    QWidget *leftPane = new QWidget;
    leftPane->setBackgroundRole(QPalette::Dark);
    qComboBoxSelectCategory = new QComboBox;
    qComboBoxSelectCategory->setMaxVisibleItems(200);
    qTableWidget = new QTableWidget(0, 3);
    qTableWidget->setColumnCount(4);
    qTableWidget->setHorizontalHeaderLabels(QStringList({"Спортсмен", "Страна / Регион", "Приоритет", "Разряд"}));
    qTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    qTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    qTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    qTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    qTableWidget->setFocusPolicy(Qt::NoFocus);

    QPushButton *buttonGenerate = new QPushButton("Сгенерировать сетку");
    QPushButton *buttonGenerateAll = new QPushButton("Сгенерировать все сетки");
    QPushButton *buttonDelete = new QPushButton("Удалить сетку");
    QPushButton *buttonDeleteAll = new QPushButton("Удалить все сетки");
    QLineEdit* filterCategoriesLE = new QLineEdit;

    groupBox = new QGroupBox(tr("Фильтр сеток"));
    radioButtonAll = new QRadioButton(tr("Все"));
    radioButtonLonly = new QRadioButton(tr("Одиночки"));
    radioButtonInvalid = new QRadioButton(tr("Разные участники"));
    radioButtonInvalidTurn = new QRadioButton(tr("Незаполненные круги, ошибки"));
    radioButtonAll->setChecked(true);
    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(radioButtonAll);
    hbox->addWidget(radioButtonLonly);
    hbox->addWidget(radioButtonInvalid);
    hbox->addWidget(radioButtonInvalidTurn);
    hbox->addStretch(1);
    groupBox->setLayout(hbox);

    QGroupBox *groupBoxScale = new QGroupBox("Размер шрифта");
    QSpinBox *spinBoxFontSize = new QSpinBox();
    spinBoxFontSize->setMinimum(1);
    spinBoxFontSize->setMaximum(228);
    spinBoxFontSize->setValue(qTableWidget->font().pointSize());
    {
        QHBoxLayout *hbox = new QHBoxLayout;
        hbox->addWidget(spinBoxFontSize);
        hbox->addStretch(1);
        groupBoxScale->setLayout(hbox);
    }

    {
        QGridLayout *mainLayout = new QGridLayout;
        mainLayout->addWidget(filterCategoriesLE, 0, 0, 1, 5);

        mainLayout->addWidget(groupBox, 1, 0, 1, 4);
        mainLayout->addWidget(groupBoxScale, 1, 4, 1, 1);

        mainLayout->addWidget(qComboBoxSelectCategory, 2, 0, 1, 5);
        mainLayout->addWidget(qTableWidget, 3, 0, 1, 5);
        {
            QHBoxLayout *qHBoxLayout = new QHBoxLayout();
            qHBoxLayout->addWidget(buttonGenerateAll);
            qHBoxLayout->addWidget(buttonDelete);
            qHBoxLayout->addWidget(buttonDeleteAll);
            qHBoxLayout->addWidget(buttonGenerate);
            QWidget* wdg = new QWidget();
            wdg->setLayout(qHBoxLayout);
            mainLayout->addWidget(wdg, 4, 0, 1, 5);
        }
        leftPane->setLayout(mainLayout);
    }



    QWidget *rightPane = new QWidget;
    QPushButton *buttonSave = new QPushButton("Сохранить в Excel");
    QPushButton *buttonSaveAll = new QPushButton("Сохранить все сетки в Excel");
    widthSpinBox = new QSpinBox;
    heightSpinBox = new QSpinBox;
    widthSpinBox->setMaximum(1000);
    widthSpinBox->setValue(128);
    heightSpinBox->setValue(30);


    QScrollArea *pQScrollArea = new QScrollArea;
    pRenderArea = new RenderAreaWidget(pQScrollArea, widthSpinBox->value(), heightSpinBox->value());
    pQScrollArea->setWidget(pRenderArea);
    qTabWidget = new QTabWidget();
    qTabWidget->addTab(pQScrollArea, "Сетка");


    tableWidgeRight = new QTableWidget();
    tableWidgeRight->setColumnCount(5);
    tableWidgeRight->setHorizontalHeaderLabels(QStringList({"Спортсмен A", "Регион A", "Спортсмен B", "Регион B", "Уровень"}));
    tableWidgeRight->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidgeRight->setSelectionMode(QAbstractItemView::SingleSelection);
    qTabWidget->addTab(tableWidgeRight, "Список");



    widthQLabel = new QLabel("Ширина:");
    widthQLabel->setAlignment(Qt::AlignRight | Qt::AlignCenter);
    heightQLabel = new QLabel("Высота:");
    heightQLabel->setAlignment(Qt::AlignRight | Qt::AlignCenter);

    groupBoxScaleRight = new QGroupBox("Размер шрифта");
    groupBoxScaleRight->setVisible(false);
    QSpinBox *spinBoxFontSizeRight = new QSpinBox();
    spinBoxFontSizeRight->setMinimum(1);
    spinBoxFontSizeRight->setMaximum(228);
    spinBoxFontSizeRight->setValue(tableWidgeRight->font().pointSize());
    {
        QHBoxLayout *hbox = new QHBoxLayout;
        hbox->addWidget(spinBoxFontSizeRight);
        hbox->addStretch(1);
        groupBoxScaleRight->setLayout(hbox);
    }

    {
        QGridLayout *mainLayout = new QGridLayout;

        mainLayout->addWidget(buttonSave, 0, 0);
        mainLayout->addWidget(buttonSaveAll, 0, 1);
        mainLayout->addWidget(widthQLabel, 0, 2);
        mainLayout->addWidget(widthSpinBox, 0, 3);
        mainLayout->addWidget(heightQLabel, 0, 4);
        mainLayout->addWidget(heightSpinBox, 0, 5);
        mainLayout->addWidget(groupBoxScaleRight, 0, 6);


        mainLayout->addWidget(qTabWidget, 1, 0, 1, 7);

        rightPane->setLayout(mainLayout);
    }


    QSplitter *splitter = new QSplitter;
    splitter->addWidget(leftPane);
    splitter->addWidget(rightPane);
//    splitter->setHandleWidth(10);
//    splitter->setStyleSheet("QSplitter::handle{background-color: black;}");


    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(splitter, 0, 0);
    setLayout(mainLayout);


    connect(buttonGenerate, SIGNAL(clicked(bool)), SLOT(onButtonGenerateGrid()));
    connect(widthSpinBox, SIGNAL(valueChanged(int)), pRenderArea, SLOT(widthChanged(int)));
    connect(heightSpinBox, SIGNAL(valueChanged(int)), pRenderArea, SLOT(heightChanged(int)));
    connect(qTableWidget, SIGNAL(cellClicked(int,int)), SLOT(onCellCLickedForChangePrioritet(int, int)));
    connect(buttonDelete, QPushButton::clicked, [this](){
        deleteGrid(tournamentCategories);
        pRenderArea->repaint();
        fillTableGrid();
    });
    connect(buttonDeleteAll, &QPushButton::clicked, [this](){
        for (int i = 0; i < qComboBoxSelectCategory->count(); ++i)
        {
            if (!deleteGrid(qComboBoxSelectCategory->itemData(i, Qt::UserRole).toInt()))
            {
                break;
            }
        }
        pRenderArea->repaint();
        fillTableGrid();
    });
    connect(buttonSave, SIGNAL(clicked()), pRenderArea, SLOT(onSaveInExcel()));
    connect(tableWidgeRight, SIGNAL(cellClicked(int,int)), SLOT(onCellClickedOntableGrid(int, int)));
    connect(buttonGenerateAll, &QPushButton::clicked, this, &TournamentGridDialog2::onButtonGenerateAll);
    connect(pRenderArea, &RenderAreaWidget::iChangeToutGrid, this, &TournamentGridDialog2::fillTableGrid);

    fillCategoryCombobox();
    connect(qComboBoxSelectCategory, SIGNAL(activated(int)), this, SLOT(onActivatedCategory(int)));
    if (0 < qComboBoxSelectCategory->count())
        onActivatedCategory(0);

    connect(filterCategoriesLE, &QLineEdit::textChanged, [this] (const QString& filter)
    {
        fillCategoryCombobox(filter);
    });


    connect(radioButtonAll        , &QRadioButton::clicked, [this, filterCategoriesLE] (){fillCategoryCombobox(filterCategoriesLE->text());});
    connect(radioButtonLonly      , &QRadioButton::clicked, [this, filterCategoriesLE] (){fillCategoryCombobox(filterCategoriesLE->text());});
    connect(radioButtonInvalid    , &QRadioButton::clicked, [this, filterCategoriesLE] (){fillCategoryCombobox(filterCategoriesLE->text());});
    connect(radioButtonInvalidTurn, &QRadioButton::clicked, [this, filterCategoriesLE] (){fillCategoryCombobox(filterCategoriesLE->text());});



    qTableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(qTableWidget, &QTableView::customContextMenuRequested, [this] (const QPoint& pos)
    {
        QMenu * contextMenu = new QMenu();

        QAction* restrictAction = new QAction(tr("Изменить категорию..."), contextMenu);
        contextMenu->addAction(restrictAction);
        connect(restrictAction, &QAction::triggered, [this, &pos] ()
        {
            QModelIndex index = qTableWidget->indexAt(pos);
            if (index != QModelIndex())
            {
                long long orderUID = qTableWidget->item(index.row(), 0)->data(Qt::UserRole).toLongLong();
                //qDebug() << DBUtils::getSecondNameAndOneLetterOfName(QSqlDatabase::database(), orderUID);
                CreateTournamentOrdersDialog(QSqlDatabase::database(), tournamentUID, this,
                    DBUtils::getField("SECOND_NAME", "ORDERS", orderUID),
                    DBUtils::getField("FIRST_NAME", "ORDERS", orderUID)
                ).exec();
                onActivatedCategory(qComboBoxSelectCategory->currentIndex());
            }
        });

        QAction * delAction = new QAction(tr("Перейти в заявки..."), contextMenu);
        contextMenu->addAction(delAction);
        connect(delAction, &QAction::triggered, [this, &pos] ()
        {
            CreateTournamentOrdersDialog(QSqlDatabase::database(), tournamentUID, this).exec();
            onActivatedCategory(qComboBoxSelectCategory->currentIndex());
        });

        contextMenu->exec(qTableWidget->viewport()->mapToGlobal(pos));
    });


    connect(buttonSaveAll, &QPushButton::clicked, [this]
    {
        DialogChoseData dlg(DialogChoseData::Type::grids);
        if (dlg.exec() != QDialog::Accepted)
            return;

        QString directoryPath = QFileDialog::getExistingDirectory(this, tr("Выберите папку"), NULL, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        if (directoryPath.isNull()) return;
        //qDebug() << dir;
        QSqlQuery query("SELECT * FROM TOURNAMENT_CATEGORIES WHERE TOURNAMENT_FK = ? ORDER BY SEX_FK, TYPE_FK, AGE_FROM, AGE_TILL, WEIGHT_FROM, WEIGHT_TILL ");
        query.bindValue(0, tournamentUID);
        if (!query.exec())
        {
            qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
            return;
        }

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


        long long tBeg = QDateTime::currentMSecsSinceEpoch();
        QAxWidget excel("Excel.Application");
        QAxObject *workbooks = excel.querySubObject("WorkBooks");
        while (query.next())
        {
            workbooks->dynamicCall("Add");
            QAxObject *workbook = excel.querySubObject("ActiveWorkBook");

            qlonglong tcUID = query.value("UID").toLongLong();
            RenderAreaWidget::printTableGridInExcel(workbook, dlg, tcUID, false, directoryPath, QVector<int>(), "", "");
            progress.setValue(progress.value() + 1);
            if (progress.wasCanceled())
                break;

            workbook->dynamicCall("Close()");
            delete workbook;
        }
        delete workbooks;
        excel.dynamicCall("Quit()");
        long long sec = (QDateTime::currentMSecsSinceEpoch() - tBeg) / 1000;
        qDebug() << "Время печати всех сеток" <<  sec / 60 << " м" << sec % 60 << " с";
    });


    //connect(spinBoxFontSize, &QSpinBox::valueChanged, this, &TournamentGridDialog2::onSpinBoxFontSizeChanged);
    connect(spinBoxFontSize, SIGNAL(valueChanged(int)), this, SLOT(onSpinBoxFontSizeChanged(int)));
    connect(spinBoxFontSizeRight, SIGNAL(valueChanged(int)), this, SLOT(onSpinBoxFontSizeChangedOfRightTable(int)));
    connect(qTabWidget, SIGNAL(currentChanged(int)), this, SLOT(onTabSwitch(int)));

    setWindowFlags(windowFlags() | Qt::WindowMinMaxButtonsHint);
    resize(1000, 700);
    //showMaximized();
}


// юзер выбирает категорию турнира
void TournamentGridDialog2::onActivatedCategory(int id)
{
    if (!(0 <= id && id < qComboBoxSelectCategory->count()))
    {
        qTableWidget->setRowCount(0);
        tableWidgeRight->setRowCount(0);
        pRenderArea->slotSetTournamentCategories(0);
        return;
    }
    specialGroup = QVector<int>(4, false);
    tournamentCategories = qComboBoxSelectCategory->itemData(id, Qt::UserRole).toInt();

    pRenderArea->slotSetTournamentCategories(tournamentCategories);
    //qDebug() << __LINE__ << __PRETTY_FUNCTION__ << "tournamentCategories: " << tournamentCategories;

    QSqlQuery query("SELECT * FROM ORDERS WHERE TOURNAMENT_CATEGORY_FK = ? ORDER BY SECOND_NAME, FIRST_NAME");
    query.bindValue(0, tournamentCategories);

    //qDebug() << "\n" << __PRETTY_FUNCTION__  << "\n" << "tournamentCategories: " << tournamentCategories << "\n";

    qTableWidget->setRowCount(0);
    if (query.exec())
    {
        while (query.next())
        {
            QString name = query.value("SECOND_NAME").toString() + " " + query.value("FIRST_NAME").toString();
            long long idCountry = query.value("COUNTRY_FK").toInt();
            long long idRegion = query.value("REGION_FK").toInt();
            QString countryRegion =
                    DBUtils::getField("NAME", "COUNTRIES", idCountry) + QString(" / ") +
                    DBUtils::getField("NAME", "REGIONS", idRegion);

            qTableWidget->setRowCount(qTableWidget->rowCount() + 1);
            QTableWidgetItem *item;

            item = new QTableWidgetItem(name);
            item->setData(Qt::UserRole, query.value("UID").toLongLong());
            qTableWidget->setItem(qTableWidget->rowCount() - 1, 0, item);

            item = new QTableWidgetItem(countryRegion);
            item->setData(Qt::UserRole, idRegion);
            qTableWidget->setItem(qTableWidget->rowCount() - 1, 1, item);

            qTableWidget->setItem(qTableWidget->rowCount() - 1, 2, new QTableWidgetItem(no_special_group));

            qTableWidget->setItem(qTableWidget->rowCount() - 1, 3, new QTableWidgetItem(DBUtils::getField("NAME", "SPORT_CATEGORIES", query.value("SPORT_CATEGORY_FK").toString())));
        }
    }
    else
    {
        qDebug() << __PRETTY_FUNCTION__  << query.lastError() << query.lastQuery();
    }

    qTableWidget->resizeColumnsToContents();
    qTableWidget->resizeRowsToContents();

    fillTableGrid();
}

// юзер кликает по участнику и у него меняется приоритет
void TournamentGridDialog2::onCellCLickedForChangePrioritet(int row, int )
{
    if (!(0 <= row && row < qTableWidget->rowCount())) return;
    QString orderValue = qTableWidget->item(row, 2)->data(Qt::DisplayRole).toString();
    if (orderValue == no_special_group)
    {
        for (int i = 1; i <= 3; ++i)
        {
            if ((i <= 2 && specialGroup[i] == 0) || (i == 3 && specialGroup[i] <= 1))
            {
                qTableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(i)));
                ++specialGroup[i];
                break;
            }
        }
    }
    else
    {
        qTableWidget->setItem(row, 2, new QTableWidgetItem(no_special_group));
        --specialGroup[orderValue.toInt()];
    }
}


void TournamentGridDialog2::generatGrid(const long long tournamentCaterotyUID, QVector<long long> bestUID)
{
    {
        // удалим старую сетку
        QSqlQuery query("DELETE FROM GRID WHERE TOURNAMENT_CATEGORIES_FK = ? ");
        query.bindValue(0, tournamentCaterotyUID);
        if (!query.exec())
        {
            qDebug() << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
            return;
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

        QSqlQuery query("INSERT INTO GRID VALUES (?, ?, ?, null, null)");
        query.bindValue(0, tournamentCaterotyUID);
        query.bindValue(1, v);
        query.bindValue(2, "true");
        if (!query.exec())
            qDebug() << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
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

            QSqlQuery query("INSERT INTO GRID VALUES (?, ?, ?, ?, null)");
            query.bindValue(0, tournamentCaterotyUID);
            query.bindValue(1, v);
            query.bindValue(2, "false");
            query.bindValue(3, bestUID[i]);
            if (!query.exec())
                qDebug() << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
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

bool TournamentGridDialog2::deleteGrid(const long long uidTC)
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


// генерация турнирной сетки
void TournamentGridDialog2::onButtonGenerateGrid()
{
    //
    {
        // проверяем есть ли турнирная сетка, если есть, то задаём вопрос
        QSqlQuery query("SELECT * FROM GRID WHERE TOURNAMENT_CATEGORIES_FK = ? ");
        query.bindValue(0, tournamentCategories);
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
    pRenderArea->clearSelection();



    QVector<std::pair<int, long long>> bestFighters;
    for (int row = 0; row < qTableWidget->rowCount(); ++row)
    {
        long long orderUID = qTableWidget->item(row, 0)->data(Qt::UserRole).toLongLong();
        QString special_group = qTableWidget->item(row, 2)->data(Qt::DisplayRole).toString();
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

    TournamentGridDialog2::generatGrid(tournamentCategories, bestUID);

    pRenderArea->repaint();
    fillTableGrid();
}






TournamentGridDialog2::~TournamentGridDialog2(){}

void TournamentGridDialog2::fillTableGrid()
{
    selectedRowOfRableGrid = -1;
    selectedColumnOfRableGrid = -1;
    QVector<DBUtils::NodeOfTournirGrid> nodes = DBUtils::getNodes(tournamentCategories);
    {
        QVector<DBUtils::NodeOfTournirGrid> leafs;
        for (DBUtils::NodeOfTournirGrid node : nodes)
            if (!node.isFighing)
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

    for(int i = 0; i < tableWidgeRight->rowCount(); ++i)
    {
        QAbstractItemDelegate* delegate = tableWidgeRight->itemDelegateForRow( i );
        tableWidgeRight->setItemDelegateForRow(i, 0);
        if (delegate)
            delete delegate; // Криво как свинячья пиписька но работает.
    }

    tableWidgeRight->setRowCount(0);
    bool findCenter = false;
    for (DBUtils::NodeOfTournirGrid node : nodes)
    {
        if ((node.v & 1) == 0) continue;

        tableWidgeRight->setRowCount(tableWidgeRight->rowCount() + 1);

        QTableWidgetItem *item;

        item = new QTableWidgetItem(node.name);
        item->setData(Qt::UserRole, node.v);
        tableWidgeRight->setItem(tableWidgeRight->rowCount() - 1, 0, item);

        item = new QTableWidgetItem(node.region);
        item->setData(Qt::UserRole, node.v);
        tableWidgeRight->setItem(tableWidgeRight->rowCount() - 1, 1, item);

        item = new QTableWidgetItem();
        item->setData(Qt::UserRole, 0);
        tableWidgeRight->setItem(tableWidgeRight->rowCount() - 1, 2, item);
        item = new QTableWidgetItem();
        item->setData(Qt::UserRole, 0);
        tableWidgeRight->setItem(tableWidgeRight->rowCount() - 1, 3, item);
        for (DBUtils::NodeOfTournirGrid node2 : nodes)
        {
            if (node2.v != (node.v ^ 1)) continue;
            item = new QTableWidgetItem(node2.name);
            item->setData(Qt::UserRole, node2.v);
            tableWidgeRight->setItem(tableWidgeRight->rowCount() - 1, 2, item);
            item = new QTableWidgetItem(node2.region);
            item->setData(Qt::UserRole, node2.v);
            tableWidgeRight->setItem(tableWidgeRight->rowCount() - 1, 3, item);
            break;
        }

        item = new QTableWidgetItem(RenderAreaWidget::getNameOfLevel(node.v / 2));
        tableWidgeRight->setItem(tableWidgeRight->rowCount() - 1, 4, item);

        if(!findCenter && QString::number(node.v, 2).startsWith("10"))
        {
            findCenter = true;
            tableWidgeRight->setItemDelegateForRow(tableWidgeRight->rowCount() - 1, new DrawBorderDelegate(this));
        }
    }
    tableWidgeRight->resizeColumnsToContents();
    tableWidgeRight->resizeRowsToContents();
    tableWidgeRight->clearSelection();
    tableWidgeRight->clearFocus();
}

void TournamentGridDialog2::onSpinBoxFontSizeChanged(int sizeFont)
{
    QFont font = qTableWidget->font();
    font.setPointSize(sizeFont);
    qTableWidget->setFont(font);
    qTableWidget->resizeColumnsToContents();
    qTableWidget->resizeRowsToContents();
}

void TournamentGridDialog2::onSpinBoxFontSizeChangedOfRightTable(int sizeFont)
{
    QFont font = tableWidgeRight->font();
    font.setPointSize(sizeFont);
    tableWidgeRight->setFont(font);
    tableWidgeRight->resizeColumnsToContents();
    tableWidgeRight->resizeRowsToContents();
}

void TournamentGridDialog2::onTabSwitch(int idTab)
{
    qDebug() << idTab;
    if (idTab == 1)
    {
        widthQLabel  ->setVisible(false);
        heightQLabel ->setVisible(false);
        widthSpinBox ->setVisible(false);
        heightSpinBox->setVisible(false);

        groupBoxScaleRight->setVisible(true);
    }
    else
    {
        widthQLabel  ->setVisible(true);
        heightQLabel ->setVisible(true);
        widthSpinBox ->setVisible(true);
        heightSpinBox->setVisible(true);

        groupBoxScaleRight->setVisible(false);
    }
}


void TournamentGridDialog2::fillCategoryCombobox(QString filterStr)
{
    qDebug() << __LINE__ << "TournamentGridDialog2";
    qComboBoxSelectCategory->clear();

    QStringList filters = filterStr.split(" ", QString::SkipEmptyParts);
    QString whereStatement = "";
    for (const QString& filter: filters)
    {
        whereStatement += " AND NAME LIKE '%" + filter + "%' ";
    }

    QSqlQuery query("SELECT * FROM TOURNAMENT_CATEGORIES WHERE TOURNAMENT_FK = ? " + whereStatement + " ORDER BY SEX_FK, TYPE_FK, AGE_FROM, AGE_TILL, WEIGHT_FROM, WEIGHT_TILL ");
    query.bindValue(0, tournamentUID);
    if (!query.exec())
    {
        qDebug() << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
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
                queryOrders.bindValue(0, categoryUID);
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
            for(DBUtils::NodeOfTournirGrid it : DBUtils::getNodes(categoryUID.toLongLong()))
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
                        DBUtils::NodeOfTournirGrid node = grid[i][j];
                        if (node.isFighing)
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
                                //havePartiallyFilledLevel = true;
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
                (radioButtonAll->isChecked() && haveSomePeopleInGridOrInOrder) ||
                (radioButtonLonly->isChecked() && mansFromOrder.size() == 1) ||
                (radioButtonInvalid->isChecked() && std::vector<int>(mansFromOrder.begin(), mansFromOrder.end()) != std::vector<int>(mansFromGrig.begin(), mansFromGrig.end())) ||
                (radioButtonInvalidTurn->isChecked() && havePartiallyFilledLevel)
            ){
                qComboBoxSelectCategory->addItem(categoryName, categoryUID);
            }
        }
    }

    onActivatedCategory(0);
}

void TournamentGridDialog2::onCellClickedOntableGrid(int row, int column)
{
    //qDebug() << row << column;
    //for (int i = 1; i <= 20; ++i) qDebug() << i << RenderAreaWidget::getNameOfLevel(i);
    if (tableWidgeRight->item(row, column)->data(Qt::UserRole).toInt() <= 0)
    {
        tableWidgeRight->clearSelection();
        tableWidgeRight->clearFocus();
        selectedRowOfRableGrid = -1;
        selectedColumnOfRableGrid = -1;
        return;
    }

    if (selectedRowOfRableGrid == -1 || selectedColumnOfRableGrid == -1)
    {
        selectedRowOfRableGrid = row;
        selectedColumnOfRableGrid = column;
        QModelIndex i = tableWidgeRight->model()->index(row, column ^ 1);
        tableWidgeRight->selectionModel()->select(i, QItemSelectionModel::Select);
    }
    else
    {
        int vertexA = tableWidgeRight->item(row, column)->data(Qt::UserRole).toInt();
        int vertexB = tableWidgeRight->item(selectedRowOfRableGrid, selectedColumnOfRableGrid)->data(Qt::UserRole).toInt();
        //qDebug() << vertexA << vertexB;
        if (0 < vertexA && 0 < vertexB)
        {
            DBUtils::swapNodesOfGrid(tournamentCategories, vertexA, vertexB);
            //qDebug() << "DONE!";
        }
        fillTableGrid();

        tableWidgeRight->clearSelection();
        tableWidgeRight->clearFocus();
        selectedRowOfRableGrid = -1;
        selectedColumnOfRableGrid = -1;
    }

}


void TournamentGridDialog2::onButtonGenerateAll()
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
            generatGrid(tcUID, bestUID);

        progress.setValue(progress.value() + 1);
        if (progress.wasCanceled())
            break;

    }

    pRenderArea->repaint();
    fillTableGrid();
//    }
}










