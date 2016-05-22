#ifndef FIGHTINGTABLE2_H
#define FIGHTINGTABLE2_H

#include "aspectratiotextlabel.h"
#include "fighting.h"
#include "formscore.h"
#include "qrightclickbutton.h"

#include <QWidget>
#include <QPixmap>
#include <QDebug>
#include <QLayoutItem>




namespace Ui {
class FightingTable2;
}

class FightingTable2 : public QWidget
{
    Q_OBJECT

private:
    Ui::FightingTable2 *ui;
    QRightClickButton *pushButtonStart;
    QRightClickButton *pushButtonDoctor;
    QRightClickButton *pushButtonStop;
    QRightClickButton *cancelLastPenalty;

    Fighting *f;
    const QString nameLeft;
    const QString nameRight;
    const QImage mLeftFlag;
    const QImage mRightFlag;

    const bool isForJudge;
    const bool showAdvertisement;

    QString forceResult;

public:
    explicit FightingTable2(Fighting* f, QString categoty, QString nameLeft, QString regionLeft, QString nameRight, QString regionRight, QImage leftFlag, QImage rightFlag, bool isForJudge, bool showAdvertisement, QWidget *parent = 0);
    ~FightingTable2();

private:
    static void setTextColor(QWidget *label, Qt::GlobalColor color);


};

#endif // FIGHTINGTABLE2_H
