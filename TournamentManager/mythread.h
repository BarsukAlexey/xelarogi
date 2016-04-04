#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <vector>
#include <QDebug>

class MyThread : public QThread
{
    Q_OBJECT

private:
    const std::vector<int> time;
    const int countRings;
    std::vector<int> count;
    bool mStop;

public:
    // пытаемся самое нагруженное татами разгрузить,
    // пытаемся самое РАЗгруженное татами ЗАгрузить,
    int maxSumSeg;
    int minSumSeg;
    std::vector<int> ans;


public:
    MyThread( const std::vector<int> time, const int countRings, const int maxSumSeg, const int minSumSeg) :
        time(time), countRings(countRings), maxSumSeg(maxSumSeg), minSumSeg(minSumSeg)
    {
        mStop = false;
    }

    inline void setStop( void )
    {
        mStop = true;
    }

private:

    void f(int pos, int sumLastSegment, int curMaxSumSeg, int curMinSumSeg)
    {
        if (mStop) return;

        if (!(maxSumSeg > curMaxSumSeg || (maxSumSeg == curMaxSumSeg && minSumSeg < curMinSumSeg)))
            return;

        if (pos == (int)time.size())
        {
            curMinSumSeg = qMin(sumLastSegment, curMinSumSeg);
            if (maxSumSeg > curMaxSumSeg || (maxSumSeg == curMaxSumSeg && minSumSeg < curMinSumSeg))
            {
                maxSumSeg = curMaxSumSeg;
                minSumSeg = curMinSumSeg;
                ans = count;
                //qDebug() << "delta: " << count.size() << maxSumSeg << minSumSeg;
            }
        }
        else
        {
            if (count.size())
            {
                ++count[count.size() - 1];
                sumLastSegment += time[pos];
                f(pos + 1, sumLastSegment, qMax(curMaxSumSeg, sumLastSegment), curMinSumSeg);
                sumLastSegment -= time[pos];
                --count[count.size() - 1];
            }

            if ((int)count.size() < countRings)
            {
                count.push_back(1);
                f(pos + 1, time[pos], qMax(curMaxSumSeg, sumLastSegment), sumLastSegment? qMin(curMinSumSeg, sumLastSegment) : (int)1e9);
                count.pop_back();
            }

        }
    }



protected:
    void run()
    {
        f(0, 0, 0, (int)1e9);
        QString message;
        int pos = 0;
        for (int cnt : ans) {
            int curTime = 0;
            while(cnt-->0) curTime += time[pos++];
            message += QString::number(curTime/3600) + ":" + QString("%1").arg(curTime/60%60, 2, 10, QChar('0')) + ", ";
        }
        qDebug() << "Поток: " << message;
    }
};

#endif // MYTHREAD_H

