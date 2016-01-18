#include "tournamentmanager.h"


QVector<TournamentManager::InitialParticapantRecord> TournamentManager::getTournamentInitialState(QVector<TournamentManager::TournamentManager::InitialParticapantRecord> particapants)
{
    qSort(particapants.begin(), particapants.end());
    int count = particapants.size();

    QVector<QVector<InitialParticapantRecord>> T;
    InitialParticapantRecord temp = {"", -1, -1};
    for (const InitialParticapantRecord& particapant : particapants)
    {
        bool needNewLevel = false;
        if (particapant.priorityOrder != 0 && T.size() == 0)
        {
            needNewLevel = true;
        }
        else if (particapant.regionFK != temp.regionFK && particapant.priorityOrder == 0)
        {
            needNewLevel = true;
        }

        if (needNewLevel)
        {
            T.push_back(QVector<InitialParticapantRecord>());
            temp = particapant;
        }

        T.back().push_back(particapant);
    }

    for (QVector<InitialParticapantRecord>& ps : T)
    {
        std::random_shuffle(ps.begin(), ps.end());
    };
    std::random_shuffle(T.begin() + 1, T.end());


    particapants.clear();
    particapants.resize(count);
    for (const QVector<InitialParticapantRecord>& ps : T)
    {

        int s = std::max(1, (count - 1) / ps.size());
        int waitCount = s;
        int l = 0;
        for (int i = 0; l < ps.size(); i = (i + 1) % particapants.size())
        {
            if (particapants[i].regionFK != ps[l].regionFK ||
                 particapants[i].priorityOrder != 0 ||
                 particapants[i].text.isEmpty()
               )
            {
                --waitCount;
            }
            else
            {
                //waitCount = s;
                continue;
            }

            if (waitCount <= 0 &&
                particapants[i].text.isEmpty()
               )
            {
                particapants[i] = ps[l];
                ++l;
                waitCount = s;
                continue;
            }
            waitCount = std::max(0, waitCount - 1);
        }
    }

    return instance().mRecords = particapants;
}

QVector<TournamentManager::Border> TournamentManager::getTournamentBorders(QVector<QVector<TournamentManager::Point> > levels)
{
    QVector<Border> borders;
    for (const auto& level : levels)
    {
        for (const Point& p : level)
        {
            borders.push_back({p.x, p.y, true, true, true, true});
        }
    }

    for (int i = 0; i < (int)levels.size() - 1; i++)
    {
        for (int j = 0; j < (int)levels[i].size(); j += 2)
        {
            Point parent = levels[i + 1][levels[i][j].parentIndex];
            for (int y = levels[i][j].y + 1; y < parent.y; y++)
                borders.push_back({levels[i][j].x, y, false, false, true, false});
            for (int y = levels[i][j + 1].y - 1; y > parent.y; y--)
                borders.push_back({levels[i][j].x, y, false, false, true, false});
        }
    }

    return borders;
}

QVector<TournamentManager::InitialParticapantRecord> TournamentManager::getSavedRecords()
{
    return instance().mRecords;
}

QVector<QVector<TournamentManager::Point>> TournamentManager::getTournamentRectangles(QVector<TournamentManager::InitialParticapantRecord> particapants)
{
    int count = particapants.size();

    int lowDeg = 0;
    for (int i = 1; ; ++i)
    {
        int p = 1 << i;
        if (p <= count) lowDeg = p;
        else            break;
    }

    bool wasSpecificLevel = ( count != lowDeg );
    int addLayerCount = 2 * (count - lowDeg);
    if (wasSpecificLevel) lowDeg *= 2;
    else addLayerCount = 0;

    int wasLayerCount = addLayerCount;
    int vIndex = 0;
    QVector<QVector<Point>> levels;
    for (int i = 1; lowDeg > 0; i++)
    {
        levels.push_back(QVector<Point>());
        if (addLayerCount > 0) {
            int k = 0;
            while (addLayerCount) {
                Point p;
                p.x = i;
                p.y = ((1 << (i - 1)) + k * (1 << i));
                p.text = particapants[vIndex++].text;
                p.parentIndex = levels.back().size() / 2;
                p.isClicked = false;
                levels.back().push_back(p);
                k++;
                addLayerCount--;
            }
        }
        else {
            for (int j = 1; j <= lowDeg; j++) {
                Point p;
                p.x = i;
                p.y = ((1 << (i - 1)) + (j - 1) * (1 << i));
                if (vIndex < particapants.size())
                {
                    p.text = particapants[vIndex++].text;
                }
                p.parentIndex = levels.back().size() / 2;
                p.isClicked = false;
                levels.back().push_back(p);
            }
        }
        lowDeg /= 2;
    }

    if (wasSpecificLevel && levels.size() > 1)
    {
        for (int i = 0; i < levels[0].size()/2 && i < levels[1].size(); i++)
        {
            if ((i + 1) * 2 <= levels[0].size())
            {
                int j1 = 2*i;
                int j2 = 2*i + 1;
                int dy = abs(levels[1][i].y - levels[0][j1].y);

                int ri = levels[1].size() - 1 - i;
                levels[0][j1].y = levels[1][ri].y + dy;
                levels[0][j2].y = levels[1][ri].y - dy;

                levels[0][j1].parentIndex = ri;
                levels[0][j2].parentIndex = ri;

                int rj1 = 2*ri;
                int rj2 = 2*ri + 1;
                if (rj1 < levels[0].size())
                {
                    levels[0][rj1].parentIndex = i;
                }
                if (rj2 < levels[0].size())
                {
                    levels[0][rj2].parentIndex = i;
                }
            }
        }
    }

    return levels;
}

TournamentManager &TournamentManager::instance()
{
    static TournamentManager obj;
    return obj;
}
