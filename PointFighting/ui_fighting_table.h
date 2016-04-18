/********************************************************************************
** Form generated from reading UI file 'fighting_table.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIGHTING_TABLE_H
#define UI_FIGHTING_TABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FightingTable
{
public:
    QGridLayout *gridLayout;
    QWidget *widgetRoof;
    QGridLayout *gridLayout_2;
    QLabel *labelLeftHead;
    QLabel *labelTime;
    QLabel *labelRightHead;
    QWidget *widgetFooter;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonStart;
    QPushButton *pushButtonDoctor;
    QLabel *labelDoctorTimer;
    QSpacerItem *horizontalSpacer;
    QWidget *widgetRight;
    QGridLayout *gridLayout_3;
    QPushButton *pushButtonPointRight;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QLabel *labelRegion_right;
    QLabel *labelRightFlag;
    QLabel *labelFIO_right;
    QWidget *widgetLeft;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_4;
    QLabel *labelFIO_left;
    QLabel *labelLeftFlag;
    QLabel *labelRegion_left;
    QPushButton *pushButtonPointLeft;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *label_4;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QWidget *FightingTable)
    {
        if (FightingTable->objectName().isEmpty())
            FightingTable->setObjectName(QStringLiteral("FightingTable"));
        FightingTable->resize(863, 680);
        gridLayout = new QGridLayout(FightingTable);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widgetRoof = new QWidget(FightingTable);
        widgetRoof->setObjectName(QStringLiteral("widgetRoof"));
        QFont font;
        font.setPointSize(22);
        widgetRoof->setFont(font);
        widgetRoof->setStyleSheet(QStringLiteral("background-color: rgb(192, 192, 192);"));
        gridLayout_2 = new QGridLayout(widgetRoof);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        labelLeftHead = new QLabel(widgetRoof);
        labelLeftHead->setObjectName(QStringLiteral("labelLeftHead"));

        gridLayout_2->addWidget(labelLeftHead, 0, 0, 1, 1);

        labelTime = new QLabel(widgetRoof);
        labelTime->setObjectName(QStringLiteral("labelTime"));
        labelTime->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(labelTime, 0, 1, 1, 1);

        labelRightHead = new QLabel(widgetRoof);
        labelRightHead->setObjectName(QStringLiteral("labelRightHead"));
        labelRightHead->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(labelRightHead, 0, 2, 1, 1);


        gridLayout->addWidget(widgetRoof, 0, 0, 1, 2);

        widgetFooter = new QWidget(FightingTable);
        widgetFooter->setObjectName(QStringLiteral("widgetFooter"));
        widgetFooter->setStyleSheet(QStringLiteral(""));
        horizontalLayout = new QHBoxLayout(widgetFooter);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButtonStart = new QPushButton(widgetFooter);
        pushButtonStart->setObjectName(QStringLiteral("pushButtonStart"));

        horizontalLayout->addWidget(pushButtonStart);

        pushButtonDoctor = new QPushButton(widgetFooter);
        pushButtonDoctor->setObjectName(QStringLiteral("pushButtonDoctor"));
        pushButtonDoctor->setEnabled(true);

        horizontalLayout->addWidget(pushButtonDoctor);

        labelDoctorTimer = new QLabel(widgetFooter);
        labelDoctorTimer->setObjectName(QStringLiteral("labelDoctorTimer"));
        QFont font1;
        font1.setPointSize(14);
        labelDoctorTimer->setFont(font1);

        horizontalLayout->addWidget(labelDoctorTimer);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addWidget(widgetFooter, 2, 0, 1, 2);

        widgetRight = new QWidget(FightingTable);
        widgetRight->setObjectName(QStringLiteral("widgetRight"));
        widgetRight->setStyleSheet(QStringLiteral("background-color: rgb(0, 85, 255);"));
        gridLayout_3 = new QGridLayout(widgetRight);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        pushButtonPointRight = new QPushButton(widgetRight);
        pushButtonPointRight->setObjectName(QStringLiteral("pushButtonPointRight"));
        pushButtonPointRight->setMinimumSize(QSize(0, 256));
        QPalette palette;
        QBrush brush(QColor(0, 85, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        QBrush brush2(QColor(120, 120, 120, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        pushButtonPointRight->setPalette(palette);
        QFont font2;
        font2.setPointSize(99);
        pushButtonPointRight->setFont(font2);
        pushButtonPointRight->setCheckable(false);

        gridLayout_3->addWidget(pushButtonPointRight, 5, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_3, 4, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 128, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 6, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 0, 0, 1, 1);

        labelRegion_right = new QLabel(widgetRight);
        labelRegion_right->setObjectName(QStringLiteral("labelRegion_right"));
        QFont font3;
        font3.setPointSize(15);
        labelRegion_right->setFont(font3);
        labelRegion_right->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        labelRegion_right->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(labelRegion_right, 3, 0, 1, 1);

        labelRightFlag = new QLabel(widgetRight);
        labelRightFlag->setObjectName(QStringLiteral("labelRightFlag"));
        labelRightFlag->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(labelRightFlag, 2, 0, 1, 1);

        labelFIO_right = new QLabel(widgetRight);
        labelFIO_right->setObjectName(QStringLiteral("labelFIO_right"));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush);
        labelFIO_right->setPalette(palette1);
        QFont font4;
        font4.setPointSize(25);
        labelFIO_right->setFont(font4);
        labelFIO_right->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        labelFIO_right->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(labelFIO_right, 1, 0, 1, 1);


        gridLayout->addWidget(widgetRight, 1, 1, 1, 1);

        widgetLeft = new QWidget(FightingTable);
        widgetLeft->setObjectName(QStringLiteral("widgetLeft"));
        QPalette palette2;
        QBrush brush3(QColor(255, 0, 0, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush3);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush3);
        widgetLeft->setPalette(palette2);
        widgetLeft->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 0);"));
        verticalLayout = new QVBoxLayout(widgetLeft);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_4 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        labelFIO_left = new QLabel(widgetLeft);
        labelFIO_left->setObjectName(QStringLiteral("labelFIO_left"));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette3.setBrush(QPalette::Active, QPalette::Button, brush3);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush3);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush3);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush3);
        labelFIO_left->setPalette(palette3);
        labelFIO_left->setFont(font4);
        labelFIO_left->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        labelFIO_left->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelFIO_left);

        labelLeftFlag = new QLabel(widgetLeft);
        labelLeftFlag->setObjectName(QStringLiteral("labelLeftFlag"));
        labelLeftFlag->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelLeftFlag);

        labelRegion_left = new QLabel(widgetLeft);
        labelRegion_left->setObjectName(QStringLiteral("labelRegion_left"));
        labelRegion_left->setFont(font3);
        labelRegion_left->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        labelRegion_left->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelRegion_left);

        pushButtonPointLeft = new QPushButton(widgetLeft);
        pushButtonPointLeft->setObjectName(QStringLiteral("pushButtonPointLeft"));
        pushButtonPointLeft->setMinimumSize(QSize(0, 256));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::Button, brush3);
        palette4.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette4.setBrush(QPalette::Active, QPalette::Window, brush3);
        palette4.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette4.setBrush(QPalette::Inactive, QPalette::Window, brush3);
        palette4.setBrush(QPalette::Disabled, QPalette::Button, brush3);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        palette4.setBrush(QPalette::Disabled, QPalette::Window, brush3);
        pushButtonPointLeft->setPalette(palette4);
        pushButtonPointLeft->setFont(font2);
        pushButtonPointLeft->setAutoDefault(false);
        pushButtonPointLeft->setFlat(false);

        verticalLayout->addWidget(pushButtonPointLeft);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(widgetLeft);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font1);
        label->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label);

        label_4 = new QLabel(widgetLeft);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font1);
        label_4->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));

        horizontalLayout_2->addWidget(label_4);


        verticalLayout->addLayout(horizontalLayout_2);

        label_2 = new QLabel(widgetLeft);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font1);
        label_2->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(widgetLeft);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font1);
        label_3->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(label_3);


        gridLayout->addWidget(widgetLeft, 1, 0, 1, 1);

        gridLayout->setRowStretch(0, 10);

        retranslateUi(FightingTable);

        pushButtonPointLeft->setDefault(false);


        QMetaObject::connectSlotsByName(FightingTable);
    } // setupUi

    void retranslateUi(QWidget *FightingTable)
    {
        FightingTable->setWindowTitle(QApplication::translate("FightingTable", "Form", 0));
        labelLeftHead->setText(QApplication::translate("FightingTable", "\320\233\320\265\320\262\321\213\320\271", 0));
        labelTime->setText(QApplication::translate("FightingTable", "\320\222\321\200\320\265\320\274\321\217", 0));
        labelRightHead->setText(QApplication::translate("FightingTable", "\320\237\321\200\320\260\320\262\321\213\320\271", 0));
        pushButtonStart->setText(QApplication::translate("FightingTable", "Start", 0));
        pushButtonDoctor->setText(QApplication::translate("FightingTable", "Call a doctor!", 0));
        labelDoctorTimer->setText(QString());
        pushButtonPointRight->setText(QApplication::translate("FightingTable", "0", 0));
        labelRegion_right->setText(QApplication::translate("FightingTable", "TextLabel", 0));
        labelRightFlag->setText(QApplication::translate("FightingTable", "TextLabel", 0));
        labelFIO_right->setText(QApplication::translate("FightingTable", "TextLabel", 0));
        labelFIO_left->setText(QApplication::translate("FightingTable", "TextLabel", 0));
        labelLeftFlag->setText(QApplication::translate("FightingTable", "TextLabel", 0));
        labelRegion_left->setText(QApplication::translate("FightingTable", "TextLabel", 0));
        pushButtonPointLeft->setText(QApplication::translate("FightingTable", "0", 0));
        label->setText(QApplication::translate("FightingTable", "Minus:", 0));
        label_4->setText(QApplication::translate("FightingTable", "Minus:", 0));
        label_2->setText(QApplication::translate("FightingTable", "Fo:", 0));
        label_3->setText(QApplication::translate("FightingTable", "Ex:", 0));
    } // retranslateUi

};

namespace Ui {
    class FightingTable: public Ui_FightingTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIGHTING_TABLE_H
