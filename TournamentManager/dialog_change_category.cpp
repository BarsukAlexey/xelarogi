#include "dialog_change_category.h"
#include "ui_dialogchangecategory.h"


DialogChangeCategory::DialogChangeCategory(const int orderUID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChangeCategory)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window);

    const long long uidTC = DBUtils::getField("TOURNAMENT_CATEGORY_FK", "ORDERS", orderUID).toLongLong();
    const int       tournamentUID = DBUtils::getField("TOURNAMENT_FK", "TOURNAMENT_CATEGORIES", uidTC).toLongLong();
    const int       sexUID = DBUtils::getField("SEX_FK", "ORDERS", orderUID).toLongLong();
    const int       a = Utils::getAge(
                            DBUtils::get("BIRTHDATE"     , "ORDERS"     , orderUID).toDate(),
                            DBUtils::get("DATE_WEIGHTING", "TOURNAMENTS", tournamentUID).toDate());
    const double    w = DBUtils::getField("WEIGHT", "ORDERS", orderUID).toDouble();


    QAbstractItemModel* model = ui->tableWidget->model();

    QSqlQuery query;
    if (!query.prepare(
            "SELECT * "
            "FROM "
            "   TOURNAMENT_CATEGORIES A "
            "WHERE "
            "   UID != :uidTC AND "
            "   TOURNAMENT_FK = :tournamentUID AND "
            "   SEX_FK = :sexUID AND "
            "   AGE_FROM <= :a AND :a <= AGE_TILL AND "
            "   (WEIGHT_FROM + 1e-7 < :w AND :w < WEIGHT_TILL + 1e-7 OR "
            "      EXISTS ("
            "         SELECT * "
            "         FROM TOURNAMENT_CATEGORIES B "
            "         WHERE "
            "            B.TOURNAMENT_FK = A.TOURNAMENT_FK AND"
            "            B.SEX_FK        = A.SEX_FK AND "
            "            B.TYPE_FK       = A.TYPE_FK AND "
            "            B.AGE_FROM      = A.AGE_FROM AND "
            "            B.AGE_TILL      = A.AGE_TILL AND "
            "            B.WEIGHT_FROM + 1e-7 < :w AND :w < B.WEIGHT_TILL + 1e-7 AND"
            "            ABS(A.WEIGHT_FROM - B.WEIGHT_TILL) < 1e-7 "
            "      ) "
            "   )"
            "ORDER BY "
            "   AGE_FROM, AGE_TILL, TYPE_FK, WEIGHT_FROM, WEIGHT_TILL "))
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
    }
    query.bindValue(":uidTC", uidTC);
    query.bindValue(":tournamentUID", tournamentUID);
    query.bindValue(":sexUID", sexUID);
    query.bindValue(":a", a);
    query.bindValue(":w", w);
    if (!query.exec())
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError() << query.lastQuery();
    }
    while (query.next())
    {
        long long curUidTC = query.value("UID").toLongLong();
        int countPeople = DBUtils::getNodes(curUidTC).size();
        if (!countPeople)
        {
            continue;
        }

        int row = model->rowCount();
        model->insertRow(row);
        model->setData(model->index(row, 0), curUidTC);
        model->setData(model->index(row, 1), DBUtils::get("NAME", "TOURNAMENT_CATEGORIES", curUidTC));
        model->setData(model->index(row, 2), DBUtils::get("NAME", "TYPES", DBUtils::get("TYPE_FK", "TOURNAMENT_CATEGORIES", curUidTC)));
        model->setData(model->index(row, 3), DBUtils::get("WEIGHT_FROM", "TOURNAMENT_CATEGORIES", curUidTC));
        model->setData(model->index(row, 4), DBUtils::get("WEIGHT_TILL", "TOURNAMENT_CATEGORIES", curUidTC));
        model->setData(model->index(row, 5), countPeople);
    }
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();


    ui->label->setText(
                DBUtils::getSecondNameAndFirstName(orderUID) + "\n" +
                DBUtils::roundDouble(w, 3) + " кг\n" +
                "Возраст: " + QString::number(a) + "\n" +
                DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", uidTC)
                );

    connect(ui->buttonBox, &QDialogButtonBox::accepted, [this, orderUID, model]{
        QModelIndexList lst =  ui->tableWidget->selectionModel()->selectedRows();
        if (!lst.size()) return;
        int uidCategory = model->data(model->index(lst[0].row(), 0)).toInt();

        QSqlQuery updateQuery;
        updateQuery.prepare(
                    "UPDATE ORDERS "
                    "SET "
                    "TOURNAMENT_CATEGORY_FK = ?, TYPE_FK = ? "
                    "WHERE UID = ? ");
        updateQuery.addBindValue(uidCategory);
        updateQuery.addBindValue(DBUtils::getField("TYPE_FK", "TOURNAMENT_CATEGORIES", uidCategory));
        updateQuery.addBindValue(orderUID);
        if (!updateQuery.exec())
        {
            QMessageBox::critical(this, "",
                                  "Некорректные данные:\n" +
                                  updateQuery.lastError().databaseText() + "\n" +
                                  updateQuery.lastError().driverText());
            return ;
        }

        accept();
    });

    connect(ui->buttonBox, &QDialogButtonBox::rejected, [this]{
        reject();
    });

    connect(ui->pushButtonShowGrid, &QPushButton::clicked, [this, model, tournamentUID](){
        QModelIndexList lst =  ui->tableWidget->selectionModel()->selectedRows();
        if (!lst.size()) return;
        int uidCategory = model->data(model->index(lst[0].row(), 0)).toInt();

        DialogTournamentGrid(this, DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", uidCategory), tournamentUID).exec();
    });
}

DialogChangeCategory::~DialogChangeCategory()
{
    delete ui;
}
