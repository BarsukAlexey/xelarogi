/********************************************************************************
** Form generated from reading UI file 'handbookdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HANDBOOKDIALOG_H
#define UI_HANDBOOKDIALOG_H

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

QT_BEGIN_NAMESPACE

class Ui_HandbookDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnInsert;
    QPushButton *btnSave;
    QPushButton *btnRevert;
    QPushButton *btnExit;
    QLabel *label_3;

    void setupUi(QDialog *HandbookDialog)
    {
        if (HandbookDialog->objectName().isEmpty())
            HandbookDialog->setObjectName(QStringLiteral("HandbookDialog"));
        HandbookDialog->resize(872, 435);
        gridLayout = new QGridLayout(HandbookDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_2 = new QLabel(HandbookDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(HandbookDialog);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(18);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        tableView = new QTableView(HandbookDialog);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setContextMenuPolicy(Qt::CustomContextMenu);

        gridLayout->addWidget(tableView, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        btnInsert = new QPushButton(HandbookDialog);
        btnInsert->setObjectName(QStringLiteral("btnInsert"));

        horizontalLayout_2->addWidget(btnInsert);

        btnSave = new QPushButton(HandbookDialog);
        btnSave->setObjectName(QStringLiteral("btnSave"));

        horizontalLayout_2->addWidget(btnSave);

        btnRevert = new QPushButton(HandbookDialog);
        btnRevert->setObjectName(QStringLiteral("btnRevert"));

        horizontalLayout_2->addWidget(btnRevert);

        btnExit = new QPushButton(HandbookDialog);
        btnExit->setObjectName(QStringLiteral("btnExit"));

        horizontalLayout_2->addWidget(btnExit);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        label_3 = new QLabel(HandbookDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 4, 0, 1, 1);


        retranslateUi(HandbookDialog);

        QMetaObject::connectSlotsByName(HandbookDialog);
    } // setupUi

    void retranslateUi(QDialog *HandbookDialog)
    {
        HandbookDialog->setWindowTitle(QApplication::translate("HandbookDialog", "Dialog", 0));
        label_2->setText(QApplication::translate("HandbookDialog", "<a href=\"http://127.0.0.1:49255/viewer/frameset?__report=C%3A%5CUsers%5C\320\220\320\273\320\265\320\272\321\201\320\265\320\271%5Cworkspace%5CReports%5Ctest_report.rptdesign&__format=html&__svg=true&__locale=ru_RU&__timezone=W-SU&__masterpage=true&__rtl=false&__cubememsize=100&__resourceFolder=C%3A%5CUsers%5C\320\220\320\273\320\265\320\272\321\201\320\265\320\271%5Cworkspace%5CReports&998452581\"> \320\237\320\276\321\201\320\274\320\276\321\202\321\200\320\265\321\202\321\214 \321\202\320\265\321\201\321\202\320\276\320\262\321\213\320\271 \320\276\321\202\321\207\320\265\321\202 </a>", 0));
        label->setText(QApplication::translate("HandbookDialog", "\320\241\320\277\321\200\320\260\320\262\320\276\321\207\320\275\320\270\320\272", 0));
        btnInsert->setText(QApplication::translate("HandbookDialog", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\275\320\276\320\262\321\203\321\216 \320\267\320\260\320\277\320\270\321\201\321\214", 0));
        btnSave->setText(QApplication::translate("HandbookDialog", "\320\241\320\276\321\205\321\200\320\275\320\270\321\202\321\214 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217", 0));
        btnRevert->setText(QApplication::translate("HandbookDialog", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217", 0));
        btnExit->setText(QApplication::translate("HandbookDialog", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", 0));
        label_3->setText(QApplication::translate("HandbookDialog", "<a href=\"http://127.0.0.1:49255/viewer/frameset?__report=C%3A%5CUsers%5C\320\220\320\273\320\265\320\272\321\201\320\265\320\271%5Cworkspace%5CReports%5Ctest_report.rptdesign&__format=xlsx&__svg=true&__locale=ru_RU&__timezone=W-SU&__masterpage=true&__rtl=false&__cubememsize=100&__resourceFolder=C%3A%5CUsers%5C\320\220\320\273\320\265\320\272\321\201\320\265\320\271%5Cworkspace%5CReports&998452581\"> \320\237\320\276\320\273\321\203\321\207\320\270\321\202\321\214 \321\202\320\265\321\201\321\202\320\276\320\262\321\213\320\271 \320\276\321\202\321\207\320\265\321\202 \320\262 \321\204\320\276\321\200\320\274\320\260\321\202\320\265 excel </a>", 0));
    } // retranslateUi

};

namespace Ui {
    class HandbookDialog: public Ui_HandbookDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HANDBOOKDIALOG_H
