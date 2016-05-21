#include "myqlcdnumber.h"
#include <QPalette>

MyQLCDNumber::MyQLCDNumber(QWidget* p) :
    QLCDNumber(p)
{
    setDigitCount(1);
    setSegmentStyle(Flat);

//    QPalette localPalette = palette();
//    localPalette.setColor(QPalette::ColorRole::WindowText, Qt::red);
//    localPalette.setColor(QPalette::ColorRole::Background, Qt::black);
//    setPalette(localPalette);
    //setStyleSheet("color:rgb(85, 85, 255)");

}

void MyQLCDNumber::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
        display(intValue() + 1);
    else if(event->button() == Qt::RightButton)
        display(intValue() - 1);

    if (checkOverflow(intValue())){
        setDigitCount(digitCount() + 1);
        display(intValue());
    } else {
        while (QString::number(intValue()).length() < digitCount())
            setDigitCount(digitCount() - 1);
    }
}

