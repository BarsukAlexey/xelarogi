/********************************************************************************
** Form generated from reading UI file 'dialogaward.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGAWARD_H
#define UI_DIALOGAWARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>
#include "dialogaward.h"

QT_BEGIN_NAMESPACE

class Ui_DialogAward
{
public:
    QGridLayout *gridLayout;
    QWidget *widget_2;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonNew;
    QPushButton *pushButtonDelete;
    QComboBox *comboBoxName;
    QPushButton *pushButtonSave;
    QWidget *widgetTools;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonGo;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_8;
    QPushButton *pushButtonColorBoundText;
    QPushButton *pushButtonColorBound;
    QPushButton *pushButtonColorText;
    QPushButton *pushButtonFont;
    QSpinBox *spinBoxWidthTextBound;
    QLabel *label_7;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_7;
    QRadioButton *radioButtonHymnCounty;
    QRadioButton *radioButtonHymnRegion;
    QRadioButton *radioButtonHymnCity;
    QRadioButton *radioButtonHymnClub;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_6;
    QRadioButton *radioButtonFlagCounty;
    QRadioButton *radioButtonFlagRegion;
    QRadioButton *radioButtonFlagCity;
    QRadioButton *radioButtonFlagClub;
    QGroupBox *groupBox_7;
    QFormLayout *formLayout;
    QPushButton *pushButtonLoadImg;
    QLabel *label_5;
    QLabel *labelImageWidth;
    QLabel *label_6;
    QLabel *labelImageHeight;
    QGroupBox *groupBox_6;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QRadioButton *radioButtonFlag1;
    QRadioButton *radioButtonFlag0;
    QRadioButton *radioButtonName2;
    QRadioButton *radioButtonFlag2;
    QRadioButton *radioButtonName3;
    QRadioButton *radioButtonName0;
    QRadioButton *radioButtonFlag3;
    QRadioButton *radioButtonName1;
    QRadioButton *radioButtonTC;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_5;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label;
    QSpinBox *spinBoxX;
    QSpinBox *spinBoxY;
    QSpinBox *spinBoxWidth;
    QSpinBox *spinBoxHeight;
    QGroupBox *groupBox_8;
    QGridLayout *gridLayout_9;
    QRadioButton *radioButtonNameCounty;
    QRadioButton *radioButtonNameRegion;
    QRadioButton *radioButtonNameCity;
    QRadioButton *radioButtonNameClub;
    DialogAwardWidget *widgetAward;

    void setupUi(QDialog *DialogAward)
    {
        if (DialogAward->objectName().isEmpty())
            DialogAward->setObjectName(QStringLiteral("DialogAward"));
        DialogAward->resize(1402, 644);
        gridLayout = new QGridLayout(DialogAward);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget_2 = new QWidget(DialogAward);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(widget_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 4, 1, 1);

        pushButtonNew = new QPushButton(widget_2);
        pushButtonNew->setObjectName(QStringLiteral("pushButtonNew"));

        gridLayout_2->addWidget(pushButtonNew, 1, 1, 1, 1);

        pushButtonDelete = new QPushButton(widget_2);
        pushButtonDelete->setObjectName(QStringLiteral("pushButtonDelete"));

        gridLayout_2->addWidget(pushButtonDelete, 1, 3, 1, 1);

        comboBoxName = new QComboBox(widget_2);
        comboBoxName->setObjectName(QStringLiteral("comboBoxName"));
        comboBoxName->setMinimumSize(QSize(200, 0));

        gridLayout_2->addWidget(comboBoxName, 1, 0, 1, 1);

        pushButtonSave = new QPushButton(widget_2);
        pushButtonSave->setObjectName(QStringLiteral("pushButtonSave"));

        gridLayout_2->addWidget(pushButtonSave, 1, 2, 1, 1);


        gridLayout->addWidget(widget_2, 0, 0, 1, 1);

        widgetTools = new QWidget(DialogAward);
        widgetTools->setObjectName(QStringLiteral("widgetTools"));
        sizePolicy.setHeightForWidth(widgetTools->sizePolicy().hasHeightForWidth());
        widgetTools->setSizePolicy(sizePolicy);
        gridLayout_3 = new QGridLayout(widgetTools);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 0, 5, 1, 1);

        pushButtonGo = new QPushButton(widgetTools);
        pushButtonGo->setObjectName(QStringLiteral("pushButtonGo"));

        gridLayout_3->addWidget(pushButtonGo, 0, 9, 1, 1);

        groupBox_5 = new QGroupBox(widgetTools);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        gridLayout_8 = new QGridLayout(groupBox_5);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        pushButtonColorBoundText = new QPushButton(groupBox_5);
        pushButtonColorBoundText->setObjectName(QStringLiteral("pushButtonColorBoundText"));

        gridLayout_8->addWidget(pushButtonColorBoundText, 2, 0, 1, 1);

        pushButtonColorBound = new QPushButton(groupBox_5);
        pushButtonColorBound->setObjectName(QStringLiteral("pushButtonColorBound"));

        gridLayout_8->addWidget(pushButtonColorBound, 3, 0, 1, 1);

        pushButtonColorText = new QPushButton(groupBox_5);
        pushButtonColorText->setObjectName(QStringLiteral("pushButtonColorText"));

        gridLayout_8->addWidget(pushButtonColorText, 1, 0, 1, 1);

        pushButtonFont = new QPushButton(groupBox_5);
        pushButtonFont->setObjectName(QStringLiteral("pushButtonFont"));

        gridLayout_8->addWidget(pushButtonFont, 0, 0, 1, 1);

        spinBoxWidthTextBound = new QSpinBox(groupBox_5);
        spinBoxWidthTextBound->setObjectName(QStringLiteral("spinBoxWidthTextBound"));
        spinBoxWidthTextBound->setMinimum(1);
        spinBoxWidthTextBound->setMaximum(1000);

        gridLayout_8->addWidget(spinBoxWidthTextBound, 2, 2, 1, 1);

        label_7 = new QLabel(groupBox_5);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_8->addWidget(label_7, 2, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_5, 0, 3, 1, 1);

        groupBox_4 = new QGroupBox(widgetTools);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        gridLayout_7 = new QGridLayout(groupBox_4);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        radioButtonHymnCounty = new QRadioButton(groupBox_4);
        radioButtonHymnCounty->setObjectName(QStringLiteral("radioButtonHymnCounty"));
        radioButtonHymnCounty->setChecked(true);

        gridLayout_7->addWidget(radioButtonHymnCounty, 0, 0, 1, 1);

        radioButtonHymnRegion = new QRadioButton(groupBox_4);
        radioButtonHymnRegion->setObjectName(QStringLiteral("radioButtonHymnRegion"));

        gridLayout_7->addWidget(radioButtonHymnRegion, 1, 0, 1, 1);

        radioButtonHymnCity = new QRadioButton(groupBox_4);
        radioButtonHymnCity->setObjectName(QStringLiteral("radioButtonHymnCity"));

        gridLayout_7->addWidget(radioButtonHymnCity, 2, 0, 1, 1);

        radioButtonHymnClub = new QRadioButton(groupBox_4);
        radioButtonHymnClub->setObjectName(QStringLiteral("radioButtonHymnClub"));

        gridLayout_7->addWidget(radioButtonHymnClub, 3, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_4, 0, 8, 1, 1);

        groupBox_3 = new QGroupBox(widgetTools);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_6 = new QGridLayout(groupBox_3);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        radioButtonFlagCounty = new QRadioButton(groupBox_3);
        radioButtonFlagCounty->setObjectName(QStringLiteral("radioButtonFlagCounty"));
        radioButtonFlagCounty->setChecked(true);

        gridLayout_6->addWidget(radioButtonFlagCounty, 0, 0, 1, 1);

        radioButtonFlagRegion = new QRadioButton(groupBox_3);
        radioButtonFlagRegion->setObjectName(QStringLiteral("radioButtonFlagRegion"));

        gridLayout_6->addWidget(radioButtonFlagRegion, 1, 0, 1, 1);

        radioButtonFlagCity = new QRadioButton(groupBox_3);
        radioButtonFlagCity->setObjectName(QStringLiteral("radioButtonFlagCity"));

        gridLayout_6->addWidget(radioButtonFlagCity, 2, 0, 1, 1);

        radioButtonFlagClub = new QRadioButton(groupBox_3);
        radioButtonFlagClub->setObjectName(QStringLiteral("radioButtonFlagClub"));

        gridLayout_6->addWidget(radioButtonFlagClub, 3, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_3, 0, 7, 1, 1);

        groupBox_7 = new QGroupBox(widgetTools);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        formLayout = new QFormLayout(groupBox_7);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        pushButtonLoadImg = new QPushButton(groupBox_7);
        pushButtonLoadImg->setObjectName(QStringLiteral("pushButtonLoadImg"));

        formLayout->setWidget(0, QFormLayout::SpanningRole, pushButtonLoadImg);

        label_5 = new QLabel(groupBox_7);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_5);

        labelImageWidth = new QLabel(groupBox_7);
        labelImageWidth->setObjectName(QStringLiteral("labelImageWidth"));

        formLayout->setWidget(1, QFormLayout::FieldRole, labelImageWidth);

        label_6 = new QLabel(groupBox_7);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_6);

        labelImageHeight = new QLabel(groupBox_7);
        labelImageHeight->setObjectName(QStringLiteral("labelImageHeight"));

        formLayout->setWidget(2, QFormLayout::FieldRole, labelImageHeight);


        gridLayout_3->addWidget(groupBox_7, 0, 0, 1, 1);

        groupBox_6 = new QGroupBox(widgetTools);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        horizontalLayout = new QHBoxLayout(groupBox_6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox = new QGroupBox(groupBox_6);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        radioButtonFlag1 = new QRadioButton(groupBox);
        radioButtonFlag1->setObjectName(QStringLiteral("radioButtonFlag1"));

        gridLayout_4->addWidget(radioButtonFlag1, 1, 2, 1, 1);

        radioButtonFlag0 = new QRadioButton(groupBox);
        radioButtonFlag0->setObjectName(QStringLiteral("radioButtonFlag0"));

        gridLayout_4->addWidget(radioButtonFlag0, 0, 2, 1, 1);

        radioButtonName2 = new QRadioButton(groupBox);
        radioButtonName2->setObjectName(QStringLiteral("radioButtonName2"));

        gridLayout_4->addWidget(radioButtonName2, 2, 1, 1, 1);

        radioButtonFlag2 = new QRadioButton(groupBox);
        radioButtonFlag2->setObjectName(QStringLiteral("radioButtonFlag2"));

        gridLayout_4->addWidget(radioButtonFlag2, 2, 2, 1, 1);

        radioButtonName3 = new QRadioButton(groupBox);
        radioButtonName3->setObjectName(QStringLiteral("radioButtonName3"));

        gridLayout_4->addWidget(radioButtonName3, 3, 1, 1, 1);

        radioButtonName0 = new QRadioButton(groupBox);
        radioButtonName0->setObjectName(QStringLiteral("radioButtonName0"));
        radioButtonName0->setChecked(false);

        gridLayout_4->addWidget(radioButtonName0, 0, 1, 1, 1);

        radioButtonFlag3 = new QRadioButton(groupBox);
        radioButtonFlag3->setObjectName(QStringLiteral("radioButtonFlag3"));

        gridLayout_4->addWidget(radioButtonFlag3, 3, 2, 1, 1);

        radioButtonName1 = new QRadioButton(groupBox);
        radioButtonName1->setObjectName(QStringLiteral("radioButtonName1"));

        gridLayout_4->addWidget(radioButtonName1, 1, 1, 1, 1);

        radioButtonTC = new QRadioButton(groupBox);
        radioButtonTC->setObjectName(QStringLiteral("radioButtonTC"));
        radioButtonTC->setChecked(true);

        gridLayout_4->addWidget(radioButtonTC, 1, 0, 1, 1);


        horizontalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(groupBox_6);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_5 = new QGridLayout(groupBox_2);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_5->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_5->addWidget(label_3, 2, 0, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_5->addWidget(label_4, 3, 0, 1, 1);

        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_5->addWidget(label, 0, 0, 1, 1);

        spinBoxX = new QSpinBox(groupBox_2);
        spinBoxX->setObjectName(QStringLiteral("spinBoxX"));
        spinBoxX->setMinimum(0);
        spinBoxX->setMaximum(100500);
        spinBoxX->setSingleStep(10);

        gridLayout_5->addWidget(spinBoxX, 0, 1, 1, 1);

        spinBoxY = new QSpinBox(groupBox_2);
        spinBoxY->setObjectName(QStringLiteral("spinBoxY"));
        spinBoxY->setMinimum(0);
        spinBoxY->setMaximum(100500);
        spinBoxY->setSingleStep(10);

        gridLayout_5->addWidget(spinBoxY, 1, 1, 1, 1);

        spinBoxWidth = new QSpinBox(groupBox_2);
        spinBoxWidth->setObjectName(QStringLiteral("spinBoxWidth"));
        spinBoxWidth->setMinimum(10);
        spinBoxWidth->setMaximum(100500);
        spinBoxWidth->setSingleStep(10);

        gridLayout_5->addWidget(spinBoxWidth, 2, 1, 1, 1);

        spinBoxHeight = new QSpinBox(groupBox_2);
        spinBoxHeight->setObjectName(QStringLiteral("spinBoxHeight"));
        spinBoxHeight->setMinimum(10);
        spinBoxHeight->setMaximum(100500);
        spinBoxHeight->setSingleStep(10);

        gridLayout_5->addWidget(spinBoxHeight, 3, 1, 1, 1);


        horizontalLayout->addWidget(groupBox_2);


        gridLayout_3->addWidget(groupBox_6, 0, 1, 1, 1);

        groupBox_8 = new QGroupBox(widgetTools);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        gridLayout_9 = new QGridLayout(groupBox_8);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        radioButtonNameCounty = new QRadioButton(groupBox_8);
        radioButtonNameCounty->setObjectName(QStringLiteral("radioButtonNameCounty"));
        radioButtonNameCounty->setChecked(true);

        gridLayout_9->addWidget(radioButtonNameCounty, 0, 0, 1, 1);

        radioButtonNameRegion = new QRadioButton(groupBox_8);
        radioButtonNameRegion->setObjectName(QStringLiteral("radioButtonNameRegion"));

        gridLayout_9->addWidget(radioButtonNameRegion, 1, 0, 1, 1);

        radioButtonNameCity = new QRadioButton(groupBox_8);
        radioButtonNameCity->setObjectName(QStringLiteral("radioButtonNameCity"));

        gridLayout_9->addWidget(radioButtonNameCity, 2, 0, 1, 1);

        radioButtonNameClub = new QRadioButton(groupBox_8);
        radioButtonNameClub->setObjectName(QStringLiteral("radioButtonNameClub"));

        gridLayout_9->addWidget(radioButtonNameClub, 3, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_8, 0, 6, 1, 1);


        gridLayout->addWidget(widgetTools, 2, 0, 1, 1);

        widgetAward = new DialogAwardWidget(DialogAward);
        widgetAward->setObjectName(QStringLiteral("widgetAward"));

        gridLayout->addWidget(widgetAward, 1, 0, 1, 1);

        QWidget::setTabOrder(comboBoxName, pushButtonNew);
        QWidget::setTabOrder(pushButtonNew, pushButtonSave);
        QWidget::setTabOrder(pushButtonSave, pushButtonDelete);
        QWidget::setTabOrder(pushButtonDelete, pushButtonLoadImg);
        QWidget::setTabOrder(pushButtonLoadImg, radioButtonName0);
        QWidget::setTabOrder(radioButtonName0, radioButtonName1);
        QWidget::setTabOrder(radioButtonName1, radioButtonName2);
        QWidget::setTabOrder(radioButtonName2, radioButtonName3);
        QWidget::setTabOrder(radioButtonName3, radioButtonFlag0);
        QWidget::setTabOrder(radioButtonFlag0, radioButtonFlag1);
        QWidget::setTabOrder(radioButtonFlag1, radioButtonFlag2);
        QWidget::setTabOrder(radioButtonFlag2, radioButtonFlag3);
        QWidget::setTabOrder(radioButtonFlag3, spinBoxX);
        QWidget::setTabOrder(spinBoxX, spinBoxY);
        QWidget::setTabOrder(spinBoxY, spinBoxWidth);
        QWidget::setTabOrder(spinBoxWidth, spinBoxHeight);
        QWidget::setTabOrder(spinBoxHeight, pushButtonFont);
        QWidget::setTabOrder(pushButtonFont, pushButtonColorText);
        QWidget::setTabOrder(pushButtonColorText, pushButtonColorBoundText);
        QWidget::setTabOrder(pushButtonColorBoundText, spinBoxWidthTextBound);
        QWidget::setTabOrder(spinBoxWidthTextBound, pushButtonColorBound);
        QWidget::setTabOrder(pushButtonColorBound, radioButtonFlagCounty);
        QWidget::setTabOrder(radioButtonFlagCounty, radioButtonFlagRegion);
        QWidget::setTabOrder(radioButtonFlagRegion, radioButtonFlagCity);
        QWidget::setTabOrder(radioButtonFlagCity, radioButtonFlagClub);
        QWidget::setTabOrder(radioButtonFlagClub, radioButtonHymnCounty);
        QWidget::setTabOrder(radioButtonHymnCounty, radioButtonHymnRegion);
        QWidget::setTabOrder(radioButtonHymnRegion, radioButtonHymnCity);
        QWidget::setTabOrder(radioButtonHymnCity, radioButtonHymnClub);

        retranslateUi(DialogAward);

        QMetaObject::connectSlotsByName(DialogAward);
    } // setupUi

    void retranslateUi(QDialog *DialogAward)
    {
        pushButtonNew->setText(QApplication::translate("DialogAward", "\320\235\320\276\320\262\321\213\320\271", 0));
        pushButtonDelete->setText(QApplication::translate("DialogAward", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", 0));
        pushButtonSave->setText(QApplication::translate("DialogAward", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0));
        pushButtonGo->setText(QApplication::translate("DialogAward", "\320\222\321\213\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\264\320\260\320\275\320\275\321\213\320\265", 0));
        groupBox_5->setTitle(QApplication::translate("DialogAward", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", 0));
        pushButtonColorBoundText->setText(QApplication::translate("DialogAward", "\320\246\320\262\320\265\321\202 \320\276\320\261\320\262\320\276\320\264\320\272\320\270 \321\202\320\265\320\272\321\201\321\202\320\260", 0));
        pushButtonColorBound->setText(QApplication::translate("DialogAward", "\320\246\320\262\320\265\321\202 \320\276\320\261\320\262\320\276\320\264\320\272\320\270 \321\204\320\273\320\260\320\263\320\260", 0));
        pushButtonColorText->setText(QApplication::translate("DialogAward", "\320\246\320\262\320\265\321\202 \321\202\320\265\320\272\321\201\321\202\320\260", 0));
        pushButtonFont->setText(QApplication::translate("DialogAward", "\320\250\321\200\320\270\321\202\321\204 \321\202\320\265\320\272\321\201\321\202\320\260", 0));
        spinBoxWidthTextBound->setSuffix(QString());
        label_7->setText(QApplication::translate("DialogAward", "\320\250\320\270\321\200\320\270\320\275\320\260 \320\276\320\261\320\262\320\276\320\264\320\272\320\270:", 0));
        groupBox_4->setTitle(QApplication::translate("DialogAward", "\320\223\320\270\320\274\320\275", 0));
        radioButtonHymnCounty->setText(QApplication::translate("DialogAward", "\320\241\321\202\321\200\320\260\320\275\320\260", 0));
        radioButtonHymnRegion->setText(QApplication::translate("DialogAward", "\320\240\320\265\320\263\320\270\320\276\320\275", 0));
        radioButtonHymnCity->setText(QApplication::translate("DialogAward", "\320\223\320\276\321\200\320\276\320\264", 0));
        radioButtonHymnClub->setText(QApplication::translate("DialogAward", "\320\232\320\273\321\203\320\261", 0));
        groupBox_3->setTitle(QApplication::translate("DialogAward", "\320\244\320\273\320\260\320\263", 0));
        radioButtonFlagCounty->setText(QApplication::translate("DialogAward", "\320\241\321\202\321\200\320\260\320\275\320\260", 0));
        radioButtonFlagRegion->setText(QApplication::translate("DialogAward", "\320\240\320\265\320\263\320\270\320\276\320\275", 0));
        radioButtonFlagCity->setText(QApplication::translate("DialogAward", "\320\223\320\276\321\200\320\276\320\264", 0));
        radioButtonFlagClub->setText(QApplication::translate("DialogAward", "\320\232\320\273\321\203\320\261", 0));
        groupBox_7->setTitle(QApplication::translate("DialogAward", "\320\232\320\260\321\200\321\202\320\270\320\275\320\272\320\260", 0));
        pushButtonLoadImg->setText(QApplication::translate("DialogAward", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\272\320\260\321\200\321\202\320\270\320\275\320\272\321\203...", 0));
        label_5->setText(QApplication::translate("DialogAward", "\320\250\320\270\321\200\320\270\320\275\320\260", 0));
        labelImageWidth->setText(QApplication::translate("DialogAward", "#", 0));
        label_6->setText(QApplication::translate("DialogAward", "\320\222\321\213\321\201\320\276\321\202\320\260", 0));
        labelImageHeight->setText(QApplication::translate("DialogAward", "#", 0));
        groupBox_6->setTitle(QApplication::translate("DialogAward", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213", 0));
        groupBox->setTitle(QString());
        radioButtonFlag1->setText(QApplication::translate("DialogAward", "\320\244\320\273\320\260\320\263 2", 0));
        radioButtonFlag0->setText(QApplication::translate("DialogAward", "\320\244\320\273\320\260\320\263 1", 0));
        radioButtonName2->setText(QApplication::translate("DialogAward", "\320\244\320\230\320\236 3", 0));
        radioButtonFlag2->setText(QApplication::translate("DialogAward", "\320\244\320\273\320\260\320\263 3", 0));
        radioButtonName3->setText(QApplication::translate("DialogAward", "\320\244\320\230\320\236 4", 0));
        radioButtonName0->setText(QApplication::translate("DialogAward", "\320\244\320\230\320\236 1", 0));
        radioButtonFlag3->setText(QApplication::translate("DialogAward", "\320\244\320\273\320\260\320\263 4", 0));
        radioButtonName1->setText(QApplication::translate("DialogAward", "\320\244\320\230\320\236 2", 0));
        radioButtonTC->setText(QApplication::translate("DialogAward", "\320\222\320\265\321\201\320\276\320\262\320\260\321\217 \320\272\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\217", 0));
        groupBox_2->setTitle(QString());
        label_2->setText(QApplication::translate("DialogAward", "Y", 0));
        label_3->setText(QApplication::translate("DialogAward", "\320\250\320\270\321\200\320\270\320\275\320\260", 0));
        label_4->setText(QApplication::translate("DialogAward", "\320\222\321\213\321\201\320\276\321\202\320\260", 0));
        label->setText(QApplication::translate("DialogAward", "X", 0));
        groupBox_8->setTitle(QApplication::translate("DialogAward", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", 0));
        radioButtonNameCounty->setText(QApplication::translate("DialogAward", "\320\241\321\202\321\200\320\260\320\275\320\260", 0));
        radioButtonNameRegion->setText(QApplication::translate("DialogAward", "\320\240\320\265\320\263\320\270\320\276\320\275", 0));
        radioButtonNameCity->setText(QApplication::translate("DialogAward", "\320\223\320\276\321\200\320\276\320\264", 0));
        radioButtonNameClub->setText(QApplication::translate("DialogAward", "\320\232\320\273\321\203\320\261", 0));
        Q_UNUSED(DialogAward);
    } // retranslateUi

};

namespace Ui {
    class DialogAward: public Ui_DialogAward {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGAWARD_H
