#include "renderareawidget.h"

#include <QPainter>
#include <QPaintEvent>
#include <QVector>
#include <QRect>
#include <QDebug>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QTime>
#include <QtAlgorithms>
#include <QSqlQuery>
#include <QSqlError>
#include <QAxObject>
#include <QAxBase>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QAxObject>
#include <QAxBase>
#include <QDebug>
#include <QAxObject>
#include <QAxWidget>

//#include "QVariant"


RenderAreaWidget::RenderAreaWidget(QWidget *parent, int widthCell, int heightCell, const QSqlDatabase &_database)
    : QWidget(parent),
      database(_database)
{
    tournamentCategories = -1;
    countRows = 0;
    countColumns = 0;
    this->widthCell = widthCell;
    this->heightCell = heightCell;
    setNormalSize();
}

int RenderAreaWidget::log2(int x)
{
    int ans = 0;
    while (x >>= 1) ++ans;
    return ans;
}

QPoint RenderAreaWidget::getCell(int v)
{
    QPoint p;
    p.setY(countColumns - log2(v) - 1);
    p.setX( (1 << (p.y() + 1)) * ((1 << (countColumns - p.y())) - 1 - v) + (1 << p.y()) - 1);
    return p;
}

long long RenderAreaWidget::getTournamentUID() const
{
    long long tournamentUID = -1;
    QSqlQuery query;
    if (!query.prepare("SELECT * FROM TOURNAMENT_CATEGORIES WHERE UID = ?"))
        qDebug() << query.lastError().text();
    query.bindValue(0, tournamentCategories);
    if (query.exec() && query.next())
    {
        tournamentUID = query.value("TOURNAMENT_FK").toLongLong();
    }
    else
    {
        qDebug() << query.lastError().text();
    }

    return tournamentUID;
}

QString RenderAreaWidget::getCategoryName() const
{
    QString name = "";
    QSqlQuery query;
    if (!query.prepare("SELECT NAME FROM TOURNAMENT_CATEGORIES WHERE UID = ?"))
        qDebug() << query.lastError().text();
    query.bindValue(0, tournamentCategories);
    if (query.exec() && query.next())
    {
        name = query.value("NAME").toString();
    }
    else
    {
        qDebug() << query.lastError().text();
    }

    return name;
}

void RenderAreaWidget::paintEvent(QPaintEvent* )
{
    //qDebug() << __PRETTY_FUNCTION__ << " " << QDateTime::currentDateTime();
    //return;

    QPainter painter(this);

    QVector<DBUtils::NodeOfTournirGrid> nodes = DBUtils::getNodes(database, tournamentCategories);
    if (nodes.empty()) return;
    qSort(nodes);

    //countColumns = qMax(countColumns, log2(nodes.last().v) + 1);
    countColumns = log2(nodes.last().v) + 1;
    countRows = 2 * (1 << (countColumns - 1)) - 1;
    setNormalSize();

    for (const DBUtils::NodeOfTournirGrid& node : nodes)
    {
        QPoint cell = getCell(node.v);
        paintRect(cell.x(), cell.y(), painter, node);
        for (int child : {2 * node.v, 2 * node.v + 1})
        {
            if (qBinaryFind(nodes, DBUtils::NodeOfTournirGrid({child, "", "", false, -1})) != nodes.end() )
            {
                paintLine(getCell(node.v), getCell(child), painter);
            }
        }
    }
}

void RenderAreaWidget::mousePressEvent(QMouseEvent* event)
{
    QPoint p(event->y() / heightCell, event->x() / widthCell);

    DBUtils::NodeOfTournirGrid currentNode = noNode;
    for (const DBUtils::NodeOfTournirGrid& node : DBUtils::getNodes(database, tournamentCategories))
        if (getCell(node.v) == p)
            currentNode = node;
    if (currentNode.v == noNode.v) return;

    if (event->button() == Qt::RightButton){
        if (selectedNode.v != noNode.v)
        {
            if (selectedNode.v == currentNode.v && selectedNode.isFighing)
            {
                QSqlQuery query("UPDATE GRID SET ORDER_FK = ? WHERE TOURNAMENT_CATEGORIES_FK = ? AND VERTEX = ?", database);
                query.bindValue(0, QVariant(QVariant::Int));
                query.bindValue(1, tournamentCategories);
                query.bindValue(2, selectedNode.v);
                if (!query.exec())
                    qDebug() << __PRETTY_FUNCTION__ << " " << query.lastError().text() << "\n" << query.lastQuery();
            }
            selectedNode = noNode;
        }
    } else if (event->button() == Qt::LeftButton){
        if (selectedNode.v == noNode.v)
        {
            selectedNode = currentNode;
        }
        else
        {
            DBUtils::NodeOfTournirGrid node0 = selectedNode;
            DBUtils::NodeOfTournirGrid node1 = currentNode;
            selectedNode = noNode;
            if (!node0.isFighing && !node1.isFighing)
            {
                {
                    QSqlQuery query("UPDATE GRID SET VERTEX = ? WHERE TOURNAMENT_CATEGORIES_FK = ? AND VERTEX = ?", database);
                    query.bindValue(0, 100500);
                    query.bindValue(1, tournamentCategories);
                    query.bindValue(2, node0.v);
                    if (!query.exec())
                        qDebug() << __PRETTY_FUNCTION__ << " " << query.lastError().text() << "\n" << query.lastQuery();
                }
                {
                    QSqlQuery query("UPDATE GRID SET VERTEX = ? WHERE TOURNAMENT_CATEGORIES_FK = ? AND VERTEX = ?", database);
                    query.bindValue(0, node0.v);
                    query.bindValue(1, tournamentCategories);
                    query.bindValue(2, node1.v);
                    if (!query.exec())
                        qDebug() << __PRETTY_FUNCTION__ << " " << query.lastError().text() << "\n" << query.lastQuery();
                }
                {
                    QSqlQuery query("UPDATE GRID SET VERTEX = ? WHERE TOURNAMENT_CATEGORIES_FK = ? AND VERTEX = ?", database);
                    query.bindValue(0, node1.v);
                    query.bindValue(1, tournamentCategories);
                    query.bindValue(2, 100500);
                    if (!query.exec())
                        qDebug() << __PRETTY_FUNCTION__ << " " << query.lastError().text() << "\n" << query.lastQuery();
                }
            }
            if (node0.v > node1.v) std::swap(node0, node1);
            if (2 * node0.v == node1.v || 2 * node0.v + 1 == node1.v)
            {
                RenderAreaResultDialog dlg(node1.name, node1.region, this);
                dlg.exec();

                node0.result = RenderAreaResultDialog::mLastResult;

                QString orderUID;
                {
                    QSqlQuery query("SELECT * FROM GRID WHERE TOURNAMENT_CATEGORIES_FK = ? AND VERTEX = ?", database);
                    query.bindValue(0, tournamentCategories);
                    query.bindValue(1, node1.v);
                    if (!( query.exec() && query.next()))
                        qDebug() << __PRETTY_FUNCTION__ << " " << query.lastError().text() << "\n" << query.lastQuery();
                    orderUID = query.value("ORDER_FK").toString();
                }
                QSqlQuery query("UPDATE GRID SET ORDER_FK = ?, RESULT = ? WHERE TOURNAMENT_CATEGORIES_FK = ? AND VERTEX = ?", database);
                query.bindValue(0, orderUID);
                query.bindValue(1, node0.result);
                query.bindValue(2, tournamentCategories);
                query.bindValue(3, node0.v);
                if (!query.exec())
                    qDebug() << __PRETTY_FUNCTION__ << " " << query.lastError().text() << "\n" << query.lastQuery();
            }
        }
    }
    repaint();
}



void RenderAreaWidget::paintRect(int i, int j, QPainter& painter, const DBUtils::NodeOfTournirGrid& node)
{
    QRect rect(j * widthCell, i * heightCell, widthCell, heightCell);
    if (node.v == selectedNode.v)
        painter.fillRect(rect, QBrush(Qt::green));
    //else
        //painter.fillRect(rect, QBrush(Qt::gray));
        //painter.fillRect(rect, QBrush(Qt::lightGray));
    painter.drawRect(rect);
    QRect rectName(rect.topLeft(), QSize(rect.width(), rect.height() / 2));
    QRect rectRegion(QPoint(rect.topLeft().x(), rect.topLeft().y() + rect.height() / 2), QSize(rect.width(), rect.height() / 2));

    painter.drawText(rectName  , Qt::AlignHCenter | Qt::AlignVCenter, node.name);
    if (node.isFighing)
        painter.drawText(rectRegion, Qt::AlignHCenter | Qt::AlignVCenter, node.result);
    else
        painter.drawText(rectRegion, Qt::AlignHCenter | Qt::AlignVCenter, node.region);
}

void RenderAreaWidget::paintLine(QPoint aa, QPoint bb, QPainter& painter)
{
    QPoint a(qMin(aa.x(), bb.x()), qMin(aa.y(), bb.y()));
    QPoint b(qMax(aa.x(), bb.x()), qMax(aa.y(), bb.y()));
    painter.drawLine(QPoint(widthCell * (a.y() + 1), heightCell * (a.x())),
                     QPoint(widthCell *  b.y()     , heightCell * (b.x() + 1)));

}


void RenderAreaWidget::setNormalSize()
{
    resize(countColumns * widthCell + 1, countRows * heightCell + 1);
}




void RenderAreaWidget::slotSetTournamentCategories(int tournamentCategories)
{
    this->tournamentCategories = tournamentCategories;
    selectedNode = noNode;
    repaint();
}

void RenderAreaWidget::widthChanged(int width)
{
    widthCell = width;
    setNormalSize();
    repaint();
}

void RenderAreaWidget::heightChanged(int height)
{
    heightCell = height;
    setNormalSize();
    repaint();
}

void RenderAreaWidget::onSaveInExcel()
{
    QVector<DBUtils::NodeOfTournirGrid> nodes = DBUtils::getNodes(database, tournamentCategories);
    if (nodes.empty()) return;
    qSort(nodes);

    countColumns = log2(nodes.last().v) + 1;
    countRows = 2 * (1 << (countColumns - 1)) - 1;


//    QAxObject* excel = new QAxObject( "Excel.Application", this );
//    excel->setProperty("Visible", true);
//    QAxObject* workbooks = excel->querySubObject( "Workbooks" );
//    QAxObject* workbook = workbooks->querySubObject( "Open(const QString&)", "D:/test_t.xlsx" );
//    QAxObject* sheets = workbook->querySubObject( "Sheets" );
//    int sheetNumber = 1;
//    QAxObject* sheet = sheets->querySubObject( "Item( int )", sheetNumber );

    QAxWidget excel("Excel.Application");
    excel.setProperty("Visible", true);
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
    workbooks->dynamicCall("Add");
    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");
    QAxObject *sheets = workbook->querySubObject("WorkSheets");
    QAxObject* sheet = sheets->querySubObject( "Item( int )", 1);

    int offset = 3;
    ExcelUtils::setValue(sheet, 2, 1, getCategoryName(), -1);

    int maxRow = offset;

    for (const DBUtils::NodeOfTournirGrid& node : nodes)
    {

        QPoint p = getCell(node.v);

        QAxObject* cell = sheet->querySubObject( "Cells( int, int )", p.x() + 1 + offset, p.y() + 1);
        maxRow = qMax(maxRow, p.x() + 1 + offset);

        if (node.isFighing)
            cell->setProperty("Value", QVariant(node.name + " (" + node.result + ")"));
        else
            cell->setProperty("Value", QVariant(node.name));

        QAxObject *border = cell->querySubObject("Borders()");
        border->setProperty("LineStyle", 1);
        border->setProperty("Weight", 2);
        delete cell;

        for (int child : {2 * node.v, 2 * node.v + 1})
        {
            if (qBinaryFind(nodes, DBUtils::NodeOfTournirGrid({child, "", "", false, -1})) != nodes.end() )
            {
                QPoint aa = getCell(node.v);
                QPoint bb = getCell(child);

                QPoint a(qMin(aa.x(), bb.x()), qMin(aa.y(), bb.y()));
                QPoint b(qMax(aa.x(), bb.x()), qMax(aa.y(), bb.y()));
                for (int row = a.x(); row <= b.x(); ++row)
                {
                    cell = sheet->querySubObject( "Cells( int, int )", row + 1 + offset, a.y() + 1);
                    QAxObject *border = cell->querySubObject("Borders(xlEdgeRight)");
                    border->setProperty("LineStyle", 1);
                    border->setProperty("Weight", 2);
                    delete border;

                    maxRow = qMax(maxRow, row + 1 + offset);
                }
            }
        }
    }

    maxRow += 2;
    long long tournamentUID = getTournamentUID();

    ExcelUtils::setValue(sheet, maxRow, 1, "Главный судья: " + DBUtils::get_MAIN_JUDGE(database, tournamentUID), 0);
    ++maxRow;

    ExcelUtils::setValue(sheet, maxRow, 1, "Главный секретарь: " + DBUtils::get_MAIN_SECRETARY(database, tournamentUID), 0);
    ++maxRow;

    ExcelUtils::setValue(sheet, maxRow, 1, "Заместитель главного судьи: " + DBUtils::get_ASSOCIATE_MAIN_JUDGE(database, tournamentUID), 0);
    ++maxRow;

    //workbook->dynamicCall("Close()");
    delete sheet;
    delete sheets;
    delete workbook;
    delete workbooks;
    //excel->dynamicCall("Quit()");
    //delete excel;
}
