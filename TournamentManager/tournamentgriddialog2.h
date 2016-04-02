#ifndef TOURNAMENTGRIDDIALOG2_H
#define TOURNAMENTGRIDDIALOG2_H

#include "renderareawidget.h"
#include <QDialog>
#include <QSqlDatabase>
#include <QComboBox>
#include <QTableWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QStyledItemDelegate>
#include <QGroupBox>
#include <QRadioButton>



class DrawBorderDelegate : public QStyledItemDelegate
{
public:
     DrawBorderDelegate( QObject* parent = 0 ) : QStyledItemDelegate( parent ) {}
     void paint( QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const
     {
        const QRect rect( option.rect );
        painter->drawLine( rect.topLeft(), rect.topRight() );
        QStyledItemDelegate::paint( painter, option, index );
     }
};

class TournamentGridDialog2 : public QDialog
{
    Q_OBJECT

private:
//    struct BestFigher
//    {
//        int orderUID;
//        int priority;
//        int region;

//        BestFigher()
//        {
//        }

//        BestFigher(int orderUID, int priority, int region) : orderUID(orderUID), priority(priority), region(region)
//        {
//        }

//        bool operator < (const BestFigher& b) const {
//            return priority < b.priority;
//        }
//    };

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
    const QSqlDatabase& database;
    long long tournamentUID; // id турнира
    long long tournamentCategories;   // id категории
    RenderAreaWidget *pRenderArea;
    QComboBox *qComboBoxSelectCategory;
    QTableWidget *qTableWidget;
    QTableWidget *tableGrid;
    QString no_special_group = "нет";
    QVector<int> specialGroup;

    QTabWidget *qTabWidget;

    QGroupBox *groupBox;
    QRadioButton *radioButtonAll;
    QRadioButton *radioButtonLonly;
    QRadioButton *radioButtonInvalid;

    int selectedRowOfRableGrid;
    int selectedColumnOfRableGrid;

public:
    TournamentGridDialog2(const QSqlDatabase &database, long long tournamentUID, QWidget *parent = 0);
    ~TournamentGridDialog2();

private:

    static void generatGrid(const long long tournamentCaterotyUID, QVector<long long> bestFighters);

private slots:
    void onActivatedCategory(int id);
    void onCellCLickedForChangePrioritet(int, int);
    void onButtonGenerateGrid();
    void onButtonDelete();

    void fillCategoryCombobox(QString filterStr = "");
    void onCellClickedOntableGrid(int row, int column);

    void onButtonGenerateAll();
    void fillTableGrid();
};




#endif // TOURNAMENTGRIDDIALOG2_H
