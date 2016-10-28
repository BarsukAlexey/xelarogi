/********************************************************************************
** Form generated from reading UI file 'dialogdisq.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGDISQ_H
#define UI_DIALOGDISQ_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogDisq
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioButton_Left;
    QRadioButton *radioButton_Right;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogDisq)
    {
        if (DialogDisq->objectName().isEmpty())
            DialogDisq->setObjectName(QStringLiteral("DialogDisq"));
        DialogDisq->resize(398, 201);
        verticalLayout = new QVBoxLayout(DialogDisq);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(DialogDisq);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        radioButton_Left = new QRadioButton(groupBox);
        radioButton_Left->setObjectName(QStringLiteral("radioButton_Left"));
        radioButton_Left->setChecked(true);

        horizontalLayout_2->addWidget(radioButton_Left);

        radioButton_Right = new QRadioButton(groupBox);
        radioButton_Right->setObjectName(QStringLiteral("radioButton_Right"));

        horizontalLayout_2->addWidget(radioButton_Right);


        verticalLayout->addWidget(groupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(DialogDisq);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(DialogDisq);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(DialogDisq);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(DialogDisq);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogDisq, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogDisq, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogDisq);
    } // setupUi

    void retranslateUi(QDialog *DialogDisq)
    {
        DialogDisq->setWindowTitle(QApplication::translate("DialogDisq", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("DialogDisq", "Select winner", 0));
        radioButton_Left->setText(QApplication::translate("DialogDisq", "Red conner", 0));
        radioButton_Right->setText(QApplication::translate("DialogDisq", "Blue conner", 0));
        label->setText(QApplication::translate("DialogDisq", "Input result:", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogDisq: public Ui_DialogDisq {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGDISQ_H
