#include "dialogschedule2treewidget.h"

Dialogschedule2TreeWidget::Dialogschedule2TreeWidget(QWidget *parent) :
    QTreeWidget(parent)
{
    setDragEnabled(true);
    setAcceptDrops(false);
    //setDropIndicatorShown(true);
}

void Dialogschedule2TreeWidget::startDrag(Qt::DropActions )
{
    QStringList stringList = currentIndex().data(Qt::UserRole).toStringList();
    //qDebug() << "stringList: " << stringList;

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << stringList;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-lolka", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->exec(Qt::MoveAction);
}

