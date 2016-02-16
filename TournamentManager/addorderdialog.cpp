#include "addorderdialog.h"
#include "ui_addorderdialog.h"

AddOrderDialog::AddOrderDialog(long long tournamentUID, QWidget *parent) :
    QDialog(parent),
    mTournamentUID(tournamentUID),
    ui(new Ui::AddOrderDialog)
{
    ui->setupUi(this);

    connect(this, &AddOrderDialog::accepted, this, &AddOrderDialog::onOkBtn);

    QSqlQuery query;

    //раздел
    query.prepare("SELECT * FROM TYPES");
    if (query.exec())
    {
        int index = 0;
        while (query.next())
        {
            ui->typesCB->addItem(query.value("NAME").toString(), Qt::DisplayRole);
            ui->typesCB->setItemData(index, query.value("UID"), Qt::UserRole);
            ++index;
        }
    }
    else
    {
        query.lastError().text();
    }
    query.clear();

    //спортивная разряд
    query.prepare("SELECT * FROM SPORT_CATEGORIES");
    if (query.exec())
    {
        int index = 0;
        while (query.next())
        {
            ui->sportCategoriesCB->addItem(query.value("NAME").toString(), Qt::DisplayRole);
            ui->sportCategoriesCB->setItemData(index, query.value("UID"), Qt::UserRole);
            ++index;
        }
    }
    else
    {
        query.lastError().text();
    }
    query.clear();

    //категория турнира
    query.prepare("SELECT * FROM TOURNAMENT_CATEGORIES WHERE TOURNAMENT_FK = ?");
    query.bindValue(0, tournamentUID);
    if (query.exec())
    {
        int index = 0;
        while (query.next())
        {
            ui->tournamentCategoriesCB->addItem(query.value("NAME").toString(), Qt::DisplayRole);
            ui->tournamentCategoriesCB->setItemData(index, query.value("UID"), Qt::UserRole);
            ++index;
        }
    }
    else
    {
        query.lastError().text();
    }
    query.clear();

    //клуб
    query.prepare("SELECT * FROM CLUBS");
    if (query.exec())
    {
        int index = 0;
        while (query.next())
        {
            ui->clubsCB->addItem(query.value("NAME").toString(), Qt::DisplayRole);
            ui->clubsCB->setItemData(index, query.value("UID"), Qt::UserRole);
            ++index;
        }
    }
    else
    {
        query.lastError().text();
    }
    query.clear();

    //тренер
    query.prepare("SELECT * FROM COACHS");
    if (query.exec())
    {
        int index = 0;
        while (query.next())
        {
            ui->coachsCB->addItem(query.value("NAME").toString(), Qt::DisplayRole);
            ui->coachsCB->setItemData(index, query.value("UID"), Qt::UserRole);
            ++index;
        }
    }
    else
    {
        query.lastError().text();
    }
    query.clear();

    //страна
    query.prepare("SELECT * FROM COUNTRIES");
    if (query.exec())
    {
        int index = 0;
        while (query.next())
        {
            ui->countriesCB->addItem(query.value("NAME").toString(), Qt::DisplayRole);
            ui->countriesCB->setItemData(index, query.value("UID"), Qt::UserRole);
            ++index;
        }
    }
    else
    {
        query.lastError().text();
    }
    query.clear();

    //регион
    query.prepare("SELECT * FROM REGIONS");
    if (query.exec())
    {
        int index = 0;
        while (query.next())
        {
            ui->regionsCB->addItem(query.value("NAME").toString(), Qt::DisplayRole);
            ui->regionsCB->setItemData(index, query.value("UID"), Qt::UserRole);
            ++index;
        }
    }
    else
    {
        query.lastError().text();
    }
    query.clear();

    //населенный пункт
    query.prepare("SELECT * FROM REGION_UNITS");
    if (query.exec())
    {
        int index = 0;
        while (query.next())
        {
            ui->regionUnitsCB->addItem(query.value("NAME").toString(), Qt::DisplayRole);
            ui->regionUnitsCB->setItemData(index, query.value("UID"), Qt::UserRole);
            ++index;
        }
    }
    else
    {
        query.lastError().text();
    }
    query.clear();

    //название турнира
    query.prepare("SELECT * FROM TOURNAMENTS WHERE UID = ?");
    query.bindValue(0, tournamentUID);
    if (query.exec() && query.next())
    {
        ui->tournamentLabel->setText(query.value("NAME").toString());
    }
    else
    {
        query.lastError().text();
    }
    query.clear();
}

AddOrderDialog::~AddOrderDialog()
{
    delete ui;
}

void AddOrderDialog::onOkBtn()
{

}
