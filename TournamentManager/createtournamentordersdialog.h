#ifndef CREATETOURNAMENTORDERSDIALOG_H
#define CREATETOURNAMENTORDERSDIALOG_H

#include "db_utils.h"
#include "dialog_change_category.h"
#include "dialogtournamentgrid.h"
#include "errormessagesdialog.h"
#include "excel_utils.h"
#include "dialogsqltablemanager.h"
#include "errormessagesdialog.h"

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
    explicit CreateTournamentOrdersDialog(int tournamentUID,
                                          QWidget *parent = 0,
                                          QString filterSecondName = "",
                                          QString filterFirstName = "");
    ~CreateTournamentOrdersDialog();

private slots:
    void loadFromExcel();

private:
    int getGenderUID(const QString& gender);

    int getUID(QString& name,
               const QString& table,
               QMap<QString, QString>& mapNames,
               const QMap<QString, QVariant>& map = QMap<QString, QVariant>());

private slots:

private:
    Ui::CreateTournamentOrdersDialog *ui;
    const int tournamentUID;
};

#endif // CREATETOURNAMENTORDERSDIALOG_H
