#include "mainwindow.h"
#include "ui_mainwindow.h"

TournamentModel::TournamentModel(QObject* parent) :
    QAbstractTableModel(parent)
{
    modelTournament = new QSqlRelationalTableModel(this);
    modelTournament->setTable("TOURNAMENTS");
    selectAndSortData();
}


int TournamentModel::rowCount(const QModelIndex& ) const
{
    return modelTournament->rowCount();
}

int TournamentModel::columnCount(const QModelIndex& ) const
{
    return 1;
}

QVariant TournamentModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        int row = index.row();
        QString name = modelTournament->data(modelTournament->index(row, modelTournament->fieldIndex("NAME"))).toString();
        QString date = modelTournament->data(modelTournament->index(row, modelTournament->fieldIndex("TEXT_DAT_RANGE"))).toString();
        return name + (date.isEmpty()? "" : "\n(" + date + ")");
    }
    return QVariant();
}

QVariant TournamentModel::headerData(int , Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            return "Турнир";
        }
    }
    return QVariant();
}

int TournamentModel::getUID(int row)
{
    return modelTournament->data(modelTournament->index(row, 0)).toInt();
}

void TournamentModel::selectAndSortData()
{
    beginResetModel();
    modelTournament->select();
    while (modelTournament->canFetchMore())
        modelTournament->fetchMore();
    modelTournament->sort(0, Qt::SortOrder::DescendingOrder);
    endResetModel();
}











MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new TournamentModel(this);
    ui->tableViewTournament->setModel(model);
    ui->tableViewTournament->resizeColumnsToContents();
    ui->tableViewTournament->resizeRowsToContents();

    connect(ui->tableViewTournament->selectionModel(),&QItemSelectionModel::selectionChanged,
            [this](const QItemSelection& a, const QItemSelection& ){
        if (a.indexes().isEmpty())
            ui->stackedWidget->setCurrentIndex(0);
        else
        {
            ui->stackedWidget->setCurrentIndex(1);
            int row = a.indexes()[0].row();
            ui->labelTournament->setText(a.indexes()[0].data().toString());
            tournamentUID = model->getUID(row);
        }
    });
    connect(ui->tableViewTournament->model(), &QAbstractItemModel::modelReset, [this](){
        ui->stackedWidget->setCurrentIndex(0);
    });





    connect(ui->tournamentAction, &QAction::triggered, [this](){
        onAction("TOURNAMENTS");
        model->selectAndSortData();
    });

    connect(ui->actionAgeCategory, &QAction::triggered, [this](){
        onAction("AGE_CATEGORIES");
    });
    connect(ui->typeAction, &QAction::triggered, [this](){
        onAction("TYPES");
    });
    connect(ui->sportCategoryAction, &QAction::triggered, [this](){
        onAction("SPORT_CATEGORIES");
    });

    connect(ui->countryAction, &QAction::triggered, [this](){
        onAction("COUNTRIES");
    });
    connect(ui->regionAction, &QAction::triggered, [this](){
        onAction("REGIONS");
    });
    connect(ui->ateAction, &QAction::triggered, [this](){
        onAction("REGION_UNITS");
    });

    connect(ui->clubAction, &QAction::triggered, [this](){
        onAction("CLUBS");
    });
    connect(ui->coachAction, &QAction::triggered, [this](){
        onAction("COACHS");
    });



    connect(ui->pushButtonTournamentCategories, &QPushButton::clicked, [this] ()
    {
        this->hide();
        CreateTournamentCategoriesDialog dlg(tournamentUID, 0);
        dlg.showMaximized();
        dlg.exec();
        this->show();
    });
    connect(ui->pushButtonOrders, &QPushButton::clicked, [this] ()
    {
        this->hide();
        CreateTournamentOrdersDialog dlg(tournamentUID, 0);
        dlg.showMaximized();
        dlg.exec();
        this->show();
    });
    connect(ui->pushButtonGrids, &QPushButton::clicked, [this] ()
    {
        this->hide();
        DialogTournamentGrid dlg(0, "", tournamentUID);
        dlg.showMaximized();
        dlg.exec();
        this->show();
    });
    connect(ui->pushButtonProtokolVzveshinanya, &QPushButton::clicked, [this] ()
    {
        WeighingProtocol w(tournamentUID);
    });
    connect(ui->pushButtonFightDist, &QPushButton::clicked, [this] ()
    {
        this->hide();
        DialogSchedule dlg(0, tournamentUID);
        dlg.showMaximized();
        dlg.exec();
        this->show();
    });
    connect(ui->pushButtonTimeScheduling, &QPushButton::clicked, [this] ()
    {
        this->hide();
        Dialogschedule2 dlg(tournamentUID);
        dlg.showMaximized();
        dlg.exec();
        this->show();
    });
    connect(ui->pushButtonPair, &QPushButton::clicked, [this] ()
    {
        this->hide();
        FightingPairs dlg(tournamentUID);
        dlg.showMaximized();
        dlg.exec();
        this->show();
    });
    connect(ui->trophyBtnImage, &QPushButton::clicked, [this]()
    {
        this->hide();
        FormDipl dlg(tournamentUID);
        dlg.showMaximized();
        dlg.exec();
        this->show();
    });




    connect(ui->pushButtonCountries, &QPushButton::clicked, [this] ()
    {
        onButton("COUNTRY_FK", "COUNTRIES");
    });

    connect(ui->pushButtonRegions, &QPushButton::clicked, [this] ()
    {
        onButton("REGION_FK", "REGIONS");
    });

    connect(ui->pushButtonCities, &QPushButton::clicked, [this] ()
    {
        onButton("REGION_UNIT_FK", "REGION_UNITS");
    });

    connect(ui->pushButtonClubs, &QPushButton::clicked, [this] ()
    {
        onButton("CLUB_FK", "CLUBS");
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAction(QString table)
{
    this->hide();
    DialogSqlTableManager dlg(0, table);
    dlg.showMaximized();
    dlg.exec();
    this->show();
}

void MainWindow::onButton(const QString& field, const QString& table)
{
    this->hide();
    QString filter =
            "UID IN ("
            "SELECT " + field + " "
            "FROM "
            "    ORDERS O "
            "    JOIN TOURNAMENT_CATEGORIES T  "
            "    ON O.TOURNAMENT_CATEGORY_FK = T.UID "
            "WHERE "
            "    T.TOURNAMENT_FK = " + QString::number(tournamentUID) + " "
            "GROUP BY " + field +
            ")";
    DialogSqlTableManager dlg(0, table, filter);
    dlg.showMaximized();
    dlg.exec();
    this->show();
}

void MainWindow::on_pushButtonWinnerReport_clicked()
{
    WinnerReport(tournamentUID, this);
}

void MainWindow::on_pushButtonLoadWinner_clicked()
{
    QString openFileName = QFileDialog::getOpenFileName(this);
    if (openFileName.isEmpty())
        return;

    QFile file(openFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(this, ". . .", "Не возможно откыть файл", QMessageBox::Yes);
        return;
    }
    QJsonDocument d = QJsonDocument::fromJson(QString(file.readAll()).toUtf8());
    file.close();


    int okCount = 0;
    int countSame = 0;
    QStringList errorMessage;
    QJsonArray array = d.array();
    for (int i = 0; i < array.size(); ++i)
    {
        QJsonObject object = array[i].toObject();
        int TOURNAMENT_CATEGORIES_FK = object["TOURNAMENT_CATEGORIES_FK"].toInt();
        int VERTEX         = object["VERTEX"].toInt();
        int orderUID       = object["orderUID"].toInt();
        int orderUID_left  = object["orderUID_left"].toInt();
        int orderUID_right = object["orderUID_right"].toInt();

        QString result = object["result"].toString();


        //qDebug() << TOURNAMENT_CATEGORIES_FK << VERTEX << orderUID;

        QVector<DBUtils::NodeOfTournirGrid> nodes = DBUtils::getNodes(TOURNAMENT_CATEGORIES_FK);


        if (nodes.size() <= 2 * VERTEX + 1 - 1)
        {
            errorMessage +=
                    "Не возможно загрузть результаты для " + DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", TOURNAMENT_CATEGORIES_FK) + "\n"
                    "Пара: " + DBUtils::getSecondNameAndFirstName(orderUID_left) + " VS " + DBUtils::getSecondNameAndFirstName(orderUID_right) + "\n"
                    "Так как сетка была изменена или удалена\n";
            continue;
        }

        if (orderUID_left != nodes[2 * VERTEX + 1 - 1].UID && orderUID_right != nodes[2 * VERTEX - 1].UID){
            errorMessage +=
                    "Не возможно загрузть результаты для " + DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", TOURNAMENT_CATEGORIES_FK) + "\n"
                    "Пара: " + DBUtils::getSecondNameAndFirstName(orderUID_left) + " VS " + DBUtils::getSecondNameAndFirstName(orderUID_right) + "\n"
                    "Так как сетка изменилась\n";
            continue;
        }

        if (0 < nodes[VERTEX - 1].UID)
        {
            if (0 < orderUID && orderUID != nodes[VERTEX - 1].UID)
                errorMessage +=
                        "Не возможно загрузть результаты для " + DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", TOURNAMENT_CATEGORIES_FK) + "\n"
                        "Пара: " + DBUtils::getSecondNameAndFirstName(orderUID_left) + " VS " + DBUtils::getSecondNameAndFirstName(orderUID_right) + "\n"
                        "Так как победитель уже занесен в турнирную сетку\n" +
                        "В программе победитель: " + DBUtils::getSecondNameAndFirstName(nodes[VERTEX - 1].UID) + "\n"
                        "A Вы пытаетесь загрузить: " + DBUtils::getSecondNameAndFirstName(orderUID) + "\n";
            else if (orderUID == nodes[VERTEX - 1].UID)
                ++countSame;
        }
        else if (0 < orderUID)
        {
            if (DBUtils::insertResultOfFightForNodeOfGrid(TOURNAMENT_CATEGORIES_FK, VERTEX, orderUID, result))
                ++okCount;
            else
                errorMessage +=
                    "Не возможно загрузть результаты для " + DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", TOURNAMENT_CATEGORIES_FK) + "\n"
                    "Пара: " + DBUtils::getSecondNameAndFirstName(orderUID_left) + " VS " + DBUtils::getSecondNameAndFirstName(orderUID_right) + "\n"
                    "Неизвестная ошибка\n";
        }
        else if (orderUID <= 0)
        {
            errorMessage +=
                "Не возможно загрузть результаты для " + DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", TOURNAMENT_CATEGORIES_FK) + "\n"
                "Пара: " + DBUtils::getSecondNameAndFirstName(orderUID_left) + " VS " + DBUtils::getSecondNameAndFirstName(orderUID_right) + "\n"
                "Жюри не запускала эту пару на ринг\n";
        }
        else
        {
            qDebug() << "wtf";
        }
    }

    QMessageBox dlg(this);
    dlg.setText("Успешно загруженно: " + QString::number(okCount) + "\n" +
                "Уже в БД есть: " + QString::number(countSame) + "\n" +
                "Ошибок: " + QString::number(array.size() - okCount - countSame));
    dlg.exec();

    ErrorMessagesDialog dlg2(errorMessage, this);
    dlg2.exec();
}


void MainWindow::on_manda_clicked()
{
    ReportManda::report(tournamentUID);
}


void MainWindow::on_btn_report_ministr_clicked()
{
    ReporMinistr::report(tournamentUID);
}




