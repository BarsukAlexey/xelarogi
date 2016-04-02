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

    connect(this, &CreateTournamentDialog::accepted, [this] ()
    {
        QString name = ui->nameLE->text();
        QString shortName = ui->shortNameLE->text();
        QDate startDate = ui->startDate->date();
        QDate endDate = ui->endDate->date();

        QSqlQuery query;
        if (!query.prepare("INSERT INTO TOURNAMENTS("
                      "NAME, SHORTNAME, "
                      "DATE_BEGIN, DATE_END, "
                      "MAIN_JUDGE, MAIN_SECRETARY, ASSOCIATE_MAIN_JUDGE, "
                      "HOST, DATE_WEIGHTING"
                      ") "
                      "VALUES(?, ?, ?,    ?, ?, ?,   ?, ?, ?)"))
            qDebug() << query.lastError().text();
//        query.bindValue(0, name);
//        query.bindValue(1, shortName);
//        query.bindValue(2, startDate.toString("yyyy-MM-dd"));
//        query.bindValue(3, endDate.toString("yyyy-MM-dd"));
//        query.bindValue(4, ui->mainJudgeLE->text());
//        query.bindValue(5, ui->mainSecretaryLE->text());
//        query.bindValue(6, ui->mainJudgeHelperLE->text());
//        query.bindValue(7, ui->lineEditHost->text());
//        query.bindValue(8, ui->weightDate->date().toString("yyyy-MM-dd"));
        query.addBindValue(name);
        query.addBindValue(shortName);
        query.addBindValue(startDate.toString("yyyy-MM-dd"));
        query.addBindValue(endDate.toString("yyyy-MM-dd"));
        query.addBindValue(ui->mainJudgeLE->text());
        query.addBindValue(ui->mainSecretaryLE->text());
        query.addBindValue(ui->mainJudgeHelperLE->text());
        query.addBindValue(ui->lineEditHost->text());
        query.addBindValue(ui->weightDate->date().toString("yyyy-MM-dd"));

        if (!query.exec())
            qDebug() << query.lastError();
    });
}

CreateTournamentDialog::~CreateTournamentDialog()
{
    delete ui;
}

