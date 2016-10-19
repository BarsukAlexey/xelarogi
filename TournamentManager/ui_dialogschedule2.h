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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>
#include "dialogschedule2tablewidget.h"
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
    QSpinBox *spinBoxDelay;
    QSpinBox *spinBoxRing;
    QLabel *labelContest;
    QLabel *label_3;
    QLabel *label_2;
    QComboBox *comboBoxDay;
    Dialogschedule2TreeWidget *treeWidget;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioTextCountry;
    QRadioButton *radioTextRegion;
    QRadioButton *radioTextCity;
    QRadioButton *radioTextClub;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioFlagCountry;
    QRadioButton *radioFlagRegion;
    QRadioButton *radioFlagCity;
    QRadioButton *radioFlagClub;
    QPushButton *pushButton;
    QPushButton *pushButtonListOfPairs;
    Dialogschedule2TableWidget *tableWidget;

    void setupUi(QDialog *Dialogschedule2)
    {
        if (Dialogschedule2->objectName().isEmpty())
            Dialogschedule2->setObjectName(QStringLiteral("Dialogschedule2"));
        Dialogschedule2->resize(1114, 631);
        gridLayout_2 = new QGridLayout(Dialogschedule2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        splitter = new QSplitter(Dialogschedule2);
        splitter->setObjectName(QStringLiteral("splitter"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setOrientation(Qt::Horizontal);
        widget = new QWidget(splitter);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        spinBoxDelay = new QSpinBox(widget);
        spinBoxDelay->setObjectName(QStringLiteral("spinBoxDelay"));
        spinBoxDelay->setMinimum(5);
        spinBoxDelay->setMaximum(100500);
        spinBoxDelay->setSingleStep(10);
        spinBoxDelay->setValue(120);

        gridLayout->addWidget(spinBoxDelay, 3, 1, 1, 1);

        spinBoxRing = new QSpinBox(widget);
        spinBoxRing->setObjectName(QStringLiteral("spinBoxRing"));
        spinBoxRing->setMinimum(1);
        spinBoxRing->setMaximum(228);

        gridLayout->addWidget(spinBoxRing, 1, 1, 1, 1);

        labelContest = new QLabel(widget);
        labelContest->setObjectName(QStringLiteral("labelContest"));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        labelContest->setFont(font);
        labelContest->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelContest, 0, 0, 1, 2);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        comboBoxDay = new QComboBox(widget);
        comboBoxDay->setObjectName(QStringLiteral("comboBoxDay"));

        gridLayout->addWidget(comboBoxDay, 2, 1, 1, 1);

        treeWidget = new Dialogschedule2TreeWidget(widget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(1, QString::fromUtf8("\320\221\320\276\320\270"));
        __qtreewidgetitem->setText(0, QString::fromUtf8("\320\232\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\217"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setFocusPolicy(Qt::ClickFocus);
        treeWidget->setStyleSheet(QStringLiteral(""));
        treeWidget->setColumnCount(5);

        gridLayout->addWidget(treeWidget, 7, 0, 1, 2);

        groupBox_2 = new QGroupBox(widget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        radioTextCountry = new QRadioButton(groupBox_2);
        radioTextCountry->setObjectName(QStringLiteral("radioTextCountry"));
        radioTextCountry->setChecked(true);

        horizontalLayout_2->addWidget(radioTextCountry);

        radioTextRegion = new QRadioButton(groupBox_2);
        radioTextRegion->setObjectName(QStringLiteral("radioTextRegion"));

        horizontalLayout_2->addWidget(radioTextRegion);

        radioTextCity = new QRadioButton(groupBox_2);
        radioTextCity->setObjectName(QStringLiteral("radioTextCity"));

        horizontalLayout_2->addWidget(radioTextCity);

        radioTextClub = new QRadioButton(groupBox_2);
        radioTextClub->setObjectName(QStringLiteral("radioTextClub"));

        horizontalLayout_2->addWidget(radioTextClub);


        gridLayout->addWidget(groupBox_2, 4, 0, 1, 1);

        groupBox = new QGroupBox(widget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        radioFlagCountry = new QRadioButton(groupBox);
        radioFlagCountry->setObjectName(QStringLiteral("radioFlagCountry"));
        radioFlagCountry->setChecked(true);

        horizontalLayout->addWidget(radioFlagCountry);

        radioFlagRegion = new QRadioButton(groupBox);
        radioFlagRegion->setObjectName(QStringLiteral("radioFlagRegion"));

        horizontalLayout->addWidget(radioFlagRegion);

        radioFlagCity = new QRadioButton(groupBox);
        radioFlagCity->setObjectName(QStringLiteral("radioFlagCity"));

        horizontalLayout->addWidget(radioFlagCity);

        radioFlagClub = new QRadioButton(groupBox);
        radioFlagClub->setObjectName(QStringLiteral("radioFlagClub"));

        horizontalLayout->addWidget(radioFlagClub);


        gridLayout->addWidget(groupBox, 4, 1, 1, 1);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 5, 0, 1, 1);

        pushButtonListOfPairs = new QPushButton(widget);
        pushButtonListOfPairs->setObjectName(QStringLiteral("pushButtonListOfPairs"));

        gridLayout->addWidget(pushButtonListOfPairs, 5, 1, 1, 1);

        splitter->addWidget(widget);
        tableWidget = new Dialogschedule2TableWidget(splitter);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setFocusPolicy(Qt::NoFocus);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        splitter->addWidget(tableWidget);

        gridLayout_2->addWidget(splitter, 0, 0, 1, 1);

        QWidget::setTabOrder(spinBoxRing, comboBoxDay);
        QWidget::setTabOrder(comboBoxDay, spinBoxDelay);
        QWidget::setTabOrder(spinBoxDelay, treeWidget);

        retranslateUi(Dialogschedule2);

        QMetaObject::connectSlotsByName(Dialogschedule2);
    } // setupUi

    void retranslateUi(QDialog *Dialogschedule2)
    {
        Dialogschedule2->setWindowTitle(QApplication::translate("Dialogschedule2", "Dialog", 0));
        label->setText(QApplication::translate("Dialogschedule2", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\277\320\273\320\276\321\211\320\260\320\264\320\276\320\272:", 0));
        labelContest->setText(QApplication::translate("Dialogschedule2", "#", 0));
        label_3->setText(QApplication::translate("Dialogschedule2", "\320\227\320\260\320\264\320\265\321\200\320\266\320\272\320\260 \321\201\320\274\320\265\320\275\321\213 \320\277\320\260\321\200 (\320\262 \321\201\320\265\320\272\321\203\320\275\320\264\320\260\321\205)", 0));
        label_2->setText(QApplication::translate("Dialogschedule2", "\320\224\320\265\320\275\321\214:", 0));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(4, QApplication::translate("Dialogschedule2", "\320\237\320\276\321\200\321\217\320\264\320\276\320\272", 0));
        ___qtreewidgetitem->setText(3, QApplication::translate("Dialogschedule2", "\320\240\320\270\320\275\320\263", 0));
        ___qtreewidgetitem->setText(2, QApplication::translate("Dialogschedule2", "\320\224\320\260\321\202\320\260", 0));
        groupBox_2->setTitle(QApplication::translate("Dialogschedule2", "\320\242\320\265\320\272\321\201\321\202", 0));
        radioTextCountry->setText(QApplication::translate("Dialogschedule2", "\320\241\321\202\321\200\320\260\320\275\320\260", 0));
        radioTextRegion->setText(QApplication::translate("Dialogschedule2", "\320\240\320\265\320\263\320\270\320\276\320\275", 0));
        radioTextCity->setText(QApplication::translate("Dialogschedule2", "\320\223\320\276\321\200\320\276\320\264", 0));
        radioTextClub->setText(QApplication::translate("Dialogschedule2", "\320\232\320\273\321\203\320\261", 0));
        groupBox->setTitle(QApplication::translate("Dialogschedule2", "\320\244\320\273\320\260\320\263", 0));
        radioFlagCountry->setText(QApplication::translate("Dialogschedule2", "\320\241\321\202\321\200\320\260\320\275\320\260", 0));
        radioFlagRegion->setText(QApplication::translate("Dialogschedule2", "\320\240\320\265\320\263\320\270\320\276\320\275", 0));
        radioFlagCity->setText(QApplication::translate("Dialogschedule2", "\320\223\320\276\321\200\320\276\320\264", 0));
        radioFlagClub->setText(QApplication::translate("Dialogschedule2", "\320\232\320\273\321\203\320\261", 0));
        pushButton->setText(QApplication::translate("Dialogschedule2", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \321\200\320\260\321\201\320\277\320\270\321\201\320\260\320\275\320\270\320\265 \320\262 excel...", 0));
        pushButtonListOfPairs->setText(QApplication::translate("Dialogschedule2", "\320\237\320\276\320\273\321\203\321\207\320\270\321\202\321\214  \321\201\320\277\320\270\321\201\320\276\320\272 \320\277\320\260\321\200 \320\270 \321\201\320\265\321\202\320\272\320\270 \320\275\320\260 \320\264\320\265\320\275\321\214...", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialogschedule2: public Ui_Dialogschedule2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSCHEDULE2_H
