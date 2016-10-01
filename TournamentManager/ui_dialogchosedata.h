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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogChoseData
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_Rows;
    QGridLayout *gridLayout_3;
    QTableWidget *tableWidget;
    QPushButton *pushButtonAddRow;
    QPushButton *pushButtonDeleteRow;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QComboBox *comboBox;
    QPushButton *pushButtonSave;
    QPushButton *pushButtonDelete;
    QPushButton *pushButtonSaveAs;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBoxTitle;
    QGridLayout *gridLayout_4;
    QLabel *label;
    QLineEdit *lineEditTitle;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_6;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_5;
    QCheckBox *checkBoxMainSecretary;
    QCheckBox *checkBoxAssociateMainJudge;
    QCheckBox *checkBoxMainJudge;
    QLineEdit *lineEditTitleAssociateMainJudge;
    QLineEdit *lineEditTitleMainSecretary;
    QLineEdit *lineEditTitleMainJudge;
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_7;
    QSpacerItem *horizontalSpacer_3;
    QComboBox *comboBoxMaxPlace;

    void setupUi(QDialog *DialogChoseData)
    {
        if (DialogChoseData->objectName().isEmpty())
            DialogChoseData->setObjectName(QStringLiteral("DialogChoseData"));
        DialogChoseData->resize(987, 853);
        gridLayout = new QGridLayout(DialogChoseData);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox_Rows = new QGroupBox(DialogChoseData);
        groupBox_Rows->setObjectName(QStringLiteral("groupBox_Rows"));
        groupBox_Rows->setEnabled(true);
        gridLayout_3 = new QGridLayout(groupBox_Rows);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        tableWidget = new QTableWidget(groupBox_Rows);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

        gridLayout_3->addWidget(tableWidget, 0, 0, 1, 3);

        pushButtonAddRow = new QPushButton(groupBox_Rows);
        pushButtonAddRow->setObjectName(QStringLiteral("pushButtonAddRow"));

        gridLayout_3->addWidget(pushButtonAddRow, 1, 0, 1, 1);

        pushButtonDeleteRow = new QPushButton(groupBox_Rows);
        pushButtonDeleteRow->setObjectName(QStringLiteral("pushButtonDeleteRow"));

        gridLayout_3->addWidget(pushButtonDeleteRow, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 1, 2, 1, 1);


        gridLayout->addWidget(groupBox_Rows, 2, 0, 1, 1);

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
        QPalette palette;
        QBrush brush(QColor(1, 115, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        pushButtonSave->setPalette(palette);

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

        groupBoxTitle = new QGroupBox(DialogChoseData);
        groupBoxTitle->setObjectName(QStringLiteral("groupBoxTitle"));
        gridLayout_4 = new QGridLayout(groupBoxTitle);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        label = new QLabel(groupBoxTitle);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_4->addWidget(label, 0, 0, 1, 1);

        lineEditTitle = new QLineEdit(groupBoxTitle);
        lineEditTitle->setObjectName(QStringLiteral("lineEditTitle"));

        gridLayout_4->addWidget(lineEditTitle, 0, 1, 1, 1);


        gridLayout->addWidget(groupBoxTitle, 1, 0, 1, 1);

        groupBox_2 = new QGroupBox(DialogChoseData);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_6 = new QGridLayout(groupBox_2);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        scrollArea = new QScrollArea(groupBox_2);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 947, 202));
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_6->addWidget(scrollArea, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_2, 5, 0, 1, 1);

        groupBox_4 = new QGroupBox(DialogChoseData);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        gridLayout_5 = new QGridLayout(groupBox_4);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        checkBoxMainSecretary = new QCheckBox(groupBox_4);
        checkBoxMainSecretary->setObjectName(QStringLiteral("checkBoxMainSecretary"));
        checkBoxMainSecretary->setChecked(true);

        gridLayout_5->addWidget(checkBoxMainSecretary, 1, 0, 1, 1);

        checkBoxAssociateMainJudge = new QCheckBox(groupBox_4);
        checkBoxAssociateMainJudge->setObjectName(QStringLiteral("checkBoxAssociateMainJudge"));
        checkBoxAssociateMainJudge->setChecked(true);

        gridLayout_5->addWidget(checkBoxAssociateMainJudge, 2, 0, 1, 1);

        checkBoxMainJudge = new QCheckBox(groupBox_4);
        checkBoxMainJudge->setObjectName(QStringLiteral("checkBoxMainJudge"));
        checkBoxMainJudge->setChecked(true);

        gridLayout_5->addWidget(checkBoxMainJudge, 0, 0, 1, 1);

        lineEditTitleAssociateMainJudge = new QLineEdit(groupBox_4);
        lineEditTitleAssociateMainJudge->setObjectName(QStringLiteral("lineEditTitleAssociateMainJudge"));

        gridLayout_5->addWidget(lineEditTitleAssociateMainJudge, 2, 1, 1, 1);

        lineEditTitleMainSecretary = new QLineEdit(groupBox_4);
        lineEditTitleMainSecretary->setObjectName(QStringLiteral("lineEditTitleMainSecretary"));

        gridLayout_5->addWidget(lineEditTitleMainSecretary, 1, 1, 1, 1);

        lineEditTitleMainJudge = new QLineEdit(groupBox_4);
        lineEditTitleMainJudge->setObjectName(QStringLiteral("lineEditTitleMainJudge"));

        gridLayout_5->addWidget(lineEditTitleMainJudge, 0, 1, 1, 1);


        gridLayout->addWidget(groupBox_4, 4, 0, 1, 1);

        buttonBox = new QDialogButtonBox(DialogChoseData);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 6, 0, 1, 1);

        groupBox_3 = new QGroupBox(DialogChoseData);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_7 = new QGridLayout(groupBox_3);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_3, 0, 1, 1, 1);

        comboBoxMaxPlace = new QComboBox(groupBox_3);
        comboBoxMaxPlace->setObjectName(QStringLiteral("comboBoxMaxPlace"));

        gridLayout_7->addWidget(comboBoxMaxPlace, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_3, 3, 0, 1, 1);

        QWidget::setTabOrder(comboBox, pushButtonSaveAs);
        QWidget::setTabOrder(pushButtonSaveAs, pushButtonSave);
        QWidget::setTabOrder(pushButtonSave, pushButtonDelete);
        QWidget::setTabOrder(pushButtonDelete, lineEditTitle);
        QWidget::setTabOrder(lineEditTitle, tableWidget);
        QWidget::setTabOrder(tableWidget, pushButtonAddRow);
        QWidget::setTabOrder(pushButtonAddRow, pushButtonDeleteRow);
        QWidget::setTabOrder(pushButtonDeleteRow, checkBoxMainJudge);
        QWidget::setTabOrder(checkBoxMainJudge, lineEditTitleMainJudge);
        QWidget::setTabOrder(lineEditTitleMainJudge, checkBoxMainSecretary);
        QWidget::setTabOrder(checkBoxMainSecretary, lineEditTitleMainSecretary);
        QWidget::setTabOrder(lineEditTitleMainSecretary, checkBoxAssociateMainJudge);
        QWidget::setTabOrder(checkBoxAssociateMainJudge, lineEditTitleAssociateMainJudge);

        retranslateUi(DialogChoseData);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogChoseData, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogChoseData, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogChoseData);
    } // setupUi

    void retranslateUi(QDialog *DialogChoseData)
    {
        DialogChoseData->setWindowTitle(QApplication::translate("DialogChoseData", "Dialog", 0));
        groupBox_Rows->setTitle(QApplication::translate("DialogChoseData", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \320\264\320\260\320\275\320\275\321\213\321\205 \321\202\320\260\320\261\320\273\320\270\321\206\321\213 (\321\201\320\265\321\202\320\276\320\272)", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("DialogChoseData", "\320\242\320\270\320\277 \320\264\320\260\320\275\320\275\321\213\321\205 \321\201\321\202\320\276\320\273\320\261\321\206\320\260", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("DialogChoseData", "\320\242\320\265\320\272\321\201\321\202 \320\264\320\273\321\217 \320\267\320\260\320\263\320\276\320\273\320\276\320\262\320\276\320\272\320\260 \321\201\321\202\320\276\320\273\320\261\321\206\320\260 (\320\264\320\273\321\217 \321\201\320\265\321\202\320\276\320\272 \320\274\320\276\320\266\320\275\320\276 \320\275\320\270\321\207\320\265\320\263\320\276 \320\275\320\265 \321\203\320\272\320\260\320\267\321\213\320\262\320\260\321\202\321\214)", 0));
        pushButtonAddRow->setText(QApplication::translate("DialogChoseData", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\201\321\202\321\200\320\276\320\272\321\203", 0));
        pushButtonDeleteRow->setText(QApplication::translate("DialogChoseData", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\201\321\202\321\200\320\276\320\272\321\203", 0));
        groupBox->setTitle(QApplication::translate("DialogChoseData", "\320\222\321\213\320\261\320\276\321\200 \320\270 \321\203\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \321\210\320\260\320\261\320\273\320\276\320\275\320\260\320\274\320\270", 0));
        pushButtonSave->setText(QApplication::translate("DialogChoseData", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217 \320\262 \321\210\320\260\320\261\320\273\320\276\320\275\320\265", 0));
        pushButtonDelete->setText(QApplication::translate("DialogChoseData", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\210\320\260\320\261\320\273\320\276\320\275", 0));
        pushButtonSaveAs->setText(QApplication::translate("DialogChoseData", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\275\320\276\320\262\321\213\320\271 \321\210\320\260\320\261\320\273\320\276\320\275", 0));
        groupBoxTitle->setTitle(QApplication::translate("DialogChoseData", "\320\227\320\260\320\263\320\276\320\273\320\276\320\262\320\276\320\272", 0));
        label->setText(QApplication::translate("DialogChoseData", "\320\227\320\260\320\263\320\276\320\273\320\276\320\262\320\276\320\272 (\320\277\321\200\320\276\321\202\320\276\320\272 \320\262\320\267\320\262\320\265\321\210\320\270\320\262\320\260\320\275\320\270\321\217, \321\201\320\276\321\201\321\202\320\260\320\262 \320\277\320\260\321\200, ...)", 0));
        groupBox_2->setTitle(QApplication::translate("DialogChoseData", "\320\237\320\265\321\200\320\265\320\262\320\276\320\264 \321\201\320\273\320\276\320\262", 0));
        groupBox_4->setTitle(QApplication::translate("DialogChoseData", "\320\237\320\276\320\264\320\277\320\270\321\201\320\270", 0));
        checkBoxMainSecretary->setText(QApplication::translate("DialogChoseData", "\320\223\320\273\320\260\320\262\320\275\321\213\320\271 \321\201\320\265\320\272\321\200\320\265\321\202\320\260\321\202\321\214:", 0));
        checkBoxAssociateMainJudge->setText(QApplication::translate("DialogChoseData", "\320\227\320\260\320\274. \320\263\320\273\320\260\320\262\320\275\320\276\320\263\320\276 \321\201\321\203\320\264\321\214\320\270:", 0));
        checkBoxMainJudge->setText(QApplication::translate("DialogChoseData", "\320\223\320\273\320\260\320\262\320\275\321\213\320\271 \321\201\321\203\320\264\321\214\321\217:", 0));
        lineEditTitleAssociateMainJudge->setText(QApplication::translate("DialogChoseData", "\320\227\320\260\320\274. \320\263\320\273\320\260\320\262\320\275\320\276\320\263\320\276 \321\201\321\203\320\264\321\214\320\270:", 0));
        lineEditTitleMainSecretary->setText(QApplication::translate("DialogChoseData", "\320\223\320\273\320\260\320\262\320\275\321\213\320\271 \321\201\320\265\320\272\321\200\320\265\321\202\320\260\321\200\321\214:", 0));
        lineEditTitleMainJudge->setText(QApplication::translate("DialogChoseData", "\320\223\320\273\320\260\320\262\320\275\321\213\320\271 \321\201\321\203\320\264\321\214\321\217:", 0));
        groupBox_3->setTitle(QApplication::translate("DialogChoseData", "\320\234\320\260\320\272\321\201. \320\267\320\260\320\275\321\217\321\202\320\276\320\265 \320\274\320\265\321\201\321\202\320\276 (\320\262\320\272\320\273\321\216\321\207\320\270\321\202\320\265\320\273\321\214\320\275\320\276) \320\262 \321\202\321\203\321\200\320\275\320\270\321\200\320\275\320\276\320\271 \321\201\320\265\321\202\320\272\320\265 (\320\264\320\273\321\217 \321\201\320\277\320\270\321\201\320\272\320\260 \320\277\321\200\320\270\320\267\321\221\321\200\320\276\320\262)", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogChoseData: public Ui_DialogChoseData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCHOSEDATA_H
