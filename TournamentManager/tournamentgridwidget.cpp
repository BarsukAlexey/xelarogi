#include "tournamentgridwidget.h"
#include "ui_tournamentgridwidget.h"

TournamentGridWidget::TournamentGridWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TournamentGridWidget)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &TournamentGridWidget::onPushButtonClicked);

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
    update();

    connect(ui->pushButton_2, &QPushButton::clicked, [this] ()
    {
       mRecW = ui->spinBox->value();
       mRecH = ui->spinBox_2->value();
       repaint();
    });

}

TournamentGridWidget::~TournamentGridWidget()
{
    delete ui;
}

void TournamentGridWidget::update()
{
    mLevels = TournamentManager::getTournamentRectangles(TournamentManager::getSavedRecords());
    mBorders = TournamentManager::getTournamentBorders(mLevels);

    mClickCount = 0;
}

void TournamentGridWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QColor recColor = QColor(0, 0, 0);

    double shiftX = 0.0;
    double shiftY = 50.0;
    QPainter p(this);
    for (const auto& level : mLevels)
    {
        for (const TournamentManager::Point& point : level)
        {
            QRect rect = QRect(point.x*mRecW + point.x*shiftX, point.y*mRecH + shiftY, mRecW, mRecH);
            p.setPen(recColor);
            p.fillRect(rect, point.isClicked ? QBrush(Qt::green) : QBrush(Qt::gray));
            p.drawRect(rect);
            p.setPen(Qt::yellow);
            p.drawText(rect, Qt::AlignHCenter | Qt::AlignVCenter, point.text);
        }
    }
    for (const TournamentManager::Border& border : mBorders)
    {
        QRect rect = QRect(border.x*mRecW + border.x*shiftX, border.y*mRecH + shiftY, mRecW, mRecH);
        p.setPen(recColor);
        if (border.l)
            p.drawLine(rect.x(), rect.y(), rect.x(), rect.y() + mRecH);
        if (border.t)
            p.drawLine(rect.x(), rect.y(), rect.x() + mRecW, rect.y());
        if (border.r)
            p.drawLine(rect.x() + mRecW, rect.y(), rect.x() + mRecW, rect.y() + mRecH);
        if (border.b)
            p.drawLine(rect.x(), rect.y() + mRecH, rect.x() + mRecW, rect.y() + mRecH);
    }
}

void TournamentGridWidget::mousePressEvent(QMouseEvent *event)
{
    double shiftX = 0.0;
    double shiftY = 50.0;

    if (event->button() == Qt::LeftButton)
    {
        for (QVector<TournamentManager::Point>& level : mLevels)
        {
            for (TournamentManager::Point& point : level)
            {
                QRect rect = QRect(point.x*mRecW + point.x*shiftX, point.y*mRecH + shiftY, mRecW, mRecH);
                if (event->x() >= rect.left() && event->x() <= rect.right())
                {
                    if (event->y() >= rect.top() && event->y() <= rect.bottom())
                    {
                        point.isClicked = !point.isClicked;
                        if (point.isClicked)    mClickCount++;
                        else                    mClickCount--;

                        if (mClickCount >= 2)
                        {
                            int levelIndexes[2] = {0, 0};
                            int pointIndexes[2] = {0, 0};
                            int levelIndex = 0;
                            int pointIndex = 0;
                            for (QVector<TournamentManager::Point>& level : mLevels)
                            {
                                for (TournamentManager::Point& point : level)
                                {
                                    if (point.isClicked && mClickCount >= 2)
                                    {
                                        levelIndexes[0] = levelIndex;
                                        pointIndexes[0] = pointIndex;
                                        mClickCount--;

                                        point.isClicked = false;
                                    }
                                    else if (point.isClicked && mClickCount == 1)
                                    {
                                        levelIndexes[1] = levelIndex;
                                        pointIndexes[1] = pointIndex;
                                        mClickCount--;

                                        point.isClicked = false;
                                    }
                                    ++pointIndex;
                                }
                                ++levelIndex;
                                pointIndex = 0;
                            }

                            TournamentManager::Point &p1 = mLevels[levelIndexes[0]][pointIndexes[0]];
                            TournamentManager::Point &p2 = mLevels[levelIndexes[1]][pointIndexes[1]];

                            qSwap(p1.text, p2.text);

                            mClickCount = 0;
                        }
                    }
                }
            }
        }
        repaint();
    }
    else if (event->button() == Qt::RightButton)
    {
        for (QVector<TournamentManager::Point>& level : mLevels)
        {
            for (TournamentManager::Point& point : level)
            {
                QRect rect = QRect(point.x*mRecW + point.x*shiftX, point.y*mRecH + shiftY, mRecW, mRecH);
                if (event->x() >= rect.left() && event->x() <= rect.right())
                {
                    if (event->y() >= rect.top() && event->y() <= rect.bottom())
                    {
                        if (point.text.isEmpty())
                        {
                            point.text = "Победитель?";
                        }
                    }
                }
            }
        }
        repaint();
    }
}

void TournamentGridWidget::onPushButtonClicked()
{
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

    for (int i = 0; i < (int)mLevels.size(); i++)
    {
        for (int j = 0; j < (int)mLevels[i].size(); j++)
        {
            TournamentManager::Point p = mLevels[i][j];

            QAxObject* cell = sheet->querySubObject( "Cells( int, int )", p.y, p.x );
            cell->setProperty("Value", QVariant(p.text));
            delete cell;
        }
    }

    for (int i = 0; i < (int)mBorders.size(); i++)
    {
        TournamentManager::Point p = {mBorders[i].x, mBorders[i].y};

        QAxObject* cell = sheet->querySubObject( "Cells( int, int )", p.y, p.x );
        if (mBorders[i].l)
        {
            QAxObject *border = cell->querySubObject("Borders(xlEdgeLeft)");
            border->setProperty("LineStyle",1);
            border->setProperty("Weight",2);
            delete border;
        }
        if (mBorders[i].t)
        {
            QAxObject *border = cell->querySubObject("Borders(xlEdgeTop)");
            border->setProperty("LineStyle",1);
            border->setProperty("Weight",2);
            delete border;
        }
        if (mBorders[i].r)
        {
            QAxObject *border = cell->querySubObject("Borders(xlEdgeRight)");
            border->setProperty("LineStyle",1);
            border->setProperty("Weight",2);
            delete border;
        }
        if (mBorders[i].b)
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
