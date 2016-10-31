#include "createtournamentcategoriesdialog.h"
#include "ui_createtournamentcategoriesdialog.h"




CreateTournamentCategoriesDialog::CreateTournamentCategoriesDialog(long long tournamentUID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateTournamentCategoriesDialog),
    mTournamentUID(tournamentUID)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window);

    ui->managerSqlTable->setSqlTable(
                "TOURNAMENT_CATEGORIES",
                "TOURNAMENT_FK = " + QString::number(mTournamentUID),
                QStringList() //<< "TOURNAMENT_FK"
                );
}

CreateTournamentCategoriesDialog::~CreateTournamentCategoriesDialog()
{
    delete ui;
}




//void CreateTournamentCategoriesDialog::addContextMenu()
//{
//    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
//    connect(ui->tableView, &QTableView::customContextMenuRequested, [this] (const QPoint& pos)
//    {
//        QMenu* menu = new QMenu();

//        QAction* deleteAction = new QAction("Удалить", menu);
//        connect(deleteAction, &QAction::triggered, [this, &pos] ()
//        {
//            QModelIndex index = ui->tableView->indexAt(pos);
//            QSqlRelationalTableModel* model = dynamic_cast<QSqlRelationalTableModel*>(ui->tableView->model());

//            long long uidTourCategory = model->data(model->index(index.row(), model->fieldIndex("UID"))).toLongLong();

//            if(DBUtils::getSetOfOrdersInTournamentCategory(uidTourCategory).isEmpty())
//            {
//                model->removeRow(index.row());
//                model->submitAll();
//                model->select();
//            }
//            else
//            {
//                QMessageBox::warning(this, "!", "Нельзя удалить эту турнирную категорию, так как есть участники в этой категории. Удалите их или смените им категорию");
//            }
//        });
//        menu->addAction(deleteAction);

//        menu->exec(ui->tableView->viewport()->mapToGlobal(pos));
//    });
//}



void CreateTournamentCategoriesDialog::on_pushButtonAddGroupOfCaterories_clicked()
{
    GenerateTournamentCategoriesDialog(mTournamentUID, this).exec();
    ui->managerSqlTable->updateData();
}
