#ifndef DIALOGSCHEDULE2INPUTTYPE_H
#define DIALOGSCHEDULE2INPUTTYPE_H

#include <QDialog>
#include <QTime>


namespace Ui {
class Dialogschedule2InputType;
}

class Dialogschedule2InputType : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogschedule2InputType(QWidget *parent = 0, QString str = "", int timeSec = 60, bool canEditText = true);
    ~Dialogschedule2InputType();
    QString getText();
    int getDurationInSeconds();

private:
    Ui::Dialogschedule2InputType *ui;
};

#endif // DIALOGSCHEDULE2INPUTTYPE_H
