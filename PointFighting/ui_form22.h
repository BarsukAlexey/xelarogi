/********************************************************************************
** Form generated from reading UI file 'form22.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM22_H
#define UI_FORM22_H

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

class Ui_Form22
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

    void setupUi(QWidget *Form22)
    {
        if (Form22->objectName().isEmpty())
            Form22->setObjectName(QStringLiteral("Form22"));
        Form22->resize(583, 524);
        gridLayout = new QGridLayout(Form22);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new AspectRatioTextLabel(Form22);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new AspectRatioPixmapLabel(Form22);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new AspectRatioTextLabel(Form22);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        pushButton = new QPushButton(Form22);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton, 3, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pushButton_2 = new QPushButton(Form22);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout_2->addWidget(pushButton_2, 0, 0, 1, 1);

        label_4 = new AspectRatioPixmapLabel(Form22);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 0, 1, 1, 1);

        pushButton_3 = new QPushButton(Form22);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout_2->addWidget(pushButton_3, 1, 0, 1, 1);

        label_5 = new AspectRatioPixmapLabel(Form22);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 1, 1, 1, 1);

        pushButton_4 = new QPushButton(Form22);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout_2->addWidget(pushButton_4, 2, 0, 1, 1);

        label_6 = new AspectRatioPixmapLabel(Form22);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_2->addWidget(label_6, 2, 1, 1, 1);

        gridLayout_2->setColumnStretch(0, 1);
        gridLayout_2->setColumnStretch(1, 1);

        gridLayout->addLayout(gridLayout_2, 4, 0, 1, 1);


        retranslateUi(Form22);

        QMetaObject::connectSlotsByName(Form22);
    } // setupUi

    void retranslateUi(QWidget *Form22)
    {
        Form22->setWindowTitle(QApplication::translate("Form22", "Form", 0));
        label->setText(QApplication::translate("Form22", "Name", 0));
        label_2->setText(QApplication::translate("Form22", "Flag", 0));
        label_3->setText(QApplication::translate("Form22", "Flag", 0));
        pushButton->setText(QApplication::translate("Form22", "PushButton", 0));
        pushButton_2->setText(QApplication::translate("Form22", "PushButton", 0));
        label_4->setText(QApplication::translate("Form22", "Flag", 0));
        pushButton_3->setText(QApplication::translate("Form22", "PushButton", 0));
        label_5->setText(QApplication::translate("Form22", "Flag", 0));
        pushButton_4->setText(QApplication::translate("Form22", "PushButton", 0));
        label_6->setText(QApplication::translate("Form22", "Flag", 0));
    } // retranslateUi

};

namespace Ui {
    class Form22: public Ui_Form22 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM22_H
