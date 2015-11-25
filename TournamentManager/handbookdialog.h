#ifndef HANDBOOKDIALOG_H
#define HANDBOOKDIALOG_H

#include <QDialog>
#include <QSql>
#include <QSqlDriver>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QTableWidget>
#include <QComboBox>
#include <QSqlTableModel>
#include <QTableWidgetItem>

#include "databaseexpert.h"

namespace Ui {
class HandbookDialog;
}

class HandbookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HandbookDialog(QString tableName, QString tableRusName, const QSqlDatabase & database, QWidget *parent = 0);
    ~HandbookDialog();

private:
    Ui::HandbookDialog *ui;
    const QSqlDatabase & m_database;
};

#endif // HANDBOOKDIALOG_H
