#include "countryiconsdialog.h"
#include "ui_countryiconsdialog.h"
#include <QDesktopServices>

CountryIconsDialog::CountryIconsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CountryIconsDialog)
{
    ui->setupUi(this);

    //ui->labelLink->setName("myLabel");
    //ui->labelLink->setText("<a href=\"Загрузить флаги...\">text</a>");
    ui->labelLink->setTextInteractionFlags(Qt::TextBrowserInteraction);

    connect(ui->loadNewImageBtn, &QPushButton::clicked, [this] ()
    {
        QString openFileName = QFileDialog::getOpenFileName(this, "Выберете флаг для загрузки");
        QImage image(openFileName);
        image = image.scaledToHeight(250);

        mPixmap = QPixmap::fromImage(image);
        ui->newImageL->setPixmap(mPixmap);
    });

    connect(ui->saveBtn, &QPushButton::clicked, [this] ()
    {
        if (mPixmap.isNull()) return;

        QByteArray imageBytes;
        QBuffer inBuffer(&imageBytes);
        inBuffer.open(QIODevice::WriteOnly);
        mPixmap.toImage().save(&inBuffer, "PNG");
        QString flagBase64 = QString::fromLatin1(imageBytes.toBase64().data());

        long long uid = ui->countryCB->currentData(Qt::UserRole).toLongLong();
        QSqlQuery newCountryIcon;
        newCountryIcon.prepare("UPDATE COUNTRIES SET FLAG = ? WHERE UID = ?");
        newCountryIcon.addBindValue(flagBase64);
        newCountryIcon.addBindValue(uid);
        if (!newCountryIcon.exec())
            qDebug() << newCountryIcon.lastError().text();

        ui->oldImageL->setPixmap(mPixmap);
        ui->newImageL->setPixmap(QPixmap());
        mPixmap = QPixmap();
    });

    connect(ui->countryCB, &QComboBox::currentTextChanged, [this] (const QString& )
    {
        long long uid = ui->countryCB->currentData(Qt::UserRole).toLongLong();
        QSqlQuery query;
        if (!query.prepare("SELECT * FROM COUNTRIES WHERE UID = ?"))
            qDebug() << query.lastError().text();
        else
        {
            ui->oldImageL->setText("Нет загруженной иконки для страны");

            query.addBindValue(uid);
            if (query.exec())
            {
                if (query.next())
                {
                    QByteArray data = QByteArray::fromBase64(query.value("FLAG").toString().toStdString().c_str());
                    if (data.size() != 0)
                    {
                        QImage image = QImage::fromData(data);
                        image = image.scaledToHeight(250);
                        ui->oldImageL->setPixmap(QPixmap::fromImage(image));
                    }
                }
            }
            else
                qDebug() << query.lastError().text();
        }
    });

    connect(ui->pushButtonDelete, &QPushButton::clicked, [this] (){
        long long uid = ui->countryCB->currentData(Qt::UserRole).toLongLong();
        QSqlQuery query;
        if (!query.prepare("UPDATE COUNTRIES SET FLAG = ? WHERE UID = ?"))
            qDebug() << query.lastError().text();
        else
        {
            ui->oldImageL->setText("Нет загруженной иконки для страны");

            query.addBindValue(QString(""));
            query.addBindValue(uid);
            if (!query.exec())
                qDebug() << query.lastError();
        }
    });

    fillCountries();
}

CountryIconsDialog::~CountryIconsDialog()
{
    delete ui;
}

void CountryIconsDialog::fillCountries()
{
    ui->countryCB->clear();

    QSqlQuery query;
    if (!query.prepare("SELECT * FROM COUNTRIES") || !query.exec())
    {
        qDebug() << query.lastError().text();
        return;
    }
    while (query.next())
    {
        ui->countryCB->addItem(query.value("NAME").toString(), query.value("UID").toLongLong());
    }
}

void CountryIconsDialog::on_labelLink_linkActivated(const QString &)
{
    QDesktopServices::openUrl(QUrl("https://en.wikipedia.org/wiki/Gallery_of_sovereign_state_flags"));
}
