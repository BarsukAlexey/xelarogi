#ifndef MYQLCDNUMBER_H
#define MYQLCDNUMBER_H

#include <QLCDNumber>
#include <QDebug>
#include <QMouseEvent>


class MyQLCDNumber : public QLCDNumber
{
public:
    MyQLCDNumber();

protected:
    void mousePressEvent(QMouseEvent *);

signals:

public slots:
};

#endif // MYQLCDNUMBER_H
