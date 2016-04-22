#ifndef FORMA_DVERTISEMENT_H
#define FORMA_DVERTISEMENT_H

#include <QDialog>

namespace Ui {
class FormAdvertisement;
}

class FormAdvertisement : public QDialog
{
    Q_OBJECT

public:
    explicit FormAdvertisement(QWidget *parent = 0);
    ~FormAdvertisement();

private:
    Ui::FormAdvertisement *ui;
public:
    void setImage(QImage img);
};

#endif // FORMA_DVERTISEMENT_H
