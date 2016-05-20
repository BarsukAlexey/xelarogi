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
    QHBoxLayout *horizontalLayout_2;
    QRightClickButton *pushButtonMinus;
    AspectRatioTextLabel *labelMinus;
    AspectRatioPixmapLabel *labelFlag;
    AspectRatioTextLabel *labelRegion;
    QRightClickButton *pushButtonPoint;
    QHBoxLayout *horizontalLayout_3;
    QRightClickButton *pushButtonEx;
    AspectRatioTextLabel *labelEx;
    QHBoxLayout *horizontalLayout;
    QRightClickButton *pushButtonFo;
    AspectRatioTextLabel *labelFo;
    AspectRatioTextLabel *labelFIO;

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
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButtonMinus = new QRightClickButton(widget);
        pushButtonMinus->setObjectName(QStringLiteral("pushButtonMinus"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonMinus->sizePolicy().hasHeightForWidth());
        pushButtonMinus->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(14);
        pushButtonMinus->setFont(font);
        pushButtonMinus->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(pushButtonMinus);

        labelMinus = new AspectRatioTextLabel(widget);
        labelMinus->setObjectName(QStringLiteral("labelMinus"));
        labelMinus->setFont(font);
        labelMinus->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        labelMinus->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(labelMinus);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 1);

        gridLayout_2->addLayout(horizontalLayout_2, 4, 0, 1, 1);

        labelFlag = new AspectRatioPixmapLabel(widget);
        labelFlag->setObjectName(QStringLiteral("labelFlag"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelFlag->sizePolicy().hasHeightForWidth());
        labelFlag->setSizePolicy(sizePolicy1);
        labelFlag->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(labelFlag, 1, 0, 1, 1);

        labelRegion = new AspectRatioTextLabel(widget);
        labelRegion->setObjectName(QStringLiteral("labelRegion"));
        QFont font1;
        font1.setPointSize(15);
        labelRegion->setFont(font1);
        labelRegion->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        labelRegion->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(labelRegion, 2, 0, 1, 1);

        pushButtonPoint = new QRightClickButton(widget);
        pushButtonPoint->setObjectName(QStringLiteral("pushButtonPoint"));
        sizePolicy.setHeightForWidth(pushButtonPoint->sizePolicy().hasHeightForWidth());
        pushButtonPoint->setSizePolicy(sizePolicy);
        pushButtonPoint->setStyleSheet(QStringLiteral(""));

        gridLayout_2->addWidget(pushButtonPoint, 3, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        pushButtonEx = new QRightClickButton(widget);
        pushButtonEx->setObjectName(QStringLiteral("pushButtonEx"));
        sizePolicy.setHeightForWidth(pushButtonEx->sizePolicy().hasHeightForWidth());
        pushButtonEx->setSizePolicy(sizePolicy);
        pushButtonEx->setFont(font);

        horizontalLayout_3->addWidget(pushButtonEx);

        labelEx = new AspectRatioTextLabel(widget);
        labelEx->setObjectName(QStringLiteral("labelEx"));
        labelEx->setFont(font);
        labelEx->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        labelEx->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(labelEx);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 1);

        gridLayout_2->addLayout(horizontalLayout_3, 6, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButtonFo = new QRightClickButton(widget);
        pushButtonFo->setObjectName(QStringLiteral("pushButtonFo"));
        sizePolicy.setHeightForWidth(pushButtonFo->sizePolicy().hasHeightForWidth());
        pushButtonFo->setSizePolicy(sizePolicy);
        pushButtonFo->setFont(font);

        horizontalLayout->addWidget(pushButtonFo);

        labelFo = new AspectRatioTextLabel(widget);
        labelFo->setObjectName(QStringLiteral("labelFo"));
        labelFo->setFont(font);
        labelFo->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(labelFo);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);

        gridLayout_2->addLayout(horizontalLayout, 5, 0, 1, 1);

        labelFIO = new AspectRatioTextLabel(widget);
        labelFIO->setObjectName(QStringLiteral("labelFIO"));
        labelFIO->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        labelFIO->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(labelFIO, 0, 0, 1, 1);

        gridLayout_2->setRowStretch(0, 30);
        gridLayout_2->setRowStretch(1, 30);
        gridLayout_2->setRowStretch(2, 15);
        gridLayout_2->setRowStretch(3, 50);
        gridLayout_2->setRowStretch(4, 1);
        gridLayout_2->setRowStretch(5, 1);
        gridLayout_2->setRowStretch(6, 1);

        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0));
        pushButtonMinus->setText(QApplication::translate("Form", "Minus:", 0));
        labelMinus->setText(QString());
        labelRegion->setText(QApplication::translate("Form", "Region", 0));
        pushButtonPoint->setText(QString());
        pushButtonEx->setText(QApplication::translate("Form", "Ex:", 0));
        labelEx->setText(QString());
        pushButtonFo->setText(QApplication::translate("Form", "Fo:", 0));
        labelFo->setText(QString());
        labelFIO->setText(QApplication::translate("Form", "Name", 0));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
