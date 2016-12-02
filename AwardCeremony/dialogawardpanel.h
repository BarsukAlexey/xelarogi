#ifndef DIALOGAWARDPANEL_H
#define DIALOGAWARDPANEL_H

#include "utils.h"

#include <QDialog>
#include <QPainter>
#include <QCloseEvent>

namespace Ui {
class DialogAwardPanel;
}

class DialogAwardWidget : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAwardWidget(QWidget *parent = 0);
    ~DialogAwardWidget();

    void setData(QByteArray& byteArray);

    void setTournamentCategory(const QString& value);

    void setPlayer(const int player, const QString& name, const QString& location, const QByteArray& imageFlag);

    void resetAll();

protected:
    virtual void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event)
    {
       event->ignore();
    }

private:
    Ui::DialogAwardPanel *ui;

    QPixmap image;
    QVector<QRect> rects;
    QFont font;
    QColor colorText;
    QColor colorTextBound;
    QColor colorFlagBound;
    int withTextBound;

    QString tournamentCategory;
    QVector<QString> names;
    QVector<QString> countries;
    QVector<QPixmap> flags;
};

#endif // DIALOGAWARDPANEL_H
