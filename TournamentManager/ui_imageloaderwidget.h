/********************************************************************************
** Form generated from reading UI file 'imageloaderwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGELOADERWIDGET_H
#define UI_IMAGELOADERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "imageloaderwidget.h"

QT_BEGIN_NAMESPACE

class Ui_ImageLoaderWidget
{
public:
    QHBoxLayout *horizontalLayout;
    ImageLoader *frame;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *ImageLoaderWidget)
    {
        if (ImageLoaderWidget->objectName().isEmpty())
            ImageLoaderWidget->setObjectName(QStringLiteral("ImageLoaderWidget"));
        ImageLoaderWidget->resize(506, 314);
        ImageLoaderWidget->setFocusPolicy(Qt::StrongFocus);
        ImageLoaderWidget->setAutoFillBackground(true);
        horizontalLayout = new QHBoxLayout(ImageLoaderWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        frame = new ImageLoader(ImageLoaderWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFocusPolicy(Qt::StrongFocus);

        horizontalLayout->addWidget(frame);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pushButton_2 = new QPushButton(ImageLoaderWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);
        pushButton_2->setFocusPolicy(Qt::StrongFocus);

        verticalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(ImageLoaderWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setFocusPolicy(Qt::StrongFocus);

        verticalLayout->addWidget(pushButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(ImageLoaderWidget);

        QMetaObject::connectSlotsByName(ImageLoaderWidget);
    } // setupUi

    void retranslateUi(QWidget *ImageLoaderWidget)
    {
        pushButton_2->setText(QApplication::translate("ImageLoaderWidget", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214..", 0));
        pushButton->setText(QApplication::translate("ImageLoaderWidget", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", 0));
        Q_UNUSED(ImageLoaderWidget);
    } // retranslateUi

};

namespace Ui {
    class ImageLoaderWidget: public Ui_ImageLoaderWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGELOADERWIDGET_H
