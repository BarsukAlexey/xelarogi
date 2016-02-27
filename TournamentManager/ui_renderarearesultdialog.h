/********************************************************************************
** Form generated from reading UI file 'renderarearesultdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RENDERAREARESULTDIALOG_H
#define UI_RENDERAREARESULTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_RenderAreaResultDialog
{
public:
    QGridLayout *gridLayout;
    QTextEdit *textEdit;
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QDialog *RenderAreaResultDialog)
    {
        if (RenderAreaResultDialog->objectName().isEmpty())
            RenderAreaResultDialog->setObjectName(QStringLiteral("RenderAreaResultDialog"));
        RenderAreaResultDialog->resize(400, 300);
        gridLayout = new QGridLayout(RenderAreaResultDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        textEdit = new QTextEdit(RenderAreaResultDialog);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        gridLayout->addWidget(textEdit, 1, 0, 1, 1);

        label = new QLabel(RenderAreaResultDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        pushButton = new QPushButton(RenderAreaResultDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 2, 0, 1, 1);


        retranslateUi(RenderAreaResultDialog);

        QMetaObject::connectSlotsByName(RenderAreaResultDialog);
    } // setupUi

    void retranslateUi(QDialog *RenderAreaResultDialog)
    {
        RenderAreaResultDialog->setWindowTitle(QApplication::translate("RenderAreaResultDialog", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202 \320\261\320\276\321\217", 0));
        label->setText(QApplication::translate("RenderAreaResultDialog", "TextLabel", 0));
        pushButton->setText(QApplication::translate("RenderAreaResultDialog", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0));
    } // retranslateUi

};

namespace Ui {
    class RenderAreaResultDialog: public Ui_RenderAreaResultDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RENDERAREARESULTDIALOG_H
