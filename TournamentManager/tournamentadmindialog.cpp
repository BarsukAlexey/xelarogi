#include "tournamentadmindialog.h"
#include "ui_tournamentadmindialog.h"
#include "tournamentgriddialog2.h"

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
    connect(ui->createOrdersBtn, &QPushButton::clicked, [this, database, tournamentUID] ()
    {
        CreateTournamentOrdersDialog dlg(database, tournamentUID, this,
        {"IS_WEIGHTED", "IS_MEDICAL", "IS_ACCREDITATED", "IS_PAID", "COACH_FK", "CLUB_FK", "UID"});
        dlg.exec();
    });

    connect(ui->pushButtonTournamentGrid, &QPushButton::clicked, [this, database, tournamentUID] ()
    {
        TournamentGridDialog2 dlg(database, tournamentUID, this);
        dlg.exec();
    });
}

TournamentAdminDialog::~TournamentAdminDialog()
{
    delete ui;
}
