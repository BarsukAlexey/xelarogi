/********************************************************************************
** Form generated from reading UI file 'tournamentgriddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOURNAMENTGRIDDIALOG_H
#define UI_TOURNAMENTGRIDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "tournamentgridwidget.h"

QT_BEGIN_NAMESPACE

class Ui_TournamentGridDialog
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *pushButton_2;
    QTableWidget *tableWidget;
    QPushButton *pushButton;
    TournamentGridWidget *widget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *TournamentGridDialog)
    {
        if (TournamentGridDialog->objectName().isEmpty())
            TournamentGridDialog->setObjectName(QStringLiteral("TournamentGridDialog"));
        TournamentGridDialog->resize(858, 498);
        gridLayout = new QGridLayout(TournamentGridDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        splitter = new QSplitter(TournamentGridDialog);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        tableWidget = new QTableWidget(layoutWidget);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(tableWidget);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        splitter->addWidget(layoutWidget);
        widget = new TournamentGridWidget(splitter);
        widget->setObjectName(QStringLiteral("widget"));
        splitter->addWidget(widget);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(TournamentGridDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(TournamentGridDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), TournamentGridDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), TournamentGridDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(TournamentGridDialog);
    } // setupUi

    void retranslateUi(QDialog *TournamentGridDialog)
    {
        TournamentGridDialog->setWindowTitle(QApplication::translate("TournamentGridDialog", "Dialog", 0));
        label->setText(QApplication::translate("TournamentGridDialog", "\320\227\320\260\321\217\320\262\320\272\320\270 \320\275\320\260 \321\202\321\203\321\200\320\275\320\270\321\200", 0));
        pushButton_2->setText(QApplication::translate("TournamentGridDialog", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\202\320\265\321\201\321\202\320\276\320\262\321\203\321\216 \320\267\320\260\320\277\320\270\321\201\321\214", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("TournamentGridDialog", "\320\241\320\277\320\276\321\200\321\202\321\201\320\274\320\265\320\275", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("TournamentGridDialog", "\320\240\320\265\320\263\320\270\320\276\320\275", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("TournamentGridDialog", "\320\236\321\201\320\276\320\261\320\260\321\217 \320\263\321\200\321\203\320\277\320\277\320\260", 0));
        pushButton->setText(QApplication::translate("TournamentGridDialog", "\320\241\320\263\320\265\320\275\320\265\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \321\201\320\265\321\202\320\272\321\203", 0));
    } // retranslateUi

};

namespace Ui {
    class TournamentGridDialog: public Ui_TournamentGridDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOURNAMENTGRIDDIALOG_H
