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
    QString reportMessage;


public:
    MyThread( const std::vector<int> time, const int countRings) : time(time), countRings(countRings)
    {
        mStop = false;
        maxSumSeg = (int)1e9;
        minSumSeg = 0;
    }

    void setStop()
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
            //curMaxSumSeg = qMax(curMaxSumSeg, sumLastSegment); // Нет нужды
            curMinSumSeg = qMin(curMinSumSeg, sumLastSegment);
            if (maxSumSeg > curMaxSumSeg || (maxSumSeg == curMaxSumSeg && minSumSeg < curMinSumSeg))
            {
                maxSumSeg = curMaxSumSeg;
                minSumSeg = curMinSumSeg;
                ans = count;
            }
        }
        else
        {
            if (count.size())
            {
                ++count.back();
                sumLastSegment += time[pos];
                f(pos + 1, sumLastSegment, qMax(curMaxSumSeg, sumLastSegment), curMinSumSeg);
                sumLastSegment -= time[pos];
                --count.back();
            }

            if ((int)count.size() < countRings)
            {
                count.push_back(1);
                int nextMaxSumSeg = qMax(curMaxSumSeg, qMax(sumLastSegment, time[pos]));
                f(pos + 1, time[pos], nextMaxSumSeg,
                  sumLastSegment == 0? curMinSumSeg : qMin(curMinSumSeg, sumLastSegment));
                count.pop_back();
            }

        }
    }



protected:
    void run()
    {
        f(0, 0, 0, (int)1e9);
        reportMessage = "Расчётное время";
        QString message2;
        int pos = 0;
        for (const int cnt : ans) {
            int curTime = 0;
            for (int i = 0; i < cnt; ++i)
                curTime += time[pos++];
            reportMessage += "\n" +
                             QString::number(curTime / 3600) + " ч. " +
                             QString("%1").arg(curTime / 60%60, 2, 10, QChar('0')) + " м.";
            message2 +=  QString::number(cnt) + ", ";
        }
        //qDebug() << "time.size()" << time.size() << "min,max:" << minSumSeg << maxSumSeg << "Delta: " << (maxSumSeg - minSumSeg) / 60 << "In my thread: " << reportMessage << " count in rings:" << message2;
    }
};

#endif // MYTHREAD_H

