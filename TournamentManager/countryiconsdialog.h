#ifndef COUNTRYICONSDIALOG_H
#define COUNTRYICONSDIALOG_H

#include <QDebug>
#include <QDialog>
#include <QPixmap>
#include <QImage>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFileDialog>
#include <QBuffer>
#include <QTableView>
#include <QAbstractItemModel>
#include <QPushButton>

namespace Ui {
class CountryIconsDialog;
}

class CountryIconsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CountryIconsDialog(long long tournamentUID, QWidget *parent = 0);
    ~CountryIconsDialog();

private slots:
    void on_labelLink_linkActivated(const QString &link);
    void onRadioButtonClick();

private:
    void fillEntities();

private:
    Ui::CountryIconsDialog *ui;
    const long long mTournamentUID;
    QString mCurrentTableEng;
};

#endif // COUNTRYICONSDIALOG_H
