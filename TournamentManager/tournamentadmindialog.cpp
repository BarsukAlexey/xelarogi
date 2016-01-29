#include "tournamentadmindialog.h"
#include "ui_tournamentadmindialog.h"

TournamentAdminDialog::TournamentAdminDialog(const QSqlDatabase &database, long long tournamentUID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TournamentAdminDialog)
{
    ui->setupUi(this);

    ui->testLabel->setText("Tournament UID: " + QString::number(tournamentUID));

    connect(ui->ordersAccreditationBtn, &QPushButton::clicked, [this, database, tournamentUID] ()
    {
       OneFieldSetupDialog dlg(tournamentUID, "IS_ACCREDITATED", this);
       dlg.exec();
    });
    connect(ui->ordersMedicalBtn, &QPushButton::clicked, [this, database, tournamentUID] ()
    {
       OneFieldSetupDialog dlg(tournamentUID, "IS_MEDICAL", this);
       dlg.exec();
    });
    connect(ui->ordersPayedBtn, &QPushButton::clicked, [this, database, tournamentUID] ()
    {
       OneFieldSetupDialog dlg(tournamentUID, "IS_PAID", this);
       dlg.exec();
    });
    connect(ui->ordersWeightBtn, &QPushButton::clicked, [this, database, tournamentUID] ()
    {
       OneFieldSetupDialog dlg(tournamentUID, "IS_WEIGHTED", this);
       dlg.exec();
    });
}

TournamentAdminDialog::~TournamentAdminDialog()
{
    delete ui;
}
