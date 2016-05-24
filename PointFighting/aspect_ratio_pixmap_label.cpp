#include "aspect_ratio_pixmap_label.h"
#include <QGraphicsColorizeEffect>

AspectRatioPixmapLabel::AspectRatioPixmapLabel(QWidget *parent) :
    QLabel(parent)
{
    this->setMinimumSize(1,1);
    isGray = false;
}

void AspectRatioPixmapLabel::setPixmap(const QPixmap& map)
{
    pixmap = map;
    QLabel::setPixmap(isGray? makeGrey(pixmap.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)) : pixmap.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void AspectRatioPixmapLabel::resizeEvent(QResizeEvent *)
{
    if(!pixmap.isNull())
        QLabel::setPixmap(isGray? makeGrey(pixmap.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)) : pixmap.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

QPixmap AspectRatioPixmapLabel::makeGrey(const QPixmap& mypixmap)
{
    QImage myimage = mypixmap.toImage();
    for (int i = 0; i < myimage.width(); i++)
        for (int j = 0; j < myimage.height(); j++)
        {
            int gray = qGray(myimage.pixel(i,j));
            myimage.setPixel(i, j, QColor(gray, gray, gray).rgba());
        }
    return QPixmap::fromImage(myimage);
}

void AspectRatioPixmapLabel::setGray(bool isGray)
{
    if (this->isGray == isGray)
        return;
    this->isGray = isGray;
    QLabel::setPixmap(isGray? makeGrey(pixmap.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)) : pixmap.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void AspectRatioPixmapLabel::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
        emit leftButtonClick();
    else if(event->button() == Qt::RightButton)
        emit rightButtonClick();
}
