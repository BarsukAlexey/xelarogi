#include "renderareawidget.h"

RenderAreaWidget::RenderAreaWidget(QWidget *parent, int widthCell, int heightCell) :
    QWidget(parent),
    tournamentCategories(-1),
    fontSize(8),
    countRows(0),
    countColumns(0),
    widthCell(widthCell),
    heightCell(heightCell)
{
    resizeWidgetAccordingToGrid();
}


QPoint RenderAreaWidget::getCell(int v)
{
    QPoint p;
    p.setY(countColumns - Utils::log2(v) - 1);
    p.setX( (1 << (p.y() + 1)) * ((1 << (countColumns - p.y())) - 1 - v) + (1 << p.y()) - 1);
    p.setX(p.x() + 1);
    return p;
}




void RenderAreaWidget::paintEvent(QPaintEvent* )
{
//    QTime time; time.start();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(painter.viewport(), Qt::white);

    if (tournamentCategories <= 0) return ;

    if (nodes.empty()) return;

    for (const DBUtils::NodeOfTournirGrid& node : nodes)
    {
        for (int child : {2 * node.v, 2 * node.v + 1})
        {
            if (child <= nodes.size())
            {
                paintLine(getCell(node.v), getCell(child), painter);
            }
        }
    }

    for (const DBUtils::NodeOfTournirGrid& node : nodes)
    {
        QPoint cell = getCell(node.v);
        paintNodeOfGrid(cell.x(), cell.y(), painter, node);
    }

//   qDebug() << "Grid is painted: " << time.elapsed();
}

void RenderAreaWidget::mousePressEvent(QMouseEvent* event)
{
    QPoint p(event->y() / heightCell, event->x() / widthCell);

    DBUtils::NodeOfTournirGrid currentNode = noNode;
    for (const DBUtils::NodeOfTournirGrid& node : DBUtils::getNodes(tournamentCategories))
        if (getCell(node.v) == p)
            currentNode = node;
    if (currentNode.v == noNode.v) return;

    if (event->button() == Qt::RightButton){
        if (selectedNode.v != noNode.v)
        {
            if (selectedNode.v == currentNode.v && selectedNode.isFight)
            {
                QSqlQuery query;
query.prepare("UPDATE GRIDS SET ORDER_FK = ?, result = ? WHERE TOURNAMENT_CATEGORIES_FK = ? AND VERTEX = ?");
                query.bindValue(0, QVariant(QVariant::Int));
                query.bindValue(1, QVariant(QVariant::String));
                query.bindValue(2, tournamentCategories);
                query.bindValue(3, selectedNode.v);
                if (!query.exec())
                    qDebug() << __PRETTY_FUNCTION__ << " " << query.lastError().text() << "\n" << query.lastQuery();
            }
            selectedNode = noNode;
        }
    } else if (event->button() == Qt::LeftButton){
        if (selectedNode.v == noNode.v)
        {
            selectedNode = currentNode;
        }
        else
        {
            DBUtils::NodeOfTournirGrid node0 = selectedNode;
            DBUtils::NodeOfTournirGrid node1 = currentNode;
            selectedNode = noNode;
            if (!node0.isFight && !node1.isFight)
            {
                DBUtils::swapNodesOfGrid(tournamentCategories, node0.v, node1.v);
            }
            if (node0.v > node1.v) std::swap(node0, node1);
            if (2 * node0.v == node1.v || 2 * node0.v + 1 == node1.v)
            {
                RenderAreaResultDialog dlg(DBUtils::getSecondNameAndFirstName(node1.UID), this);
                dlg.exec();

                node0.result = dlg.getResult();

                QString orderUID;
                {
                    QSqlQuery query;
query.prepare("SELECT * FROM GRIDS WHERE TOURNAMENT_CATEGORIES_FK = ? AND VERTEX = ?");
                    query.bindValue(0, tournamentCategories);
                    query.bindValue(1, node1.v);
                    if (!( query.exec() && query.next()))
                        qDebug() << __PRETTY_FUNCTION__ << " " << query.lastError().text() << "\n" << query.lastQuery();
                    orderUID = query.value("ORDER_FK").toString();
                }
                QSqlQuery query;
query.prepare("UPDATE GRIDS SET ORDER_FK = ?, RESULT = ? WHERE TOURNAMENT_CATEGORIES_FK = ? AND VERTEX = ?");
                query.bindValue(0, orderUID);
                query.bindValue(1, node0.result);
                query.bindValue(2, tournamentCategories);
                query.bindValue(3, node0.v);
                if (!query.exec())
                    qDebug() << __PRETTY_FUNCTION__ << " " << query.lastError().text() << "\n" << query.lastQuery();
            }
        }
    }
    nodes = DBUtils::getNodes(tournamentCategories);
    repaint();
    emit iChangeToutGrid();
}





void RenderAreaWidget::paintNodeOfGrid(int i, int j, QPainter& painter, const DBUtils::NodeOfTournirGrid& node)
{
    QRect rect(j * widthCell, i * heightCell, widthCell, heightCell);
    if (node.v == selectedNode.v)
    {
        painter.fillRect(rect, QBrush(Qt::green));
        painter.setPen(Qt::black);
        painter.drawRect(rect);
    }
    else if (node.v & 1)
    {
        QLinearGradient gradient(rect.topLeft(), rect.bottomRight()); // diagonal gradient from top-left to bottom-right
        gradient.setColorAt(1, Qt::white);
        gradient.setColorAt(0, QColor("#ffbfc0"));
        painter.fillRect(rect, gradient);

        painter.setPen(QColor("#ff0001"));
        painter.drawRect(rect);
    }
    else
    {
        QLinearGradient gradient(rect.topLeft(), rect.bottomRight()); // diagonal gradient from top-left to bottom-right
        gradient.setColorAt(1, Qt::white);
        gradient.setColorAt(0, QColor("#c7c6ff"));
        painter.fillRect(rect, gradient);

        painter.setPen(QColor("#0301fb"));
        painter.drawRect(rect);
    }

    QString text(node.UID <= 0? "" : DBUtils::getSecondNameAndFirstName(node.UID));
    if (node.isFight)
    {
        if (0 < node.UID && !node.result.isEmpty())
            text += " (" + node.result + ")";
    }
    else
    {
        QString location = locationPlayer[node.UID];
        if (!location.isEmpty())
            text += " (" + location + ")";
    }
    painter.setPen(Qt::black);


    QFont font = painter.font();
    font.setPointSize(fontSize);
    painter.setFont(font);
    rect.setWidth(100500);
    rect.adjust(0, -100500, 0, +100500);
    painter.drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, " " + text);
}

void RenderAreaWidget::paintLine(const QPoint& aa, const QPoint& bb, QPainter& painter)
{
    QPoint a(qMin(aa.x(), bb.x()), qMin(aa.y(), bb.y()));
    QPoint b(qMax(aa.x(), bb.x()), qMax(aa.y(), bb.y()));
    painter.drawLine(QPoint(widthCell * (a.y() + 1), heightCell * (a.x())),
                     QPoint(widthCell *  b.y()     , heightCell * (b.x() + 1)));

}


void RenderAreaWidget::resizeWidgetAccordingToGrid()
{
    if (nodes.isEmpty())
    {
        countColumns = 0;
        countRows = 0;
        resize(0, 0);
    }
    else
    {
        countColumns = Utils::log2(nodes.last().v) + 1;
        countRows = 2 * (1 << (countColumns - 1)) - 1;
        //resize(countColumns * widthCell + 1, countRows * heightCell + 1);
        resize((countColumns + 1) * widthCell + 1, (countRows + 2) * heightCell + 1);
    }
    //qDebug() << "RenderAreaWidget::size: " << size();
}




void RenderAreaWidget::tournamentCategoryIsChanged(int tournamentCategory)
{
    this->tournamentCategories = tournamentCategory;
    selectedNode = noNode;
    if (tournamentCategory <= 0)
        nodes.clear();
    else
        nodes = DBUtils::getNodes(tournamentCategory);
    resizeWidgetAccordingToGrid();
    //QTime t; t.start();
    updateLocationPlayer();
    //qDebug() << "tournamentCategoryIsChanged:" << t.elapsed();
    repaint();
}

void RenderAreaWidget::widthChanged(int width)
{
    widthCell = width;
    resizeWidgetAccordingToGrid();
    repaint();
}

void RenderAreaWidget::heightChanged(int height)
{
    heightCell = height;
    resizeWidgetAccordingToGrid();
    repaint();
}

void RenderAreaWidget::onLocationDataIsChanged(const QVector<std::pair<DBUtils::TypeField, QString> >& locationData)
{
    this->locationData = locationData;
    updateLocationPlayer();
    repaint();
}

void RenderAreaWidget::updateLocationPlayer()
{
    locationPlayer.clear();
    for (const DBUtils::NodeOfTournirGrid& node : nodes)
    {
        locationPlayer[node.UID] = DBUtils::get(locationData, node.UID);
    }
}

void RenderAreaWidget::onFontSizeChanged(const int fontSize)
{
    this->fontSize = fontSize;
    repaint();
}



void RenderAreaWidget::onSaveInExcel()
{
    DialogChoseData dlg(DialogChoseData::Type::grids);
    if (dlg.exec() != QDialog::Accepted)
        return;

    QString directoryPath = QFileDialog::getExistingDirectory(this, tr("Выберите папку"), NULL, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (directoryPath.isNull()) return;
    //qDebug() << dir;


    QAxWidget excel("Excel.Application");
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
    workbooks->dynamicCall("Add");
    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");

    printTableGridInExcel(workbook, dlg, tournamentCategories, false, directoryPath, QVector<int>(), "", "");

    workbook->dynamicCall("Close()");
    delete workbook;
    delete workbooks;
    excel.dynamicCall("Quit()");
}

void RenderAreaWidget::clearSelection()
{
    selectedNode = noNode;
    repaint();
}



QPoint RenderAreaWidget::getCell(int v, int countColumns)
{
    QPoint p;
    p.setY(countColumns - Utils::log2(v) - 1);
    p.setX( (1 << (p.y() + 1)) * ((1 << (countColumns - p.y())) - 1 - v) + (1 << p.y()) - 1);
    return p;
}

void RenderAreaWidget::printTableGridInExcel(QAxObject* workbook, DialogChoseData& dlg, int tournamentCategory,
        bool likePointFighing, QString directoryPath, QVector<int> fightNumber, QString text, QString prefFileName)
{
    QAxObject *sheets   = workbook->querySubObject("WorkSheets");
    QAxObject *sheet    = sheets->querySubObject("Item( int )", 1);

    QVector<DBUtils::NodeOfTournirGrid> nodes = DBUtils::getNodes(tournamentCategory);
    if (nodes.empty()) return;
    qSort(nodes);

    const int countColumns = Utils::log2(nodes.last().v) + 1;
    int countPlayers = 0;
    for (const DBUtils::NodeOfTournirGrid& node : nodes) if (!node.isFight) ++countPlayers;

    int offset = 3;
    int maxRow = offset;
    int maxColumn = 1;

    QVector<std::pair<QString, QVector<std::pair<DBUtils::TypeField, QString> > > > data = dlg.getData();

    for (const DBUtils::NodeOfTournirGrid& node : nodes)
    {
        QPoint p = getCell(node.v, countColumns);

        maxRow    = qMax(maxRow   , p.x() + 1 + offset);
        maxColumn = qMax(maxColumn, p.y() + 1);

        if (node.isFight)
        {
            if (0 < node.UID)
            {
                ExcelUtils::setValue(sheet, p.x() + 1 + offset, p.y() + 1, DBUtils::getSecondNameAndFirstName(node.UID) + "\n" + node.result);
            }
        }
        else
        {
            QString message;
            for (int i = 0; i < data.size(); ++i)
            {
                message += DBUtils::get(data[i].second, node.UID) + (i + 1 == data.size()? "" : " ");
            }
            ExcelUtils::setValue(sheet, p.x() + 1 + offset, p.y() + 1, DBUtils::getSecondNameAndFirstName(node.UID) + "\n" + message);
        }

        ExcelUtils::setBorder(sheet, p.x() + 1 + offset, p.y() + 1, p.x() + 1 + offset, p.y() + 1, 3);

        for (int child : {2 * node.v, 2 * node.v + 1})
        {
            if (child <= nodes.size())
            {
                QPoint aa = getCell(node.v, countColumns);
                QPoint bb = getCell(child, countColumns);

                QPoint a(qMin(aa.x(), bb.x()), qMin(aa.y(), bb.y()));
                QPoint b(qMax(aa.x(), bb.x()), qMax(aa.y(), bb.y()));
                for (int row = a.x(); row <= b.x(); ++row)
                {
                    QAxObject *cell = sheet->querySubObject( "Cells( int, int )", row + 1 + offset, a.y() + 1);
                    QAxObject *border = cell->querySubObject("Borders(xlEdgeRight)");
                    border->setProperty("LineStyle", 1);
                    border->setProperty("Weight", 3);
                    delete border;
                    delete cell;

                    maxRow    = qMax(maxRow   , row + 1 + offset);
                    maxColumn = qMax(maxColumn, a.y() + 1);
                }
            }
        }
    }

    if (likePointFighing)
    {
        std::sort(nodes.begin(), nodes.end(),
            [](const DBUtils::NodeOfTournirGrid& lhs, const DBUtils::NodeOfTournirGrid& rhs)  -> bool
        {
            return lhs.v > rhs.v;
        });

        while (nodes.size() && !nodes.front().isFight) nodes.pop_front();

        for (int i = 0; i < nodes.size(); ++i)
        {
            QPoint p = getCell(nodes[i].v, countColumns);
            ExcelUtils::setValue(sheet, p.x() + 1 + offset, p.y(), QString::number(fightNumber[nodes[i].v]) + " / " + text);
        }
    }

    for (int i = 1; i <= maxRow   ; ++i) ExcelUtils::setRowHeight(sheet, i, 50);
    for (int i = 1; i <= maxColumn; ++i) ExcelUtils::setColumnWidth(sheet, i, 50);
    for (int i = 1; i <= maxColumn; ++i) ExcelUtils::setColumnAutoFit(sheet, i);
    for (int i = 1; i <= maxRow   ; ++i) ExcelUtils::setRowAutoFit(sheet, i);
    for (int i = 1; i <= maxColumn; ++i)
    {
        QAxObject *pColumn = sheet->querySubObject("Columns(QVariant&)", i);
        if (qAbs(50 - pColumn->property("ColumnWidth").toDouble()) < 1e-7 ||
            pColumn->property("ColumnWidth").toDouble() < 8.43)
        {
            pColumn->setProperty("ColumnWidth", 8.43);
        }
        delete pColumn;
    }

    maxColumn = qMax(4, maxColumn);


    long long tournamentUID = DBUtils::getField("TOURNAMENT_FK", "TOURNAMENT_CATEGORIES", tournamentCategory).toLongLong();

    ExcelUtils::setTournamentName(sheet, DBUtils::getTournamentNameAsHeadOfDocument(tournamentUID), 1, 1, 1, maxColumn);

    ExcelUtils::uniteRange(sheet, 2, 1, 2, maxColumn);
    ExcelUtils::setValue(sheet, 2, 1, DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", tournamentCategory));

    ExcelUtils::uniteRange(sheet, 3, 1, 3, maxColumn);
    ExcelUtils::setValue(sheet, 3, 1, prefFileName.left(prefFileName.length() - 5));
    maxRow += 2;


    ExcelUtils::setFooter(sheet, maxRow, 1, 3, 25, dlg.getJudges(), DBUtils::getJudges(tournamentUID));


    ExcelUtils::setPageOrientation(sheet, 2);
    ExcelUtils::setFitToPagesWide(sheet, countPlayers <= 8? 1 : 2);
    ExcelUtils::setCenterHorizontally(sheet, true);


    QTime timer;
    timer.start();
    ExcelUtils::saveAsFile(workbook, directoryPath, prefFileName + ", " + DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", tournamentCategory) + ".xls");
    //qDebug() << "\t\t\t\tsave in" << timer.elapsed();

    delete sheet;
    delete sheets;
}

QString RenderAreaWidget::getNameOfLevel(int vertex)
{
    int level = Utils::log2(vertex) + 1;
    return level == 1? "Финал" : level == 2? "Полуфинал" : "1 / " + QString::number(1 << (level - 1));
}
