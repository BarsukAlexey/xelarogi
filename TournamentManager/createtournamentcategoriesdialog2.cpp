#include "createtournamentcategoriesdialog2.h"
#include "ui_createtournamentcategoriesdialog2.h"

MySqlRelationalDelegate::MySqlRelationalDelegate(QObject* parent) :
    QSqlRelationalDelegate(parent)
{

}

QWidget* MySqlRelationalDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& i, const QModelIndex& index) const
{
    const MySortFilterProxyModel *proxyModel =
            qobject_cast<const MySortFilterProxyModel *>(index.model());
    if (proxyModel)
    {
        QModelIndex sourceIndex = proxyModel->mapToSource(index);
        return createEditor(parent, i, sourceIndex);
    }

    const QSqlRelationalTableModel *sqlModel =
            qobject_cast<const QSqlRelationalTableModel *>(index.model());
    if (!sqlModel)
        return QSqlRelationalDelegate::createEditor(parent, i, index);

    if (QString::compare(sqlModel->record().field(index.column()).name(), "UID", Qt::CaseInsensitive) == 0)
        return 0;

    if(sqlModel->record().field(index.column()).type() == QVariant::Int)
    {
        QSpinBox* spinBox = new QSpinBox(parent);
        spinBox->setMaximum(100500);
        spinBox->setValue(index.data().toInt());
        return spinBox;
    }

    return QSqlRelationalDelegate::createEditor(parent, i, index);
}

void MySqlRelationalDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    const MySortFilterProxyModel *proxyModel = qobject_cast<const MySortFilterProxyModel *>(model);

    if (proxyModel)
    {
        setModelData(editor, proxyModel->sourceModel(),  proxyModel->mapToSource(index));
        return;
    }

    QSqlRelationalTableModel *sqlModel = qobject_cast<QSqlRelationalTableModel *>(model);
    if (!sqlModel)
    {
        QSqlRelationalDelegate::setModelData(editor, model, index);
        return;
    }

    if(sqlModel->record().field(index.column()).type() == QVariant::Int)
    {
        QSpinBox* spinBox = qobject_cast<QSpinBox *>(editor);
        sqlModel->setData(index, spinBox->value(), Qt::DisplayRole);
        sqlModel->setData(index, spinBox->value(), Qt::EditRole);
        return;
    }


    QSqlRelationalDelegate::setModelData(editor, model, index);
}






MySortFilterProxyModel::MySortFilterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    columnsForSortForTournamentCategoties
            << QSqlDatabase::database().record("TOURNAMENT_CATEGORIES").indexOf("TYPE_FK")
            << QSqlDatabase::database().record("TOURNAMENT_CATEGORIES").indexOf("AGE_FROM")
            << QSqlDatabase::database().record("TOURNAMENT_CATEGORIES").indexOf("AGE_TILL")
            << QSqlDatabase::database().record("TOURNAMENT_CATEGORIES").indexOf("SEX_FK")
            << QSqlDatabase::database().record("TOURNAMENT_CATEGORIES").indexOf("WEIGHT_FROM")
            << QSqlDatabase::database().record("TOURNAMENT_CATEGORIES").indexOf("WEIGHT_TILL")
           ;
}

bool MySortFilterProxyModel::lessThan(const QModelIndex& left, const QModelIndex& right) const
{

    const QSqlRelationalTableModel *sqlModel =
                qobject_cast<const QSqlRelationalTableModel *>(sourceModel());

    if(!sqlModel)
        return QSortFilterProxyModel::lessThan(left, right);

    if (sqlModel->tableName() == "TOURNAMENT_CATEGORIES")
    {
        QVariantList a; a << left.data();
        QVariantList b; b << right.data();
        for (const int& column : columnsForSortForTournamentCategoties)
        {
            a << sqlModel->index(left .row(), column).data();
            b << sqlModel->index(right.row(), column).data();
        }
        return a < b;
    }

    return QSortFilterProxyModel::lessThan(left, right);

}















CreateTournamentCategoriesDialog2::CreateTournamentCategoriesDialog2(QWidget *parent, const int tournamentUID) :
    QDialog(parent),
    ui(new Ui::CreateTournamentCategoriesDialog2),
    tournamentUID(tournamentUID)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window);


    QSqlRelationalTableModel *model = new QSqlRelationalTableModel(this);



    model->setTable("TOURNAMENT_CATEGORIES");
    model->setFilter("TOURNAMENT_FK = " + QString::number(tournamentUID));
    model->setJoinMode(QSqlRelationalTableModel::JoinMode::LeftJoin);

    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model->setRelation(model->fieldIndex("TYPE_FK"), QSqlRelation("TYPES", "UID", "NAME"));
    int colCase = model->fieldIndex("IN_CASE_TIE");
    model->setRelation(colCase, QSqlRelation("IN_CASES_OF_TIE", "UID", "NAME"));
    model->setRelation(model->fieldIndex("SEX_FK"), QSqlRelation("SEXES", "UID", "NAME"));
    const int colAge = model->fieldIndex("AGE_CATEGORY_FK");
    model->setRelation(colAge, QSqlRelation("AGE_CATEGORIES", "UID", "NAME"));

    model->select();

    QSqlTableModel* relModel = model->relationModel(colAge);
    relModel->sort(1, Qt::SortOrder::AscendingOrder); // ЧТОБЫ ВЫПАДАЛ СПИСОК ОТСОРТИРОВАННЫМ


    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new MySqlRelationalDelegate(ui->tableView));
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();





    MySortFilterProxyModel *proxyModel =
            new MySortFilterProxyModel(this);
    proxyModel->setSourceModel(model);

    ui->tableView_2->setModel(proxyModel);
    ui->tableView_2->sortByColumn(1, Qt::SortOrder::AscendingOrder);
    ui->tableView_2->setItemDelegate(new MySqlRelationalDelegate(ui->tableView_2));
    ui->tableView_2->resizeColumnsToContents();
    ui->tableView_2->resizeRowsToContents();



    connect(ui->pushButtonSave, &QPushButton::clicked, [this, model](){
        if (model->submitAll())
            qDebug() << "Save all";
        else
        {
            qDebug() << model->lastError();
            QMessageBox::warning(this, "", "Некорректные данные:\n" + model->lastError().databaseText() + "\n" + model->lastError().driverText());
            //model->revertAll();
        }
    });
    connect(ui->pushButtonCancel, &QPushButton::clicked, [model](){
        model->revertAll();
        model->select();
    });
}

CreateTournamentCategoriesDialog2::~CreateTournamentCategoriesDialog2()
{
    delete ui;
}


