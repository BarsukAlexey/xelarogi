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
    void setText(const QString &text);

protected:
    void resizeEvent(QResizeEvent* e);

private slots:
    void mousePressEvent(QMouseEvent *e);

signals:
    void rightClicked();

private:
    void setSizeFont();
};

#endif // QRIGHTCLICKBUTTON_H
