#ifndef COUNTRYICONSDIALOG_H
#define COUNTRYICONSDIALOG_H

#include <QDialog>
#include <QPixmap>
#include <QImage>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFileDialog>
#include <QBuffer>

#include <QDebug>

namespace Ui {
class CountryIconsDialog;
}

class CountryIconsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CountryIconsDialog(QWidget *parent = 0);
    ~CountryIconsDialog();

private slots:
    void on_labelLink_linkActivated(const QString &link);

private:
    void fillCountries();

private:
    Ui::CountryIconsDialog *ui;
    QPixmap mPixmap;
};

#endif // COUNTRYICONSDIALOG_H
