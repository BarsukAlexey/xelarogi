#ifndef DIALOGTOURNAMENTGRID_H
#define DIALOGTOURNAMENTGRID_H

#include "dialogchosedata.h"
#include "renderareawidget.h"
#include "createtournamentordersdialog.h"

#include <algorithm>
#include <assert.h>
#include <iostream>
#include <QAbstractItemModel>
#include <QApplication>
#include <QAxBase>
#include <QAxObject>
#include <QCheckBox>
#include <QComboBox>
#include <QDate>
#include <qDebug>
#include <QDebug>
#include <QDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QListWidgetItem>
#include <QMenu>
#include <QMessageBox>
#include <QModelIndex>
#include <QProgressDialog>
#include <QPushButton>
#include <QQueue>
#include <QRadioButton>
#include <QScrollArea>
#include <QSettings>
#include <QSpinBox>
#include <QSplitter>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStyledItemDelegate>
#include <QTableWidget>
#include <QTabWidget>
#include <QtGlobal>
#include <QWidget>
#include <set>
#include <string>
#include <time.h>
#include <utility>


namespace Ui {
class DialogTournamentGrid;
}

class DrawBorderDelegate : public QStyledItemDelegate
{
public:
     DrawBorderDelegate (QObject* parent = 0) : QStyledItemDelegate(parent) {}
     void paint (QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
     {
        const QRect rect(option.rect);
        painter->drawLine(rect.topLeft(), rect.topRight());
        QStyledItemDelegate::paint(painter, option, index);
     }
};

class DialogTournamentGrid : public QDialog
{
    Q_OBJECT

private:
    struct RegionRandomOrders
    {
        long long region;
        long long random_number;
        QVector<long long> orderUIDs;

        bool operator < (const RegionRandomOrders& a) const
        {
            if (orderUIDs.size() != a.orderUIDs.size()) return orderUIDs.size() > a.orderUIDs.size();
            if (random_number    != a.random_number   ) return random_number    < a.random_number;
            return region < a.region;
        }
    };

private:
    Ui::DialogTournamentGrid *ui;
    const long long tournamentUID;
    int selectedRowOfRableGrid;
    int selectedColumnOfRableGrid;
    QVector<int> specialGroup;
    const QString no_special_group = "нет";

public:
    explicit DialogTournamentGrid(QWidget *parent, QString filter, long long tournamentUID);
    ~DialogTournamentGrid();

private:
    static void generatGrid(const long long tournamentUID, const long long tournamentCaterotyUID, QVector<long long> bestFighters);
    static bool deleteGrid (const long long uidTC);
    QString getLocation(const int orderUID);
    QVector<std::pair<DBUtils::TypeField, QString>> getLocationData();

    void fillListOfOrders();
    void fillListOfPairs();



private slots:
    void onActivatedCategory();
    void onCellCLickedForChangePrioritet(int, int);
    void onButtonGenerateGrid();

    void saveAllGridsInExcel();
    void deleteAllGrids();
    void onDeleteGrid();

    void fillCategoryCombobox(QString filterStr = "");
    void onCellClickedOntableGrid(int row, int column);

    void onButtonGenerateAll();


    void onCustomContextMenuRequested(const QPoint& pos);

    void onSpinBoxFontSizeChangedOfTournamentCategory(const int sizeFont);
    void onSpinBoxFontSizeChangedOfListOfOrders(int sizeFont);
    //void onSpinBoxFontSizeChangedOfNodeOfGrid(const int sizeFont);
    void onSpinBoxFontSizeChangedOfListOfPairs(int sizeFont);

    void onCheckBoxesChangeState();



signals:



};

#endif // DIALOGTOURNAMENTGRID_H
