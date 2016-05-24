#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "fighting_table.h"

#include <QHeaderView>
#include <QStringList>
#include <QDialog>
#include <QDesktopWidget>
#include "forma_dvertisement.h"
#include "form_advertisement_setting.h"
#include "logindialog.h"
#include <QDateTime>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    while (true)
    {
        LoginDialog loginDialog(this);
        if (loginDialog.exec() == QDialog::Accepted)
        {
            break;
        }
        if (!LoginDialog::mOkBtnClicked)
        {
            exit(0);
        }
        else
        {
            QMessageBox::warning(this, "Неудачная попытка авторизации", "Логи или пароль введены неверно");
        }
    }


    ui->setupUi(this);


    QJsonDocument JSON = loadJSON(nameSettingFile);
    if (JSON.isObject())
    {
        QJsonObject object = JSON.object();
        showAdvertisement = object["showAdvertisement"].toBool(showAdvertisement);
        classicSkin = object["classicSkin"].toBool(classicSkin);
        int interval = object["interval"].toInt(15);
        advTimer.setInterval(1000 * interval);
        advTimer.start();
    }
    else
    {
        showAdvertisement = true;
        classicSkin = true;
        advTimer.setInterval(1000 * 15);
        advTimer.start();
    }

    for (int i = 0; i < QApplication::desktop()->screenCount(); ++i)
    {
        QRect screenres = QApplication::desktop()->screenGeometry(i);
        if (screenres == QApplication::desktop()->screenGeometry(-1))
            continue;
        FormAdvertisement *formAdvertisement = new FormAdvertisement(this);
        formsForAdvertisement << formAdvertisement;
        formAdvertisement->move(QPoint(screenres.x(), screenres.y()));
        formAdvertisement->resize(screenres.width(), screenres.height());
        formAdvertisement->showFullScreen();
        formAdvertisement->show();
    }


    updateAdvertisement();

    update();

    connect(&advTimer, &QTimer::timeout, this, &MainWindow::updateAdvertisement);

    connect(ui->actionLoad_data, &QAction::triggered, [this] () {
        QString path = QFileDialog::getOpenFileName(this);
        if (path.isNull()) return;
        {
            QFileInfo fileInfo(nameSaveFile);
            if (fileInfo.exists() && fileInfo.isFile() &&
                QMessageBox::StandardButton::Ok != QMessageBox::warning(this, "", "If you load new data  you lose old data.\nContinue and lose old data?", QMessageBox::StandardButton::Ok, QMessageBox::StandardButton::Abort))
            {
                return;
            }
        }
        QFile(nameSaveFile).remove();
        QFile::copy(path, nameSaveFile);
        update();
    });

    connect(ui->actionExport_results, &QAction::triggered, [this] () {
        QFile file(nameSaveFile);
        if (!file.exists()) return;

        QString path = QFileDialog::getExistingDirectory(this);
        if (path.isNull()) return;
        path = QDir::toNativeSeparators(path);
        if (!path.endsWith(QDir::separator())) path += QDir::separator();
        path = QDir::toNativeSeparators(path);
        path += "Results " + QDateTime::currentDateTime().toString("hh.mm__dd.MM.yyyy") + ".json";

        if (!file.copy(path))
            QMessageBox::warning(this, "", "Can't save file as " + path + "\n\n" + file.errorString());
    });

    connect(ui->actionAdv, &QAction::triggered, [this] () {
        FormAdvertisementSetting dlg(this, advTimer.interval() / 1000, showAdvertisement, classicSkin);
        if (dlg.exec() == QDialog::Accepted)
        {
            if (advTimer.interval() != 1000 * dlg.getTime())
                advTimer.setInterval(1000 * dlg.getTime());

            if (showAdvertisement != dlg.showAdvertisement())
            {
                showAdvertisement = dlg.showAdvertisement();
                updateAdvertisement();
            }

            classicSkin = dlg.getClassicSkin();

            QJsonObject object;
            object["showAdvertisement"] = showAdvertisement;
            object["classicSkin"] = classicSkin;
            object["interval"] = advTimer.interval() / 1000;


            QFile saveFile(nameSettingFile);
            saveFile.open(QIODevice::WriteOnly);
            saveFile.write(QJsonDocument(object).toJson());
            saveFile.close();
        }
    });

    connect(ui->pushButtonGo, &QPushButton::clicked, [this]() {
        if (!ui->tableWidget->selectionModel()->selectedRows().size())
        {
            QMessageBox::warning(this, "", "Select pair of fighters");
            return;
        }

        int row = ui->tableWidget->selectionModel()->selectedRows()[0].row();
        bool canStart = ui->tableWidget->item(row, 6)->data(Qt::UserRole).toBool();
        if (!canStart)
        {
            QMessageBox::warning(this, "", "Played");
            return;
        }



        Fighting * fighting = new Fighting(
                    ui->tableWidget->item(row,  8)->data(Qt::DisplayRole).toInt(),
                    ui->tableWidget->item(row,  9)->data(Qt::DisplayRole).toInt(),
                    ui->tableWidget->item(row,  10)->data(Qt::DisplayRole).toInt(),
                    ui->tableWidget->item(row,  11)->data(Qt::DisplayRole).toInt()
                    );


        QString nameLeft    = ui->tableWidget->item(row,  1)->data(Qt::DisplayRole).toString();
        QString regionLeft  = ui->tableWidget->item(row,  2)->data(Qt::DisplayRole).toString();
        QString nameRight   = ui->tableWidget->item(row,  3)->data(Qt::DisplayRole).toString();
        QString regionRight = ui->tableWidget->item(row,  4)->data(Qt::DisplayRole).toString();
        QImage leftFlag  = flags[row][0];
        QImage rightFlag = flags[row][1];

        if (classicSkin)
        {
            FightingTable *tableForJudge = 0;
            QVector<FightingTable *> tableForSpectators;
            for (int i = 0; i < QApplication::desktop()->screenCount(); ++i)
            {
                QRect screenres = QApplication::desktop()->screenGeometry(i);
                if (screenres == QApplication::desktop()->screenGeometry(-1))
                {
                    tableForJudge = new FightingTable(fighting, nameLeft, regionLeft, nameRight, regionRight, leftFlag, rightFlag, true, showAdvertisement);
                    tableForJudge->move(QPoint(screenres.x(), screenres.y()));
                }
                else
                {
                    tableForSpectators << new FightingTable(fighting, nameLeft, regionLeft, nameRight, regionRight, leftFlag, rightFlag, false, showAdvertisement);
                    tableForSpectators.back()->move(QPoint(screenres.x(), screenres.y()));
                    tableForSpectators.back()->resize(screenres.width(), screenres.height());
                    tableForSpectators.back()->showFullScreen();

                }
            }
            this->hide();
            for (FightingTable* t : tableForSpectators)
                t->show();
            tableForJudge->showMaximized();
            tableForJudge->exec();
            for (FightingTable* t : tableForSpectators)
                t->hide();
            this->show();

            delete tableForJudge;
            for (FightingTable* t : tableForSpectators)
                delete t;
        }
        else
        {
            QString category = ui->tableWidget->item(row,  0)->data(Qt::DisplayRole).toString() + ". " + ui->tableWidget->item(row,  7)->data(Qt::DisplayRole).toString();
            FightingTable2 *tableForJudge = 0;
            QVector<FightingTable2 *> tableForSpectators;
            for (int i = 0; i < QApplication::desktop()->screenCount(); ++i)
            {
                QRect screenres = QApplication::desktop()->screenGeometry(i);
                if (screenres == QApplication::desktop()->screenGeometry(-1))
                {
                    tableForJudge = new FightingTable2(fighting, category, nameLeft, regionLeft, nameRight, regionRight, leftFlag, rightFlag, true, showAdvertisement);
                    tableForJudge->move(QPoint(screenres.x(), screenres.y()));
                }
                else
                {
                    tableForSpectators << new FightingTable2(fighting, category, nameLeft, regionLeft, nameRight, regionRight, leftFlag, rightFlag, false, showAdvertisement);
                    tableForSpectators.back()->move(QPoint(screenres.x(), screenres.y()));
                    tableForSpectators.back()->resize(screenres.width(), screenres.height());
                    tableForSpectators.back()->showFullScreen();

                }
            }
            this->hide();
            for (FightingTable2* t : tableForSpectators)
                t->show();
            tableForJudge->showMaximized();
            tableForJudge->exec();
            for (FightingTable2* t : tableForSpectators)
                t->hide();
            this->show();

            delete tableForJudge;
            for (FightingTable2* t : tableForSpectators)
                delete t;
        }




        QString winner;
        int winnerUID;
        QStringList winnerKeys;
        if      (fighting->getWinner() == Fighting::Player::Left){
            winner    = ui->tableWidget->item(row, 1)->data(Qt::DisplayRole).toString();
            winnerUID = ui->tableWidget->item(row, 1)->data(Qt::UserRole).toLongLong();
            winnerKeys << "nameOfLeftFighter" << "orderUID_left" << "regionOfLeftFighter" << "leftFlag";
        }
        else if (fighting->getWinner() == Fighting::Player::Right){
            winner    = ui->tableWidget->item(row, 3)->data(Qt::DisplayRole).toString();
            winnerUID = ui->tableWidget->item(row, 3)->data(Qt::UserRole).toLongLong();
            winnerKeys << "nameOfRightFighter" << "orderUID_right" << "regionOfRightFighter" << "rightFlag";
        }
        else
        {
            delete fighting;
            return;
        }

        QJsonDocument doc = loadJSON(nameSaveFile);
        QJsonArray array = doc.array();
        QJsonObject object = array.at(row).toObject();
        object["winner"] = winner;
        object["orderUID"] = winnerUID;
        object["result"] = fighting->getResult();
        array.removeAt(row);
        array.insert(row, object);
        int TOURNAMENT_CATEGORIES_FK = object["TOURNAMENT_CATEGORIES_FK"].toInt();
        int VERTEX = object["VERTEX"].toInt();
        for (int i = 0; i < array.size(); ++i)
        {
            QJsonObject currentObject = array.at(i).toObject();
            if (currentObject["TOURNAMENT_CATEGORIES_FK"].toInt() == TOURNAMENT_CATEGORIES_FK &&
                currentObject["VERTEX"                  ].toInt() == VERTEX / 2){

                int pos = 0;
                for (QString key : {VERTEX % 2? "nameOfLeftFighter"    : "nameOfRightFighter",
                                    VERTEX % 2? "orderUID_left"        : "orderUID_right",
                                    VERTEX % 2? "regionOfLeftFighter"  : "regionOfRightFighter",
                                    VERTEX % 2? "leftFlag"             : "rightFlag"})
                {
                    currentObject[key] = object[winnerKeys[pos++]];
                }
                array.removeAt(i);
                array.insert(i, currentObject);
            }
        }

        QFile saveFile(nameSaveFile);
        saveFile.open(QIODevice::WriteOnly);
        saveFile.write(QJsonDocument(array).toJson());
        saveFile.close();

        delete fighting;

        update();
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}


QJsonDocument MainWindow::loadJSON(const QString& path)
{
    QFile loadFile(path);
    if (!loadFile.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open save file.");
        return QJsonDocument();
    }
    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    loadFile.close();
    return loadDoc;
}

void MainWindow::update()
{
    QJsonDocument doc = loadJSON(nameSaveFile);
    QJsonArray array = doc.array();
    ui->tableWidget->setRowCount(array.size());
    QStringList heads({"Fight #", "Red conner", "Country/Region", "Blue conner", "Country/Region", "Winner", "Can start?", "Tournament Categoty", "Duration of fight", "Duration of break", "Count of rounds", "Duration of extra round"});
    ui->tableWidget->setColumnCount(heads.size());
    ui->tableWidget->setHorizontalHeaderLabels(heads);
    flags.clear();
    for (int i = 0; i < array.size(); ++i)
    {
        QTableWidgetItem *item;
        int column = 0;
        QJsonObject object = array.at(i).toObject();

        item = new QTableWidgetItem(QString::number(object["fightId"].toInt()));
        ui->tableWidget->setItem(i, column++, item);

        item = new QTableWidgetItem(object["nameOfLeftFighter"].toString());
        item->setData(Qt::UserRole, object["orderUID_left"].toInt());
        ui->tableWidget->setItem(i, column++, item);

        item = new QTableWidgetItem(object["regionOfLeftFighter"].toString());
        ui->tableWidget->setItem(i, column++, item);

        item = new QTableWidgetItem(object["nameOfRightFighter"].toString());
        item->setData(Qt::UserRole, object["orderUID_right"].toInt());
        ui->tableWidget->setItem(i, column++, item);

        item = new QTableWidgetItem(object["regionOfRightFighter"].toString());
        ui->tableWidget->setItem(i, column++, item);

        QString winner = object["winner"].toString();
        QString result = object["result"].toString();
        if (!result.isEmpty())
            ui->tableWidget->setItem(i, column++, new QTableWidgetItem(winner + " (" + result + ")"));
        else
            ui->tableWidget->setItem(i, column++, new QTableWidgetItem(winner));

        bool canStart = 0 < object["orderUID_left"].toInt() && 0 < object["orderUID_right"].toInt() && !object["orderUID"].toInt(0);
        //qDebug() << i << object["orderUID_left"].toInt() << object["orderUID_right"].toInt() << canStart << column;
        item = new QTableWidgetItem(canStart? "Yes" : "No");
        item->setData(Qt::UserRole, QVariant(canStart));
        ui->tableWidget->setItem(i, column++, item);

        ui->tableWidget->setItem(i, column++, new QTableWidgetItem(object["categoryOfFighting"].toString()));
        ui->tableWidget->setItem(i, column++, new QTableWidgetItem(object["durationOfRound"].toString()));
        ui->tableWidget->setItem(i, column++, new QTableWidgetItem(object["durationOfBreak"].toString()));
        ui->tableWidget->setItem(i, column++, new QTableWidgetItem(object["countOfRounds"].toString()));


        flags << QVector<QImage>();
        QImage a = QImage::fromData(QByteArray::fromBase64(object["leftFlag" ].toString().toStdString().c_str()));
        QImage b = QImage::fromData(QByteArray::fromBase64(object["rightFlag"].toString().toStdString().c_str()));
        if (!a.isNull()) a = a.scaledToHeight(200);
        if (!b.isNull()) b = b.scaledToHeight(200);
        flags.back() << a << b;

        ui->tableWidget->setItem(i, column++, new QTableWidgetItem(QString::number(object["DURATION_EXTRA_ROUND"].toInt())));
    }
    ui->tableWidget->resizeColumnsToContents();
}



void MainWindow::updateAdvertisement()
{
    QImage img;
    if (!showAdvertisement)
    {
        QPixmap pm(1, 1);
        pm.fill(Qt::transparent);
        img = pm.toImage();
    }
    else
    {
        QDir dir(QString(".") + QDir::separator() + "advertisement");

        QVector<QString>::iterator it = images.begin();
        while (it != images.end())
        {
            QFileInfo fileInfo(*it);
            if (!fileInfo.exists())
                it = images.erase(it);
            else
                ++it;
        }

        for (QFileInfo fileInfo : dir.entryInfoList())
        {
            if (fileInfo.isFile() && !images.contains(fileInfo.absoluteFilePath()))
            {
                QImage img(fileInfo.absoluteFilePath());
                if (!img.isNull())
                {
                    images << fileInfo.absoluteFilePath();
                }
            }
        }

        posImage = qMax(0, qMin(posImage, images.size()));
        if (posImage == images.size()) posImage = 0;
        img = QImage(images[posImage++]);
    }

    for (FormAdvertisement *f : formsForAdvertisement)
    {
        f->setImage(img);
    }
}
