#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QAxObject>
#include <QAxBase>
#include <vector>

#include "handbookdialog.h"
#include "tournamentgriddialog2.h"
#include "fiting_distribution.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    srand(time(0));

    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName("./database/kickboxing.db");

    if (m_database.open()) {
        qDebug() << "opened";
    }
    else  {
        qDebug() << m_database.lastError().text();
        return;
    }


    connect(ui->countryAction, &QAction::triggered, [this] () {
        HandbookDialog handbookDlg(QString("COUNTRIES"), QString("Страны"), m_database, this, {"UID"});
          handbookDlg.exec();
    });

    connect(ui->regionAction, &QAction::triggered, [this] () {
          HandbookDialog handbookDlg(QString("REGIONS"), QString("Регионы"), m_database, this, {"UID"});
          handbookDlg.exec();
    });

    connect(ui->ateAction, &QAction::triggered, [this] () {
          HandbookDialog handbookDlg(QString("REGION_UNITS"), QString("АТЕ"), m_database, this, {"UID"});
          handbookDlg.exec();
    });

    connect(ui->sexAction, &QAction::triggered, [this] () {
          HandbookDialog handbookDlg(QString("SEXES"), QString("Пол"), m_database, this, {"UID"});
          handbookDlg.exec();
    });

    connect(ui->typeAction, &QAction::triggered, [this] () {
          HandbookDialog handbookDlg(QString("TYPES"), QString("Разделы"), m_database, this, {"UID"});
          handbookDlg.exec();
    });

    connect(ui->sportCategoryAction, &QAction::triggered, [this] () {
          HandbookDialog handbookDlg(QString("SPORT_CATEGORIES"), QString("Спортивные разряды"), m_database, this, {"UID"});
          handbookDlg.exec();
    });

    connect(ui->tournamentAction, &QAction::triggered, [this] () {
          HandbookDialog handbookDlg(QString("TOURNAMENTS"), QString("Турниры"), m_database, this, {"UID"});
          handbookDlg.exec();
    });

    connect(ui->tournamentCategoryAction, &QAction::triggered, [this] () {
          HandbookDialog handbookDlg(QString("TOURNAMENT_CATEGORIES"), QString("Категории турнира"), m_database, this, {"UID"});
          handbookDlg.exec();
    });

    connect(ui->clubAction, &QAction::triggered, [this] () {
          HandbookDialog handbookDlg(QString("CLUBS"), QString("Клубы"), m_database, this, {"UID"});
          handbookDlg.exec();
    });

    connect(ui->coachAction, &QAction::triggered, [this] () {
          HandbookDialog handbookDlg(QString("COACHS"), QString("Тренерский состав"), m_database, this, {"UID"});
          handbookDlg.exec();
    });

    connect(ui->orderAction, &QAction::triggered, [this] () {
          HandbookDialog handbookDlg(QString("ORDERS"), QString("Заявки"), m_database, this,
          {"IS_WEIGHTED", "IS_MEDICAL", "IS_ACCREDITATED", "IS_PAID", "COACH_FK", "CLUB_FK",
            /*"COUNTRY_FK", "REGION_FK", "REGION_UNIT_FK",*/ "UID"});
          handbookDlg.exec();
    });

    connect(ui->pushButton, &QPushButton::clicked, [this] ()
    {
        TournamentGridDialog dialog(m_database, this);
        dialog.exec();
    });

    connectButtons();
    updateTournamentTreeWidget();

    ui->tournamentUidLabel->setVisible(false);

    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::on_pushButton_2_clicked);
}

MainWindow::~MainWindow()
{
    if (m_database.isOpen())
        m_database.close();

    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);
}

void MainWindow::on_btnExcel_clicked()
{
    QAxObject* excel = new QAxObject( "Excel.Application", 0 );
    QAxObject* workbooks = excel->querySubObject( "Workbooks" );
    QAxObject* workbook = workbooks->querySubObject( "Open(const QString&)", "C:/Code/TournamentManager/test.xlsx" );


    QAxObject* sheets = workbook->querySubObject( "Sheets" );
    int sheetCount = sheets->dynamicCall("Count()").toInt();
    int sheetNumber = 1;

    QAxObject* sheet = sheets->querySubObject( "Item( int )", sheetNumber );

    // Find the cells that actually have content
    QAxObject* usedrange = sheet->querySubObject( "UsedRange");
    QAxObject * rows = usedrange->querySubObject("Rows");
    QAxObject * columns = usedrange->querySubObject("Columns");
    int intRowStart = usedrange->property("Row").toInt();
    int intColStart = usedrange->property("Column").toInt();
    int intCols = columns->property("Count").toInt();
    int intRows = rows->property("Count").toInt();

    for (int row=intRowStart ; row < intRowStart+intRows ; row++) {
        QString name = "";
        QString nameEng = "";
        QString shortNameEng2 = "";
        QString shortNameEng3 = "";
        for (int col=intColStart ; col < intColStart+intCols ; col++) {
            QAxObject* cell = sheet->querySubObject( "Cells( int, int )", row, col );
            QVariant value = cell->dynamicCall( "Value()" );
            if (value.toString().isEmpty())
                continue;

            switch (col) {
                case 1:
                    name = value.toString();
                    break;
                case 2:
                    nameEng = value.toString();
                    break;
                case 3:
                    shortNameEng2 = value.toString();
                    break;
                case 4:
                    shortNameEng3 = value.toString();
                    break;
                default:
                    break;
            }
        }
        QSqlQuery query("INSERT INTO COUNTRIES(NAME, NAME_ENG, SHORTNAME, SHORTNAME_ENG) VALUES('" + name + "','" + nameEng + "','" + shortNameEng2 + "','" + shortNameEng3 + "')", m_database);
        if (!query.exec())
            qDebug() << query.lastError().text() << query.lastQuery();
    }

    // clean up and close up
    workbook->dynamicCall("Close()");
    delete workbook;
    excel->dynamicCall("Quit()");
    delete excel;
}

void MainWindow::updateTournamentTreeWidget()
{
    ui->tournamentTreeWidget->clear();
    ui->tournamentTreeWidget->setColumnCount(2);
    ui->tournamentTreeWidget->setHeaderLabels({"Турнир", "Дата проведения"});

    ui->tournamentTreeWidget->setColumnWidth(0, 200);

    std::map<int, std::vector<QTreeWidgetItem*>, std::greater<int>> items;

    QSqlQuery query;
    query.prepare("SELECT * FROM TOURNAMENTS ORDER BY DATE_BEGIN ASC");
    int currentYear = -1000;
    if (query.exec())
    {
        while (query.next())
        {
            QString uid = query.value("UID").toString();
            QString name = query.value("NAME").toString();
            QString shortName = query.value("SHORTNAME").toString();
            QDate beginDate = QDate::fromString(query.value("DATE_BEGIN").toString(),"yyyy-MM-dd");
            QDate endDate = QDate::fromString(query.value("DATE_END").toString(),"yyyy-MM-dd");

            int year = beginDate.year();
            if (year != currentYear)
            {
                currentYear = year;
            }

            QTreeWidgetItem* item = new QTreeWidgetItem({name + " (" + shortName + ")",
                                                         QString::number(beginDate.day()) + "." + QString::number(beginDate.month()) + " - " +
                                                         QString::number(endDate.day()) + "." + QString::number(endDate.month())
                                                        });
            item->setData(0, Qt::UserRole, uid);
            item->setData(1, Qt::UserRole, uid);

            items[currentYear].push_back(item);
        }

        for (auto pair : items)
        {
            int year = pair.first;
            QTreeWidgetItem* topLevel = new QTreeWidgetItem({QString::number(year) + " год", ""});
            for (auto item : items[year])
            {
                topLevel->addChild(item);
            }
            ui->tournamentTreeWidget->addTopLevelItem(topLevel);
        }

        connect(ui->tournamentTreeWidget, &QTreeWidget::clicked, [this] (const QModelIndex& index)
        {
            if (index.parent() == QModelIndex())
            {
                ui->stackedWidget->setCurrentIndex(0);
            }
            else
            {
                QString uid = index.data(Qt::UserRole).toString();
                if (!uid.isEmpty())
                {
                    long long tournamentUID = uid.toLongLong();
                    QSqlQuery tournamentQuery;
                    tournamentQuery.prepare("SELECT * FROM TOURNAMENTS WHERE UID = ?");
                    tournamentQuery.bindValue(0, tournamentUID);
                    if (tournamentQuery.exec() && tournamentQuery.next())
                    {
                        ui->tournamentLabel->setText(tournamentQuery.value("NAME").toString());
                        ui->tournamentUidLabel->setText(QString::number(tournamentUID));
                    }
                    else
                    {
                        qDebug() << tournamentQuery.lastError().text();
                    }

                    ui->stackedWidget->setCurrentIndex(1);
                }
            }
        });
    }
    else
    {
        qDebug() << query.lastError().text();
    }

    ui->tournamentTreeWidget->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
    connect(ui->tournamentTreeWidget, &QTreeWidget::customContextMenuRequested, [this] (const QPoint& pos)
    {
        QMenu menu;

        connect(menu.addAction("Добавить"), &QAction::triggered, [this, pos] ()
        {
            CreateTournamentDialog dlg(this);
            dlg.exec();
            updateTournamentTreeWidget();
        });
        connect(menu.addAction("Удалить"), &QAction::triggered, [this, pos] ()
        {
            QModelIndex index = ui->tournamentTreeWidget->indexAt(pos);
            QString uid = index.data(Qt::UserRole).toString();
            if (uid.isEmpty() == false)
            {
                long long tournamentUID = uid.toLongLong();
                QSqlQuery query;
                query.prepare("DELETE FROM TOURNAMENTS WHERE UID = ?");
                query.bindValue(0, tournamentUID);
                if (!query.exec())
                {
                    qDebug() << query.lastError().text();
                }
                else
                {
                    updateTournamentTreeWidget();
                    ui->stackedWidget->setCurrentIndex(0);
                }
            }
        });

        menu.exec(ui->tournamentTreeWidget->viewport()->mapToGlobal(pos));
    });
}

void MainWindow::connectButtons()
{
    connect(ui->ordersAccreditationBtn, &QPushButton::clicked, [this] ()
    {
        long long tournamentUID = ui->tournamentUidLabel->text().toLongLong();
        OneFieldSetupDialog dlg(tournamentUID, "IS_ACCREDITATED", this);
        dlg.exec();
    });
    connect(ui->ordersMedicalBtn, &QPushButton::clicked, [this] ()
    {
        long long tournamentUID = ui->tournamentUidLabel->text().toLongLong();
        OneFieldSetupDialog dlg(tournamentUID, "IS_MEDICAL", this);
        dlg.exec();
    });
    connect(ui->ordersPayedBtn, &QPushButton::clicked, [this] ()
    {
        long long tournamentUID = ui->tournamentUidLabel->text().toLongLong();
        OneFieldSetupDialog dlg(tournamentUID, "IS_PAID", this);
        dlg.exec();
    });
    connect(ui->ordersWeightBtn, &QPushButton::clicked, [this] ()
    {
        long long tournamentUID = ui->tournamentUidLabel->text().toLongLong();
        OneFieldSetupDialog dlg(tournamentUID, "IS_WEIGHTED", this);
        dlg.exec();
    });
    connect(ui->createOrdersBtn, &QPushButton::clicked, [this] ()
    {
        long long tournamentUID = ui->tournamentUidLabel->text().toLongLong();
        CreateTournamentOrdersDialog dlg(m_database, tournamentUID, this,
        {"IS_WEIGHTED", "IS_MEDICAL", "IS_ACCREDITATED", "IS_PAID", "UID"});
        dlg.exec();
    });
}

void MainWindow::on_pushButton_2_clicked()
{
//    TournamentGridDialog2 d(m_database, ui->tournamentUidLabel->text().toLongLong(), this);
//    d.exec();
    //FitingDistribution dd(m_database, ui->tournamentUidLabel->text().toLongLong());
    FitingDistribution dd(m_database, 1);
}
