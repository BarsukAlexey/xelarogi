/********************************************************************************
** Form generated from reading UI file 'webreportdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEBREPORTDIALOG_H
#define UI_WEBREPORTDIALOG_H

#include <QtCore/QVariant>
#include <QtWebKitWidgets/QWebView>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_WebReportDialog
{
public:
    QGridLayout *gridLayout;
    QWebView *webView;

    void setupUi(QDialog *WebReportDialog)
    {
        if (WebReportDialog->objectName().isEmpty())
            WebReportDialog->setObjectName(QStringLiteral("WebReportDialog"));
        WebReportDialog->resize(400, 300);
        gridLayout = new QGridLayout(WebReportDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        webView = new QWebView(WebReportDialog);
        webView->setObjectName(QStringLiteral("webView"));
        webView->setUrl(QUrl(QStringLiteral("about:blank")));

        gridLayout->addWidget(webView, 0, 0, 1, 1);


        retranslateUi(WebReportDialog);

        QMetaObject::connectSlotsByName(WebReportDialog);
    } // setupUi

    void retranslateUi(QDialog *WebReportDialog)
    {
        WebReportDialog->setWindowTitle(QApplication::translate("WebReportDialog", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class WebReportDialog: public Ui_WebReportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEBREPORTDIALOG_H
