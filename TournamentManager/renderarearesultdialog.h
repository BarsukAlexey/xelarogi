#ifndef RENDERAREARESULTDIALOG_H
#define RENDERAREARESULTDIALOG_H

#include <QDialog>

namespace Ui {
class RenderAreaResultDialog;
}

class RenderAreaResultDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RenderAreaResultDialog(QString name, QWidget *parent = 0);
    ~RenderAreaResultDialog();

public:
    QString getResult();

private:
    Ui::RenderAreaResultDialog *ui;
};

#endif // RENDERAREARESULTDIALOG_H
