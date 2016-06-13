#include "countryiconsdialog.h"
#include "ui_countryiconsdialog.h"
#include <QDesktopServices>

CountryIconsDialog::CountryIconsDialog(long long tournamentUID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CountryIconsDialog),
    mTournamentUID(tournamentUID)
{
    ui->setupUi(this);
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

    connect(ui->closeBtn, &QPushButton::clicked, [this] ()
    {
        accept();
    });

    connect(ui->countryRB, &QRadioButton::toggled, this, &CountryIconsDialog::onRadioButtonClick);
    connect(ui->regionRB, &QRadioButton::toggled, this, &CountryIconsDialog::onRadioButtonClick);
    connect(ui->regionUnitRB, &QRadioButton::toggled, this, &CountryIconsDialog::onRadioButtonClick);
    connect(ui->clubRB, &QRadioButton::toggled, this, &CountryIconsDialog::onRadioButtonClick);

    onRadioButtonClick();

    ui->entitiesTW->setColumnWidth(1, 300);
    fillEntities();
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
    while (ui->entitiesTW->rowCount() > 0)
        ui->entitiesTW->removeRow(0);

    QString foreignKey = mCurrentTableEng.left(mCurrentTableEng.size() - 1) + "_FK";
    if (mCurrentTableEng.contains("countries", Qt::CaseInsensitive))
        foreignKey = "COUNTRY_FK";

    QSqlQuery query;
    if (!query.prepare("SELECT DISTINCT c.NAME as nn, c.UID as uu, c.FLAG as ff "
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
    int rowIndex = 0;
    while (query.next())
    {
        ui->entitiesTW->insertRow(rowIndex);

        QString name = query.value("nn").toString();
        long long uid = query.value("uu").toLongLong();
        QTableWidgetItem* item = new QTableWidgetItem(name);
        item->setData(Qt::UserRole, uid);
        ui->entitiesTW->setItem(rowIndex, 1, item);

        QPushButton * flagButton = new QPushButton();
        QByteArray byteArray = QByteArray::fromBase64(query.value("ff").toString().toLocal8Bit());
        if (byteArray.size() > 0)
        {
            QImage flag = QImage::fromData(byteArray);
            flag = flag.scaledToHeight(50);
            QPixmap pixmap;
            pixmap.convertFromImage(flag);
            flagButton->setIcon(QIcon(pixmap));
            flagButton->setIconSize(pixmap.rect().size());
        }
        flagButton->setFlat(true);

        connect(flagButton, &QPushButton::clicked, [this, flagButton, rowIndex]
        {
            if (rowIndex < ui->entitiesTW->rowCount())
            {
                bool ok = false;
                long long uid = ui->entitiesTW->item(rowIndex, 1)->data(Qt::UserRole).toLongLong(&ok);
                if (ok)
                {
                    QString openFileName = QFileDialog::getOpenFileName(this, "Выберете флаг для загрузки");
                    if (openFileName.size() > 0)
                    {
                        QImage image(openFileName);
                        image = image.scaledToHeight(250);

                        QByteArray imageBytes;
                        QBuffer inBuffer(&imageBytes);
                        inBuffer.open(QIODevice::WriteOnly);
                        image.save(&inBuffer, "PNG");
                        QString flagBase64 = QString::fromLocal8Bit(imageBytes.toBase64().data());

                        QSqlQuery newFlagIcon;
                        newFlagIcon.prepare("UPDATE " + mCurrentTableEng + " SET FLAG = ? WHERE UID = ?");
                        newFlagIcon.addBindValue(flagBase64);
                        newFlagIcon.addBindValue(uid);
                        if (!newFlagIcon.exec())
                            qDebug() << newFlagIcon.lastError().text();
                        else
                        {
                            QImage flag = image;
                            flag = flag.scaledToHeight(50);
                            QPixmap pixmap;
                            pixmap.convertFromImage(flag);
                            flagButton->setIcon(QIcon(pixmap));
                            flagButton->setIconSize(pixmap.rect().size());
                        }
                    }
                }
            }
        });

        ui->entitiesTW->setCellWidget(rowIndex, 0, flagButton);


        QPushButton* deleteButton = new QPushButton("Удалить флаг");
        deleteButton->setFlat(true);
        connect(deleteButton, &QPushButton::clicked, [this, flagButton, rowIndex]
        {
            if (rowIndex < ui->entitiesTW->rowCount())
            {
                bool ok = false;
                long long uid = ui->entitiesTW->item(rowIndex, 1)->data(Qt::UserRole).toLongLong(&ok);
                if (ok)
                {
                    QSqlQuery query;
                    if (!query.prepare("UPDATE " + mCurrentTableEng + " SET FLAG = ? WHERE UID = ?"))
                        qDebug() << query.lastError().text();
                    else
                    {
                        query.addBindValue(QString(""));
                        query.addBindValue(uid);
                        if (!query.exec())
                            qDebug() << query.lastError();
                        else
                            flagButton->setIcon(QIcon());
                    }
                }
            }
        });
        ui->entitiesTW->setCellWidget(rowIndex, 2, deleteButton);

        rowIndex++;
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
