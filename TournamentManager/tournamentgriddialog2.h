#ifndef TOURNAMENTGRIDDIALOG2_H
#define TOURNAMENTGRIDDIALOG2_H

#include "renderareawidget.h"
#include <QDialog>
#include <QSqlDatabase>
#include <QComboBox>
#include <QTableWidget>
#include <QLineEdit>
#include <QCheckBox>

class TournamentGridDialog2 : public QDialog
{
    Q_OBJECT

private:
    struct BestFigher
    {
        int orderUID;
        int priority;
        int region;

        BestFigher()
        {
        }

        BestFigher(int orderUID, int priority, int region) : orderUID(orderUID), priority(priority), region(region)
        {
        }

        bool operator < (const BestFigher& b) const {
            return priority < b.priority;
        }
    };

private:
    const QSqlDatabase& database;
    long long tournamentUID; // id турнира
    long long tournamentCategories;   // id категории
    RenderAreaWidget *pRenderArea;
    QComboBox *qComboBoxSelectCategory;
    QTableWidget *qTableWidget;
    QTableWidget * tableGrid;
    QString no_special_group = "нет";
    QVector<int> specialGroup;

    QCheckBox * qCheckBox;
    int selectedRowOfRableGrid;
    int selectedColumnOfRableGrid;

public:
    TournamentGridDialog2(const QSqlDatabase &database, long long tournamentUID, QWidget *parent = 0);
    ~TournamentGridDialog2();

private:
    void updateInfoTableGrid();

private slots:
    void onActivatedCategory(int id);
    void onCellCLickedForChangePrioritet(int, int);
    void onButtonGenerateGrid();
    void onButtonDelete();

    void sdfsdfsf(){}

    void fillCategoryCombobox(QString filterStr = "");
    void onCellClickedOntableGrid(int row, int column);
};
#endif // TOURNAMENTGRIDDIALOG2_H
