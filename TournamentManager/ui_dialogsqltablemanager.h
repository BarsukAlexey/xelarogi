/********************************************************************************
** Form generated from reading UI file 'dialogsqltablemanager.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSQLTABLEMANAGER_H
#define UI_DIALOGSQLTABLEMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "sqltablemanager.h"

QT_BEGIN_NAMESPACE

class Ui_DialogSqlTableManager
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTitle;
    QLabel *labelMessage;
    SqlTableManager *sqlTableManager;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButtonSelect;
    QPushButton *pushButtonJustAdd;
    QPushButton *pushButtonStop;

    void setupUi(QDialog *DialogSqlTableManager)
    {
        if (DialogSqlTableManager->objectName().isEmpty())
            DialogSqlTableManager->setObjectName(QStringLiteral("DialogSqlTableManager"));
        DialogSqlTableManager->resize(800, 600);
        DialogSqlTableManager->setMinimumSize(QSize(800, 600));
        verticalLayout = new QVBoxLayout(DialogSqlTableManager);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        labelTitle = new QLabel(DialogSqlTableManager);
        labelTitle->setObjectName(QStringLiteral("labelTitle"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelTitle->sizePolicy().hasHeightForWidth());
        labelTitle->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        labelTitle->setFont(font);
        labelTitle->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelTitle);

        labelMessage = new QLabel(DialogSqlTableManager);
        labelMessage->setObjectName(QStringLiteral("labelMessage"));
        labelMessage->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelMessage);

        sqlTableManager = new SqlTableManager(DialogSqlTableManager);
        sqlTableManager->setObjectName(QStringLiteral("sqlTableManager"));

        verticalLayout->addWidget(sqlTableManager);

        widget = new QWidget(DialogSqlTableManager);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButtonSelect = new QPushButton(widget);
        pushButtonSelect->setObjectName(QStringLiteral("pushButtonSelect"));

        horizontalLayout_2->addWidget(pushButtonSelect);

        pushButtonJustAdd = new QPushButton(widget);
        pushButtonJustAdd->setObjectName(QStringLiteral("pushButtonJustAdd"));

        horizontalLayout_2->addWidget(pushButtonJustAdd);

        pushButtonStop = new QPushButton(widget);
        pushButtonStop->setObjectName(QStringLiteral("pushButtonStop"));

        horizontalLayout_2->addWidget(pushButtonStop);


        verticalLayout->addWidget(widget);

        verticalLayout->setStretch(2, 75);

        retranslateUi(DialogSqlTableManager);

        QMetaObject::connectSlotsByName(DialogSqlTableManager);
    } // setupUi

    void retranslateUi(QDialog *DialogSqlTableManager)
    {
        DialogSqlTableManager->setWindowTitle(QApplication::translate("DialogSqlTableManager", "Dialog", 0));
        labelTitle->setText(QApplication::translate("DialogSqlTableManager", "\320\227\320\260\320\263\320\276\320\273\320\276\320\262\320\276\320\272", 0));
        labelMessage->setText(QApplication::translate("DialogSqlTableManager", "TextLabel", 0));
        pushButtonSelect->setText(QApplication::translate("DialogSqlTableManager", "\320\227\320\260\320\274\320\265\320\275\320\270\321\202\321\214 \320\275\320\260 \320\262\321\213\320\261\321\200\320\260\320\275\320\275\321\203\321\216 \320\267\320\260\320\277\320\270\321\201\321\214", 0));
        pushButtonJustAdd->setText(QApplication::translate("DialogSqlTableManager", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \"\320\272\320\260\320\272 \320\265\321\201\321\202\321\214\"", 0));
        pushButtonStop->setText(QApplication::translate("DialogSqlTableManager", "\320\236\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214 \320\267\320\260\320\263\321\200\321\203\320\267\320\272\321\203 \320\267\320\260\321\217\320\262\320\276\320\272", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogSqlTableManager: public Ui_DialogSqlTableManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSQLTABLEMANAGER_H
