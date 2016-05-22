/********************************************************************************
** Form generated from reading UI file 'form_advertisement_setting.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_ADVERTISEMENT_SETTING_H
#define UI_FORM_ADVERTISEMENT_SETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormAdvertisementSetting
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QSpinBox *spinBox;
    QLabel *label_3;
    QCheckBox *checkBox;
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QRadioButton *radioButtonClassic;
    QRadioButton *radioButton_2;

    void setupUi(QWidget *FormAdvertisementSetting)
    {
        if (FormAdvertisementSetting->objectName().isEmpty())
            FormAdvertisementSetting->setObjectName(QStringLiteral("FormAdvertisementSetting"));
        FormAdvertisementSetting->resize(358, 255);
        gridLayout = new QGridLayout(FormAdvertisementSetting);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(FormAdvertisementSetting);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(FormAdvertisementSetting);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        spinBox = new QSpinBox(FormAdvertisementSetting);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMinimum(1);
        spinBox->setMaximum(100500);
        spinBox->setValue(15);

        horizontalLayout->addWidget(spinBox);

        label_3 = new QLabel(FormAdvertisementSetting);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);


        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 1);

        checkBox = new QCheckBox(FormAdvertisementSetting);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setLayoutDirection(Qt::LeftToRight);
        checkBox->setChecked(true);

        gridLayout->addWidget(checkBox, 2, 0, 1, 1);

        buttonBox = new QDialogButtonBox(FormAdvertisementSetting);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 4, 0, 1, 1);

        groupBox = new QGroupBox(FormAdvertisementSetting);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        radioButtonClassic = new QRadioButton(groupBox);
        radioButtonClassic->setObjectName(QStringLiteral("radioButtonClassic"));
        radioButtonClassic->setChecked(true);

        gridLayout_2->addWidget(radioButtonClassic, 0, 0, 1, 1);

        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));

        gridLayout_2->addWidget(radioButton_2, 0, 1, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(FormAdvertisementSetting);

        QMetaObject::connectSlotsByName(FormAdvertisementSetting);
    } // setupUi

    void retranslateUi(QWidget *FormAdvertisementSetting)
    {
        FormAdvertisementSetting->setWindowTitle(QApplication::translate("FormAdvertisementSetting", "Advertisement setting", 0));
        label->setText(QApplication::translate("FormAdvertisementSetting", "Drop all advertisement images to directory ./advertisement", 0));
        label_2->setText(QApplication::translate("FormAdvertisementSetting", "Time of replacement of pictures", 0));
        label_3->setText(QApplication::translate("FormAdvertisementSetting", "seconds", 0));
        checkBox->setText(QApplication::translate("FormAdvertisementSetting", "Show advertisement", 0));
        groupBox->setTitle(QApplication::translate("FormAdvertisementSetting", "Select skin", 0));
        radioButtonClassic->setText(QApplication::translate("FormAdvertisementSetting", "Classic", 0));
        radioButton_2->setText(QApplication::translate("FormAdvertisementSetting", "Big timer", 0));
    } // retranslateUi

};

namespace Ui {
    class FormAdvertisementSetting: public Ui_FormAdvertisementSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_ADVERTISEMENT_SETTING_H
