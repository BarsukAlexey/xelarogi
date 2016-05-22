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
    explicit FormAdvertisementSetting(QWidget *parent, int intervel, bool showAdvertisement, bool classicSkin);
    ~FormAdvertisementSetting();

private:
    Ui::FormAdvertisementSetting *ui;

public:
    bool showAdvertisement();
    int getTime();
    bool getClassicSkin();
};

#endif // FORM_ADVERTISEMENT_SETTING_H
