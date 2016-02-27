#include "renderarearesultdialog.h"
#include "ui_renderarearesultdialog.h"

QString RenderAreaResultDialog::mLastResult = "";

RenderAreaResultDialog::RenderAreaResultDialog(QString name, QString region, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RenderAreaResultDialog)
{
    ui->setupUi(this);
    ui->label->setText("Спортсмен " + name + " (" + region + ") победил в бою.\nЗапишите его результат в поле ниже");

    connect(ui->pushButton, &QPushButton::clicked, [this] ()
    {
        mLastResult = ui->textEdit->toPlainText();
        this->accept();
    });
}

RenderAreaResultDialog::~RenderAreaResultDialog()
{
    delete ui;
}
