#include "dialogaward.h"
#include "ui_dialogaward.h"

DialogAwardWidget::DialogAwardWidget(QWidget* parent) :
    QWidget(parent)
{
}

void DialogAwardWidget::setImage(QString path)
{
    image.load(path);
    repaint();
}

void DialogAwardWidget::setData(QByteArray& byteArray)
{
    //qDebug() << "DialogAwardWidget::setData  size" << byteArray.size();
    if (byteArray.isEmpty())
    {
        image = QPixmap();
        rects = QVector<QRect>();
        for (int i = 0; i < 8; ++i)
        {
            rects << QRect(0, 0, 100, 100);
        }
        font = QFont();
        colorText  = Qt::white;
        colorBound = Qt::white;
    }
    else
    {
        QDataStream dataStream(&byteArray, QIODevice::ReadOnly);
        dataStream >> image
                >> rects
                >> font
                >> colorText
                >> colorBound;
    }
    repaint();
}

QByteArray DialogAwardWidget::getDate()
{
    QByteArray byteArray;
    QDataStream dataStream(&byteArray, QIODevice::WriteOnly);
    dataStream << image
               << rects
               << font
               << colorText
               << colorBound;
    return byteArray;
}

QRect DialogAwardWidget::getRects(int index)
{
    return rects[index];
}

QColor DialogAwardWidget::getColorText()
{
    return colorText;
}

void DialogAwardWidget::setColorText(const QColor& color)
{
    colorText = color;
    repaint();
}

QFont DialogAwardWidget::getFont()
{
    return font;
}

void DialogAwardWidget::setFont(const QFont& font)
{
    this->font = font;
    repaint();
}

QColor DialogAwardWidget::getColorBound()
{
    return colorBound;
}

void DialogAwardWidget::setColorBound(const QColor& color)
{
    colorBound = color;
    repaint();
}


void DialogAwardWidget::onRectTextChanged(int row, const QRect& rect)
{
    rects[row] = rect;
    //qDebug() << "onRectTextChanged:" << rect;
    repaint();
}

void DialogAwardWidget::paintEvent(QPaintEvent* event)
{
    //qDebug() << event->rect() << event->region();
    if (image.isNull())
        return;

    QTime t; t.start();

    QPainter painter(this);

    const double coef = qMin((double)size().width() / image.width(),
                             (double)size().height() / image.height());
    const QPixmap imageScaled = image.scaled(
                                    (int)(coef * image.width()),
                                    (int)(coef * image.height()));
    const int offsetW = (size().width()  - imageScaled.size().width() ) / 2;
    const int offsetH = (size().height() - imageScaled.size().height()) / 2;
    painter.drawPixmap(offsetW, offsetH, imageScaled);

    const double kw = (double)imageScaled.width()  / image.width();
    const double kh = (double)imageScaled.height() / image.height();
    for (int i = 0; i < rects.size(); ++i)
    {
        QRect rect = rects[i];
        rect.setX(offsetW + (int)(kw * rect.x()));
        rect.setY(offsetH + (int)(kh * rect.y()));
        rect.setWidth ((int)(kw * rects[i].width ()));
        rect.setHeight((int)(kh * rects[i].height()));


        painter.fillRect(rect, QColor(255 - colorText.red(),
                                      255 - colorText.green(),
                                      255 - colorText.blue()
                                      ));
        if (4 <= i)
        {
            painter.save();
            QPen p;
            p.setWidth(3);
            p.setColor(colorBound);
            painter.setPen(p);
            painter.drawRect(rect);
            painter.restore();
        }

        QFont font = this->font;
        QString text;
        if      (i == 0) text = "1Фродо Бэггинс\nMordor";
        else if (i == 1) text = "2Бильбо Бэггинс\nHarad";
        else if (i == 2) text = "3Торин Дубощит\nLindon ";
        else if (i == 3) text = "4Бард Лучник\nKhand";
        else if (i == 4) text = "Флаг1";
        else if (i == 5) text = "Флаг2";
        else if (i == 6) text = "Флаг3";
        else if (i == 7) text = "Флаг4";
        font.setPointSize(Utils::getFontSize(text, font, rect));
        painter.setFont(font);
        painter.setPen(colorText);
        painter.drawText(rect, Qt::AlignCenter, text);
    }

    qDebug() << "Paint in: " << t.elapsed();
}



DialogAward::DialogAward(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAward)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window);

    radio
            << ui->radioButtonName0
            << ui->radioButtonName1
            << ui->radioButtonName2
            << ui->radioButtonName3
            << ui->radioButtonFlag0
            << ui->radioButtonFlag1
            << ui->radioButtonFlag2
            << ui->radioButtonFlag3;

    model = new QSqlTableModel(this);
    model->setTable("AWARD");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    while (model->canFetchMore())
        model->fetchMore();

    ui->comboBoxName->setModel(model);

    ui->widgetTools->hide();

    void (QSpinBox::*fun)(int) = static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged);
    connect(ui->spinBoxX     , fun, this, &DialogAward::onInput);
    connect(ui->spinBoxY     , fun, this, &DialogAward::onInput);
    connect(ui->spinBoxWidth , fun, this, &DialogAward::onInput);
    connect(ui->spinBoxHeight, fun, this, &DialogAward::onInput);

    connect(ui->radioButtonName0, &QRadioButton::clicked, this, &DialogAward::onRadio);
    connect(ui->radioButtonName1, &QRadioButton::clicked, this, &DialogAward::onRadio);
    connect(ui->radioButtonName2, &QRadioButton::clicked, this, &DialogAward::onRadio);
    connect(ui->radioButtonName3, &QRadioButton::clicked, this, &DialogAward::onRadio);

    connect(ui->radioButtonFlag0, &QRadioButton::clicked, this, &DialogAward::onRadio);
    connect(ui->radioButtonFlag1, &QRadioButton::clicked, this, &DialogAward::onRadio);
    connect(ui->radioButtonFlag2, &QRadioButton::clicked, this, &DialogAward::onRadio);
    connect(ui->radioButtonFlag3, &QRadioButton::clicked, this, &DialogAward::onRadio);

    on_comboBoxName_currentIndexChanged(ui->comboBoxName->currentIndex());
}

DialogAward::~DialogAward()
{
    on_pushButtonSave_clicked();
    delete ui;
}

void DialogAward::on_pushButtonNew_clicked()
{
    bool ok;
    QString name = QInputDialog::getText(this, "", "Введите название шаблона",
                                         QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty())
        return;
    QSqlRecord record = model->record();
    record.setValue("NAME", name);
    model->insertRecord(model->rowCount(), record);
    if (!model->submitAll())
        model->revertAll();
}

void DialogAward::on_pushButtonDelete_clicked()
{
    model->removeRow(ui->comboBoxName->currentIndex());
    if (!model->submitAll())
        model->revertAll();
}

void DialogAward::on_comboBoxName_currentIndexChanged(int index)
{
    //qDebug() << "index:" << index;
    if (index == -1)
    {
        ui->widgetAward->hide();
        ui->widgetTools->hide();
        return;
    }
    QByteArray byteArray = model->index(index, 1).data(Qt::EditRole).toByteArray();
    ui->widgetAward->setData(byteArray);
    ui->widgetAward->show();
    ui->widgetTools->show();

    onRadio();
}

void DialogAward::on_pushButtonLoadImg_clicked()
{
    QString openFileName = QFileDialog::getOpenFileName();
    if (openFileName.isEmpty())
        return;
    ui->widgetAward->setImage(openFileName);
}

void DialogAward::onInput()
{

    for (int i = 0; i < radio.size(); ++i)
    {
        if (radio[i]->isChecked())
        {
            ui->widgetAward->onRectTextChanged(i, QRect(
                                                   ui->spinBoxX->value(),
                                                   ui->spinBoxY->value(),
                                                   ui->spinBoxWidth->value(),
                                                   ui->spinBoxHeight->value()
                                                   ));
            break;
        }
    }
}

void DialogAward::onRadio()
{

    for (int i = 0; i < radio.size(); ++i)
    {
        if (radio[i]->isChecked())
        {
            QRect rect = ui->widgetAward->getRects(i);

            void (QSpinBox::*fun)(int) = static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged);

            disconnect(ui->spinBoxX     , fun, this, &DialogAward::onInput);
            disconnect(ui->spinBoxY     , fun, this, &DialogAward::onInput);
            disconnect(ui->spinBoxWidth , fun, this, &DialogAward::onInput);
            disconnect(ui->spinBoxHeight, fun, this, &DialogAward::onInput);

            ui->spinBoxX->setValue(rect.x());
            ui->spinBoxY->setValue(rect.y());
            ui->spinBoxWidth->setValue(rect.width());
            ui->spinBoxHeight-> setValue(rect.height());

            connect(ui->spinBoxX     , fun, this, &DialogAward::onInput);
            connect(ui->spinBoxY     , fun, this, &DialogAward::onInput);
            connect(ui->spinBoxWidth , fun, this, &DialogAward::onInput);
            connect(ui->spinBoxHeight, fun, this, &DialogAward::onInput);
        }
    }
}

void DialogAward::on_pushButtonSave_clicked()
{
    int row = ui->comboBoxName->currentIndex();
    model->setData(model->index(ui->comboBoxName->currentIndex(), 1), ui->widgetAward->getDate());
    if (!model->submitAll())
    {
        model->revertAll();
        qDebug() << "on_pushButtonSave_clicked:: no submitAll in model";
    }
    ui->comboBoxName->setCurrentIndex(row);
}

void DialogAward::on_pushButtonColorText_clicked()
{
    QColor initColor = ui->widgetAward->getColorText();
    QColorDialog dlg(initColor, this);
    connect(&dlg, &QColorDialog::currentColorChanged, [this](const QColor& color){
        ui->widgetAward->setColorText(color);
    });
    if (dlg.exec() == QDialog::Rejected)
    {
        ui->widgetAward->setColorText(initColor);
    }
}

void DialogAward::on_pushButtonFont_clicked()
{
    QFont initFont = ui->widgetAward->getFont();
    QFontDialog dlg(initFont, this);
    connect(&dlg, &QFontDialog::currentFontChanged, [this](const QFont& font){
        ui->widgetAward->setFont(font);
    });
    if (dlg.exec() == QDialog::Rejected)
    {
        ui->widgetAward->setFont(initFont);
    }
}

void DialogAward::on_pushButtonColorBound_clicked()
{
    QColor initColor = ui->widgetAward->getColorBound();
    QColorDialog dlg(initColor, this);
    connect(&dlg, &QColorDialog::currentColorChanged, [this](const QColor& color){
        ui->widgetAward->setColorBound(color);
    });
    if (dlg.exec() == QDialog::Rejected)
    {
        ui->widgetAward->setColorBound(initColor);
    }
}
