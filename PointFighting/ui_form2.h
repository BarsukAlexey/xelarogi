/********************************************************************************
** Form generated from reading UI file 'form2.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM2_H
#define UI_FORM2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <aspect_ratio_pixmap_label.h>
#include <aspectratiotextlabel.h>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QGridLayout *gridLayout;
    AspectRatioTextLabel *label;
    AspectRatioPixmapLabel *label_2;
    AspectRatioTextLabel *label_3;
    QPushButton *pushButton;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_2;
    AspectRatioPixmapLabel *label_4;
    QPushButton *pushButton_3;
    AspectRatioPixmapLabel *label_5;
    QPushButton *pushButton_4;
    AspectRatioPixmapLabel *label_6;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(592, 461);
        gridLayout = new QGridLayout(Form);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new AspectRatioTextLabel(Form);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new AspectRatioPixmapLabel(Form);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new AspectRatioTextLabel(Form);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        pushButton = new QPushButton(Form);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 3, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pushButton_2 = new QPushButton(Form);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout_2->addWidget(pushButton_2, 0, 0, 1, 1);

        label_4 = new AspectRatioPixmapLabel(Form);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 0, 1, 1, 1);

        pushButton_3 = new QPushButton(Form);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout_2->addWidget(pushButton_3, 1, 0, 1, 1);

        label_5 = new AspectRatioPixmapLabel(Form);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 1, 1, 1, 1);

        pushButton_4 = new QPushButton(Form);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout_2->addWidget(pushButton_4, 2, 0, 1, 1);

        label_6 = new AspectRatioPixmapLabel(Form);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_2->addWidget(label_6, 2, 1, 1, 1);

        gridLayout_2->setColumnStretch(0, 1);
        gridLayout_2->setColumnStretch(1, 1);

        gridLayout->addLayout(gridLayout_2, 4, 0, 1, 1);

        gridLayout->setRowStretch(0, 10);
        gridLayout->setRowStretch(1, 10);
        gridLayout->setRowStretch(2, 5);
        gridLayout->setRowStretch(3, 10);
        gridLayout->setRowStretch(4, 3);

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0));
        label->setText(QApplication::translate("Form", "Name", 0));
        label_2->setText(QApplication::translate("Form", "Flag", 0));
        label_3->setText(QApplication::translate("Form", "Flag", 0));
        pushButton->setText(QApplication::translate("Form", "PushButton", 0));
        pushButton_2->setText(QApplication::translate("Form", "PushButton", 0));
        label_4->setText(QApplication::translate("Form", "Flag", 0));
        pushButton_3->setText(QApplication::translate("Form", "PushButton", 0));
        label_5->setText(QApplication::translate("Form", "Flag", 0));
        pushButton_4->setText(QApplication::translate("Form", "PushButton", 0));
        label_6->setText(QApplication::translate("Form", "Flag", 0));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM2_H
