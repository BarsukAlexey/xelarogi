#ifndef SQLTABLEMANAGER_H
#define SQLTABLEMANAGER_H


#include "db_utils.h"
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
#include <QSqlRelation>
#include <QSqlRelationalDelegate>
#include <QSqlRelationalTableModel>

#include <QPainter>
#include <QFileDialog>
#include <QBuffer>

#include <QEvent>
#include <QKeyEvent>



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
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const Q_DECL_OVERRIDE;

//    bool eventFilter(QObject* object, QEvent* event) Q_DECL_OVERRIDE
//    {
//////        if (event->type() != QEvent::Paint)
//////            qDebug() << object << event->type();
////        ImageLoaderWidget* editor = qobject_cast<ImageLoaderWidget*>(object);
////        if (editor)
////        {
////            if (event->type() != QEvent::FocusOut)
////            {
////                //emit commitData(editor);
////            }
//////            if (event->type() != QEvent::Paint)
//////                qDebug() << editor << event->type();
////        }
//        bool res = QSqlRelationalDelegate::eventFilter(object, event);
//        //if (res) qDebug() << object << event->type() << res;
//        return res;
//    }

protected:
    QWidget *createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const Q_DECL_OVERRIDE;
//    bool editorEvent(QEvent * event,
//                     QAbstractItemModel * model,
//                     const QStyleOptionViewItem & option,
//                     const QModelIndex & index) Q_DECL_OVERRIDE;
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
class SqlTableManager;
}

class SqlTableManager : public QWidget
{
    Q_OBJECT

public:
    explicit SqlTableManager(QWidget *parent = 0);
    void setSqlTable(const QString& table, const QString& whereStatement = "", const QStringList& hidenColumns = QStringList());
    void updateData();
    ~SqlTableManager();



private:
    Ui::SqlTableManager *ui;
    ColumnAlignedLayout *alignedLayout;
    QSqlRelationalTableModel *model;

private slots:
    void invalidateAlignedLayout();
};

#endif // SQLTABLEMANAGER_H

