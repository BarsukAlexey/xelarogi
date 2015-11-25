#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include "handbookdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName("./kickboxing.db");

    if (m_database.open()) {
        qDebug() << "opened";
    }
    else  {
        qDebug() << m_database.lastError().text();
        return;
    }


    connect(ui->countryAction, &QAction::triggered, [this] () {
          HandbookDialog handbookDlg(QString("COUNTRIES"), QString("Страны"), m_database, this);
          handbookDlg.exec();
    });

    connect(ui->regionAction, &QAction::triggered, [this] () {
          HandbookDialog handbookDlg(QString("REGIONS"), QString("Регионы"), m_database, this);
          handbookDlg.exec();
    });

    connect(ui->ateAction, &QAction::triggered, [this] () {
          HandbookDialog handbookDlg(QString("REGION_UNITS"), QString("АТЕ"), m_database, this);
          handbookDlg.exec();
    });

    connect(ui->sexAction, &QAction::triggered, [this] () {
          HandbookDialog handbookDlg(QString("SEXES"), QString("Пол"), m_database, this);
          handbookDlg.exec();
    });

    connect(ui->typeAction, &QAction::triggered, [this] () {
          HandbookDialog handbookDlg(QString("TYPES"), QString("Разделы"), m_database, this);
          handbookDlg.exec();
    });

    connect(ui->sportCategoryAction, &QAction::triggered, [this] () {
          HandbookDialog handbookDlg(QString("SPORT_CATEGORIES"), QString("Спортивные разряды"), m_database, this);
          handbookDlg.exec();
    });

    connect(ui->tournamentAction, &QAction::triggered, [this] () {
          HandbookDialog handbookDlg(QString("TOURNAMENTS"), QString("Турниры"), m_database, this);
          handbookDlg.exec();
    });

    connect(ui->tournamentCategoryAction, &QAction::triggered, [this] () {
          HandbookDialog handbookDlg(QString("TOURNAMENT_CATEGORIES"), QString("Категории турнира"), m_database, this);
          handbookDlg.exec();
    });

    connect(ui->clubAction, &QAction::triggered, [this] () {
          HandbookDialog handbookDlg(QString("CLUBS"), QString("Клубы"), m_database, this);
          handbookDlg.exec();
    });

    connect(ui->coachAction, &QAction::triggered, [this] () {
          HandbookDialog handbookDlg(QString("COACHS"), QString("Тренерский состав"), m_database, this);
          handbookDlg.exec();
    });

    connect(ui->orderAction, &QAction::triggered, [this] () {
          HandbookDialog handbookDlg(QString("ORDERS"), QString("Заявки"), m_database, this);
          handbookDlg.exec();
    });
}

MainWindow::~MainWindow()
{
    if (m_database.isOpen())
        m_database.close();

    delete ui;
}
