#ifndef FIGHTINGPAIRS_H
#define FIGHTINGPAIRS_H

#include <db_utils.h>
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
    explicit FightingPairs(const QSqlDatabase &_database, long long _tournamentUID, QWidget* parent);
    ~FightingPairs();

private:
    const QSqlDatabase &database;
    long long tournamentUID;
    //QListWidget* qListWidget;
    QTableWidget * qTableWidget;
    QPushButton* qPushButton;
    QSpinBox* ringSpinBox;
    QLineEdit *qLineEdit;
    QCheckBox *checkBoxPointfighting;
    QSpinBox* spinBoxDelay;
    QVector<QVector<DBUtils::Fighing> > globalListsOfPairs;
    void printInExcel(QAxObject *sheets, const QVector<DBUtils::Fighing>& fighting, int ring);
    void printInJSON(const QVector<DBUtils::Fighing>& fighting, int ring, const QString& path);

    void makeGridsForPointFighting(QString existingDirectory, QVector<long long> tournamentCategoryUIDs, int delay);
signals:

public slots:
    void onGoPress();
};

#endif // FIGHTINGPAIRS_H

