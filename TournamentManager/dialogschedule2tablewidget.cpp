#include "dialogschedule2tablewidget.h"

Dialogschedule2TableWidget::Dialogschedule2TableWidget(QWidget* parent) :
    QTableWidget(parent)
{
    setAcceptDrops(true);
}

void Dialogschedule2TableWidget::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasFormat("application/x-lolka"))
        event->accept();
    else
        event->ignore();
}

void Dialogschedule2TableWidget::dragLeaveEvent(QDragLeaveEvent* event)
{
    event->accept();
}

void Dialogschedule2TableWidget::dragMoveEvent(QDragMoveEvent* event)
{

    if (event->mimeData()->hasFormat("application/x-lolka") &&
        indexAt(event->pos()).isValid())
    {
        event->accept();
    } else {
        event->ignore();
    }
}

void Dialogschedule2TableWidget::dropEvent(QDropEvent* event)
{
    QModelIndex index = indexAt(event->pos());

    if (event->mimeData()->hasFormat("application/x-lolka") &&
        index.isValid())
    {
        QByteArray pieceData = event->mimeData()->data("application/x-lolka");
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
        QStringList strs;
        dataStream >> strs;

        //qDebug() << "Кинул" << strs << "   в" << index;
        emit ohDrop(strs, index.row(), index.column());

        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
    {
        event->ignore();
    }
}






