#include "superstruct.h"


Region::Region(const int regionUID) :
    regionUID(regionUID)
{

}

bool Region::operator <(const Region& rh)
{
    if (orderUIDs.size() != rh.orderUIDs.size())
        return orderUIDs.size() < rh.orderUIDs.size();
    if (rnd != rh.rnd)
        return rnd < rh.rnd;
    return regionUID < rh.regionUID;
}

void Region::add(int orderUID)
{
    orderUIDs.push_back(orderUID);
}

int Region::getRegionUID() const
{
    return regionUID;
}

void Region::updataRndAndLocation()
{
    rnd = rand();
    //qDebug() << "Region::updataRndAndLocation";
    std::random_shuffle(orderUIDs.begin(), orderUIDs.end());
}

QVector<int> Region::getAllOrderUIDs() const
{
    return orderUIDs;
}

int Region::pollOrderUid()
{
    return orderUIDs.takeLast();
}
//------------------------------------------------------------------
Country::Country(int countryUID) :
    countryUID(countryUID)
{

}

bool Country::operator <(const Country& rh)
{
    int maxSizeA = 0;
    int maxSizeB = 0;
    for (const Region& region :    regions)
    {
        //maxSizeA = max(maxSizeA, region.getCountOfOrders());
        maxSizeA += region.getAllOrderUIDs().size();
    }
    for (const Region& region : rh.regions)
    {
        //maxSizeB = max(maxSizeB, region.getCountOfOrders());
        maxSizeB += region.getAllOrderUIDs().size();
    }

    if (maxSizeA != maxSizeB)
        return maxSizeA < maxSizeB;
    if (rnd != rh.rnd)
        return rnd < rh.rnd;
    return countryUID < rh.countryUID;
}

void Country::add(int regionUID, int orderUID)
{
    for (int i = 0; i < (int)regions.size(); ++i)
    {
        if (regions[i].getRegionUID() == regionUID)
        {
            regions[i].add(orderUID);
            return;
        }
    }
    regions.push_back(Region(regionUID));
    regions.back().add(orderUID);
}

int Country::getCountryUID() const
{
    return countryUID;
}

void Country::updataRndAndLocation()
{
    for (int i = (int)regions.size() - 1; 0 <= i; --i)
    {
        if (regions[i].getAllOrderUIDs().isEmpty())
        {
            regions.remove(i);
        }
    }

    rnd = rand();
    for (int i = 0; i < (int)regions.size(); ++i)
    {
        regions[i].updataRndAndLocation();
    }
    sort(regions.begin(), regions.end());
}

QVector<int> Country::getAllOrderUIDs() const
{
    QVector<int> orderUIDs;
    for (const Region& region: regions)
    {
        orderUIDs << region.getAllOrderUIDs();
    }
    return orderUIDs;
}

int Country::pollOrderUid()
{
    return regions.last().pollOrderUid();
}
//------------------------------------------------------------------
SuperStruct::SuperStruct(int separator) :
    separator(separator)
{
}

void SuperStruct::add(const int orderUID)
{
    int countryUID;
    int regionUID;
    getLocation(countryUID, regionUID, orderUID);
    for (int i = 0; i < (int)countries.size(); ++i)
    {
        if (countries[i].getCountryUID() == countryUID)
        {
            countries[i].add(regionUID, orderUID);
            return;
        }
    }
    countries.push_back(Country(countryUID));
    countries.back().add(regionUID, orderUID);
}

void SuperStruct::updataRndAndLocation()
{
    for (int i = (int)countries.size() - 1; 0 <= i; --i)
    {
        if (countries[i].getAllOrderUIDs().isEmpty())
        {
            countries.remove(i);
        }
    }

    if (countries.size() == 1 && separator < 2)
    {
        ++separator;
        QVector<int> orderUIDs = getAllOrderUIDs();
        countries.clear();
        for (int orderUID : orderUIDs)
            add(orderUID);
    }

    for (int i = 0; i < (int)countries.size(); ++i)
    {
        countries[i].updataRndAndLocation();
    }
    sort(countries.begin(), countries.end());
}

int SuperStruct::pollOrderUid(const int orderUID)
{
    int countryUID;
    int regionUID;
    getLocation(countryUID, regionUID, orderUID);
    updataRndAndLocation();
    for (int i = (int)countries.size() - 1; 0 <= i; --i)
    {
        if (countries.size() == 1 || countries[i].getCountryUID() != countryUID)
        {
            return countries[i].pollOrderUid();
        }
    }
    qDebug() << "Super::getOrderUid fucked up";
    return -1;
}

void SuperStruct::pollTwoOrders(int& orderUID0, int& orderUID1)
{
    updataRndAndLocation();
    if (countries.size() == 1)
    {
        orderUID0 = countries[0].pollOrderUid();
        updataRndAndLocation();
        orderUID1 = countries[0].pollOrderUid();
    }
    else
    {
        orderUID0 = countries[countries.size() - 1].pollOrderUid();
        orderUID1 = countries[countries.size() - 2].pollOrderUid();
    }
}

int SuperStruct::pollLastOrder()
{
   updataRndAndLocation();
   return countries.last().pollOrderUid();
}

QVector<int> SuperStruct::getAllOrderUIDs() const
{
    QVector<int> orderUIDs;
    for (const Country& country: countries)
    {
        orderUIDs << country.getAllOrderUIDs();
    }
    return orderUIDs;
}

int SuperStruct::getLoc(int type, int orderUID)
{
    if (type == 0) return DBUtils::get("COUNTRY_FK"    , "ORDERS", orderUID).toInt();
    if (type == 1) return DBUtils::get("REGION_FK"     , "ORDERS", orderUID).toInt();
    if (type == 2) return DBUtils::get("REGION_UNIT_FK", "ORDERS", orderUID).toInt();
    if (type == 3) return DBUtils::get("CLUB_FK"       , "ORDERS", orderUID).toInt();
    qDebug() << "getLoc::FUCK";
    return -1;
}

void SuperStruct::getLocation(int& countryUID, int& regionUID, int orderUID)
{
    countryUID = getLoc(separator    , orderUID);
    if (separator == 3)
        regionUID = -1;
    else
        regionUID  = getLoc(separator + 1, orderUID);
}
