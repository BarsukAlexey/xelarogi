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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>
#include <aspect_ratio_pixmap_label.h>
#include <aspectratiotextlabel.h>
#include <qrightclickbutton.h>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QRightClickButton *pushButtonMinus;
    AspectRatioPixmapLabel *labelMinus;
    QRightClickButton *pushButtonFo;
    AspectRatioPixmapLabel *labelFo;
    QRightClickButton *pushButtonEx;
    AspectRatioPixmapLabel *labelEx;
    AspectRatioTextLabel *labelRegion;
    AspectRatioPixmapLabel *labelFlag;
    AspectRatioTextLabel *labelFIO;
    QRightClickButton *pushButtonPoint;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(766, 618);
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
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pushButtonMinus = new QRightClickButton(widget);
        pushButtonMinus->setObjectName(QStringLiteral("pushButtonMinus"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonMinus->sizePolicy().hasHeightForWidth());
        pushButtonMinus->setSizePolicy(sizePolicy);
        pushButtonMinus->setStyleSheet(QStringLiteral(""));

        gridLayout_2->addWidget(pushButtonMinus, 4, 0, 1, 1);

        labelMinus = new AspectRatioPixmapLabel(widget);
        labelMinus->setObjectName(QStringLiteral("labelMinus"));
        QFont font;
        font.setPointSize(14);
        labelMinus->setFont(font);
        labelMinus->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        labelMinus->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(labelMinus, 4, 1, 1, 1);

        pushButtonFo = new QRightClickButton(widget);
        pushButtonFo->setObjectName(QStringLiteral("pushButtonFo"));
        sizePolicy.setHeightForWidth(pushButtonFo->sizePolicy().hasHeightForWidth());
        pushButtonFo->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(pushButtonFo, 5, 0, 1, 1);

        labelFo = new AspectRatioPixmapLabel(widget);
        labelFo->setObjectName(QStringLiteral("labelFo"));
        labelFo->setFont(font);
        labelFo->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(labelFo, 5, 1, 1, 1);

        pushButtonEx = new QRightClickButton(widget);
        pushButtonEx->setObjectName(QStringLiteral("pushButtonEx"));
        sizePolicy.setHeightForWidth(pushButtonEx->sizePolicy().hasHeightForWidth());
        pushButtonEx->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(pushButtonEx, 6, 0, 1, 1);

        labelEx = new AspectRatioPixmapLabel(widget);
        labelEx->setObjectName(QStringLiteral("labelEx"));
        labelEx->setFont(font);
        labelEx->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        labelEx->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(labelEx, 6, 1, 1, 1);

        labelRegion = new AspectRatioTextLabel(widget);
        labelRegion->setObjectName(QStringLiteral("labelRegion"));
        QFont font1;
        font1.setPointSize(15);
        labelRegion->setFont(font1);
        labelRegion->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        labelRegion->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(labelRegion, 2, 0, 1, 2);

        labelFlag = new AspectRatioPixmapLabel(widget);
        labelFlag->setObjectName(QStringLiteral("labelFlag"));
        sizePolicy.setHeightForWidth(labelFlag->sizePolicy().hasHeightForWidth());
        labelFlag->setSizePolicy(sizePolicy);
        labelFlag->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(labelFlag, 1, 0, 1, 2);

        labelFIO = new AspectRatioTextLabel(widget);
        labelFIO->setObjectName(QStringLiteral("labelFIO"));
        labelFIO->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        labelFIO->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(labelFIO, 0, 0, 1, 2);

        pushButtonPoint = new QRightClickButton(widget);
        pushButtonPoint->setObjectName(QStringLiteral("pushButtonPoint"));
        sizePolicy.setHeightForWidth(pushButtonPoint->sizePolicy().hasHeightForWidth());
        pushButtonPoint->setSizePolicy(sizePolicy);
        pushButtonPoint->setStyleSheet(QStringLiteral(""));

        gridLayout_2->addWidget(pushButtonPoint, 3, 0, 1, 2);

        gridLayout_2->setRowStretch(0, 30);
        gridLayout_2->setRowStretch(1, 30);
        gridLayout_2->setRowStretch(2, 18);
        gridLayout_2->setRowStretch(3, 42);
        gridLayout_2->setRowStretch(4, 5);
        gridLayout_2->setRowStretch(5, 5);
        gridLayout_2->setRowStretch(6, 5);

        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0));
        pushButtonMinus->setText(QApplication::translate("Form", "Minus:", 0));
        labelMinus->setText(QString());
        pushButtonFo->setText(QApplication::translate("Form", "Fo:", 0));
        labelFo->setText(QString());
        pushButtonEx->setText(QApplication::translate("Form", "Ex:", 0));
        labelEx->setText(QString());
        labelRegion->setText(QApplication::translate("Form", "Region", 0));
        labelFIO->setText(QApplication::translate("Form", "Name", 0));
        pushButtonPoint->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
