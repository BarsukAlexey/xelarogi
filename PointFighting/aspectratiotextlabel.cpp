#include "aspectratiotextlabel.h"

#include <QDebug>
#include <QDateTime>


AspectRatioTextLabel::AspectRatioTextLabel(QWidget *parent) :
    QLabel(parent)
{
    this->setMinimumSize(1,1);
}

void AspectRatioTextLabel::mySetFontSize()
{
    if (0 < width() && 0 < height())
    {
        QFont myFont = font();
        int l = 1, r = qMin(width(), height());
        while (l < r)
        {
            int m = (l + r + 1) / 2;
            myFont.setPointSize(m);
            QFontMetrics fm(myFont);
            QRect bound = fm.boundingRect(text());
            if (bound.width() < width() && bound.height() < height())
                l = m;
            else
                r = m - 1;
        }
        myFont.setPointSize(l);
        setFont(myFont);
        //qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss zzz") << size() << l;
    }
}

void AspectRatioTextLabel::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
        emit leftButtonClick();
    else if(event->button() == Qt::RightButton)
        emit rightButtonClick();
}

void AspectRatioTextLabel::setText(const QString& str)
{
    if (text() == str)
    {
        //qDebug() << "AspectRatioTextLabel::setText: " << "YES";
        return;
    }
    QLabel::setText(str);
    mySetFontSize();
}

void AspectRatioTextLabel::resizeEvent(QResizeEvent * )
{
    mySetFontSize();
}
