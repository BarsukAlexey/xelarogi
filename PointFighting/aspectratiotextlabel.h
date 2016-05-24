#ifndef ASPECTRATIOTEXTLABEL_H
#define ASPECTRATIOTEXTLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <QDateTime>


class AspectRatioTextLabel : public QLabel
{
    Q_OBJECT

private:
    bool isTimer;


public:
    explicit AspectRatioTextLabel(QWidget *parent = 0);
    void setLableAsTimer(bool isTimer);

private:
    void mySetFontSize();
    int mySetFontSize(QFont myFont, int width, int height, QString str);

signals:
    void leftButtonClick();
    void rightButtonClick();

protected:
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;

public slots:
    void setText(const QString& str);
    void resizeEvent(QResizeEvent *);



};

#endif // ASPECTRATIOTEXTLABEL_H
