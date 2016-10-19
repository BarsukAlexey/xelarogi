#ifndef FIGHTINGPAIRS_H
#define FIGHTINGPAIRS_H

#include "db_utils.h"
#include "dialogchosedata.h"

#include <QAxWidget>
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

    static void printListOfPairsInExcel(
            DialogChoseData& dlg,
            QAxObject *sheets,
            const QVector<DBUtils::NodeOfTournirGrid>& pairs,
            int ring,
            int typeText,
            QString stringDate,
            int tournamentUID
            );
    static void printListOfPairsInJSON(const QVector<DBUtils::NodeOfTournirGrid>& pairs, int ring, const QString& existingDirectory, int typeText, int typeFlag);
    void makeGridsForPointFighting(QString existingDirectory, QVector<long long> tournamentCategoryUIDs);
public:
    static void writeGridsForPointFighting(
            QString existingDirectory,
            QVector<long long> uids,
            QAxObject *workbooks,
            QAxWidget& excel,
            const int numberRing,
            const QString date,
            DialogChoseData& dlg,
            const int typeText,
            const int typeFlag
            );
    static void writeListOfPairs(
            const QVector<std::pair<int, int>>& uidTC_Level,
            QAxObject *sheets,
            DialogChoseData& dlg,
            int ringNumber,
            int typeText,
            int typeFlag,
            QString stringDate,
            QString existingDirectory,
            int tournamentUID
            );
private:
    static QString getTextLocal(long long orderUID, int type);
    static QString getFlagImage(long long orderUID, int type);
    static QJsonObject getQJsonObject(const DBUtils::NodeOfTournirGrid& f, const int fightingId, int typeText, int typeFlag);

    std::vector<int> getDurationsOfFightsForChampionship(const QVector<int>& selectedRows);

signals:

public slots:
    void onGoPress();
    void onItemSelectionChanged();
};

#endif // FIGHTINGPAIRS_H

