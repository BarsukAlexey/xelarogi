#ifndef CREATETYPEDIALOG_H
#define CREATETYPEDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class CreateTypeDialog;
}

class CreateTypeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateTypeDialog(QWidget *parent = 0);
    ~CreateTypeDialog();

private:
    Ui::CreateTypeDialog *ui;
};

#endif // CREATETYPEDIALOG_H
