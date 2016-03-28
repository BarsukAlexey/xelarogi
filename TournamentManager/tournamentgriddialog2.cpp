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

TournamentGridDialog2::TournamentGridDialog2(const QSqlDatabase &_database, long long _tournamentUID, QWidget *_parent)
    : QDialog(_parent),
      database(_database),
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
    qTableWidget->setHorizontalHeaderLabels(QStringList({"Спортсмен", "Регион", "Приоритет", "Разряд"}));
    qTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    qTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    qTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    qTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    qTableWidget->setFocusPolicy(Qt::NoFocus);
    QPushButton *buttonGenerate = new QPushButton("Сгенерировать сетку");
    QPushButton *buttonDelete = new QPushButton("Удалить сетку");
    QLineEdit* filterCategoriesLE = new QLineEdit;
    qCheckBox = new QCheckBox();
    qCheckBox->setText("Скрыть категории без спортсменов");
    qCheckBox->setCheckState(Qt::Checked);

    qCheckBoxBadTournGrid = new QCheckBox();
    qCheckBoxBadTournGrid->setText("Показывать только некорректные сетки");
    {
        QGridLayout *mainLayout = new QGridLayout;
        mainLayout->addWidget(filterCategoriesLE, 0, 0, 1, 2);
        mainLayout->addWidget(qCheckBox, 1, 0);
        mainLayout->addWidget(qCheckBoxBadTournGrid, 1, 1);
        mainLayout->addWidget(qComboBoxSelectCategory, 2, 0, 1, 2);
        mainLayout->addWidget(qTableWidget, 3, 0, 10, 2);
        mainLayout->addWidget(buttonDelete, 13, 0);
        mainLayout->addWidget(buttonGenerate, 13, 1);
        leftPane->setLayout(mainLayout);
    }



    QWidget *rightPane = new QWidget;
    QPushButton *buttonSave = new QPushButton("Сохранить в Excel");
    QSpinBox *widthSpinBox = new QSpinBox;
    QSpinBox *heightSpinBox = new QSpinBox;
    widthSpinBox->setMaximum(1000);
    widthSpinBox->setValue(128);
    heightSpinBox->setValue(30);


    QScrollArea *pQScrollArea = new QScrollArea;
    pRenderArea = new RenderAreaWidget(pQScrollArea, widthSpinBox->value(), heightSpinBox->value(), database);
    pQScrollArea->setWidget(pRenderArea);
    QTabWidget *qTabWidget = new QTabWidget();
    qTabWidget->addTab(pQScrollArea, "Сетка"); // TODO!
    tableGrid = new QTableWidget();
    tableGrid->setColumnCount(5);
    tableGrid->setHorizontalHeaderLabels(QStringList({"Спортсмен A", "Регион A", "Спортсмен B", "Регион B", "Уровень"}));
    tableGrid->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableGrid->setSelectionMode(QAbstractItemView::SingleSelection);
    //tableGrid->setFocusPolicy(Qt::NoFocus);
    qTabWidget->addTab(tableGrid, "Список");


    QLabel *widthQLabel = new QLabel("Ширина:");
    widthQLabel->setAlignment(Qt::AlignRight | Qt::AlignCenter);
    QLabel *heightQLabel = new QLabel("Высота:");
    heightQLabel->setAlignment(Qt::AlignRight | Qt::AlignCenter);
    {
        QGridLayout *mainLayout = new QGridLayout;

        mainLayout->addWidget(buttonSave, 0, 0);
        mainLayout->addWidget(widthQLabel, 0, 1);
        mainLayout->addWidget(widthSpinBox, 0, 2);
        mainLayout->addWidget(heightQLabel, 0, 3);
        mainLayout->addWidget(heightSpinBox, 0, 4);

        mainLayout->addWidget(qTabWidget, 1, 0, 1, 5);

        rightPane->setLayout(mainLayout);
    }


    QSplitter *splitter = new QSplitter;
    splitter->addWidget(leftPane);
    splitter->addWidget(rightPane);
    splitter->setHandleWidth(10);
    splitter->setStyleSheet("QSplitter::handle{background-color: black;}");


    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(splitter, 0, 0);
    setLayout(mainLayout);


    connect(buttonGenerate, SIGNAL(clicked(bool)), SLOT(onButtonGenerateGrid()));
    connect(widthSpinBox, SIGNAL(valueChanged(int)), pRenderArea, SLOT(widthChanged(int)));
    connect(heightSpinBox, SIGNAL(valueChanged(int)), pRenderArea, SLOT(heightChanged(int)));
    connect(qTableWidget, SIGNAL(cellClicked(int,int)), SLOT(onCellCLickedForChangePrioritet(int, int)));
    connect(buttonDelete, SIGNAL(clicked()), SLOT(onButtonDelete()));
    connect(buttonSave, SIGNAL(clicked()), pRenderArea, SLOT(onSaveInExcel()));
    connect(tableGrid, SIGNAL(cellClicked(int,int)), SLOT(onCellClickedOntableGrid(int, int)));

    fillCategoryCombobox();
    connect(qComboBoxSelectCategory, SIGNAL(activated(int)), this, SLOT(onActivatedCategory(int)));
    if (0 < qComboBoxSelectCategory->count())
        onActivatedCategory(0);

    connect(filterCategoriesLE, &QLineEdit::textChanged, [this] (const QString& filter)
    {
        fillCategoryCombobox(filter);
    });

    connect(qCheckBox, &QCheckBox::stateChanged, [this, filterCategoriesLE] ()
    {
        fillCategoryCombobox(filterCategoriesLE->text());
    });
    connect(qCheckBoxBadTournGrid, &QCheckBox::stateChanged, [this, filterCategoriesLE] ()
    {
        fillCategoryCombobox(filterCategoriesLE->text());
    });



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
                qDebug() << DBUtils::getSecondNameAndOneLetterOfName(QSqlDatabase::database(), orderUID);
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
            ;
        });

        contextMenu->exec(qTableWidget->viewport()->mapToGlobal(pos));
    });




    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);
    resize(1000, 700);
    //showMaximized();
}


// юзер выбирает категорию турнира
void TournamentGridDialog2::onActivatedCategory(int id)
{
    if (!(0 <= id && id < qComboBoxSelectCategory->count()))
    {
        qTableWidget->setRowCount(0);
        tableGrid->setRowCount(0);
        pRenderArea->slotSetTournamentCategories(0);
        return;
    }
    specialGroup = QVector<int>(4, false);
    tournamentCategories = qComboBoxSelectCategory->itemData(id, Qt::UserRole).toInt();

    pRenderArea->slotSetTournamentCategories(tournamentCategories);
    //qDebug() << __LINE__ << __PRETTY_FUNCTION__ << "tournamentCategories: " << tournamentCategories;

    QSqlQuery query("SELECT * FROM ORDERS WHERE TOURNAMENT_CATEGORY_FK = ? ORDER BY SECOND_NAME, FIRST_NAME", database);
    query.bindValue(0, tournamentCategories);

    //qDebug() << "\n" << __PRETTY_FUNCTION__  << "\n" << "tournamentCategories: " << tournamentCategories << "\n";

    qTableWidget->setRowCount(0);
    if (query.exec())
    {
        while (query.next())
        {
            QString name = query.value("SECOND_NAME").toString() + " " + query.value("FIRST_NAME").toString();
            long long idRegion = query.value("REGION_FK").toInt();
            QString region = DBUtils::getField("NAME", "REGIONS", idRegion);

            qTableWidget->setRowCount(qTableWidget->rowCount() + 1);
            QTableWidgetItem *item;

            item = new QTableWidgetItem(name);
            item->setData(Qt::UserRole, query.value("UID").toLongLong());
            qTableWidget->setItem(qTableWidget->rowCount() - 1, 0, item);

            item = new QTableWidgetItem(region);
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

// генерация турнирной сетки
void TournamentGridDialog2::onButtonGenerateGrid()
{
    //
    {
        // проверяем есть ли турнирная сетка, если есть, то задаём вопрос
        QSqlQuery query("SELECT * FROM GRID WHERE TOURNAMENT_CATEGORIES_FK = ? ", database);
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
    /**/

    {
        // удалим старую сетку
        QSqlQuery query("DELETE FROM GRID WHERE TOURNAMENT_CATEGORIES_FK = ? ", database);
        query.bindValue(0, tournamentCategories);
        if (!query.exec())
        {
            qDebug() << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
            return;
        }
    }



    QSqlDatabase::database().transaction();

    int n = qTableWidget->rowCount();
    if (n <= 0) return;
    QVector<bool> isLeaf(2);
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
    const int maxVertex = isLeaf.size() - 1;

    for (int v = maxVertex;  1 <= v; --v)
    {
        if (isLeaf[v]) continue;

        QSqlQuery query("INSERT INTO GRID VALUES (?, ?, ?, null, null)", database);
        query.bindValue(0, tournamentCategories);
        query.bindValue(1, v);
        query.bindValue(2, "true");
        if (!query.exec())
            qDebug() << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
    }


    QVector<BestFigher> bestFighters;
    QHash<int, QVector<int>> usualFighters;
    for (int row = 0; row < qTableWidget->rowCount(); ++row)
    {
        long long orderUID = qTableWidget->item(row, 0)->data(Qt::UserRole).toLongLong();
        long long region   = qTableWidget->item(row, 1)->data(Qt::UserRole).toLongLong();
        QString special_group = qTableWidget->item(row, 2)->data(Qt::DisplayRole).toString();
        if (special_group == no_special_group)
            usualFighters[region].push_back(orderUID);
        else
        {
            int priority = special_group.toInt();
            bestFighters.push_back(BestFigher(orderUID, priority, region));
            //qDebug() << __LINE__ << __PRETTY_FUNCTION__ << orderUID << " " << priority << " " << region;
        }
    }

    std::random_shuffle(bestFighters.begin(), bestFighters.end());
    qSort(bestFighters.begin(), bestFighters.end());


    QVector<bool> isUsedLeaf(maxVertex + 1);
    QVector<long long> regionLeaf(maxVertex + 1);
    if (!bestFighters.isEmpty())
    {
        QVector<QString> pref;
        if (bestFighters.size() == 1) pref << "1";
        if (bestFighters.size() == 2) pref << "11" << "10";
        if (bestFighters.size() == 3) pref << "11" << "101" << "100";
        if (bestFighters.size() == 4) pref << "111" << "110" << "101" << "100";
        for (int i = 0; i < bestFighters.size(); ++i)
        {
            int v = pref[i].toInt(0, 2);
            while (!isLeaf[v]) v = 2 * v + 1;
            //qDebug() << v;

            isUsedLeaf[v] = true;
            regionLeaf[v] = DBUtils::getField("REGION_FK", "ORDERS", bestFighters[i].orderUID).toLongLong();

            QSqlQuery query("INSERT INTO GRID VALUES (?, ?, ?, ?, null)", database);
            query.bindValue(0, tournamentCategories);
            query.bindValue(1, v);
            query.bindValue(2, "false");
            query.bindValue(3, bestFighters[i].orderUID);
            if (!query.exec())
                qDebug() << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
        }
    }

    struct RegionRandomOrders
    {
        int region;
        int random_number;
        QVector<int> orderUIDs;

        bool operator < (const RegionRandomOrders& a) const
        {
            if (orderUIDs.size() != a.orderUIDs.size()) return orderUIDs.size() > a.orderUIDs.size();
            if (random_number    != a.random_number   ) return random_number    < a.random_number;
            return region < a.region;
        }
    };


    std::set<RegionRandomOrders> notUsedFighters; // всех простых бойцов из another  кидаем в notUsedFighters
    for (auto it = usualFighters.begin(); it != usualFighters.end(); ++it)
    {
        std::random_shuffle(it.value().begin(), it.value().end());
        notUsedFighters.insert(RegionRandomOrders({it.key(), rand(), it.value()}));
    }

    // находим пару для особых бойцов
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
                orderUID_V = b.orderUIDs.back(); b.orderUIDs.pop_back();

                if (!b.orderUIDs.empty())
                {
                    b.random_number = rand();
                    notUsedFighters.insert(b);
                }
            }
            else
            {
                orderUID_V = a.orderUIDs.back(); a.orderUIDs.pop_back();
            }

            if (!a.orderUIDs.empty())
            {
                a.random_number = rand();
                notUsedFighters.insert(a);
            }

            DBUtils::insertLeafOfGrid(tournamentCategories, v, orderUID_V);
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
            orderUID0 = a.orderUIDs.back(); a.orderUIDs.pop_back();
            if (notUsedFighters.empty()) // соединяем двух чуваков с одного региона; какая жалость
            {
                orderUID1 = a.orderUIDs.back(); a.orderUIDs.pop_back();
            }
            else
            {
                RegionRandomOrders b = *notUsedFighters.begin();
                notUsedFighters.erase(notUsedFighters.begin());
                orderUID1 = b.orderUIDs.back(); b.orderUIDs.pop_back();

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

        DBUtils::insertLeafOfGrid(tournamentCategories, pair.first , orderUID0);
        DBUtils::insertLeafOfGrid(tournamentCategories, pair.second, orderUID1);

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
            long long orderUID = b.orderUIDs.back();
            b.orderUIDs.pop_back();

            if (!b.orderUIDs.empty())
            {
                b.random_number = rand();
                notUsedFighters.insert(b);
            }

            DBUtils::insertLeafOfGrid(tournamentCategories, v, orderUID);
            break;
        }
    }

    assert (notUsedFighters.empty());
    QSqlDatabase::database().commit();

    pRenderArea->repaint();
    fillTableGrid();

}

void TournamentGridDialog2::onButtonDelete()
{
    {
        // проверяем есть ли турнирная сетка, если есть, то задаём вопрос
        QSqlQuery query("SELECT * FROM GRID WHERE TOURNAMENT_CATEGORIES_FK = ? ", database);
        query.bindValue(0, tournamentCategories);
        if (query.exec())
        {
            if (query.next())
            {
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, "?", "Удалить сетку?", QMessageBox::Yes | QMessageBox::No);
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
    QSqlQuery query("DELETE FROM GRID WHERE TOURNAMENT_CATEGORIES_FK = ?", database);
    query.bindValue(0, tournamentCategories);
    if (!query.exec())
        qDebug() << __PRETTY_FUNCTION__ << " " << query.lastError().text() << " " << query.lastQuery();
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
    tableGrid->setRowCount(0);
    for (DBUtils::NodeOfTournirGrid node : nodes)
    {
        if ((node.v & 1) == 0) continue;

        tableGrid->setRowCount(tableGrid->rowCount() + 1);

        QTableWidgetItem *item;

        item = new QTableWidgetItem(node.name);
        item->setData(Qt::UserRole, node.v);
        tableGrid->setItem(tableGrid->rowCount() - 1, 0, item);

        item = new QTableWidgetItem(node.region);
        item->setData(Qt::UserRole, node.v);
        tableGrid->setItem(tableGrid->rowCount() - 1, 1, item);

        item = new QTableWidgetItem();
        item->setData(Qt::UserRole, 0);
        tableGrid->setItem(tableGrid->rowCount() - 1, 2, item);
        item = new QTableWidgetItem();
        item->setData(Qt::UserRole, 0);
        tableGrid->setItem(tableGrid->rowCount() - 1, 3, item);
        for (DBUtils::NodeOfTournirGrid node2 : nodes)
        {
            if (node2.v != (node.v ^ 1)) continue;
            item = new QTableWidgetItem(node2.name);
            item->setData(Qt::UserRole, node2.v);
            tableGrid->setItem(tableGrid->rowCount() - 1, 2, item);
            item = new QTableWidgetItem(node2.region);
            item->setData(Qt::UserRole, node2.v);
            tableGrid->setItem(tableGrid->rowCount() - 1, 3, item);
            break;
        }

        item = new QTableWidgetItem(RenderAreaWidget::getNameOfLevel(node.v / 2));
        tableGrid->setItem(tableGrid->rowCount() - 1, 4, item);
    }
    tableGrid->resizeColumnsToContents();
    tableGrid->clearSelection();
    tableGrid->clearFocus();
}

void TournamentGridDialog2::fillCategoryCombobox(QString filterStr)
{
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
            bool haveSomeGridOrSomeOrders = 0 < mansFromOrder.size();
            for(DBUtils::NodeOfTournirGrid it : DBUtils::getNodes(categoryUID.toLongLong()))
            {
                haveSomeGridOrSomeOrders = true;
                if (0 < it.UID)
                    mansFromGrig.insert(it.UID);
            }

            if (
                ( qCheckBoxBadTournGrid->isChecked() && std::vector<long long>(mansFromOrder.begin(), mansFromOrder.end()) != std::vector<long long>(mansFromGrig.begin(), mansFromGrig.end()))
                ||
                (!qCheckBoxBadTournGrid->isChecked() && (!qCheckBox->isChecked() || (qCheckBox->isChecked() && haveSomeGridOrSomeOrders)))
            ){
                QListWidgetItem* item = new QListWidgetItem();
                item->setData(Qt::DisplayRole, categoryName);
                item->setData(Qt::UserRole, categoryUID);

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
    if (tableGrid->item(row, column)->data(Qt::UserRole).toInt() <= 0)
    {
        tableGrid->clearSelection();
        tableGrid->clearFocus();
        selectedRowOfRableGrid = -1;
        selectedColumnOfRableGrid = -1;
        return;
    }

    if (selectedRowOfRableGrid == -1 || selectedColumnOfRableGrid == -1)
    {
        selectedRowOfRableGrid = row;
        selectedColumnOfRableGrid = column;
        QModelIndex i = tableGrid->model()->index(row, column ^ 1);
        tableGrid->selectionModel()->select(i, QItemSelectionModel::Select);
    }
    else
    {
        int vertexA = tableGrid->item(row, column)->data(Qt::UserRole).toInt();
        int vertexB = tableGrid->item(selectedRowOfRableGrid, selectedColumnOfRableGrid)->data(Qt::UserRole).toInt();
        //qDebug() << vertexA << vertexB;
        if (0 < vertexA && 0 < vertexB)
        {
            DBUtils::swapNodesOfGrid(tournamentCategories, vertexA, vertexB);
            //qDebug() << "DONE!";
        }
        fillTableGrid();

        tableGrid->clearSelection();
        tableGrid->clearFocus();
        selectedRowOfRableGrid = -1;
        selectedColumnOfRableGrid = -1;
    }

}










