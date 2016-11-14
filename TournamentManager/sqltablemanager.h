#ifndef SQLTABLEMANAGER_H
#define SQLTABLEMANAGER_H


#include "db_utils.h"
#include "excel_utils.h"
#include "imageloaderwidget.h"



#include <QAbstractItemModel>
#include <QAxObject>
#include <QAxWidget>
#include <QBuffer>
#include <QComboBox>
#include <QDateEdit>
#include <QDebug>
#include <QDialog>
#include <QEvent>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QItemDelegate>
#include <QKeyEvent>
#include <QLineEdit>
#include <QMapIterator>
#include <QMessageBox>
#include <QPainter>
#include <QProgressDialog>
#include <QScrollBar>
#include <QSortFilterProxyModel>
#include <QSpinBox>
#include <QSqlError>
#include <QSqlField>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QVector>


#include <QMap>


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

class MyQSqlRelationalTableModel : public QSqlTableModel
{
    Q_OBJECT
public:
    MyQSqlRelationalTableModel(QObject* parent);

    void setTable(const QString& table) Q_DECL_OVERRIDE;

    QSqlTableModel* relationModel(int column, QObject* parent = 0, const QString& whereStatment = "") const;
    void setRelation(int column, const QString& table, const QString& columnName);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool haveRelation(int column) const;
    int displayColumn(int column) const;

public Q_SLOTS:
    virtual bool select() Q_DECL_OVERRIDE;

private:
    QVector<QMap<int, QVariant>> hashs;
    QVector<QString> tables;
    QVector<int> displayColumns;
};


//----------------------------------------------------------------------------------------------------------

class MyQSqlRelationalDelegate : public QItemDelegate
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
    MyQSqlRelationalTableModel *sqlModel;
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
                     QString whereStatement = "",
                     QMap<QString, QVariant> columnValue = QMap<QString, QVariant>());
    void setFilter(const QString& columnName, const QString& text);
    void updateMyData(int row = -1);
    ~SqlTableManager();
    QModelIndex getUidIndexOfSelectedRow();
    bool addNewName(const QString& name);



private:
    void saveToExcel();
private slots:
    bool submitAllChanges();


private:
    Ui::SqlTableManager *ui;
    ColumnAlignedLayout *alignedLayout;
    MyQSqlRelationalTableModel *model;
    MySortFilterProxyModel *proxyModel;
    QVector<QLineEdit *> lineEdits;
    QMap<int, QVariant> columnDefaultValue;
};

#endif // SQLTABLEMANAGER_H



