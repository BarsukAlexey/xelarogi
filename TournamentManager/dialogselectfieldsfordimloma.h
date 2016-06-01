#ifndef DIALOGSELECTFIELDSFORDIMLOMA_H
#define DIALOGSELECTFIELDSFORDIMLOMA_H


#include <QDebug>
#include <QDialog>
#include <QMap>

namespace Ui {
class DialogSelectFieldsForDimloma;
}

class DialogSelectFieldsForDimloma : public QDialog
{
    Q_OBJECT

public:
    enum TypeField
    {
        secondName,
        firstName,
        patromicName,

        ageRange,
        //yearRange,

        weightRange,
        weight,

        place,
        placeRome,

        sexAgeType,
        TYPES

    };

public:
    QMap<QString, TypeField> map;

public:
    explicit DialogSelectFieldsForDimloma(QWidget *parent = 0);
    ~DialogSelectFieldsForDimloma();
    QVector<QString> getFields();
    QMap<QString, TypeField> getMap();

private:
    Ui::DialogSelectFieldsForDimloma *ui;


};

#endif // DIALOGSELECTFIELDSFORDIMLOMA_H
