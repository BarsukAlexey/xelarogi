/********************************************************************************
** Form generated from reading UI file 'dialogschedulesettinglists.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSCHEDULESETTINGLISTS_H
#define UI_DIALOGSCHEDULESETTINGLISTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogScheduleSettingLists
{
public:
    QGridLayout *gridLayout;
    QTableView *tableView;
    QPushButton *pushButtonAddList;
    QTableWidget *tableWidget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogScheduleSettingLists)
    {
        if (DialogScheduleSettingLists->objectName().isEmpty())
            DialogScheduleSettingLists->setObjectName(QStringLiteral("DialogScheduleSettingLists"));
        DialogScheduleSettingLists->resize(914, 543);
        gridLayout = new QGridLayout(DialogScheduleSettingLists);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableView = new QTableView(DialogScheduleSettingLists);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setFocusPolicy(Qt::NoFocus);
        tableView->setSelectionMode(QAbstractItemView::NoSelection);

        gridLayout->addWidget(tableView, 1, 0, 1, 1);

        pushButtonAddList = new QPushButton(DialogScheduleSettingLists);
        pushButtonAddList->setObjectName(QStringLiteral("pushButtonAddList"));

        gridLayout->addWidget(pushButtonAddList, 0, 0, 1, 1);

        tableWidget = new QTableWidget(DialogScheduleSettingLists);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setFocusPolicy(Qt::NoFocus);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setSelectionMode(QAbstractItemView::NoSelection);

        gridLayout->addWidget(tableWidget, 1, 2, 1, 1);

        buttonBox = new QDialogButtonBox(DialogScheduleSettingLists);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 4);


        retranslateUi(DialogScheduleSettingLists);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogScheduleSettingLists, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogScheduleSettingLists, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogScheduleSettingLists);
    } // setupUi

    void retranslateUi(QDialog *DialogScheduleSettingLists)
    {
        DialogScheduleSettingLists->setWindowTitle(QApplication::translate("DialogScheduleSettingLists", "Dialog", 0));
        pushButtonAddList->setText(QApplication::translate("DialogScheduleSettingLists", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\275\320\276\320\262\321\213\320\271 \321\201\320\277\320\270\321\201\320\276\320\272...", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("DialogScheduleSettingLists", "\320\240\320\260\320\267\320\264\320\265\320\273", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("DialogScheduleSettingLists", "\320\222\320\276\320\267\321\200\320\260\321\201 \320\276\321\202", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("DialogScheduleSettingLists", "\320\222\320\276\320\267\320\264\320\260\321\201\321\202 \320\264\320\276", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("DialogScheduleSettingLists", "\320\241\320\277\320\270\321\201\320\276\320\272", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogScheduleSettingLists: public Ui_DialogScheduleSettingLists {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSCHEDULESETTINGLISTS_H
