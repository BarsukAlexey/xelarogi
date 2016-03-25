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
#include <QDate>
#include <assert.h>
#include <string>
#include <QTabWidget>


TournamentGridDialog2::TournamentGridDialog2(const QSqlDatabase &_database, long long _tournamentUID, QWidget *_parent)
    : QDialog(_parent),
      database(_database),
      tournamentUID(_tournamentUID)
{
    tournamentCategories = -1;
    specialGroup = QVector<int>(4, false);


    //ebnutVBazyGovno(); // TODO DELETE THIS


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
    {
        QGridLayout *mainLayout = new QGridLayout;
        mainLayout->addWidget(filterCategoriesLE, 0, 0, 1, 2);
        mainLayout->addWidget(qCheckBox, 1, 0, 1, 2);
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
    qTabWidget->addTab(pQScrollArea, "Сетка");
    qTabWidget->addTab(new QLabel("Табличка"), "Список");

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
    resize(800, 800);

    connect(buttonGenerate, SIGNAL(clicked(bool)), SLOT(onButtonGenerateGrid()));
    connect(widthSpinBox, SIGNAL(valueChanged(int)), pRenderArea, SLOT(widthChanged(int)));
    connect(heightSpinBox, SIGNAL(valueChanged(int)), pRenderArea, SLOT(heightChanged(int)));
    connect(qTableWidget, SIGNAL(cellClicked(int,int)), SLOT(onCellCLickedForChangePrioritet(int, int)));
    connect(buttonDelete, SIGNAL(clicked()), SLOT(onButtonDelete()));
    connect(buttonSave, SIGNAL(clicked()), pRenderArea, SLOT(onSaveInExcel()));


    fillCategoryCombobox();
    connect(qComboBoxSelectCategory, SIGNAL(activated(int)), this, SLOT(onActivatedCategory(int)));
    if (0 < qComboBoxSelectCategory->count())
        onActivatedCategory(0);

    connect(filterCategoriesLE, &QLineEdit::textChanged, [this] (const QString& filter)
    {
        fillCategoryCombobox(filter);
    });

    showMaximized();

    connect(qCheckBox, &QCheckBox::stateChanged, [this, filterCategoriesLE] ()
    {
        fillCategoryCombobox(filterCategoriesLE->text());
    });

    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);
}

#include <QHeaderView>
// юзер выбирает категорию турнира
void TournamentGridDialog2::onActivatedCategory(int id)
{
    if (id < 0)
    {
        qTableWidget->setRowCount(0);
        return;
    }
    specialGroup = QVector<int>(4, false);
    tournamentCategories = qComboBoxSelectCategory->itemData(id, Qt::UserRole).toInt();

    pRenderArea->slotSetTournamentCategories(tournamentCategories);
    //qDebug() << __LINE__ << __PRETTY_FUNCTION__ << "tournamentCategories: " << tournamentCategories;

    QSqlQuery query("SELECT * FROM ORDERS WHERE TOURNAMENT_CATEGORY_FK = ? AND IS_VALID = ? ORDER BY SECOND_NAME, FIRST_NAME", database);
    query.bindValue(0, tournamentCategories);
    query.bindValue(1, 1);

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
        qDebug() << "\n" << __PRETTY_FUNCTION__ << "\n" << query.lastError().text() << "\n" << query.lastQuery() << "\n";
    }

    qTableWidget->resizeColumnsToContents();
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

        QSqlQuery query("INSERT INTO GRID VALUES (?, ?, ?, null, null)", database);
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

        QSqlQuery query("INSERT INTO GRID VALUES (?, ?, ?, ?, null)", database);
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
            QSqlQuery query("INSERT INTO GRID VALUES (?, ?, ?, ?, null)", database);
            query.bindValue(0, tournamentCategories);
            query.bindValue(1, v);
            query.bindValue(2, "false");
            query.bindValue(3, orderUID0);
            if (!query.exec())
                qDebug() << "\n" << __PRETTY_FUNCTION__ << "\n" << query.lastError().text() << "\n" << query.lastQuery() << "\n";
        }
        {
            QSqlQuery query("INSERT INTO GRID VALUES (?, ?, ?, ?, null)", database);
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
            QSqlQuery query("INSERT INTO GRID VALUES (?, ?, ?, ?, null)", database);
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


            QSqlQuery query("INSERT INTO GRID VALUES (?, ?, ?, ?, null)", database);
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
        // TODO ЗДЕСЬ ПЛОХАЯ БАГА. УЧИТЫВАЙ  КОЛИЧЕСТВО СВОБОДНЫХ ВЕРШИН или ЛИСТОВ
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

        if (2 < bestFighters.size()) {
            if (isLeaf[2 * v + 1]) // сработает только когда у нас 3 участника
                right.push_back(bestFighters[2]);
            else
                left.push_back(bestFighters[2]);
        }
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
    if (query.exec())
    {
        while (query.next())
        {
            QString categoryUID = query.value("UID").toString();
            QString categoryName = query.value("NAME").toString();

            int countMansInThisCategory = 228;
            QSqlQuery queryCount("SELECT COUNT(*) AS CNT FROM ORDERS WHERE TOURNAMENT_CATEGORY_FK = ? ");
            queryCount.bindValue(0, categoryUID);
            if (!queryCount.exec() || !queryCount.next())
                qDebug() << __PRETTY_FUNCTION__ << queryCount.lastError() << queryCount.lastQuery();
            else
                countMansInThisCategory = queryCount.value("CNT").toInt();

            if (!qCheckBox->isChecked() || qCheckBox->isChecked() && 0 < countMansInThisCategory)
            {
                QListWidgetItem* item = new QListWidgetItem();
                item->setData(Qt::DisplayRole, categoryName);
                item->setData(Qt::UserRole, categoryUID);

                qComboBoxSelectCategory->addItem(categoryName, categoryUID);
            }
        }
    }

    if (0 < qComboBoxSelectCategory->count())
        onActivatedCategory(0);
}










