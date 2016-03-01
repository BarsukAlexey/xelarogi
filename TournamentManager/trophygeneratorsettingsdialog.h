#ifndef TROPHYGENERATORSETTINGSDIALOG_H
#define TROPHYGENERATORSETTINGSDIALOG_H

#include <QDialog>
#include <QComboBox>

namespace Ui {
class TrophyGeneratorSettingsDialog;
}

class TrophyGeneratorSettingsDialog : public QDialog
{
    Q_OBJECT

public:

    struct ExcelPoint
    {
        int row;
        int column;
        bool isUsed;
    };

    explicit TrophyGeneratorSettingsDialog(QWidget *parent = 0);
    ~TrophyGeneratorSettingsDialog();

private:
    int getRow(QComboBox * cb);
    int getColumn(QComboBox * cb);
    void setExcelPointByComboBox(ExcelPoint & point, QComboBox * cbRow, QComboBox * cbColumn);

private:
    Ui::TrophyGeneratorSettingsDialog *ui;

public:
    static ExcelPoint mFullName;
    static ExcelPoint mPlace;
    static ExcelPoint mRegion;
    static ExcelPoint mTournament;
    static ExcelPoint mType;
    static ExcelPoint mAges;
    static ExcelPoint mWeights;
    static ExcelPoint mAge;
    static ExcelPoint mWeight;
    static ExcelPoint mSportCategory;
};

#endif // TROPHYGENERATORSETTINGSDIALOG_H
