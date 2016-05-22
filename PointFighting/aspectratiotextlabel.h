#ifndef ASPECTRATIOTEXTLABEL_H
#define ASPECTRATIOTEXTLABEL_H

#include <QLabel>
#include <QMouseEvent>


class AspectRatioTextLabel : public QLabel
{
    Q_OBJECT
public:
    explicit AspectRatioTextLabel(QWidget *parent = 0);
private:
    void mySetFontSize();

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
