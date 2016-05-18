#include "mainwindow.h"
#include "fighting_table.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "aspect_ratio_pixmap_label.h"
#include "aspectratiotextlabel.h"

#include <QLCDNumber>
#include "myqlcdnumber.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    QPixmap map(".\\resources\\images\\images.jpg");
//    AspectRatioPixmapLabel* lbl = new AspectRatioPixmapLabel();
//    lbl->setPixmap(map);
//    lbl->show();

//    AspectRatioTextLabel* lbl = new AspectRatioTextLabel();
//    lbl->show();

//    MyQLCDNumber* lcd = new MyQLCDNumber();
//    lcd->show();
//    lcd->resize(100, 100);



    return a.exec();
}
