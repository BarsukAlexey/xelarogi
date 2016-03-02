#include "trophygeneratorsettingsdialog.h"
#include "ui_trophygeneratorsettingsdialog.h"

TrophyGeneratorSettingsDialog::ExcelPoint TrophyGeneratorSettingsDialog::mFullName;
TrophyGeneratorSettingsDialog::ExcelPoint TrophyGeneratorSettingsDialog::mPlace;
TrophyGeneratorSettingsDialog::ExcelPoint TrophyGeneratorSettingsDialog::mRegion;
TrophyGeneratorSettingsDialog::ExcelPoint TrophyGeneratorSettingsDialog::mTournament;
TrophyGeneratorSettingsDialog::ExcelPoint TrophyGeneratorSettingsDialog::mType;
TrophyGeneratorSettingsDialog::ExcelPoint TrophyGeneratorSettingsDialog::mAges;
TrophyGeneratorSettingsDialog::ExcelPoint TrophyGeneratorSettingsDialog::mWeights;
TrophyGeneratorSettingsDialog::ExcelPoint TrophyGeneratorSettingsDialog::mAge;
TrophyGeneratorSettingsDialog::ExcelPoint TrophyGeneratorSettingsDialog::mWeight;
TrophyGeneratorSettingsDialog::ExcelPoint TrophyGeneratorSettingsDialog::mSportCategory;


TrophyGeneratorSettingsDialog::TrophyGeneratorSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrophyGeneratorSettingsDialog)
{
    ui->setupUi(this);

    connect(this, &TrophyGeneratorSettingsDialog::accepted, [this] ()
    {
        setExcelPointByComboBox(mFullName, ui->fullNameRow, ui->fullNameColumn);
        setExcelPointByComboBox(mPlace, ui->placeRow, ui->placeColumn);
        setExcelPointByComboBox(mRegion, ui->regionRow, ui->regionColumn);
        setExcelPointByComboBox(mTournament, ui->tournamentRow, ui->tournamentColumn);
        setExcelPointByComboBox(mType, ui->typeRow, ui->typeColumn);
        setExcelPointByComboBox(mAges, ui->agesRow, ui->agesColumn);
        setExcelPointByComboBox(mWeights, ui->weightsRow, ui->weightsColumn);
        setExcelPointByComboBox(mAge, ui->ageRow, ui->ageColumn);
        setExcelPointByComboBox(mWeight, ui->weightRow, ui->weightColumn);
        setExcelPointByComboBox(mSportCategory, ui->sportCategoryRow, ui->sportCategoryColumn);
    });
}

TrophyGeneratorSettingsDialog::~TrophyGeneratorSettingsDialog()
{
    delete ui;
}

int TrophyGeneratorSettingsDialog::getRow(QComboBox *cb)
{
    QString text = cb->currentText().toUpper();
    if (text.size() != 1 || text < "A" || text > "Z")
        return -1;

    return (text[0].toLatin1() - 'A' + 1);
}

int TrophyGeneratorSettingsDialog::getColumn(QComboBox *cb)
{
    int column = cb->currentText().toInt();

    if (column < 1 || column > 25)
        return -1;

    return column;
}

void TrophyGeneratorSettingsDialog::setExcelPointByComboBox(TrophyGeneratorSettingsDialog::ExcelPoint &point, QComboBox *cbRow, QComboBox *cbColumn)
{
    point.row = getRow(cbRow);
    point.column = getColumn(cbColumn);
    qSwap(point.row, point.column);
    point.isUsed = ( point.row > 0 && point.column > 0 );
}
