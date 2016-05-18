#ifndef ASPECTRATIOTEXTLABEL_H
#define ASPECTRATIOTEXTLABEL_H

#include <QLabel>

class AspectRatioTextLabel : public QLabel
{
    Q_OBJECT
public:
    explicit AspectRatioTextLabel(QWidget *parent = 0);
signals:

public slots:
//    void setText ( const QString & );
    void resizeEvent(QResizeEvent *);

};

#endif // ASPECTRATIOTEXTLABEL_H
