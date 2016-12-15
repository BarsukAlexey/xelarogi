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

void Utils::setFontSize(const QString& text, QFont& font, const QRect& taget, QRect& boundRect)
{
    int l = 1, r = font.pointSize();
    while(l < r)
    {
        int m = (l + r + 1) / 2;
        font.setPointSize(m);
        QRect boundingRect = QFontMetrics(font).boundingRect(text);
        if (boundingRect.width() <= taget.width() && boundingRect.height() <= taget.height())
            l = m;
        else
            r = m - 1;
    }
    font.setPointSize(l);
    boundRect = QFontMetrics(font).boundingRect(text);

//    qDebug() << taget.height()
//             << boundRect.height()
//             << QFontMetrics(font).ascent() + QFontMetrics(font).descent()
    //             << QFontMetrics(font).height();
}

QColor Utils::getContrastColor(const QColor& color)
{
    return 0.3 * color.red() + 0.59 * color.green() + 0.11 * color.blue()  < 128?
                Qt::white :
                Qt::black;
//    return QColor(color.red()   < 128? 255 : 0,
//                  color.green() < 128? 255 : 0,
//                  color.blue()  < 128? 255 : 0
//                  );
//    return QColor(255 - color.red(),
//                  255 - color.green(),
//                  255 - color.blue()
//                  );
//    return QColor(255 - color.red(),
//                  255 - color.green(),
//                  255 - color.blue(),
//                  color.alpha()
//                  );
}

void Utils::eraseBadChars(QString& str){
    str = str
          .replace('\\', ' ')
          .replace('/', ' ')
          .replace(':', ' ')
          .replace('*', ' ')
          .replace('?', ' ')
          .replace('"', ' ')
          .replace('<', ' ')
          .replace('>', ' ')
          .replace('|', ' ')

          .replace('%', ' ')
          .replace('!', ' ')
          .replace('@', ' ')

          .trimmed();
//    while (str.endsWith('.'))
//    {
//        str = str.remove(str.length() - 1).simplified();
//    }

}


