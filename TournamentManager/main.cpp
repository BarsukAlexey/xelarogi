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
using namespace std;

int main(int argc, char *argv[])
{
    //qInstallMessageHandler(crashMessageOutput);

    QApplication a(argc, argv);

//    vector<int> arr;
//    for (int i = 1; i <= 251; ++i) arr.push_back(60 + rand() % 1500);
//    for (int i = 1; i <= 251; ++i) arr.push_back(60 + rand() % 40);
//    std::random_shuffle(arr.begin(), arr.end());
//    for (int i = 0; i < (int)arr.size(); ++i) qDebug() << i << arr[i];
//    MyThread *aa = new MyThread(arr, 5, 100000000);
//    aa->start();
//    aa->wait(1 * 1000);
//    aa->setStop();
//    aa->wait();
//    std::vector<int> cnt = aa->ans;
//    qDebug() << "sum: " << std::accumulate(arr.begin(), arr.end(), 0);
//    qDebug() << "sumC: " << std::accumulate(cnt.begin(), cnt.end(), 0);
//    qDebug() << cnt.size();
//    for (int i = 0; i < (int)cnt.size(); ++i)
//        qDebug() << i << ") " << cnt[i];
//    delete aa;


    MainWindow w;
    w.show();

    return a.exec();
}
