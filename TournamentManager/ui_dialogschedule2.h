/********************************************************************************
** Form generated from reading UI file 'dialogschedule2.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSCHEDULE2_H
#define UI_DIALOGSCHEDULE2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include "dialogschedule2treewidget.h"

QT_BEGIN_NAMESPACE

class Ui_Dialogschedule2
{
public:
    QGridLayout *gridLayout_2;
    QSplitter *splitter;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpinBox *spinBoxRing;
    QLabel *label_3;
    QSpinBox *spinBoxRing_2;
    QLabel *labelContest;
    QLabel *label_2;
    QComboBox *comboBoxDay;
    Dialogschedule2TreeWidget *treeWidget;
    QTableWidget *tableWidget;

    void setupUi(QDialog *Dialogschedule2)
    {
        if (Dialogschedule2->objectName().isEmpty())
            Dialogschedule2->setObjectName(QStringLiteral("Dialogschedule2"));
        Dialogschedule2->resize(548, 335);
        gridLayout_2 = new QGridLayout(Dialogschedule2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        splitter = new QSplitter(Dialogschedule2);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        widget = new QWidget(splitter);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        spinBoxRing = new QSpinBox(widget);
        spinBoxRing->setObjectName(QStringLiteral("spinBoxRing"));
        spinBoxRing->setMinimum(1);
        spinBoxRing->setMaximum(228);

        gridLayout->addWidget(spinBoxRing, 1, 1, 1, 1);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        spinBoxRing_2 = new QSpinBox(widget);
        spinBoxRing_2->setObjectName(QStringLiteral("spinBoxRing_2"));
        spinBoxRing_2->setMinimum(120);
        spinBoxRing_2->setMaximum(100500);

        gridLayout->addWidget(spinBoxRing_2, 3, 1, 1, 1);

        labelContest = new QLabel(widget);
        labelContest->setObjectName(QStringLiteral("labelContest"));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        labelContest->setFont(font);
        labelContest->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelContest, 0, 0, 1, 2);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        comboBoxDay = new QComboBox(widget);
        comboBoxDay->setObjectName(QStringLiteral("comboBoxDay"));

        gridLayout->addWidget(comboBoxDay, 2, 1, 1, 1);

        treeWidget = new Dialogschedule2TreeWidget(widget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->header()->setVisible(false);

        gridLayout->addWidget(treeWidget, 4, 0, 1, 2);

        splitter->addWidget(widget);
        tableWidget = new QTableWidget(splitter);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        splitter->addWidget(tableWidget);
        tableWidget->horizontalHeader()->setVisible(false);

        gridLayout_2->addWidget(splitter, 0, 0, 1, 1);


        retranslateUi(Dialogschedule2);

        QMetaObject::connectSlotsByName(Dialogschedule2);
    } // setupUi

    void retranslateUi(QDialog *Dialogschedule2)
    {
        Dialogschedule2->setWindowTitle(QApplication::translate("Dialogschedule2", "Dialog", 0));
        label->setText(QApplication::translate("Dialogschedule2", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\277\320\273\320\276\321\211\320\260\320\264\320\276\320\272:", 0));
        label_3->setText(QApplication::translate("Dialogschedule2", "\320\227\320\260\320\264\320\265\321\200\320\266\320\272\320\260 \321\201\320\274\320\265\320\275\321\213 \320\277\320\260\321\200 (\320\262 \321\201\320\265\320\272\321\203\320\275\320\264\320\260\321\205)", 0));
        labelContest->setText(QApplication::translate("Dialogschedule2", "#", 0));
        label_2->setText(QApplication::translate("Dialogschedule2", "\320\224\320\265\320\275\321\214:", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialogschedule2: public Ui_Dialogschedule2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSCHEDULE2_H
