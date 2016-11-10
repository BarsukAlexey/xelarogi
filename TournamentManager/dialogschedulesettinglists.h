#ifndef DIALOGSCHEDULESETTINGLISTS_H
#define DIALOGSCHEDULESETTINGLISTS_H

#include <QDialog>
#include <QDebug>
#include <QSqlError>
#include <QSqlRelationalTableModel>
#include <QInputDialog>
#include <QTableWidgetItem>
#include <QComboBox>
#include <QSqlRecord>
#include <QSqlQuery>






namespace Ui {
class DialogScheduleSettingLists;
}

class DialogScheduleSettingLists : public QDialog
{
    Q_OBJECT

private:
    QSqlRelationalTableModel* modelList;
    const long long tournamentUID;
    Ui::DialogScheduleSettingLists *ui;
    QVector<QComboBox*> comboBoxLists;
    QVector<long long> RING_TATAMI_LISTS_DATA_UID;

public:
    explicit DialogScheduleSettingLists(QWidget *parent, const long long tournamentUID);
    ~DialogScheduleSettingLists();

private slots:
    void onPushButtonAddList();
    void onbuttonBoxAccepted();
};

#endif // DIALOGSCHEDULESETTINGLISTS_H

