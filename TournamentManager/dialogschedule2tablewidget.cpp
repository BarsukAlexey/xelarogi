#include "dialogschedule2tablewidget.h"

Dialogschedule2TableWidget::Dialogschedule2TableWidget(QWidget* parent) :
    QTableWidget(parent)
{
    setAcceptDrops(true);
}

void Dialogschedule2TableWidget::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasFormat(Dialogschedule2TreeWidget::getMimiType()))
    {
        event->acceptProposedAction();
    }
}

//void Dialogschedule2TableWidget::dragLeaveEvent(QDragLeaveEvent* event)
//{
//    event->accept();
//}

void Dialogschedule2TableWidget::dragMoveEvent(QDragMoveEvent* event)
{
    if (event->mimeData()->hasFormat(Dialogschedule2TreeWidget::getMimiType()) &&
        indexAt(event->pos()).isValid())
    {
        event->acceptProposedAction();
    }
}

void Dialogschedule2TableWidget::dropEvent(QDropEvent* event)
{
    QModelIndex index = indexAt(event->pos());

    if (event->mimeData()->hasFormat(Dialogschedule2TreeWidget::getMimiType()) &&
        index.isValid())
    {
        QByteArray pieceData = event->mimeData()->data(Dialogschedule2TreeWidget::getMimiType());
        if (pieceData.isEmpty())
        {
            qDebug() << __LINE__ << __PRETTY_FUNCTION__ << "FUCK";
            return;
        }

        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
        QStringList strs;
        dataStream >> strs;
        if (strs.isEmpty())
        {
            qDebug() << __LINE__ << __PRETTY_FUNCTION__ << "FUCK";
            return;
        }

        event->acceptProposedAction();

        emit dataIsDropped(strs, index.row(), index.column());
    }
}






