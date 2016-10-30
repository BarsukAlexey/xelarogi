#ifndef DIALOGMANAGERSQLTABLE_H
#define DIALOGMANAGERSQLTABLE_H

#include "db_utils.h"

#include <QAbstractItemModel>
#include <QDebug>
#include <QDialog>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLineEdit>
#include <QMessageBox>
#include <QScrollBar>
#include <QSortFilterProxyModel>
#include <QSpinBox>
#include <QSqlError>
#include <QSqlField>
#include <QSqlRecord>
#include <QSqlRelation>
#include <QSqlRelationalDelegate>
#include <QSqlRelationalTableModel>

class ColumnAlignedLayout : public QHBoxLayout
{
    Q_OBJECT
public:
    explicit ColumnAlignedLayout(QWidget *parent);
    void setTableColumnsToTrack(QHeaderView *view);

signals:

public slots:

private:
    void setGeometry(const QRect &r);
    QHeaderView *headerView;
};


class MySqlRelationalDelegate : public QSqlRelationalDelegate
{
    Q_OBJECT

public:
    explicit MySqlRelationalDelegate(QObject *parent = 0);
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;

protected:
    QWidget* createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const;

};



class MySortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    MySortFilterProxyModel(QObject *parent);
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    void setMyFilter(const int column, const QStringList& filter);
    void setSourceModel(QAbstractItemModel *sourceModel) Q_DECL_OVERRIDE;

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const Q_DECL_OVERRIDE;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const Q_DECL_OVERRIDE;

private:
    QVector<int> columnsForSort;
    QVector<QStringList> filters;
};
















namespace Ui {
class DialogManagerSqlTable;
}

class DialogManagerSqlTable : public QDialog
{
    Q_OBJECT

public:
    explicit DialogManagerSqlTable(QWidget *parent, const QString& table, const QString& whereStatement, const QStringList& hidenColumns = QStringList());
    ~DialogManagerSqlTable();



private:
    Ui::DialogManagerSqlTable *ui;
    ColumnAlignedLayout *alignedLayout;

private slots:
    void invalidateAlignedLayout();
};

#endif // DIALOGMANAGERSQLTABLE_H
