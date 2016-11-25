#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QDate>
#include <QFont>
#include <QFontMetrics>
#include <QDebug>

class Utils
{
public:
    static QString getTime(int timeSec);
    static int getAge(QDate birthdayDate, QDate DATE_WEIGHTING);
    static int log2(int x);
    static int getFontSize(const QString& text, QFont font, const QRect& rect);
};

#endif // UTILS_H
