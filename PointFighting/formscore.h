#ifndef FORMSCORE_H
#define FORMSCORE_H

#include <QWidget>
#include "ui_form.h"

class FormScore : public QWidget
{
    Q_OBJECT

public:
    QColor backgroundColor;
    bool isWinner;
    Ui_Form * ui;
    const QImage flag;

    explicit FormScore(QString name, QString region, QImage flag, QColor backgroundColor, QWidget *parent = 0);
    ~FormScore();

    void setWinner(bool isWinner);

    static QPixmap drawBorder(QImage flag);
    static QImage makeGrey(QImage flag);
    static QPixmap drawCubes(int count);

public:
    void setCountMinus(int countCubes);
    void setCountFo(int countCubes);
    void setCountEx(int countCubes);
};

#endif // FORMSCORE_H
