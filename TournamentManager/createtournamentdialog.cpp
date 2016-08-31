#include "createtournamentdialog.h"
#include "ui_createtournamentdialog.h"

CreateTournamentDialog::CreateTournamentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateTournamentDialog)
{
    ui->setupUi(this);

    ui->startDate->setDate(QDate::currentDate());
    ui->endDate->setDate(QDate::currentDate());
    ui->weightDate->setDate(QDate::currentDate());

    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(checkValues(QAbstractButton*)));

    connect(this, &CreateTournamentDialog::accepted, [this] ()
    {
        QSqlQuery query;
        if (!query.prepare("INSERT INTO TOURNAMENTS("
                               "NAME, "
                               "DATE_BEGIN, DATE_END, DATE_WEIGHTING, "
                               "TEXT_DAT_RANGE, HOST, "
                               "MAIN_JUDGE, MAIN_SECRETARY, ASSOCIATE_MAIN_JUDGE "
                           ") "
                           "VALUES(?,   ?,?,?,   ?,?,   ?,?,?)"))
        {
            qDebug() << query.lastError();
            return;
        }
        query.addBindValue(ui->nameLE->text());

        query.addBindValue(ui->startDate->date().toString("yyyy-MM-dd"));
        query.addBindValue(ui->endDate->date().toString("yyyy-MM-dd"));
        query.addBindValue(ui->weightDate->date().toString("yyyy-MM-dd"));

        query.addBindValue(ui->lineEdit_TextDataRange->text());
        query.addBindValue(ui->lineEditHost->text());


        query.addBindValue(ui->mainJudgeLE->text());
        query.addBindValue(ui->mainSecretaryLE->text());
        query.addBindValue(ui->mainJudgeHelperLE->text());


        if (!query.exec())
            qDebug() << query.lastError();
    });
}

CreateTournamentDialog::~CreateTournamentDialog()
{
    delete ui;
}

void CreateTournamentDialog::checkValues(QAbstractButton* b)
{
    if (ui->buttonBox->buttonRole(b) == QDialogButtonBox::AcceptRole)
    {
        QDate dataWeight = ui->weightDate->date();
        QDate beg = ui->startDate->date();
        QDate end = ui->endDate->date();
        if (dataWeight <= beg && beg <= end)
        {
            accept();
        }
        else
        {
            QMessageBox::warning(this, "", "Не выполняется условие: дата_взвешивания <= дата_начала <= дата_окончания");
        }
    }
    else
    {
        reject();
    }
    qDebug() << "checkValues";
}



