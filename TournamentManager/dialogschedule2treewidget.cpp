#include "dialogschedule2treewidget.h"

Dialogschedule2TreeWidget::Dialogschedule2TreeWidget(QWidget *parent) :
    QTreeWidget(parent)
{
    setDragEnabled(true);
    //setAcceptDrops(false);
    //setDropIndicatorShown(true);
}



void Dialogschedule2TreeWidget::startDrag(Qt::DropActions )
{
    QStringList stringList = currentIndex().data(Qt::UserRole).toStringList();
    if (stringList.isEmpty())
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << "FUCK";
        return;
    }


    QByteArray byteArray;
    QDataStream dataStream(&byteArray, QIODevice::WriteOnly);
    dataStream << stringList; // http://www.prog.org.ru/topic_14195_0.html
    if (byteArray.isEmpty())
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << "FUCK";
        return;
    }

    QMimeData *mimeData = new QMimeData;
    mimeData->setData(getMimiType(), byteArray);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->exec();
}

void Dialogschedule2TreeWidget::setTournamentUID(const int tournamentUID)
{
    this->tournamentUID = tournamentUID;
}

void Dialogschedule2TreeWidget::updateDataInTable()
{

}

