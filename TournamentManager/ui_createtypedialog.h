/********************************************************************************
** Form generated from reading UI file 'createtypedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATETYPEDIALOG_H
#define UI_CREATETYPEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CreateTypeDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *typeNameLE;
    QHBoxLayout *horizontalLayout;
    QPushButton *acceptBtn;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelBtn;

    void setupUi(QDialog *CreateTypeDialog)
    {
        if (CreateTypeDialog->objectName().isEmpty())
            CreateTypeDialog->setObjectName(QStringLiteral("CreateTypeDialog"));
        CreateTypeDialog->resize(249, 142);
        verticalLayout_2 = new QVBoxLayout(CreateTypeDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(CreateTypeDialog);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(12);
        label->setFont(font);
        label->setWordWrap(true);

        verticalLayout->addWidget(label);

        typeNameLE = new QLineEdit(CreateTypeDialog);
        typeNameLE->setObjectName(QStringLiteral("typeNameLE"));

        verticalLayout->addWidget(typeNameLE);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        acceptBtn = new QPushButton(CreateTypeDialog);
        acceptBtn->setObjectName(QStringLiteral("acceptBtn"));

        horizontalLayout->addWidget(acceptBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cancelBtn = new QPushButton(CreateTypeDialog);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(CreateTypeDialog);

        QMetaObject::connectSlotsByName(CreateTypeDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateTypeDialog)
    {
        CreateTypeDialog->setWindowTitle(QApplication::translate("CreateTypeDialog", "\320\224\320\276\320\261\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\275\320\276\320\262\320\276\320\263\320\276 \321\200\320\260\320\267\320\264\320\265\320\273\320\260", 0));
        label->setText(QApplication::translate("CreateTypeDialog", "\320\243\320\272\320\260\320\266\320\270\321\202\320\265 \320\275\320\260\320\270\320\274\320\265\320\275\320\276\320\262\320\260\320\275\320\270\320\265, \320\272\320\276\321\202\320\276\321\200\320\276\320\265 \321\201\320\273\320\265\320\264\321\203\320\265\321\202 \320\264\320\276\320\261\320\260\320\262\320\270\321\202\321\214", 0));
        acceptBtn->setText(QApplication::translate("CreateTypeDialog", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", 0));
        cancelBtn->setText(QApplication::translate("CreateTypeDialog", "\320\236\321\202\320\274\320\265\320\275\320\260", 0));
    } // retranslateUi

};

namespace Ui {
    class CreateTypeDialog: public Ui_CreateTypeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATETYPEDIALOG_H
