#ifndef IMAGELOADERWIDGET_H
#define IMAGELOADERWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QFrame>
#include <QDebug>
#include <QFileDialog>
#include <QBuffer>


class ImageLoader : public QFrame
{
    Q_OBJECT

public:
    ImageLoader(QWidget *parent = 0);
    QImage img;

protected:
    void paintEvent(QPaintEvent *event);
};



namespace Ui {
class ImageLoaderWidget;
}

class ImageLoaderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImageLoaderWidget(QWidget *parent, const QImage& img);
    ~ImageLoaderWidget();
    QString getBase64Image();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ImageLoaderWidget *ui;
};

#endif // IMAGELOADERWIDGET_H


