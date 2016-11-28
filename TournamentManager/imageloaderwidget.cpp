#include "imageloaderwidget.h"
#include "ui_imageloaderwidget.h"


ImageLoader::ImageLoader(QWidget* parent) :
    QFrame(parent)
{

}

void ImageLoader::paintEvent(QPaintEvent* event)
{
    //qDebug() << QApplication::focusWidget();
    if (img.isNull())
    {
        QFrame::paintEvent(event);
    }
    else
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        const int delta = 1;
        QRect rect = frameRect().adjusted(delta, delta, -delta, -delta);
        QImage img2 = img.scaled(rect.size(), Qt::KeepAspectRatio);
        QRect rec(0, 0, img2.width(), img2.height());
        painter.drawImage(rec, img2, rec);
        painter.drawRect(rec);
    }
}

ImageLoaderWidget::ImageLoaderWidget(QWidget *parent, const QImage& img) :
    QWidget(parent),
    ui(new Ui::ImageLoaderWidget)
{
    ui->setupUi(this);
    ui->frame->img = img;
    ui->frame->repaint();
}

ImageLoaderWidget::~ImageLoaderWidget()
{
    delete ui;
}

QString ImageLoaderWidget::getBase64Image()
{
    QImage img = ui->frame->img;
    if (!img.isNull())
        img = img.scaledToHeight(250);
    QByteArray imageBytes;
    QBuffer inBuffer(&imageBytes);
    inBuffer.open(QIODevice::WriteOnly);
    img.save(&inBuffer, "PNG");
    return QString::fromLocal8Bit(imageBytes.toBase64().data());
}



void ImageLoaderWidget::on_pushButton_clicked()
{
    ui->frame->img = QImage();
    ui->frame->repaint();
}

void ImageLoaderWidget::on_pushButton_2_clicked()
{
    QString openFileName = QFileDialog::getOpenFileName(0, "Выберете флаг для загрузки");
    //qDebug() << "openFileName::" << openFileName;
    if (openFileName.size() > 0)
    {
        ui->frame->img.load(openFileName);
        ui->frame->img = ui->frame->img.scaledToHeight(250);
        ui->frame->repaint();
    }
}
