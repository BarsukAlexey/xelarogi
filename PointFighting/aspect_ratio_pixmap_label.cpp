#include "aspect_ratio_pixmap_label.h"
#include <QDebug>

AspectRatioPixmapLabel::AspectRatioPixmapLabel(QWidget *parent) :
    QLabel(parent)
{
    this->setMinimumSize(1,1);
    //pixmap = QPixmap(".\\resources\\images\\images.jpg");
}

void AspectRatioPixmapLabel::setPixmap(const QPixmap& map)
{
    pixmap = map;
    QLabel::setPixmap(pixmap.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void AspectRatioPixmapLabel::resizeEvent(QResizeEvent *)
{


    if(!pixmap.isNull())
    {
        //qDebug() << this->size() << e->size(); // equal
        QLabel::setPixmap(pixmap.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}
