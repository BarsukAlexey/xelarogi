/********************************************************************************
** Form generated from reading UI file 'fighting_pairs.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIGHTING_PAIRS_H
#define UI_FIGHTING_PAIRS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FightingPairs
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioTextCountry;
    QRadioButton *radioTextRegion;
    QRadioButton *radioTextCity;
    QRadioButton *radioTextClub;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *radioButtonChampionship;
    QRadioButton *radioButtonCube;
    QFormLayout *formLayout;
    QLabel *label;
    QSpinBox *ringSpinBox;
    QLabel *label_2;
    QLineEdit *qLineEdit;
    QLabel *label_3;
    QSpinBox *spinBoxDelay;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioFlagCountry;
    QRadioButton *radioFlagRegion;
    QRadioButton *radioFlagCity;
    QRadioButton *radioFlagClub;
    QSpacerItem *horizontalSpacer_2;
    QTableWidget *qTableWidget;
    QPushButton *qPushButton;
    QLabel *label_4;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelAverageTime11111;
    QLabel *labelAverageTime;

    void setupUi(QDialog *FightingPairs)
    {
        if (FightingPairs->objectName().isEmpty())
            FightingPairs->setObjectName(QStringLiteral("FightingPairs"));
        gridLayout = new QGridLayout(FightingPairs);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox = new QGroupBox(FightingPairs);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        radioTextCountry = new QRadioButton(groupBox);
        radioTextCountry->setObjectName(QStringLiteral("radioTextCountry"));

        horizontalLayout->addWidget(radioTextCountry);

        radioTextRegion = new QRadioButton(groupBox);
        radioTextRegion->setObjectName(QStringLiteral("radioTextRegion"));
        radioTextRegion->setChecked(true);

        horizontalLayout->addWidget(radioTextRegion);

        radioTextCity = new QRadioButton(groupBox);
        radioTextCity->setObjectName(QStringLiteral("radioTextCity"));

        horizontalLayout->addWidget(radioTextCity);

        radioTextClub = new QRadioButton(groupBox);
        radioTextClub->setObjectName(QStringLiteral("radioTextClub"));

        horizontalLayout->addWidget(radioTextClub);


        gridLayout->addWidget(groupBox, 4, 2, 1, 1);

        groupBox_3 = new QGroupBox(FightingPairs);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_3);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        radioButtonChampionship = new QRadioButton(groupBox_3);
        radioButtonChampionship->setObjectName(QStringLiteral("radioButtonChampionship"));
        radioButtonChampionship->setChecked(true);

        horizontalLayout_3->addWidget(radioButtonChampionship);

        radioButtonCube = new QRadioButton(groupBox_3);
        radioButtonCube->setObjectName(QStringLiteral("radioButtonCube"));

        horizontalLayout_3->addWidget(radioButtonCube);


        gridLayout->addWidget(groupBox_3, 4, 1, 1, 1);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(FightingPairs);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        ringSpinBox = new QSpinBox(FightingPairs);
        ringSpinBox->setObjectName(QStringLiteral("ringSpinBox"));
        ringSpinBox->setMinimum(1);
        ringSpinBox->setMaximum(100500);

        formLayout->setWidget(0, QFormLayout::FieldRole, ringSpinBox);

        label_2 = new QLabel(FightingPairs);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        qLineEdit = new QLineEdit(FightingPairs);
        qLineEdit->setObjectName(QStringLiteral("qLineEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, qLineEdit);

        label_3 = new QLabel(FightingPairs);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setWordWrap(true);

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        spinBoxDelay = new QSpinBox(FightingPairs);
        spinBoxDelay->setObjectName(QStringLiteral("spinBoxDelay"));
        spinBoxDelay->setMaximum(100500);
        spinBoxDelay->setValue(120);

        formLayout->setWidget(2, QFormLayout::FieldRole, spinBoxDelay);


        gridLayout->addLayout(formLayout, 4, 0, 1, 1);

        groupBox_2 = new QGroupBox(FightingPairs);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        radioFlagCountry = new QRadioButton(groupBox_2);
        radioFlagCountry->setObjectName(QStringLiteral("radioFlagCountry"));

        horizontalLayout_2->addWidget(radioFlagCountry);

        radioFlagRegion = new QRadioButton(groupBox_2);
        radioFlagRegion->setObjectName(QStringLiteral("radioFlagRegion"));
        radioFlagRegion->setChecked(true);

        horizontalLayout_2->addWidget(radioFlagRegion);

        radioFlagCity = new QRadioButton(groupBox_2);
        radioFlagCity->setObjectName(QStringLiteral("radioFlagCity"));

        horizontalLayout_2->addWidget(radioFlagCity);

        radioFlagClub = new QRadioButton(groupBox_2);
        radioFlagClub->setObjectName(QStringLiteral("radioFlagClub"));

        horizontalLayout_2->addWidget(radioFlagClub);


        gridLayout->addWidget(groupBox_2, 4, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 4, 4, 1, 1);

        qTableWidget = new QTableWidget(FightingPairs);
        if (qTableWidget->columnCount() < 3)
            qTableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        qTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        qTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        qTableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        qTableWidget->setObjectName(QStringLiteral("qTableWidget"));
        QPalette palette;
        QBrush brush(QColor(51, 153, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Highlight, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Highlight, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Highlight, brush);
        qTableWidget->setPalette(palette);
        qTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        qTableWidget->setSelectionMode(QAbstractItemView::MultiSelection);
        qTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

        gridLayout->addWidget(qTableWidget, 0, 0, 1, 5);

        qPushButton = new QPushButton(FightingPairs);
        qPushButton->setObjectName(QStringLiteral("qPushButton"));

        gridLayout->addWidget(qPushButton, 7, 0, 1, 5);

        label_4 = new QLabel(FightingPairs);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 8, 0, 1, 5);

        widget = new QWidget(FightingPairs);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout_4 = new QHBoxLayout(widget);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        labelAverageTime11111 = new QLabel(widget);
        labelAverageTime11111->setObjectName(QStringLiteral("labelAverageTime11111"));
        QFont font;
        font.setPointSize(12);
        font.setItalic(true);
        labelAverageTime11111->setFont(font);
        labelAverageTime11111->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(labelAverageTime11111);

        labelAverageTime = new QLabel(widget);
        labelAverageTime->setObjectName(QStringLiteral("labelAverageTime"));
        labelAverageTime->setFont(font);
        labelAverageTime->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(labelAverageTime);


        gridLayout->addWidget(widget, 2, 0, 1, 5);


        retranslateUi(FightingPairs);

        QMetaObject::connectSlotsByName(FightingPairs);
    } // setupUi

    void retranslateUi(QDialog *FightingPairs)
    {
        groupBox->setTitle(QApplication::translate("FightingPairs", "\320\242\320\265\320\272\321\201\321\202 (\320\264\320\273\321\217 \321\202\320\260\320\261\320\273\320\276 \320\270 Excel-\321\204\320\260\320\271\320\273\320\260)", 0));
        radioTextCountry->setText(QApplication::translate("FightingPairs", "\320\241\321\202\321\200\320\260\320\275\320\260", 0));
        radioTextRegion->setText(QApplication::translate("FightingPairs", "\320\240\320\265\320\263\320\270\320\276\320\275", 0));
        radioTextCity->setText(QApplication::translate("FightingPairs", "\320\223\320\276\321\200\320\276\320\264", 0));
        radioTextClub->setText(QApplication::translate("FightingPairs", "\320\232\320\273\321\203\320\261", 0));
        groupBox_3->setTitle(QApplication::translate("FightingPairs", "\320\242\320\270\320\277", 0));
        radioButtonChampionship->setText(QApplication::translate("FightingPairs", "\320\247\320\265\320\274\320\277\320\270\320\276\320\275\320\260\321\202", 0));
        radioButtonCube->setText(QApplication::translate("FightingPairs", "\320\232\321\203\320\261\320\276\320\272", 0));
        label->setText(QApplication::translate("FightingPairs", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\200\320\270\320\275\320\263\320\276\320\262", 0));
        label_2->setText(QApplication::translate("FightingPairs", "\320\224\320\260\321\202\320\260 + {\321\203\321\202\321\200\320\276, \320\264\320\265\320\275\321\214, \320\262\320\265\321\207\320\265\321\200}", 0));
        label_3->setText(QApplication::translate("FightingPairs", "\320\241\321\200\320\265\320\264\320\275\321\217\321\217 \320\267\320\260\320\264\320\265\321\200\320\266\320\272\320\260 \320\277\321\200\320\270 \321\201\320\274\320\265\320\275\320\265 \320\277\320\260\321\200 \320\275\320\260 \321\200\320\270\320\275\320\263\320\265 (\320\262 \321\201\320\265\320\272\321\203\320\275\320\264\320\260\321\205)", 0));
        groupBox_2->setTitle(QApplication::translate("FightingPairs", "\320\244\320\273\320\260\320\263 (\320\264\320\273\321\217 \321\202\320\260\320\261\320\273\320\276)", 0));
        radioFlagCountry->setText(QApplication::translate("FightingPairs", "\320\241\321\202\321\200\320\260\320\275\320\260", 0));
        radioFlagRegion->setText(QApplication::translate("FightingPairs", "\320\240\320\265\320\263\320\270\320\276\320\275", 0));
        radioFlagCity->setText(QApplication::translate("FightingPairs", "\320\223\320\276\321\200\320\276\320\264", 0));
        radioFlagClub->setText(QApplication::translate("FightingPairs", "\320\232\320\273\321\203\320\261", 0));
        QTableWidgetItem *___qtablewidgetitem = qTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("FightingPairs", "\320\232\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\217", 0));
        QTableWidgetItem *___qtablewidgetitem1 = qTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("FightingPairs", "\320\221\320\276\320\270", 0));
        QTableWidgetItem *___qtablewidgetitem2 = qTableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("FightingPairs", "\320\232\320\276\320\273-\320\262\320\276 \320\272\321\200\321\203\320\263\320\276\320\262", 0));
        qPushButton->setText(QApplication::translate("FightingPairs", "Ok", 0));
        label_4->setText(QApplication::translate("FightingPairs", "* \320\222\321\200\320\265\320\274\321\217 \320\262\321\213\321\207\320\270\321\201\320\273\320\265\320\275\320\270\321\217 \321\200\320\260\321\201\320\277\320\265\321\200\320\265\320\264\320\265\320\273\320\265\320\275\320\270\321\217 \320\261\320\276\321\221\320\262 \320\277\320\276 \321\200\320\270\320\275\320\263\320\260\320\274 \320\274\320\276\320\266\320\265\321\202 \321\201\320\276\321\201\321\202\320\260\320\262\320\273\321\217\321\202\321\214 \320\264\320\276 1 \320\274\320\270\320\275", 0));
        labelAverageTime11111->setText(QApplication::translate("FightingPairs", "\320\241\321\200\320\265\320\264\320\275\320\265\320\265 \320\262\321\200\320\265\320\274\321\217:", 0));
        labelAverageTime->setText(QString());
        Q_UNUSED(FightingPairs);
    } // retranslateUi

};

namespace Ui {
    class FightingPairs: public Ui_FightingPairs {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIGHTING_PAIRS_H