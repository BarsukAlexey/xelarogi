#include "choosetournamentdialog.h"
#include "ui_choosetournamentdialog.h"

ChooseTournamentDialog::ChooseTournamentDialog(const QSqlDatabase &database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseTournamentDialog)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, [this, database] ()
    {
        if (ui->listWidget->selectedItems().size() > 0)
        {
            QString selectedTournamentUID = ui->listWidget->selectedItems()[0]->data(Qt::UserRole).toString();
            TournamentAdminDialog dlg(database, selectedTournamentUID.toLongLong(), this);
            dlg.exec();
        }
        else
        {
            QMessageBox::information(this,
                                     tr("Турнир не выбран"),
                                     tr("Выберете турнир, чтобы перейти к его редактированию")
                                     );
        }
    });

    ui->listWidget->clear();

    QSqlQuery query("SELECT * FROM TOURNAMENTS", database);
    if (query.exec())
    {
        while (query.next())
        {
            QString tournamentUID = query.value("UID").toString();
            QString tournamentName = query.value("NAME").toString();

            QListWidgetItem* item = new QListWidgetItem();
            item->setData(Qt::DisplayRole, tournamentName);
            item->setData(Qt::UserRole, tournamentUID);

            ui->listWidget->addItem(item);
        }
    }
}

ChooseTournamentDialog::~ChooseTournamentDialog()
{
    delete ui;
}
