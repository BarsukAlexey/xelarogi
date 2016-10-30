#include "createtournamentcategoriesdialog2.h"
#include "ui_createtournamentcategoriesdialog2.h"


ColumnAlignedLayout::ColumnAlignedLayout(QWidget* parent)
    : QHBoxLayout(parent)
{

}

void ColumnAlignedLayout::setTableColumnsToTrack(QHeaderView* view) { headerView = view; }

void ColumnAlignedLayout::setGeometry(const QRect& r)
{
    QHBoxLayout::setGeometry(r);

    Q_ASSERT_X(headerView, "layout", "no table columns to track");
    if (!headerView)
    {
        return;
    }

    Q_ASSERT_X(headerView->count() == count(), "layout", "there must be as many items in the layout as there are columns in the table");
    if (headerView->count() != count())
    {
        return;
    }

    Q_ASSERT(parentWidget());

    int widgetX = parentWidget()->mapToGlobal(QPoint(0, 0)).x();
    int headerX = headerView->mapToGlobal(QPoint(0, 0)).x();

    int delta = headerX - widgetX;

    for (int ii = 0; ii < headerView->count(); ++ii)
    {
        int pos = headerView->sectionViewportPosition(ii);
        int size = headerView->sectionSize(ii);

        auto item = itemAt(ii);
        auto r = item->geometry();
        r.setLeft(pos + delta);
        r.setWidth(size);
        item->setGeometry(r);
    }
}

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

QVariant MySortFilterProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Vertical && role == Qt::DisplayRole)
        return section + 1;
    return QSortFilterProxyModel::headerData(section, orientation, role);
}

void MySortFilterProxyModel::setMyFilter(const int column, const QStringList& filter)
{
    if (filters.size() <= column)
        filters.resize(column + 1);
    filters[column] = filter;
    invalidateFilter();
}

bool MySortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
    QAbstractItemModel* model = sourceModel();
    for (int column = 0; column < filters.size(); ++column)
    {
        const QStringList& list = filters[column];

        bool haveThisFilter = list.isEmpty();
        for (const QString& filter : list)
        {
            QString text = model->data(model->index(sourceRow, column, sourceParent)).toString();
            haveThisFilter |= text.contains(filter, Qt::CaseInsensitive);
        }
        if (!haveThisFilter)
            return false;
    }
    return true;
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

CreateTournamentCategoriesDialog2::CreateTournamentCategoriesDialog2(QWidget *parent, const QString& table, const QString& whereStatement) :

    QDialog(parent),
    ui(new Ui::CreateTournamentCategoriesDialog2)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window);


    QSqlRelationalTableModel *model = new QSqlRelationalTableModel(this);

    model->setTable(table);
    if (!whereStatement.isEmpty())
        model->setFilter(whereStatement);
    model->setJoinMode(QSqlRelationalTableModel::JoinMode::LeftJoin);

    model->setEditStrategy(QSqlTableModel::OnManualSubmit);


    QMap<QString, std::tuple<QString, QString> > map = DBUtils::get_NAME_RUS__RELATION_TABLE_NAME();
    for (int i = 0; i < model->columnCount(); ++i)
    {
        QString eng = model->headerData(i, Qt::Horizontal).toString();
        QString rus = std::get<0>(map[eng]);
        //qDebug() << eng << rus;
        if (!rus.isEmpty())
            model->setHeaderData(i, Qt::Horizontal, rus);

        QString relTable = std::get<1>(map[eng]);
        if (!relTable.isEmpty())
            model->setRelation(model->fieldIndex(eng), QSqlRelation(relTable, "UID", "NAME"));
    }


    model->select();
    while (model->canFetchMore())
        model->fetchMore();

    for (int i = 0; i < model->columnCount(); ++i)
    {
        QSqlTableModel* relModel = model->relationModel(i);
        if (relModel)
            relModel->sort(1, Qt::SortOrder::AscendingOrder);
    }



    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new MySqlRelationalDelegate(ui->tableView));
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();


    MySortFilterProxyModel *proxyModel =
            new MySortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    proxyModel->setDynamicSortFilter(false);


    ui->tableView_2->setModel(proxyModel);
    ui->tableView_2->sortByColumn(1, Qt::SortOrder::AscendingOrder);
    ui->tableView_2->setItemDelegate(new MySqlRelationalDelegate(ui->tableView_2));
    ui->tableView_2->resizeColumnsToContents();
    ui->tableView_2->resizeRowsToContents();

    QHeaderView* verticalHeader = ui->tableView_2->verticalHeader();
    if (verticalHeader->count())
    {
        verticalHeader->setDefaultSectionSize(verticalHeader->sectionSize(0));
    }


    alignedLayout = new ColumnAlignedLayout(ui->widget2222);
    for (int i = 0; i < model->columnCount(); ++i)
    {
        QLineEdit *edit = new QLineEdit(this);
        edit->setPlaceholderText(model->headerData(i, Qt::Horizontal).toString());
        alignedLayout->addWidget(edit);
        connect(edit, &QLineEdit::textChanged, [i, proxyModel](const QString& str){
            QStringList list = str.split(" ", QString::SkipEmptyParts);
            proxyModel->setMyFilter(i, list);
        });
    }

    ui->widget2222->setLayout(alignedLayout);
    alignedLayout->setParent(ui->widget2222);

    alignedLayout->setTableColumnsToTrack(ui->tableView_2->horizontalHeader());
    connect(ui->tableView_2->horizontalHeader(), SIGNAL(sectionResized(int,int,int)), SLOT(invalidateAlignedLayout()));
    connect(ui->tableView_2->horizontalScrollBar(), SIGNAL(valueChanged(int)), SLOT(invalidateAlignedLayout()));

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
    connect(ui->pushButtonInsert, &QPushButton::clicked, [model](){
        model->insertRow(model->rowCount());
    });

}

CreateTournamentCategoriesDialog2::~CreateTournamentCategoriesDialog2()
{
    delete ui;
}

void CreateTournamentCategoriesDialog2::invalidateAlignedLayout()
{
    alignedLayout->invalidate();
}
