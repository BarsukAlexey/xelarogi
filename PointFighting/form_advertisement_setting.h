#ifndef FORM_ADVERTISEMENT_SETTING_H
#define FORM_ADVERTISEMENT_SETTING_H

#include <QDialog>

namespace Ui {
class FormAdvertisementSetting;
}

class FormAdvertisementSetting : public QDialog
{
    Q_OBJECT

public:
    explicit FormAdvertisementSetting(QWidget *parent = 0);
    ~FormAdvertisementSetting();

private:
    Ui::FormAdvertisementSetting *ui;

public:
    bool showAdvertisement();
    int getTime();
};

#endif // FORM_ADVERTISEMENT_SETTING_H
