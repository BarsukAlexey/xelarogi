#include "onefieldsetupdialog.h"
#include "ui_onefieldsetupdialog.h"

OneFieldSetupDialog::OneFieldSetupDialog(long long tournamentUID, QString fieldName, QWidget *parent) :
    QDialog(parent),
    mTournamentUID(tournamentUID),
    mFieldName(fieldName),
    ui(new Ui::OneFieldSetupDialog)
{
    ui->setupUi(this);

    updateListWidgets();


    connect(ui->toCorrectBtn, &QPushButton::clicked, [this, tournamentUID, fieldName] ()
    {
        QString uids = "(-100";
        for (QListWidgetItem* item : ui->incorrectLW->selectedItems())
        {
            uids += "," + item->data(Qt::UserRole).toString();
        }
        uids += ")";
        QSqlQuery modifQuery("UPDATE ORDERS SET " + fieldName + " = 1 WHERE UID IN " + uids);
        modifQuery.exec();
        updateListWidgets();
    });
    connect(ui->toIncorrectBtn, &QPushButton::clicked, [this, tournamentUID, fieldName] ()
    {
        QString uids = "(-100";
        for (QListWidgetItem* item : ui->correctLW->selectedItems())
        {
            uids += "," + item->data(Qt::UserRole).toString();
        }
        uids += ")";
        QSqlQuery modifQuery("UPDATE ORDERS SET " + fieldName + " = 0 WHERE UID IN " + uids);
        modifQuery.exec();
        updateListWidgets();
    });
}

OneFieldSetupDialog::~OneFieldSetupDialog()
{
    delete ui;
}

void OneFieldSetupDialog::updateListWidgets()
{
    ui->incorrectLW->clear();
    ui->correctLW->clear();
    QSqlQuery query("SELECT * FROM ORDERS LEFT JOIN TOURNAMENT_CATEGORIES ON ORDERS.TOURNAMENT_CATEGORY_FK = TOURNAMENT_CATEGORIES.UID WHERE TOURNAMENT_CATEGORIES.TOURNAMENT_FK = " + QString::number(mTournamentUID));
    if (query.exec())
    {
        while (query.next())
        {
            QString UID = query.value("UID").toString();
            QString name =  query.value("SECOND_NAME").toString() + " " +
                            query.value("FIRST_NAME").toString() + " " +
                            query.value("PATRONYMIC").toString();
            bool isCorrect = query.value(mFieldName).toBool();
            QListWidgetItem* item = new QListWidgetItem();
            item->setData(Qt::DisplayRole, name);
            item->setData(Qt::UserRole, UID);
            if (isCorrect)
            {
                ui->correctLW->addItem(item);
            }
            else
            {
                ui->incorrectLW->addItem(item);
            }
        }
    }
    else qDebug() << query.lastError().text();
}
