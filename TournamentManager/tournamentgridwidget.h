#ifndef TOURNAMENTGRIDWIDGET_H
#define TOURNAMENTGRIDWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QAxObject>
#include <QAxBase>
#include <QDebug>

#include "tournamentmanager.h"

namespace Ui {
class TournamentGridWidget;
}

class TournamentGridWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TournamentGridWidget(QWidget *parent = 0);
    ~TournamentGridWidget();

public slots:
    void update();

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);

private slots:
    void onPushButtonClicked();

private:
    Ui::TournamentGridWidget *ui;

private:
    QVector<QVector<TournamentManager::Point>> mLevels;
    QVector<TournamentManager::Border> mBorders;

    int mClickCount = 0;
    int mRecW = 80;
    int mRecH = 20;
};

#endif // TOURNAMENTGRIDWIDGET_H
