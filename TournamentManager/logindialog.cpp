#include "logindialog.h"
#include "ui_logindialog.h"

bool LoginDialog::mOkBtnClicked = false;

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    connect(ui->cancelBtn, &QPushButton::clicked, [this] ()
    {
        mOkBtnClicked = false;
        reject();
    });
    connect(ui->okBtn, &QPushButton::clicked, [this] ()
    {
        mOkBtnClicked = true;

        QString login = ui->loginLE->text().trimmed().toLower();
        QString password = ui->passwordLE->text().trimmed().toLower();

        if (login == "admin" && password == "admin2016admin")
            accept();
        else
            reject();
    });
}

LoginDialog::~LoginDialog()
{
    delete ui;
}
