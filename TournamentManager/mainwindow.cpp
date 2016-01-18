#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QAxObject>
#include <QAxBase>
#include <vector>

#include "handbookdialog.h"

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

    connect(ui->pushButton, &QPushButton::clicked, [this] ()
    {
        TournamentGridDialog dialog(m_database, this);
        dialog.exec();
    });

    connect(ui->pushButton_3, &QPushButton::clicked, [this] ()
    {
        ChooseTournamentDialog dialog(this);
        dialog.exec();
    });
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
