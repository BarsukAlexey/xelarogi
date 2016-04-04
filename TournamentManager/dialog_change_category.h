#ifndef DIALOG_CHANGE_CATEGORY_H
#define DIALOG_CHANGE_CATEGORY_H

#include <QDialog>
#include <QVector>


namespace Ui {
class DialogChangeCategory;
}

class DialogChangeCategory : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChangeCategory(QString title, QVector<long long> category, QWidget *parent = 0);
    ~DialogChangeCategory();
    long long uidCategory = -1;

private:
    Ui::DialogChangeCategory *ui;
};

#endif // DIALOG_CHANGE_CATEGORY_H
