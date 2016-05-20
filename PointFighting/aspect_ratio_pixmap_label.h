#ifndef ASPECT_RATIO_PIXMAP_LABEL_H
#define ASPECT_RATIO_PIXMAP_LABEL_H

#include <QLabel>

#include <QLabel>
#include <QPixmap>
#include <QResizeEvent>

class AspectRatioPixmapLabel : public QLabel
{
    Q_OBJECT
private:
    QPixmap pixmap;
public:
    explicit AspectRatioPixmapLabel(QWidget *parent = 0);
public slots:
    void setPixmap ( const QPixmap & );
    void resizeEvent(QResizeEvent *);

};

#endif // ASPECT_RATIO_PIXMAP_LABEL_H
