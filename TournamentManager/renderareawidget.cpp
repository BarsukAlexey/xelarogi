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


RenderAreaWidget::RenderAreaWidget(QWidget *parent, int widthCell, int heightCell, const QSqlDatabase &_database, long long _tournamentUID)
    : QWidget(parent),
      database(_database),
      tournamentUID(_tournamentUID)
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
    p.setX( (1 << (p.y() + 1)) * ((1 << (countColumns - p.y())) - 1 - v) + (1 << p.y()) -1);
    return p;
}

void RenderAreaWidget::paintEvent(QPaintEvent* )
{
    //qDebug() << __PRETTY_FUNCTION__ << " " << QDateTime::currentDateTime();
    //return;

    QPainter painter(this);

    QVector<NodeOfTournirGrid> nodes = getNodes();
    if (nodes.empty()) return;
    qSort(nodes);

    //countColumns = qMax(countColumns, log2(nodes.last().v) + 1);
    countColumns = log2(nodes.last().v) + 1;
    countRows = 2 * (1 << (countColumns - 1)) - 1;
    setNormalSize();

    for (const NodeOfTournirGrid& node : nodes)
    {
        QPoint cell = getCell(node.v);
        paintRect(cell.x(), cell.y(), painter, node);
        for (int child : {2 * node.v, 2 * node.v + 1})
        {
            if (qBinaryFind(nodes, NodeOfTournirGrid(child, "")) != nodes.end() )
            {
                paintLine(getCell(node.v), getCell(child), painter);
            }
        }
    }
}

void RenderAreaWidget::mousePressEvent(QMouseEvent* event)
{
    QPoint p(event->y() / heightCell, event->x() / widthCell);
    setOfSelectedCells.push_back(p);
    repaint();
}

void RenderAreaWidget::wheelEvent(QWheelEvent* )
{
    cntNodes += 2;
    repaint();
}


void RenderAreaWidget::paintRect(int i, int j, QPainter& painter, const NodeOfTournirGrid& node)
{
    QRect rect(j * widthCell, i * heightCell, widthCell, heightCell);
    if (setOfSelectedCells.contains(QPoint(i, j)))
        painter.fillRect(rect, QBrush(Qt::green));
    else
        painter.fillRect(rect, QBrush(Qt::gray));
    painter.drawRect(rect);
    painter.drawText(rect, Qt::AlignHCenter | Qt::AlignVCenter, node.name);
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

void RenderAreaWidget::getNodes_ForDebuging(int v, QVector<RenderAreaWidget::NodeOfTournirGrid>& arr)
{
    if (cntNodes < v) return;
    arr.push_back(RenderAreaWidget::NodeOfTournirGrid(v, QString::number(v)));
    getNodes_ForDebuging(2 * v, arr);
    getNodes_ForDebuging(2 * v + 1, arr);
}

QVector<RenderAreaWidget::NodeOfTournirGrid> RenderAreaWidget::getNodes()
{
    QVector<RenderAreaWidget::NodeOfTournirGrid> arr;
    //getNodes_ForDebuging(1, arr);

    //
    QSqlQuery query("SELECT * FROM GRID WHERE TOURNAMENT_CATEGORIES_FK = ? ", database);
    query.bindValue(0, tournamentCategories);
    if (query.exec())
    {
        while (query.next())
        {
            QString orderUID = query.value("ORDER_FK").toString();
            QString name = "Unknown";
            QString region = "";
            if (orderUID.size() != 0)
            {
                QSqlQuery queryOrder("SELECT * FROM ORDERS WHERE UID = ? ", database);
                queryOrder.bindValue(0, orderUID);
                if (!(queryOrder.exec() && queryOrder.next()))
                {
                    qDebug() << __PRETTY_FUNCTION__ << " " << queryOrder.lastError().text() << "\n" << queryOrder.lastQuery();
                    arr.clear();
                    return arr;
                }
                //name = queryOrder.value("SECOND_NAME").toString() + " " + queryOrder.value("FIRST_NAME").toString();
                name = queryOrder.value("SECOND_NAME").toString();

                QSqlQuery queryRegion("SELECT * FROM REGIONS WHERE UID = ? ", database);
                //qDebug() << __PRETTY_FUNCTION__ << queryOrder.value("REGION_FK").toString();
                queryRegion.bindValue(0, queryOrder.value("REGION_FK").toString());
                if (!(queryRegion.exec() && queryRegion.next()))
                {
                    qDebug() << __PRETTY_FUNCTION__ << " " << queryRegion.lastError().text() << "\n" << queryRegion.lastQuery();
                    arr.clear();
                    return arr;
                }
                region = queryRegion.value("SHORTNAME").toString();
            }



            arr.push_back(RenderAreaWidget::NodeOfTournirGrid(query.value("VERTEX").toInt(), name + " " + region));
        }
    }
    else
    {
        qDebug() << __PRETTY_FUNCTION__ << " " << query.lastError().text() << "\n" << query.lastQuery();
        arr.clear();
        return arr;
    }
    return arr;
}

void RenderAreaWidget::slotSetTournamentCategories(int tournamentCategories)
{
    this->tournamentCategories = tournamentCategories;
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
