/********************************************************************************
** Form generated from reading UI file 'formdipl.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMDIPL_H
#define UI_FORMDIPL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormDipl
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonAdd;
    QPushButton *pushButtonDelete;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_3;
    QGridLayout *gridLayout_3;
    QLabel *label_3;
    QPushButton *pushButtonPrint;
    QLabel *label_4;
    QLabel *label_6;
    QTableWidget *tableWidget;
    QWidget *widget_2;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_5;
    QLabel *label;
    QSpinBox *spinBoxWidth;
    QLabel *label_2;
    QSpinBox *spinBoxHeight;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_6;
    QPushButton *pushButtonNew;
    QPushButton *pushButtonSave;
    QPushButton *pushButton_3;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBoxPlace;
    QGridLayout *gridLayout_7;
    QLabel *label_5;
    QComboBox *comboBoxMaxPlace;
    QCheckBox *checkBoxAllGrids;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *radioButtonBadge;
    QRadioButton *radioButtonDiplom;

    void setupUi(QDialog *FormDipl)
    {
        if (FormDipl->objectName().isEmpty())
            FormDipl->setObjectName(QStringLiteral("FormDipl"));
        FormDipl->resize(1101, 581);
        gridLayout = new QGridLayout(FormDipl);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
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


        gridLayout->addWidget(widget, 3, 0, 1, 1);

        widget_3 = new QWidget(FormDipl);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        gridLayout_3 = new QGridLayout(widget_3);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_3 = new QLabel(widget_3);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_3->addWidget(label_3, 1, 0, 1, 1);

        pushButtonPrint = new QPushButton(widget_3);
        pushButtonPrint->setObjectName(QStringLiteral("pushButtonPrint"));

        gridLayout_3->addWidget(pushButtonPrint, 0, 0, 1, 1);

        label_4 = new QLabel(widget_3);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setWordWrap(true);

        gridLayout_3->addWidget(label_4, 2, 0, 1, 1);

        label_6 = new QLabel(widget_3);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_3->addWidget(label_6, 3, 0, 1, 1);


        gridLayout->addWidget(widget_3, 4, 0, 1, 1);

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
        tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);

        gridLayout->addWidget(tableWidget, 2, 0, 1, 1);

        widget_2 = new QWidget(FormDipl);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        gridLayout_2 = new QGridLayout(widget_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupBox_2 = new QGroupBox(widget_2);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_5 = new QGridLayout(groupBox_2);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_5->addWidget(label, 0, 0, 1, 1);

        spinBoxWidth = new QSpinBox(groupBox_2);
        spinBoxWidth->setObjectName(QStringLiteral("spinBoxWidth"));
        spinBoxWidth->setMinimum(1);
        spinBoxWidth->setMaximum(100500);
        spinBoxWidth->setValue(210);

        gridLayout_5->addWidget(spinBoxWidth, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_5->addWidget(label_2, 1, 0, 1, 1);

        spinBoxHeight = new QSpinBox(groupBox_2);
        spinBoxHeight->setObjectName(QStringLiteral("spinBoxHeight"));
        spinBoxHeight->setMinimum(1);
        spinBoxHeight->setMaximum(100500);
        spinBoxHeight->setValue(297);

        gridLayout_5->addWidget(spinBoxHeight, 1, 1, 1, 1);


        gridLayout_2->addWidget(groupBox_2, 0, 1, 1, 1);

        groupBox_3 = new QGroupBox(widget_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_6 = new QGridLayout(groupBox_3);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        pushButtonNew = new QPushButton(groupBox_3);
        pushButtonNew->setObjectName(QStringLiteral("pushButtonNew"));

        gridLayout_6->addWidget(pushButtonNew, 1, 0, 1, 1);

        pushButtonSave = new QPushButton(groupBox_3);
        pushButtonSave->setObjectName(QStringLiteral("pushButtonSave"));
        QPalette palette;
        QBrush brush(QColor(1, 115, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        pushButtonSave->setPalette(palette);

        gridLayout_6->addWidget(pushButtonSave, 1, 1, 1, 1);

        pushButton_3 = new QPushButton(groupBox_3);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout_6->addWidget(pushButton_3, 1, 2, 1, 1);

        comboBox = new QComboBox(groupBox_3);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout_6->addWidget(comboBox, 0, 0, 1, 3);


        gridLayout_2->addWidget(groupBox_3, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 4, 1, 1);

        groupBoxPlace = new QGroupBox(widget_2);
        groupBoxPlace->setObjectName(QStringLiteral("groupBoxPlace"));
        gridLayout_7 = new QGridLayout(groupBoxPlace);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        label_5 = new QLabel(groupBoxPlace);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_7->addWidget(label_5, 0, 0, 1, 1);

        comboBoxMaxPlace = new QComboBox(groupBoxPlace);
        comboBoxMaxPlace->setObjectName(QStringLiteral("comboBoxMaxPlace"));

        gridLayout_7->addWidget(comboBoxMaxPlace, 0, 1, 1, 1);

        checkBoxAllGrids = new QCheckBox(groupBoxPlace);
        checkBoxAllGrids->setObjectName(QStringLiteral("checkBoxAllGrids"));

        gridLayout_7->addWidget(checkBoxAllGrids, 1, 0, 1, 2);


        gridLayout_2->addWidget(groupBoxPlace, 0, 3, 1, 1);

        groupBox = new QGroupBox(widget_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout_3 = new QHBoxLayout(groupBox);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        radioButtonBadge = new QRadioButton(groupBox);
        radioButtonBadge->setObjectName(QStringLiteral("radioButtonBadge"));
        radioButtonBadge->setChecked(true);

        horizontalLayout_3->addWidget(radioButtonBadge);

        radioButtonDiplom = new QRadioButton(groupBox);
        radioButtonDiplom->setObjectName(QStringLiteral("radioButtonDiplom"));

        horizontalLayout_3->addWidget(radioButtonDiplom);


        gridLayout_2->addWidget(groupBox, 0, 2, 1, 1);


        gridLayout->addWidget(widget_2, 0, 0, 1, 1);


        retranslateUi(FormDipl);

        QMetaObject::connectSlotsByName(FormDipl);
    } // setupUi

    void retranslateUi(QDialog *FormDipl)
    {
        FormDipl->setWindowTitle(QApplication::translate("FormDipl", "Form", 0));
        pushButtonAdd->setText(QApplication::translate("FormDipl", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\201\321\202\321\200\320\276\320\272\321\203", 0));
        pushButtonDelete->setText(QApplication::translate("FormDipl", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\201\321\202\321\200\320\276\320\272\321\203", 0));
        label_3->setText(QApplication::translate("FormDipl", "* \320\237\321\200\320\270 \320\277\320\265\321\207\320\260\321\202\320\270 PDF \321\203\320\272\320\260\320\266\320\270\321\202\320\265 100% \320\274\320\260\321\201\321\210\321\202\320\260\320\261 (\320\261\320\265\320\267 \320\277\320\276\320\273\320\265\320\271, \320\276\321\202\321\201\321\202\321\203\320\277\320\276\320\262 \320\270 \321\202.\320\264.)", 0));
        pushButtonPrint->setText(QApplication::translate("FormDipl", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\320\272 PDF...", 0));
        label_4->setText(QApplication::translate("FormDipl", "<html><head/><body><p>** \320\225\321\201\320\273\320\270 \321\202\320\265\320\272\321\201\321\202 \320\261\321\203\320\264\320\265\321\202 \320\262\321\213\320\273\320\265\320\267\320\260\321\202\321\214 \320\267\320\260 \321\210\320\270\321\200\320\270\320\275\321\203 \320\276\321\202\320\262\320\265\320\264\321\221\320\275\320\275\320\276\320\271 \320\265\320\271 \321\201\321\202\321\200\320\276\320\272\320\270, \321\202\320\276 \321\200\320\260\320\267\320\274\320\265\321\200 \321\210\321\200\320\270\321\204\321\202\320\260 \320\264\320\273\321\217 \321\215\321\202\320\276\320\263\320\276 \321\202\320\265\320\272\321\201\321\202\320\260 \320\260\320\262\321\202\320\276\320\274\320\260\321\202\320\270\321\207\320\265\321\201\320\272\320\270 \321\203\320\274\320\265\320\275\321\214\321\210\320\270\321\202\321\201\321\217 \321\202\320\260\320\272, \321\207\321\202\320\276\320\261\321\213 \320\277\320\276\320\273\320\275\320\276\321\201\321\202\321\214\321\216 \320\277\320\276\320\274\320\265\321\201\321\202\320"
                        "\270\321\202\321\214\321\201\321\217 \320\275\320\260 \321\201\321\202\321\200\320\276\320\272\320\265</p></body></html>", 0));
        label_6->setText(QApplication::translate("FormDipl", "*** \320\237\320\265\321\200\320\265\320\264 \320\277\320\265\321\207\320\260\321\202\321\214\321\216 \320\261\320\265\320\271\320\264\320\266\320\270\320\272\320\276\320\262 \320\275\320\265\320\276\320\261\321\205\320\276\320\264\320\270\320\274\320\276 \321\201\320\263\320\265\320\275\320\265\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \321\202\321\203\321\200\320\275\320\270\321\200\320\275\321\213\320\265 \321\201\320\265\321\202\320\272\320\270", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("FormDipl", "\320\247\321\202\320\276 \320\277\320\270\321\201\320\260\321\202\321\214?", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("FormDipl", "\320\222\321\213\321\200\320\260\320\262\320\275\320\270\320\262\320\260\320\275\320\270\320\265", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("FormDipl", "\320\250\321\200\320\270\321\204\321\202", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("FormDipl", "\320\246\320\262\320\265\321\202", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("FormDipl", "\320\240\320\260\321\201\321\202\320\276\321\217\320\275\320\270\320\265 \320\276\321\202 \320\273\320\265\320\262\320\276\320\263\320\276 \320\272\321\200\320\260\321\217, \320\274\320\274", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("FormDipl", "\320\240\320\260\321\201\321\202\320\276\320\275\320\270\320\265 \320\276\321\202 \320\262\320\265\321\200\321\205\320\275\320\265\320\263\320\276 \320\272\321\200\320\260\321\217, \320\274\320\274", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("FormDipl", "\320\224\320\273\320\270\320\275\320\260 \321\201\321\202\321\200\320\276\320\272\320\270, \320\274\320\274", 0));
        groupBox_2->setTitle(QApplication::translate("FormDipl", "\320\233\320\270\321\201\321\202", 0));
        label->setText(QApplication::translate("FormDipl", "\320\250\320\270\321\200\320\270\320\275\320\260 \320\273\320\270\321\201\321\202\320\260 (\320\274\320\274)", 0));
        label_2->setText(QApplication::translate("FormDipl", "\320\222\321\213\321\201\320\276\321\202\320\260 \320\273\320\270\321\201\321\202\320\260 (\320\274\320\274)", 0));
        groupBox_3->setTitle(QApplication::translate("FormDipl", "\320\250\320\260\320\261\320\273\320\276\320\275", 0));
        pushButtonNew->setText(QApplication::translate("FormDipl", "\320\235\320\276\320\262\321\213\320\271", 0));
        pushButtonSave->setText(QApplication::translate("FormDipl", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0));
        pushButton_3->setText(QApplication::translate("FormDipl", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", 0));
        groupBoxPlace->setTitle(QApplication::translate("FormDipl", "\320\234\320\265\321\201\321\202\320\276", 0));
        label_5->setText(QApplication::translate("FormDipl", "\320\234\320\260\320\272\321\201. \320\274\320\265\321\201\321\202\320\276:", 0));
        checkBoxAllGrids->setText(QApplication::translate("FormDipl", "\320\237\320\265\321\207\320\260\321\202\320\260\321\202\321\214 \320\275\320\265 \320\264\320\276 \320\272\320\276\320\275\321\206\320\260 \320\267\320\260\320\277\320\276\320\273\320\275\320\265\320\275\320\275\321\213\320\265 \321\201\320\265\321\202\320\272\320\270", 0));
        groupBox->setTitle(QApplication::translate("FormDipl", "\320\242\320\270\320\277", 0));
        radioButtonBadge->setText(QApplication::translate("FormDipl", "\320\221\320\265\320\271\320\264\320\266\320\270\320\272\320\270\n"
"(\320\262\321\201\320\265 \321\201\320\277\320\276\321\200\321\202\321\201\320\274\320\265\320\275\321\213)", 0));
        radioButtonDiplom->setText(QApplication::translate("FormDipl", "\320\223\321\200\320\260\320\274\320\276\321\202\321\213", 0));
    } // retranslateUi

};

namespace Ui {
    class FormDipl: public Ui_FormDipl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMDIPL_H
