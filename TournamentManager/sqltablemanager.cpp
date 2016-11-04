#include "sqltablemanager.h"
#include "ui_sqltablemanager.h"


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

    int countSectionNotHidden = 0;
    for (int ii = 0; ii < headerView->count(); ++ii)
    {
        if (!headerView->isSectionHidden(ii))
        {
            ++countSectionNotHidden;
        }
    }
    Q_ASSERT_X(countSectionNotHidden == count(), "layout", "there must be as many items in the layout as there are columns in the table");
    if (countSectionNotHidden != count())
    {
        return;
    }

    Q_ASSERT(parentWidget());

    int widgetX = parentWidget()->mapToGlobal(QPoint(0, 0)).x();
    int headerX = headerView->mapToGlobal(QPoint(0, 0)).x();

    int delta = headerX - widgetX;

    for (int i = 0, indexOfLineEdit = 0; i < headerView->count(); ++i)
    {
        if (!headerView->isSectionHidden(i))
        {
            int pos = headerView->sectionViewportPosition(i);
            int size = headerView->sectionSize(i);

            QLayoutItem* item = itemAt(indexOfLineEdit++);
            QRect r = item->geometry();
            r.setLeft(pos + delta);
            r.setWidth(size);
            item->setGeometry(r);
        }
    }
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

    if (QString::compare(sqlModel->record().field(index.column()).name(), "FLAG", Qt::CaseInsensitive) == 0)
    {
        QImage img;
        QByteArray byteArray = QByteArray::fromBase64(index.data().toString().toLocal8Bit());
        if (byteArray.size() > 0)
        {
            img.loadFromData(byteArray);
        }
        ImageLoaderWidget * imageLoaderWidget = new ImageLoaderWidget(parent, img);
        //imageLoaderWidget->installEventFilter(const_cast<MySqlRelationalDelegate *>(this));
        return imageLoaderWidget;
    }

    if(sqlModel->record().field(index.column()).type() == QVariant::Int)
    {
        QSpinBox* spinBox = new QSpinBox(parent);
        spinBox->setMaximum(100500);
        spinBox->setValue(index.data().toInt());
        return spinBox;
    }

    return QSqlRelationalDelegate::createEditor(parent, i, index);
}

//bool MySqlRelationalDelegate::editorEvent(QEvent* event, QAbstractItemModel* model,
//                                          const QStyleOptionViewItem& option, const QModelIndex& index)
//{
//    MySortFilterProxyModel *proxyModel =
//            qobject_cast<MySortFilterProxyModel *>(model);
//    if (proxyModel)
//    {
//        return editorEvent(event, proxyModel->sourceModel(), option, proxyModel->mapToSource(index));
//    }

//    const QSqlRelationalTableModel *sqlModel =
//            qobject_cast<const QSqlRelationalTableModel *>(index.model());
//    if (!sqlModel)
//        return QSqlRelationalDelegate::editorEvent(event, model, option, index);
//    if (QString::compare(sqlModel->record().field(index.column()).name(), "FLAG", Qt::CaseInsensitive) == 0)
//    {
//        qDebug() << "editorEvent:: " << event->type();
//    }

//    bool res = QSqlRelationalDelegate::editorEvent(event, model, option, index);
//    qDebug() << res << event->type();
//    return res;

//}

MySqlRelationalDelegate::MySqlRelationalDelegate(QObject* parent) :
    QSqlRelationalDelegate(parent)
{

}

void MySqlRelationalDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    MySortFilterProxyModel *proxyModel = qobject_cast<MySortFilterProxyModel *>(model);

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

    if (QString::compare(sqlModel->record().field(index.column()).name(), "FLAG", Qt::CaseInsensitive) == 0)
    {
        ImageLoaderWidget* imgLoader = qobject_cast<ImageLoaderWidget *>(editor);
        QString base64Image = imgLoader->getBase64Image();
        sqlModel->setData(index, base64Image, Qt::DisplayRole);
        sqlModel->setData(index, base64Image, Qt::EditRole);
        return ;
    }

    QSqlRelationalDelegate::setModelData(editor, model, index);
}

void MySqlRelationalDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    const MySortFilterProxyModel *proxyModel = qobject_cast<const MySortFilterProxyModel *>(index.model());

    if (proxyModel)
    {
        paint(painter, option, proxyModel->mapToSource(index));
        return;
    }

    const QSqlRelationalTableModel *sqlModel = qobject_cast<const  QSqlRelationalTableModel *>(index.model());
    if (!sqlModel)
    {
        QSqlRelationalDelegate::paint(painter, option, index);
        return;
    }

    if (QString::compare(sqlModel->record().field(index.column()).name(), "FLAG", Qt::CaseInsensitive) == 0)
    {
//        qDebug()<< sqlModel->data(sqlModel->index(index.row(), 1))
//                << QString::number(option.state, 16)
//                << QString::number(QStyle::State_Selected, 16);

        if (option.state & QStyle::State_Selected)
        {
            painter->fillRect(option.rect, option.palette.highlight());
        }
//        qDebug()
//                << sqlModel->data(sqlModel->index(index.row(), 1))
//                << QString::number(option.state, 16)
//                << QString::number(QStyle::State_Selected, 16);

//        if (!(option.state & 0x10100))
//        {
//            return ;
//        }

        QByteArray byteArray = QByteArray::fromBase64(index.data().toString().toLocal8Bit());
        if (byteArray.size() > 0)
        {
            QPixmap pixmap;
            pixmap.loadFromData(byteArray);
            pixmap = pixmap.scaled(option.rect.size(), Qt::KeepAspectRatio);
            QPoint A(option.rect.x() + (option.rect.width() - pixmap.width()) / 2,
                     option.rect.y() + (option.rect.height() - pixmap.height()) / 2);
            QPoint B = A + QPoint(pixmap.width(), pixmap.height());

            painter->drawPixmap(QRect(A, B), pixmap);

            painter->setPen(Qt::lightGray);

            painter->drawLine(A, B - QPoint(pixmap.width(), 0));
            painter->drawLine(A + QPoint(pixmap.width(), 0), B);
        }
        return ;
    }

    QSqlRelationalDelegate::paint(painter, option, index);
}

QSize MySqlRelationalDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    const MySortFilterProxyModel *proxyModel = qobject_cast<const MySortFilterProxyModel *>(index.model());

    if (proxyModel)
    {
        return sizeHint(option, proxyModel->mapToSource(index));
    }

    const QSqlRelationalTableModel *sqlModel = qobject_cast<const  QSqlRelationalTableModel *>(index.model());
    if (!sqlModel)
    {
        return QSqlRelationalDelegate::sizeHint(option, index);

    }

    if (QString::compare(sqlModel->record().field(index.column()).name(), "FLAG", Qt::CaseInsensitive) == 0)
    {
        return QSize(300, 100);
    }
    return QSqlRelationalDelegate::sizeHint(option, index);
}



MySortFilterProxyModel::MySortFilterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{

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

void MySortFilterProxyModel::setSourceModel(QAbstractItemModel* sourceModel)
{
    QSortFilterProxyModel::setSourceModel(sourceModel);

    const QSqlRelationalTableModel *sqlModel =
            qobject_cast<const QSqlRelationalTableModel *>(sourceModel);
    if (sqlModel)
    {
        if (sqlModel->tableName() == "TOURNAMENT_CATEGORIES")
        {
            QSqlRecord record = QSqlDatabase::database().record("TOURNAMENT_CATEGORIES");
            columnsForSort
                << record.indexOf("TOURNAMENT_FK")
                << record.indexOf("TYPE_FK")
                << record.indexOf("AGE_FROM")
                << record.indexOf("AGE_TILL")
                << record.indexOf("SEX_FK")
                << record.indexOf("WEIGHT_FROM")
                << record.indexOf("WEIGHT_TILL");
        }
    }
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
        for (const int& column : columnsForSort)
        {
            a << sqlModel->index(left .row(), column).data();
            b << sqlModel->index(right.row(), column).data();
        }
        return a < b;
    }

    return QSortFilterProxyModel::lessThan(left, right);

}

SqlTableManager::SqlTableManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SqlTableManager)
{
    ui->setupUi(this);
}

void SqlTableManager::setSqlTable(const QString& table, const QString& whereStatement, const QStringList& hidenColumns)
{
    model = new QSqlRelationalTableModel(this);

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

    QSet<int> idOfhidenColumns;
    for (const QString column : hidenColumns)
    {
        int index = model->fieldIndex(column);
        if (index == -1)
        {
            qDebug() << "WTF! no suck column:" << index;
        }
        else
        {
            idOfhidenColumns << index;
        }
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

    MySortFilterProxyModel *proxyModel =
            new MySortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    proxyModel->setDynamicSortFilter(false);
    //proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);


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
        if (idOfhidenColumns.contains(i))
        {
            ui->tableView_2->hideColumn(i);
        }
        else
        {
            QLineEdit *edit = new QLineEdit(this);
            edit->setPlaceholderText(model->headerData(i, Qt::Horizontal).toString());
            alignedLayout->addWidget(edit);
            connect(edit, &QLineEdit::textChanged, [i, proxyModel](const QString& str){
                QStringList list = str.split(" ", QString::SkipEmptyParts);
                proxyModel->setMyFilter(i, list);
            });
        }
    }

    ui->widget2222->setLayout(alignedLayout);
    alignedLayout->setParent(ui->widget2222);

    alignedLayout->setTableColumnsToTrack(ui->tableView_2->horizontalHeader());
    connect(ui->tableView_2->horizontalHeader(), SIGNAL(sectionResized(int,int,int)), SLOT(invalidateAlignedLayout()));
    connect(ui->tableView_2->horizontalScrollBar(), SIGNAL(valueChanged(int)), SLOT(invalidateAlignedLayout()));

    connect(ui->pushButtonSave, &QPushButton::clicked, [this, proxyModel](){
        //qDebug() << model->rowCount();
        if (model->submitAll())
        {
            qDebug() << "Save all";
            while (model->canFetchMore())
                model->fetchMore();
            proxyModel->invalidate();
            //qDebug() << model->rowCount();
        }
        else
        {
            qDebug() << model->lastError();
            QMessageBox::warning(this, "", "Некорректные данные:\n" + model->lastError().databaseText() + "\n" + model->lastError().driverText());
            //model->revertAll();
        }
    });
    connect(ui->pushButtonCancel, &QPushButton::clicked, [this](){
        model->revertAll();
    });
    connect(ui->pushButtonInsert, &QPushButton::clicked, [this](){
        model->insertRow(model->rowCount());
    });
}

void SqlTableManager::updateData()
{
    model->select();
    while (model->canFetchMore())
        model->fetchMore();
    //proxyModel->invalidate();
}

SqlTableManager::~SqlTableManager()
{
    delete ui;
}



void SqlTableManager::invalidateAlignedLayout()
{
    alignedLayout->invalidate();
}

