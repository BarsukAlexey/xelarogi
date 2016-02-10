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

RenderAreaWidget::RenderAreaWidget(QWidget *parent, int widthCell, int heightCell) : QWidget(parent)
{
    countRows = 1;
    countColumns = 1;
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
    QPainter painter(this);

    QVector<NodeOfTournirGrid> nodes = getNodes();
    qSort(nodes);

    countColumns = qMax(countColumns, log2(nodes.last().v) + 1);
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

void RenderAreaWidget::wheelEvent(QWheelEvent* event)
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
    getNodes_ForDebuging(1, arr);
    return arr;
}

void RenderAreaWidget::setPlayers()
{
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
