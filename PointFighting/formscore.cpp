#include "formscore.h"
#include <QPainter>
#include <QPen>
#include <QPixmap>


FormScore::FormScore(QString name, QString region, QImage flag, QColor backgroundColor, QWidget *parent ) :
    QWidget(parent),
    backgroundColor(backgroundColor),
    ui(new Ui_Form),
    flag(flag)
{
    ui->setupUi(this);
    ui->labelFIO->setText(name);
    ui->labelRegion->setText(region);

    int r, g, b;
    backgroundColor.getRgb(&r, &g, &b);
    setStyleSheet(styleSheet() + QString(";\nbackground-color: rgb(%1, %2, %3);").arg(r).arg(g).arg(b));

    isWinner = false;
    setWinner(true);
}

FormScore::~FormScore()
{
    delete ui;
}

void FormScore::setWinner(bool isWinner)
{
    if (this->isWinner == isWinner)
        return;
    this->isWinner = isWinner;

    if (isWinner)
    {
        int r, g, b;
        backgroundColor.getRgb(&r, &g, &b);
        setStyleSheet(styleSheet() + QString(";\nbackground-color: rgb(%1, %2, %3);").arg(r).arg(g).arg(b));
        ui->labelFlag->setPixmap(drawBorder(flag));
    }
    else
    {
        setStyleSheet(styleSheet() + QString(";\nbackground-color: rgb(169, 169, 169);"));
        ui->labelFlag->setPixmap(drawBorder(makeGrey(flag)));
    }
}


QPixmap FormScore::drawBorder(QImage flag)
{
    QPixmap pm = QPixmap::fromImage(flag);
    QPainter painter(&pm);
    QPen pen(Qt::white);
    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawRoundedRect(0, 0, flag.width() - 1, flag.height() - 1, 0, 0);
    return pm;
}

QImage FormScore::makeGrey(QImage image)
{
    for (int i = 0; i < image.width(); i++)
        for (int j = 0; j < image.height(); j++)
        {
            int gray = qGray(image.pixel(i,j));
            image.setPixel(i, j, QColor(gray, gray, gray).rgba());
        }
    return image;
}

QPixmap FormScore::drawCubes(int count)
{
    if (count == 0)
    {
        QPixmap pm(1, 1);
        pm.fill(Qt::transparent);
        return pm;
    }
    const int sizeOfSideOfCube = 50;
    QPixmap pm(4 * sizeOfSideOfCube + 3 * sizeOfSideOfCube, sizeOfSideOfCube);
    pm.fill(Qt::transparent);
    QPainter painter(&pm);
    for (int i = 0; i < count; ++i)
        painter.fillRect(i * (sizeOfSideOfCube + sizeOfSideOfCube), 0, sizeOfSideOfCube, sizeOfSideOfCube, Qt::yellow);
    return pm;
}

void FormScore::setCountPoints(int countPoints)
{
    ui->pushButtonPoint->setText(QString::number(countPoints));
}

void FormScore::setCountMinus(int countCubes)
{
    ui->labelMinus->setPixmap(drawCubes(countCubes));
}

void FormScore::setCountFo(int countCubes)
{
    ui->labelFo->setPixmap(drawCubes(countCubes));
}

void FormScore::setCountEx(int countCubes)
{
    ui->labelEx->setPixmap(drawCubes(countCubes));
}
