#include "forma_dvertisement.h"
#include "ui_form_advertisement.h"

FormAdvertisement::FormAdvertisement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormAdvertisement)
{
    ui->setupUi(this);
}

FormAdvertisement::~FormAdvertisement()
{
    delete ui;
}

void FormAdvertisement::setImage(QImage img)
{
    img = img.scaled(size(), Qt::KeepAspectRatio);
    ui->label->setPixmap(QPixmap::fromImage(img));
}
