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

QSize DialogAwardWidget::getImageSize()
{
    return image.size();
}

void DialogAwardWidget::setData(QByteArray& byteArray)
{
    //qDebug() << "DialogAwardWidget::setData  size" << byteArray.size();
    if (byteArray.isEmpty())
    {
        image = QPixmap();
        rects = QVector<QRect>();
        for (int i = 0; i < 9; ++i)
        {
            rects << QRect(0, 0, 100, 100);
        }
        font = QFont();
        colorText  = Qt::white;
        colorTextBound = Qt::black;
        colorFlagBound = Qt::red;
        withTextBound = 1;
    }
    else
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
    names << "1Фродо Бэггинс"
          << "2Бильбо Бэггинс"
          << "3Торин Дубощит"
          << "4Бард Лучник";
    countries.clear();
    countries << "Mordor"
              << "Harad"
              << "Lindon"
              << "Khand";
    tournamentCategory = "low kick, Women, 17-18  years, 56-60 kg.";
    repaint();
}

QByteArray DialogAwardWidget::getDate()
{
    QByteArray byteArray;
    QDataStream dataStream(&byteArray, QIODevice::WriteOnly);
    dataStream
            << image
            << rects
            << font
            << colorText
            << colorTextBound
            << colorFlagBound
            << withTextBound;
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
    return colorFlagBound;
}

void DialogAwardWidget::setColorBound(const QColor& color)
{
    colorFlagBound = color;
    repaint();
}

QColor DialogAwardWidget::getColorTextBound()
{
    return colorTextBound;
}

void DialogAwardWidget::setColorTextBound(const QColor& color)
{
    colorTextBound = color;
    repaint();
}


void DialogAwardWidget::onRectTextChanged(int row, const QRect& rect)
{
    rects[row] = rect;
    //qDebug() << "onRectTextChanged:" << rect;
    repaint();
}

void DialogAwardWidget::paintEvent(QPaintEvent* /*event*/)
{
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
            painter.setBrush(QBrush());
            painter.setPen(QPen(QColor(255 - colorText.red(),
                                       255 - colorText.green(),
                                       255 - colorText.blue()),
                                3,
                                Qt::DashDotLine));
            painter.drawRect(rect);
        }
        else
        {
            painter.setPen(QPen(colorFlagBound));
            painter.setBrush(QBrush(colorFlagBound));
            painter.drawRect(rect);
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
            QString text;
            if      (i == 4) text = "1 Флаг";
            else if (i == 5) text = "2 Флаг";
            else if (i == 6) text = "3 Флаг";
            else if (i == 7) text = "4 Флаг";
            painter.setPen(QColor(255 - colorFlagBound.red(),
                                  255 - colorFlagBound.green(),
                                  255 - colorFlagBound.blue()));
            painter.setFont(font);
            painter.drawText(rect, Qt::AlignCenter, text);
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

int DialogAwardWidget::getWithTextBound() const
{
    return withTextBound;
}

void DialogAwardWidget::setWithTextBound(int value)
{
    withTextBound = value;
    repaint();
}



DialogAward::DialogAward(const int tournamentUID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAward),
    tournamentUID(tournamentUID)
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
            << ui->radioButtonFlag3
            << ui->radioButtonTC;

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

    for (QRadioButton *r : radio)
    {
        connect(r, &QRadioButton::clicked, this, &DialogAward::onRadio);
    }

    connect(ui->spinBoxWidthTextBound, fun, [this](int value){
        ui->widgetAward->setWithTextBound(value);
    });

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

    QSize imageSize = ui->widgetAward->getImageSize();
    ui->labelImageWidth->setText(QString::number(imageSize.width()));
    ui->labelImageHeight->setText(QString::number(imageSize.height()));

    ui->spinBoxWidthTextBound->setValue(ui->widgetAward->getWithTextBound());

    onRadio();
}

void DialogAward::on_pushButtonLoadImg_clicked()
{
    QString openFileName = QFileDialog::getOpenFileName();
    if (openFileName.isEmpty())
        return;
    ui->widgetAward->setImage(openFileName);

    QSize imageSize = ui->widgetAward->getImageSize();
    ui->labelImageWidth->setText(QString::number(imageSize.width()));
    ui->labelImageHeight->setText(QString::number(imageSize.height()));
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

void DialogAward::on_pushButtonColorBoundText_clicked()
{
    QColor initColor = ui->widgetAward->getColorTextBound();
    QColorDialog dlg(initColor, this);
    connect(&dlg, &QColorDialog::currentColorChanged, [this](const QColor& color){
        ui->widgetAward->setColorTextBound(color);
    });
    if (dlg.exec() == QDialog::Rejected)
    {
        ui->widgetAward->setColorTextBound(initColor);
    }
}

void DialogAward::on_pushButtonGo_clicked()
{

    DialogAwardSelectTournamentCategories dlg(tournamentUID, this);
    dlg.showMaximized();
    if (dlg.exec() == QDialog::Rejected)
    {
        return;
    }




    QVector<QString> TCs;
    QVector<QVector<QString>> players;
    QVector<QVector<int>> names;
    QVector<QVector<int>> flags;
    QVector<QVector<int>> hymns;
    QMap<int, QString> mapNames;
    QMap<int, QByteArray> mapFlag;
    QMap<int, QByteArray> mapHymn;
    for (const int uidTC : DBUtils::getTournamentCategoryUIDs(tournamentUID))
    {
        QVector<std::pair<long long, std::pair<int, int>>> orderUIDs =
                DBUtils::getUIDsAndPlaces(uidTC, 4, true);
        if (orderUIDs.isEmpty())
            continue;

        TCs << DBUtils::get("NAME", "TOURNAMENT_CATEGORIES", uidTC).toString();
        players << QVector<QString>();
        names   << QVector<int>();
        flags   << QVector<int>();
        hymns   << QVector<int>();
        for (std::pair<long long, std::pair<int, int>> orderItem: orderUIDs)
        {
            const int orderUID = orderItem.first;
            players.back() << DBUtils::getSecondNameAndFirstName(orderUID);
            names  .back() << DBUtils::getLocalUIDOfOrderUID(orderUID, getTypeName());
            flags  .back() << DBUtils::getLocalUIDOfOrderUID(orderUID, getTypeFlag());
            hymns  .back() << DBUtils::getLocalUIDOfOrderUID(orderUID, getTypeHymn());
        }
    }
    for (QVector<int> vect: names)
        for (int localUID : vect)
            if (!mapNames.contains(localUID))
                 mapNames[localUID] = DBUtils::getLocalFKValue("NAME", localUID, getTypeName()).toString();

    for (QVector<int> vect: flags)
        for (int localUID : vect)
            if (!mapFlag.contains(localUID))
                 mapFlag[localUID] = QByteArray::fromBase64(
                                        DBUtils::getLocalFKValue("FLAG", localUID, getTypeFlag())
                                        .toString()
                                        .toLocal8Bit());

    for (QVector<int> vect: hymns)
        for (int localUID : vect)
            if (!mapHymn.contains(localUID))
            {
                mapHymn[localUID] = DBUtils::getLocalFKValue("HYMN", localUID, getTypeHymn()).toByteArray();
            }


    QString mainDirectory = QFileDialog::getExistingDirectory(this);
    if (mainDirectory.isEmpty())
        return;

    QFile file(QDir(mainDirectory).filePath("award.dat"));
    file.open(QIODevice::WriteOnly);
    QDataStream dataStream(&file);
    dataStream << ui->widgetAward->getDate()
               << TCs
               << players
               << names
               << flags
               << hymns
               << mapNames
               << mapFlag
               << mapHymn;
    file.flush();
    file.close();
    QMessageBox::information(this, "", "DONE!");
}

int DialogAward::getTypeName()
{
    if (ui->radioButtonNameCounty->isChecked()) return 0;
    if (ui->radioButtonNameRegion->isChecked()) return 1;
    if (ui->radioButtonNameCity  ->isChecked()) return 2;
    if (ui->radioButtonNameClub  ->isChecked()) return 3;
    return -1;
}

int DialogAward::getTypeFlag()
{
    if (ui->radioButtonFlagCounty->isChecked()) return 0;
    if (ui->radioButtonFlagRegion->isChecked()) return 1;
    if (ui->radioButtonFlagCity  ->isChecked()) return 2;
    if (ui->radioButtonFlagClub  ->isChecked()) return 3;
    return -1;
}

int DialogAward::getTypeHymn()
{
    if (ui->radioButtonHymnCounty->isChecked()) return 0;
    if (ui->radioButtonHymnRegion->isChecked()) return 1;
    if (ui->radioButtonHymnCity  ->isChecked()) return 2;
    if (ui->radioButtonHymnClub  ->isChecked()) return 3;
    return -1;
}
