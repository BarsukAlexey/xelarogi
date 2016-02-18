#ifndef FIGHTINGPAIRS_H
#define FIGHTINGPAIRS_H

#include <bd_utils.h>
#include <QObject>
#include <QDialog>
#include <QVector>
#include <QListWidget>
#include <QPushButton>
#include <QSpinBox>

class FightingPairs : public QDialog
{
    Q_OBJECT

public:
    explicit FightingPairs(const QSqlDatabase &_database, long long _tournamentUID, QWidget* parent);
    ~FightingPairs();

private:
    const QSqlDatabase &database;
    long long tournamentUID;
    QListWidget* qListWidget;
    QPushButton* qPushButton;
    QSpinBox* ringSpinBox;
    QVector<QVector<BDUtils::Fighing> > globalListsOfPairs;


signals:

public slots:
    void onGoPress();
};

#endif // FIGHTINGPAIRS_H

