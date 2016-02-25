#ifndef CREATETOURNAMENTORDERSDIALOG_H
#define CREATETOURNAMENTORDERSDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QMenu>
#include <QAction>
#include <QSql>
#include <QSqlDriver>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QWidget>
#include <QTableWidget>
#include <QComboBox>
#include <QSqlTableModel>
#include <QTableWidgetItem>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QCheckBox>
#include <QPainter>
#include <QDateEdit>
#include <QChar>
#include <QAxObject>
#include <QAxBase>

#include "databaseexpert.h"
#include "webreportdialog.h"


namespace Ui {
class CreateTournamentOrdersDialog;
}

class CreateTournamentOrdersDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateTournamentOrdersDialog(const QSqlDatabase & database,
                                            long long tournamentUID,
                                            QWidget *parent = 0,
                                            QStringList hiddenColumns = QStringList()
                                            );
    ~CreateTournamentOrdersDialog();

    static QSqlRecord m_record;

private slots:
    void loadFromExcel();
    void updateFillOrderWidget(long long orderUID);

private:
    long long getCountryUID(QString countryName);
    long long getRegionUID(QString regionName, long long countryUID);
    long long getRegionUnitUID(QString unitName, long long regionUID, long long countryUID);
    long long getGenderUID(QString genderName);
    long long getTournamentCategoryUID(long long sexUID, double age, double weight);
    long long getSportCategoryUID(QString categoryName);
    long long getTypeUID(QString typeName);
    long long getClubUID(QString clubName, long long coutryUID, long long regionUID, long long unitUID);
    long long getCoachUID(QString coachName, long long clubUID);


    void updateSexComboBox(long long currentUID);
    void updateCountryComboBox(long long currentUID);
    void updateRegionComboBox(long long regionUID, long long countryUID);
    void updateRegionUnitComboBox(long long regionUnitUID, long long regionUID);
    void updateSportCategoryComboBox(long long currentUID);
    void updateTypeComboBox(long long currentUID);
    void updateClubComboBox(long long clubUID, long long regionUID);
    void updateCoachComboBox(long long coachUID, long long clubUID);

private:
    Ui::CreateTournamentOrdersDialog *ui;
    const QSqlDatabase & m_database;
    long long mTournamentUID;
    QStringList mHiddenColumns;

};

#endif // CREATETOURNAMENTORDERSDIALOG_H
