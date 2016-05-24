#include "qrightclickbutton.h"

QRightClickButton::QRightClickButton(QWidget *parent) :
    QPushButton(parent)
{
}

void QRightClickButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
        emit rightClicked();
    QPushButton::mousePressEvent(event);
}

void QRightClickButton::setSizeFont()
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
            if (bound.width() < 0.90 * width() && bound.height() < 0.90 * height())
                l = m;
            else
                r = m - 1;
        }
        myFont.setPointSize(l);
        setFont(myFont);
        //qDebug() << "QRightClickButton::resizeEvent" << QDateTime::currentDateTime().toString("hh:mm:ss zzz") << size() << l;
    }
}

void QRightClickButton::setText(const QString& text)
{
    QPushButton::setText(text);
    setSizeFont();

}

void QRightClickButton::resizeEvent(QResizeEvent* )
{
    setSizeFont();
}
