#ifndef SUPERSTRUCT_H
#define SUPERSTRUCT_H

#include "db_utils.h"
using namespace std;

class Region
{
public:
    Region(const int regionUID = -1);
    bool operator < (const Region& rh);
    void add(int orderUID);
    int getRegionUID() const;
    void updataRndAndLocation();
    QVector<int> getAllOrderUIDs() const;
    int pollOrderUid();

private:
    int regionUID;
    QVector<int> orderUIDs;
    int rnd;
};
//------------------------------------------------------------------
class Country
{
public:
    Country(int countryUID = -1);
    bool operator < (const Country& rh);
    void add(int regionUID, int orderUID);
    int getCountryUID() const;
    void updataRndAndLocation();
    QVector<int> getAllOrderUIDs() const;
    int pollOrderUid();

private:
    int countryUID;
    QVector<Region> regions;
    int rnd;
};
//------------------------------------------------------------------
class SuperStruct
{
public:
    SuperStruct(int separator);
    void add(const int orderUID);
    void updataRndAndLocation();
    int pollOrderUid(const int orderUID);
    void pollTwoOrders(int& orderUID0, int& orderUID1);
    int pollLastOrder();
    QVector<int> getAllOrderUIDs() const;
private:

    static int getLoc(int type, int orderUID);
    void getLocation(int& countryUID, int& regionUID, int orderUID);

    int separator;
    QVector<Country> countries;
};

#endif // SUPERSTRUCT_H
