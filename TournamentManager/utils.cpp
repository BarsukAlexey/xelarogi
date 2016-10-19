#include "utils.h"




QString Utils::getTime(int timeSec)
{
    return
            QString("%1").arg(timeSec / 3600, 2, 10, QChar('0')) +
            ":" +
            QString("%1").arg(timeSec / 60 % 60, 2, 10, QChar('0'));
}
