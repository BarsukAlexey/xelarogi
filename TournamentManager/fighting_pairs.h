#ifndef FIGHTINGPAIRS_H
#define FIGHTINGPAIRS_H

#include "db_utils.h"
#include "dialogchosedata.h"

#include <QGroupBox>
#include <QRadioButton>
#include <QObject>
#include <QDialog>
#include <QVector>
#include <QListWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QAxObject>
#include <QLineEdit>
#include <QCheckBox>
#include <QTableWidget>
#include <QProgressDialog>
#include <QTimer>



namespace Ui {
class FightingPairs;
}

class FightingPairs : public QDialog
{
    Q_OBJECT

public:
    explicit FightingPairs(long long _tournamentUID, QWidget* parent = 0);
    ~FightingPairs();

private:
    long long tournamentUID;
    QVector<long long> tournamentCategoryUIDs;
    QVector<QVector<QVector<DBUtils::NodeOfTournirGrid>>> grids;
    QVector<QSpinBox*> spinBoxes;
    Ui::FightingPairs* ui;

    void printListOfPairsInExcel(DialogChoseData& dlg, QAxObject *sheets, const QVector<DBUtils::NodeOfTournirGrid>& pairs, int ring);
    void printListOfPairsInJSON(const QVector<DBUtils::NodeOfTournirGrid>& pairs, int ring, const QString& existingDirectory);
    void makeGridsForPointFighting(QString existingDirectory, QVector<long long> tournamentCategoryUIDs);
    QString getTextLocal(long long orderUID);
    QString getFlagImage(long long orderUID);
    QJsonObject getQJsonObject(const DBUtils::NodeOfTournirGrid& f, const int fightingId);

    std::vector<int> getDurationsOfFightsForChampionship(const QVector<int>& selectedRows);

signals:

public slots:
    void onGoPress();
    void onItemSelectionChanged();
};

#endif // FIGHTINGPAIRS_H

