#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(DialogAwardWidget* awardPanel, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    awardPanel(awardPanel)
{
    ui->setupUi(this);

    currentRow = - 1;
    shown.clear();
    shown.resize(4);

    //on_actionLoadData_triggered();

    model = new QFileSystemModel(this);
    QString path = QDir(QDir::currentPath()).filePath("music");
    model->setRootPath(path);
    model->setFilter(QDir::Files);
    //qDebug() << path;
    ui->treeViewMusic->setModel(model);
    ui->treeViewMusic->setRootIndex(model->index(path));

    for (int i = 1; i < model->columnCount(); ++i)
        ui->treeViewMusic->hideColumn(i);

    loadData("award.dat");


    QShortcut* shortcut = new QShortcut(QKeySequence(Qt::Key_Space), this);
    connect(shortcut, &QShortcut::activated, this, &MainWindow::onPressSpace);
    connect(ui->tableWidget, &QTableWidget::itemSelectionChanged, this, &MainWindow::onSelectionChanged);
    connect(ui->treeViewMusic->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::onMusicSelectionChanged);

    connect(ui->soundPlayer, &SoundPlayer::iPlayMusic, ui->soundPlayerHymn, &SoundPlayer::onSomePlayerStarPlayMusic);
    connect(ui->soundPlayerHymn, &SoundPlayer::iPlayMusic, ui->soundPlayer, &SoundPlayer::onSomePlayerStarPlayMusic);

    connect(ui->soundPlayer, &SoundPlayer::giveMeNextMusic, this, &MainWindow::onGiveMeNextMusic);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLoadData_triggered()
{
    QString openFileName = QFileDialog::getOpenFileName(this);
    //QString openFileName = "C:\\Users\\User\\Saved Games\\Desktop\\award.dat";
    QFile::copy(openFileName, "award.dat");
    loadData("award.dat");




}

void MainWindow::onSelectionChanged()
{
    QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
    if (items.isEmpty())
    {
        currentRow = - 1;
        shown.clear();
        shown.resize(4);
        awardPanel->resetAll();
        ui->soundPlayerHymn->setRawData(QByteArray());
        ui->soundPlayerHymn->setTitle("#");
        return ;
    }

    if (currentRow == items[0]->row())
        return;

    currentRow = items[0]->row();
    shown.clear();
    shown.resize(4);
    awardPanel->resetAll();
    awardPanel->setTournamentCategory(TCs[currentRow]);
    ui->soundPlayerHymn->setRawData(mapHymn[hymns[currentRow][0]]);
    ui->soundPlayerHymn->setTitle(mapNames[names[currentRow][0]]);
}

void MainWindow::onPressSpace()
{
    if (currentRow == -1)
        return;
    int countPlayers = players[currentRow].size();
    if (ui->radioButtonFrom1To3->isChecked())
    {
        for (int i = 0; i < countPlayers; ++i)
        {
            if (!shown[i])
            {
                showPlayer(i);
                return;
            }
        }
    }
    else
    {
        qDebug() << "from 3 to 1";
        for (int i = countPlayers - 1; 0 <= i; --i)
        {
            if (!shown[i])
            {
                showPlayer(i);
                return;
            }
        }
    }
}



void MainWindow::on_pushButtonAll_clicked()
{
    if (currentRow == -1)
        return;
    int countPlayers = players[currentRow].size();
    for (int i = 0; i < countPlayers; ++i)
    {
        showPlayer(i);
    }
}


void MainWindow::on_pushButtonI_clicked()
{
    showPlayer(0);
}

void MainWindow::on_pushButtonII_clicked()
{
    showPlayer(1);
}

void MainWindow::on_pushButtonIII_clicked()
{
    showPlayer(2);
}

void MainWindow::on_pushButtonIV_clicked()
{
    showPlayer(3);
}

void MainWindow::showPlayer(int player)
{
    if (currentRow == -1)
        return;
    if (!shown[player])
    {
        shown[player] = true;
        awardPanel->setPlayer(player,
                              players       [currentRow][player],
                              mapNames[names[currentRow][player]],
                              mapFlag [flags[currentRow][player]]);
    }
}

void MainWindow::loadData(const QString& openFileName)
{
    QFile file(openFileName);
    if (!file.open(QIODevice::ReadOnly))
        return;
    QDataStream dataStream(&file);


    QByteArray widgetAwardData;


    dataStream
        >> widgetAwardData
        >> TCs
        >> players
        >> names
        >> flags
        >> hymns
        >> mapNames
        >> mapFlag
        >> mapHymn;

    if (dataStream.status() == QDataStream::ReadCorruptData)
    {
        qDebug() << "still doesnt work";
    }
    //qDebug() << "status read data:" << dataStream.status();

    for (int i = 0; i < TCs.size(); ++i)
    {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount(row + 1);

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(TCs[i]));
        for (int j = 0; j < players[i].size(); ++j)
            ui->tableWidget->setItem(row, j + 1, new QTableWidgetItem(players[i][j]));

    }
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();

    awardPanel->setData(widgetAwardData);
}



void MainWindow::closeEvent(QCloseEvent* event)
{
    awardPanel->hide();
    event->accept();
}



void MainWindow::onMusicSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
    if (selected.indexes().isEmpty())
        return;
    QModelIndex index = selected.indexes()[0];

    QString path = model->filePath(index);
    //qDebug() << "load:" << path;

    ui->soundPlayer->loadMusic(path, true);
}

void MainWindow::onGiveMeNextMusic()
{
    QModelIndex index = ui->treeViewMusic->currentIndex();
    QModelIndex nextIndex = ui->treeViewMusic->indexBelow(index);
    ui->treeViewMusic->
            selectionModel()->
            setCurrentIndex(nextIndex,
                            QItemSelectionModel::SelectCurrent);
}
