/********************************************************************************
** Form generated from reading UI file 'dialogselectfieldsfordimloma.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSELECTFIELDSFORDIMLOMA_H
#define UI_DIALOGSELECTFIELDSFORDIMLOMA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogSelectFieldsForDimloma
{
public:
    QGridLayout *gridLayout;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButtonAdd;
    QDialogButtonBox *buttonBox;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QListWidget *listWidgetLeft;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButtonLeftRight;
    QPushButton *pushButtonRightLeft;
    QSpacerItem *verticalSpacer_2;
    QListWidget *listWidgetRight;
    QLabel *label;

    void setupUi(QDialog *DialogSelectFieldsForDimloma)
    {
        if (DialogSelectFieldsForDimloma->objectName().isEmpty())
            DialogSelectFieldsForDimloma->setObjectName(QStringLiteral("DialogSelectFieldsForDimloma"));
        DialogSelectFieldsForDimloma->resize(651, 465);
        gridLayout = new QGridLayout(DialogSelectFieldsForDimloma);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget_3 = new QWidget(DialogSelectFieldsForDimloma);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        horizontalLayout = new QHBoxLayout(widget_3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineEdit = new QLineEdit(widget_3);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        pushButtonAdd = new QPushButton(widget_3);
        pushButtonAdd->setObjectName(QStringLiteral("pushButtonAdd"));

        horizontalLayout->addWidget(pushButtonAdd);


        gridLayout->addWidget(widget_3, 2, 0, 1, 1);

        buttonBox = new QDialogButtonBox(DialogSelectFieldsForDimloma);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 3, 0, 1, 1);

        widget = new QWidget(DialogSelectFieldsForDimloma);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        listWidgetLeft = new QListWidget(widget);
        listWidgetLeft->setObjectName(QStringLiteral("listWidgetLeft"));

        gridLayout_2->addWidget(listWidgetLeft, 0, 0, 1, 1);

        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pushButtonLeftRight = new QPushButton(widget_2);
        pushButtonLeftRight->setObjectName(QStringLiteral("pushButtonLeftRight"));

        verticalLayout->addWidget(pushButtonLeftRight);

        pushButtonRightLeft = new QPushButton(widget_2);
        pushButtonRightLeft->setObjectName(QStringLiteral("pushButtonRightLeft"));

        verticalLayout->addWidget(pushButtonRightLeft);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        gridLayout_2->addWidget(widget_2, 0, 1, 1, 1);

        listWidgetRight = new QListWidget(widget);
        listWidgetRight->setObjectName(QStringLiteral("listWidgetRight"));

        gridLayout_2->addWidget(listWidgetRight, 0, 2, 1, 1);

        gridLayout_2->setColumnStretch(0, 100);
        gridLayout_2->setColumnStretch(1, 1);
        gridLayout_2->setColumnStretch(2, 100);

        gridLayout->addWidget(widget, 0, 0, 1, 1);

        label = new QLabel(DialogSelectFieldsForDimloma);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);


        retranslateUi(DialogSelectFieldsForDimloma);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogSelectFieldsForDimloma, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogSelectFieldsForDimloma, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogSelectFieldsForDimloma);
    } // setupUi

    void retranslateUi(QDialog *DialogSelectFieldsForDimloma)
    {
        DialogSelectFieldsForDimloma->setWindowTitle(QApplication::translate("DialogSelectFieldsForDimloma", "Dialog", 0));
        pushButtonAdd->setText(QApplication::translate("DialogSelectFieldsForDimloma", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", 0));
        pushButtonLeftRight->setText(QApplication::translate("DialogSelectFieldsForDimloma", ">>", 0));
        pushButtonRightLeft->setText(QApplication::translate("DialogSelectFieldsForDimloma", "<<", 0));
        label->setText(QApplication::translate("DialogSelectFieldsForDimloma", "\320\233\321\216\320\261\320\276\320\271 \321\202\320\265\320\272\321\201\321\202", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogSelectFieldsForDimloma: public Ui_DialogSelectFieldsForDimloma {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSELECTFIELDSFORDIMLOMA_H
