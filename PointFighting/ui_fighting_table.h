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
    QWidget *widgetLeft;
    QPushButton *pushButtonPointLeft;
    QWidget *widgetRight;
    QPushButton *pushButtonPointRight;
    QWidget *widgetFooter;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonStart;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;

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
        font.setPointSize(16);
        widgetRoof->setFont(font);
        widgetRoof->setStyleSheet(QStringLiteral(""));
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

        widgetLeft = new QWidget(FightingTable);
        widgetLeft->setObjectName(QStringLiteral("widgetLeft"));
        widgetLeft->setStyleSheet(QStringLiteral("background-color: rgb(0, 85, 255);"));
        pushButtonPointLeft = new QPushButton(widgetLeft);
        pushButtonPointLeft->setObjectName(QStringLiteral("pushButtonPointLeft"));
        pushButtonPointLeft->setGeometry(QRect(60, 180, 281, 191));
        QFont font1;
        font1.setPointSize(26);
        pushButtonPointLeft->setFont(font1);

        gridLayout->addWidget(widgetLeft, 1, 0, 1, 1);

        widgetRight = new QWidget(FightingTable);
        widgetRight->setObjectName(QStringLiteral("widgetRight"));
        widgetRight->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 0);"));
        pushButtonPointRight = new QPushButton(widgetRight);
        pushButtonPointRight->setObjectName(QStringLiteral("pushButtonPointRight"));
        pushButtonPointRight->setGeometry(QRect(100, 180, 251, 201));
        pushButtonPointRight->setFont(font1);

        gridLayout->addWidget(widgetRight, 1, 1, 1, 1);

        widgetFooter = new QWidget(FightingTable);
        widgetFooter->setObjectName(QStringLiteral("widgetFooter"));
        widgetFooter->setStyleSheet(QStringLiteral(""));
        horizontalLayout = new QHBoxLayout(widgetFooter);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButtonStart = new QPushButton(widgetFooter);
        pushButtonStart->setObjectName(QStringLiteral("pushButtonStart"));

        horizontalLayout->addWidget(pushButtonStart);

        pushButton = new QPushButton(widgetFooter);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addWidget(widgetFooter, 2, 0, 1, 2);

        gridLayout->setRowStretch(0, 10);
        gridLayout->setRowStretch(1, 80);
        gridLayout->setRowStretch(2, 10);

        retranslateUi(FightingTable);

        QMetaObject::connectSlotsByName(FightingTable);
    } // setupUi

    void retranslateUi(QWidget *FightingTable)
    {
        FightingTable->setWindowTitle(QApplication::translate("FightingTable", "Form", 0));
        labelLeftHead->setText(QApplication::translate("FightingTable", "\320\233\320\265\320\262\321\213\320\271", 0));
        labelTime->setText(QApplication::translate("FightingTable", "\320\222\321\200\320\265\320\274\321\217", 0));
        labelRightHead->setText(QApplication::translate("FightingTable", "\320\237\321\200\320\260\320\262\321\213\320\271", 0));
        pushButtonPointLeft->setText(QApplication::translate("FightingTable", "0", 0));
        pushButtonPointRight->setText(QApplication::translate("FightingTable", "0", 0));
        pushButtonStart->setText(QApplication::translate("FightingTable", "Start", 0));
        pushButton->setText(QApplication::translate("FightingTable", "Call a doctor!", 0));
    } // retranslateUi

};

namespace Ui {
    class FightingTable: public Ui_FightingTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIGHTING_TABLE_H
