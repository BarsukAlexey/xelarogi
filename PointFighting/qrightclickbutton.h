#ifndef QRIGHTCLICKBUTTON_H
#define QRIGHTCLICKBUTTON_H

#include <QPushButton>
#include <QMouseEvent>
#include <QDebug>
#include <QDateTime>
#include <QPainter>
#include <QResizeEvent>




class QRightClickButton : public QPushButton
{
    Q_OBJECT

private:
    QString str;
    int flag;
public:
    explicit QRightClickButton(QWidget *parent = 0);

protected:
    //virtual void paintEvent(QPaintEvent * event);
    void resizeEvent(QResizeEvent* e);

private slots:
    void mousePressEvent(QMouseEvent *e);

//public:
    //void setText(const QString &text);

signals:
    void rightClicked();

public slots:
    //void setAlignmentFlag(Qt::AlignmentFlag flag);
    //void setAlignmentFlag(int flag);

};

#endif // QRIGHTCLICKBUTTON_H
