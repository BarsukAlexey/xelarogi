#include "qrightclickbutton.h"

QRightClickButton::QRightClickButton(QWidget *parent) :
    QPushButton(parent)
{
}

void QRightClickButton::paintEvent(QPaintEvent* event)
{

    QPushButton::paintEvent(event);
    if (0 < width() && 0 < height())
    {
        QPainter painter(this);
        QFont myFont = painter.font();
        int l = 1, r = qMin(width(), height());
        while (l < r)
        {
            int m = (l + r + 1) / 2;
            myFont.setPointSize(m);
            QFontMetrics fm(myFont);
            QRect bound = fm.boundingRect(str);
            if (bound.width() < width() && bound.height() < height())
                l = m;
            else
                r = m - 1;
            //qDebug() << text();
        }
        myFont.setPointSize(l);


        painter.setFont(myFont);
        painter.drawText(QRect(0, 0, width(), height()), flag, str);
    }
}

void QRightClickButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
        emit rightClicked();
    QPushButton::mousePressEvent(event);
}

void QRightClickButton::setText(const QString& s)
{
    str = s;
    repaint();
}

void QRightClickButton::setAlignmentFlag(int flag)
{
    this->flag = flag;
    repaint();
}

//void QRightClickButton::resizeEvent(QResizeEvent* e)
//{
//    //qDebug() << e->size() << width() << height();
//    if (0 < width() && 0 < height())
//    {
////        QFont myFont = font();
////        int l = 1, r = qMax(width(), height());
////        while (l < r)
////        {
////            int m = (l + r + 1) / 2;
////            myFont.setPointSize(m);
////            QFontMetrics fm(myFont);
////            QRect bound = fm.boundingRect(text());
////            if (bound.width() < width() && bound.height() < height())
////                l = m;
////            else
////                r = m - 1;
////            //qDebug() << text();
////        }
////        myFont.setPointSize(l);
////        setFont(myFont);
//        //qDebug() << "QRightClickButton::resizeEvent" << QDateTime::currentDateTime().toString("hh:mm:ss zzz") << size() << l;
//    }
//}
