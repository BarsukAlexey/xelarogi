#ifndef DIALOGAWARD_H
#define DIALOGAWARD_H

#include <QDialog>
#include <QInputDialog>
#include <QSqlTableModel>
#include <QDir>
#include <QDebug>
#include <QSqlRecord>
#include <QFileDialog>
#include <QPainter>
#include <QPaintEvent>
#include <QRadioButton>
#include <QColorDialog>
#include <QFontComboBox>
#include <QFontDialog>

#include "utils.h"

class DialogAwardWidget : public QWidget
{
    Q_OBJECT
public:
    DialogAwardWidget(QWidget *parent);
    void setImage(QString path);

    void setData(QByteArray& byteArray);

    QByteArray getDate();
    QRect getRects(int index);

    QColor getColorText();
    void setColorText(const QColor& color);

    QFont getFont();
    void setFont(const QFont& font);

    QColor getColorBound();
    void setColorBound(const QColor& color);

public slots:
    void onRectTextChanged(int row, const QRect& rect);

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    QPixmap image;
    QVector<QRect> rects;
    QFont font;
    QColor colorText;
    QColor colorBound;

};


namespace Ui {
class DialogAward;
}

class DialogAward : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAward(QWidget *parent = 0);
    ~DialogAward();

private slots:
    void on_comboBoxName_currentIndexChanged(int index);
    void on_pushButtonNew_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonLoadImg_clicked();

    void onInput();
    void onRadio();

    void on_pushButtonColorText_clicked();

    void on_pushButtonFont_clicked();

    void on_pushButtonColorBound_clicked();

private:
    Ui::DialogAward *ui;
    QSqlTableModel* model;
    QVector<QRadioButton* > radio;
};

#endif // DIALOGAWARD_H
