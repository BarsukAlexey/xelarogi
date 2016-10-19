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
    {
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        dataStream << stringList;
        dataStream.device()->close();
        // dataStream надо закрыть и сделать FLUSH
        // http://www.prog.org.ru/topic_14195_0.html
    }
    qDebug() << __LINE__ << __PRETTY_FUNCTION__ << itemData.size();

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-lolka", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    if (drag->exec(Qt::MoveAction))
    {
        //qDebug() << "TODO больше нельзя его изать";
    }
    else
    {
        //qDebug() << "Не попал =)";
    }
}

void Dialogschedule2TreeWidget::setTournamentUID(const int tournamentUID)
{
    this->tournamentUID = tournamentUID;
}

void Dialogschedule2TreeWidget::updateDataInTable()
{

}

