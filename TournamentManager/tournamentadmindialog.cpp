#include "tournamentadmindialog.h"
#include "ui_tournamentadmindialog.h"

TournamentAdminDialog::TournamentAdminDialog(const QSqlDatabase &database, long long tournamentUID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TournamentAdminDialog)
{
    ui->setupUi(this);

    ui->testLabel->setText("Tournament UID: " + QString::number(tournamentUID));
}

TournamentAdminDialog::~TournamentAdminDialog()
{
    delete ui;
}
