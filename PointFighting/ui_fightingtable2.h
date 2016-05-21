/********************************************************************************
** Form generated from reading UI file 'fightingtable2.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIGHTINGTABLE2_H
#define UI_FIGHTINGTABLE2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>
#include <aspect_ratio_pixmap_label.h>
#include <aspectratiotextlabel.h>
#include <myqlcdnumber.h>

QT_BEGIN_NAMESPACE

class Ui_FightingTable2
{
public:
    QGridLayout *gridLayout_7;
    AspectRatioTextLabel *label;
    QWidget *widget_2;
    QGridLayout *gridLayout;
    AspectRatioTextLabel *label_3;
    AspectRatioTextLabel *label_2;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_5;
    QWidget *widget_5;
    QGridLayout *gridLayout_4;
    AspectRatioTextLabel *rightRegion;
    AspectRatioPixmapLabel *rightFlag;
    MyQLCDNumber *lcdNumber_2;
    QWidget *widget_10;
    QGridLayout *gridLayout_8;
    AspectRatioTextLabel *label_16;
    AspectRatioTextLabel *label_11;
    AspectRatioTextLabel *label_15;
    AspectRatioTextLabel *label_12;
    AspectRatioTextLabel *label_18;
    AspectRatioTextLabel *label_19;
    QGridLayout *gridLayout_2;
    QWidget *widget_3;
    QGridLayout *gridLayout_3;
    AspectRatioPixmapLabel *leftFlag;
    AspectRatioTextLabel *leftRegion;
    QWidget *widget_8;
    QGridLayout *gridLayout_9;
    AspectRatioTextLabel *label_10;
    AspectRatioTextLabel *label_13;
    AspectRatioTextLabel *label_9;
    AspectRatioTextLabel *label_14;
    AspectRatioTextLabel *label_20;
    AspectRatioTextLabel *label_21;
    MyQLCDNumber *lcdNumber;
    AspectRatioTextLabel *label_8;
    AspectRatioTextLabel *label_17;

    void setupUi(QWidget *FightingTable2)
    {
        if (FightingTable2->objectName().isEmpty())
            FightingTable2->setObjectName(QStringLiteral("FightingTable2"));
        FightingTable2->resize(969, 735);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        FightingTable2->setPalette(palette);
        gridLayout_7 = new QGridLayout(FightingTable2);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        label = new AspectRatioTextLabel(FightingTable2);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QPalette palette1;
        QBrush brush2(QColor(255, 196, 19, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        QBrush brush3(QColor(120, 120, 120, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        label->setPalette(palette1);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setScaledContents(true);
        label->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label, 0, 0, 1, 1);

        widget_2 = new QWidget(FightingTable2);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        sizePolicy.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(widget_2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_3 = new AspectRatioTextLabel(widget_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        label_3->setPalette(palette2);
        label_3->setFont(font);
        label_3->setScaledContents(true);
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        label_2 = new AspectRatioTextLabel(widget_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        label_2->setPalette(palette3);
        label_2->setFont(font);
        label_2->setScaledContents(true);
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 1);

        gridLayout_7->addWidget(widget_2, 1, 0, 1, 1);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        widget_5 = new QWidget(FightingTable2);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        sizePolicy.setHeightForWidth(widget_5->sizePolicy().hasHeightForWidth());
        widget_5->setSizePolicy(sizePolicy);
        gridLayout_4 = new QGridLayout(widget_5);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        rightRegion = new AspectRatioTextLabel(widget_5);
        rightRegion->setObjectName(QStringLiteral("rightRegion"));
        sizePolicy.setHeightForWidth(rightRegion->sizePolicy().hasHeightForWidth());
        rightRegion->setSizePolicy(sizePolicy);
        QPalette palette4;
        QBrush brush4(QColor(0, 85, 255, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        rightRegion->setPalette(palette4);
        rightRegion->setFont(font);
        rightRegion->setScaledContents(true);

        gridLayout_4->addWidget(rightRegion, 0, 1, 1, 1);

        rightFlag = new AspectRatioPixmapLabel(widget_5);
        rightFlag->setObjectName(QStringLiteral("rightFlag"));
        sizePolicy.setHeightForWidth(rightFlag->sizePolicy().hasHeightForWidth());
        rightFlag->setSizePolicy(sizePolicy);
        rightFlag->setScaledContents(false);

        gridLayout_4->addWidget(rightFlag, 0, 2, 1, 1);


        gridLayout_5->addWidget(widget_5, 0, 0, 1, 1);

        lcdNumber_2 = new MyQLCDNumber(FightingTable2);
        lcdNumber_2->setObjectName(QStringLiteral("lcdNumber_2"));
        sizePolicy.setHeightForWidth(lcdNumber_2->sizePolicy().hasHeightForWidth());
        lcdNumber_2->setSizePolicy(sizePolicy);
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        lcdNumber_2->setPalette(palette5);
        lcdNumber_2->setLineWidth(1);

        gridLayout_5->addWidget(lcdNumber_2, 1, 0, 1, 1);

        widget_10 = new QWidget(FightingTable2);
        widget_10->setObjectName(QStringLiteral("widget_10"));
        sizePolicy.setHeightForWidth(widget_10->sizePolicy().hasHeightForWidth());
        widget_10->setSizePolicy(sizePolicy);
        gridLayout_8 = new QGridLayout(widget_10);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        label_16 = new AspectRatioTextLabel(widget_10);
        label_16->setObjectName(QStringLiteral("label_16"));
        sizePolicy.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy);
        label_16->setScaledContents(true);

        gridLayout_8->addWidget(label_16, 2, 1, 1, 1);

        label_11 = new AspectRatioTextLabel(widget_10);
        label_11->setObjectName(QStringLiteral("label_11"));
        sizePolicy.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy);
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette6.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette6.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        label_11->setPalette(palette6);
        label_11->setFont(font);
        label_11->setScaledContents(true);
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_11, 0, 0, 1, 1);

        label_15 = new AspectRatioTextLabel(widget_10);
        label_15->setObjectName(QStringLiteral("label_15"));
        sizePolicy.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy);
        label_15->setScaledContents(true);

        gridLayout_8->addWidget(label_15, 0, 1, 1, 1);

        label_12 = new AspectRatioTextLabel(widget_10);
        label_12->setObjectName(QStringLiteral("label_12"));
        sizePolicy.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy);
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette7.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette7.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        label_12->setPalette(palette7);
        label_12->setFont(font);
        label_12->setScaledContents(true);
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_12, 2, 0, 1, 1);

        label_18 = new AspectRatioTextLabel(widget_10);
        label_18->setObjectName(QStringLiteral("label_18"));
        sizePolicy.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy);
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette8.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette8.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        label_18->setPalette(palette8);
        label_18->setFont(font);
        label_18->setScaledContents(true);
        label_18->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_18, 1, 0, 1, 1);

        label_19 = new AspectRatioTextLabel(widget_10);
        label_19->setObjectName(QStringLiteral("label_19"));
        sizePolicy.setHeightForWidth(label_19->sizePolicy().hasHeightForWidth());
        label_19->setSizePolicy(sizePolicy);
        label_19->setScaledContents(true);

        gridLayout_8->addWidget(label_19, 1, 1, 1, 1);


        gridLayout_5->addWidget(widget_10, 2, 0, 1, 1);

        gridLayout_5->setRowStretch(0, 23);
        gridLayout_5->setRowStretch(1, 47);
        gridLayout_5->setRowStretch(2, 30);

        gridLayout_6->addLayout(gridLayout_5, 0, 2, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        widget_3 = new QWidget(FightingTable2);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        sizePolicy.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy);
        gridLayout_3 = new QGridLayout(widget_3);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        leftFlag = new AspectRatioPixmapLabel(widget_3);
        leftFlag->setObjectName(QStringLiteral("leftFlag"));
        sizePolicy.setHeightForWidth(leftFlag->sizePolicy().hasHeightForWidth());
        leftFlag->setSizePolicy(sizePolicy);
        QPalette palette9;
        QBrush brush5(QColor(255, 0, 0, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette9.setBrush(QPalette::Active, QPalette::Text, brush5);
        palette9.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        palette9.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        leftFlag->setPalette(palette9);
        leftFlag->setScaledContents(false);

        gridLayout_3->addWidget(leftFlag, 0, 0, 1, 1);

        leftRegion = new AspectRatioTextLabel(widget_3);
        leftRegion->setObjectName(QStringLiteral("leftRegion"));
        sizePolicy.setHeightForWidth(leftRegion->sizePolicy().hasHeightForWidth());
        leftRegion->setSizePolicy(sizePolicy);
        QPalette palette10;
        palette10.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette10.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette10.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        leftRegion->setPalette(palette10);
        leftRegion->setFont(font);
        leftRegion->setScaledContents(true);

        gridLayout_3->addWidget(leftRegion, 0, 1, 1, 1);


        gridLayout_2->addWidget(widget_3, 0, 0, 1, 1);

        widget_8 = new QWidget(FightingTable2);
        widget_8->setObjectName(QStringLiteral("widget_8"));
        sizePolicy.setHeightForWidth(widget_8->sizePolicy().hasHeightForWidth());
        widget_8->setSizePolicy(sizePolicy);
        gridLayout_9 = new QGridLayout(widget_8);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        label_10 = new AspectRatioTextLabel(widget_8);
        label_10->setObjectName(QStringLiteral("label_10"));
        sizePolicy.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy);
        QPalette palette11;
        palette11.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette11.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette11.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        label_10->setPalette(palette11);
        label_10->setFont(font);
        label_10->setScaledContents(true);
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_9->addWidget(label_10, 0, 0, 1, 1);

        label_13 = new AspectRatioTextLabel(widget_8);
        label_13->setObjectName(QStringLiteral("label_13"));
        sizePolicy.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy);
        label_13->setScaledContents(true);

        gridLayout_9->addWidget(label_13, 0, 1, 1, 1);

        label_9 = new AspectRatioTextLabel(widget_8);
        label_9->setObjectName(QStringLiteral("label_9"));
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);
        QPalette palette12;
        palette12.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette12.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette12.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        label_9->setPalette(palette12);
        label_9->setFont(font);
        label_9->setScaledContents(true);
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_9->addWidget(label_9, 2, 0, 1, 1);

        label_14 = new AspectRatioTextLabel(widget_8);
        label_14->setObjectName(QStringLiteral("label_14"));
        sizePolicy.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy);
        label_14->setScaledContents(true);

        gridLayout_9->addWidget(label_14, 2, 1, 1, 1);

        label_20 = new AspectRatioTextLabel(widget_8);
        label_20->setObjectName(QStringLiteral("label_20"));
        sizePolicy.setHeightForWidth(label_20->sizePolicy().hasHeightForWidth());
        label_20->setSizePolicy(sizePolicy);
        QPalette palette13;
        palette13.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette13.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette13.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        label_20->setPalette(palette13);
        label_20->setFont(font);
        label_20->setScaledContents(true);
        label_20->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_9->addWidget(label_20, 1, 0, 1, 1);

        label_21 = new AspectRatioTextLabel(widget_8);
        label_21->setObjectName(QStringLiteral("label_21"));
        sizePolicy.setHeightForWidth(label_21->sizePolicy().hasHeightForWidth());
        label_21->setSizePolicy(sizePolicy);
        label_21->setScaledContents(true);

        gridLayout_9->addWidget(label_21, 1, 1, 1, 1);


        gridLayout_2->addWidget(widget_8, 2, 0, 1, 1);

        lcdNumber = new MyQLCDNumber(FightingTable2);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        sizePolicy.setHeightForWidth(lcdNumber->sizePolicy().hasHeightForWidth());
        lcdNumber->setSizePolicy(sizePolicy);
        QPalette palette14;
        palette14.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette14.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette14.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        lcdNumber->setPalette(palette14);
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        lcdNumber->setFont(font1);
        lcdNumber->setLineWidth(1);
        lcdNumber->setSmallDecimalPoint(false);

        gridLayout_2->addWidget(lcdNumber, 1, 0, 1, 1);

        gridLayout_2->setRowStretch(0, 23);
        gridLayout_2->setRowStretch(1, 47);
        gridLayout_2->setRowStretch(2, 30);

        gridLayout_6->addLayout(gridLayout_2, 0, 0, 1, 1);

        label_8 = new AspectRatioTextLabel(FightingTable2);
        label_8->setObjectName(QStringLiteral("label_8"));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);
        QPalette palette15;
        palette15.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette15.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette15.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        label_8->setPalette(palette15);
        label_8->setScaledContents(true);
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_8, 0, 1, 1, 1);

        gridLayout_6->setColumnStretch(0, 1);
        gridLayout_6->setColumnStretch(1, 1);
        gridLayout_6->setColumnStretch(2, 1);

        gridLayout_7->addLayout(gridLayout_6, 2, 0, 1, 1);

        label_17 = new AspectRatioTextLabel(FightingTable2);
        label_17->setObjectName(QStringLiteral("label_17"));
        sizePolicy.setHeightForWidth(label_17->sizePolicy().hasHeightForWidth());
        label_17->setSizePolicy(sizePolicy);
        QPalette palette16;
        palette16.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette16.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette16.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        label_17->setPalette(palette16);
        label_17->setFont(font);
        label_17->setScaledContents(true);
        label_17->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_17, 3, 0, 1, 1);

        gridLayout_7->setRowStretch(0, 5);
        gridLayout_7->setRowStretch(1, 10);
        gridLayout_7->setRowStretch(2, 75);
        gridLayout_7->setRowStretch(3, 10);

        retranslateUi(FightingTable2);

        QMetaObject::connectSlotsByName(FightingTable2);
    } // setupUi

    void retranslateUi(QWidget *FightingTable2)
    {
        FightingTable2->setWindowTitle(QApplication::translate("FightingTable2", "Form", 0));
        label->setText(QApplication::translate("FightingTable2", "033. PF Boys -42kg", 0));
        label_3->setText(QApplication::translate("FightingTable2", "\320\234\320\270\321\202\321\200\320\270\321\207 \320\237\321\221\321\202\321\200", 0));
        label_2->setText(QApplication::translate("FightingTable2", "\320\223\320\265\320\275\320\260\320\264\320\270\320\271 \320\232\320\276\321\200\320\276\321\202\320\272\320\265\320\262\320\270\321\207", 0));
        rightRegion->setText(QApplication::translate("FightingTable2", "ITA", 0));
        rightFlag->setText(QApplication::translate("FightingTable2", "TextLabel", 0));
        label_16->setText(QApplication::translate("FightingTable2", "TextLabel", 0));
        label_11->setText(QApplication::translate("FightingTable2", "Minus:", 0));
        label_15->setText(QApplication::translate("FightingTable2", "TextLabel", 0));
        label_12->setText(QApplication::translate("FightingTable2", "Ex:", 0));
        label_18->setText(QApplication::translate("FightingTable2", "Fo:", 0));
        label_19->setText(QApplication::translate("FightingTable2", "TextLabel", 0));
        leftFlag->setText(QApplication::translate("FightingTable2", "TextLabel", 0));
        leftRegion->setText(QApplication::translate("FightingTable2", "RUS", 0));
        label_10->setText(QApplication::translate("FightingTable2", "Minus:", 0));
        label_13->setText(QApplication::translate("FightingTable2", "TextLabel", 0));
        label_9->setText(QApplication::translate("FightingTable2", "Ex:", 0));
        label_14->setText(QApplication::translate("FightingTable2", "TextLabel", 0));
        label_20->setText(QApplication::translate("FightingTable2", "Fo:", 0));
        label_21->setText(QApplication::translate("FightingTable2", "TextLabel", 0));
        label_8->setText(QApplication::translate("FightingTable2", "69:69", 0));
        label_17->setText(QApplication::translate("FightingTable2", "Round 1/2", 0));
    } // retranslateUi

};

namespace Ui {
    class FightingTable2: public Ui_FightingTable2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIGHTINGTABLE2_H
