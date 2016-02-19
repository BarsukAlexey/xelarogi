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
    QLineEdit *qLineEdit;
    QVector<QVector<DBUtils::Fighing> > globalListsOfPairs;
    void printInExcel(QAxObject *sheets, const QVector<DBUtils::Fighing>& fighting, int ring);

signals:

public slots:
    void onGoPress();
};

#endif // FIGHTINGPAIRS_H

