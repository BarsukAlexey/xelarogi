#ifndef TOURNAMENTGRIDDIALOG2_H
#define TOURNAMENTGRIDDIALOG2_H

#include "renderareawidget.h"
#include "dialogchosedata.h"

#include <QDialog>
#include <QSqlDatabase>
#include <QComboBox>
#include <QTableWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QStyledItemDelegate>
#include <QGroupBox>
#include <QProgressDialog>
#include <QRadioButton>
#include <QSpinBox>


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
    long long tournamentUID; // id турнира
    long long tournamentCategories;   // id категории
    RenderAreaWidget *pRenderArea;
    QComboBox *qComboBoxSelectCategory;
    QTableWidget *qTableWidget;
    QTableWidget *tableWidgeRight;
    QString no_special_group = "нет";
    QVector<int> specialGroup;

    QTabWidget *qTabWidget;

    QGroupBox *groupBox;
    QRadioButton *radioButtonAll;
    QRadioButton *radioButtonLonly;
    QRadioButton *radioButtonInvalid;
    QRadioButton *radioButtonInvalidTurn;

    QLabel *widthQLabel;
    QLabel *heightQLabel;
    QSpinBox *widthSpinBox;
    QSpinBox *heightSpinBox;

    QGroupBox *groupBoxScaleRight;

    int selectedRowOfRableGrid;
    int selectedColumnOfRableGrid;

public:
    TournamentGridDialog2(QString filter, long long tournamentUID, QWidget *parent = 0);
    ~TournamentGridDialog2();

private:

    static void generatGrid(const long long tournamentUID, const long long tournamentCaterotyUID, QVector<long long> bestFighters);
    static bool deleteGrid (const long long uidTC);

private slots:
    void onActivatedCategory(int id);
    void onCellCLickedForChangePrioritet(int, int);
    void onButtonGenerateGrid();


    void fillCategoryCombobox(QString filterStr = "");
    void onCellClickedOntableGrid(int row, int column);

    void onButtonGenerateAll();
    void fillTableGrid();

    void onSpinBoxFontSizeChanged(int sizeFont);
    void onSpinBoxFontSizeChangedOfRightTable(int sizeFont);
    void onTabSwitch(int idTab);
};




#endif // TOURNAMENTGRIDDIALOG2_H
