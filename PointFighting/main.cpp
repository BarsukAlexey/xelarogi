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
#include <QPixmap>
#include <QImage>
#include "myqlcdnumber.h"
#include "formscore.h"
#include "qrightclickbutton.h"
#include "fightingtable2.h"
#include "fighting.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


//    Fighting* f = new Fighting(10, 13, 2, 15);

//    FightingTable2 ft(f,
//                                            "3. ACM ICPC. +50",
//                                            "Петр Митрич", "Псковская",
//                                            "Геннадий Короткевич", "ИТМО",
//                                            QImage(".\\resources\\images\\Canada.png"),
//                                            QImage(".\\resources\\images\\Switzerland.png"),
//                                            1,
//                                            false
//                                            //true,
//                                            //true
//                                            );

//    FightingTable2 ft2(f,
//                                            "3. ACM ICPC. +50",
//                                            "Петр Митрич", "Псковская",
//                                            "Геннадий Короткевич", "ИТМО",
//                                            QImage(".\\resources\\images\\Canada.png"),
//                                            QImage(".\\resources\\images\\Switzerland.png"),
//                                            0,
//                                            false
//                                            //true,
//                                            //true
//                                            );
//    ft2.show();
//    ft.show();
//    ft.exec();

//    ft2.hide();

//    ft->close();
//    ft2->close();

//    delete f;

    //ft->hide();

    MainWindow w;
//    w.show();
    w.showMaximized();

//    QRightClickButton* b = new QRightClickButton();
//    b->show();
//    b->setText("asda");


//    FormScore* fc = new FormScore("Vasya", "Russina", QImage(".\\resources\\images\\images.jpg"), QColor(Qt::blue));
//    fc->show();
//    Form22* f = new Form22();
//    f->show();



//    FightingTable* ft = new FightingTable(0, "Иван Иванов", "Санкт-Петербург", "Пётр Петров", "Махачкала", QImage(".\\resources\\images\\Canada.png"), QImage(".\\resources\\images\\Switzerland.png"), true, true);
//    ft->show();

//    tempForm* tf = new tempForm();
//    tf->show();


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
