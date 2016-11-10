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






MyQSqlRelationalDelegate::MyQSqlRelationalDelegate(QObject* parent, QMap<int, QVariant> columnDefaultValue) :
    QSqlRelationalDelegate(parent),
    columnDefaultValue(columnDefaultValue)
{
}

QWidget* MyQSqlRelationalDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& i, const QModelIndex& index) const
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

    QSqlField field = sqlModel->record().field(index.column());
    if (QString::compare(field.name(), "UID", Qt::CaseInsensitive) == 0)
        return 0;

    if (QString::compare(field.name(), "FLAG", Qt::CaseInsensitive) == 0)
    {
        QImage img;
        QByteArray byteArray = QByteArray::fromBase64(index.data().toString().toLocal8Bit());
        if (byteArray.size() > 0)
        {
            img.loadFromData(byteArray);
        }
        ImageLoaderWidget * imageLoaderWidget = new ImageLoaderWidget(parent, img);
        imageLoaderWidget->installEventFilter(const_cast<MyQSqlRelationalDelegate *>(this)); // хуй знает зачем эта строчка кода, но пусть будет
        return imageLoaderWidget;
    }

    if(field.type() == QVariant::Int)
    {
        QSpinBox* spinBox = new QSpinBox(parent);
        spinBox->setMaximum(100500);
        spinBox->setValue(index.data().toInt());
        return spinBox;
    }


    if (field.name().startsWith("DATE", Qt::CaseInsensitive) ||
        field.name().compare("BIRTHDATE", Qt::CaseInsensitive) == 0)
    {
        QDateEdit *dateEdit = new QDateEdit(parent);
        dateEdit->setDate(index.data(Qt::EditRole).toDate());
        return dateEdit;
    }


    if (sqlModel->relationModel(index.column()))
    {
        QWidget* editor = QSqlRelationalDelegate::createEditor(parent, i, index);
        QComboBox *combo = qobject_cast<QComboBox *>(editor);

        QSqlTableModel *childModel = qobject_cast<QSqlTableModel *>(combo->model());
        while (childModel && childModel->canFetchMore())
        {
            childModel->fetchMore();
        }
        combo->setMaxVisibleItems(1000);
        if (sqlModel->isDirty(index))
        {
            int uidChild = index.data(Qt::EditRole).toInt();
            for (int r = 0; r < childModel->rowCount(); ++r)
            {
                if (childModel->data(childModel->index(r, 0)).toInt() == uidChild)
                {
                    combo->setCurrentIndex(r);
                    break;
                }
            }
        }
        return editor;
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



void MyQSqlRelationalDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
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


    QMapIterator<int, QVariant> iter(columnDefaultValue);
    while (iter.hasNext()) {
        iter.next();
        sqlModel->setData(sqlModel->index(index.row(), iter.key()), iter.value());
    }

    QSqlField field = sqlModel->record().field(index.column());

    if(field.type() == QVariant::Int)
    {
        QSpinBox* spinBox = qobject_cast<QSpinBox *>(editor);
        sqlModel->setData(index, spinBox->value(), Qt::EditRole);
    }
    else if (QString::compare(field.name(), "FLAG", Qt::CaseInsensitive) == 0)
    {
        ImageLoaderWidget* imgLoader = qobject_cast<ImageLoaderWidget *>(editor);
        QString base64Image = imgLoader->getBase64Image();
        sqlModel->setData(index, base64Image, Qt::EditRole);
    }
    else if (field.name().startsWith("DATE", Qt::CaseInsensitive) ||
             field.name().compare("BIRTHDATE", Qt::CaseInsensitive) == 0)
    {
        QDateEdit *dateEdit = qobject_cast<QDateEdit *>(editor);
        sqlModel->setData(index, dateEdit->date(), Qt::EditRole);
    }
    else
    {
        QSqlRelationalDelegate::setModelData(editor, model, index);
    }


    if (sqlModel->tableName() == "ORDERS")
    {
        int uidTC = sqlModel->data(sqlModel->index(index.row(), sqlModel->fieldIndex("TOURNAMENT_CATEGORY_FK"))).toInt();
        int uidT = DBUtils::get("TOURNAMENT_FK", "TOURNAMENT_CATEGORIES", uidTC).toInt();
        int newUidTc = DBUtils::findUidToutnamentCategory(
                    uidT,
                    sqlModel->data(sqlModel->index(index.row(), sqlModel->fieldIndex("BIRTHDATE"))).toDate(),
                    sqlModel->data(sqlModel->index(index.row(), sqlModel->fieldIndex("SEX_FK"))).toInt(),
                    sqlModel->data(sqlModel->index(index.row(), sqlModel->fieldIndex("WEIGHT"))).toDouble(),
                    sqlModel->data(sqlModel->index(index.row(), sqlModel->fieldIndex("TYPE_FK"))).toInt()
                    );
        QModelIndex indexTC = sqlModel->index(index.row(), sqlModel->fieldIndex("TOURNAMENT_CATEGORY_FK"));
        qDebug() << "find TC:" << newUidTc;
        if (newUidTc <= 0)
        {
            sqlModel->setData(indexTC, QVariant(), Qt::EditRole);
        }
        else
        {
            sqlModel->setData(indexTC, newUidTc, Qt::EditRole);
        }
        emit sqlModel->dataChanged(indexTC, indexTC);
    }
}

void MyQSqlRelationalDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& _index) const
{

    drawBackground(painter, option, _index);
    drawFocus(painter, option, option.rect);

    QModelIndex index = _index;
    const MySortFilterProxyModel *proxyModel = qobject_cast<const MySortFilterProxyModel *>(index.model());
    if (proxyModel)
    {
        index = proxyModel->mapToSource(index);
    }

    const QSqlRelationalTableModel *sqlModel = qobject_cast<const  QSqlRelationalTableModel *>(index.model());
    QSqlField field = sqlModel->record().field(index.column());

    if (QString::compare(field.name(), "FLAG", Qt::CaseInsensitive) == 0)
    {
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

    }
    else if (field.name().startsWith("DATE", Qt::CaseInsensitive) ||
        field.name().compare("BIRTHDATE", Qt::CaseInsensitive) == 0)
    {
        QString str = " " + index.data(Qt::EditRole).toDate().toString("dd.MM.yyyy");
        QFontMetrics metrics(painter->font());
        str = metrics.elidedText(str, Qt::ElideRight, option.rect.width());
        painter->drawText(option.rect, Qt::AlignVCenter, str);
        return ;
    }
    else
    {
        QSqlRelationalDelegate::paint(painter, option, index);
    }
}

QSize MyQSqlRelationalDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
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
    sqlModel = qobject_cast<QSqlRelationalTableModel *>(sourceModel);

    QSqlRecord record = QSqlDatabase::database().record(sqlModel->tableName());
    if (sqlModel->tableName() == "TOURNAMENT_CATEGORIES")
    {
        columnsForSort
            << record.indexOf("TOURNAMENT_FK")
            << record.indexOf("TYPE_FK")
            << record.indexOf("AGE_FROM")
            << record.indexOf("AGE_TILL")
            << record.indexOf("SEX_FK")
            << record.indexOf("WEIGHT_FROM")
            << record.indexOf("WEIGHT_TILL");
    }
    if (sqlModel->tableName() == "TOURNAMENTS")
    {
        columnsForSort
            << record.indexOf("UID");
    }
    if (sqlModel->tableName() == "ORDERS")
    {
        columnsForSort
            << record.indexOf("SECOND_NAME")
            << record.indexOf("FIRST_NAME")
            << record.indexOf("PATRONYMIC")
            << record.indexOf("BIRTHDATE")
            << record.indexOf("SEX_FK")
            << record.indexOf("WEIGHT")
            << record.indexOf("TYPE_FK")
            << record.indexOf("TOURNAMENT_CATEGORY_FK");
    }

}

bool MySortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
    for (int column = 0; column < filters.size(); ++column)
    {
        const QStringList& list = filters[column];
        if (list.isEmpty()) continue;

        for (const QString& filter : list)
        {
            QModelIndex index = sqlModel->index(sourceRow, column, sourceParent);
            QVariant data = sqlModel->data(index);
            QString text;
            if (sqlModel->record().field(index.column()).name().startsWith("DATE", Qt::CaseInsensitive))
                text = data.toDate().toString("dd.MM.yyyy");
            else
                text = data.toString();
            if (!text.contains(filter, Qt::CaseInsensitive))
                return false;
        }
    }
    return true;
}

bool MySortFilterProxyModel::lessThan(const QModelIndex& source_left, const QModelIndex& source_right) const
{
    if (QSortFilterProxyModel::lessThan(source_left, source_right))
    {
        return true;
    }
    else if (QSortFilterProxyModel::lessThan(source_right, source_left))
    {
        return false;
    }
    if(sqlModel)
    {
        for (const int column : columnsForSort)
        {
            if (QSortFilterProxyModel::lessThan(sqlModel->index(source_left .row(), column),
                                                sqlModel->index(source_right.row(), column)))
            {
                return true;
            }
            else if (QSortFilterProxyModel::lessThan(sqlModel->index(source_right.row(), column),
                                                      sqlModel->index(source_left .row(), column)))
            {
                return false;
            }
        }
    }
    return false;
}

SqlTableManager::SqlTableManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SqlTableManager),
    model(0)
{
    ui->setupUi(this);
}

void SqlTableManager::setSqlTable(const QString& table,
                                  const QString& whereStatement,
                                  QMap<QString, QVariant> columnValue)
{
    if (model)
    {
        qDebug() << "Повторная попытка setSqlTable";
        return;
    }
    model = new QSqlRelationalTableModel(this);

    model->setTable(table);
    if (!whereStatement.isEmpty())
        model->setFilter(whereStatement);

    model->setJoinMode(QSqlRelationalTableModel::JoinMode::LeftJoin);

    model->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);


    QMap<QString, QSqlRecord > map = DBUtils::get_NAME_RUS__RELATION_TABLE_NAME();
    QMap<int, int> columnSortColumn;
    for (int i = 0; i < model->columnCount(); ++i)
    {
        QString eng = model->headerData(i, Qt::Horizontal).toString();
        if (map.contains(eng))
        {
            model->setHeaderData(i, Qt::Horizontal, map[eng].value("NAME_RUS"));

            QString relTable = map[eng].value("RELATION_TABLE_NAME").toString();
            if (!relTable.isEmpty())
            {
                model->setRelation(model->fieldIndex(eng), QSqlRelation(relTable, "UID", "NAME"));
                columnSortColumn[i] = map[eng].value("DISPLAY_COLUMN").toInt();
            }
        }
    }


    QMapIterator<QString, QVariant> iter(columnValue);
    QMap<int, QVariant> columnDefaultValue;
    while (iter.hasNext())
    {
        iter.next();
        columnDefaultValue[model->fieldIndex(iter.key())] = iter.value();
    }

    model->select();
    while (model->canFetchMore())
        model->fetchMore();

    for (int i = 0; i < model->columnCount(); ++i)
    {
        QSqlTableModel* childModel = model->relationModel(i);
        if (childModel)
        {
            childModel->sort(columnSortColumn[i], Qt::AscendingOrder);
        }
    }


    proxyModel = new MySortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    proxyModel->setDynamicSortFilter(false);
    proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);


    ui->tableView_2->setModel(proxyModel);
    {
        QSet<QString> tableSort0;
        tableSort0 << "TOURNAMENTS";
        if (tableSort0.contains(table))
            ui->tableView_2->sortByColumn(0, Qt::SortOrder::AscendingOrder);
        else
            ui->tableView_2->sortByColumn(1, Qt::SortOrder::AscendingOrder);
    }
    ui->tableView_2->setItemDelegate(new MyQSqlRelationalDelegate(ui->tableView_2, columnDefaultValue));
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
        if (columnDefaultValue.contains(i))
        {
            ui->tableView_2->hideColumn(i);
        }
        else
        {
            QLineEdit *edit = new QLineEdit(this);
            edit->setPlaceholderText(model->headerData(i, Qt::Horizontal).toString());
            alignedLayout->addWidget(edit);
            connect(edit, &QLineEdit::textChanged, [i, this](const QString& str){
                QStringList list = str.split(" ", QString::SkipEmptyParts);
                proxyModel->setMyFilter(i, list);
                alignedLayout->invalidate();
            });
        }
    }

    ui->widget2222->setLayout(alignedLayout);
    alignedLayout->setParent(ui->widget2222);

    alignedLayout->setTableColumnsToTrack(ui->tableView_2->horizontalHeader());
    connect(ui->tableView_2->horizontalHeader(), &QHeaderView::sectionResized, alignedLayout, &ColumnAlignedLayout::invalidate);
    connect(ui->tableView_2->horizontalScrollBar(), &QScrollBar::valueChanged, alignedLayout, &ColumnAlignedLayout::invalidate);

    connect(ui->pushButtonSave, &QPushButton::clicked, this, &SqlTableManager::submitAllChanges);
    connect(ui->pushButtonCancel, &QPushButton::clicked, [this](){
        model->revertAll();
    });
    connect(ui->pushButtonInsert, &QPushButton::clicked, [this](){
        int row = model->rowCount();
        model->insertRow(row);
        ui->tableView_2->scrollTo(proxyModel->mapFromSource(model->index(row, 0)), QAbstractItemView::PositionAtCenter);
    });
    connect(ui->pushButtonDelete, &QPushButton::clicked, [this](){
        qDebug() << "DELETING";
        for (QModelIndex index : ui->tableView_2->selectionModel()->selectedRows())
        {
            if (model->removeRow(proxyModel->mapToSource(index).row()))
                qDebug() << "remove: "  << index.row();
            else
                qDebug() << "NOT remove: "  << index.row();

//            if (proxyModel->removeRow(index.row()))
//                qDebug() << "remove: "  << index.row();
//            else
//                qDebug() << "NOT remove: "  << index.row();
        }
        submitAllChanges();
    });

    connect(ui->pushButtonSaveInExcel, &QPushButton::clicked, [this](){
        saveToExcel();
    });
}

void SqlTableManager::updateMyData(int row)
{
    model->select();
    while (model->canFetchMore())
        model->fetchMore();
    proxyModel->invalidate();
    ui->tableView_2->setCurrentIndex(proxyModel->index(row, 0));
    alignedLayout->invalidate();
}

SqlTableManager::~SqlTableManager()
{
    delete ui;
}

QModelIndex SqlTableManager::getUidIndexOfSelectedRow()
{
    QModelIndexList rows = ui->tableView_2->selectionModel()->selectedRows();
    if (rows.count())
        return rows[0];
    return QModelIndex();
}

void SqlTableManager::submitAllChanges()
{
    if (model->submitAll())
    {
        qDebug() << "Save all";
        while (model->canFetchMore())
            model->fetchMore();
        proxyModel->invalidate();
        //ui->tableView_2->resizeColumnsToContents();
        alignedLayout->invalidate();
    }
    else
    {
        qDebug() << model->lastError();
        QMessageBox::warning(this, "", "Некорректные данные:\n" + model->lastError().databaseText() + "\n" + model->lastError().driverText());
        //model->revertAll();
    }
}



void SqlTableManager::saveToExcel()
{
    QProgressDialog progress("", "Cancel", 0, proxyModel->columnCount() * (proxyModel->rowCount() + 1), this);
    progress.setWindowTitle("Save in Excel");
    progress.setWindowModality(Qt::ApplicationModal);
    progress.setMinimumDuration(0);
    progress.setValue(0);
    QApplication::processEvents();

    QAxWidget excel("Excel.Application", this);
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
    workbooks->dynamicCall("Add");
    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");
    QAxObject *sheets = workbook->querySubObject("WorkSheets");
    QAxObject *sheet = sheets->querySubObject("Item(int)", 1);

    bool wasBreak = false;
    int iter = 0;
    for (int column = 0; !wasBreak && column < proxyModel->columnCount(); ++column)
    {
        progress.setValue(iter++);
        if (progress.wasCanceled())
        {
            wasBreak = true;
            break;
        }
        QApplication::processEvents();

        ExcelUtils::setValue(sheet, 1, column + 1, model->headerData(column, Qt::Horizontal, Qt::DisplayRole).toString());
    }


    for (int row = 0; !wasBreak && row < proxyModel->rowCount(); ++row)
    {
        for (int column = 0; column < proxyModel->columnCount(); ++column)
        {
            progress.setValue(iter++);
            if (progress.wasCanceled())
            {
                wasBreak = true;
                break;
            }
            QApplication::processEvents();

            QModelIndex index = proxyModel->index(row, column);
            QVariant data = index.data();
            QString str;
            if (data.type() == QVariant::Double)
            {
                str = DBUtils::roundDouble(data.toDouble(), 4).replace(".", ",");
            }
            else if (QString::compare(model->record().field(index.column()).name(), "FLAG", Qt::CaseInsensitive) == 0)
            {
                str = "";
            }
            else
            {
                str = data.toString();
            }
            ExcelUtils::setValue(sheet, row + 2, column + 1, str);
        }
    }

    for (int column = 0; column < proxyModel->columnCount(); ++column)
        ExcelUtils::setColumnAutoFit(sheet, column + 1);

    ExcelUtils::setBorder(sheet, 1, 1, proxyModel->rowCount() + 1, proxyModel->columnCount(), 2);

    delete sheet;
    delete sheets;
    delete workbook;
    delete workbooks;
    excel.setProperty("Visible", true);
}


