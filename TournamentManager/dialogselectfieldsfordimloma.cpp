#include "dialogselectfieldsfordimloma.h"
#include "ui_dialogselectfieldsfordimloma.h"



DialogSelectFieldsForDimloma::DialogSelectFieldsForDimloma(QWidget *parent, QVector<std::pair<DBUtils::TypeField, QString>> typeFields) :
    QDialog(parent),
    allTypeFields(DBUtils::getAllTypeFieldl()),
    result(typeFields),
    ui(new Ui::DialogSelectFieldsForDimloma)
{
    ui->setupUi(this);

    QMap<DBUtils::TypeField, QString> map = DBUtils::getExplanationOfTypeField();
    for (DBUtils::TypeField key : allTypeFields)
    {
        QListWidgetItem *newItem = new QListWidgetItem(map[key]);
        ui->listWidgetLeft->addItem(newItem);
    }

    updateListWidgetRight();

    connect(ui->pushButtonLeftRight, &QPushButton::clicked, [this, map](){
        int row = ui->listWidgetLeft->currentRow();
        if (!(0 <= allTypeFields.size() && row < allTypeFields.size()))
            return;
        if (allTypeFields[row] == DBUtils::TypeField::PlainText)
        {
            QString text = ui->lineEdit->text();
            if (text.isEmpty())
                return;
            result << std::make_pair(allTypeFields[row], text);
            ui->listWidgetRight->addItem(new QListWidgetItem(map[allTypeFields[row]] + " (" + text + ")"));
        }
        else
        {
            result << std::make_pair(allTypeFields[row], "");
            ui->listWidgetRight->addItem(new QListWidgetItem(map[allTypeFields[row]]));
        }
        updateListWidgetRight();

    });

    connect(ui->pushButtonRightLeft, &QPushButton::clicked, [this](){
        int row = ui->listWidgetRight->currentRow();
        if (row == -1) return;
        result.removeAt(row);
        delete ui->listWidgetRight->item(row);
    });
}

DialogSelectFieldsForDimloma::~DialogSelectFieldsForDimloma()
{
    delete ui;
}

QVector<std::pair<DBUtils::TypeField, QString> > DialogSelectFieldsForDimloma::getFields()
{
    return result;
}

void DialogSelectFieldsForDimloma::updateListWidgetRight()
{
    ui->listWidgetRight->clear();
    QMap<DBUtils::TypeField, QString> map = DBUtils::getExplanationOfTypeField();
    for (std::pair<DBUtils::TypeField, QString> pair : result)
    {
        if (pair.first == DBUtils::TypeField::PlainText)
        {
            ui->listWidgetRight->addItem(new QListWidgetItem(map[pair.first] + " (" + pair.second + ")"));
        }
        else
        {
            ui->listWidgetRight->addItem(new QListWidgetItem(map[pair.first]));
        }
    }
}
