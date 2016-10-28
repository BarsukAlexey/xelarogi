/********************************************************************************
** Form generated from reading UI file 'fighting_table.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
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
#include <QtWidgets/QWidget>
#include <aspectratiotextlabel.h>

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
    AspectRatioTextLabel *labelDoctorTimer;

    void setupUi(QWidget *FightingTable)
    {
        if (FightingTable->objectName().isEmpty())
            FightingTable->setObjectName(QStringLiteral("FightingTable"));
        FightingTable->resize(863, 680);
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(FightingTable->sizePolicy().hasHeightForWidth());
        FightingTable->setSizePolicy(sizePolicy);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        FightingTable->setFont(font);
        gridLayout = new QGridLayout(FightingTable);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMaximumSize);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widgetRoof = new QWidget(FightingTable);
        widgetRoof->setObjectName(QStringLiteral("widgetRoof"));
        sizePolicy.setHeightForWidth(widgetRoof->sizePolicy().hasHeightForWidth());
        widgetRoof->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setPointSize(22);
        font1.setBold(true);
        font1.setWeight(75);
        widgetRoof->setFont(font1);
        widgetRoof->setStyleSheet(QStringLiteral("background-color: rgb(192, 192, 192);"));
        horizontalLayoutWidgetRoof = new QHBoxLayout(widgetRoof);
        horizontalLayoutWidgetRoof->setObjectName(QStringLiteral("horizontalLayoutWidgetRoof"));
        labelLeftHead = new AspectRatioTextLabel(widgetRoof);
        labelLeftHead->setObjectName(QStringLiteral("labelLeftHead"));
        sizePolicy.setHeightForWidth(labelLeftHead->sizePolicy().hasHeightForWidth());
        labelLeftHead->setSizePolicy(sizePolicy);
        labelLeftHead->setFont(font);

        horizontalLayoutWidgetRoof->addWidget(labelLeftHead);

        labelTime = new AspectRatioTextLabel(widgetRoof);
        labelTime->setObjectName(QStringLiteral("labelTime"));
        sizePolicy.setHeightForWidth(labelTime->sizePolicy().hasHeightForWidth());
        labelTime->setSizePolicy(sizePolicy);
        labelTime->setFont(font);
        labelTime->setAlignment(Qt::AlignCenter);

        horizontalLayoutWidgetRoof->addWidget(labelTime);

        labelRightHead = new AspectRatioTextLabel(widgetRoof);
        labelRightHead->setObjectName(QStringLiteral("labelRightHead"));
        sizePolicy.setHeightForWidth(labelRightHead->sizePolicy().hasHeightForWidth());
        labelRightHead->setSizePolicy(sizePolicy);
        labelRightHead->setFont(font);
        labelRightHead->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayoutWidgetRoof->addWidget(labelRightHead);

        horizontalLayoutWidgetRoof->setStretch(0, 1);
        horizontalLayoutWidgetRoof->setStretch(1, 1);
        horizontalLayoutWidgetRoof->setStretch(2, 1);

        gridLayout->addWidget(widgetRoof, 0, 0, 1, 1);

        horizontalLayoutMain = new QHBoxLayout();
        horizontalLayoutMain->setSpacing(0);
        horizontalLayoutMain->setObjectName(QStringLiteral("horizontalLayoutMain"));

        gridLayout->addLayout(horizontalLayoutMain, 1, 0, 1, 1);

        widgetFooter = new QWidget(FightingTable);
        widgetFooter->setObjectName(QStringLiteral("widgetFooter"));
        sizePolicy.setHeightForWidth(widgetFooter->sizePolicy().hasHeightForWidth());
        widgetFooter->setSizePolicy(sizePolicy);
        widgetFooter->setFont(font);
        widgetFooter->setStyleSheet(QStringLiteral("background-color: rgb(192, 192, 192);"));
        widgetFooterHorizontalLayout = new QHBoxLayout(widgetFooter);
        widgetFooterHorizontalLayout->setObjectName(QStringLiteral("widgetFooterHorizontalLayout"));
        labelDoctorTimer = new AspectRatioTextLabel(widgetFooter);
        labelDoctorTimer->setObjectName(QStringLiteral("labelDoctorTimer"));
        sizePolicy.setHeightForWidth(labelDoctorTimer->sizePolicy().hasHeightForWidth());
        labelDoctorTimer->setSizePolicy(sizePolicy);
        labelDoctorTimer->setFont(font1);

        widgetFooterHorizontalLayout->addWidget(labelDoctorTimer);


        gridLayout->addWidget(widgetFooter, 2, 0, 1, 1);

        gridLayout->setRowStretch(0, 10);
        gridLayout->setRowStretch(1, 80);
        gridLayout->setRowStretch(2, 5);

        retranslateUi(FightingTable);

        QMetaObject::connectSlotsByName(FightingTable);
    } // setupUi

    void retranslateUi(QWidget *FightingTable)
    {
        FightingTable->setWindowTitle(QApplication::translate("FightingTable", "Form", 0));
        labelLeftHead->setText(QApplication::translate("FightingTable", "\320\233\320\265\320\262\321\213\320\271", 0));
        labelTime->setText(QApplication::translate("FightingTable", "\320\222\321\200\320\265\320\274\321\217", 0));
        labelRightHead->setText(QApplication::translate("FightingTable", "asdafsdgsdahfhfdshgfdssdgfdgfsdgfsdgsfdgsfdgsfdgfdgfdgfdgsfdgsfdgfdgfdgdsfgfd", 0));
        labelDoctorTimer->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FightingTable: public Ui_FightingTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIGHTING_TABLE_H
