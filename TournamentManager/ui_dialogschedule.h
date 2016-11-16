/********************************************************************************
** Form generated from reading UI file 'dialogschedule.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSCHEDULE_H
#define UI_DIALOGSCHEDULE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogSchedule
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QSpinBox *spinBoxDelay;
    QLabel *label_3;
    QSpinBox *spinBoxRing;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBoxList;
    QPushButton *pushButtonLists;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QTableWidget *tableWidget;
    QPushButton *pushButtonSaveExcel;

    void setupUi(QDialog *DialogSchedule)
    {
        if (DialogSchedule->objectName().isEmpty())
            DialogSchedule->setObjectName(QStringLiteral("DialogSchedule"));
        DialogSchedule->resize(1252, 392);
        gridLayout = new QGridLayout(DialogSchedule);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox_5 = new QGroupBox(DialogSchedule);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        gridLayout_2 = new QGridLayout(groupBox_5);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label = new QLabel(groupBox_5);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        spinBoxDelay = new QSpinBox(groupBox_5);
        spinBoxDelay->setObjectName(QStringLiteral("spinBoxDelay"));
        spinBoxDelay->setMaximum(100500);
        spinBoxDelay->setValue(120);

        gridLayout_2->addWidget(spinBoxDelay, 0, 3, 1, 1);

        label_3 = new QLabel(groupBox_5);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3->setWordWrap(true);

        gridLayout_2->addWidget(label_3, 0, 2, 1, 1);

        spinBoxRing = new QSpinBox(groupBox_5);
        spinBoxRing->setObjectName(QStringLiteral("spinBoxRing"));
        spinBoxRing->setMinimum(1);
        spinBoxRing->setMaximum(100500);

        gridLayout_2->addWidget(spinBoxRing, 0, 1, 1, 1);


        gridLayout->addWidget(groupBox_5, 3, 1, 1, 1);

        groupBox = new QGroupBox(DialogSchedule);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        comboBoxList = new QComboBox(groupBox);
        comboBoxList->setObjectName(QStringLiteral("comboBoxList"));

        horizontalLayout->addWidget(comboBoxList);

        pushButtonLists = new QPushButton(groupBox);
        pushButtonLists->setObjectName(QStringLiteral("pushButtonLists"));

        horizontalLayout->addWidget(pushButtonLists);


        gridLayout->addWidget(groupBox, 0, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 3, 2, 1, 3);

        tableWidget = new QTableWidget(DialogSchedule);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidget->verticalHeader()->setVisible(false);

        gridLayout->addWidget(tableWidget, 1, 0, 1, 5);

        pushButtonSaveExcel = new QPushButton(DialogSchedule);
        pushButtonSaveExcel->setObjectName(QStringLiteral("pushButtonSaveExcel"));

        gridLayout->addWidget(pushButtonSaveExcel, 0, 3, 1, 1);


        retranslateUi(DialogSchedule);

        QMetaObject::connectSlotsByName(DialogSchedule);
    } // setupUi

    void retranslateUi(QDialog *DialogSchedule)
    {
        DialogSchedule->setWindowTitle(QApplication::translate("DialogSchedule", "Dialog", 0));
        groupBox_5->setTitle(QApplication::translate("DialogSchedule", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213", 0));
        label->setText(QApplication::translate("DialogSchedule", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\200\320\270\320\275\320\263\320\276\320\262", 0));
        label_3->setText(QApplication::translate("DialogSchedule", "\320\227\320\260\320\264\320\265\321\200\320\266\320\272\320\260 \320\277\321\200\320\270 \321\201\320\274\320\265\320\275\320\265 \320\277\320\260\321\200 \320\275\320\260 \321\200\320\270\320\275\320\263\320\265 (\320\262 \321\201\320\265\320\272\321\203\320\275\320\264\320\260\321\205)", 0));
        groupBox->setTitle(QString());
        pushButtonLists->setText(QApplication::translate("DialogSchedule", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \321\201\320\277\320\270\321\201\320\272\320\276\320\262...", 0));
        pushButtonSaveExcel->setText(QApplication::translate("DialogSchedule", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\262 Excel...", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogSchedule: public Ui_DialogSchedule {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSCHEDULE_H
