#include "createtournamentdialog.h"
#include "ui_createtournamentdialog.h"

CreateTournamentDialog::CreateTournamentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateTournamentDialog)
{
    ui->setupUi(this);

    ui->startDate->setDate(QDate::currentDate());
    ui->endDate->setDate(QDate::currentDate());

    connect(this, &CreateTournamentDialog::accepted, [this] ()
    {
        QString name = ui->nameLE->text();
        QString shortName = ui->shortNameLE->text();
        QDate startDate = ui->startDate->date();
        QDate endDate = ui->endDate->date();

        if (tournamentExist(name, startDate, endDate) == false)
        {

            QSqlQuery query;
            query.prepare("INSERT INTO TOURNAMENTS(NAME, SHORTNAME, DATE_BEGIN, DATE_END) "
                          "VALUES(?, ?, ?, ?)");
            query.bindValue(0, name);
            query.bindValue(1, shortName);
            query.bindValue(2, startDate.toString("yyyy-MM-dd"));
            query.bindValue(3, endDate.toString("yyyy-MM-dd"));

            if (!query.exec())
                qDebug() << query.lastError().text();

        }
    });
}

CreateTournamentDialog::~CreateTournamentDialog()
{
    delete ui;
}

bool CreateTournamentDialog::tournamentExist(QString name, QDate beginDate, QDate endDate)
{
    QSqlQuery query;
    query.prepare("SELECT * from TOURNAMENTS");
    if (query.exec())
    {
        while (query.next())
        {
            QString tempName = query.value("NAME").toString();
            QDate tempBeginDate = QDate::fromString(
                        query.value("DATE_BEGIN").toString(),
                        "yyyy-MM-dd"
                        );
            QDate tempEndDate = QDate::fromString(
                        query.value("DATE_END").toString(),
                        "yyyy-MM-dd"
                        );

            if (tempBeginDate.month() == beginDate.month() &&
                    tempBeginDate.year() == beginDate.year() &&
                    tempEndDate.month() == endDate.month() &&
                    tempEndDate.year() == endDate.year() &&
                    name.toLower() == tempName.toLower())
            {
                return true;
            }
        }
    }
    else
    {
        qDebug() << query.lastError().text();
    }

    return false;
}
