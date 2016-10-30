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

class Ui_CreateTournamentCategoriesDialog2
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
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonInsert;

    void setupUi(QDialog *CreateTournamentCategoriesDialog2)
    {
        if (CreateTournamentCategoriesDialog2->objectName().isEmpty())
            CreateTournamentCategoriesDialog2->setObjectName(QStringLiteral("CreateTournamentCategoriesDialog2"));
        CreateTournamentCategoriesDialog2->resize(724, 514);
        gridLayout = new QGridLayout(CreateTournamentCategoriesDialog2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        splitter = new QSplitter(CreateTournamentCategoriesDialog2);
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
        pushButtonSave = new QPushButton(CreateTournamentCategoriesDialog2);
        pushButtonSave->setObjectName(QStringLiteral("pushButtonSave"));

        horizontalLayout->addWidget(pushButtonSave);

        pushButtonCancel = new QPushButton(CreateTournamentCategoriesDialog2);
        pushButtonCancel->setObjectName(QStringLiteral("pushButtonCancel"));

        horizontalLayout->addWidget(pushButtonCancel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButtonInsert = new QPushButton(CreateTournamentCategoriesDialog2);
        pushButtonInsert->setObjectName(QStringLiteral("pushButtonInsert"));

        horizontalLayout->addWidget(pushButtonInsert);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(CreateTournamentCategoriesDialog2);

        QMetaObject::connectSlotsByName(CreateTournamentCategoriesDialog2);
    } // setupUi

    void retranslateUi(QDialog *CreateTournamentCategoriesDialog2)
    {
        CreateTournamentCategoriesDialog2->setWindowTitle(QApplication::translate("CreateTournamentCategoriesDialog2", "Dialog", 0));
        pushButtonSave->setText(QApplication::translate("CreateTournamentCategoriesDialog2", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217", 0));
        pushButtonCancel->setText(QApplication::translate("CreateTournamentCategoriesDialog2", "\320\236\321\202\320\272\320\260\321\202\320\270\321\202\321\214 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217", 0));
        pushButtonInsert->setText(QApplication::translate("CreateTournamentCategoriesDialog2", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\275\320\276\320\262\321\203\321\216 \320\267\320\260\320\277\320\270\321\201\321\214", 0));
    } // retranslateUi

};

namespace Ui {
    class CreateTournamentCategoriesDialog2: public Ui_CreateTournamentCategoriesDialog2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATETOURNAMENTCATEGORIESDIALOG2_H
