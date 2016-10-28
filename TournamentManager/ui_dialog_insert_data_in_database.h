/********************************************************************************
** Form generated from reading UI file 'dialog_insert_data_in_database.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_INSERT_DATA_IN_DATABASE_H
#define UI_DIALOG_INSERT_DATA_IN_DATABASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogInsertDataInDatabase
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *plainTextEdit;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit;
    QComboBox *comboBox;
    QPushButton *pushButtonAddNew;
    QPushButton *pushButtonSelectOld;

    void setupUi(QDialog *DialogInsertDataInDatabase)
    {
        if (DialogInsertDataInDatabase->objectName().isEmpty())
            DialogInsertDataInDatabase->setObjectName(QStringLiteral("DialogInsertDataInDatabase"));
        DialogInsertDataInDatabase->resize(604, 443);
        widget = new QWidget(DialogInsertDataInDatabase);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 10, 561, 411));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        plainTextEdit = new QPlainTextEdit(widget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setReadOnly(true);

        verticalLayout->addWidget(plainTextEdit);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 0, 1, 1);

        comboBox = new QComboBox(widget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setMinimumSize(QSize(259, 0));
        comboBox->setMaxVisibleItems(69);

        gridLayout->addWidget(comboBox, 0, 1, 1, 1);

        pushButtonAddNew = new QPushButton(widget);
        pushButtonAddNew->setObjectName(QStringLiteral("pushButtonAddNew"));

        gridLayout->addWidget(pushButtonAddNew, 1, 0, 1, 1);

        pushButtonSelectOld = new QPushButton(widget);
        pushButtonSelectOld->setObjectName(QStringLiteral("pushButtonSelectOld"));

        gridLayout->addWidget(pushButtonSelectOld, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(DialogInsertDataInDatabase);

        QMetaObject::connectSlotsByName(DialogInsertDataInDatabase);
    } // setupUi

    void retranslateUi(QDialog *DialogInsertDataInDatabase)
    {
        DialogInsertDataInDatabase->setWindowTitle(QApplication::translate("DialogInsertDataInDatabase", "Dialog", 0));
        pushButtonAddNew->setText(QApplication::translate("DialogInsertDataInDatabase", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\275\320\276\320\262\321\213\320\271", 0));
        pushButtonSelectOld->setText(QApplication::translate("DialogInsertDataInDatabase", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \320\270\320\267 \321\201\320\277\320\270\321\201\320\272\320\260", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogInsertDataInDatabase: public Ui_DialogInsertDataInDatabase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_INSERT_DATA_IN_DATABASE_H
