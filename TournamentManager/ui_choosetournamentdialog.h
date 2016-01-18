/********************************************************************************
** Form generated from reading UI file 'choosetournamentdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSETOURNAMENTDIALOG_H
#define UI_CHOOSETOURNAMENTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ChooseTournamentDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QDateEdit *dateEdit;
    QPushButton *pushButton;
    QListWidget *listWidget;

    void setupUi(QDialog *ChooseTournamentDialog)
    {
        if (ChooseTournamentDialog->objectName().isEmpty())
            ChooseTournamentDialog->setObjectName(QStringLiteral("ChooseTournamentDialog"));
        ChooseTournamentDialog->resize(390, 318);
        gridLayout = new QGridLayout(ChooseTournamentDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(ChooseTournamentDialog);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineEdit = new QLineEdit(ChooseTournamentDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        dateEdit = new QDateEdit(ChooseTournamentDialog);
        dateEdit->setObjectName(QStringLiteral("dateEdit"));

        horizontalLayout->addWidget(dateEdit);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        pushButton = new QPushButton(ChooseTournamentDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 2, 0, 1, 1);

        listWidget = new QListWidget(ChooseTournamentDialog);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        gridLayout->addWidget(listWidget, 1, 0, 1, 1);


        retranslateUi(ChooseTournamentDialog);

        QMetaObject::connectSlotsByName(ChooseTournamentDialog);
    } // setupUi

    void retranslateUi(QDialog *ChooseTournamentDialog)
    {
        ChooseTournamentDialog->setWindowTitle(QApplication::translate("ChooseTournamentDialog", "Dialog", 0));
        label->setText(QApplication::translate("ChooseTournamentDialog", "\320\237\320\276\320\270\321\201\320\272", 0));
        pushButton->setText(QApplication::translate("ChooseTournamentDialog", "\320\237\320\265\321\200\320\265\320\271\321\202\320\270", 0));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("ChooseTournamentDialog", "\320\242\320\265\321\201\321\202\320\276\320\262\321\213\320\271 \321\202\321\203\321\200\320\275\320\270\321\200", 0));
        listWidget->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class ChooseTournamentDialog: public Ui_ChooseTournamentDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSETOURNAMENTDIALOG_H
