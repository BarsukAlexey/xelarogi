#include "form_advertisement_setting.h"
#include "ui_form_advertisement_setting.h"

FormAdvertisementSetting::FormAdvertisementSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormAdvertisementSetting)
{
    ui->setupUi(this);


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