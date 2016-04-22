/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qrightclickbutton.h"

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_4;
    QLabel *labelFIO;
    QLabel *labelFlag;
    QLabel *labelRegion;
    QRightClickButton *pushButtonPoint;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_2;
    QRightClickButton *pushButtonMinus;
    QLabel *labelMinus;
    QHBoxLayout *horizontalLayout;
    QRightClickButton *pushButtonFo;
    QLabel *labelFo;
    QHBoxLayout *horizontalLayout_3;
    QRightClickButton *pushButtonEx;
    QLabel *labelEx;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(781, 683);
        Form->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\n"
"Text-align:right;\n"
"color: rgb(255, 255, 255)"));
        gridLayout = new QGridLayout(Form);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(Form);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QStringLiteral(""));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_4 = new QSpacerItem(20, 90, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        labelFIO = new QLabel(widget);
        labelFIO->setObjectName(QStringLiteral("labelFIO"));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        labelFIO->setPalette(palette);
        QFont font;
        font.setPointSize(25);
        labelFIO->setFont(font);
        labelFIO->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        labelFIO->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelFIO);

        labelFlag = new QLabel(widget);
        labelFlag->setObjectName(QStringLiteral("labelFlag"));
        labelFlag->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        labelFlag->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelFlag);

        labelRegion = new QLabel(widget);
        labelRegion->setObjectName(QStringLiteral("labelRegion"));
        QFont font1;
        font1.setPointSize(15);
        labelRegion->setFont(font1);
        labelRegion->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        labelRegion->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelRegion);

        pushButtonPoint = new QRightClickButton(widget);
        pushButtonPoint->setObjectName(QStringLiteral("pushButtonPoint"));
        pushButtonPoint->setMinimumSize(QSize(0, 0));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        pushButtonPoint->setPalette(palette1);
        QFont font2;
        font2.setPointSize(99);
        pushButtonPoint->setFont(font2);
        pushButtonPoint->setStyleSheet(QStringLiteral("Text-align:center"));
        pushButtonPoint->setAutoDefault(false);
        pushButtonPoint->setFlat(false);

        verticalLayout->addWidget(pushButtonPoint);

        verticalSpacer_5 = new QSpacerItem(20, 89, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButtonMinus = new QRightClickButton(widget);
        pushButtonMinus->setObjectName(QStringLiteral("pushButtonMinus"));
        QFont font3;
        font3.setPointSize(14);
        pushButtonMinus->setFont(font3);
        pushButtonMinus->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(pushButtonMinus);

        labelMinus = new QLabel(widget);
        labelMinus->setObjectName(QStringLiteral("labelMinus"));
        labelMinus->setFont(font3);
        labelMinus->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        labelMinus->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(labelMinus);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButtonFo = new QRightClickButton(widget);
        pushButtonFo->setObjectName(QStringLiteral("pushButtonFo"));
        pushButtonFo->setFont(font3);
        pushButtonFo->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(pushButtonFo);

        labelFo = new QLabel(widget);
        labelFo->setObjectName(QStringLiteral("labelFo"));
        labelFo->setFont(font3);
        labelFo->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(labelFo);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        pushButtonEx = new QRightClickButton(widget);
        pushButtonEx->setObjectName(QStringLiteral("pushButtonEx"));
        pushButtonEx->setFont(font3);

        horizontalLayout_3->addWidget(pushButtonEx);

        labelEx = new QLabel(widget);
        labelEx->setObjectName(QStringLiteral("labelEx"));
        labelEx->setFont(font3);
        labelEx->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        labelEx->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(labelEx);


        verticalLayout->addLayout(horizontalLayout_3);


        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(Form);

        pushButtonPoint->setDefault(false);


        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0));
        labelFIO->setText(QApplication::translate("Form", "Name", 0));
        labelFlag->setText(QApplication::translate("Form", "Flag", 0));
        labelRegion->setText(QApplication::translate("Form", "Region", 0));
        pushButtonPoint->setText(QApplication::translate("Form", "0", 0));
        pushButtonMinus->setText(QApplication::translate("Form", "Minus:", 0));
        labelMinus->setText(QString());
        pushButtonFo->setText(QApplication::translate("Form", "Fo:", 0));
        labelFo->setText(QString());
        pushButtonEx->setText(QApplication::translate("Form", "Ex:", 0));
        labelEx->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
