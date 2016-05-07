#ifndef DIALOGDISQ_H
#define DIALOGDISQ_H

#include "fighting_table.h"
#include <QDialog>

namespace Ui {
class DialogDisq;
}

class DialogDisq : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDisq(QWidget *parent = 0);
    ~DialogDisq();

    FightingTable::Player getWinner();
    QString getResult();
private:
    Ui::DialogDisq *ui;
};

#endif // DIALOGDISQ_H
