#ifndef DIALOGSCHEDULE2TREEWIDGET_H
#define DIALOGSCHEDULE2TREEWIDGET_H

#include <QDebug>
#include <QTreeWidget>
#include <QWidget>
#include <QMimeData>
#include <QDrag>

class Dialogschedule2TreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit Dialogschedule2TreeWidget(QWidget *parent = 0);

private:
    int tournamentUID;

protected:
    void startDrag(Qt::DropActions supportedActions) Q_DECL_OVERRIDE;

signals:

public slots:
    void setTournamentUID(const int tournamentUID);
    void updateDataInTable();
};

#endif // DIALOGSCHEDULE2TREEWIDGET_H
