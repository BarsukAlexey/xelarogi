/********************************************************************************
** Form generated from reading UI file 'createtournamentdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATETOURNAMENTDIALOG_H
#define UI_CREATETOURNAMENTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CreateTournamentDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *nameLE;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *shortNameLE;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLabel *label_4;
    QDateEdit *startDate;
    QLabel *label_5;
    QDateEdit *endDate;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *CreateTournamentDialog)
    {
        if (CreateTournamentDialog->objectName().isEmpty())
            CreateTournamentDialog->setObjectName(QStringLiteral("CreateTournamentDialog"));
        CreateTournamentDialog->resize(353, 141);
        gridLayout = new QGridLayout(CreateTournamentDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(CreateTournamentDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        nameLE = new QLineEdit(CreateTournamentDialog);
        nameLE->setObjectName(QStringLiteral("nameLE"));

        horizontalLayout->addWidget(nameLE);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(CreateTournamentDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        shortNameLE = new QLineEdit(CreateTournamentDialog);
        shortNameLE->setObjectName(QStringLiteral("shortNameLE"));

        horizontalLayout_2->addWidget(shortNameLE);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(CreateTournamentDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        label_4 = new QLabel(CreateTournamentDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_3->addWidget(label_4);

        startDate = new QDateEdit(CreateTournamentDialog);
        startDate->setObjectName(QStringLiteral("startDate"));

        horizontalLayout_3->addWidget(startDate);

        label_5 = new QLabel(CreateTournamentDialog);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_3->addWidget(label_5);

        endDate = new QDateEdit(CreateTournamentDialog);
        endDate->setObjectName(QStringLiteral("endDate"));

        horizontalLayout_3->addWidget(endDate);


        verticalLayout->addLayout(horizontalLayout_3);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(CreateTournamentDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(CreateTournamentDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), CreateTournamentDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CreateTournamentDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(CreateTournamentDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateTournamentDialog)
    {
        CreateTournamentDialog->setWindowTitle(QApplication::translate("CreateTournamentDialog", "\320\241\320\276\320\267\320\264\320\260\320\275\320\270\320\265 \321\202\321\203\321\200\320\275\320\270\321\200\320\260", 0));
        label->setText(QApplication::translate("CreateTournamentDialog", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265  \321\202\321\203\321\200\320\275\320\270\321\200\320\260", 0));
        label_2->setText(QApplication::translate("CreateTournamentDialog", "\320\232\321\200\320\260\321\202\320\272\320\276\320\265 \320\276\320\261\320\276\320\267\320\275\320\260\321\207\320\265\320\275\320\270\320\265", 0));
        label_3->setText(QApplication::translate("CreateTournamentDialog", "\320\242\321\203\321\200\320\275\320\270\321\200 \320\261\321\203\320\264\320\265\321\202 \320\277\321\200\320\276\321\205\320\276\320\264\320\270\321\202\321\214", 0));
        label_4->setText(QApplication::translate("CreateTournamentDialog", "\321\201", 0));
        label_5->setText(QApplication::translate("CreateTournamentDialog", "\320\277\320\276", 0));
    } // retranslateUi

};

namespace Ui {
    class CreateTournamentDialog: public Ui_CreateTournamentDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATETOURNAMENTDIALOG_H
