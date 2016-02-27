#ifndef RENDERAREAWIDGET_H
#define RENDERAREAWIDGET_H

#include <db_utils.h>

#include <QWidget>
#include <QVector>
#include <QRect>
#include <QPainter>
#include <QSet>
#include <QPoint>
#include <QSqlDatabase>
#include "renderarearesultdialog.h"


class RenderAreaWidget : public QWidget
{
    Q_OBJECT

public:


private:
    const QSqlDatabase &database;
    long long tournamentCategories;
    int countRows, countColumns;
    int widthCell, heightCell;
    const DBUtils::NodeOfTournirGrid noNode = DBUtils::NodeOfTournirGrid({-1, "", "", false, -1});
    DBUtils::NodeOfTournirGrid selectedNode = noNode;

public:
    explicit RenderAreaWidget(QWidget *parent, int widthCell, int heightCell, const QSqlDatabase &_database);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

private:
    void paintRect(int i, int j, QPainter& painter, const DBUtils::NodeOfTournirGrid& node);
    void paintLine(QPoint , QPoint , QPainter& painter);
    void setNormalSize();
    //QVector<NodeOfTournirGrid> getNodes();
    int log2(int x);
    QPoint getCell(int v);

signals:

public slots:
    void slotSetTournamentCategories(int tournamentCategories);
    void widthChanged(int);
    void heightChanged(int);
    void onSaveInExcel();
};
#endif // RENDERAREAWIDGET_H
