#include "mainwindow.h"
#include "dialogawardpanel.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QMessageBox>
#include <iostream>
#include <ctime>

void break_point(QtMsgType msgType, const QMessageLogContext &, const QString &msg)
{
    if (msgType == QtDebugMsg)
    {
        std::cerr << msg.toStdString() << std::endl;
        return ;
    }
    std::cerr << msg.toStdString() << std::endl;
    return ;
}

void on_terminate()
{
    qDebug() << "on_terminate";
    return ;
}

int main(int argc, char *argv[])
{
    srand(time(0));
    qInstallMessageHandler(break_point);
    std::set_terminate(on_terminate);
    QApplication a(argc, argv);

    DialogAwardWidget panel;
    MainWindow w(&panel);

    if (QApplication::desktop()->screenCount() == 1)
    {
        QMessageBox::warning(0, "", "Закройте эту программу.\n"
                                    "Подключите второй экран (проектор, TV и т.д)\n"
                                    "и запустите эту программу ещё раз.");

        QSize size = QApplication::desktop()->screenGeometry(-1).size();

        panel.show();
        panel.move(size.width() / 2, 0);
        panel.resize(size.width() / 2 - 5, size.height() - 100);

        w.show();
        w.move(0, 0);
        w.resize(size.width()/ 2 - 20, size.height() - 100);

    }
    else
    {
        for (int i = 0; i < QApplication::desktop()->screenCount(); ++i)
        {
            QRect screenres = QApplication::desktop()->screenGeometry(i);
            if (screenres == QApplication::desktop()->screenGeometry(-1))
                continue;

            panel.move(screenres.x(), screenres.y());
            //panel->resize(screenres.width(), screenres.height());
            panel.showFullScreen();
            //formAdvertisement->show();
        }

        w.showMaximized();
    }

    return a.exec();
}
