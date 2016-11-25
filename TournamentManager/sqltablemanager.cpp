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
    QItemDelegate(parent),
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

    const MyQSqlRelationalTableModel *sqlModel =
            qobject_cast<const MyQSqlRelationalTableModel *>(index.model());
    if (!sqlModel)
        return QItemDelegate::createEditor(parent, i, index);

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



    if (sqlModel->relationModel(index.column()))
    {
        if (sqlModel->tableName() == "ORDERS" && sqlModel->fieldIndex("TOURNAMENT_CATEGORY_FK") == index.column())
        {
            return 0;
        }

        QString whereStatement = "";

        if (sqlModel->fieldIndex("REGION_FK") == index.column())
        {
            whereStatement = "COUNTRY_FK = " + sqlModel->index(index.row(), sqlModel->fieldIndex("COUNTRY_FK")).data(Qt::EditRole).toString();
        }
        if (sqlModel->fieldIndex("REGION_UNIT_FK") == index.column())
        {
            whereStatement = "REGION_FK = " + sqlModel->index(index.row(), sqlModel->fieldIndex("REGION_FK")).data(Qt::EditRole).toString();
        }
        if (sqlModel->fieldIndex("CLUB_FK") == index.column() && sqlModel->tableName() == "ORDERS")
        {
            whereStatement = "REGION_UNIT_FK = " + sqlModel->index(index.row(), sqlModel->fieldIndex("REGION_UNIT_FK")).data(Qt::EditRole).toString();
        }
        if (sqlModel->fieldIndex("COACH_FK") == index.column() && sqlModel->tableName() == "ORDERS")
        {
            whereStatement = "CLUB_FK = " + sqlModel->index(index.row(), sqlModel->fieldIndex("CLUB_FK")).data(Qt::EditRole).toString();
        }
        if (sqlModel->fieldIndex("SEX_FK") == index.column() && sqlModel->tableName() == "ORDERS")
        {
            QString str;
            {
                QSqlQuery q;
                q.prepare("SELECT DISTINCT SEX_FK FROM TOURNAMENT_CATEGORIES WHERE TOURNAMENT_FK = ?");
                int uidTC = sqlModel->index(index.row(), sqlModel->fieldIndex("TOURNAMENT_CATEGORY_FK")).data(Qt::EditRole).toInt();
                int uidT = DBUtils::get("TOURNAMENT_FK", "TOURNAMENT_CATEGORIES", uidTC).toInt();
                q.addBindValue(uidT);
                q.exec();
                while(q.next())
                {
                    if (!str.isEmpty()) str += ", ";
                    str += q.value("SEX_FK").toString();
                }
                //qDebug() << str;
            }
            whereStatement = "UID IN (" + str + ")";
        }
        if (sqlModel->fieldIndex("TYPE_FK") == index.column() && sqlModel->tableName() == "ORDERS")
        {
            QString str;
            {
                QSqlQuery q;
                q.prepare("SELECT DISTINCT TYPE_FK FROM TOURNAMENT_CATEGORIES WHERE TOURNAMENT_FK = ?");
                int uidTC = sqlModel->index(index.row(), sqlModel->fieldIndex("TOURNAMENT_CATEGORY_FK")).data(Qt::EditRole).toInt();
                int uidT = DBUtils::get("TOURNAMENT_FK", "TOURNAMENT_CATEGORIES", uidTC).toInt();
                q.addBindValue(uidT);
                q.exec();
                while(q.next())
                {
                    if (!str.isEmpty()) str += ", ";
                    str += q.value("TYPE_FK").toString();
                }
                //qDebug() << str;
            }
            whereStatement = "UID IN (" + str + ")";
        }


        QSqlTableModel *childModel = sqlModel->relationModel(index.column(), parent, whereStatement);
        int seletedRow = -1;
        for (int r = 0; r < childModel->rowCount(); ++r)
        {
            if (childModel->index(r, 0).data().toInt() == index.data(Qt::EditRole).toInt())
            {
                seletedRow = r;
                break;
            }
        }
        //qDebug() << "seletedRow: " << seletedRow;

        QComboBox *combo = new QComboBox(parent);
        combo->setModel(childModel);
        combo->setModelColumn(sqlModel->displayColumn(index.column()));
        combo->setMaxVisibleItems(1000);
        combo->setCurrentIndex(seletedRow);
        combo->installEventFilter(const_cast<MyQSqlRelationalDelegate *>(this));
        return combo;
    }

    if(field.type() == QVariant::Int)
    {
        QSpinBox* spinBox = new QSpinBox(parent);
        spinBox->setMaximum(100500);
        spinBox->setValue(index.data().toInt());
        // installEventFilter ???
        return spinBox;
    }


    if (field.name().startsWith("DATE", Qt::CaseInsensitive) ||
        field.name().compare("BIRTHDATE", Qt::CaseInsensitive) == 0)
    {
        QDateEdit *dateEdit = new QDateEdit(parent);
        dateEdit->setDate(index.data(Qt::EditRole).toDate());
        // installEventFilter ???
        return dateEdit;
    }



    return QItemDelegate::createEditor(parent, i, index);
}

void MyQSqlRelationalDelegate::setModelData(QWidget* editor,
                                            QAbstractItemModel* model,
                                            const QModelIndex& _index) const
{
    MySortFilterProxyModel *proxyModel = qobject_cast<MySortFilterProxyModel *>(model);

    QModelIndex index = _index;
    if (proxyModel)
    {
        index = proxyModel->mapToSource(index);
        model = proxyModel->sourceModel();
    }

    MyQSqlRelationalTableModel *sqlModel = qobject_cast<MyQSqlRelationalTableModel *>(model);
    if (!sqlModel)
    {
        QItemDelegate::setModelData(editor, model, index);
        return;
    }


    QMapIterator<int, QVariant> iter(columnDefaultValue);
    while (iter.hasNext()) {
        iter.next();
        sqlModel->setData(sqlModel->index(index.row(), iter.key()), iter.value());
    }



    QSqlField field = sqlModel->record().field(index.column());

    if (QString::compare(field.name(), "FLAG", Qt::CaseInsensitive) == 0)
    {
        ImageLoaderWidget* imgLoader = qobject_cast<ImageLoaderWidget *>(editor);
        QString base64Image = imgLoader->getBase64Image();
        sqlModel->setData(index, base64Image, Qt::EditRole);
    }
    else if (sqlModel->relationModel(index.column()))
    {
        QComboBox *combo = qobject_cast<QComboBox *>(editor);
        QSqlTableModel *childModel = qobject_cast<QSqlTableModel *>(combo->model());
        int currentItem = combo->currentIndex();
        QVariant data = childModel->index(currentItem, 0).data(Qt::EditRole);
        //qDebug() << data;
        sqlModel->setData(index,
                          data.toInt(),
                          Qt::EditRole);
    }
    else if(field.type() == QVariant::Int)
    {
        QSpinBox* spinBox = qobject_cast<QSpinBox *>(editor);
        sqlModel->setData(index, spinBox->value(), Qt::EditRole);
    }
    else if (field.name().startsWith("DATE", Qt::CaseInsensitive) ||
             field.name().compare("BIRTHDATE", Qt::CaseInsensitive) == 0)
    {
        QDateEdit *dateEdit = qobject_cast<QDateEdit *>(editor);
        sqlModel->setData(index, dateEdit->date(), Qt::EditRole);
    }
    else
    {
        QItemDelegate::setModelData(editor, sqlModel, index);
    }



    if (sqlModel->tableName() == "ORDERS")
    {
        int sexUID     = sqlModel->index(index.row(), sqlModel->fieldIndex("SEX_FK"    )).data(Qt::EditRole).toInt();
        int typeUID    = sqlModel->index(index.row(), sqlModel->fieldIndex("TYPE_FK"   )).data(Qt::EditRole).toInt();
        double weight  = sqlModel->index(index.row(), sqlModel->fieldIndex("WEIGHT"    )).data(Qt::EditRole).toDouble();
        QDate birthday = sqlModel->index(index.row(), sqlModel->fieldIndex("BIRTHDATE" )).data(Qt::EditRole).toDate();

        int uidTC = sqlModel->index(index.row(), sqlModel->fieldIndex("TOURNAMENT_CATEGORY_FK")).data(Qt::EditRole).toInt();
        int uidT = DBUtils::get("TOURNAMENT_FK", "TOURNAMENT_CATEGORIES", uidTC).toInt();
        int newUidTc = DBUtils::findUidToutnamentCategory(uidT, birthday, sexUID, weight, typeUID);

        QModelIndex indexTC = sqlModel->index(index.row(), sqlModel->fieldIndex("TOURNAMENT_CATEGORY_FK"));
//        qDebug() << "old, new:" << uidT << birthday << sexUID << weight << typeUID << uidTC << newUidTc
//                 << indexTC
//                 << proxyModel->mapFromSource(indexTC);
        if (1 <= newUidTc)
            sqlModel->setData(indexTC, newUidTc);

        emit sqlModel->dataChanged(indexTC, indexTC);
        if (proxyModel)
            emit proxyModel->dataChanged(proxyModel->mapFromSource(indexTC),
                                         proxyModel->mapFromSource(indexTC));

        QVector<int> columns;
        columns
              << sqlModel->fieldIndex("COUNTRY_FK")
              << sqlModel->fieldIndex("REGION_FK")
              << sqlModel->fieldIndex("REGION_UNIT_FK")
              << sqlModel->fieldIndex("CLUB_FK")
              << sqlModel->fieldIndex("COACH_FK");

        int startPos = columns.indexOf(index.column());
        if (startPos != -1)
        {
            for (int i = startPos + 1; i < columns.size(); ++i)
            {
                QModelIndex ind = sqlModel->index(index.row(), columns[i]);
                sqlModel->setData(ind, QVariant());
                emit sqlModel->dataChanged(ind, ind);
                if (proxyModel)
                    emit proxyModel->dataChanged(proxyModel->mapFromSource(ind),
                                                 proxyModel->mapFromSource(ind));
            }
        }
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

    const MyQSqlRelationalTableModel *sqlModel = qobject_cast<const  MyQSqlRelationalTableModel *>(index.model());
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
        QItemDelegate::paint(painter, option, index);
    }
}

QSize MyQSqlRelationalDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    const MySortFilterProxyModel *proxyModel = qobject_cast<const MySortFilterProxyModel *>(index.model());

    if (proxyModel)
    {
        return sizeHint(option, proxyModel->mapToSource(index));
    }

    const MyQSqlRelationalTableModel *sqlModel = qobject_cast<const  MyQSqlRelationalTableModel *>(index.model());
    if (!sqlModel)
    {
        return QItemDelegate::sizeHint(option, index);

    }

    if (QString::compare(sqlModel->record().field(index.column()).name(), "FLAG", Qt::CaseInsensitive) == 0)
    {
        return QSize(300, 100);
    }
    return QItemDelegate::sizeHint(option, index);
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
    sqlModel = qobject_cast<MyQSqlRelationalTableModel *>(sourceModel);

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

    if (sqlModel->tableName() == "REGIONS")
    {
        columnsForSort
            << record.indexOf("COUNTRY_FK")
            << record.indexOf("NAME");
    }
    if (sqlModel->tableName() == "REGION_UNITS")
    {
        columnsForSort
            << record.indexOf("COUNTRY_FK")
            << record.indexOf("REGION_FK")
            << record.indexOf("NAME");
    }

    if (sqlModel->tableName() == "CLUBS")
    {
        columnsForSort
            << record.indexOf("COUNTRY_FK")
            << record.indexOf("REGION_FK")
            << record.indexOf("REGION_UNIT_FK")
            << record.indexOf("NAME");
    }
    if (sqlModel->tableName() == "COACHS")
    {
        columnsForSort
            << record.indexOf("CLUB_FK")
            << record.indexOf("NAME");
    }
}

bool MySortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
    if (!sqlModel->index(sourceRow, 0).data(Qt::EditRole).toInt())
        return true;
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
                                  QString filter,
                                  QMap<QString, QVariant> columnValue)
{
    if (model)
    {
        qDebug() << "Повторная попытка setSqlTable";
        return;
    }
    model = new MyQSqlRelationalTableModel(this);

    model->setTable(table);

    QMapIterator<QString, QVariant> iterator(columnValue);
    while (iterator.hasNext())
    {
        iterator.next();
        if (!filter.isEmpty()) filter += " AND ";
        filter += iterator.key() + " = " + iterator.value().toString();
    }
    if (!filter.isEmpty())
    {
        model->setFilter(filter);
    }

    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    QMap<QString, QSqlRecord > map = DBUtils::get_NAME_RUS__RELATION_TABLE_NAME();
    for (int i = 0; i < model->columnCount(); ++i)
    {
        QString eng = model->headerData(i, Qt::Horizontal).toString();
        if (map.contains(eng))
        {
            model->setHeaderData(i, Qt::Horizontal, map[eng].value("NAME_RUS"));

            QString relTable = map[eng].value("RELATION_TABLE_NAME").toString();
            if (!relTable.isEmpty())
            {
                model->setRelation(model->fieldIndex(eng), relTable, "NAME");
            }
        }
    }

    model->select();
    while (model->canFetchMore())
        model->fetchMore();

    QMapIterator<QString, QVariant> iter(columnValue);
    QMap<int, QVariant> columnDefaultValue;
    while (iter.hasNext())
    {
        iter.next();
        columnDefaultValue[model->fieldIndex(iter.key())] = iter.value();
    }
    this->columnDefaultValue = columnDefaultValue;



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
    lineEdits.clear();
    for (int i = 0; i < model->columnCount(); ++i)
    {
        if (columnDefaultValue.contains(i))
        {
            ui->tableView_2->hideColumn(i);
            lineEdits << 0;
        }
        else
        {
            QLineEdit *edit = new QLineEdit(this);
            if (model->headerData(i, Qt::Horizontal).toString() == "Флаг")
            {
                edit->setEnabled(false);
            }
            lineEdits << edit;
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
        //ui->tableView_2->scrollTo(proxyModel->mapFromSource(model->index(row, 0)), QAbstractItemView::PositionAtCenter);
        ui->tableView_2->scrollToBottom();
    });
    connect(ui->pushButtonDelete, &QPushButton::clicked, [this](){
        for (QModelIndex index : ui->tableView_2->selectionModel()->selectedRows())
        {
            if (!model->removeRow(proxyModel->mapToSource(index).row()))
                qDebug() << "NOT remove!";
            //qDebug() << index << index.data();
        }
        submitAllChanges();
    });

    connect(ui->pushButtonSaveInExcel, &QPushButton::clicked, [this](){
        saveToExcel();
    });
}

void SqlTableManager::setFilter(const QString& columnName, const QString& text)
{
    lineEdits[model->fieldIndex(columnName)]->setText(text);
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
    if (model->isDirty())
    {
        QMessageBox::warning(0, "", "Сохраните изменения и выберите запись");
        return QModelIndex();
    }

    QModelIndexList rows = ui->tableView_2->selectionModel()->selectedRows();
    if (1 < rows.count())
    {
        QMessageBox::warning(0, "",
                             "Количество выделеных строк: " + QString::number(rows.count()) + "\n" +
                             "Выберите какую-нибудь одну строку");
        return QModelIndex();
    }
    if (rows.count())
        return rows[0];
    return QModelIndex();
}

bool SqlTableManager::addNewName(const QString& name)
{
    QSqlRecord rec = model->record();

    QMapIterator<int, QVariant> iter(columnDefaultValue);
    while (iter.hasNext()) {
        iter.next();
        rec.setValue(iter.key(), iter.value());
    }
    rec.setValue("NAME", name);
    //qDebug() << rec;
    bool ok = model->insertRecord(-1, rec) && submitAllChanges();
    if (ok)
    {
        updateMyData(proxyModel->mapFromSource(model->index(model->rowCount() - 1, 0)).row());
        //qDebug() << model->record();
    }
    return ok;
}

bool SqlTableManager::submitAllChanges()
{
    if (model->submitAll())
    {
        //qDebug() << "Save all";
        while (model->canFetchMore())
            model->fetchMore();
        proxyModel->invalidate();
//        alignedLayout->invalidate();
        return true;
    }
    else
    {
        qDebug() << model->lastError();
        QMessageBox::warning(this, "", "Некорректные данные:\n" + model->lastError().databaseText() + "\n" + model->lastError().driverText());
        //model->revertAll();
        return false;
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




MyQSqlRelationalTableModel::MyQSqlRelationalTableModel(QObject* parent) : QSqlTableModel(parent)
{

}

void MyQSqlRelationalTableModel::setTable(const QString& table)
{
    QSqlTableModel::setTable(table);

    int size = QSqlDatabase::database().record(table).count();
    hashs = QVector<QMap<int, QVariant>>(size);
    tables = QVector<QString>(size);
    displayColumns = QVector<int>(size);
}

QSqlTableModel*MyQSqlRelationalTableModel::relationModel(int column, QObject* parent, const QString& whereStatment) const
{
    if (!haveRelation(column))
        return 0;
    QSqlTableModel* model = new QSqlTableModel(parent);
    model->setTable(tables[column]);
    model->setFilter(whereStatment);
    model->sort(displayColumns[column], Qt::AscendingOrder);
    model->select();
    while (model->canFetchMore())
        model->fetchMore();
    return model;
}

void MyQSqlRelationalTableModel::setRelation(int column, const QString& table, const QString& columnName)
{
    tables[column] = table;
    displayColumns[column] = QSqlDatabase::database().record(table).indexOf(columnName);
}

QVariant MyQSqlRelationalTableModel::data(const QModelIndex& index, int role) const
{
    QVariant data = QSqlTableModel::data(index, role);
    if (role == Qt::DisplayRole && haveRelation(index.column()))
    {
        return hashs[index.column()][data.toInt()];
    }
    return data;
}

bool MyQSqlRelationalTableModel::haveRelation(int column) const
{
    return 0 <= column && column < tables.size() && !tables[column].isEmpty();
}

int MyQSqlRelationalTableModel::displayColumn(int column) const
{
    return displayColumns[column];
}

bool MyQSqlRelationalTableModel::select()
{
    bool result = QSqlTableModel::select();
    for (int c = 0; c < tables.size(); ++c)
    {
        hashs[c].clear();
        if (!haveRelation(c)) continue;
        QSqlTableModel* model = relationModel(c);
        for (int r = 0; r < model->rowCount(); ++r)
        {
            QSqlRecord record = model->record(r);
            hashs[c][record.value(0).toInt()] = record.value(displayColumns[c]);
        }
        delete model;
    }
    return result;
}
