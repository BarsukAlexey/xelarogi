/********************************************************************************
** Form generated from reading UI file 'dialogchangecategory.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCHANGECATEGORY_H
#define UI_DIALOGCHANGECATEGORY_H

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
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogChangeCategory
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QDialogButtonBox *buttonBox;
    QTableWidget *tableWidget;
    QPushButton *pushButtonShowGrid;

    void setupUi(QDialog *DialogChangeCategory)
    {
        if (DialogChangeCategory->objectName().isEmpty())
            DialogChangeCategory->setObjectName(QStringLiteral("DialogChangeCategory"));
        DialogChangeCategory->resize(754, 465);
        gridLayout = new QGridLayout(DialogChangeCategory);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(DialogChangeCategory);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(DialogChangeCategory);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 3, 0, 1, 1);

        tableWidget = new QTableWidget(DialogChangeCategory);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setVisible(false);

        gridLayout->addWidget(tableWidget, 1, 0, 1, 1);

        pushButtonShowGrid = new QPushButton(DialogChangeCategory);
        pushButtonShowGrid->setObjectName(QStringLiteral("pushButtonShowGrid"));

        gridLayout->addWidget(pushButtonShowGrid, 2, 0, 1, 1);


        retranslateUi(DialogChangeCategory);

        QMetaObject::connectSlotsByName(DialogChangeCategory);
    } // setupUi

    void retranslateUi(QDialog *DialogChangeCategory)
    {
        DialogChangeCategory->setWindowTitle(QApplication::translate("DialogChangeCategory", "Dialog", 0));
        label->setText(QApplication::translate("DialogChangeCategory", "TextLabel", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("DialogChangeCategory", "UID", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("DialogChangeCategory", "\320\235\320\260\320\270\320\274\320\265\320\275\320\276\320\262\320\260\320\275\320\270\320\265", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("DialogChangeCategory", "\320\240\320\260\320\267\320\264\320\265\320\273", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("DialogChangeCategory", "\320\222\320\265\321\201 \320\276\321\202 ", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("DialogChangeCategory", "\320\222\320\265\321\201 \320\264\320\276", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("DialogChangeCategory", "\320\232\320\276\320\273-\320\262\320\276 \321\207\320\265\320\273\320\276\320\262\320\265\320\272", 0));
        pushButtonShowGrid->setText(QApplication::translate("DialogChangeCategory", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 \321\201\320\265\321\202\320\272\321\203", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogChangeCategory: public Ui_DialogChangeCategory {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCHANGECATEGORY_H
