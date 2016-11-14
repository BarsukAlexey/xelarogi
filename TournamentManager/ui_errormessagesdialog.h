/********************************************************************************
** Form generated from reading UI file 'errormessagesdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ERRORMESSAGESDIALOG_H
#define UI_ERRORMESSAGESDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPlainTextEdit>

QT_BEGIN_NAMESPACE

class Ui_ErrorMessagesDialog
{
public:
    QGridLayout *gridLayout;
    QPlainTextEdit *plainTextEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ErrorMessagesDialog)
    {
        if (ErrorMessagesDialog->objectName().isEmpty())
            ErrorMessagesDialog->setObjectName(QStringLiteral("ErrorMessagesDialog"));
        ErrorMessagesDialog->resize(824, 451);
        gridLayout = new QGridLayout(ErrorMessagesDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        plainTextEdit = new QPlainTextEdit(ErrorMessagesDialog);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));

        gridLayout->addWidget(plainTextEdit, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(ErrorMessagesDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(ErrorMessagesDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ErrorMessagesDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ErrorMessagesDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ErrorMessagesDialog);
    } // setupUi

    void retranslateUi(QDialog *ErrorMessagesDialog)
    {
        ErrorMessagesDialog->setWindowTitle(QApplication::translate("ErrorMessagesDialog", "\320\241\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\265", 0));
    } // retranslateUi

};

namespace Ui {
    class ErrorMessagesDialog: public Ui_ErrorMessagesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ERRORMESSAGESDIALOG_H
