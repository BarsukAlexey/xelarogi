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
#include <QInputDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QHeaderView>
#include <QPainter>
#include <QPixmap>
#include <QPrinter>
#include <QProgressDialog>
#include <QSpinBox>
#include <QSqlQuery>
#include <QWidget>



namespace Ui {
class FormDipl;
}

class FormDipl : public QDialog
{
    Q_OBJECT

private:
    Ui::FormDipl *ui;
    const long long UID_tournament;

private:
    QVector <QVector<std::pair<DBUtils::TypeField, QString> > > fields;
    QVector <QFont> fonts;
    QVector <QColor> colors;
    const QString dirPath = "template\\diplom";

public:
    explicit FormDipl(long long UID_tournament, QWidget *parent = 0);
    ~FormDipl();

private:
    void onSaveData();
    void loadData();

private slots:
    void onTableClicked(const QModelIndex & index);
    void addRow();
    void deleteRow();
    void onPushPrint();

    void onNewTemplate();
};

#endif // FORMDIPL_H
