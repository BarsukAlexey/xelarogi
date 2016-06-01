#include "dialogselectfieldsfordimloma.h"
#include "ui_dialogselectfieldsfordimloma.h"



DialogSelectFieldsForDimloma::DialogSelectFieldsForDimloma(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSelectFieldsForDimloma)
{
    ui->setupUi(this);

    map["01. Фамилия"] = TypeField::secondName;
    map["02. Имя"] = TypeField::firstName;
    map["03. Отчество"] = TypeField::patromicName;

    map["04. Возрастной диапозон (до 7, 12-15, 18-24, от 35)"] = TypeField::ageRange;
    //map["05. Диапозон дней рождений (1997-1999)"] = TypeField::yearRange;

    map["06. Весовой диапозон (до 40 кг, от 50 до 70 кг, свыше 90 кг)"] = TypeField::weightRange;
    map["07. Просто вес (-66,68,72,+83)"] = TypeField::weight;

    map["08. Занятое место"] = TypeField::place;
    map["09. Занятое место римскими цифрами"] = TypeField::placeRome;

    map["10. Юноши, Девушки, Юниоры..."] = TypeField::sexAgeType;
    map["11. Тип(фулконтакт, лайт, пойнтфайтинг...)"] = TypeField::TYPES;

    for (QString key : map.keys())
    {
        QListWidgetItem *newItem = new QListWidgetItem(key);
        ui->listWidgetLeft->addItem(newItem);
    }

    connect(ui->pushButtonLeftRight, &QPushButton::clicked, [this](){
        for (QListWidgetItem *item : ui->listWidgetLeft->selectedItems())
        {
            ui->listWidgetRight->addItem(new QListWidgetItem(item->text()));
            //qDebug() << item->text();
        }
    });

    connect(ui->pushButtonRightLeft, &QPushButton::clicked, [this](){
        qDeleteAll(ui->listWidgetRight->selectedItems());
    });

    connect(ui->pushButtonAdd, &QPushButton::clicked, [this](){
        QString text = ui->lineEdit->text();
        if (text.isEmpty())
            return;
        ui->listWidgetRight->addItem(new QListWidgetItem(text));
        ui->lineEdit->clear();
    });
}

DialogSelectFieldsForDimloma::~DialogSelectFieldsForDimloma()
{
    delete ui;
}

QVector<QString> DialogSelectFieldsForDimloma::getFields()
{
    QVector<QString> arr;
    for (int row = 0; row < ui->listWidgetRight->count(); ++row)
    {
        arr << ui->listWidgetRight->item(row)->text();
    }
    return arr;
}

QMap<QString, DialogSelectFieldsForDimloma::TypeField> DialogSelectFieldsForDimloma::getMap()
{
    return map;
}
