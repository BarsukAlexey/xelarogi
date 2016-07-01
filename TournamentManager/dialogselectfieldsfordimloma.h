#ifndef DIALOGSELECTFIELDSFORDIMLOMA_H
#define DIALOGSELECTFIELDSFORDIMLOMA_H


#include "db_utils.h"

#include <QDebug>
#include <QDialog>
#include <QMap>

namespace Ui {
class DialogSelectFieldsForDimloma;
}

class DialogSelectFieldsForDimloma : public QDialog
{
    Q_OBJECT

private:
    const QVector<DBUtils::TypeField> allTypeFields;
    QVector<std::pair<DBUtils::TypeField, QString> > result;
    Ui::DialogSelectFieldsForDimloma *ui;

public:
    explicit DialogSelectFieldsForDimloma(QWidget *parent, QVector<std::pair<DBUtils::TypeField, QString>> typeFields);
    ~DialogSelectFieldsForDimloma();
    QVector<std::pair<DBUtils::TypeField, QString> > getFields();

private:
    void updateListWidgetRight();

};

#endif // DIALOGSELECTFIELDSFORDIMLOMA_H
