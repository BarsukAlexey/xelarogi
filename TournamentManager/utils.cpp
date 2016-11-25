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

int Utils::getFontSize(const QString& text, QFont font, const QRect& rect)
{
    int l = 1, r = 1;
    while (1)
    {
        font.setPointSize(r);
        QRect rectText = QFontMetrics(font).boundingRect(rect, Qt::AlignCenter, text);
        if (rect.width() <= rectText.width() || rect.height() <= rectText.height())
            break;
        l = r;
        r *= 2;
    }

    while (l != r)
    {
        int m = (l + r + 1) / 2;
        font.setPointSize(m);
        QRect rectText = QFontMetrics(font).boundingRect(rect, Qt::AlignCenter, text);
        if (rectText.width() < rect.width() && rectText.height() < rect.height())
            l = m;
        else
            r = m - 1;
    }
    return l;
}


