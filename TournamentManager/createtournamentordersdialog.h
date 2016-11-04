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
#include <QAxWidget>
#include <QMessageBox>
#include <QFileDialog>

#include "errormessagesdialog.h"
#include "dialogtournamentgrid.h"


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

    static QSqlRecord m_record;

private slots:
    void loadFromExcel();
    void saveToExcel();
    void updateFillOrderWidget(long long orderUID = -1);

private:
    void addContextMenu();
    void addSearchFilters();
    void setComboBoxDependencies();
    QString getAllowTournamentCategories();
    QString getAllowOrderUIDsByCoach(const QString& coachNameMask);
    QString getAllowOrderUIDsByCountry(const QString& countryNameMask);
    QString getAllowOrderUIDsByRegion(const QString& regionNameMask);
    QString getAllowOrderUIDsByRegionUnit(const QString& regionUnitNameMask);
    QString getAllowOrderUIDsByGender(const QString& genderMask);
    QString getAllowOrderUIDsbyTournamentCategory(const QString& tournamentCategoryMask);

    long long getCountryUID(QString countryName);
    long long getRegionUID(QString regionName, long long countryUID);
    long long getRegionUnitUID(QString unitName, long long regionUID, long long countryUID);
    long long getGenderUID(QString genderName);
    long long getTournamentCategoryUID(long long sexUID, double age, double weight, long long typeUID, const QString& sexName, const QString& typeName);
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
    void findTournamentCategoryForLabel();

    void fillNullString(QString& s);

    static int getAge(QDate birthdayDate, QDate DATE_WEIGHTING);

private:
    Ui::CreateTournamentOrdersDialog *ui;
    const QSqlDatabase m_database;
    long long mTournamentUID;
    QString mGlobalError = "";

    QHash<QString, QString> mCountry;
    QHash<QString, QString> mRegion;
    QHash<QString, QString> mType;
};

#endif // CREATETOURNAMENTORDERSDIALOG_H
