#ifndef HANDBOOKDIALOG_H
#define HANDBOOKDIALOG_H

#include <QDialog>
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

#include "databaseexpert.h"
#include "webreportdialog.h"

namespace Ui {
class HandbookDialog;
}

class HandbookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HandbookDialog(QString tableName, QString tableRusName, const QSqlDatabase & database, QWidget *parent = 0);
    ~HandbookDialog();

    static QSqlRecord m_record;

private:
    Ui::HandbookDialog *ui;
    const QSqlDatabase & m_database;

};

class MySqlRelationDelegate : public QItemDelegate
{
public:

    explicit MySqlRelationDelegate(QObject *aParent = 0)
        : QItemDelegate(aParent)
    {}
    ~MySqlRelationDelegate() { }

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

    QWidget *createEditor(QWidget *aParent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const;
};

#endif // HANDBOOKDIALOG_H
