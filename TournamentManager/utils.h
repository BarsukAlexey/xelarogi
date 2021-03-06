#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QDate>
#include <QFont>
#include <QFontMetrics>
#include <QDebug>
#include <QColor>

class Utils
{
public:
    static QString getTime(int timeSec);
    static int getAge(QDate birthdayDate, QDate DATE_WEIGHTING);
    static int log2(int x);
    static void setFontSize(const QString& text, QFont& font, const QRect& taget, QRect& boundRect);
    static QColor getContrastColor(const QColor& color);
    static void eraseBadChars(QString& str);
};

#endif // UTILS_H
