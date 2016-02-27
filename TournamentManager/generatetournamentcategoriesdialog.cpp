#include "generatetournamentcategoriesdialog.h"
#include "ui_generatetournamentcategoriesdialog.h"

GenerateTournamentCategoriesDialog::GenerateTournamentCategoriesDialog(long long tournamentUID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GenerateTournamentCategoriesDialog),
    mTournamentUID(tournamentUID)
{
    ui->setupUi(this);

    fillSexCB();
    fillTypeCB();

    connect(this, &GenerateTournamentCategoriesDialog::accepted, [this] ()
    {
        QString name = ui->nameLE->text().trimmed();
        long long sexUID = ui->sexCB->currentData(Qt::UserRole).toLongLong();
        long long typeUID = ui->typeCB->currentData(Qt::UserRole).toLongLong();
        int ageFrom = ui->ageFromSB->value();
        int ageTill = ui->ageTillSB->value();

        QString weightCorrect = ui->weightsLE->text().trimmed().replace(",", ".");
        QStringList weights = weightCorrect.split(";", QString::SkipEmptyParts);
        for (int index = 0; index < (int)weights.size(); index++)
        {
            QString modifyName = name;
            double weightFrom = weights[index].toDouble();
            double weightTill = weightFrom;
            if (index + 1 < (int)weights.size())
            {
                weightTill = weights[index + 1].toDouble();

                modifyName += ", " +
                        ui->typeCB->currentText() + ", " +
                        QString::number(weightFrom) + "-" + QString::number(weightTill);
            }
            else
            {
                weightTill = 100000.0;

                modifyName += ", " +
                        ui->typeCB->currentText() + ", " +
                        QString::number(weightFrom) + "+";
            }

            QSqlQuery query;
            if (!query.prepare("INSERT INTO TOURNAMENT_CATEGORIES("
                               "NAME, AGE_FROM, AGE_TILL, WEIGHT_FROM, WEIGHT_TILL,"
                               "SEX_FK, TYPE_FK, TOURNAMENT_FK) "
                               "VALUES (?, ?, ?, ?, ?, ?, ?, ?)"))
                qDebug() << query.lastError().text();
            query.bindValue(0, modifyName);
            query.bindValue(1, ageFrom);
            query.bindValue(2, ageTill);
            query.bindValue(3, weightFrom);
            query.bindValue(4, weightTill);
            query.bindValue(5, sexUID);
            query.bindValue(6, typeUID);
            query.bindValue(7, mTournamentUID);

            if (!query.exec())
                qDebug() << query.lastError().text();
            else
            {
                QMessageBox::information(this, "Добавлена новая категория", "Добавлена новая категория: " + modifyName);
            }

            query.clear();
        }
    });
}

GenerateTournamentCategoriesDialog::~GenerateTournamentCategoriesDialog()
{
    delete ui;
}

void GenerateTournamentCategoriesDialog::fillSexCB()
{
    ui->sexCB->clear();

    QSqlQuery query;
    if (!query.prepare("SELECT * FROM SEXES"))
        qDebug() << query.lastError().text();
    if (query.exec())
    {
        int index = 0;
        while (query.next())
        {
            ui->sexCB->addItem(query.value("NAME").toString());
            ui->sexCB->setItemData(index, query.value("UID").toLongLong(), Qt::UserRole);
            ++index;
        }
    }
    else
    {
        qDebug() << query.lastError().text();
    }
}

void GenerateTournamentCategoriesDialog::fillTypeCB()
{
    ui->typeCB->clear();

    QSqlQuery query;
    if (!query.prepare("SELECT * FROM TYPES"))
        qDebug() << query.lastError().text();
    if (query.exec())
    {
        int index = 0;
        while (query.next())
        {
            ui->typeCB->addItem(query.value("NAME").toString());
            ui->typeCB->setItemData(index, query.value("UID").toLongLong(), Qt::UserRole);
            ++index;
        }
    }
    else
    {
        qDebug() << query.lastError().text();
    }
}
