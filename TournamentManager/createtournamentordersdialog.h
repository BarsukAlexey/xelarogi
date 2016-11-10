#ifndef CREATETOURNAMENTORDERSDIALOG_H
#define CREATETOURNAMENTORDERSDIALOG_H

#include "db_utils.h"
#include "dialog_change_category.h"
#include "dialogtournamentgrid.h"
#include "errormessagesdialog.h"
#include "excel_utils.h"

#include <QAction>
#include <QAxBase>
#include <QAxObject>
#include <QAxWidget>
#include <QChar>
#include <QCheckBox>
#include <QComboBox>
#include <QDateEdit>
#include <QDialog>
#include <QFileDialog>
#include <QMenu>
#include <QMessageBox>
#include <QPainter>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlRelationalDelegate>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QStringList>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QWidget>


namespace Ui {
class CreateTournamentOrdersDialog;
}

class CreateTournamentOrdersDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateTournamentOrdersDialog(
                                            long long tournamentUID,
                                            QWidget *parent = 0,
                                            QString filterSecondName = "",
                                            QString filterFirstName = ""
                                          );
    ~CreateTournamentOrdersDialog();

private slots:
    void loadFromExcel();

private:
    int getGenderUID(QString genderName);
    int getTypeUID(QString typeName);


    QVariant getSportCategoryUID(QString categoryName);

    QVariant getCountryUID(QString countryName);
    QVariant getRegionUID(QString regionName, long long countryUID);
    QVariant getRegionUnitUID(QString unitName, long long regionUID, long long countryUID);

    QVariant getClubUID(QString clubName, long long coutryUID, long long regionUID, long long unitUID);
    QVariant getCoachUID(QString coachName, long long clubUID);



private slots:
    //void onPushButtonChangeCategory();

private:
    Ui::CreateTournamentOrdersDialog *ui;
    long long tournamentUID;
    QString globalError = "";

    QHash<QString, QString> mCountry;
    QHash<QString, QString> mRegion;
    QHash<QString, QString> mType;
};

#endif // CREATETOURNAMENTORDERSDIALOG_H
