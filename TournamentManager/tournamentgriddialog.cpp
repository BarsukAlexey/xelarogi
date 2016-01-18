#include "tournamentgriddialog.h"
#include "ui_tournamentgriddialog.h"

TournamentGridDialog::TournamentGridDialog(const QSqlDatabase& database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TournamentGridDialog)
{
    ui->setupUi(this);

    QSqlQuery query("SELECT * FROM ORDERS", database);
    if (query.exec())
    {
        while (query.next())
        {
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0,
                                     new QTableWidgetItem(
                                         query.value("SECOND_NAME").toString() + " " +
                                         query.value("FIRST_NAME").toString() + " " +
                                         query.value("PATRONYMIC").toString()
                                    )
                                );
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1,
                                     new QTableWidgetItem(
                                        query.value("REGION_UNIT_FK").toString()
                                    )
                                );
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2,
                                     new QTableWidgetItem(
                                        QString::number(0)
                                    )
                                );
        }
    }
    else
    {
        qDebug() << __PRETTY_FUNCTION__ << "from orders error";
    }

    connect(ui->tableWidget, &QTableWidget::cellClicked, [this] (int row, int column)
    {
       int orderValue = ui->tableWidget->item(row, 2)->data(Qt::DisplayRole).toInt();
       orderValue = (orderValue + 1) % 2;
       ui->tableWidget->setItem(row, 2, new QTableWidgetItem(
                                    QString::number(orderValue)
                                )
                            );
    });

    connect(ui->pushButton, &QPushButton::clicked, this, &TournamentGridDialog::generate);
    connect(ui->pushButton_2, &QPushButton::clicked, [this] ()
    {
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0,
                                 new QTableWidgetItem(
                                    "Запись " + QString::number(ui->tableWidget->rowCount())
                                )
                            );
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1,
                                 new QTableWidgetItem(
                                   QString::number(rand() % 7)
                                )
                            );
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2,
                                 new QTableWidgetItem(
                                   QString::number(0)
                                )
                            );
    });
}

TournamentGridDialog::~TournamentGridDialog()
{
    delete ui;
}

void TournamentGridDialog::generate()
{
    QVector<TournamentManager::InitialParticapantRecord> v;
    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        v.push_back({
                        ui->tableWidget->item(i, 0)->data(Qt::DisplayRole).toString(),
                        ui->tableWidget->item(i, 2)->data(Qt::DisplayRole).toInt(),
                        ui->tableWidget->item(i, 1)->data(Qt::DisplayRole).toInt()
                    });
    }
    v = TournamentManager::getTournamentInitialState(v);
    ui->widget->update();
    ui->widget->repaint();
}
