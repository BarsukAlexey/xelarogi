#include "renderarearesultdialog.h"
#include "ui_renderarearesultdialog.h"


RenderAreaResultDialog::RenderAreaResultDialog(QString name, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RenderAreaResultDialog)
{
    ui->setupUi(this);
    ui->label->setText("Спортсмен(ка)" + name + " победил(а) в бою.\nВведите результат боя");

    connect(ui->pushButton, &QPushButton::clicked, [this] (){
        this->accept();
    });
}

RenderAreaResultDialog::~RenderAreaResultDialog()
{
    delete ui;
}

QString RenderAreaResultDialog::getResult()
{
    return ui->textEdit->toPlainText();
}
