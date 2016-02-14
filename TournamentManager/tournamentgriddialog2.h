#ifndef TOURNAMENTGRIDDIALOG2_H
#define TOURNAMENTGRIDDIALOG2_H

#include "renderareawidget.h"
#include <QDialog>
#include <QSqlDatabase>
#include <QComboBox>
#include <QTableWidget>

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
    QString no_special_group = "нет";
    QVector<int> specialGroup;

public:
    TournamentGridDialog2(const QSqlDatabase &database, long long tournamentUID, QWidget *parent = 0);
    ~TournamentGridDialog2();

private:
    void ebnutVBazyGovno();
    void setInGridBestFigher(int v, const QVector<bool>& isLeaf, const QVector<int>& distToLeaf, const QVector<TournamentGridDialog2::BestFigher>& bestFighters, QHash<long long, int>& vertexOfBest);

private slots:
    void playerChanged();
    void onActivatedCategory(int id);
    void onCellCLickedForChangePrioritet(int, int);
    void onButtonGenerateGrid();


};

#endif // TOURNAMENTGRIDDIALOG2_H
