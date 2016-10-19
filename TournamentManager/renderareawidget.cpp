#include "excel_utils.h"
#include "renderareawidget.h"

#include <QPainter>
#include <QPaintEvent>
#include <QVector>
#include <QRect>
#include <QDebug>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QTime>
#include <QtAlgorithms>
#include <QSqlQuery>
#include <QSqlError>
#include <QAxObject>
#include <QAxBase>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QAxObject>
#include <QAxBase>
#include <QDebug>
#include <QAxObject>
#include <QAxWidget>
#include <QFileDialog>


RenderAreaWidget::RenderAreaWidget(QWidget *parent, int widthCell, int heightCell)
    : QWidget(parent)
{
    tournamentCategories = -1;
    countRows = 0;
    countColumns = 0;
    this->widthCell = widthCell;
    this->heightCell = heightCell;
    setNormalSize();
}

int RenderAreaWidget::log2(int x)
{
    int ans = 0;
    while (x >>= 1) ++ans;
    return ans;
}

QPoint RenderAreaWidget::getCell(int v)
{
    QPoint p;
    p.setY(countColumns - log2(v) - 1);
    p.setX( (1 << (p.y() + 1)) * ((1 << (countColumns - p.y())) - 1 - v) + (1 << p.y()) - 1);
    return p;
}

long long RenderAreaWidget::getTournamentUID() const
{
    long long tournamentUID = -1;
    QSqlQuery query;
    if (!query.prepare("SELECT * FROM TOURNAMENT_CATEGORIES WHERE UID = ?"))
        qDebug() << query.lastError().text();
    query.bindValue(0, tournamentCategories);
    if (query.exec() && query.next())
    {
        tournamentUID = query.value("TOURNAMENT_FK").toLongLong();
    }
    else
    {
        qDebug() << query.lastError().text();
    }

    return tournamentUID;
}

QString RenderAreaWidget::getCategoryName() const
{
    QString name = "";
    QSqlQuery query;
    if (!query.prepare("SELECT NAME FROM TOURNAMENT_CATEGORIES WHERE UID = ?"))
        qDebug() << query.lastError().text();
    query.bindValue(0, tournamentCategories);
    if (query.exec() && query.next())
    {
        name = query.value("NAME").toString();
    }
    else
    {
        qDebug() << query.lastError().text();
    }

    return name;
}

void RenderAreaWidget::paintEvent(QPaintEvent* )
{
    //qDebug() << __PRETTY_FUNCTION__ << " " << QDateTime::currentDateTime();
    //return;

    QPainter painter(this);

    painter.fillRect(painter.viewport(), Qt::white);

    QVector<DBUtils::NodeOfTournirGrid> nodes = DBUtils::getNodes(tournamentCategories);
    if (nodes.empty()) return;

    for (const DBUtils::NodeOfTournirGrid& node : nodes)
    {
        for (int child : {2 * node.v, 2 * node.v + 1})
        {
            if (qBinaryFind(nodes, DBUtils::NodeOfTournirGrid(-1, child)) != nodes.end() )
            {
                paintLine(getCell(node.v), getCell(child), painter);
            }
        }
    }

    for (const DBUtils::NodeOfTournirGrid& node : nodes)
    {
        QPoint cell = getCell(node.v);
        paintRect(cell.x(), cell.y(), painter, node);
    }

    //countColumns = qMax(countColumns, log2(nodes.last().v) + 1);
    countColumns = log2(nodes.last().v) + 1;
    countRows = 2 * (1 << (countColumns - 1)) - 1;
    setNormalSize();


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
                QSqlQuery query("UPDATE GRID SET ORDER_FK = ?, result = ? WHERE TOURNAMENT_CATEGORIES_FK = ? AND VERTEX = ?");
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
                RenderAreaResultDialog dlg(node1.name, node1.region, this);
                dlg.exec();

                node0.result = RenderAreaResultDialog::mLastResult;

                QString orderUID;
                {
                    QSqlQuery query("SELECT * FROM GRID WHERE TOURNAMENT_CATEGORIES_FK = ? AND VERTEX = ?");
                    query.bindValue(0, tournamentCategories);
                    query.bindValue(1, node1.v);
                    if (!( query.exec() && query.next()))
                        qDebug() << __PRETTY_FUNCTION__ << " " << query.lastError().text() << "\n" << query.lastQuery();
                    orderUID = query.value("ORDER_FK").toString();
                }
                QSqlQuery query("UPDATE GRID SET ORDER_FK = ?, RESULT = ? WHERE TOURNAMENT_CATEGORIES_FK = ? AND VERTEX = ?");
                query.bindValue(0, orderUID);
                query.bindValue(1, node0.result);
                query.bindValue(2, tournamentCategories);
                query.bindValue(3, node0.v);
                if (!query.exec())
                    qDebug() << __PRETTY_FUNCTION__ << " " << query.lastError().text() << "\n" << query.lastQuery();
            }
        }
    }
    repaint();
    emit iChangeToutGrid();
}

void RenderAreaWidget::getAppropriateFontSize(QPainter& painter, const QRect& rect, const QString& text, int flags)
{
    QFont font = painter.font();
    int l = 1, r = 228;
    const qreal coef = 0.9;
    while (l < r)
    {
        qreal m = (l + r + 1) / 2;
        font.setPointSizeF(m);
        QRect boundingRect = QFontMetrics(font).boundingRect(text);
        if (boundingRect.width() <= coef * rect.width() && boundingRect.height() <= coef * rect.height())
            l = m;
        else
            r = m - 1;
    }
    font.setPointSizeF(l);
    painter.setFont(font);
    painter.drawText(rect, flags, text);
}



void RenderAreaWidget::paintRect(int i, int j, QPainter& painter, const DBUtils::NodeOfTournirGrid& node)
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

    QString text(node.name == "_________"? "" : node.name);
    if (node.isFight)
    {
        if (0 < node.UID && !node.result.isEmpty())
            text += " (" + node.result + ")";
    }
    else
        text += " (" + node.region + ")";
    painter.setPen(Qt::black);
    getAppropriateFontSize(painter, rect, text, Qt::AlignHCenter | Qt::AlignVCenter);
}

void RenderAreaWidget::paintLine(QPoint aa, QPoint bb, QPainter& painter)
{
    QPoint a(qMin(aa.x(), bb.x()), qMin(aa.y(), bb.y()));
    QPoint b(qMax(aa.x(), bb.x()), qMax(aa.y(), bb.y()));
    painter.drawLine(QPoint(widthCell * (a.y() + 1), heightCell * (a.x())),
                     QPoint(widthCell *  b.y()     , heightCell * (b.x() + 1)));

}


void RenderAreaWidget::setNormalSize()
{
    resize(countColumns * widthCell + 1, countRows * heightCell + 1);
}




void RenderAreaWidget::slotSetTournamentCategories(int tournamentCategories)
{
    this->tournamentCategories = tournamentCategories;
    selectedNode = noNode;
    repaint();
}

void RenderAreaWidget::widthChanged(int width)
{
    widthCell = width;
    setNormalSize();
    repaint();
}

void RenderAreaWidget::heightChanged(int height)
{
    heightCell = height;
    setNormalSize();
    repaint();
}



void RenderAreaWidget::onSaveInExcel()
{
    qDebug() << "RenderAreaWidget::onSaveInExcel: " << DialogChoseData::Type::grids;
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
    p.setY(countColumns - log2(v) - 1);
    p.setX( (1 << (p.y() + 1)) * ((1 << (countColumns - p.y())) - 1 - v) + (1 << p.y()) - 1);
    return p;
}

void RenderAreaWidget::printTableGridInExcel(QAxObject* workbook, DialogChoseData& dlg, int tournamentCategory,
        bool likePointFighing, QString directoryPath, QVector<int> fightNumber, QString text, QString prefFileName)
{
    QAxObject *sheets   = workbook->querySubObject("WorkSheets");
    QAxObject *sheet    = sheets->querySubObject( "Item( int )", 1);

    QVector<DBUtils::NodeOfTournirGrid> nodes = DBUtils::getNodes(tournamentCategory);
    if (nodes.empty()) return;
    qSort(nodes);

    const int countColumns = log2(nodes.last().v) + 1;
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
            ExcelUtils::setValue(sheet, p.x() + 1 + offset, p.y() + 1, node.name + "\n" + node.result);
        else
        {
            QString message;
            for (int i = 0; i < data.size(); ++i)
            {
                message += DBUtils::get(data[i].second, node.UID) + (i + 1 == data.size()? "" : " ");
            }
            //ExcelUtils::setValue(sheet, p.x() + 1 + offset, p.y() + 1, node.name + "\n" + node.region);
            ExcelUtils::setValue(sheet, p.x() + 1 + offset, p.y() + 1, node.name + "\n" + message);
        }

        ExcelUtils::setBorder(sheet, p.x() + 1 + offset, p.y() + 1, p.x() + 1 + offset, p.y() + 1, 3);

        for (int child : {2 * node.v, 2 * node.v + 1})
        {
            if (qBinaryFind(nodes, DBUtils::NodeOfTournirGrid(-1, child)) != nodes.end() )
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



    long long tournamentUID = DBUtils::getField("TOURNAMENT_FK", "TOURNAMENT_CATEGORIES", tournamentCategory).toLongLong();

    maxColumn = qMax(4, maxColumn);

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


    ExcelUtils::saveAsFile(workbook, directoryPath, prefFileName + ", " + DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", tournamentCategory) + ".xls");

    delete sheet;
    delete sheets;
}

QString RenderAreaWidget::getNameOfLevel(int vertex)
{
    int level = RenderAreaWidget::log2(vertex) + 1;
    return level == 1? "Финал" : level == 2? "Полуфинал" : "1 / " + QString::number(1 << (level - 1));
}
