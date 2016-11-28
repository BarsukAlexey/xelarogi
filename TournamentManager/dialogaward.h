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


#include <QFile>


#include "utils.h"
#include "dialogawardselecttournamentcategories.h"

class DialogAwardWidget : public QWidget
{
    Q_OBJECT
public:
    DialogAwardWidget(QWidget *parent);

    void setData(QByteArray& byteArray);

    void setImage(QString path);
    QSize getImageSize();

    QByteArray getDate();
    QRect getRects(int index);

    QColor getColorText();
    void setColorText(const QColor& color);

    QFont getFont();
    void setFont(const QFont& font);

    QColor getColorBound();
    void setColorBound(const QColor& color);

    QColor getColorTextBound();
    void setColorTextBound(const QColor& color);


    int getWithTextBound() const;
    void setWithTextBound(int value);

public slots:
    void onRectTextChanged(int row, const QRect& rect);

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
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

};


namespace Ui {
class DialogAward;
}

class DialogAward : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAward(const int tournamentUID, QWidget *parent = 0);
    ~DialogAward();

private slots:
    void on_comboBoxName_currentIndexChanged(int index);
    void on_pushButtonNew_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonSave_clicked();


    void onInput();
    void onRadio();

    void on_pushButtonLoadImg_clicked();
    void on_pushButtonColorText_clicked();
    void on_pushButtonFont_clicked();
    void on_pushButtonColorBound_clicked();

    void on_pushButtonColorBoundText_clicked();
public slots:
    void on_pushButtonGo_clicked();

private:
    int getTypeName();
    int getTypeFlag();
    int getTypeHymn();

private:
    Ui::DialogAward *ui;
    QSqlTableModel* model;
    QVector<QRadioButton* > radio;
    const int tournamentUID;
};

#endif // DIALOGAWARD_H
