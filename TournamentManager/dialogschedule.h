#ifndef DIALOGSCHEDULE_H
#define DIALOGSCHEDULE_H

#include <QDialog>
#include <QScrollBar>
#include <QStyledItemDelegate>
#include <QPainter>

#include "utils.h"
#include "db_utils.h"
#include "dialogschedulesettinglists.h"
//#include "renderareawidget.h"
#include "fiting_distribution.h"

namespace Ui {
class DialogSchedule;
}

class StyledItemDelegateDraw3thVerticalLine : public QStyledItemDelegate
{
public:
     StyledItemDelegateDraw3thVerticalLine( QObject* parent = 0 ) : QStyledItemDelegate( parent ) {}

     void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
     {
        if (index.column() % 3 == 0)
        {
            const QRect rect(option.rect);
            painter->drawLine(rect.topRight(), rect.bottomRight());
        }
        QStyledItemDelegate::paint(painter, option, index);
     }
};

class DialogSchedule : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSchedule(QWidget *parent, long long tournamentUID);
    ~DialogSchedule();


private:
    Ui::DialogSchedule *ui;
    const long long tournamentUID;
    QSqlRelationalTableModel *modelList;
    int selectedRow, selectedColumn;
    QVector<QVector<QVector<int>>> levels;
    QVector<int> tournamentCategories;

    int prevUidList;
private:


public slots:
    void onListChanged();
    void onCellClicked(int row, int column);
    void onSaveExcel();
};

#endif // DIALOGSCHEDULE_H
