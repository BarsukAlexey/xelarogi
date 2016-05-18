#ifndef ASPECT_RATIO_PIXMAP_LABEL_H
#define ASPECT_RATIO_PIXMAP_LABEL_H

#include <QLabel>

#include <QLabel>
#include <QPixmap>
#include <QResizeEvent>

class AspectRatioPixmapLabel : public QLabel
{
    Q_OBJECT
public:
    explicit AspectRatioPixmapLabel(QWidget *parent = 0);
public slots:
    void setPixmap ( const QPixmap & );
    void resizeEvent(QResizeEvent *);
private:
    QPixmap pixmap;
};

#endif // ASPECT_RATIO_PIXMAP_LABEL_H
