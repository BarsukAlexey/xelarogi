/********************************************************************************
** Form generated from reading UI file 'dialogorderoftc.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGORDEROFTC_H
#define UI_DIALOGORDEROFTC_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogOrderOfTC
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButtonUP;
    QPushButton *pushButtonDown;
    QSpacerItem *verticalSpacer;
    QLabel *labelTitle;
    QTableView *tableView;

    void setupUi(QDialog *DialogOrderOfTC)
    {
        if (DialogOrderOfTC->objectName().isEmpty())
            DialogOrderOfTC->setObjectName(QStringLiteral("DialogOrderOfTC"));
        DialogOrderOfTC->resize(510, 345);
        gridLayout = new QGridLayout(DialogOrderOfTC);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        pushButtonUP = new QPushButton(DialogOrderOfTC);
        pushButtonUP->setObjectName(QStringLiteral("pushButtonUP"));

        verticalLayout->addWidget(pushButtonUP);

        pushButtonDown = new QPushButton(DialogOrderOfTC);
        pushButtonDown->setObjectName(QStringLiteral("pushButtonDown"));

        verticalLayout->addWidget(pushButtonDown);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout, 1, 1, 1, 1);

        labelTitle = new QLabel(DialogOrderOfTC);
        labelTitle->setObjectName(QStringLiteral("labelTitle"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        labelTitle->setFont(font);
        labelTitle->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelTitle, 0, 0, 1, 2);

        tableView = new QTableView(DialogOrderOfTC);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->horizontalHeader()->setStretchLastSection(true);

        gridLayout->addWidget(tableView, 1, 0, 1, 1);


        retranslateUi(DialogOrderOfTC);

        QMetaObject::connectSlotsByName(DialogOrderOfTC);
    } // setupUi

    void retranslateUi(QDialog *DialogOrderOfTC)
    {
        DialogOrderOfTC->setWindowTitle(QApplication::translate("DialogOrderOfTC", "Dialog", 0));
        pushButtonUP->setText(QApplication::translate("DialogOrderOfTC", "UP", 0));
        pushButtonDown->setText(QApplication::translate("DialogOrderOfTC", "DOWN", 0));
        labelTitle->setText(QApplication::translate("DialogOrderOfTC", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogOrderOfTC: public Ui_DialogOrderOfTC {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGORDEROFTC_H
