#ifndef DIALOGORDEROFTC_H
#define DIALOGORDEROFTC_H

#include <QDialog>
#include <QDebug>
#include <QAbstractTableModel>
#include "db_utils.h"

class MyModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    MyModel(const QVector<std::pair<int, int>>& uidTC_Level, QObject *parent = 0) :
        QAbstractTableModel(parent),
        uidTC_Level(uidTC_Level)
    {
    }

    int rowCount(const QModelIndex & = QModelIndex()) const Q_DECL_OVERRIDE
    {
        return uidTC_Level.size();
    }

    int columnCount(const QModelIndex & = QModelIndex()) const Q_DECL_OVERRIDE
    {
        return 2;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE
    {
        if (index.isValid())
        {
            if (role == Qt::DisplayRole)
            {
                if (index.column() == 0)
                    return DBUtils::get("NAME", "TOURNAMENT_CATEGORIES", uidTC_Level[index.row()].first);
                if (index.column() == 1)
                {
                    int level = uidTC_Level[index.row()].second;
                    if      (level == -1) return "Вся сетка";
                    else if (level ==  0) return "Финал";
                    else if (level ==  1) return "Полуфинал";
                    return  1 << level;
                }
            }
        }
        return QVariant();
    }

    bool moveRows(const QModelIndex &sourceParent, int srcRow, int ,
                  const QModelIndex &destinationParent, int destRow) Q_DECL_OVERRIDE
    {
        if ((srcRow < destRow && uidTC_Level[srcRow].first == uidTC_Level[destRow - 1].first && uidTC_Level[srcRow].second > uidTC_Level[destRow - 1].second) ||
            (srcRow > destRow && uidTC_Level[srcRow].first == uidTC_Level[destRow    ].first && uidTC_Level[srcRow].second < uidTC_Level[destRow].second))
        {
            return false;
        }
        beginMoveRows(sourceParent, srcRow, srcRow,
                      destinationParent, destRow);

        if (srcRow < destRow)
        {
            uidTC_Level.insert(destRow, uidTC_Level[srcRow]);
            uidTC_Level.remove(srcRow);
        }
        else if (srcRow > destRow)
        {
            uidTC_Level.insert(destRow, uidTC_Level[srcRow]);
            uidTC_Level.remove(srcRow + 1);
        }
        endMoveRows();
        return true;
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const
    {
        if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        {
            if      (section == 0) return "Весовая категория";
            else if (section == 1) return "Уровень";
        }
        return QAbstractTableModel::headerData(section, orientation, role);
    }

    QVector<std::pair<int, int>> getTournamentCategotyUIDs()
    {
        return uidTC_Level;
    }
private:
    QVector<std::pair<int, int>> uidTC_Level;
};

namespace Ui {
class DialogOrderOfTC;
}

class DialogOrderOfTC : public QDialog
{
    Q_OBJECT

public:
    explicit DialogOrderOfTC(QWidget *parent = 0);
    ~DialogOrderOfTC();
    void setTournamentCategories(const QVector<std::pair<int, int>>& uidTC_Level, const QString& title);
    QVector<std::pair<int, int>> getTournamentCategories();

private:
    Ui::DialogOrderOfTC *ui;


private slots:
    void onPushButtonUp();
    void onPushButtonDown();
};

#endif // DIALOGORDEROFTC_H
