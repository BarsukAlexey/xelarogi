#include "dialogorderoftc.h"
#include "ui_dialogorderoftc.h"

DialogOrderOfTC::DialogOrderOfTC(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogOrderOfTC)
{
    ui->setupUi(this);
}

DialogOrderOfTC::~DialogOrderOfTC()
{
    delete ui;
}

void DialogOrderOfTC::setTournamentCategories(const QVector<std::pair<int, int>>& uidTC_Level,
                                              const QString& title)
{
    MyModel* model = new MyModel(uidTC_Level, this);

    ui->tableView->setModel(model);

    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();

    ui->labelTitle->setText(title);

    connect(ui->pushButtonUP, &QPushButton::clicked, this, &DialogOrderOfTC::onPushButtonUp);
    connect(ui->pushButtonDown, &QPushButton::clicked, this, &DialogOrderOfTC::onPushButtonDown);
}

QVector<std::pair<int, int> > DialogOrderOfTC::getTournamentCategories()
{
    MyModel * model = qobject_cast<MyModel *>(ui->tableView->model());
    return model->getTournamentCategotyUIDs();
}

void DialogOrderOfTC::onPushButtonUp()
{
    QModelIndex index = ui->tableView->currentIndex();
    if (!index.isValid() || index.row() == 0) return;
    QAbstractItemModel* model = ui->tableView->model();
    model->moveRow(QModelIndex(), index.row(), QModelIndex(), index.row() - 1);
}

void DialogOrderOfTC::onPushButtonDown()
{
    QModelIndex index = ui->tableView->currentIndex();
    QAbstractItemModel* model = ui->tableView->model();
    if (!index.isValid() || index.row() + 1 == model->rowCount()) return;
    model->moveRow(QModelIndex(), index.row(),
                   QModelIndex(), index.row() + 2);
}
