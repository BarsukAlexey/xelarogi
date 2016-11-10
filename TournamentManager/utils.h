#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QDate>

class Utils
{
public:
    static QString getTime(int timeSec);
    static int getAge(QDate birthdayDate, QDate DATE_WEIGHTING);
    static int log2(int x);
};

#endif // UTILS_H
