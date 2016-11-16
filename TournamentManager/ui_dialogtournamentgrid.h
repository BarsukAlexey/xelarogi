/********************************************************************************
** Form generated from reading UI file 'dialogtournamentgrid.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGTOURNAMENTGRID_H
#define UI_DIALOGTOURNAMENTGRID_H

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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "renderareawidget.h"

QT_BEGIN_NAMESPACE

class Ui_DialogTournamentGrid
{
public:
    QGridLayout *gridLayout_2;
    QSplitter *splitter;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLineEdit *filterCategoriesLE;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioButtonAll;
    QRadioButton *radioButtonLonly;
    QRadioButton *radioButtonInvalid;
    QRadioButton *radioButtonInvalidTurn;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_5;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBoxCountry;
    QCheckBox *checkBoxRegion;
    QCheckBox *checkBoxCity;
    QCheckBox *checkBoxClub;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_6;
    QSpinBox *spinBoxFontSizeOfOrders;
    QSpinBox *spinBoxHeight;
    QSpinBox *spinBoxWidth;
    QSpinBox *spinBoxFontSizeOfTC;
    QSpinBox *spinBoxFontSizeOfListOfPairs;
    QSpinBox *spinBoxFontSizeOfNodeOfGrid;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer;
    QComboBox *qComboBoxSelectCategory;
    QTableWidget *qTableWidget;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *buttonGenerate;
    QPushButton *buttonGenerateAll;
    QPushButton *buttonDelete;
    QPushButton *buttonDeleteAll;
    QPushButton *buttonSave;
    QPushButton *buttonSaveAll;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *qTabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QScrollArea *scrollArea;
    RenderAreaWidget *pRenderArea;
    QWidget *tab_2;
    QGridLayout *gridLayout_4;
    QTableWidget *tableWidgeRight;

    void setupUi(QDialog *DialogTournamentGrid)
    {
        if (DialogTournamentGrid->objectName().isEmpty())
            DialogTournamentGrid->setObjectName(QStringLiteral("DialogTournamentGrid"));
        DialogTournamentGrid->resize(966, 430);
        gridLayout_2 = new QGridLayout(DialogTournamentGrid);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        splitter = new QSplitter(DialogTournamentGrid);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        widget = new QWidget(splitter);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        filterCategoriesLE = new QLineEdit(widget);
        filterCategoriesLE->setObjectName(QStringLiteral("filterCategoriesLE"));

        verticalLayout->addWidget(filterCategoriesLE);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox = new QGroupBox(widget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        radioButtonAll = new QRadioButton(groupBox);
        radioButtonAll->setObjectName(QStringLiteral("radioButtonAll"));
        radioButtonAll->setChecked(true);

        horizontalLayout_2->addWidget(radioButtonAll);

        radioButtonLonly = new QRadioButton(groupBox);
        radioButtonLonly->setObjectName(QStringLiteral("radioButtonLonly"));

        horizontalLayout_2->addWidget(radioButtonLonly);

        radioButtonInvalid = new QRadioButton(groupBox);
        radioButtonInvalid->setObjectName(QStringLiteral("radioButtonInvalid"));

        horizontalLayout_2->addWidget(radioButtonInvalid);

        radioButtonInvalidTurn = new QRadioButton(groupBox);
        radioButtonInvalidTurn->setObjectName(QStringLiteral("radioButtonInvalidTurn"));

        horizontalLayout_2->addWidget(radioButtonInvalidTurn);


        horizontalLayout->addWidget(groupBox);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        groupBox_2 = new QGroupBox(widget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        checkBoxCountry = new QCheckBox(groupBox_2);
        checkBoxCountry->setObjectName(QStringLiteral("checkBoxCountry"));

        horizontalLayout_3->addWidget(checkBoxCountry);

        checkBoxRegion = new QCheckBox(groupBox_2);
        checkBoxRegion->setObjectName(QStringLiteral("checkBoxRegion"));

        horizontalLayout_3->addWidget(checkBoxRegion);

        checkBoxCity = new QCheckBox(groupBox_2);
        checkBoxCity->setObjectName(QStringLiteral("checkBoxCity"));

        horizontalLayout_3->addWidget(checkBoxCity);

        checkBoxClub = new QCheckBox(groupBox_2);
        checkBoxClub->setObjectName(QStringLiteral("checkBoxClub"));

        horizontalLayout_3->addWidget(checkBoxClub);


        horizontalLayout_5->addWidget(groupBox_2);

        groupBox_5 = new QGroupBox(widget);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        gridLayout_6 = new QGridLayout(groupBox_5);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        spinBoxFontSizeOfOrders = new QSpinBox(groupBox_5);
        spinBoxFontSizeOfOrders->setObjectName(QStringLiteral("spinBoxFontSizeOfOrders"));
        spinBoxFontSizeOfOrders->setMinimum(1);
        spinBoxFontSizeOfOrders->setMaximum(228);
        spinBoxFontSizeOfOrders->setValue(9);

        gridLayout_6->addWidget(spinBoxFontSizeOfOrders, 1, 1, 1, 1);

        spinBoxHeight = new QSpinBox(groupBox_5);
        spinBoxHeight->setObjectName(QStringLiteral("spinBoxHeight"));
        spinBoxHeight->setMinimum(1);
        spinBoxHeight->setMaximum(3000);
        spinBoxHeight->setValue(30);

        gridLayout_6->addWidget(spinBoxHeight, 1, 4, 1, 1);

        spinBoxWidth = new QSpinBox(groupBox_5);
        spinBoxWidth->setObjectName(QStringLiteral("spinBoxWidth"));
        spinBoxWidth->setMinimum(1);
        spinBoxWidth->setMaximum(3000);
        spinBoxWidth->setSingleStep(5);
        spinBoxWidth->setValue(300);

        gridLayout_6->addWidget(spinBoxWidth, 1, 3, 1, 1);

        spinBoxFontSizeOfTC = new QSpinBox(groupBox_5);
        spinBoxFontSizeOfTC->setObjectName(QStringLiteral("spinBoxFontSizeOfTC"));
        spinBoxFontSizeOfTC->setMinimum(1);
        spinBoxFontSizeOfTC->setMaximum(228);
        spinBoxFontSizeOfTC->setValue(8);

        gridLayout_6->addWidget(spinBoxFontSizeOfTC, 1, 0, 1, 1);

        spinBoxFontSizeOfListOfPairs = new QSpinBox(groupBox_5);
        spinBoxFontSizeOfListOfPairs->setObjectName(QStringLiteral("spinBoxFontSizeOfListOfPairs"));
        spinBoxFontSizeOfListOfPairs->setMinimum(1);
        spinBoxFontSizeOfListOfPairs->setMaximum(228);
        spinBoxFontSizeOfListOfPairs->setValue(9);

        gridLayout_6->addWidget(spinBoxFontSizeOfListOfPairs, 1, 5, 1, 1);

        spinBoxFontSizeOfNodeOfGrid = new QSpinBox(groupBox_5);
        spinBoxFontSizeOfNodeOfGrid->setObjectName(QStringLiteral("spinBoxFontSizeOfNodeOfGrid"));
        spinBoxFontSizeOfNodeOfGrid->setMinimum(1);
        spinBoxFontSizeOfNodeOfGrid->setMaximum(228);
        spinBoxFontSizeOfNodeOfGrid->setValue(9);

        gridLayout_6->addWidget(spinBoxFontSizeOfNodeOfGrid, 1, 2, 1, 1);

        label = new QLabel(groupBox_5);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_6->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(groupBox_5);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_6->addWidget(label_2, 0, 1, 1, 1);

        label_3 = new QLabel(groupBox_5);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_6->addWidget(label_3, 0, 2, 1, 1);

        label_4 = new QLabel(groupBox_5);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_6->addWidget(label_4, 0, 3, 1, 1);

        label_5 = new QLabel(groupBox_5);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_6->addWidget(label_5, 0, 4, 1, 1);

        label_6 = new QLabel(groupBox_5);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_6->addWidget(label_6, 0, 5, 1, 1);


        horizontalLayout_5->addWidget(groupBox_5);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_5);

        qComboBoxSelectCategory = new QComboBox(widget);
        qComboBoxSelectCategory->setObjectName(QStringLiteral("qComboBoxSelectCategory"));
        qComboBoxSelectCategory->setMaxVisibleItems(300);

        verticalLayout->addWidget(qComboBoxSelectCategory);

        qTableWidget = new QTableWidget(widget);
        if (qTableWidget->columnCount() < 4)
            qTableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        qTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        qTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        qTableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        qTableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        qTableWidget->setObjectName(QStringLiteral("qTableWidget"));
        qTableWidget->setFocusPolicy(Qt::NoFocus);
        qTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        qTableWidget->setSelectionMode(QAbstractItemView::NoSelection);

        verticalLayout->addWidget(qTableWidget);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        buttonGenerate = new QPushButton(widget);
        buttonGenerate->setObjectName(QStringLiteral("buttonGenerate"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(buttonGenerate->sizePolicy().hasHeightForWidth());
        buttonGenerate->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(buttonGenerate);

        buttonGenerateAll = new QPushButton(widget);
        buttonGenerateAll->setObjectName(QStringLiteral("buttonGenerateAll"));
        sizePolicy1.setHeightForWidth(buttonGenerateAll->sizePolicy().hasHeightForWidth());
        buttonGenerateAll->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(buttonGenerateAll);

        buttonDelete = new QPushButton(widget);
        buttonDelete->setObjectName(QStringLiteral("buttonDelete"));
        sizePolicy1.setHeightForWidth(buttonDelete->sizePolicy().hasHeightForWidth());
        buttonDelete->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(buttonDelete);

        buttonDeleteAll = new QPushButton(widget);
        buttonDeleteAll->setObjectName(QStringLiteral("buttonDeleteAll"));
        sizePolicy1.setHeightForWidth(buttonDeleteAll->sizePolicy().hasHeightForWidth());
        buttonDeleteAll->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(buttonDeleteAll);

        buttonSave = new QPushButton(widget);
        buttonSave->setObjectName(QStringLiteral("buttonSave"));
        sizePolicy1.setHeightForWidth(buttonSave->sizePolicy().hasHeightForWidth());
        buttonSave->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(buttonSave);

        buttonSaveAll = new QPushButton(widget);
        buttonSaveAll->setObjectName(QStringLiteral("buttonSaveAll"));
        sizePolicy1.setHeightForWidth(buttonSaveAll->sizePolicy().hasHeightForWidth());
        buttonSaveAll->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(buttonSaveAll);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_4);

        splitter->addWidget(widget);
        widget_2 = new QWidget(splitter);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        qTabWidget = new QTabWidget(widget_2);
        qTabWidget->setObjectName(QStringLiteral("qTabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        scrollArea = new QScrollArea(tab);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setAlignment(Qt::AlignCenter);
        pRenderArea = new RenderAreaWidget();
        pRenderArea->setObjectName(QStringLiteral("pRenderArea"));
        pRenderArea->setGeometry(QRect(0, 0, 252, 348));
        scrollArea->setWidget(pRenderArea);

        gridLayout_3->addWidget(scrollArea, 0, 0, 1, 1);

        qTabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_4 = new QGridLayout(tab_2);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        tableWidgeRight = new QTableWidget(tab_2);
        if (tableWidgeRight->columnCount() < 5)
            tableWidgeRight->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgeRight->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgeRight->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgeRight->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgeRight->setHorizontalHeaderItem(3, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgeRight->setHorizontalHeaderItem(4, __qtablewidgetitem8);
        tableWidgeRight->setObjectName(QStringLiteral("tableWidgeRight"));
        tableWidgeRight->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidgeRight->setSelectionMode(QAbstractItemView::SingleSelection);

        gridLayout_4->addWidget(tableWidgeRight, 0, 0, 1, 1);

        qTabWidget->addTab(tab_2, QString());

        verticalLayout_2->addWidget(qTabWidget);

        splitter->addWidget(widget_2);

        gridLayout_2->addWidget(splitter, 1, 0, 1, 1);

        QWidget::setTabOrder(filterCategoriesLE, radioButtonAll);
        QWidget::setTabOrder(radioButtonAll, radioButtonLonly);
        QWidget::setTabOrder(radioButtonLonly, radioButtonInvalid);
        QWidget::setTabOrder(radioButtonInvalid, radioButtonInvalidTurn);
        QWidget::setTabOrder(radioButtonInvalidTurn, checkBoxCountry);
        QWidget::setTabOrder(checkBoxCountry, checkBoxRegion);
        QWidget::setTabOrder(checkBoxRegion, checkBoxCity);
        QWidget::setTabOrder(checkBoxCity, checkBoxClub);
        QWidget::setTabOrder(checkBoxClub, spinBoxFontSizeOfTC);
        QWidget::setTabOrder(spinBoxFontSizeOfTC, spinBoxFontSizeOfOrders);
        QWidget::setTabOrder(spinBoxFontSizeOfOrders, spinBoxWidth);
        QWidget::setTabOrder(spinBoxWidth, spinBoxHeight);
        QWidget::setTabOrder(spinBoxHeight, spinBoxFontSizeOfListOfPairs);
        QWidget::setTabOrder(spinBoxFontSizeOfListOfPairs, qComboBoxSelectCategory);
        QWidget::setTabOrder(qComboBoxSelectCategory, buttonGenerate);
        QWidget::setTabOrder(buttonGenerate, buttonGenerateAll);
        QWidget::setTabOrder(buttonGenerateAll, buttonDelete);
        QWidget::setTabOrder(buttonDelete, buttonDeleteAll);
        QWidget::setTabOrder(buttonDeleteAll, buttonSave);
        QWidget::setTabOrder(buttonSave, buttonSaveAll);
        QWidget::setTabOrder(buttonSaveAll, qTabWidget);
        QWidget::setTabOrder(qTabWidget, scrollArea);
        QWidget::setTabOrder(scrollArea, tableWidgeRight);

        retranslateUi(DialogTournamentGrid);

        qTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DialogTournamentGrid);
    } // setupUi

    void retranslateUi(QDialog *DialogTournamentGrid)
    {
        DialogTournamentGrid->setWindowTitle(QApplication::translate("DialogTournamentGrid", "\320\241\320\265\321\202\320\272\320\270", 0));
        filterCategoriesLE->setInputMask(QString());
        filterCategoriesLE->setPlaceholderText(QString());
        groupBox->setTitle(QApplication::translate("DialogTournamentGrid", "\320\244\320\270\320\273\321\214\321\202\321\200 \321\201\320\265\321\202\320\276\320\272", 0));
        radioButtonAll->setText(QApplication::translate("DialogTournamentGrid", "\320\222\321\201\320\265", 0));
        radioButtonLonly->setText(QApplication::translate("DialogTournamentGrid", "\320\236\320\264\320\270\320\275", 0));
        radioButtonInvalid->setText(QApplication::translate("DialogTournamentGrid", "\320\240\320\260\320\267\320\275\321\213\320\265 \321\203\321\207\320\260\321\201\321\202\320\275\320\270\320\272\320\270", 0));
        radioButtonInvalidTurn->setText(QApplication::translate("DialogTournamentGrid", "\320\235\320\265\320\267\320\260\320\277\320\276\320\273\320\275\320\265\320\275\320\275\321\213\320\265 \320\272\321\200\321\203\320\263\320\270", 0));
        groupBox_2->setTitle(QString());
        checkBoxCountry->setText(QApplication::translate("DialogTournamentGrid", "\320\241\321\202\321\200\320\260\320\275\320\260", 0));
        checkBoxRegion->setText(QApplication::translate("DialogTournamentGrid", "\320\240\320\265\320\263\320\270\320\276\320\275", 0));
        checkBoxCity->setText(QApplication::translate("DialogTournamentGrid", "\320\223\320\276\321\200\320\276\320\264", 0));
        checkBoxClub->setText(QApplication::translate("DialogTournamentGrid", "\320\232\320\273\321\203\320\261", 0));
        groupBox_5->setTitle(QString());
        label->setText(QApplication::translate("DialogTournamentGrid", "\320\232\320\260\321\202\320\265\320\263.", 0));
        label_2->setText(QApplication::translate("DialogTournamentGrid", "\320\243\321\207\320\260\321\201\321\202\320\275.", 0));
        label_3->setText(QApplication::translate("DialogTournamentGrid", "\320\241\320\265\321\202\320\272\320\260", 0));
        label_4->setText(QApplication::translate("DialogTournamentGrid", "\320\250\320\270\321\200\320\270\320\275\320\260", 0));
        label_5->setText(QApplication::translate("DialogTournamentGrid", "\320\222\321\213\321\201\320\276\321\202\320\260", 0));
        label_6->setText(QApplication::translate("DialogTournamentGrid", "\320\237\320\260\321\200\321\213", 0));
        QTableWidgetItem *___qtablewidgetitem = qTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("DialogTournamentGrid", "\320\241\320\277\320\276\321\200\321\202\321\201\320\274\320\265\320\275", 0));
        QTableWidgetItem *___qtablewidgetitem1 = qTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("DialogTournamentGrid", "\320\241\321\202\321\200\320\260\320\275\320\260/\321\200\320\265\320\263\320\270\320\276\320\275/\320\263\320\276\321\200\320\276\320\264/\320\272\320\273\321\203\320\261", 0));
        QTableWidgetItem *___qtablewidgetitem2 = qTableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("DialogTournamentGrid", "\320\237\321\200\320\270\320\276\321\200\320\270\321\202\320\265\321\202", 0));
        QTableWidgetItem *___qtablewidgetitem3 = qTableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("DialogTournamentGrid", "\320\240\320\260\320\267\321\200\321\217\320\264", 0));
        buttonGenerate->setText(QApplication::translate("DialogTournamentGrid", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", 0));
        buttonGenerateAll->setText(QApplication::translate("DialogTournamentGrid", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\262\321\201\321\221", 0));
        buttonDelete->setText(QApplication::translate("DialogTournamentGrid", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", 0));
        buttonDeleteAll->setText(QApplication::translate("DialogTournamentGrid", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\262\321\201\321\221", 0));
        buttonSave->setText(QApplication::translate("DialogTournamentGrid", "Save as Excel", 0));
        buttonSaveAll->setText(QApplication::translate("DialogTournamentGrid", "Save all as Excel", 0));
        qTabWidget->setTabText(qTabWidget->indexOf(tab), QApplication::translate("DialogTournamentGrid", "\320\241\320\265\321\202\320\272\320\260", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgeRight->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("DialogTournamentGrid", "\320\241\320\277\320\276\321\200\321\202\321\201\320\274\320\265\320\275 A", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgeRight->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QApplication::translate("DialogTournamentGrid", "\320\240\320\265\320\263\320\270\320\276\320\275 A", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgeRight->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QApplication::translate("DialogTournamentGrid", "\320\241\320\277\320\276\321\200\321\202\321\201\320\274\320\265\320\275 B", 0));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgeRight->horizontalHeaderItem(3);
        ___qtablewidgetitem7->setText(QApplication::translate("DialogTournamentGrid", "\320\240\320\265\320\263\320\270\320\276\320\275 B", 0));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgeRight->horizontalHeaderItem(4);
        ___qtablewidgetitem8->setText(QApplication::translate("DialogTournamentGrid", "\320\243\321\200\320\276\320\262\320\265\320\275\321\214", 0));
        qTabWidget->setTabText(qTabWidget->indexOf(tab_2), QApplication::translate("DialogTournamentGrid", "\320\241\320\277\320\270\321\201\320\276\320\272", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogTournamentGrid: public Ui_DialogTournamentGrid {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGTOURNAMENTGRID_H
