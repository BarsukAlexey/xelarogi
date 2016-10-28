#ifndef CREATETOURNAMENTCATEGORIESDIALOG2_H
#define CREATETOURNAMENTCATEGORIESDIALOG2_H

#include <QDialog>
#include <QDebug>
#include <QSqlRecord>
#include <QSqlRelation>
#include <QSqlRelationalDelegate>
#include <QSqlRelationalTableModel>
#include <QSortFilterProxyModel>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlField>
#include <QSpinBox>
#include <QAbstractItemModel>

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

protected:
    //bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const Q_DECL_OVERRIDE;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const Q_DECL_OVERRIDE;

private:
    QVector<int> columnsForSortForTournamentCategoties;
};





namespace Ui {
class CreateTournamentCategoriesDialog2;
}

class CreateTournamentCategoriesDialog2 : public QDialog
{
    Q_OBJECT

public:
    explicit CreateTournamentCategoriesDialog2(QWidget *parent, const int tournamentUID);
    ~CreateTournamentCategoriesDialog2();

private:
    Ui::CreateTournamentCategoriesDialog2 *ui;
    const int tournamentUID;
};

#endif // CREATETOURNAMENTCATEGORIESDIALOG2_H
