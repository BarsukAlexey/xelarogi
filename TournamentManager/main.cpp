#include "mainwindow.h"
#include <QApplication>

//#include <qapplication.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <QDebug>
//#include <QtGlobal>
//#include <QtGui>
//#include <QtGlobal>
//#include <QApplication>


//void crashMessageOutput(QtMsgType type, const QMessageLogContext &, const QString & msg)
//{
//   FILE *file; // указатель на файл, в который пишем
//   file = fopen("file.log", "a"); // открываем файл на запись
//    switch (type) {
//    case QtDebugMsg:
//        fprintf(file, "Debug: %s\n", msg.toStdString().c_str());
//        break;
//    case QtWarningMsg:
//        fprintf(file, "Warning: %s\n", msg.toStdString().c_str());
//        break;
//    case QtCriticalMsg:
//        fprintf(file, "Critical: %s\n", msg.toStdString().c_str());
//        break;
//    case QtFatalMsg:
//        fprintf(file, "Fatal: %s\n", msg.toStdString().c_str());
//        abort();
//    }
//   fclose(file); // закрываем файл
//}
#include "mythread.h"
#include <vector>
#include <QFontDialog>
using namespace std;

int main(int argc, char *argv[])
{
    //qInstallMessageHandler(crashMessageOutput);

    QApplication a(argc, argv);


    QFontDialog * dlg = new QFontDialog;
    dlg->exec();
    dlg->selectedFont();



//    MainWindow w;
//    w.show();

    return a.exec();
}
