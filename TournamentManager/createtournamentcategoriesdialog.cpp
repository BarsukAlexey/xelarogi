#include "createtournamentcategoriesdialog.h"
#include "ui_createtournamentcategoriesdialog.h"




CreateTournamentCategoriesDialog::CreateTournamentCategoriesDialog(long long tournamentUID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateTournamentCategoriesDialog),
    mTournamentUID(tournamentUID)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window);

    QMap<QString, QVariant> map;
    map["TOURNAMENT_FK"] = mTournamentUID;

    ui->managerSqlTable->setSqlTable(
                "TOURNAMENT_CATEGORIES",
                "TOURNAMENT_FK = " + QString::number(mTournamentUID),
                map
                );
}

CreateTournamentCategoriesDialog::~CreateTournamentCategoriesDialog()
{
    delete ui;
}


void CreateTournamentCategoriesDialog::on_pushButtonAddGroupOfCaterories_clicked()
{
    GenerateTournamentCategoriesDialog(mTournamentUID, this).exec();
    ui->managerSqlTable->updateMyData();
}
