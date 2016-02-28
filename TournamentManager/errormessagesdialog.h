#ifndef ERRORMESSAGESDIALOG_H
#define ERRORMESSAGESDIALOG_H

#include <QDialog>
#include <QStringList>

namespace Ui {
class ErrorMessagesDialog;
}

class ErrorMessagesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ErrorMessagesDialog(QStringList list, QWidget *parent = 0);
    ~ErrorMessagesDialog();

private:
    Ui::ErrorMessagesDialog *ui;
};

#endif // ERRORMESSAGESDIALOG_H
