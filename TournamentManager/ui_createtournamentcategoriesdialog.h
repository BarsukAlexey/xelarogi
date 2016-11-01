/********************************************************************************
** Form generated from reading UI file 'createtournamentcategoriesdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATETOURNAMENTCATEGORIESDIALOG_H
#define UI_CREATETOURNAMENTCATEGORIESDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include "sqltablemanager.h"

QT_BEGIN_NAMESPACE

class Ui_CreateTournamentCategoriesDialog
{
public:
    QVBoxLayout *verticalLayout;
    SqlTableManager *managerSqlTable;
    QPushButton *pushButtonAddGroupOfCaterories;

    void setupUi(QDialog *CreateTournamentCategoriesDialog)
    {
        if (CreateTournamentCategoriesDialog->objectName().isEmpty())
            CreateTournamentCategoriesDialog->setObjectName(QStringLiteral("CreateTournamentCategoriesDialog"));
        CreateTournamentCategoriesDialog->setWindowModality(Qt::NonModal);
        CreateTournamentCategoriesDialog->resize(1069, 581);
        verticalLayout = new QVBoxLayout(CreateTournamentCategoriesDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        managerSqlTable = new SqlTableManager(CreateTournamentCategoriesDialog);
        managerSqlTable->setObjectName(QStringLiteral("managerSqlTable"));

        verticalLayout->addWidget(managerSqlTable);

        pushButtonAddGroupOfCaterories = new QPushButton(CreateTournamentCategoriesDialog);
        pushButtonAddGroupOfCaterories->setObjectName(QStringLiteral("pushButtonAddGroupOfCaterories"));

        verticalLayout->addWidget(pushButtonAddGroupOfCaterories);


        retranslateUi(CreateTournamentCategoriesDialog);

        QMetaObject::connectSlotsByName(CreateTournamentCategoriesDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateTournamentCategoriesDialog)
    {
        CreateTournamentCategoriesDialog->setWindowTitle(QApplication::translate("CreateTournamentCategoriesDialog", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265 \320\272\320\260\321\202\320\265\320\263\320\276\321\200\320\270\320\271 \320\264\320\273\321\217 \321\202\321\203\321\200\320\275\320\270\321\200\320\260", 0));
        pushButtonAddGroupOfCaterories->setText(QApplication::translate("CreateTournamentCategoriesDialog", "\320\224\320\276\320\261\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\263\321\200\321\203\320\277\320\277\321\213 \320\272\320\260\321\202\320\265\320\263\320\276\321\200\320\270\320\271 \321\202\321\203\321\200\320\275\320\270\321\200\320\260...", 0));
    } // retranslateUi

};

namespace Ui {
    class CreateTournamentCategoriesDialog: public Ui_CreateTournamentCategoriesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATETOURNAMENTCATEGORIESDIALOG_H
