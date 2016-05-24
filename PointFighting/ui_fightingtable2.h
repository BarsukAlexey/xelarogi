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
    QGridLayout *gridLayoutMain;
    AspectRatioTextLabel *labelLeftHead;
    AspectRatioTextLabel *labelCategory;
    QGridLayout *gridLayoutCenter;
    QGridLayout *gridLayout_5;
    QWidget *widget_5;
    QGridLayout *gridLayout_4;
    AspectRatioTextLabel *rightRegion;
    AspectRatioPixmapLabel *rightFlag;
    MyQLCDNumber *rightLcdNumber;
    QWidget *widget_10;
    QGridLayout *gridLayout_8;
    AspectRatioPixmapLabel *rightEx;
    AspectRatioTextLabel *labelRightMinus;
    AspectRatioPixmapLabel *rightMinus;
    AspectRatioTextLabel *labelRightEx;
    AspectRatioTextLabel *labelRightFo;
    AspectRatioPixmapLabel *rightFo;
    QGridLayout *gridLayout_2;
    QWidget *widget_3;
    QGridLayout *gridLayout_3;
    AspectRatioPixmapLabel *leftFlag;
    AspectRatioTextLabel *leftRegion;
    QWidget *widget_8;
    QGridLayout *gridLayout_9;
    AspectRatioTextLabel *labelLeftMinus;
    AspectRatioPixmapLabel *leftMinus;
    AspectRatioTextLabel *labelLeftEx;
    AspectRatioPixmapLabel *leftEx;
    AspectRatioTextLabel *labelLeftFo;
    AspectRatioPixmapLabel *leftFo;
    MyQLCDNumber *leftLcdNumber;
    AspectRatioTextLabel *labelTime;
    QWidget *widget_2;
    QGridLayout *gridLayout;
    AspectRatioTextLabel *leftName;
    AspectRatioTextLabel *rightName;

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
        gridLayoutMain = new QGridLayout(FightingTable2);
        gridLayoutMain->setObjectName(QStringLiteral("gridLayoutMain"));
        labelLeftHead = new AspectRatioTextLabel(FightingTable2);
        labelLeftHead->setObjectName(QStringLiteral("labelLeftHead"));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelLeftHead->sizePolicy().hasHeightForWidth());
        labelLeftHead->setSizePolicy(sizePolicy);
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush2(QColor(120, 120, 120, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        labelLeftHead->setPalette(palette1);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        labelLeftHead->setFont(font);
        labelLeftHead->setScaledContents(true);
        labelLeftHead->setAlignment(Qt::AlignCenter);

        gridLayoutMain->addWidget(labelLeftHead, 3, 0, 1, 1);

        labelCategory = new AspectRatioTextLabel(FightingTable2);
        labelCategory->setObjectName(QStringLiteral("labelCategory"));
        sizePolicy.setHeightForWidth(labelCategory->sizePolicy().hasHeightForWidth());
        labelCategory->setSizePolicy(sizePolicy);
        QPalette palette2;
        QBrush brush3(QColor(255, 196, 19, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        labelCategory->setPalette(palette2);
        labelCategory->setFont(font);
        labelCategory->setScaledContents(true);
        labelCategory->setAlignment(Qt::AlignCenter);

        gridLayoutMain->addWidget(labelCategory, 0, 0, 1, 1);

        gridLayoutCenter = new QGridLayout();
        gridLayoutCenter->setObjectName(QStringLiteral("gridLayoutCenter"));
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
        QPalette palette3;
        QBrush brush4(QColor(0, 85, 255, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        rightRegion->setPalette(palette3);
        rightRegion->setFont(font);
        rightRegion->setScaledContents(true);

        gridLayout_4->addWidget(rightRegion, 0, 1, 1, 1);

        rightFlag = new AspectRatioPixmapLabel(widget_5);
        rightFlag->setObjectName(QStringLiteral("rightFlag"));
        sizePolicy.setHeightForWidth(rightFlag->sizePolicy().hasHeightForWidth());
        rightFlag->setSizePolicy(sizePolicy);
        rightFlag->setScaledContents(false);
        rightFlag->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(rightFlag, 0, 2, 1, 1);


        gridLayout_5->addWidget(widget_5, 0, 0, 1, 1);

        rightLcdNumber = new MyQLCDNumber(FightingTable2);
        rightLcdNumber->setObjectName(QStringLiteral("rightLcdNumber"));
        sizePolicy.setHeightForWidth(rightLcdNumber->sizePolicy().hasHeightForWidth());
        rightLcdNumber->setSizePolicy(sizePolicy);
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        rightLcdNumber->setPalette(palette4);
        rightLcdNumber->setLineWidth(1);

        gridLayout_5->addWidget(rightLcdNumber, 1, 0, 1, 1);

        widget_10 = new QWidget(FightingTable2);
        widget_10->setObjectName(QStringLiteral("widget_10"));
        sizePolicy.setHeightForWidth(widget_10->sizePolicy().hasHeightForWidth());
        widget_10->setSizePolicy(sizePolicy);
        gridLayout_8 = new QGridLayout(widget_10);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        rightEx = new AspectRatioPixmapLabel(widget_10);
        rightEx->setObjectName(QStringLiteral("rightEx"));
        sizePolicy.setHeightForWidth(rightEx->sizePolicy().hasHeightForWidth());
        rightEx->setSizePolicy(sizePolicy);

        gridLayout_8->addWidget(rightEx, 2, 1, 1, 1);

        labelRightMinus = new AspectRatioTextLabel(widget_10);
        labelRightMinus->setObjectName(QStringLiteral("labelRightMinus"));
        sizePolicy.setHeightForWidth(labelRightMinus->sizePolicy().hasHeightForWidth());
        labelRightMinus->setSizePolicy(sizePolicy);
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        labelRightMinus->setPalette(palette5);
        labelRightMinus->setFont(font);
        labelRightMinus->setScaledContents(true);
        labelRightMinus->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(labelRightMinus, 0, 0, 1, 1);

        rightMinus = new AspectRatioPixmapLabel(widget_10);
        rightMinus->setObjectName(QStringLiteral("rightMinus"));
        sizePolicy.setHeightForWidth(rightMinus->sizePolicy().hasHeightForWidth());
        rightMinus->setSizePolicy(sizePolicy);

        gridLayout_8->addWidget(rightMinus, 0, 1, 1, 1);

        labelRightEx = new AspectRatioTextLabel(widget_10);
        labelRightEx->setObjectName(QStringLiteral("labelRightEx"));
        sizePolicy.setHeightForWidth(labelRightEx->sizePolicy().hasHeightForWidth());
        labelRightEx->setSizePolicy(sizePolicy);
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette6.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette6.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        labelRightEx->setPalette(palette6);
        labelRightEx->setFont(font);
        labelRightEx->setScaledContents(true);
        labelRightEx->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(labelRightEx, 2, 0, 1, 1);

        labelRightFo = new AspectRatioTextLabel(widget_10);
        labelRightFo->setObjectName(QStringLiteral("labelRightFo"));
        sizePolicy.setHeightForWidth(labelRightFo->sizePolicy().hasHeightForWidth());
        labelRightFo->setSizePolicy(sizePolicy);
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette7.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette7.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        labelRightFo->setPalette(palette7);
        labelRightFo->setFont(font);
        labelRightFo->setScaledContents(true);
        labelRightFo->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(labelRightFo, 1, 0, 1, 1);

        rightFo = new AspectRatioPixmapLabel(widget_10);
        rightFo->setObjectName(QStringLiteral("rightFo"));
        sizePolicy.setHeightForWidth(rightFo->sizePolicy().hasHeightForWidth());
        rightFo->setSizePolicy(sizePolicy);

        gridLayout_8->addWidget(rightFo, 1, 1, 1, 1);


        gridLayout_5->addWidget(widget_10, 2, 0, 1, 1);

        gridLayout_5->setRowStretch(0, 23);
        gridLayout_5->setRowStretch(1, 47);
        gridLayout_5->setRowStretch(2, 30);

        gridLayoutCenter->addLayout(gridLayout_5, 0, 2, 1, 1);

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
        QPalette palette8;
        QBrush brush5(QColor(255, 0, 0, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette8.setBrush(QPalette::Active, QPalette::Text, brush5);
        palette8.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        palette8.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        leftFlag->setPalette(palette8);
        leftFlag->setScaledContents(false);
        leftFlag->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(leftFlag, 0, 0, 1, 1);

        leftRegion = new AspectRatioTextLabel(widget_3);
        leftRegion->setObjectName(QStringLiteral("leftRegion"));
        sizePolicy.setHeightForWidth(leftRegion->sizePolicy().hasHeightForWidth());
        leftRegion->setSizePolicy(sizePolicy);
        QPalette palette9;
        palette9.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette9.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette9.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        leftRegion->setPalette(palette9);
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
        labelLeftMinus = new AspectRatioTextLabel(widget_8);
        labelLeftMinus->setObjectName(QStringLiteral("labelLeftMinus"));
        sizePolicy.setHeightForWidth(labelLeftMinus->sizePolicy().hasHeightForWidth());
        labelLeftMinus->setSizePolicy(sizePolicy);
        QPalette palette10;
        palette10.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette10.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette10.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        labelLeftMinus->setPalette(palette10);
        labelLeftMinus->setFont(font);
        labelLeftMinus->setScaledContents(true);
        labelLeftMinus->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_9->addWidget(labelLeftMinus, 0, 0, 1, 1);

        leftMinus = new AspectRatioPixmapLabel(widget_8);
        leftMinus->setObjectName(QStringLiteral("leftMinus"));
        sizePolicy.setHeightForWidth(leftMinus->sizePolicy().hasHeightForWidth());
        leftMinus->setSizePolicy(sizePolicy);

        gridLayout_9->addWidget(leftMinus, 0, 1, 1, 1);

        labelLeftEx = new AspectRatioTextLabel(widget_8);
        labelLeftEx->setObjectName(QStringLiteral("labelLeftEx"));
        sizePolicy.setHeightForWidth(labelLeftEx->sizePolicy().hasHeightForWidth());
        labelLeftEx->setSizePolicy(sizePolicy);
        QPalette palette11;
        palette11.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette11.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette11.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        labelLeftEx->setPalette(palette11);
        labelLeftEx->setFont(font);
        labelLeftEx->setScaledContents(true);
        labelLeftEx->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_9->addWidget(labelLeftEx, 2, 0, 1, 1);

        leftEx = new AspectRatioPixmapLabel(widget_8);
        leftEx->setObjectName(QStringLiteral("leftEx"));
        sizePolicy.setHeightForWidth(leftEx->sizePolicy().hasHeightForWidth());
        leftEx->setSizePolicy(sizePolicy);

        gridLayout_9->addWidget(leftEx, 2, 1, 1, 1);

        labelLeftFo = new AspectRatioTextLabel(widget_8);
        labelLeftFo->setObjectName(QStringLiteral("labelLeftFo"));
        sizePolicy.setHeightForWidth(labelLeftFo->sizePolicy().hasHeightForWidth());
        labelLeftFo->setSizePolicy(sizePolicy);
        QPalette palette12;
        palette12.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette12.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette12.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        labelLeftFo->setPalette(palette12);
        labelLeftFo->setFont(font);
        labelLeftFo->setScaledContents(true);
        labelLeftFo->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_9->addWidget(labelLeftFo, 1, 0, 1, 1);

        leftFo = new AspectRatioPixmapLabel(widget_8);
        leftFo->setObjectName(QStringLiteral("leftFo"));
        sizePolicy.setHeightForWidth(leftFo->sizePolicy().hasHeightForWidth());
        leftFo->setSizePolicy(sizePolicy);

        gridLayout_9->addWidget(leftFo, 1, 1, 1, 1);


        gridLayout_2->addWidget(widget_8, 2, 0, 1, 1);

        leftLcdNumber = new MyQLCDNumber(FightingTable2);
        leftLcdNumber->setObjectName(QStringLiteral("leftLcdNumber"));
        sizePolicy.setHeightForWidth(leftLcdNumber->sizePolicy().hasHeightForWidth());
        leftLcdNumber->setSizePolicy(sizePolicy);
        QPalette palette13;
        palette13.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette13.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette13.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        leftLcdNumber->setPalette(palette13);
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        leftLcdNumber->setFont(font1);
        leftLcdNumber->setLineWidth(1);
        leftLcdNumber->setSmallDecimalPoint(false);

        gridLayout_2->addWidget(leftLcdNumber, 1, 0, 1, 1);

        gridLayout_2->setRowStretch(0, 23);
        gridLayout_2->setRowStretch(1, 47);
        gridLayout_2->setRowStretch(2, 30);

        gridLayoutCenter->addLayout(gridLayout_2, 0, 0, 1, 1);

        labelTime = new AspectRatioTextLabel(FightingTable2);
        labelTime->setObjectName(QStringLiteral("labelTime"));
        sizePolicy.setHeightForWidth(labelTime->sizePolicy().hasHeightForWidth());
        labelTime->setSizePolicy(sizePolicy);
        QPalette palette14;
        palette14.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette14.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette14.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        labelTime->setPalette(palette14);
        labelTime->setScaledContents(true);
        labelTime->setAlignment(Qt::AlignCenter);

        gridLayoutCenter->addWidget(labelTime, 0, 1, 1, 1);

        gridLayoutCenter->setColumnStretch(0, 1);
        gridLayoutCenter->setColumnStretch(1, 1);
        gridLayoutCenter->setColumnStretch(2, 1);

        gridLayoutMain->addLayout(gridLayoutCenter, 2, 0, 1, 1);

        widget_2 = new QWidget(FightingTable2);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        sizePolicy.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(widget_2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        leftName = new AspectRatioTextLabel(widget_2);
        leftName->setObjectName(QStringLiteral("leftName"));
        sizePolicy.setHeightForWidth(leftName->sizePolicy().hasHeightForWidth());
        leftName->setSizePolicy(sizePolicy);
        QPalette palette15;
        palette15.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette15.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette15.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        leftName->setPalette(palette15);
        leftName->setFont(font);
        leftName->setScaledContents(true);
        leftName->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(leftName, 0, 0, 1, 1);

        rightName = new AspectRatioTextLabel(widget_2);
        rightName->setObjectName(QStringLiteral("rightName"));
        sizePolicy.setHeightForWidth(rightName->sizePolicy().hasHeightForWidth());
        rightName->setSizePolicy(sizePolicy);
        QPalette palette16;
        palette16.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette16.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette16.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        rightName->setPalette(palette16);
        rightName->setFont(font);
        rightName->setScaledContents(true);
        rightName->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(rightName, 0, 1, 1, 1);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 1);

        gridLayoutMain->addWidget(widget_2, 1, 0, 1, 1);

        gridLayoutMain->setRowStretch(0, 5);
        gridLayoutMain->setRowStretch(1, 10);
        gridLayoutMain->setRowStretch(2, 75);
        gridLayoutMain->setRowStretch(3, 10);

        retranslateUi(FightingTable2);

        QMetaObject::connectSlotsByName(FightingTable2);
    } // setupUi

    void retranslateUi(QWidget *FightingTable2)
    {
        FightingTable2->setWindowTitle(QApplication::translate("FightingTable2", "Form", 0));
        labelLeftHead->setText(QApplication::translate("FightingTable2", "Round 1/2", 0));
        labelCategory->setText(QApplication::translate("FightingTable2", "033. PF Boys -42kg", 0));
        rightRegion->setText(QApplication::translate("FightingTable2", "ITA", 0));
        rightFlag->setText(QApplication::translate("FightingTable2", "TextLabel", 0));
        rightEx->setText(QApplication::translate("FightingTable2", "TextLabel", 0));
        labelRightMinus->setText(QApplication::translate("FightingTable2", "Minus:", 0));
        rightMinus->setText(QApplication::translate("FightingTable2", "TextLabel", 0));
        labelRightEx->setText(QApplication::translate("FightingTable2", "Ex:", 0));
        labelRightFo->setText(QApplication::translate("FightingTable2", "Fo:", 0));
        rightFo->setText(QApplication::translate("FightingTable2", "TextLabel", 0));
        leftFlag->setText(QApplication::translate("FightingTable2", "TextLabel", 0));
        leftRegion->setText(QApplication::translate("FightingTable2", "RUS", 0));
        labelLeftMinus->setText(QApplication::translate("FightingTable2", "Minus:", 0));
        leftMinus->setText(QApplication::translate("FightingTable2", "TextLabel", 0));
        labelLeftEx->setText(QApplication::translate("FightingTable2", "Ex:", 0));
        leftEx->setText(QApplication::translate("FightingTable2", "TextLabel", 0));
        labelLeftFo->setText(QApplication::translate("FightingTable2", "Fo:", 0));
        leftFo->setText(QApplication::translate("FightingTable2", "TextLabel", 0));
        labelTime->setText(QApplication::translate("FightingTable2", "69:69", 0));
        leftName->setText(QApplication::translate("FightingTable2", "\320\234\320\270\321\202\321\200\320\270\321\207 \320\237\321\221\321\202\321\200", 0));
        rightName->setText(QApplication::translate("FightingTable2", "\320\223\320\265\320\275\320\260\320\264\320\270\320\271 \320\232\320\276\321\200\320\276\321\202\320\272\320\265\320\262\320\270\321\207", 0));
    } // retranslateUi

};

namespace Ui {
    class FightingTable2: public Ui_FightingTable2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIGHTINGTABLE2_H
