#include "countryiconsdialog.h"
#include "ui_countryiconsdialog.h"
#include <QDesktopServices>

CountryIconsDialog::CountryIconsDialog(long long tournamentUID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CountryIconsDialog),
    mTournamentUID(tournamentUID)
{
    ui->setupUi(this);

    //ui->labelLink->setName("myLabel");
    //ui->labelLink->setText("<a href=\"Загрузить флаги...\">text</a>");
    ui->labelLink->setTextInteractionFlags(Qt::TextBrowserInteraction);

    QSqlQuery tournamentQuery("SELECT NAME FROM TOURNAMENTS WHERE UID = ?");
    tournamentQuery.bindValue(0, tournamentUID);
    if (tournamentQuery.exec())
    {
        while (tournamentQuery.next())
            ui->tournamentL->setText(tournamentQuery.value("NAME").toString());
    }
    else
        qDebug() << tournamentQuery.lastError().text();

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

        long long uid = ui->entitiesCB->currentData(Qt::UserRole).toLongLong();
        QSqlQuery newCountryIcon;
        newCountryIcon.prepare("UPDATE " + mCurrentTableEng + " SET FLAG = ? WHERE UID = ?");
        newCountryIcon.addBindValue(flagBase64);
        newCountryIcon.addBindValue(uid);
        if (!newCountryIcon.exec())
            qDebug() << newCountryIcon.lastError().text();

        ui->oldImageL->setPixmap(mPixmap);
        ui->newImageL->setPixmap(QPixmap());
        mPixmap = QPixmap();
    });

    connect(ui->entitiesCB, &QComboBox::currentTextChanged, [this] (const QString& )
    {
        long long uid = ui->entitiesCB->currentData(Qt::UserRole).toLongLong();
        QSqlQuery query;
        if (!query.prepare("SELECT * FROM " + mCurrentTableEng + " WHERE UID = ?"))
            qDebug() << query.lastError().text();
        else
        {
            ui->oldImageL->setText("Иконка не была загружена ранее");

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
        long long uid = ui->entitiesCB->currentData(Qt::UserRole).toLongLong();
        QSqlQuery query;
        if (!query.prepare("UPDATE " + mCurrentTableEng + " SET FLAG = ? WHERE UID = ?"))
            qDebug() << query.lastError().text();
        else
        {
            ui->oldImageL->setText("Иконка не была загружена ранее");

            query.addBindValue(QString(""));
            query.addBindValue(uid);
            if (!query.exec())
                qDebug() << query.lastError();
        }
    });

    connect(ui->countryRB, &QRadioButton::toggled, this, &CountryIconsDialog::onRadioButtonClick);
    connect(ui->regionRB, &QRadioButton::toggled, this, &CountryIconsDialog::onRadioButtonClick);
    connect(ui->regionUnitRB, &QRadioButton::toggled, this, &CountryIconsDialog::onRadioButtonClick);
    connect(ui->clubRB, &QRadioButton::toggled, this, &CountryIconsDialog::onRadioButtonClick);

    onRadioButtonClick();
}

CountryIconsDialog::~CountryIconsDialog()
{
    delete ui;
}

void CountryIconsDialog::on_labelLink_linkActivated(const QString &)
{
    QDesktopServices::openUrl(QUrl("https://en.wikipedia.org/wiki/Gallery_of_sovereign_state_flags"));
}

void CountryIconsDialog::fillEntities()
{
    if (mCurrentTableEng.contains("countries", Qt::CaseInsensitive))
        ui->entitiesL->setText("Выберите страну");
    else if (mCurrentTableEng.contains("units", Qt::CaseInsensitive))
        ui->entitiesL->setText("Выберите населенный пункт");
    else if (mCurrentTableEng.contains("regions", Qt::CaseInsensitive))
        ui->entitiesL->setText("Выберите регион");
    else if (mCurrentTableEng.contains("clubs", Qt::CaseInsensitive))
        ui->entitiesL->setText("Выберите клуб");
    else
    {
        ui->entitiesL->setText("Неизвестно");
        return;
    }

    ui->entitiesCB->clear();

    QString foreignKey = mCurrentTableEng.left(mCurrentTableEng.size() - 1) + "_FK";
    if (mCurrentTableEng.contains("countries", Qt::CaseInsensitive))
        foreignKey = "COUNTRY_FK";

    QSqlQuery query;
    if (!query.prepare("SELECT DISTINCT c.NAME as ff, c.UID as ss "
                       "FROM ORDERS as a "
                       "LEFT JOIN TOURNAMENT_CATEGORIES as b ON (a.TOURNAMENT_CATEGORY_FK = b.UID) "
                       "LEFT JOIN " + mCurrentTableEng + " as c ON (a." + foreignKey + " = c.UID) "
                       "WHERE b.TOURNAMENT_FK = ? "
                       "ORDER BY c.NAME"))
    {
        qDebug() << query.lastError().text();
        return;
    }
    query.bindValue(0, mTournamentUID);
    if (!query.exec())
    {
        qDebug() << query.lastError().text();
        return;
    }
    while (query.next())
    {
        ui->entitiesCB->addItem(query.value("ff").toString(), query.value("ss").toLongLong());
    }
}

void CountryIconsDialog::onRadioButtonClick()
{
    if (ui->countryRB->isChecked())
    {
        mCurrentTableEng = "COUNTRIES";
    }
    else if (ui->regionRB->isChecked())
    {
        mCurrentTableEng = "REGIONS";
    }
    else if (ui->regionUnitRB->isChecked())
    {
        mCurrentTableEng = "REGION_UNITS";
    }
    else if (ui->clubRB->isChecked())
    {
        mCurrentTableEng = "CLUBS";
    }

    fillEntities();
}
