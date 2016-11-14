/********************************************************************************
** Form generated from reading UI file 'createtournamentordersdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATETOURNAMENTORDERSDIALOG_H
#define UI_CREATETOURNAMENTORDERSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include "sqltablemanager.h"

QT_BEGIN_NAMESPACE

class Ui_CreateTournamentOrdersDialog
{
public:
    QVBoxLayout *verticalLayout;
    SqlTableManager *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonLoad;
    QPushButton *pushButtonChangeCategory;
    QPushButton *pushButtonShowGrid;

    void setupUi(QDialog *CreateTournamentOrdersDialog)
    {
        if (CreateTournamentOrdersDialog->objectName().isEmpty())
            CreateTournamentOrdersDialog->setObjectName(QStringLiteral("CreateTournamentOrdersDialog"));
        CreateTournamentOrdersDialog->resize(764, 613);
        verticalLayout = new QVBoxLayout(CreateTournamentOrdersDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget = new SqlTableManager(CreateTournamentOrdersDialog);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(widget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButtonLoad = new QPushButton(CreateTournamentOrdersDialog);
        pushButtonLoad->setObjectName(QStringLiteral("pushButtonLoad"));

        horizontalLayout->addWidget(pushButtonLoad);

        pushButtonChangeCategory = new QPushButton(CreateTournamentOrdersDialog);
        pushButtonChangeCategory->setObjectName(QStringLiteral("pushButtonChangeCategory"));

        horizontalLayout->addWidget(pushButtonChangeCategory);

        pushButtonShowGrid = new QPushButton(CreateTournamentOrdersDialog);
        pushButtonShowGrid->setObjectName(QStringLiteral("pushButtonShowGrid"));

        horizontalLayout->addWidget(pushButtonShowGrid);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(CreateTournamentOrdersDialog);

        QMetaObject::connectSlotsByName(CreateTournamentOrdersDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateTournamentOrdersDialog)
    {
        CreateTournamentOrdersDialog->setWindowTitle(QApplication::translate("CreateTournamentOrdersDialog", "\320\224\320\276\320\261\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\267\320\260\321\217\320\262\320\276\320\272 \320\272 \321\202\321\203\321\200\320\275\320\270\321\200\321\203", 0));
        pushButtonLoad->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\270\320\267 excel", 0));
        pushButtonChangeCategory->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\241\320\274\320\265\320\275\320\270\321\202\321\214 \320\272\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\216 \321\203\321\207\320\260\321\201\321\202\320\275\320\270\320\272\320\260....", 0));
        pushButtonShowGrid->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 \321\201\320\265\321\202\320\272\321\203", 0));
    } // retranslateUi

};

namespace Ui {
    class CreateTournamentOrdersDialog: public Ui_CreateTournamentOrdersDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATETOURNAMENTORDERSDIALOG_H
