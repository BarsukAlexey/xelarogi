#ifndef SQLTABLEMANAGER_H
#define SQLTABLEMANAGER_H


#include "db_utils.h"
#include "excel_utils.h"
#include "imageloaderwidget.h"

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
#include <QSqlTableModel>

#include <QItemDelegate>


#include <QPainter>
#include <QFileDialog>
#include <QBuffer>

#include <QEvent>
#include <QKeyEvent>
#include <QMapIterator>


#include <QDateEdit>
#include <QAxWidget>
#include <QAxObject>
#include <QProgressDialog>
#include <QComboBox>
#include <QSqlRelationalDelegate>


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


//----------------------------------------------------------------------------------------------------------

class MyQSqlRelationalDelegate : public QSqlRelationalDelegate
{
    Q_OBJECT
private:
    const QMap<int, QVariant> columnDefaultValue;

public:
    explicit MyQSqlRelationalDelegate(QObject *parent, QMap<int, QVariant> columnDefaultValue);
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const Q_DECL_OVERRIDE;

    bool eventFilter(QObject* object, QEvent* event) Q_DECL_OVERRIDE
    {
        if (event->type() != QEvent::FocusOut)
        {
            ImageLoaderWidget* editor = qobject_cast<ImageLoaderWidget*>(object);
            if (editor)
            {
                emit commitData(editor);
            }
        }
        bool res = QItemDelegate::eventFilter(object, event);
        return res;
    }

protected:
    QWidget *createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const Q_DECL_OVERRIDE;


};

//----------------------------------------------------------------------------------------------------------

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
    QSqlRelationalTableModel *sqlModel;
    QVector<int> columnsForSort;
    QVector<QStringList> filters;
};



//----------------------------------------------------------------------------------------------------------


namespace Ui {
class SqlTableManager;
}

class SqlTableManager : public QWidget
{
    Q_OBJECT

public:
    explicit SqlTableManager(QWidget *parent = 0);
    void setSqlTable(const QString& table,
                     const QString& whereStatement = "",
                     QMap<QString, QVariant> columnValue = QMap<QString, QVariant>());
    void updateMyData(int row = -1);
    ~SqlTableManager();
    QModelIndex getUidIndexOfSelectedRow();



private:
    void saveToExcel();
private slots:
    void submitAllChanges();


private:
    Ui::SqlTableManager *ui;
    ColumnAlignedLayout *alignedLayout;
    QSqlRelationalTableModel *model;
    MySortFilterProxyModel *proxyModel;
};

#endif // SQLTABLEMANAGER_H



