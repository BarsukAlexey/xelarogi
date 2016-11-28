/********************************************************************************
** Form generated from reading UI file 'soundplayer.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOUNDPLAYER_H
#define UI_SOUNDPLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SoundPlayer
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonOpen;
    QPushButton *pushButtonPlay;
    QPushButton *pushButtonStop;
    QPushButton *pushButtonDelete;
    QSlider *sliderVolume;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelCurrent;
    QSlider *sliderPosition;
    QLabel *labelRemain;
    QLabel *labelPath;

    void setupUi(QWidget *SoundPlayer)
    {
        if (SoundPlayer->objectName().isEmpty())
            SoundPlayer->setObjectName(QStringLiteral("SoundPlayer"));
        SoundPlayer->resize(324, 154);
        SoundPlayer->setAutoFillBackground(true);
        gridLayout = new QGridLayout(SoundPlayer);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButtonOpen = new QPushButton(SoundPlayer);
        pushButtonOpen->setObjectName(QStringLiteral("pushButtonOpen"));

        horizontalLayout->addWidget(pushButtonOpen);

        pushButtonPlay = new QPushButton(SoundPlayer);
        pushButtonPlay->setObjectName(QStringLiteral("pushButtonPlay"));

        horizontalLayout->addWidget(pushButtonPlay);

        pushButtonStop = new QPushButton(SoundPlayer);
        pushButtonStop->setObjectName(QStringLiteral("pushButtonStop"));

        horizontalLayout->addWidget(pushButtonStop);

        pushButtonDelete = new QPushButton(SoundPlayer);
        pushButtonDelete->setObjectName(QStringLiteral("pushButtonDelete"));

        horizontalLayout->addWidget(pushButtonDelete);

        sliderVolume = new QSlider(SoundPlayer);
        sliderVolume->setObjectName(QStringLiteral("sliderVolume"));
        sliderVolume->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(sliderVolume);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelCurrent = new QLabel(SoundPlayer);
        labelCurrent->setObjectName(QStringLiteral("labelCurrent"));

        horizontalLayout_2->addWidget(labelCurrent);

        sliderPosition = new QSlider(SoundPlayer);
        sliderPosition->setObjectName(QStringLiteral("sliderPosition"));
        sliderPosition->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(sliderPosition);

        labelRemain = new QLabel(SoundPlayer);
        labelRemain->setObjectName(QStringLiteral("labelRemain"));

        horizontalLayout_2->addWidget(labelRemain);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        labelPath = new QLabel(SoundPlayer);
        labelPath->setObjectName(QStringLiteral("labelPath"));

        gridLayout->addWidget(labelPath, 0, 0, 1, 1);


        retranslateUi(SoundPlayer);

        QMetaObject::connectSlotsByName(SoundPlayer);
    } // setupUi

    void retranslateUi(QWidget *SoundPlayer)
    {
        SoundPlayer->setWindowTitle(QApplication::translate("SoundPlayer", "Form", 0));
        pushButtonOpen->setText(QApplication::translate("SoundPlayer", "Open", 0));
        pushButtonPlay->setText(QString());
        pushButtonStop->setText(QString());
        pushButtonDelete->setText(QApplication::translate("SoundPlayer", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", 0));
        labelCurrent->setText(QApplication::translate("SoundPlayer", "TextLabel", 0));
        labelRemain->setText(QApplication::translate("SoundPlayer", "TextLabel", 0));
        labelPath->setText(QApplication::translate("SoundPlayer", "#", 0));
    } // retranslateUi

};

namespace Ui {
    class SoundPlayer: public Ui_SoundPlayer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOUNDPLAYER_H
