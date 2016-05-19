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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "aspectratiotextlabel.h"

QT_BEGIN_NAMESPACE

class Ui_FightingTable
{
public:
    QGridLayout *gridLayout;
    QWidget *widgetRoof;
    QHBoxLayout *horizontalLayoutWidgetRoof;
    AspectRatioTextLabel *labelLeftHead;
    AspectRatioTextLabel *labelTime;
    AspectRatioTextLabel *labelRightHead;
    QHBoxLayout *horizontalLayoutMain;
    QWidget *widgetFooter;
    QHBoxLayout *widgetFooterHorizontalLayout;
    QLabel *labelDoctorTimer;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *FightingTable)
    {
        if (FightingTable->objectName().isEmpty())
            FightingTable->setObjectName(QStringLiteral("FightingTable"));
        FightingTable->resize(863, 680);
        gridLayout = new QGridLayout(FightingTable);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMaximumSize);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widgetRoof = new QWidget(FightingTable);
        widgetRoof->setObjectName(QStringLiteral("widgetRoof"));
        QFont font;
        font.setPointSize(22);
        widgetRoof->setFont(font);
        widgetRoof->setStyleSheet(QStringLiteral("background-color: rgb(192, 192, 192);"));
        horizontalLayoutWidgetRoof = new QHBoxLayout(widgetRoof);
        horizontalLayoutWidgetRoof->setObjectName(QStringLiteral("horizontalLayoutWidgetRoof"));
        labelLeftHead = new AspectRatioTextLabel(widgetRoof);
        labelLeftHead->setObjectName(QStringLiteral("labelLeftHead"));

        horizontalLayoutWidgetRoof->addWidget(labelLeftHead);

        labelTime = new AspectRatioTextLabel(widgetRoof);
        labelTime->setObjectName(QStringLiteral("labelTime"));
        labelTime->setAlignment(Qt::AlignCenter);

        horizontalLayoutWidgetRoof->addWidget(labelTime);

        labelRightHead = new AspectRatioTextLabel(widgetRoof);
        labelRightHead->setObjectName(QStringLiteral("labelRightHead"));
        labelRightHead->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayoutWidgetRoof->addWidget(labelRightHead);


        gridLayout->addWidget(widgetRoof, 0, 0, 1, 1);

        horizontalLayoutMain = new QHBoxLayout();
        horizontalLayoutMain->setSpacing(0);
        horizontalLayoutMain->setObjectName(QStringLiteral("horizontalLayoutMain"));

        gridLayout->addLayout(horizontalLayoutMain, 1, 0, 1, 1);

        widgetFooter = new QWidget(FightingTable);
        widgetFooter->setObjectName(QStringLiteral("widgetFooter"));
        widgetFooter->setStyleSheet(QStringLiteral("background-color: rgb(192, 192, 192);"));
        widgetFooterHorizontalLayout = new QHBoxLayout(widgetFooter);
        widgetFooterHorizontalLayout->setObjectName(QStringLiteral("widgetFooterHorizontalLayout"));
        labelDoctorTimer = new QLabel(widgetFooter);
        labelDoctorTimer->setObjectName(QStringLiteral("labelDoctorTimer"));
        labelDoctorTimer->setFont(font);

        widgetFooterHorizontalLayout->addWidget(labelDoctorTimer);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        widgetFooterHorizontalLayout->addItem(horizontalSpacer);


        gridLayout->addWidget(widgetFooter, 2, 0, 1, 1);

        gridLayout->setRowStretch(0, 5);
        gridLayout->setRowStretch(1, 90);
        gridLayout->setRowStretch(2, 5);

        retranslateUi(FightingTable);

        QMetaObject::connectSlotsByName(FightingTable);
    } // setupUi

    void retranslateUi(QWidget *FightingTable)
    {
        FightingTable->setWindowTitle(QApplication::translate("FightingTable", "Form", 0));
        labelLeftHead->setText(QApplication::translate("FightingTable", "\320\233\320\265\320\262\321\213\320\271", 0));
        labelTime->setText(QApplication::translate("FightingTable", "\320\222\321\200\320\265\320\274\321\217", 0));
        labelRightHead->setText(QApplication::translate("FightingTable", "\320\237\321\200\320\260\320\262\321\213\320\271", 0));
        labelDoctorTimer->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FightingTable: public Ui_FightingTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIGHTING_TABLE_H
