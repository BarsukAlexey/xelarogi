#include "generatetournamentcategoriesdialog.h"
#include "ui_generatetournamentcategoriesdialog.h"
#include "db_utils.h"
#include "createtypedialog.h"
#include "dialog_create_age_category.h"

GenerateTournamentCategoriesDialog::GenerateTournamentCategoriesDialog(long long tournamentUID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GenerateTournamentCategoriesDialog),
    mTournamentUID(tournamentUID)
{
    ui->setupUi(this);

    fillSexCB();
    fillComboBoxAgeCategory();
    fillTypeCB();

    connect(ui->sexCB, &QComboBox::currentTextChanged, this, &GenerateTournamentCategoriesDialog::fillComboBoxAgeCategory);

    connect(this, &GenerateTournamentCategoriesDialog::accepted, [this] ()
    {
        long long ageCatUID = ui->comboBoxAgeCategory->currentData(Qt::UserRole).toLongLong();
        long long sexUID = ui->sexCB->currentData(Qt::UserRole).toLongLong();
        long long typeUID = ui->typeCB->currentData(Qt::UserRole).toLongLong();
        int ageFrom = ui->ageFromSB->value();
        int ageTill = ui->ageTillSB->value();

        int durationFighting = ui->duratiobFightingSB->value();
        int durationBreak = ui->durationBreakSB->value();
        int roundCount = ui->roundCountSB->value();
        //qDebug() << durationFighting << durationBreak << roundCount;

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

            QString ageStr;
            if (ageFrom == 0) ageStr = "до " + QString::number(ageTill);
            else if (ageTill == 99) ageStr = "от " + QString::number(ageFrom);
            else ageStr += QString::number(ageFrom) + "-" + QString::number(ageTill);


            QString modifyName = DBUtils::getField("NAME", "AGE_CATEGORIES", ageCatUID) + ", " +
                ageStr + " лет, " +
                ui->typeCB->currentText() + ", " +
                DBUtils::getNormanWeightRange(weightFrom, weightTill) + ".";

            QSqlQuery query;
            if (!query.prepare("INSERT INTO TOURNAMENT_CATEGORIES("
                               "NAME, AGE_CATEGORY_FK, AGE_FROM, AGE_TILL, WEIGHT_FROM, WEIGHT_TILL,"
                               "SEX_FK, TYPE_FK, TOURNAMENT_FK,"
                               "DURATION_FIGHING, DURATION_BREAK, ROUND_COUNT) "
                               "VALUES (?, ?, ?, ?, ?, ?,    ?, ?, ?,   ?, ?, ?)"))
                qDebug() << query.lastError().text();
            query.addBindValue(modifyName);
            query.addBindValue(ageCatUID);
            query.addBindValue(ageFrom);
            query.addBindValue(ageTill);
            query.addBindValue(weightFrom);
            query.addBindValue(weightTill);

            query.addBindValue(sexUID);
            query.addBindValue(typeUID);
            query.addBindValue(mTournamentUID);

            query.addBindValue(durationFighting);
            query.addBindValue(durationBreak);
            query.addBindValue(roundCount);

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

void GenerateTournamentCategoriesDialog::fillComboBoxAgeCategory()
{
    ui->comboBoxAgeCategory->clear();

    QSqlQuery query("SELECT * FROM AGE_CATEGORIES WHERE SEX_FK = ?");
    query.addBindValue(ui->sexCB->currentData(Qt::UserRole).toLongLong());
    if (!query.exec())
    {
        qDebug() << query.lastError();
        return ;
    }
    while (query.next())
    {
        ui->comboBoxAgeCategory->addItem(query.value("NAME").toString(), query.value("UID").toLongLong());
    }
}

void GenerateTournamentCategoriesDialog::on_pushButton_clicked()
{
    CreateTypeDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted)
    {
        fillTypeCB();
    }
}



void GenerateTournamentCategoriesDialog::on_pushButtonAddAgeCategory_clicked()
{
    DialogCreateAgeCategory(this, ui->sexCB->currentData(Qt::UserRole).toLongLong()).exec();
    fillComboBoxAgeCategory();
}
