#include "utils.h"




QString Utils::getTime(int timeSec)
{
    return
            QString("%1").arg(timeSec / 3600, 2, 10, QChar('0')) +
            ":" +
            QString("%1").arg(timeSec / 60 % 60, 2, 10, QChar('0'));
}

int Utils::getAge(QDate birthdayDate, QDate DATE_WEIGHTING)
{
    int age = DATE_WEIGHTING.year() - birthdayDate.year();
    if ( DATE_WEIGHTING.month() <  birthdayDate.month() ||
        (DATE_WEIGHTING.month() == birthdayDate.month() && DATE_WEIGHTING.day() < birthdayDate.day()))
    {
        --age;
    }
    return age;
}

int Utils::log2(int x)
{
    int ans = 0;
    while (x >>= 1) ++ans;
    return ans;
}
