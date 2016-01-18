#include "choosetournamentdialog.h"
#include "ui_choosetournamentdialog.h"

ChooseTournamentDialog::ChooseTournamentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseTournamentDialog)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, [this] ()
    {
        TournamentAdminDialog dlg(this);
        dlg.exec();
    });
}

ChooseTournamentDialog::~ChooseTournamentDialog()
{
    delete ui;
}
