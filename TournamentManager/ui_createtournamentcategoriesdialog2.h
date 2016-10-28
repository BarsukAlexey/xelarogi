/********************************************************************************
** Form generated from reading UI file 'createtournamentcategoriesdialog2.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATETOURNAMENTCATEGORIESDIALOG2_H
#define UI_CREATETOURNAMENTCATEGORIESDIALOG2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CreateTournamentCategoriesDialog2
{
public:
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QTableView *tableView;
    QTableView *tableView_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonSave;
    QPushButton *pushButtonCancel;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *CreateTournamentCategoriesDialog2)
    {
        if (CreateTournamentCategoriesDialog2->objectName().isEmpty())
            CreateTournamentCategoriesDialog2->setObjectName(QStringLiteral("CreateTournamentCategoriesDialog2"));
        CreateTournamentCategoriesDialog2->resize(724, 514);
        verticalLayout = new QVBoxLayout(CreateTournamentCategoriesDialog2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        splitter = new QSplitter(CreateTournamentCategoriesDialog2);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        tableView = new QTableView(splitter);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setSortingEnabled(true);
        splitter->addWidget(tableView);
        tableView_2 = new QTableView(splitter);
        tableView_2->setObjectName(QStringLiteral("tableView_2"));
        tableView_2->setSortingEnabled(true);
        splitter->addWidget(tableView_2);

        verticalLayout->addWidget(splitter);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButtonSave = new QPushButton(CreateTournamentCategoriesDialog2);
        pushButtonSave->setObjectName(QStringLiteral("pushButtonSave"));

        horizontalLayout->addWidget(pushButtonSave);

        pushButtonCancel = new QPushButton(CreateTournamentCategoriesDialog2);
        pushButtonCancel->setObjectName(QStringLiteral("pushButtonCancel"));

        horizontalLayout->addWidget(pushButtonCancel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(CreateTournamentCategoriesDialog2);

        QMetaObject::connectSlotsByName(CreateTournamentCategoriesDialog2);
    } // setupUi

    void retranslateUi(QDialog *CreateTournamentCategoriesDialog2)
    {
        CreateTournamentCategoriesDialog2->setWindowTitle(QApplication::translate("CreateTournamentCategoriesDialog2", "Dialog", 0));
        pushButtonSave->setText(QApplication::translate("CreateTournamentCategoriesDialog2", "Save", 0));
        pushButtonCancel->setText(QApplication::translate("CreateTournamentCategoriesDialog2", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class CreateTournamentCategoriesDialog2: public Ui_CreateTournamentCategoriesDialog2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATETOURNAMENTCATEGORIESDIALOG2_H
