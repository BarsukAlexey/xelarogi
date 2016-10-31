/********************************************************************************
** Form generated from reading UI file 'dialogmanagersqltable.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGMANAGERSQLTABLE_H
#define UI_DIALOGMANAGERSQLTABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogManagerSqlTable
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QTableView *tableView;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget2222;
    QTableView *tableView_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonSave;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonInsert;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *DialogManagerSqlTable)
    {
        if (DialogManagerSqlTable->objectName().isEmpty())
            DialogManagerSqlTable->setObjectName(QStringLiteral("DialogManagerSqlTable"));
        gridLayout = new QGridLayout(DialogManagerSqlTable);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        splitter = new QSplitter(DialogManagerSqlTable);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        tableView = new QTableView(splitter);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setSortingEnabled(true);
        splitter->addWidget(tableView);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget2222 = new QWidget(layoutWidget);
        widget2222->setObjectName(QStringLiteral("widget2222"));

        verticalLayout->addWidget(widget2222);

        tableView_2 = new QTableView(layoutWidget);
        tableView_2->setObjectName(QStringLiteral("tableView_2"));
        tableView_2->setSortingEnabled(true);

        verticalLayout->addWidget(tableView_2);

        splitter->addWidget(layoutWidget);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButtonSave = new QPushButton(DialogManagerSqlTable);
        pushButtonSave->setObjectName(QStringLiteral("pushButtonSave"));

        horizontalLayout->addWidget(pushButtonSave);

        pushButtonCancel = new QPushButton(DialogManagerSqlTable);
        pushButtonCancel->setObjectName(QStringLiteral("pushButtonCancel"));

        horizontalLayout->addWidget(pushButtonCancel);

        pushButtonInsert = new QPushButton(DialogManagerSqlTable);
        pushButtonInsert->setObjectName(QStringLiteral("pushButtonInsert"));

        horizontalLayout->addWidget(pushButtonInsert);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        pushButton = new QPushButton(DialogManagerSqlTable);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(DialogManagerSqlTable);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(DialogManagerSqlTable);

        QMetaObject::connectSlotsByName(DialogManagerSqlTable);
    } // setupUi

    void retranslateUi(QWidget *DialogManagerSqlTable)
    {
        pushButtonSave->setText(QApplication::translate("DialogManagerSqlTable", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217", 0));
        pushButtonCancel->setText(QApplication::translate("DialogManagerSqlTable", "\320\236\321\202\320\272\320\260\321\202\320\270\321\202\321\214 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217", 0));
        pushButtonInsert->setText(QApplication::translate("DialogManagerSqlTable", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\275\320\276\320\262\321\203\321\216 \320\267\320\260\320\277\320\270\321\201\321\214", 0));
        pushButton->setText(QApplication::translate("DialogManagerSqlTable", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", 0));
        pushButton_2->setText(QApplication::translate("DialogManagerSqlTable", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\262 Excel", 0));
        Q_UNUSED(DialogManagerSqlTable);
    } // retranslateUi

};

namespace Ui {
    class DialogManagerSqlTable: public Ui_DialogManagerSqlTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGMANAGERSQLTABLE_H
