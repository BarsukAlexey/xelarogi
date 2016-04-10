#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QAxObject>
#include <QAxBase>
#include <vector>

#include "handbookdialog.h"
#include "tournamentgriddialog2.h"
#include "fiting_distribution.h"
#include "fighting_pairs.h"
#include "weighing_protocol.h"
#include "winner_report.h"
#include "ebnutvbazu.h"
#include "report_manda.h"
#include "report_ministr.h"

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


using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//    bool mTryLogin = true;
//    while (mTryLogin)
//    {
//        LoginDialog loginDialog(this);
//        if (loginDialog.exec() == QDialog::Accepted)
//        {
//            break;
//        }
//        mTryLogin = LoginDialog::mOkBtnClicked;
//        if (!mTryLogin)
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
        updateTournamentTreeWidget();
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
        {"UID"});
        handbookDlg.exec();
    });

    connect(ui->actionAgeCategory, &QAction::triggered, [this] () {
        HandbookDialog handbookDlg(QString("AGE_CATEGORIES"), QString("Возрастные категории"), m_database, this,
        {"UID"});
        handbookDlg.exec();
    });



    connectButtons();
    updateTournamentTreeWidget();

    ui->tournamentUidLabel->setVisible(false);
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
        dlg.exec();
        this->show();
    });

    connect(ui->createTournamentCategoriesBtn, &QPushButton::clicked, [this] ()
    {
        this->hide();
        long long tournamentUID = ui->tournamentUidLabel->text().toLongLong();
        CreateTournamentCategoriesDialog dlg(tournamentUID, 0);
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
}


void MainWindow::on_pushButtonGrid_clicked()
{
    this->hide();
    long long routnamentUID = ui->tournamentUidLabel->text().toLongLong();
    qDebug() << "routnamentUID: " << routnamentUID;
    TournamentGridDialog2 dialog(m_database, routnamentUID, 0);
    dialog.exec();
    this->show();
}

void MainWindow::on_pushButtonFightinDistribution_clicked()
{
    long long routnamentUID = ui->tournamentUidLabel->text().toLongLong();
    qDebug() << "routnamentUID: " << routnamentUID;
    FitingDistribution(m_database, routnamentUID);
}

void MainWindow::on_pushButtonPair_clicked()
{
    this->hide();
    long long routnamentUID = ui->tournamentUidLabel->text().toLongLong();
    qDebug() << "routnamentUID: " << routnamentUID;
    FightingPairs dialog(m_database, routnamentUID, 0);
    dialog.exec();
    this->show();
}

void MainWindow::on_pushButtonProtokolVzveshinanya_clicked()
{
    long long routnamentUID = ui->tournamentUidLabel->text().toLongLong();
    qDebug() << "routnamentUID: " << routnamentUID;
    WeighingProtocol(m_database, routnamentUID, this);
}

void MainWindow::on_pushButtonWinnerReport_clicked()
{
    long long routnamentUID = ui->tournamentUidLabel->text().toLongLong();
    qDebug() << "routnamentUID: " << routnamentUID;
    WinnerReport(m_database, routnamentUID, this);
}

void MainWindow::on_pushButtonLoadWinner_clicked()
{
    QString openFileName = QFileDialog::getOpenFileName(this);
    if (openFileName.size() == 0) return;
    //qDebug() << "openFileName: " << openFileName;

    QFile jSonFile(openFileName);
    if (!jSonFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, ". . .", "Не возможно откыть файл", QMessageBox::Yes);
        return;
    }

    QFile file;
    file.setFileName(openFileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonDocument d = QJsonDocument::fromJson(QString(file.readAll()).toUtf8());
    file.close();

    int okCount = 0;
    int errorCount = 0;
    QJsonArray array = d.array();
    for (int i = 0; i < array.size(); ++i)
    {
        QJsonObject object = array[i].toObject();
        int TOURNAMENT_CATEGORIES_FK = object["TOURNAMENT_CATEGORIES_FK"].toInt();
        int VERTEX = object["VERTEX"].toInt();
        int orderUID = object["orderUID"].toInt();
        QString result = object["result"].toString();
        qDebug() << TOURNAMENT_CATEGORIES_FK << VERTEX << orderUID;
        if (DBUtils::updateNodeOfGrid(m_database, TOURNAMENT_CATEGORIES_FK, VERTEX, orderUID, result))
        {
            okCount++;
        }
        else
        {
            ++errorCount;
        }
    }

    QMessageBox::information(this, "Результаты загрузки", "Успешно загруженно " +
                             QString::number(okCount) + " результатов боев из " +
                             QString::number(okCount + errorCount)
                             );
}






void MainWindow::on_manda_clicked()
{
    long long routnamentUID = ui->tournamentUidLabel->text().toLongLong();
    qDebug() << "routnamentUID: " << routnamentUID;
    ReportManda(m_database, routnamentUID);
}


void MainWindow::on_btn_report_ministr_clicked()
{
    long long routnamentUID = ui->tournamentUidLabel->text().toLongLong();
    qDebug() << "routnamentUID: " << routnamentUID;
    ReporMinistr d(routnamentUID);
}



void MainWindow::on_pushButton_clicked()
{
//    EbnutVBazu::setTournamentCat(ui->tournamentUidLabel->text().toLongLong());
//    qDebug() << "DONE";

    QString openFileName = QFileDialog::getOpenFileName();
    QImage image(openFileName);
//    QLabel label;
//    label.setPixmap(QPixmap::fromImage(image));
//    label.show();
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    image.save(&buffer, "PNG");
    QString iconBase64 = QString::fromLatin1(byteArray.toBase64().data());
    qDebug() << "iconBase64.length(): " << iconBase64.length();

    QSqlQuery query("INSERT INTO COUNTRIES(NAME, SHORTNAME, FLAG) VALUES(?,?,?)");
    query.addBindValue("Олала");
    query.addBindValue("Ола");
    query.addBindValue(iconBase64);
    if(!query.exec())
        qDebug() << "Fuck!";
}

void MainWindow::on_pushButton_2_clicked()
{
    EbnutVBazu::setRandomWinner();
    qDebug() << "DONE";
}


