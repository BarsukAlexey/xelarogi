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

private:
    Ui::CreateTournamentOrdersDialog *ui;
    const QSqlDatabase & m_database;
    long long mTournamentUID;
    QStringList mHiddenColumns;

};

class OrdersRelationDelegate : public QItemDelegate
{
public:

    explicit OrdersRelationDelegate(QObject *aParent = 0)
        : QItemDelegate(aParent)
    {}
    ~OrdersRelationDelegate() { }

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

#endif // CREATETOURNAMENTORDERSDIALOG_H
