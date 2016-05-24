#include "myqlcdnumber.h"



MyQLCDNumber::MyQLCDNumber(QWidget* p) : QLCDNumber(p)
{
    setDigitCount(1);
    setSegmentStyle(Flat);
}



void MyQLCDNumber::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
        emit leftButtonClick();
    else if(event->button() == Qt::RightButton)
        emit rightButtonClick();
}

void MyQLCDNumber::display(int num)
{
    while (QString::number(num).length() < digitCount())
        setDigitCount(digitCount() - 1);
    while (QString::number(num).length() > digitCount())
        setDigitCount(digitCount() + 1);

    QLCDNumber::display(num);
}

