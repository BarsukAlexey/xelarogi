#ifndef RENDERAREAWIDGET_H
#define RENDERAREAWIDGET_H

#include <QWidget>

#include <QWidget>
#include <QVector>
#include <QRect>
#include <QPainter>
#include <QSet>
#include <QPoint>
#include <QSqlDatabase>

class RenderAreaWidget : public QWidget
{
    Q_OBJECT

public:
    struct NodeOfTournirGrid
    {
        int v; // id вершины; вершины нумируются как в дереве отрезков (только зеркально)
        QString name;
        QString region;
        int isFighing;

        bool operator < (const NodeOfTournirGrid& other) const
        {
            return v < other.v;
        }
    };

private:
    const QSqlDatabase &database;
    long long tournamentCategories;
    int countRows, countColumns;
    int widthCell, heightCell;
    const NodeOfTournirGrid noNode = NodeOfTournirGrid({-1, "", "", false});
    NodeOfTournirGrid selectedNode = noNode;

public:
    explicit RenderAreaWidget(QWidget *parent, int widthCell, int heightCell, const QSqlDatabase &_database);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

private:
    void paintRect(int i, int j, QPainter& painter, const NodeOfTournirGrid& node);
    void paintLine(QPoint , QPoint , QPainter& painter);
    void setNormalSize();
    QVector<NodeOfTournirGrid> getNodes();
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
