#include "dialogawardpanel.h"
#include "ui_dialogawardpanel.h"

DialogAwardWidget::DialogAwardWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAwardPanel)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowMaximizeButtonHint);
}

DialogAwardWidget::~DialogAwardWidget()
{
    delete ui;
}

void DialogAwardWidget::setData(QByteArray& byteArray)
{
    if (!byteArray.isEmpty())
    {
        QDataStream dataStream(&byteArray, QIODevice::ReadOnly);
        dataStream
                >> image
                >> rects
                >> font
                >> colorText
                >> colorTextBound
                >> colorFlagBound
                >> withTextBound;
    }
    names.clear();
    countries.clear();

    names.resize(4);
    countries.resize(4);

    flags.clear();
    flags.resize(4);

    repaint();
}

void DialogAwardWidget::paintEvent(QPaintEvent* event)
{

    {
        QPainter painter(this);
        painter.fillRect(0, 0, size().width(), size().height(), Qt::white);
    }
    //QTime t; t.start();
    //qDebug() << event->rect() << event->region();
    if (image.isNull())
        return;

    QPixmap img(image);
    QPainter painter(&img);
    painter.setRenderHint(QPainter::Antialiasing);

    for (int i = 0; i < rects.size(); ++i)
    {
        const QRect rect = rects[i];
        if (i < 4 || i == 8)
        {
//            painter.setBrush(QBrush());
//            painter.setPen(QPen(QColor(255 - colorText.red(),
//                                       255 - colorText.green(),
//                                       255 - colorText.blue()),
//                                3,
//                                Qt::DashDotLine));
//            painter.drawRect(rect);
        }
        else
        {
//            painter.setPen(QPen(colorFlagBound));
//            painter.setBrush(QBrush(colorFlagBound));
//            painter.drawRect(rect);
        }

        QString text;
        if (i < 4)
        {
            for (int iter = 0; iter < 2; ++iter)
            {
                QString text = iter == 0? names[i] : countries[i];
                QFont font = this->font;
                QRect boundRect;
                QRect target(rect.topLeft().x(),
                             rect.topLeft().y() + iter * rect.height() / 2,
                             rect.width(),
                             rect.height() / 2);
                Utils::setFontSize(text, font, target, boundRect);

                QPoint pointOfBaseline(
                            target.topLeft().x() + (target.width() - boundRect.width()) / 2,
                            target.topLeft().y() + (target.height() + QFontMetrics(font).ascent()) / 2);

                QPainterPath path;
                path.addText(pointOfBaseline, font, text);

                painter.setPen(QPen(colorTextBound, withTextBound));
                painter.setBrush(QBrush(colorText));
                painter.drawPath(path);
            }
        }
        else if (i == 8)
        {
            QString text = tournamentCategory;
            QFont font = this->font;
            QRect boundRect;
            Utils::setFontSize(text, font, rect, boundRect);

            QPoint pointOfBaseline(
                        rect.topLeft().x() + (rect.width() - boundRect.width()) / 2,
                        rect.topLeft().y() + (rect.height() + QFontMetrics(font).ascent()) / 2);


            QPainterPath path;
            path.addText(pointOfBaseline, font, text);

            painter.setPen(QPen(colorTextBound, withTextBound));
            painter.setBrush(QBrush(colorText));
            painter.drawPath(path);
        }
        else
        {
//            QString text;
//            if      (i == 4) text = "1 Флаг";
//            else if (i == 5) text = "2 Флаг";
//            else if (i == 6) text = "3 Флаг";
//            else if (i == 7) text = "4 Флаг";
//            painter.setPen(QColor(255 - colorFlagBound.red(),
//                                  255 - colorFlagBound.green(),
//                                  255 - colorFlagBound.blue()));
//            painter.setFont(font);
//            painter.drawText(rect, Qt::AlignCenter, text);

            if (!flags[i - 4].isNull())
            {
                QPixmap scaledImg = flags[i - 4].scaled(rect.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                painter.drawPixmap(rect.x() + (rect.width() - scaledImg.width()) / 2,
                                   rect.y() + (rect.height() - scaledImg.height()) / 2,
                                   scaledImg);
            }
        }
    }
    painter.end();

    painter.begin(this);
    const QPixmap imageScaled = img.scaled(
                                    size().width(),
                                    size().height(),
                                    Qt::KeepAspectRatio,
                                    Qt::SmoothTransformation);

    const int offsetW = (size().width()  - imageScaled.size().width() ) / 2;
    const int offsetH = (size().height() - imageScaled.size().height()) / 2;
    painter.drawPixmap(offsetW, offsetH, imageScaled);
    //qDebug() << "Paint in: " << t.elapsed();
}


void DialogAwardWidget::setTournamentCategory(const QString& value)
{
    tournamentCategory = value;
    repaint();
}

void DialogAwardWidget::setPlayer(const int player, const QString& name, const QString& location,
                                  const QByteArray& imageFlag)
{
    names[player] = name;
    countries[player] = location;
    flags[player].loadFromData(imageFlag);
    repaint();
}

void DialogAwardWidget::resetAll()
{
    tournamentCategory = "";

    names.clear();
    names.resize(4);

    countries.clear();
    countries.resize(4);

    flags.clear();
    flags.resize(4);
}


