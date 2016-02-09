/********************************************************************************
** Form generated from reading UI file 'createtournamentordersdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CreateTournamentOrdersDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnInsert;
    QPushButton *loadBtn;
    QPushButton *btnSave;
    QPushButton *btnRevert;
    QPushButton *btnExit;

    void setupUi(QDialog *CreateTournamentOrdersDialog)
    {
        if (CreateTournamentOrdersDialog->objectName().isEmpty())
            CreateTournamentOrdersDialog->setObjectName(QStringLiteral("CreateTournamentOrdersDialog"));
        CreateTournamentOrdersDialog->resize(801, 423);
        gridLayout = new QGridLayout(CreateTournamentOrdersDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(CreateTournamentOrdersDialog);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(18);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new QTableView(CreateTournamentOrdersDialog);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setContextMenuPolicy(Qt::CustomContextMenu);
        tableView->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(tableView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        btnInsert = new QPushButton(CreateTournamentOrdersDialog);
        btnInsert->setObjectName(QStringLiteral("btnInsert"));

        horizontalLayout_2->addWidget(btnInsert);

        loadBtn = new QPushButton(CreateTournamentOrdersDialog);
        loadBtn->setObjectName(QStringLiteral("loadBtn"));

        horizontalLayout_2->addWidget(loadBtn);

        btnSave = new QPushButton(CreateTournamentOrdersDialog);
        btnSave->setObjectName(QStringLiteral("btnSave"));

        horizontalLayout_2->addWidget(btnSave);

        btnRevert = new QPushButton(CreateTournamentOrdersDialog);
        btnRevert->setObjectName(QStringLiteral("btnRevert"));

        horizontalLayout_2->addWidget(btnRevert);

        btnExit = new QPushButton(CreateTournamentOrdersDialog);
        btnExit->setObjectName(QStringLiteral("btnExit"));

        horizontalLayout_2->addWidget(btnExit);


        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(CreateTournamentOrdersDialog);

        QMetaObject::connectSlotsByName(CreateTournamentOrdersDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateTournamentOrdersDialog)
    {
        CreateTournamentOrdersDialog->setWindowTitle(QApplication::translate("CreateTournamentOrdersDialog", "\320\224\320\276\320\261\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\267\320\260\321\217\320\262\320\276\320\272 \320\272 \321\202\321\203\321\200\320\275\320\270\321\200\321\203", 0));
        label->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\241\320\277\321\200\320\260\320\262\320\276\321\207\320\275\320\270\320\272", 0));
        btnInsert->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\275\320\276\320\262\321\203\321\216 \320\267\320\260\320\277\320\270\321\201\321\214", 0));
        loadBtn->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\270\320\267 excel", 0));
        btnSave->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\241\320\276\321\205\321\200\320\275\320\270\321\202\321\214 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217", 0));
        btnRevert->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217", 0));
        btnExit->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", 0));
    } // retranslateUi

};

namespace Ui {
    class CreateTournamentOrdersDialog: public Ui_CreateTournamentOrdersDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATETOURNAMENTORDERSDIALOG_H
