#include "dialog_change_category.h"
#include "ui_dialogchangecategory.h"
#include "db_utils.h"

DialogChangeCategory::DialogChangeCategory(QString title, QVector<long long> category, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChangeCategory)
{
    ui->setupUi(this);

    ui->label->setText(title);

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList({"Категория", "Кол-во участников"}));

    for (long long uidCT : category)
    {
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);

        QTableWidgetItem *item;

        item = new QTableWidgetItem(DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", uidCT));
        item->setData(Qt::UserRole, uidCT);
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, item);

        item = new QTableWidgetItem(QString::number(DBUtils::getSetOfOrdersInTournamentCategory(uidCT).size()));
        item->setData(Qt::UserRole, uidCT);
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, item);
    }
    ui->tableWidget->resizeColumnsToContents();

    connect(ui->buttonBox, &QDialogButtonBox::accepted, [this]{
        QModelIndexList lst =  ui->tableWidget->selectionModel()->selectedRows();
        if (lst.size())
        {
            uidCategory = ui->tableWidget->item(lst.at(0).row(), 0)->data(Qt::UserRole).toLongLong();
            accept();
        }
    });

    connect(ui->buttonBox, &QDialogButtonBox::rejected, [this]{
        reject();
    });
}

DialogChangeCategory::~DialogChangeCategory()
{
    delete ui;
}
