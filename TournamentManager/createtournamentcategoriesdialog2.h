#ifndef CREATETOURNAMENTCATEGORIESDIALOG2_H
#define CREATETOURNAMENTCATEGORIESDIALOG2_H

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

protected:
    QWidget* createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

};



class MySortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    MySortFilterProxyModel(QObject *parent);
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    void setMyFilter(const int column, const QStringList& filter);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const Q_DECL_OVERRIDE;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const Q_DECL_OVERRIDE;

private:
    QVector<int> columnsForSortForTournamentCategoties;
    QVector<QStringList> filters;
};
















namespace Ui {
class CreateTournamentCategoriesDialog2;
}

class CreateTournamentCategoriesDialog2 : public QDialog
{
    Q_OBJECT

public:
    explicit CreateTournamentCategoriesDialog2(QWidget *parent, const QString& table, const QString& whereStatement);
    ~CreateTournamentCategoriesDialog2();


private:
    Ui::CreateTournamentCategoriesDialog2 *ui;
    ColumnAlignedLayout *alignedLayout;

private slots:
    void invalidateAlignedLayout();
};

#endif // CREATETOURNAMENTCATEGORIESDIALOG2_H
