#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "fighting_table.h"

#include <QHeaderView>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionLoad_data, &QAction::triggered, [this] () {
        QString path = QFileDialog::getOpenFileName(this);
        if (path.isNull()) return;

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
        path += "Results " + QDateTime::currentDateTime().toString("hh.ss__dd.MM.yyyy") + ".json";

        if (!file.copy(path))
            QMessageBox::warning(this, "", "Can't save file as " + path + "\n\n" + file.errorString());
    });

    connect(ui->pushButtonGo, &QPushButton::clicked, [this]() {
        if (!ui->tableWidget->selectionModel()->selectedRows().size())
            return;

        int row = ui->tableWidget->selectionModel()->selectedRows()[0].row();
        bool canStart = ui->tableWidget->item(row, 6)->data(Qt::UserRole).toBool();
        if (!canStart)
            return;

        FightingTable f(this,
                        ui->tableWidget->item(row,  1)->data(Qt::DisplayRole).toString(),
                        ui->tableWidget->item(row,  2)->data(Qt::DisplayRole).toString(),
                        ui->tableWidget->item(row,  3)->data(Qt::DisplayRole).toString(),
                        ui->tableWidget->item(row,  4)->data(Qt::DisplayRole).toString(),

                        ui->tableWidget->item(row,  8)->data(Qt::DisplayRole).toInt(),
                        ui->tableWidget->item(row,  9)->data(Qt::DisplayRole).toInt(),
                        ui->tableWidget->item(row, 10)->data(Qt::DisplayRole).toInt()
                        );
        f.exec();
        if (f.status != FightingTable::Status::Finish)
            return;

        QString winner;
        int winnerUID;
        if      (f.countPointLeft > f.countPointRight){
            winner    = ui->tableWidget->item(row, 1)->data(Qt::DisplayRole).toString();
            winnerUID = ui->tableWidget->item(row, 1)->data(Qt::UserRole).toLongLong();
        }
        else if (f.countPointLeft < f.countPointRight){
            winner    = ui->tableWidget->item(row, 3)->data(Qt::DisplayRole).toString();
            winnerUID = ui->tableWidget->item(row, 3)->data(Qt::UserRole).toLongLong();
        }
        else
            return;


        QJsonDocument doc = loadJSON();
        QJsonArray array = doc.array();
        QJsonObject object = array.at(row).toObject();
        object["winner"] = winner;
        object["winnerUID"] = winnerUID;
        array.removeAt(row);
        array.insert(row, object);
        int TOURNAMENT_CATEGORIES_FK = object["TOURNAMENT_CATEGORIES_FK"].toInt();
        int VERTEX = object["VERTEX"].toInt();
        for (int i = 0; i < array.size(); ++i)
        {
            QJsonObject currentObject = array.at(i).toObject();
            if (currentObject["TOURNAMENT_CATEGORIES_FK"].toInt() == TOURNAMENT_CATEGORIES_FK &&
                currentObject["VERTEX"                  ].toInt() == VERTEX / 2){

                for (QString key : {VERTEX % 2? "countryOfLeftFighter" : "countryOfRightFighter",
                                    VERTEX % 2? "nameOfLeftFighter"    : "nameOfRightFighter",
                                    VERTEX % 2? "orderUID_left"        : "orderUID_right",
                                    VERTEX % 2? "regionOfLeftFighter"  : "regionOfRightFighter"})
                {
                    currentObject[key] = object[key];
                }
                array.removeAt(i);
                array.insert(i, currentObject);
            }
        }

        QFile saveFile(nameSaveFile);
        if (!saveFile.open(QIODevice::WriteOnly)) {
            qWarning("Couldn't open save file.");
            return;
        }
        saveFile.write(QJsonDocument(array).toJson());
        saveFile.close();

        update();

    });



    update();
    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QJsonDocument MainWindow::loadJSON()
{
    QFile loadFile(nameSaveFile);
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
    QJsonDocument doc = loadJSON();
    QJsonArray array = doc.array();
    ui->tableWidget->setRowCount(array.size());
    QStringList heads({"Fight #", "Red conner", "Country/Region", "Blue conner", "Country/Region", "Winner", "Can start?", "Tournament Categoty", "Duration fight", "Duration break", "Count of rounds"});
    ui->tableWidget->setColumnCount(heads.size());
    ui->tableWidget->setHorizontalHeaderLabels(heads);
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

        item = new QTableWidgetItem(object["countryOfLeftFighter"].toString() + " / " + object["regionOfLeftFighter"].toString());
        ui->tableWidget->setItem(i, column++, item);

        item = new QTableWidgetItem(object["nameOfRightFighter"].toString());
        item->setData(Qt::UserRole, object["orderUID_right"].toInt());
        ui->tableWidget->setItem(i, column++, item);

        item = new QTableWidgetItem(object["countryOfRightFighter"].toString() + " / " + object["regionOfRightFighter"].toString());
        ui->tableWidget->setItem(i, column++, item);

        QString winner = object["winner"].toString();
        ui->tableWidget->setItem(i, column++, new QTableWidgetItem(winner));

        bool canStart = 0 < object["orderUID_left"].toInt() && 0 < object["orderUID_right"].toInt() && !object["winnerUID"].toInt(0);
        //qDebug() << i << object["orderUID_left"].toInt() << object["orderUID_right"].toInt() << canStart << column;
        item = new QTableWidgetItem(canStart? "Yes" : "No");
        item->setData(Qt::UserRole, QVariant(canStart));
        ui->tableWidget->setItem(i, column++, item);

        ui->tableWidget->setItem(i, column++, new QTableWidgetItem(object["categoryOfFighting"].toString()));
        ui->tableWidget->setItem(i, column++, new QTableWidgetItem(object["durationOfRound"].toString()));
        ui->tableWidget->setItem(i, column++, new QTableWidgetItem(object["durationOfBreak"].toString()));
        ui->tableWidget->setItem(i, column++, new QTableWidgetItem(object["countOfRounds"].toString()));
    }
    ui->tableWidget->resizeColumnsToContents();
}
