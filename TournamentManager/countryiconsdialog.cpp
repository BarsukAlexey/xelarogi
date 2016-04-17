#include "countryiconsdialog.h"
#include "ui_countryiconsdialog.h"

CountryIconsDialog::CountryIconsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CountryIconsDialog)
{
    ui->setupUi(this);

    fillCountries();

    connect(ui->loadNewImageBtn, &QPushButton::clicked, [this] ()
    {
        QString pictureName = QFileDialog::getOpenFileName(this, "Выберете иконку для загрузки", QDir::currentPath(), "PNG (*.png);;Icon (*.ico)");
        QPixmap pixmap(pictureName);
        ui->newImageL->setScaledContents(true);
        ui->newImageL->setBackgroundRole(QPalette::Base);
        ui->newImageL->setPixmap(pixmap);

        mPixmap = pixmap;
    });

    connect(ui->saveBtn, &QPushButton::clicked, [this] ()
    {
        if (mPixmap.isNull()) return;

        QByteArray imageBytes;
        QBuffer inBuffer(&imageBytes);
        inBuffer.open( QIODevice::WriteOnly );
        mPixmap.toImage().save(&inBuffer, "PNG");

        QSqlQuery query("DELETE FROM COUNTRY_ICONS WHERE COUNTRY_FK = " + ui->countryCB->currentData(Qt::UserRole).toString());
        if (!query.exec())
            qDebug() << query.lastError().text();

        long long uid = ui->countryCB->currentData(Qt::UserRole).toLongLong();
        QSqlQuery newCountryIcon;
        newCountryIcon.prepare("INSERT INTO COUNTRY_ICONS(COUNTRY_FK, ICON) VALUES( ?, ?)");
        newCountryIcon.bindValue(0, uid);
        newCountryIcon.bindValue(1, imageBytes);
        if (!newCountryIcon.exec())
            qDebug() << newCountryIcon.lastError().text();

        ui->oldImageL->setPixmap(mPixmap);
    });

    ui->countryCB->addItem("Выберете страну для изменения иконки");
    ui->countryCB->setCurrentIndex(ui->countryCB->count() - 1);
}

CountryIconsDialog::~CountryIconsDialog()
{
    delete ui;
}

void CountryIconsDialog::fillCountries()
{
    ui->countryCB->clear();

    QSqlQuery query;
    if (!query.prepare("SELECT * FROM COUNTRIES"))
        qDebug() << query.lastError().text();
    else
    {
        if (query.exec())
        {
            int index = 0;
            while (query.next())
            {
                long long uid = query.value("UID").toLongLong();
                QString name = query.value("NAME").toString();

                ui->countryCB->addItem(name);
                ui->countryCB->setItemData(index, uid, Qt::UserRole);
                ++index;
            }
        }
        else
            qDebug() << query.lastError().text();
    }

    connect(ui->countryCB, &QComboBox::currentTextChanged, [this] (const QString& text)
    {
        long long uid = ui->countryCB->currentData(Qt::UserRole).toLongLong();
        QSqlQuery query;
        if (!query.prepare("SELECT * FROM COUNTRY_ICONS WHERE COUNTRY_FK = ?"))
            qDebug() << query.lastError().text();
        else
        {
            ui->oldImageL->setScaledContents(true);
            ui->oldImageL->setBackgroundRole(QPalette::Base);
            ui->oldImageL->setText("Нет загруженной иконки для страны");

            query.bindValue(0, uid);
            if (query.exec())
            {
                if (query.next())
                {
                    QByteArray data = query.value("ICON").toByteArray();
                    if (data.size() != 0)
                    {
                        QPixmap pixmap;
                        pixmap.loadFromData(data);
                        ui->oldImageL->setPixmap(pixmap);
                    }
                }
            }
            else
                qDebug() << query.lastError().text();
        }
    });
}
