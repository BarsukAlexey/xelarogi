#include "mainwindow.h"
#include "fighting_table.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>

#include <QMediaPlayer>
#include <QMediaPlaylist>
//#include <QVideoWidget>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
}
