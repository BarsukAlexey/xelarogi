/********************************************************************************
** Form generated from reading UI file 'dialogchosedata.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCHOSEDATA_H
#define UI_DIALOGCHOSEDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogChoseData
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QComboBox *comboBox;
    QPushButton *pushButtonSave;
    QPushButton *pushButtonDelete;
    QPushButton *pushButtonSaveAs;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QTableWidget *tableWidget;
    QPushButton *pushButtonAddRow;
    QPushButton *pushButtonDeleteRow;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *DialogChoseData)
    {
        if (DialogChoseData->objectName().isEmpty())
            DialogChoseData->setObjectName(QStringLiteral("DialogChoseData"));
        DialogChoseData->resize(884, 606);
        gridLayout = new QGridLayout(DialogChoseData);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget = new QWidget(DialogChoseData);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox = new QGroupBox(widget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        gridLayout_2->addWidget(comboBox, 0, 0, 1, 1);

        pushButtonSave = new QPushButton(groupBox);
        pushButtonSave->setObjectName(QStringLiteral("pushButtonSave"));

        gridLayout_2->addWidget(pushButtonSave, 0, 2, 1, 1);

        pushButtonDelete = new QPushButton(groupBox);
        pushButtonDelete->setObjectName(QStringLiteral("pushButtonDelete"));

        gridLayout_2->addWidget(pushButtonDelete, 0, 4, 1, 1);

        pushButtonSaveAs = new QPushButton(groupBox);
        pushButtonSaveAs->setObjectName(QStringLiteral("pushButtonSaveAs"));

        gridLayout_2->addWidget(pushButtonSaveAs, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 5, 1, 1);


        horizontalLayout->addWidget(groupBox);


        gridLayout->addWidget(widget, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(DialogChoseData);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 1);

        groupBox_2 = new QGroupBox(DialogChoseData);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        tableWidget = new QTableWidget(groupBox_2);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

        gridLayout_3->addWidget(tableWidget, 0, 0, 1, 3);

        pushButtonAddRow = new QPushButton(groupBox_2);
        pushButtonAddRow->setObjectName(QStringLiteral("pushButtonAddRow"));

        gridLayout_3->addWidget(pushButtonAddRow, 1, 0, 1, 1);

        pushButtonDeleteRow = new QPushButton(groupBox_2);
        pushButtonDeleteRow->setObjectName(QStringLiteral("pushButtonDeleteRow"));

        gridLayout_3->addWidget(pushButtonDeleteRow, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 1, 2, 1, 1);


        gridLayout->addWidget(groupBox_2, 1, 0, 1, 1);


        retranslateUi(DialogChoseData);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogChoseData, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogChoseData, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogChoseData);
    } // setupUi

    void retranslateUi(QDialog *DialogChoseData)
    {
        DialogChoseData->setWindowTitle(QApplication::translate("DialogChoseData", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("DialogChoseData", "\320\222\321\213\320\261\320\276\321\200 \320\270 \321\203\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \321\210\320\260\320\261\320\273\320\276\320\275\320\260\320\274\320\270", 0));
        pushButtonSave->setText(QApplication::translate("DialogChoseData", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217 \320\262 \321\210\320\260\320\261\320\273\320\276\320\275\320\265", 0));
        pushButtonDelete->setText(QApplication::translate("DialogChoseData", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\210\320\260\320\261\320\273\320\276\320\275", 0));
        pushButtonSaveAs->setText(QApplication::translate("DialogChoseData", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\275\320\276\320\262\321\213\320\271 \321\210\320\260\320\261\320\273\320\276\320\275", 0));
        groupBox_2->setTitle(QApplication::translate("DialogChoseData", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \320\264\320\260\320\275\320\275\321\213\321\205 \321\210\320\260\320\261\320\273\320\276\320\275\320\275\320\260", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("DialogChoseData", "\320\224\320\260\320\275\320\275\321\213\320\265 \321\201\321\202\320\276\320\273\320\261\321\206\320\260", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("DialogChoseData", "\320\242\320\265\320\272\321\201\321\202 \320\264\320\273\321\217 \320\267\320\260\320\263\320\276\320\273\320\276\320\262\320\276\320\272\320\260 \321\201\321\202\320\276\320\273\320\261\321\206\320\260", 0));
        pushButtonAddRow->setText(QApplication::translate("DialogChoseData", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\201\321\202\321\200\320\276\320\272\321\203", 0));
        pushButtonDeleteRow->setText(QApplication::translate("DialogChoseData", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\201\321\202\321\200\320\276\320\272\321\203", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogChoseData: public Ui_DialogChoseData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCHOSEDATA_H
