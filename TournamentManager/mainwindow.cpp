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




    QVector<TournamentManager::InitialParticapantRecord> v;
    v.push_back({"Test1", 1, 1});
    v.push_back({"Test2", 2, 2});
    v.push_back({"Test3", 0, 3});
    v.push_back({"Test4", 0, 3});
    v.push_back({"Test5", 0, 4});
    v.push_back({"Test6", 0, 4});
    v.push_back({"Test7", 0, 4});
    v.push_back({"Test8", 0, 5});
    v.push_back({"Test9", 0, 4});
    v = TournamentManager::getTournamentInitialState(v);



    connect(ui->pushButton, &QPushButton::clicked, this, &on_pushButton_clicked);
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

    int recW = 80;
    int recH = 20;
    QColor recColor = QColor(0, 0, 0);

    QVector<QVector<TournamentManager::Point>> levels = TournamentManager::getTournamentRectangles(TournamentManager::getSavedRecords());
    QVector<TournamentManager::Border> borders = TournamentManager::getTournamentBorders(levels);
    double shiftX = 0.0;
    double shiftY = 50.0;
    QPainter p(this);
    p.setPen(recColor);
    for (const auto& level : levels)
    {
        for (const TournamentManager::Point& point : level)
        {
            QRect rect = QRect(point.x*recW + point.x*shiftX, point.y*recH + shiftY, recW, recH);
            p.fillRect(rect, QBrush(Qt::gray));
            p.drawRect(rect);
        }
    }
    for (const TournamentManager::Border& border : borders)
    {
        QRect rect = QRect(border.p.x*recW + border.p.x*shiftX, border.p.y*recH + shiftY, recW, recH);
        if (border.l)
            p.drawLine(rect.x(), rect.y(), rect.x(), rect.y() + recH);
        if (border.t)
            p.drawLine(rect.x(), rect.y(), rect.x() + recW, rect.y());
        if (border.r)
            p.drawLine(rect.x() + recW, rect.y(), rect.x() + recW, rect.y() + recH);
        if (border.b)
            p.drawLine(rect.x(), rect.y() + recH, rect.x() + recW, rect.y() + recH);
    }
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

void MainWindow::on_pushButton_clicked()
{
    QVector<QVector<TournamentManager::Point>> levels = TournamentManager::getTournamentRectangles(TournamentManager::getSavedRecords());
    QVector<TournamentManager::Border> borders = TournamentManager::getTournamentBorders(levels);


    QAxObject* excel = new QAxObject( "Excel.Application", this );
    excel->setProperty("Visible", true);
    QAxObject* workbooks = excel->querySubObject( "Workbooks" );
    QAxObject* workbook = workbooks->querySubObject( "Open(const QString&)", "D:/test_t.xlsx" );

    /*
     * workbooks->dynamicCall("Add");
//workbooks->dynamicCall("Open (const QString&)", QString("C:/test7.xls"));
QAxObject * workbook = excel.querySubObject("ActiveWorkBook");
QAxObject * worksheets = workbook->querySubObject("WorkSheets");

workbook->dynamicCall("SaveAs (const QString&)", QString("C:\test7.xls"));
workbook->dynamicCall("Close (Boolean)", false);
workbooks->dynamicCall("Open (const QString&)", QString("C:/test7.xls"));
*/

    QAxObject* sheets = workbook->querySubObject( "Sheets" );
    int sheetNumber = 1;
    QAxObject* sheet = sheets->querySubObject( "Item( int )", sheetNumber );

    for (int i = 0; i < (int)levels.size(); i++)
    {
        for (int j = 0; j < (int)levels[i].size(); j++)
        {
            TournamentManager::Point p = levels[i][j];

            QAxObject* cell = sheet->querySubObject( "Cells( int, int )", p.y, p.x );
            cell->setProperty("Value", QVariant("Text"));
            delete cell;
        }
    }

    for (int i = 0; i < (int)borders.size(); i++)
    {
        TournamentManager::Point p = borders[i].p;

        QAxObject* cell = sheet->querySubObject( "Cells( int, int )", p.y, p.x );
        if (borders[i].l)
        {
            QAxObject *border = cell->querySubObject("Borders(xlEdgeLeft)");
            border->setProperty("LineStyle",1);
            border->setProperty("Weight",2);
            delete border;
        }
        if (borders[i].t)
        {
            QAxObject *border = cell->querySubObject("Borders(xlEdgeTop)");
            border->setProperty("LineStyle",1);
            border->setProperty("Weight",2);
            delete border;
        }
        if (borders[i].r)
        {
            QAxObject *border = cell->querySubObject("Borders(xlEdgeRight)");
            border->setProperty("LineStyle",1);
            border->setProperty("Weight",2);
            delete border;
        }
        if (borders[i].b)
        {
            QAxObject *border = cell->querySubObject("Borders(xlEdgeBottom)");
            border->setProperty("LineStyle",1);
            border->setProperty("Weight",2);
            delete border;
        }
        delete cell;
    }

    /*
QAxObject *rangec = StatSheet->querySubObject( "Range(const QVariant&)",QVariant(QString("A4")));
QAxObject *razmer = rangec->querySubObject("Rows");
razmer->setProperty("RowHeight",34);
*/

    workbook->dynamicCall("Close()");
    delete sheet;
    delete sheets;
    delete workbook;
    excel->dynamicCall("Quit()");
    delete excel;
}
