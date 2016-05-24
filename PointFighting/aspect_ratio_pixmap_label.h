#ifndef ASPECT_RATIO_PIXMAP_LABEL_H
#define ASPECT_RATIO_PIXMAP_LABEL_H


#include <QDebug>
#include <QLabel>
#include <QPixmap>
#include <QResizeEvent>

class AspectRatioPixmapLabel : public QLabel
{
    Q_OBJECT
private:
    QPixmap pixmap;
    bool isGray;

public:
    explicit AspectRatioPixmapLabel(QWidget *parent = 0);
public slots:
    void setPixmap (const QPixmap &);
    void resizeEvent(QResizeEvent *);
    void setGray(bool isGray);

private:
    QPixmap makeGrey(const QPixmap&);

signals:
    void leftButtonClick();
    void rightButtonClick();

protected:
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
};

#endif // ASPECT_RATIO_PIXMAP_LABEL_H
