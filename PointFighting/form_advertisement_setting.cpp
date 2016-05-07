#include "form_advertisement_setting.h"
#include "ui_form_advertisement_setting.h"

FormAdvertisementSetting::FormAdvertisementSetting(QWidget *parent, int intervel, bool showAdvertisement) :
    QDialog(parent),
    ui(new Ui::FormAdvertisementSetting)
{
    ui->setupUi(this);

    ui->spinBox->setValue(intervel);
    ui->checkBox->setChecked(showAdvertisement);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, [this](){
        accept();
    });
    connect(ui->buttonBox, &QDialogButtonBox::rejected, [this](){
        reject();
    });
}

FormAdvertisementSetting::~FormAdvertisementSetting()
{
    delete ui;
}

bool FormAdvertisementSetting::showAdvertisement()
{
    return ui->checkBox->isChecked();
}

int FormAdvertisementSetting::getTime()
{
    return ui->spinBox->value();
}
