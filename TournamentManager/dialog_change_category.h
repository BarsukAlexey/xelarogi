#ifndef DIALOG_CHANGE_CATEGORY_H
#define DIALOG_CHANGE_CATEGORY_H

#include <QDialog>
#include <QMessageBox>
#include <QVector>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include "db_utils.h"
#include "utils.h"
#include "dialogtournamentgrid.h"

namespace Ui {
class DialogChangeCategory;
}

class DialogChangeCategory : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChangeCategory(int orderUID, QWidget *parent = 0);
    ~DialogChangeCategory();
    long long uidCategory = -1;

private:
    Ui::DialogChangeCategory *ui;
};

#endif // DIALOG_CHANGE_CATEGORY_H
