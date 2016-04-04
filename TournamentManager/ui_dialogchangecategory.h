/********************************************************************************
** Form generated from reading UI file 'dialogchangecategory.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
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
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogChangeCategory
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QTableWidget *tableWidget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogChangeCategory)
    {
        if (DialogChangeCategory->objectName().isEmpty())
            DialogChangeCategory->setObjectName(QStringLiteral("DialogChangeCategory"));
        DialogChangeCategory->resize(619, 566);
        gridLayout = new QGridLayout(DialogChangeCategory);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(DialogChangeCategory);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        tableWidget = new QTableWidget(DialogChangeCategory);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setColumnCount(2);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(true);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget->horizontalHeader()->setStretchLastSection(false);

        gridLayout->addWidget(tableWidget, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(DialogChangeCategory);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 1);


        retranslateUi(DialogChangeCategory);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogChangeCategory, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogChangeCategory, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogChangeCategory);
    } // setupUi

    void retranslateUi(QDialog *DialogChangeCategory)
    {
        DialogChangeCategory->setWindowTitle(QApplication::translate("DialogChangeCategory", "Dialog", 0));
        label->setText(QApplication::translate("DialogChangeCategory", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogChangeCategory: public Ui_DialogChangeCategory {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCHANGECATEGORY_H
