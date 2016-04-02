#include "createtournamentcategoriesdialog.h"
#include "ui_createtournamentcategoriesdialog.h"
#include "generatetournamentcategoriesdialog.h"

CreateTournamentCategoriesDialog::CreateTournamentCategoriesDialog(long long tournamentUID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateTournamentCategoriesDialog),
    mTournamentUID(tournamentUID)
{
    ui->setupUi(this);

    updateTable();

    connect(ui->tableView, &QTableView::clicked, [this] (const QModelIndex& index)
    {
        ui->applyBtn->setEnabled(true);
        QModelIndex ind = index.model()->index(index.row(), 0);
        updateDataWidget(ind.data().toLongLong());
    });

    fillSexComboBox();
    fillTypeComboBox();

    connect(ui->addBtn, &QPushButton::clicked, this, &CreateTournamentCategoriesDialog::onAddBtn);
    connect(ui->applyBtn, &QPushButton::clicked, [this] ()
    {
        QModelIndex index = ui->tableView->currentIndex();
        if (index != QModelIndex())
        {
            QModelIndex ind = index.model()->index(index.row(), 0);
            onChangeBtn(ind.data().toLongLong());
        }
    });

    addContextMenu();

    connect(ui->addTypeBtn, &QPushButton::clicked, [this] ()
    {
        CreateTypeDialog dlg(this);
        if (dlg.exec() == QDialog::Accepted)
        {
            long long selectedTypeUID = ui->typeCB->currentData(Qt::UserRole).toLongLong();
            fillTypeComboBox();
            selectTypeByUID(selectedTypeUID);
        }
    });

    setWindowFlags(windowFlags() | Qt::WindowMinMaxButtonsHint);
}

CreateTournamentCategoriesDialog::~CreateTournamentCategoriesDialog()
{
    delete ui;
}

void CreateTournamentCategoriesDialog::updateTable()
{
    QSqlRelationalTableModel * model = new QSqlRelationalTableModel();
    model->setTable("TOURNAMENT_CATEGORIES");
    //model->setRelation(model->fieldIndex("SEX_FK"), QSqlRelation("SEXES", "UID", "NAME"));
    model->setFilter("TOURNAMENT_FK = " + QString::number(mTournamentUID) +
                " ORDER BY SEX_FK, TYPE_FK, AGE_FROM, AGE_TILL, WEIGHT_FROM, WEIGHT_TILL " );
    //model->setFilter("TOURNAMENT_FK = " + QString::number(mTournamentUID) );

    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(model->fieldIndex("UID"), true);
    ui->tableView->setColumnHidden(model->fieldIndex("TOURNAMENT_FK"), true);
    ui->tableView->setColumnHidden(model->fieldIndex("AGE_FROM"), true);
    ui->tableView->setColumnHidden(model->fieldIndex("AGE_TILL"), true);
    ui->tableView->setColumnHidden(model->fieldIndex("WEIGHT_FROM"), true);
    ui->tableView->setColumnHidden(model->fieldIndex("WEIGHT_TILL"), true);
    ui->tableView->setColumnHidden(model->fieldIndex("SEX_FK"), true);
    //ui->tableView->setColumnHidden(model->fieldIndex("DURATION_FIGHING"), true);
    //ui->tableView->setColumnHidden(model->fieldIndex("DURATION_BREAK"), true);
    //ui->tableView->setColumnHidden(model->fieldIndex("ROUND_COUNT"), true);
    ui->tableView->setColumnHidden(model->fieldIndex("TYPE_FK"), true);


    model->setHeaderData(model->fieldIndex("NAME"), Qt::Horizontal, "Наименование");
    model->setHeaderData(model->fieldIndex("DURATION_FIGHING"), Qt::Horizontal, "Длительность боя");
    model->setHeaderData(model->fieldIndex("DURATION_BREAK"), Qt::Horizontal, "Перерыв");
    model->setHeaderData(model->fieldIndex("ROUND_COUNT"), Qt::Horizontal, "Кол-во раундов");

    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    model->select();
    ui->tableView->resizeColumnsToContents();
}

void CreateTournamentCategoriesDialog::updateDataWidget(long long categoryUID)
{
    QSqlQuery query;
    if (!query.prepare("SELECT * FROM TOURNAMENT_CATEGORIES WHERE UID = ?"))
        qDebug() << query.lastError().text();
    query.bindValue(0, categoryUID);

    if (query.exec() && query.next())
    {
        QString name = query.value("NAME").toString();
        double ageFrom = query.value("AGE_FROM").toDouble();
        double ageTill = query.value("AGE_TILL").toDouble();
        double weightFrom = query.value("WEIGHT_FROM").toDouble();
        double weightTill = query.value("WEIGHT_TILL").toDouble();
        int durationFighting = query.value("DURATION_FIGHING").toInt();
        int durationBreak = query.value("DURATION_BREAK").toInt();
        int roundCount = query.value("ROUND_COUNT").toInt();
        long long sexUID = query.value("SEX_FK").toLongLong();
        long long typeUID = query.value("TYPE_FK").toLongLong();

        ui->nameLE->setText(name);
        ui->ageFromSB->setValue(ageFrom);
        ui->ageTillSB->setValue(ageTill);
        ui->weightFromDSB->setValue(weightFrom);
        ui->weightTillDSB->setValue(weightTill);
        ui->durationBreakSB->setValue(durationBreak);
        ui->durationFightingSB->setValue(durationFighting);
        ui->roundCountSB->setValue(roundCount);

        selectSexByUID(sexUID);
        selectTypeByUID(typeUID);
    }
    else
    {
        qDebug() << query.lastError().text();
    }
}

void CreateTournamentCategoriesDialog::fillSexComboBox()
{
    ui->sexCB->clear();

    QSqlQuery sexQuery;
    if (!sexQuery.prepare("SELECT * FROM SEXES"))
        qDebug() << sexQuery.lastError().text();
    if (sexQuery.exec())
    {
        int index = 0;
        while (sexQuery.next())
        {
            ui->sexCB->addItem(sexQuery.value("NAME").toString());
            ui->sexCB->setItemData(index, sexQuery.value("UID").toLongLong(), Qt::UserRole);
            ++index;
        }
    }
    else
    {
        qDebug() << sexQuery.lastError().text();
    }
}

void CreateTournamentCategoriesDialog::fillTypeComboBox()
{
    ui->typeCB->clear();

    QSqlQuery typeQuery;
    if (!typeQuery.prepare("SELECT * FROM TYPES"))
        qDebug() << typeQuery.lastError().text();
    if (typeQuery.exec())
    {
        int index = 0;
        while (typeQuery.next())
        {
            ui->typeCB->addItem(typeQuery.value("NAME").toString());
            ui->typeCB->setItemData(index, typeQuery.value("UID").toLongLong(), Qt::UserRole);
            ++index;
        }
    }
    else
    {
        qDebug() << typeQuery.lastError().text();
    }
}

void CreateTournamentCategoriesDialog::selectSexByUID(long long sexUID)
{
    for (int index = 0; index < (int)ui->sexCB->count(); ++index)
    {
        if (ui->sexCB->itemData(index, Qt::UserRole).toLongLong() == sexUID)
        {
            ui->sexCB->setCurrentIndex(index);
        }
    }
}

void CreateTournamentCategoriesDialog::selectTypeByUID(long long typeUID)
{
    for (int index = 0; index < (int)ui->typeCB->count(); ++index)
    {
        if (ui->typeCB->itemData(index, Qt::UserRole).toLongLong() == typeUID)
        {
            ui->typeCB->setCurrentIndex(index);
        }
    }
}

void CreateTournamentCategoriesDialog::addContextMenu()
{
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView, &QTableView::customContextMenuRequested, [this] (const QPoint& pos)
    {
        QMenu* menu = new QMenu();

        QAction* deleteAction = new QAction("Удалить", menu);
        connect(deleteAction, &QAction::triggered, [this, &pos] ()
        {
            QModelIndex index = ui->tableView->indexAt(pos);
            QSqlRelationalTableModel* model = dynamic_cast<QSqlRelationalTableModel*>(ui->tableView->model());
            model->removeRow(index.row());
            model->submitAll();
            model->select();
        });
        menu->addAction(deleteAction);

        menu->exec(ui->tableView->viewport()->mapToGlobal(pos));
    });
}

void CreateTournamentCategoriesDialog::onAddBtn()
{
    QString name = ui->nameLE->text();
    double ageFrom = ui->ageFromSB->value();
    double ageTill = ui->ageTillSB->value();
    double weightFrom = ui->weightFromDSB->value();
    double weightTill = ui->weightTillDSB->value();
    int durationFighting = ui->durationFightingSB->value();
    int durationBreak = ui->durationBreakSB->value();
    int roundCount = ui->roundCountSB->value();
    long long sexUID = ui->sexCB->currentData(Qt::UserRole).toLongLong();
    long long typeUID = ui->typeCB->currentData(Qt::UserRole).toLongLong();

    QSqlQuery insertQuery;
    if (!insertQuery.prepare("INSERT INTO TOURNAMENT_CATEGORIES"
                             "(NAME, AGE_FROM, AGE_TILL, WEIGHT_FROM, WEIGHT_TILL, SEX_FK, TOURNAMENT_FK,"
                             "DURATION_FIGHING, DURATION_BREAK, ROUND_COUNT, TYPE_FK) "
                             "VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"))
        qDebug() << insertQuery.lastError().text();
    insertQuery.bindValue(0, name);
    insertQuery.bindValue(1, ageFrom);
    insertQuery.bindValue(2, ageTill);
    insertQuery.bindValue(3, weightFrom);
    insertQuery.bindValue(4, weightTill);
    insertQuery.bindValue(5, sexUID);
    insertQuery.bindValue(6, mTournamentUID);
    insertQuery.bindValue(7, durationFighting);
    insertQuery.bindValue(8, durationBreak);
    insertQuery.bindValue(9, roundCount);
    insertQuery.bindValue(10, typeUID);
    if (insertQuery.exec())
    {
        updateTable();
    }
    else
    {
        qDebug() << insertQuery.lastError().text();
    }
}

void CreateTournamentCategoriesDialog::onChangeBtn(long long categoryUID)
{
    QModelIndex selectedIndex = ui->tableView->currentIndex();

    QString name = ui->nameLE->text();
    double ageFrom = ui->ageFromSB->value();
    double ageTill = ui->ageTillSB->value();
    double weightFrom = ui->weightFromDSB->value();
    double weightTill = ui->weightTillDSB->value();
    int durationFighting = ui->durationFightingSB->value();
    int durationBreak = ui->durationBreakSB->value();
    int roundCount = ui->roundCountSB->value();
    long long sexUID = ui->sexCB->currentData(Qt::UserRole).toLongLong();
    long long typeUID = ui->typeCB->currentData(Qt::UserRole).toLongLong();

    QSqlQuery updateQuery;
    if (!updateQuery.prepare("UPDATE TOURNAMENT_CATEGORIES"
                             " SET NAME = ?,"
                             " AGE_FROM = ?, AGE_TILL = ?,"
                             " WEIGHT_FROM = ?, WEIGHT_TILL = ?,"
                             " SEX_FK = ?, TOURNAMENT_FK = ?,"
                             " DURATION_FIGHING = ?, DURATION_BREAK = ?, ROUND_COUNT = ?, TYPE_FK = ?"
                             " WHERE UID = ?"))
        qDebug() << updateQuery.lastError().text();
    updateQuery.bindValue(0, name);
    updateQuery.bindValue(1, ageFrom);
    updateQuery.bindValue(2, ageTill);
    updateQuery.bindValue(3, weightFrom);
    updateQuery.bindValue(4, weightTill);
    updateQuery.bindValue(5, sexUID);
    updateQuery.bindValue(6, mTournamentUID);
    updateQuery.bindValue(7, durationFighting);
    updateQuery.bindValue(8, durationBreak);
    updateQuery.bindValue(9, roundCount);
    updateQuery.bindValue(10, typeUID);
    updateQuery.bindValue(11, categoryUID);
    if (updateQuery.exec())
    {
        updateTable();

        const QModelIndex& newCurrentIndex = ui->tableView->model()->index(selectedIndex.row(), selectedIndex.column());
        if (newCurrentIndex != QModelIndex())
        {
            ui->tableView->setCurrentIndex(newCurrentIndex);
        }
    }
    else
    {
        qDebug() << updateQuery.lastError().text();
    }
}


void CreateTournamentCategoriesDialog::on_pushButton_clicked()
{
    GenerateTournamentCategoriesDialog(mTournamentUID, this).exec();
    updateTable();
    fillTypeComboBox();
}

void CreateTournamentCategoriesDialog::on_okBtn_clicked()
{

}
