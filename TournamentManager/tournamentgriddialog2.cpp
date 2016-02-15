#include "tournamentgriddialog2.h"
#include "renderareawidget.h"
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
#include <assert.h>


TournamentGridDialog2::TournamentGridDialog2(const QSqlDatabase &_database, long long _tournamentUID, QWidget *_parent)
    : QDialog(_parent),
      database(_database),
      tournamentUID(_tournamentUID)
{
    tournamentCategories = -1;
    specialGroup = QVector<int>(4, false);


    ebnutVBazyGovno(); // TODO DELETE THIS


    QWidget *leftPane = new QWidget;
    leftPane->setBackgroundRole(QPalette::Dark);
    qComboBoxSelectCategory = new QComboBox;
    qTableWidget = new QTableWidget(0, 3);
    qTableWidget->setColumnCount(3);
    qTableWidget->setHorizontalHeaderLabels(QStringList({"Спортсмен", "Регион", "Приоритет"}));
    qTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    qTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    qTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    qTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    qTableWidget->setFocusPolicy(Qt::NoFocus);
    QPushButton *buttonGenerate = new QPushButton("Сгенерировать сетку");
    QPushButton *buttonDelete = new QPushButton("Удалить сетку");
    {
        QGridLayout *mainLayout = new QGridLayout;
        mainLayout->addWidget(qComboBoxSelectCategory, 0, 0, 1, 2);
        mainLayout->addWidget(qTableWidget, 1, 0, 1, 2);
        mainLayout->addWidget(buttonDelete, 2, 0);
        mainLayout->addWidget(buttonGenerate, 2, 1);
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

        mainLayout->addWidget(pQScrollArea, 1, 0, 1, 5);

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
    resize(800, 800);

    connect(buttonGenerate, SIGNAL(clicked(bool)), SLOT(onButtonGenerateGrid()));
    connect(widthSpinBox, SIGNAL(valueChanged(int)), pRenderArea, SLOT(widthChanged(int)));
    connect(heightSpinBox, SIGNAL(valueChanged(int)), pRenderArea, SLOT(heightChanged(int)));
    connect(qTableWidget, SIGNAL(cellClicked(int,int)), SLOT(onCellCLickedForChangePrioritet(int, int)));
    connect(buttonDelete, SIGNAL(clicked()), SLOT(onButtonDelete()));
    connect(buttonSave, SIGNAL(clicked()), pRenderArea, SLOT(onSaveInExcel()));


    //заполняем qComboBoxSelectCategory категориями турнира
    QSqlQuery query("SELECT * FROM TOURNAMENT_CATEGORIES WHERE TOURNAMENT_FK = ?", database);
    query.bindValue(0, tournamentUID);
    if (query.exec())
    {
        while (query.next())
        {
            QString categoryUID = query.value("UID").toString();
            QString categoryName = query.value("NAME").toString();

            QListWidgetItem* item = new QListWidgetItem();
            item->setData(Qt::DisplayRole, categoryName);
            item->setData(Qt::UserRole, categoryUID);

            qComboBoxSelectCategory->addItem(categoryName, categoryUID);
        }
    }
    connect(qComboBoxSelectCategory, SIGNAL(activated(int)), this, SLOT(onActivatedCategory(int)));
    if (0 < qComboBoxSelectCategory->count())
        onActivatedCategory(0);


    //showMaximized();


    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);
}


// юзер выбирает категорию турнира
void TournamentGridDialog2::onActivatedCategory(int id)
{
    if (id < 0) return;
    specialGroup = QVector<int>(4, false);
    tournamentCategories = qComboBoxSelectCategory->itemData(id, Qt::UserRole).toInt();

    pRenderArea->slotSetTournamentCategories(tournamentCategories);

    QSqlQuery query("SELECT * FROM ORDERS WHERE TOURNAMENT_CATEGORY_FK = ? AND IS_WEIGHTED = ? AND IS_MEDICAL = ? AND IS_ACCREDITATED = ? AND IS_PAID = ?", database);
    query.bindValue(0, tournamentCategories);
    query.bindValue(1, "true");
    query.bindValue(2, "true");
    query.bindValue(3, "true");
    query.bindValue(4, "true");

    //qDebug() << "\n" << __PRETTY_FUNCTION__  << "\n" << "tournamentCategories: " << tournamentCategories << "\n";

    qTableWidget->setRowCount(0);
    if (query.exec())
    {
        while (query.next())
        {
            QString name = query.value("SECOND_NAME").toString() + " " + query.value("FIRST_NAME").toString();
            int idRegion = query.value("REGION_FK").toInt();
            QSqlQuery q("SELECT * FROM REGIONS WHERE UID = ?", database);
            q.bindValue(0, idRegion);
            if (!q.exec())
            {
                qDebug() << "\n" << __PRETTY_FUNCTION__ << "\n" << q.lastError().text() << "\n" << q.lastQuery() << "\n";
                continue;
            }

            q.next();
            QString region = q.value("NAME").toString();

            qTableWidget->setRowCount(qTableWidget->rowCount() + 1);
            QTableWidgetItem *item;

            item = new QTableWidgetItem(name);
            item->setData(Qt::UserRole, query.value("UID").toInt());
            qTableWidget->setItem(qTableWidget->rowCount() - 1, 0, item);

            item = new QTableWidgetItem(region);
            item->setData(Qt::UserRole, idRegion);
            qTableWidget->setItem(qTableWidget->rowCount() - 1, 1, item);

            qTableWidget->setItem(qTableWidget->rowCount() - 1, 2, new QTableWidgetItem(no_special_group));
        }
    }
    else
    {
        qDebug() << "\n" << __PRETTY_FUNCTION__ << "\n" << query.lastError().text() << "\n" << query.lastQuery() << "\n";
    }
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
            qDebug() << "\n" << __PRETTY_FUNCTION__ << "\n" << query.lastError().text() << "\n" << query.lastQuery() << "\n";
            return;
        }
    }
    {
        // удалим старую сетку
        QSqlQuery query("DELETE FROM GRID WHERE TOURNAMENT_CATEGORIES_FK = ? ", database);
        query.bindValue(0, tournamentCategories);
        if (!query.exec())
        {
            qDebug() << "\n" << __PRETTY_FUNCTION__ << "\n" << query.lastError().text() << "\n" << query.lastQuery() << "\n";
            return;
        }
    }



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

    // находим длину самого длинного пути до листа
    QVector<int> maxDistationToLeaf(maxVertex + 1);
    for (int v = maxVertex;  1 <= v; --v)
    {
        if (isLeaf[v]) continue;
        maxDistationToLeaf[v] = qMin(maxDistationToLeaf[2 * v], maxDistationToLeaf[2 * v + 1]) + 1;

        QSqlQuery query("INSERT INTO GRID VALUES (?, ?, ?, null)", database);
        query.bindValue(0, tournamentCategories);
        query.bindValue(1, v);
        query.bindValue(2, "true");
        if (!query.exec())
            qDebug() << "\n" << __PRETTY_FUNCTION__ << "\n" << query.lastError().text() << "\n" << query.lastQuery() << "\n";
    }


    QVector<BestFigher> bestFighters;
    QHash<int, QVector<int>> another;
    for (int row = 0; row < qTableWidget->rowCount(); ++row)
    {
        int orderUID = qTableWidget->item(row, 0)->data(Qt::UserRole).toInt();
        int region   = qTableWidget->item(row, 1)->data(Qt::UserRole).toInt();
        QString special_group = qTableWidget->item(row, 2)->data(Qt::DisplayRole).toString();
        if (special_group == no_special_group)
            another[region].push_back(orderUID);
        else
        {
            int priority = qTableWidget->item(row, 2)->data(Qt::DisplayRole).toInt();
            bestFighters.push_back(BestFigher(orderUID, priority, region));
            //qDebug() << __PRETTY_FUNCTION__ << orderUID << " " << priority << " " << region;
            //qDebug() << __LINE__ << orderUID << " " << priority << " " << region;
        }
    }
    srand(time(0));
    std::random_shuffle(bestFighters.begin(), bestFighters.end());
    qSort(bestFighters.begin(), bestFighters.end());


    QHash<long long, int> vertexOfBest; // vertexOfBest[orderUID] = вершина в сетке
    setInGridBestFigher(1, isLeaf, maxDistationToLeaf, bestFighters, vertexOfBest);

    QVector<int> freeLeafs; for (int i = 1; i <= maxVertex; ++i) if (isLeaf[i]) freeLeafs.push_back(i);
    for (int v : vertexOfBest.values()) freeLeafs.removeOne(v);


    struct Zalupa
    {
        int region;
        int random_number;
        QVector<int> orderUIDs;

        bool operator < (const Zalupa& a) const
        {
            if (orderUIDs.size() != a.orderUIDs.size()) return -(orderUIDs.size() - a.orderUIDs.size());
            if (random_number    != a.random_number   ) return   random_number    - a.random_number;
            return region - a.region;
        }
    };


    std::set<Zalupa> notUsedFighters; // всех простых бойцов из another  кидаем в notUsedFighters
    for (auto it = another.begin(); it != another.end(); ++it)
    {
        std::random_shuffle(it.value().begin(), it.value().end());
        notUsedFighters.insert(Zalupa({it.key(), rand(), it.value()}));
    }


    // находим пару для каждого особого бойца; если он в "на стыке слоёв" или 2 лучших бойца уже пиздятся, то ненадо этого делать
    for (const BestFigher& bestFighter : bestFighters)
    {
        int vertex = vertexOfBest[bestFighter.orderUID] ^ 1;
        if(!freeLeafs.contains(vertex))
            continue;
        freeLeafs.removeOne(vertex);

        Zalupa a = *notUsedFighters.begin();
        notUsedFighters.erase(notUsedFighters.begin());
        if (bestFighter.region == a.region && !notUsedFighters.empty()){
            Zalupa b = *notUsedFighters.begin();
            notUsedFighters.erase(notUsedFighters.begin());
            notUsedFighters.insert(a);
            a = b;
        }

        QSqlQuery query("INSERT INTO GRID VALUES (?, ?, ?, ?)", database);
        query.bindValue(0, tournamentCategories);
        query.bindValue(1, vertex);
        query.bindValue(2, "false");
        query.bindValue(3, a.orderUIDs.back());
        a.orderUIDs.pop_back();
        if (!query.exec())
            qDebug() << "\n" << __PRETTY_FUNCTION__ << "\n" << query.lastError().text() << "\n" << query.lastQuery() << "\n";

        if (!a.orderUIDs.empty())
        {
            a.random_number = rand();
            notUsedFighters.insert(a);
        }
    }

    // находим пары для остальных чуваков
    while (2 <= freeLeafs.size())
    {
        int v = freeLeafs.back();
        freeLeafs.pop_back();
        assert (freeLeafs.contains(v ^ 1));
        freeLeafs.removeOne(v ^ 1);

        long long orderUID0;
        long long orderUID1;
        {
            Zalupa a = *notUsedFighters.begin();
            notUsedFighters.erase(notUsedFighters.begin());
            if (notUsedFighters.empty()) // соединяем двух чуваков с одного региона; какая жалость
            {
                orderUID0 = a.orderUIDs.back(); a.orderUIDs.pop_back();
                orderUID1 = a.orderUIDs.back(); a.orderUIDs.pop_back();
            }
            else
            {
                Zalupa b = *notUsedFighters.begin();
                notUsedFighters.erase(notUsedFighters.begin());

                orderUID0 = a.orderUIDs.back(); a.orderUIDs.pop_back();
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
        {
            QSqlQuery query("INSERT INTO GRID VALUES (?, ?, ?, ?)", database);
            query.bindValue(0, tournamentCategories);
            query.bindValue(1, v);
            query.bindValue(2, "false");
            query.bindValue(3, orderUID0);
            if (!query.exec())
                qDebug() << "\n" << __PRETTY_FUNCTION__ << "\n" << query.lastError().text() << "\n" << query.lastQuery() << "\n";
        }
        {
            QSqlQuery query("INSERT INTO GRID VALUES (?, ?, ?, ?)", database);
            query.bindValue(0, tournamentCategories);
            query.bindValue(1, v ^ 1);     // отличается этим от предыдущего блока
            query.bindValue(2, "false");
            query.bindValue(3, orderUID1); // отличается этим от предыдущего блока
            if (!query.exec())
                qDebug() << "\n" << __PRETTY_FUNCTION__ << "\n" << query.lastError().text() << "\n" << query.lastQuery() << "\n";
        }
    }

    if  (freeLeafs.size() == 1)
    {
        int v = freeLeafs.back();
        freeLeafs.pop_back();

        Zalupa a = *notUsedFighters.begin();
        notUsedFighters.erase(notUsedFighters.begin());

        long long orderUID = a.orderUIDs.back();
        a.orderUIDs.pop_back();
        if (!a.orderUIDs.empty()) // это никогда не произойдет
        {
            a.random_number = rand();
            notUsedFighters.insert(a);
        }
        {
            QSqlQuery query("INSERT INTO GRID VALUES (?, ?, ?, ?)", database);
            query.bindValue(0, tournamentCategories);
            query.bindValue(1, v);
            query.bindValue(2, "false");
            query.bindValue(3, orderUID);
            if (!query.exec())
                qDebug() << "\n" << __PRETTY_FUNCTION__ << "\n" << query.lastError().text() << "\n" << query.lastQuery() << "\n";
        }
    }

    assert (notUsedFighters.empty());
    assert (freeLeafs.empty());


    pRenderArea->repaint();
}

void TournamentGridDialog2::onButtonDelete()
{
    QSqlQuery query("DELETE FROM GRID WHERE TOURNAMENT_CATEGORIES_FK = ?", database);
    query.bindValue(0, tournamentCategories);
    if (!query.exec())
        qDebug() << __PRETTY_FUNCTION__ << " " << query.lastError().text() << " " << query.lastQuery();
    pRenderArea->repaint();
}

void TournamentGridDialog2::setInGridBestFigher(int v, const QVector<bool>& isLeaf, const QVector<int>& distToLeaf, const QVector<TournamentGridDialog2::BestFigher>& bestFighters, QHash<long long, int>& vertexOfBest)
{
    if (isLeaf[v])
    {
        if (!bestFighters.isEmpty())
        {
            if ((bestFighters[0].priority == 1) && (v == 8 || v == 9))
            {
                QVector<int> q(123);
                q[12] = 23;
                qDebug() << bestFighters[0].orderUID << " " << bestFighters[0].priority << " " << v;
            }
            //qDebug() << bestFighters[0].orderUID << " " << bestFighters[0].priority << " " << v;


            QSqlQuery query("INSERT INTO GRID VALUES (?, ?, ?, ?)", database);
            query.bindValue(0, tournamentCategories);
            query.bindValue(1, v);
            query.bindValue(2, "false");
            query.bindValue(3, bestFighters[0].orderUID);
            if (!query.exec())
                qDebug() << "\n" << __PRETTY_FUNCTION__ << "\n" << query.lastError().text() << "\n" << query.lastQuery() << "\n";
            vertexOfBest[bestFighters[0].orderUID] = v;
        }
    }
    else if (v <= 3)
    {
        QVector<TournamentGridDialog2::BestFigher> left, right;
        if ((distToLeaf[2 * v] == distToLeaf[2 * v + 1]) && (rand() % 2 == 0))
        {
            if (0 < bestFighters.size()) right.push_back(bestFighters[0]);
            if (1 < bestFighters.size()) left .push_back(bestFighters[1]);
        }
        else
        {
            if (0 < bestFighters.size()) left .push_back(bestFighters[0]);
            if (1 < bestFighters.size()) right.push_back(bestFighters[1]);
        }

        if (2 < bestFighters.size()) left .push_back(bestFighters[2]);
        if (3 < bestFighters.size()) right.push_back(bestFighters[3]);

        setInGridBestFigher(2 * v + 1, isLeaf, distToLeaf, left        , vertexOfBest);
        setInGridBestFigher(2 * v    , isLeaf, distToLeaf, right       , vertexOfBest);
    }
    else
    {
        if ((rand() % 2 == 0) && (distToLeaf[2 * v] == distToLeaf[2 * v + 1]))
            setInGridBestFigher(2 * v    , isLeaf, distToLeaf, bestFighters, vertexOfBest);
        else
            setInGridBestFigher(2 * v + 1, isLeaf, distToLeaf, bestFighters, vertexOfBest);
    }
}

TournamentGridDialog2::~TournamentGridDialog2(){}













//
void TournamentGridDialog2::ebnutVBazyGovno()
{
    return ;
    qDebug() << "ebnutVBazyGovno";
    QSqlQuery *query;

    query = new QSqlQuery("DELETE FROM ORDERS", database);
    if (!query->exec())
        qDebug() << "\n" << __PRETTY_FUNCTION__ << "\n" << query->lastError().text() << "\n" << query->lastQuery() << "\n";
    delete query;

    query = new QSqlQuery("DELETE FROM TOURNAMENT_CATEGORIES", database);
    if (!query->exec())
        qDebug() << "\n" << __PRETTY_FUNCTION__ << "\n" << query->lastError().text() << "\n" << query->lastQuery() << "\n";
    delete query;

    query = new QSqlQuery("DELETE FROM GRID", database);
    if (!query->exec())
        qDebug() << "\n" << __PRETTY_FUNCTION__ << "\n" << query->lastError().text() << "\n" << query->lastQuery() << "\n";
    delete query;

    long long UID      = 10;
    long long UID_girl = 1000;
    int countGirl = 1;
    for(int age = 10, stepAge = 7; age <= 45; age += stepAge)
    {
        for(int weight = 30, stepWeight = 21; weight <= 100; weight += stepWeight, ++UID, ++countGirl)
        {
            query = new QSqlQuery("INSERT INTO TOURNAMENT_CATEGORIES VALUES (?, ?, ?, ?, ?, ?, 1)", database);
            QString str;
            str.sprintf("Девушки от %d до %d лет, от %d до %d кг", age, age + stepAge, weight, weight + stepWeight);
            query->bindValue(0, UID);
            query->bindValue(1,  str);
            query->bindValue(2, age);
            query->bindValue(3, age + stepAge);
            query->bindValue(4, weight);
            query->bindValue(5, weight + stepWeight);
            if (!query->exec())
                qDebug() << "\n" << __PRETTY_FUNCTION__ << "\n" << query->lastError().text() << "\n" << query->lastQuery() << "\n";
            delete query;

            for (int j = 0; j < countGirl; ++j, ++UID_girl){
                query = new QSqlQuery("INSERT INTO ORDERS VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)", database);
                query->bindValue(0, UID_girl);
                query->bindValue(1, "Name" + QString('A' + j));
                query->bindValue(2, "Second" + QString(char('A' + j)));
                query->bindValue(3, "Patr" + QString(char('A' + j)));
                query->bindValue(4, "2000-01-01");
                query->bindValue(5, "2");
                query->bindValue(6, "50");
                query->bindValue(7, "1");
                query->bindValue(8, UID);
                query->bindValue(9, "1");
                query->bindValue(10, "1");
                query->bindValue(11, "2");
                query->bindValue(12, "1");
                query->bindValue(13, "1");
                query->bindValue(14, "1");

                query->bindValue(15, "true");
                query->bindValue(16, "true");
                query->bindValue(17, "true");
                query->bindValue(18, "true");
                if (!query->exec())
                {
                    qDebug() << "\n" << __PRETTY_FUNCTION__ << "\n" << query->lastError().text() << "\n" << query->lastQuery() << "\n";
                    return;
                }
                delete query;
            }

            qDebug() << "DONE " << UID;
        }
    }
}
