#ifndef FIGHTINGTABLE2_H
#define FIGHTINGTABLE2_H

#include <QWidget>
#include <QPixmap>


namespace Ui {
class FightingTable2;
}

class FightingTable2 : public QWidget
{
    Q_OBJECT

public:
    explicit FightingTable2(QWidget *parent = 0);
    ~FightingTable2();

private:
    Ui::FightingTable2 *ui;
};

#endif // FIGHTINGTABLE2_H
