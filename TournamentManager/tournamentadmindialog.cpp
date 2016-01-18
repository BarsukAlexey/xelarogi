#include "tournamentadmindialog.h"
#include "ui_tournamentadmindialog.h"

TournamentAdminDialog::TournamentAdminDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TournamentAdminDialog)
{
    ui->setupUi(this);
}

TournamentAdminDialog::~TournamentAdminDialog()
{
    delete ui;
}
