#ifndef FORMDIPL_H
#define FORMDIPL_H

#include "db_utils.h"
#include "dialogselectfieldsfordimloma.h"

#include <QComboBox>
#include <QDate>
#include <QDebug>
#include <QDir>
#include <QFont>
#include <QFontDialog>
#include <QLabel>
#include <QHeaderView>
#include <QPainter>
#include <QPixmap>
#include <QSpinBox>
#include <QSqlQuery>
#include <QWidget>




namespace Ui {
class FormDipl;
}

class FormDipl : public QWidget
{
    Q_OBJECT

public:


private:
    QVector <QVector<QString> > fields;
    QVector <QFont> fonts;

public:
    explicit FormDipl(long long UID_tournament, QWidget *parent = 0);
    ~FormDipl();

    QString convertToRoman (int val);

private slots:
    void onTableClicked(const QModelIndex & index);
    void addRow();
    void deleteRow();
    void onPushPrint();

private:
    Ui::FormDipl *ui;
    const long long UID_tournament;

};

#endif // FORMDIPL_H
