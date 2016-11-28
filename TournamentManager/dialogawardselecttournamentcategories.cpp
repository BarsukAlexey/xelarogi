#include "dialogawardselecttournamentcategories.h"
#include "ui_dialogawardselecttournamentcategories.h"



DialogAwardSelectTournamentCategories::DialogAwardSelectTournamentCategories(
        const int tournamentUID,
        QWidget *parent) :

    QDialog(parent),
    ui(new Ui::DialogAwardSelectTournamentCategories),
    tournamentUID(tournamentUID)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window);

    updateAllData();

}

DialogAwardSelectTournamentCategories::~DialogAwardSelectTournamentCategories()
{
    delete ui;
}

void DialogAwardSelectTournamentCategories::addRow(QTableWidget* table, const int uidTC)
{
    int row = table->rowCount();
    table->setRowCount(row + 1);

    QTableWidgetItem* item = new QTableWidgetItem(DBUtils::get("NAME", "TOURNAMENT_CATEGORIES", uidTC).toString());
    item->setData(Qt::UserRole, uidTC);
    table->setItem(
                row, 0,
                item);
    table->setItem(
                row, 1,
                new QTableWidgetItem(DBUtils::get("NAME", "TYPES", DBUtils::get("TYPE_FK", "TOURNAMENT_CATEGORIES", uidTC)).toString()));
    table->setItem(
                row, 2,
                new QTableWidgetItem(DBUtils::get("NAME", "SEXES", DBUtils::get("SEX_FK", "TOURNAMENT_CATEGORIES", uidTC)).toString()));
    table->setItem(
                row, 3,
                new QTableWidgetItem(DBUtils::get("AGE_FROM", "TOURNAMENT_CATEGORIES", uidTC).toString()));
    table->setItem(
                row, 4,
                new QTableWidgetItem(DBUtils::get("AGE_TILL", "TOURNAMENT_CATEGORIES", uidTC).toString()));
    table->setItem(
                row, 5,
                new QTableWidgetItem(DBUtils::get("WEIGHT_FROM", "TOURNAMENT_CATEGORIES", uidTC).toString()));
    table->setItem(
                row, 6,
                new QTableWidgetItem(DBUtils::get("WEIGHT_TILL", "TOURNAMENT_CATEGORIES", uidTC).toString()));
}

void DialogAwardSelectTournamentCategories::showGrid(QTableWidget* table)
{
    QModelIndex index = table->selectionModel()->currentIndex();
    if (!index.isValid())
        return;
    int uidTC = table->item(index.row(), 0)->data(Qt::UserRole).toInt();
    //qDebug() << "uidTC: " << uidTC;


    QString filter = DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", uidTC);

    DialogTournamentGrid dlg(this, filter, this->tournamentUID);
    dlg.showMaximized();
    dlg.exec();
    updateAllData();
}

void DialogAwardSelectTournamentCategories::updateAllData()
{
    ui->tableWidget->setRowCount(0);
    ui->tableWidgetReady->setRowCount(0);

    QSet<int> usedUidTC;

    for (const long long uidTC : DBUtils::getTournamentCategoryUIDs(tournamentUID))
    {
        QVector<std::pair<long long, std::pair<int, int>>> UIDOrder =
                DBUtils::getUIDsAndPlaces(uidTC, 4, true);
        if (UIDOrder.isEmpty())
            continue;
        addRow(ui->tableWidgetReady, uidTC);
        usedUidTC << uidTC;
    }
    ui->tableWidgetReady->resizeColumnsToContents();
    ui->tableWidgetReady->resizeRowsToContents();

    QVector<long long> tournamentCategoryUIDs = DBUtils::getTournamentCategoryUIDs(tournamentUID);
    for (const long long uidTC : tournamentCategoryUIDs)
    {
        if (DBUtils::getNodes(uidTC).isEmpty() ||
            usedUidTC.contains(uidTC)) continue;
        addRow(ui->tableWidget, uidTC);
    }
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();
}


void DialogAwardSelectTournamentCategories::on_pushButtonShowGridLeft_clicked()
{
    showGrid(ui->tableWidget);
}

void DialogAwardSelectTournamentCategories::on_pushButtonShowGridRight_clicked()
{
   showGrid(ui->tableWidgetReady);
}
