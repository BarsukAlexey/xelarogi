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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CreateTournamentDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_11;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *nameLE;
    QLineEdit *mainJudgeLE;
    QLineEdit *mainSecretaryLE;
    QLineEdit *mainJudgeHelperLE;
    QLineEdit *lineEditHost;
    QLineEdit *lineEdit_TextDataRange;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLabel *label_4;
    QDateEdit *startDate;
    QLabel *label_5;
    QDateEdit *endDate;
    QSpacerItem *horizontalSpacer;
    QLabel *label_10;
    QDateEdit *weightDate;
    QDialogButtonBox *buttonBox;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *CreateTournamentDialog)
    {
        if (CreateTournamentDialog->objectName().isEmpty())
            CreateTournamentDialog->setObjectName(QStringLiteral("CreateTournamentDialog"));
        CreateTournamentDialog->resize(667, 264);
        gridLayout = new QGridLayout(CreateTournamentDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(CreateTournamentDialog);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_2->addWidget(label);

        label_6 = new QLabel(CreateTournamentDialog);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout_2->addWidget(label_6);

        label_7 = new QLabel(CreateTournamentDialog);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout_2->addWidget(label_7);

        label_8 = new QLabel(CreateTournamentDialog);
        label_8->setObjectName(QStringLiteral("label_8"));

        verticalLayout_2->addWidget(label_8);

        label_9 = new QLabel(CreateTournamentDialog);
        label_9->setObjectName(QStringLiteral("label_9"));

        verticalLayout_2->addWidget(label_9);

        label_11 = new QLabel(CreateTournamentDialog);
        label_11->setObjectName(QStringLiteral("label_11"));

        verticalLayout_2->addWidget(label_11);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        nameLE = new QLineEdit(CreateTournamentDialog);
        nameLE->setObjectName(QStringLiteral("nameLE"));

        verticalLayout_3->addWidget(nameLE);

        mainJudgeLE = new QLineEdit(CreateTournamentDialog);
        mainJudgeLE->setObjectName(QStringLiteral("mainJudgeLE"));

        verticalLayout_3->addWidget(mainJudgeLE);

        mainSecretaryLE = new QLineEdit(CreateTournamentDialog);
        mainSecretaryLE->setObjectName(QStringLiteral("mainSecretaryLE"));

        verticalLayout_3->addWidget(mainSecretaryLE);

        mainJudgeHelperLE = new QLineEdit(CreateTournamentDialog);
        mainJudgeHelperLE->setObjectName(QStringLiteral("mainJudgeHelperLE"));

        verticalLayout_3->addWidget(mainJudgeHelperLE);

        lineEditHost = new QLineEdit(CreateTournamentDialog);
        lineEditHost->setObjectName(QStringLiteral("lineEditHost"));

        verticalLayout_3->addWidget(lineEditHost);

        lineEdit_TextDataRange = new QLineEdit(CreateTournamentDialog);
        lineEdit_TextDataRange->setObjectName(QStringLiteral("lineEdit_TextDataRange"));

        verticalLayout_3->addWidget(lineEdit_TextDataRange);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout->addLayout(horizontalLayout);

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
        startDate->setCalendarPopup(true);

        horizontalLayout_3->addWidget(startDate);

        label_5 = new QLabel(CreateTournamentDialog);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_3->addWidget(label_5);

        endDate = new QDateEdit(CreateTournamentDialog);
        endDate->setObjectName(QStringLiteral("endDate"));
        endDate->setCalendarPopup(true);

        horizontalLayout_3->addWidget(endDate);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        label_10 = new QLabel(CreateTournamentDialog);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_3->addWidget(label_10);

        weightDate = new QDateEdit(CreateTournamentDialog);
        weightDate->setObjectName(QStringLiteral("weightDate"));
        weightDate->setCalendarPopup(true);

        horizontalLayout_3->addWidget(weightDate);


        verticalLayout->addLayout(horizontalLayout_3);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(CreateTournamentDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);


        retranslateUi(CreateTournamentDialog);

        QMetaObject::connectSlotsByName(CreateTournamentDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateTournamentDialog)
    {
        CreateTournamentDialog->setWindowTitle(QApplication::translate("CreateTournamentDialog", "\320\241\320\276\320\267\320\264\320\260\320\275\320\270\320\265 \321\202\321\203\321\200\320\275\320\270\321\200\320\260", 0));
        label->setText(QApplication::translate("CreateTournamentDialog", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265  \321\202\321\203\321\200\320\275\320\270\321\200\320\260", 0));
        label_6->setText(QApplication::translate("CreateTournamentDialog", "\320\223\320\273\320\260\320\262\320\275\321\213\320\271 \321\201\321\203\320\264\321\214\321\217", 0));
        label_7->setText(QApplication::translate("CreateTournamentDialog", "\320\223\320\273\320\260\320\262\320\275\321\213\320\271 \321\201\320\265\320\272\321\200\320\265\321\202\320\260\321\200\321\214", 0));
        label_8->setText(QApplication::translate("CreateTournamentDialog", "\320\227\320\260\320\274. \320\263\320\273\320\260\320\262\320\275\320\276\320\263\320\276 \321\201\321\203\320\264\321\214\320\270", 0));
        label_9->setText(QApplication::translate("CreateTournamentDialog", "\320\234\320\265\321\201\321\202\320\276 \320\277\321\200\320\276\320\262\320\265\320\264\320\265\320\275\320\270\321\217", 0));
        label_11->setText(QApplication::translate("CreateTournamentDialog", "\320\222\321\200\320\265\320\274\321\217 \320\277\321\200\320\276\320\262\320\265\320\264\320\265\320\275\320\270\321\217 (\320\275\320\260\320\277\321\200, 24-25 \320\274\320\260\321\217 2016 \320\263\320\276\320\264\320\260)", 0));
        label_3->setText(QApplication::translate("CreateTournamentDialog", "\320\242\321\203\321\200\320\275\320\270\321\200 \320\261\321\203\320\264\320\265\321\202 \320\277\321\200\320\276\321\205\320\276\320\264\320\270\321\202\321\214", 0));
        label_4->setText(QApplication::translate("CreateTournamentDialog", "\321\201", 0));
        label_5->setText(QApplication::translate("CreateTournamentDialog", "\320\277\320\276", 0));
        label_10->setText(QApplication::translate("CreateTournamentDialog", "\320\224\320\260\321\202\320\260 \320\262\320\267\320\262\320\265\321\210\320\270\320\262\320\260\320\275\320\270\321\217:", 0));
    } // retranslateUi

};

namespace Ui {
    class CreateTournamentDialog: public Ui_CreateTournamentDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATETOURNAMENTDIALOG_H
