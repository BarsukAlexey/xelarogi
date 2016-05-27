/********************************************************************************
** Form generated from reading UI file 'formdipl.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMDIPL_H
#define UI_FORMDIPL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormDipl
{
public:
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonAdd;
    QPushButton *pushButtonDelete;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_2;
    QGridLayout *gridLayout_2;
    QSpinBox *spinBoxWidth;
    QSpinBox *spinBoxHeight;
    QLabel *label;
    QLabel *label_2;
    QWidget *widget_3;
    QGridLayout *gridLayout_3;
    QPushButton *pushButtonPrint;

    void setupUi(QWidget *FormDipl)
    {
        if (FormDipl->objectName().isEmpty())
            FormDipl->setObjectName(QStringLiteral("FormDipl"));
        FormDipl->resize(691, 569);
        gridLayout = new QGridLayout(FormDipl);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableWidget = new QTableWidget(FormDipl);
        if (tableWidget->columnCount() < 7)
            tableWidget->setColumnCount(7);
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
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);

        gridLayout->addWidget(tableWidget, 1, 0, 1, 1);

        widget = new QWidget(FormDipl);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButtonAdd = new QPushButton(widget);
        pushButtonAdd->setObjectName(QStringLiteral("pushButtonAdd"));

        horizontalLayout->addWidget(pushButtonAdd);

        pushButtonDelete = new QPushButton(widget);
        pushButtonDelete->setObjectName(QStringLiteral("pushButtonDelete"));

        horizontalLayout->addWidget(pushButtonDelete);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addWidget(widget, 2, 0, 1, 1);

        widget_2 = new QWidget(FormDipl);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        gridLayout_2 = new QGridLayout(widget_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        spinBoxWidth = new QSpinBox(widget_2);
        spinBoxWidth->setObjectName(QStringLiteral("spinBoxWidth"));
        spinBoxWidth->setMinimum(1);
        spinBoxWidth->setMaximum(100500);
        spinBoxWidth->setValue(210);

        gridLayout_2->addWidget(spinBoxWidth, 1, 0, 1, 1);

        spinBoxHeight = new QSpinBox(widget_2);
        spinBoxHeight->setObjectName(QStringLiteral("spinBoxHeight"));
        spinBoxHeight->setMinimum(1);
        spinBoxHeight->setMaximum(100500);
        spinBoxHeight->setValue(297);

        gridLayout_2->addWidget(spinBoxHeight, 3, 0, 1, 1);

        label = new QLabel(widget_2);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 2, 0, 1, 1);


        gridLayout->addWidget(widget_2, 0, 0, 1, 1);

        widget_3 = new QWidget(FormDipl);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        gridLayout_3 = new QGridLayout(widget_3);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        pushButtonPrint = new QPushButton(widget_3);
        pushButtonPrint->setObjectName(QStringLiteral("pushButtonPrint"));

        gridLayout_3->addWidget(pushButtonPrint, 0, 0, 1, 1);


        gridLayout->addWidget(widget_3, 3, 0, 1, 1);


        retranslateUi(FormDipl);

        QMetaObject::connectSlotsByName(FormDipl);
    } // setupUi

    void retranslateUi(QWidget *FormDipl)
    {
        FormDipl->setWindowTitle(QApplication::translate("FormDipl", "Form", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("FormDipl", "\320\247\321\202\320\276 \320\277\320\270\321\201\320\260\321\202\321\214?", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("FormDipl", "\320\222\321\213\321\200\320\260\320\262\320\275\320\270\320\262\320\260\320\275\320\270\320\265", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("FormDipl", "\320\250\321\200\320\270\321\204\321\202 (\320\275\320\265 \320\270\320\267\320\274\320\265\320\275\321\217\321\202\321\214 \321\200\320\260\320\267\320\274\320\265\321\200 \321\210\321\200\320\270\321\204\321\202\320\260)", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("FormDipl", "\320\240\320\260\320\267\320\274\320\265\321\200 \321\210\321\200\320\270\321\204\321\202\320\260, \320\274\320\274", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("FormDipl", "\320\240\320\260\321\201\321\202\320\276\321\217\320\275\320\270\320\265 \320\276\321\202 \320\273\320\265\320\262\320\276\320\263\320\276 \320\272\321\200\320\260\321\217, \320\274\320\274", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("FormDipl", "\320\240\320\260\321\201\321\202\320\276\320\275\320\270\320\265 \320\276\321\202 \320\262\320\265\321\200\321\205\320\275\320\265\320\263\320\276 \320\272\321\200\320\260\321\217, \320\274\320\274", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("FormDipl", "\320\224\320\273\320\270\320\275\320\260 \321\201\321\202\321\200\320\276\320\272\320\270, \320\274\320\274", 0));
        pushButtonAdd->setText(QApplication::translate("FormDipl", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\201\321\202\321\200\320\276\320\272\321\203", 0));
        pushButtonDelete->setText(QApplication::translate("FormDipl", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\201\321\202\321\200\320\276\320\272\321\203", 0));
        label->setText(QApplication::translate("FormDipl", "\320\250\320\270\321\200\320\270\320\275\320\260 \320\273\320\270\321\201\321\202\320\260", 0));
        label_2->setText(QApplication::translate("FormDipl", "\320\222\321\213\321\201\320\276\321\202\320\260 \320\273\320\270\321\201\321\202\320\260", 0));
        pushButtonPrint->setText(QApplication::translate("FormDipl", "\320\237\320\265\321\207\320\260\321\202\321\214...", 0));
    } // retranslateUi

};

namespace Ui {
    class FormDipl: public Ui_FormDipl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMDIPL_H
