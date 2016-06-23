#ifndef FIGHTINGPAIRS_H
#define FIGHTINGPAIRS_H

#include "db_utils.h"

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

class FightingPairs : public QDialog
{
    Q_OBJECT

public:
    explicit FightingPairs(long long _tournamentUID, QWidget* parent);
    ~FightingPairs();

private:
    long long tournamentUID;
    QTableWidget * qTableWidget;
    QPushButton* qPushButton;
    QSpinBox* ringSpinBox;
    QLineEdit *qLineEdit;
    QCheckBox *checkBoxPointfighting;
    QSpinBox* spinBoxDelay;
    void printInExcel(QAxObject *sheets, const QVector<DBUtils::Fighing>& fighting, int ring);
    void printInJSON(const QVector<DBUtils::Fighing>& fighting, int ring, const QString& path);
    QRadioButton * radioFlagCountry;
    QRadioButton * radioFlagRegion;
    QRadioButton * radioFlagCity;
    QRadioButton * radioFlagClub;

    QRadioButton * radioTextCountry;
    QRadioButton * radioTextRegion;
    QRadioButton * radioTextCity;
    QRadioButton * radioTextClub;

    void makeGridsForPointFighting(QString existingDirectory, QVector<long long> tournamentCategoryUIDs, int delay, int countOfRings, QString stringDate);
    QString getTextLocal(long long orderUID);
    QString getFlagImage(long long orderUID);
signals:

public slots:
    void onGoPress();
};

#endif // FIGHTINGPAIRS_H

