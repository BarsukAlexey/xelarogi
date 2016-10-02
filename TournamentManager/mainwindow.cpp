#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QAxObject>
#include <QAxBase>
#include <vector>

#include "formdipl.h"
#include "handbookdialog.h"
#include "tournamentgriddialog2.h"
#include "fiting_distribution.h"
#include "fighting_pairs.h"
#include "weighing_protocol.h"
#include "winner_report.h"
#include "ebnutvbazu.h"

#include "report_ministr.h"
#include "countryiconsdialog.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonValuePtr>
#include <QJsonValueRef>
#include <QJsonValueRefPtr>
#include <QVariantMap>
#include <QFileDialog>
#include <QMessageBox>
#include <QBuffer>
#include <iostream>
#include <fstream>



using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

//    while (true)
//    {
//        LoginDialog loginDialog(this);
//        if (loginDialog.exec() == QDialog::Accepted)
//        {
//            break;
//        }
//        if (!LoginDialog::mOkBtnClicked)
//        {
//            exit(0);
//        }
//        else
//        {
//            QMessageBox::warning(this, "Неудачная попытка авторизации", "Логи или пароль введены неверно");
//        }
//    }


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
        HandbookDialog handbookDlg(QString("COUNTRIES"), QString("Страны"), m_database, this, {"UID", "FLAG"});
        handbookDlg.exec();
    });

    connect(ui->regionAction, &QAction::triggered, [this] () {
        HandbookDialog handbookDlg(QString("REGIONS"), QString("Регионы"), m_database, this, {"UID", "FLAG"});
        handbookDlg.exec();
    });

    connect(ui->ateAction, &QAction::triggered, [this] () {
        HandbookDialog handbookDlg(QString("REGION_UNITS"), QString("АТЕ"), m_database, this, {"UID", "FLAG"});
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
        updateTournamentTreeWidget();
    });

    connect(ui->tournamentCategoryAction, &QAction::triggered, [this] () {
        HandbookDialog handbookDlg(QString("TOURNAMENT_CATEGORIES"), QString("Категории турнира"), m_database, this, {"UID"});
        handbookDlg.exec();
    });

    connect(ui->clubAction, &QAction::triggered, [this] () {
        HandbookDialog handbookDlg(QString("CLUBS"), QString("Клубы"), m_database, this, {"UID", "FLAG"});
        handbookDlg.exec();
    });

    connect(ui->coachAction, &QAction::triggered, [this] () {
        HandbookDialog handbookDlg(QString("COACHS"), QString("Тренерский состав"), m_database, this, {"UID"});
        handbookDlg.exec();
    });

    connect(ui->orderAction, &QAction::triggered, [this] () {
        HandbookDialog handbookDlg(QString("ORDERS"), QString("Заявки"), m_database, this,
        {"UID"});
        handbookDlg.exec();
    });

    connect(ui->actionAgeCategory, &QAction::triggered, [this] () {
        HandbookDialog handbookDlg(QString("AGE_CATEGORIES"), QString("Возрастные категории"), m_database, this,
        {"UID"});
        handbookDlg.exec();
    });


    connect(ui->trophyBtnImage, &QPushButton::clicked, [this]()
    {
        FormDipl * wdg = new FormDipl(ui->tournamentUidLabel->text().toLongLong());
        wdg->showMaximized();
    });

    connectButtons();
    updateTournamentTreeWidget();

    ui->tournamentUidLabel->setVisible(false);

    //

//    QVector<std::pair<long long, QString>> vect;
//    {
//        QSqlQuery query("SELECT * FROM TOURNAMENT_CATEGORIES WHERE TOURNAMENT_FK = ?");
//        query.addBindValue(21);
//        if (query.exec())
//        {
//            while (query.next())
//            {
//                qlonglong uid = query.value("UID").toLongLong();
//                QString str = query.value("NAME").toString()
//                              .replace("кг.", "kg.")
//                              .replace("лет", "years")
//                              .replace("свыше ", "+")
//                              .replace("+ ", "+")
//                              .replace("до", "-")
//                              .replace("- ", "-")
//                              ;
//                qDebug() << uid << str;
//                vect << std::make_pair(uid, str);
//            }
//        }
//    }
//    {
//        for (std::pair<long long, QString> p : vect)
//        {
//            QSqlQuery query("UPDATE TOURNAMENT_CATEGORIES "
//                            "SET NAME = ? "
//                            "WHERE UID = ?");
//            query.addBindValue(p.second);
//            query.addBindValue(p.first);
//            query.exec();
//        }
//    }
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


void MainWindow::updateTournamentTreeWidget()
{
    ui->tournamentTreeWidget->clear();
    ui->tournamentTreeWidget->setColumnCount(1);
    ui->tournamentTreeWidget->setHeaderLabels({"Турнир"});

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
            QDate beginDate = QDate::fromString(query.value("DATE_BEGIN").toString(),"yyyy-MM-dd");

            int year = beginDate.year();
            if (year != currentYear)
            {
                currentYear = year;
            }

            QTreeWidgetItem* item = new QTreeWidgetItem({name});
            item->setData(0, Qt::UserRole, uid);
            item->setData(1, Qt::UserRole, uid);

            items[currentYear].push_back(item);
        }

        for (auto pair : items)
        {
            int year = pair.first;
            QTreeWidgetItem* topLevel = new QTreeWidgetItem({QString::number(year) + " год", ""});
            for (QTreeWidgetItem* item : items[year])
            {
                topLevel->addChild(item);
            }
            ui->tournamentTreeWidget->addTopLevelItem(topLevel);
        }
        for (int i = 0; i <ui->tournamentTreeWidget->model()->rowCount(); ++i)
        {
            QModelIndex localIndex = ui->tournamentTreeWidget->model()->index(i, 0);
            ui->tournamentTreeWidget->setExpanded(localIndex, true);
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


        connect(menu.addAction("Добавить..."), &QAction::triggered, [this, pos] ()
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
    connect(ui->createOrdersBtn, &QPushButton::clicked, [this] ()
    {
        this->hide();
        long long tournamentUID = ui->tournamentUidLabel->text().toLongLong();
        CreateTournamentOrdersDialog dlg(m_database, tournamentUID, 0);
        dlg.showMaximized();
        dlg.exec();
        this->show();
    });

    connect(ui->createTournamentCategoriesBtn, &QPushButton::clicked, [this] ()
    {
        this->hide();
        long long tournamentUID = ui->tournamentUidLabel->text().toLongLong();
        CreateTournamentCategoriesDialog dlg(tournamentUID, 0);
        dlg.showMaximized();
        dlg.exec();
        this->show();
    });

    connect(ui->trophyBtn, &QPushButton::clicked, [this] ()
    {
        TrophyGeneratorSettingsDialog dlg(this);
        dlg.exec();
        if (dlg.result() == QDialog::Accepted)
        {
            long long tournamentUID = ui->tournamentUidLabel->text().toLongLong();
            TrophyGenerator trophyGenerator(tournamentUID);
        }
    });

    connect(ui->pushButton_Flag, &QPushButton::clicked, [this] (){
        long long tournamentUID = ui->tournamentUidLabel->text().toLongLong();
        CountryIconsDialog dlg (tournamentUID);
        dlg.exec();
    });

    /*
    connect(ui->testClearBtn, &QPushButton::clicked, [this]()
    {
        QSqlQuery query;

        if (!query.prepare("DELETE FROM SEXES WHERE NAME IS NULL OR NAME LIKE ''"))
            qDebug() << query.lastError().text();
        if (!query.exec())
            qDebug() << query.lastError().text();
        query.clear();

        if (!query.prepare("DELETE FROM TYPES WHERE NAME IS NULL OR NAME LIKE ''"))
            qDebug() << query.lastError().text();
        if (!query.exec())
            qDebug() << query.lastError().text();
        query.clear();

        if (!query.prepare("DELETE FROM SPORT_CATEGORIES WHERE NAME IS NULL OR NAME LIKE ''"))
            qDebug() << query.lastError().text();
        if (!query.exec())
            qDebug() << query.lastError().text();
        query.clear();

        if (!query.prepare("DELETE FROM TOURNAMENT_CATEGORIES WHERE NAME IS NULL OR NAME LIKE ''"))
            qDebug() << query.lastError().text();
        if (!query.exec())
            qDebug() << query.lastError().text();
        query.clear();

        if (!query.prepare("DELETE FROM TOURNAMENTS WHERE NAME IS NULL OR NAME LIKE ''"))
            qDebug() << query.lastError().text();
        if (!query.exec())
            qDebug() << query.lastError().text();
        query.clear();

        if (!query.prepare("DELETE FROM ORDERS WHERE REGION_FK IS NULL OR COUNTRY_FK IS NULL OR REGION_UNIT_FK IS NULL OR TYPE_FK IS NULL OR SEX_FK IS NULL OR TOURNAMENT_CATEGORY_FK IS NULL"))
            qDebug() << query.lastError().text();
        if (!query.exec()) // лучше
            qDebug() << query.lastError().text();
        query.clear();
    });
    */
}


void MainWindow::on_pushButtonGrid_clicked()
{
    this->hide();
    long long routnamentUID = ui->tournamentUidLabel->text().toLongLong();
    qDebug() << "routnamentUID: " << routnamentUID;
    TournamentGridDialog2 dialog("full", routnamentUID, 0);
    dialog.showMaximized();
    dialog.exec();
    this->show();
}

void MainWindow::on_pushButtonFightinDistribution_clicked()
{
    long long routnamentUID = ui->tournamentUidLabel->text().toLongLong();
    qDebug() << "routnamentUID: " << routnamentUID;
    FitingDistribution dlg(routnamentUID);
}

void MainWindow::on_pushButtonPair_clicked()
{
    this->hide();
    long long routnamentUID = ui->tournamentUidLabel->text().toLongLong();
    qDebug() << "routnamentUID: " << routnamentUID;
    FightingPairs dialog(routnamentUID, 0);
    dialog.exec();
    this->show();
}

void MainWindow::on_pushButtonProtokolVzveshinanya_clicked()
{
    long long routnamentUID = ui->tournamentUidLabel->text().toLongLong();
    qDebug() << "routnamentUID: " << routnamentUID;
    WeighingProtocol(routnamentUID, this);
}

void MainWindow::on_pushButtonWinnerReport_clicked()
{
    long long routnamentUID = ui->tournamentUidLabel->text().toLongLong();
    qDebug() << "routnamentUID: " << routnamentUID;
    WinnerReport(routnamentUID, this);
}

void MainWindow::on_pushButtonLoadWinner_clicked()
{
    QString openFileName = QFileDialog::getOpenFileName(this);
    if (openFileName.isEmpty())
        return;

    QFile file(openFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(this, ". . .", "Не возможно откыть файл", QMessageBox::Yes);
        return;
    }
    QJsonDocument d = QJsonDocument::fromJson(QString(file.readAll()).toUtf8());
    file.close();


    int okCount = 0;
    int countSame = 0;
    QStringList errorMessage;
    QJsonArray array = d.array();
    for (int i = 0; i < array.size(); ++i)
    {
        QJsonObject object = array[i].toObject();
        int TOURNAMENT_CATEGORIES_FK = object["TOURNAMENT_CATEGORIES_FK"].toInt();
        int VERTEX         = object["VERTEX"].toInt();
        int orderUID       = object["orderUID"].toInt();
        int orderUID_left  = object["orderUID_left"].toInt();
        int orderUID_right = object["orderUID_right"].toInt();

        QString result = object["result"].toString();


        //qDebug() << TOURNAMENT_CATEGORIES_FK << VERTEX << orderUID;

        QVector<DBUtils::NodeOfTournirGrid> nodes = DBUtils::getNodes(TOURNAMENT_CATEGORIES_FK);


        if (nodes.size() <= 2 * VERTEX + 1 - 1)
        {
            errorMessage +=
                    "Не возможно загрузть результаты для " + DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", TOURNAMENT_CATEGORIES_FK) + "\n"
                    "Пара: " + DBUtils::getSecondNameAndFirstName(orderUID_left) + " VS " + DBUtils::getSecondNameAndFirstName(orderUID_right) + "\n"
                    "Так как сетка была изменена или удалена\n";
            continue;
        }

        if (orderUID_left != nodes[2 * VERTEX + 1 - 1].UID && orderUID_right != nodes[2 * VERTEX - 1].UID){
            errorMessage +=
                    "Не возможно загрузть результаты для " + DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", TOURNAMENT_CATEGORIES_FK) + "\n"
                    "Пара: " + DBUtils::getSecondNameAndFirstName(orderUID_left) + " VS " + DBUtils::getSecondNameAndFirstName(orderUID_right) + "\n"
                    "Так как сетка изменилась\n";
            continue;
        }

        if (0 < nodes[VERTEX - 1].UID)
        {
            if (0 < orderUID && orderUID != nodes[VERTEX - 1].UID)
                errorMessage +=
                        "Не возможно загрузть результаты для " + DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", TOURNAMENT_CATEGORIES_FK) + "\n"
                        "Пара: " + DBUtils::getSecondNameAndFirstName(orderUID_left) + " VS " + DBUtils::getSecondNameAndFirstName(orderUID_right) + "\n"
                        "Так как победитель уже занесен в турнирную сетку\n" +
                        "В программе победитель: " + DBUtils::getSecondNameAndFirstName(nodes[VERTEX - 1].UID) + "\n"
                        "A Вы пытаетесь загрузить: " + DBUtils::getSecondNameAndFirstName(orderUID) + "\n";
            else if (orderUID == nodes[VERTEX - 1].UID)
                ++countSame;
        }
        else if (0 < orderUID)
        {
            if (DBUtils::updateNodeOfGrid(TOURNAMENT_CATEGORIES_FK, VERTEX, orderUID, result))
                ++okCount;
            else
                errorMessage +=
                    "Не возможно загрузть результаты для " + DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", TOURNAMENT_CATEGORIES_FK) + "\n"
                    "Пара: " + DBUtils::getSecondNameAndFirstName(orderUID_left) + " VS " + DBUtils::getSecondNameAndFirstName(orderUID_right) + "\n"
                    "Неизвестная ошибка\n";
        }
        else if (orderUID <= 0)
        {
            errorMessage +=
                "Не возможно загрузть результаты для " + DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", TOURNAMENT_CATEGORIES_FK) + "\n"
                "Пара: " + DBUtils::getSecondNameAndFirstName(orderUID_left) + " VS " + DBUtils::getSecondNameAndFirstName(orderUID_right) + "\n"
                "Жюри не запускала эту пару на ринг\n";
        }
        else
        {
            qDebug() << "wtf";
        }
    }

    QMessageBox dlg(this);
    dlg.setText("Успешно загруженно: " + QString::number(okCount) + "\n" +
                "Уже в БД есть: " + QString::number(countSame) + "\n" +
                "Ошибок: " + QString::number(array.size() - okCount - countSame));
    dlg.exec();

    ErrorMessagesDialog dlg2(errorMessage, this);
    dlg2.exec();
}


void MainWindow::on_manda_clicked()
{
    long long routnamentUID = ui->tournamentUidLabel->text().toLongLong();
    qDebug() << "routnamentUID: " << routnamentUID;
    ReportManda d(routnamentUID);
}


void MainWindow::on_btn_report_ministr_clicked()
{
    long long routnamentUID = ui->tournamentUidLabel->text().toLongLong();
    qDebug() << "routnamentUID: " << routnamentUID;
    ReporMinistr d(routnamentUID);
}



void MainWindow::on_pushButtonAddContest_clicked()
{
    CreateTournamentDialog dlg(this);
    dlg.exec();
    updateTournamentTreeWidget();
}
