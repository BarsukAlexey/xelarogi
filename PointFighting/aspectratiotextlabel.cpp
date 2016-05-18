#include "aspectratiotextlabel.h"

#include <QDebug>

AspectRatioTextLabel::AspectRatioTextLabel(QWidget *parent) :
    QLabel(parent)
{
    //    this->setMinimumSize(1,1);
    this->setText("QweSo");
}

void AspectRatioTextLabel::resizeEvent(QResizeEvent * )
{
    if (0 < width() && 0 < height())
    {
        QFont myFont = font();
        int l = 1, r = qMax(width(), height());
        while (l < r)
        {
            int m = (l + r + 1) / 2;
            myFont.setPointSize(m);
            QFontMetrics fm(myFont);
            QRect bound = fm.boundingRect(text());
            if (bound.width() <= width() && bound.height() <= height())
                l = m;
            else
                r = m - 1;
        }
        myFont.setPointSize(l);
        setFont(myFont);
        qDebug() << size() << l;
    }
}
