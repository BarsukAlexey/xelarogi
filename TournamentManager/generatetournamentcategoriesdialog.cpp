#include "generatetournamentcategoriesdialog.h"
#include "ui_generatetournamentcategoriesdialog.h"
#include "db_utils.h"

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

        int durationFighting = ui->duratiobFightingSB->value();
        int durationBreak = ui->durationBreakSB->value();
        int roundCount = ui->roundCountSB->value();
        qDebug() << durationFighting << durationBreak << roundCount;

        QString weightCorrect = ui->weightsLE->text().trimmed().replace(",", ".");
        QStringList weights = weightCorrect.split(";", QString::SkipEmptyParts);

        if (weights.size() > 0 && weights.front() != "0")
            weights.push_front("0");
        weights.push_back("100000.0");

        QString newCategoryMsg = "Добавлены новые категории:\n";

        for (int index = 0; index + 1 < weights.size(); index++)
        {
            double weightFrom = weights[index].toDouble();
            double weightTill = weights[index + 1].toDouble();
            QString modifyName = name + ", " +
                (ageFrom == 0? "до " : QString::number(ageFrom) + "-") + QString::number(ageTill) + " лет, " +
                ui->typeCB->currentText() + ", " +
                DBUtils::getNormanWeightRange(weightFrom, weightTill) + ".";

            QSqlQuery query;
            if (!query.prepare("INSERT INTO TOURNAMENT_CATEGORIES("
                               "NAME, AGE_FROM, AGE_TILL, WEIGHT_FROM, WEIGHT_TILL,"
                               "SEX_FK, TYPE_FK, TOURNAMENT_FK,"
                               "DURATION_FIGHING, DURATION_BREAK, ROUND_COUNT) "
                               "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"))
                qDebug() << query.lastError().text();
            query.bindValue(0, modifyName);
            query.bindValue(1, ageFrom);
            query.bindValue(2, ageTill);
            query.bindValue(3, weightFrom);
            query.bindValue(4, weightTill);
            query.bindValue(5, sexUID);
            query.bindValue(6, typeUID);
            query.bindValue(7, mTournamentUID);
            query.bindValue(8, durationFighting);
            query.bindValue(9, durationBreak);
            query.bindValue(10, roundCount);

            if (!query.exec())
                qDebug() << query.lastError().text();
            else
            {
                newCategoryMsg += "\t" + modifyName + "\n";
            }

            query.clear();
        }

        QMessageBox::information(this, "Добавлены новые категории", newCategoryMsg);

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
