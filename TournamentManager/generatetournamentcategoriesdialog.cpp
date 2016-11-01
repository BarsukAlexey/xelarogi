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



    void (QComboBox:: *indexChangedSignal)(int) = &QComboBox::currentIndexChanged;
    connect(ui->comboBoxTie, indexChangedSignal, [this](const int x){
        ui->spinBoxExtraRound->setEnabled(x == 2);
    });

    connect(ui->sexCB, &QComboBox::currentTextChanged, this, &GenerateTournamentCategoriesDialog::fillComboBoxAgeCategory);

    connect(this, &GenerateTournamentCategoriesDialog::accepted, [this, tournamentUID] ()
    {

        QString weightCorrect = ui->weightsLE->text().simplified().replace(",", ".").replace(" ", "");
        QStringList weights = weightCorrect.split(";", QString::SkipEmptyParts);
        if (weights.size() > 0 && weights.front() != "0")
            weights.push_front("0");
        weights.push_back("100000.0");
        QVector<double> w;
        for (QString s : weights) w << s.toDouble();

        QString newCategoryMsg = insertInDB(
                                     ui->comboBoxAgeCategory->currentData(Qt::UserRole).toLongLong(),

                                     ui->ageFromSB->value(),
                                     ui->ageTillSB->value(),

                                     w,
                                     tournamentUID,
                                     ui->typeCB->currentData(Qt::UserRole).toLongLong(),
                                     ui->sexCB->currentData(Qt::UserRole).toLongLong(),

                                     ui->duratiobFightingSB->value(),
                                     ui->durationBreakSB->value(),
                                     ui->roundCountSB->value(),

                                     ui->comboBoxTie->currentIndex(),
                                     ui->spinBoxExtraRound->value(),


                                     ui->lineEditTypeAge->text(),
                                     ui->lineEditAgeFrom->text(),
                                     ui->lineEditAgeTill->text(),

                                     ui->lineEditTypeWeight->text(),
                                     ui->lineEditWeightFrom->text(),
                                     ui->lineEditWeightTill->text()
                                     );

        QMessageBox::information(this, "Добавлены новые категории", newCategoryMsg);

    });

    connect(ui->pushButtonAddType, &QPushButton::clicked, [this](){

    });

}


GenerateTournamentCategoriesDialog::~GenerateTournamentCategoriesDialog()
{
    delete ui;
}

QString GenerateTournamentCategoriesDialog::insertInDB(long long ageCatUID, int ageFrom, int ageTill,
                                                       QVector<double> weights,
                                                       long long tournamentUID, long long typeUID, long long sexUID,
                                                       int durationFighting, int durationBreak, int roundCount,
                                                       int IN_CASE_TIE, int DURATION_EXTRA_ROUND,
                                                       QString ageUnit, QString wordAgeFrom, QString wordAgeTill,
                                                       QString weightUnit, QString wordWeightFrom, QString wordWeightTill)
{
    QString newCategoryMsg = "Добавлены новые категории:\n";
    QString errors = "Ошибки:\n";

    if (IN_CASE_TIE != 2)
        DURATION_EXTRA_ROUND = 0;

    for (int index = 0; index + 1 < weights.size(); index++)
    {
        double weightFrom = weights[index];
        double weightTill = weights[index + 1];


        QString age;
        if      (ageFrom == 0)  age = wordAgeTill + " " + QString::number(ageTill) + " " + ageUnit;
        else if (99 <= ageTill) age = wordAgeFrom + " " + QString::number(ageFrom) + " " + ageUnit;
        else                    age = QString::number(ageFrom) + "-" + QString::number(ageTill) + " " + ageUnit;

        QString weight;
        if      (weightFrom == 0)   weight = wordWeightTill + " " + DBUtils::roundDouble(weightTill, 3) + " " + weightUnit;
        else if (300 <= weightTill) weight = wordWeightFrom + " " + DBUtils::roundDouble(weightFrom, 3) + " " + weightUnit;
        else                        weight = DBUtils::roundDouble(weightFrom, 3) + "-" + DBUtils::roundDouble(weightTill, 3) + " " + weightUnit;


        QString modifyName =
                DBUtils::getField("NAME", "TYPES", typeUID) + ", " +
                DBUtils::getField("NAME", "AGE_CATEGORIES", ageCatUID) + ", " +
                age + ", " +
                weight + ".";

        QSqlQuery query;
        if (!query.prepare("INSERT INTO TOURNAMENT_CATEGORIES( "
                           "NAME, AGE_CATEGORY_FK, AGE_FROM, AGE_TILL, WEIGHT_FROM, WEIGHT_TILL, "
                           "SEX_FK, TYPE_FK, TOURNAMENT_FK, "
                           "DURATION_FIGHING, DURATION_BREAK, ROUND_COUNT, "
                           "IN_CASE_TIE, DURATION_EXTRA_ROUND, "
                           "AGE, WEIGHT) "
                           "VALUES (?, ?, ?, ?, ?, ?,    ?, ?, ?,   ?, ?, ?,   ?, ?,     ?, ?)"))
            qDebug() << query.lastError().text();
        query.addBindValue(modifyName);
        query.addBindValue(ageCatUID);
        query.addBindValue(ageFrom);
        query.addBindValue(ageTill);
        query.addBindValue(weightFrom);
        query.addBindValue(weightTill);

        query.addBindValue(sexUID);
        query.addBindValue(typeUID);
        query.addBindValue(tournamentUID);

        query.addBindValue(durationFighting);
        query.addBindValue(durationBreak);
        query.addBindValue(roundCount);

        query.addBindValue(IN_CASE_TIE);
        query.addBindValue(DURATION_EXTRA_ROUND);

        query.addBindValue(age);
        query.addBindValue(weight);

        if (!query.exec())
        {
            qDebug() << query.lastError().text();
            errors += modifyName + "\n" +
                      query.lastError().databaseText() + "\n" +
                      query.lastError().driverText() + "\n\n";
        }
        else
        {
            newCategoryMsg += "\t" + modifyName + "\n";
        }

        query.clear();
    }

    return newCategoryMsg + "\n\n" + errors;
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

void GenerateTournamentCategoriesDialog::fillTie()
{
    ui->comboBoxTie->addItem("Клик мышкой");
    ui->comboBoxTie->addItem("Европейская система");
    ui->comboBoxTie->addItem("Дополнительный раунд");
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
