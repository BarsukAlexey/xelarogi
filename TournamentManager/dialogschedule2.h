#ifndef DIALOGSCHEDULE2_H
#define DIALOGSCHEDULE2_H

#include <QDialog>

#include "db_utils.h"

namespace Ui {
class Dialogschedule2;
}

class Dialogschedule2 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogschedule2(int tournamentUID, QWidget *parent = 0);
    ~Dialogschedule2();

private:
    Ui::Dialogschedule2 *ui;
    const int tournamentUID;

private slots:
    void onCountOfRingsChanged();
};

#endif // DIALOGSCHEDULE2_H
