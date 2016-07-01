#ifndef FORMDIPL_H
#define FORMDIPL_H

#include "db_utils.h"
#include "dialogselectfieldsfordimloma.h"

#include <QColorDialog>
#include <QComboBox>
#include <QDialog>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QFont>
#include <QFontDialog>
#include <QLabel>
#include <QHeaderView>
#include <QPainter>
#include <QPixmap>
#include <QPrinter>
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
    QVector <QVector<std::pair<DBUtils::TypeField, QString> > > fields;
    QVector <QFont> fonts;
    QVector <QColor> colors;

public:
    explicit FormDipl(long long UID_tournament, QWidget *parent = 0);
    ~FormDipl();


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
