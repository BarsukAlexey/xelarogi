#ifndef DIALOGCREATEAGECATEGORY_H
#define DIALOGCREATEAGECATEGORY_H

#include "ui_dialog_create_age_category.h"
#include <QDialog>

class DialogCreateAgeCategory : public QDialog
{
    Q_OBJECT

private:
    Ui::CreateAgeCategory* ui;

public:
    DialogCreateAgeCategory(QWidget* parent, long long sexUID);
    ~DialogCreateAgeCategory();

signals:

public slots:
};

#endif // DIALOGCREATEAGECATEGORY_H
