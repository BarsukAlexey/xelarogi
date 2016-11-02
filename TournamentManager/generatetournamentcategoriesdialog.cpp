#include "generatetournamentcategoriesdialog.h"
#include "ui_generatetournamentcategoriesdialog.h"


GenerateTournamentCategoriesDialog::GenerateTournamentCategoriesDialog(long long tournamentUID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GenerateTournamentCategoriesDialog),
    mTournamentUID(tournamentUID)
{
    ui->setupUi(this);


    modelType = new QSqlRelationalTableModel(this);
    modelType->setTable("TYPES");
    modelType->setSort(1, Qt::AscendingOrder);
    modelType->select();
    ui->comboBoxType->setModel(modelType);
    ui->comboBoxType->setModelColumn(1);

    modelSex = new QSqlRelationalTableModel(this);
    modelSex->setTable("SEXES");
    modelSex->setSort(1, Qt::AscendingOrder);
    modelSex->select();
    ui->comboBoxSex->setModel(modelSex);
    ui->comboBoxSex->setModelColumn(1);

    modelAgeType = new QSqlRelationalTableModel(this);
    modelAgeType->setTable("AGE_CATEGORIES");
    modelAgeType->setSort(1, Qt::AscendingOrder);
    modelAgeType->select();
    ui->comboBoxAgeCategory->setModel(modelAgeType);
    ui->comboBoxAgeCategory->setModelColumn(1);

    modelTie = new QSqlRelationalTableModel(this);
    modelTie->setTable("IN_CASES_OF_TIE");
    modelTie->setSort(1, Qt::AscendingOrder);
    modelTie->select();
    ui->comboBoxTie->setModel(modelTie);
    ui->comboBoxTie->setModelColumn(1);

    QSettings settings;
    ui->lineEditWordAge->setText(settings.value("GenerateTournamentCategoriesDialog/lineEditWordAge", ui->lineEditWordAge->text()).toString());
    ui->lineEditAgeTill->setText(settings.value("GenerateTournamentCategoriesDialog/lineEditAgeTill", ui->lineEditAgeTill->text()).toString());
    ui->lineEditAgeFrom->setText(settings.value("GenerateTournamentCategoriesDialog/lineEditAgeFrom", ui->lineEditAgeFrom->text()).toString());

    ui->lineEditWordWeight->setText(settings.value("GenerateTournamentCategoriesDialog/lineEditWordWeight", ui->lineEditWordWeight->text()).toString());
    ui->lineEditWeightTill->setText(settings.value("GenerateTournamentCategoriesDialog/lineEditWeightTill", ui->lineEditWeightTill->text()).toString());
    ui->lineEditWeightFrom->setText(settings.value("GenerateTournamentCategoriesDialog/lineEditWeightFrom", ui->lineEditWeightFrom->text()).toString());



    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &GenerateTournamentCategoriesDialog::on_accepted);

    connect(ui->pushButtonType, &QPushButton::clicked, this, &GenerateTournamentCategoriesDialog::onPushButtonTypeClicked);
    connect(ui->pushButtonAddAgeCategory, &QPushButton::clicked, this, &GenerateTournamentCategoriesDialog::onPushButtonAddAgeCategoryClicked);


}


GenerateTournamentCategoriesDialog::~GenerateTournamentCategoriesDialog()
{
    QSettings settings;
    settings.setValue("GenerateTournamentCategoriesDialog/lineEditWordAge", ui->lineEditWordAge->text());
    settings.setValue("GenerateTournamentCategoriesDialog/lineEditAgeTill", ui->lineEditAgeTill->text());
    settings.setValue("GenerateTournamentCategoriesDialog/lineEditAgeFrom", ui->lineEditAgeFrom->text());

    settings.setValue("GenerateTournamentCategoriesDialog/lineEditWordWeight", ui->lineEditWordWeight->text());
    settings.setValue("GenerateTournamentCategoriesDialog/lineEditWeightTill", ui->lineEditWeightTill->text());
    settings.setValue("GenerateTournamentCategoriesDialog/lineEditWeightFrom", ui->lineEditWeightFrom->text());

    delete ui;
}



void GenerateTournamentCategoriesDialog::onPushButtonTypeClicked()
{
    DialogSqlTableManager dlg(this, "TYPES");
    dlg.exec();
    modelType->select();
}

void GenerateTournamentCategoriesDialog::onPushButtonAddAgeCategoryClicked()
{
    DialogSqlTableManager dlg(this, "AGE_CATEGORIES");
    dlg.exec();
    modelAgeType->select();
}


void GenerateTournamentCategoriesDialog::on_accepted()
{
    int indexType = ui->comboBoxType->currentIndex();
    if (indexType == -1)
    {
        QMessageBox::warning(this, "", "Выберите раздел");
        return ;
    }

    int indexAgeCategory = ui->comboBoxAgeCategory->currentIndex();
    if (indexAgeCategory == -1)
    {
        QMessageBox::warning(this, "", "Выберите возрастную категорию");
        return ;
    }

    if (ui->lineEditWordAge->text().simplified().isEmpty())
    {
        QMessageBox::warning(this, "", "Выберите слово \"лет\" в форме \"Возраст\"");
        return ;
    }
    if (ui->lineEditAgeTill->text().simplified().isEmpty())
    {
        QMessageBox::warning(this, "", "Выберите слово \"до\" в форме \"Возраст\"");
        return ;
    }
    if (ui->lineEditAgeFrom->text().simplified().isEmpty())
    {
        QMessageBox::warning(this, "", "Выберите слово \"от\" в форме \"Возраст\"");
        return ;
    }

    QStringList weights = ui->weightsLE->text().split(" ", QString::SkipEmptyParts);
    if (weights.isEmpty())
    {
        QMessageBox::warning(this, "", "Выберите граничные веса");
        return ;
    }
    QVector<double> w;
    w << 0;
    for (QString s : weights){
        bool ok = true;
        w << s.toDouble(&ok);
        if (!ok)
        {
            QMessageBox::warning(this, "", "Не возможно распознать число: " + s);
            return ;
        }
    }
    w << 1000;



    if (ui->lineEditWordWeight->text().simplified().isEmpty())
    {
        QMessageBox::warning(this, "", "Выберите слово \"кг\" в форме \"Вес\"");
        return ;
    }
    if (ui->lineEditWeightTill->text().simplified().isEmpty())
    {
        QMessageBox::warning(this, "", "Выберите слово \"до\" в форме \"Вес\"");
        return ;
    }
    if (ui->lineEditWeightFrom->text().simplified().isEmpty())
    {
        QMessageBox::warning(this, "", "Выберите слово \"свыше\" в форме \"Вес\"");
        return ;
    }


    QString message =
            DBUtils::insertTournamentCaregory(
                modelAgeType->data(modelAgeType->index(indexAgeCategory, 0), Qt::EditRole).toInt(),

                ui->ageFromSB->value(),
                ui->ageTillSB->value(),

                w,
                mTournamentUID,
                modelType->data(modelType->index(indexType, 0), Qt::EditRole).toInt(),
                modelSex->data(modelSex->index(ui->comboBoxSex->currentIndex(), 0), Qt::EditRole).toInt(),

                ui->duratiobFightingSB->value(),
                ui->durationBreakSB->value(),
                ui->roundCountSB->value(),

                modelTie->data(modelTie->index(ui->comboBoxTie->currentIndex(), 0), Qt::EditRole).toInt(),
                ui->spinBoxExtraRound->value(),


                ui->lineEditWordAge->text(),
                ui->lineEditAgeFrom->text(),
                ui->lineEditAgeTill->text(),

                ui->lineEditWordWeight->text(),
                ui->lineEditWeightFrom->text(),
                ui->lineEditWeightTill->text()
                );

    QMessageBox::information(this, "", message);

    accept();
}
