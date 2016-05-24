#include "aspectratiotextlabel.h"


AspectRatioTextLabel::AspectRatioTextLabel(QWidget *parent) :
    QLabel(parent)
{
    isTimer = false;
    this->setMinimumSize(1,1);
}

void AspectRatioTextLabel::setLableAsTimer(bool isTimer)
{
    this->isTimer = isTimer;
}

void AspectRatioTextLabel::mySetFontSize()
{
    int sz = mySetFontSize(font(), width(), height(), text());
    if (isTimer)
        for (int i = 0; i < 10; ++i)
            sz = qMin(sz, mySetFontSize(font(), width(), height(), QString("%1%1:%1%1").arg(i)));
    QFont font = this->font();
    font.setPointSize(sz);
    setFont(font);
}

int AspectRatioTextLabel::mySetFontSize(QFont myFont, int width, int height, QString str)
{
    if (0 < width && 0 < height)
    {
        int l = 1, r = qMin(width, height);
        while (l < r)
        {
            int m = (l + r + 1) / 2;
            myFont.setPointSize(m);
            QFontMetrics fm(myFont);
            QRect bound = fm.boundingRect(str);
            if (bound.width() < width && bound.height() < height)
                l = m;
            else
                r = m - 1;
        }
        return l;
    }
    return 1;
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
