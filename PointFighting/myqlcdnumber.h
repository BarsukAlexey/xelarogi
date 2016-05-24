#ifndef MYQLCDNUMBER_H
#define MYQLCDNUMBER_H

#include <QDebug>
#include <QLCDNumber>
#include <QMouseEvent>
#include <QPalette>


class MyQLCDNumber : public QLCDNumber
{
    Q_OBJECT
public:
    explicit MyQLCDNumber(QWidget* p = 0);



signals:
    void leftButtonClick();
    void rightButtonClick();

protected:
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;

public slots:
    void display(int num);
};

#endif // MYQLCDNUMBER_H
