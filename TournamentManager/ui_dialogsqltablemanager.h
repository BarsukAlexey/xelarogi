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
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include "sqltablemanager.h"

QT_BEGIN_NAMESPACE

class Ui_DialogSqlTableManager
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    SqlTableManager *sqlTableManager;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogSqlTableManager)
    {
        if (DialogSqlTableManager->objectName().isEmpty())
            DialogSqlTableManager->setObjectName(QStringLiteral("DialogSqlTableManager"));
        DialogSqlTableManager->resize(400, 300);
        verticalLayout = new QVBoxLayout(DialogSqlTableManager);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(DialogSqlTableManager);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        sqlTableManager = new SqlTableManager(DialogSqlTableManager);
        sqlTableManager->setObjectName(QStringLiteral("sqlTableManager"));

        verticalLayout->addWidget(sqlTableManager);

        buttonBox = new QDialogButtonBox(DialogSqlTableManager);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(DialogSqlTableManager);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogSqlTableManager, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogSqlTableManager, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogSqlTableManager);
    } // setupUi

    void retranslateUi(QDialog *DialogSqlTableManager)
    {
        DialogSqlTableManager->setWindowTitle(QApplication::translate("DialogSqlTableManager", "Dialog", 0));
        label->setText(QApplication::translate("DialogSqlTableManager", "\320\227\320\260\320\263\320\276\320\273\320\276\320\262\320\276\320\272", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogSqlTableManager: public Ui_DialogSqlTableManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSQLTABLEMANAGER_H
