#ifndef DBUTILS_H
#define DBUTILS_H

#include <algorithm>
#include <QDate>
#include <QDebug>
#include <QMap>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QStringList>
#include <QVector>


class DBUtils
{

public:

    class NodeOfTournirGrid
    {
    public:
        long long tournamentCategory;
        int v; // id вершины; вершины нумируются как в дереве отрезков (только зеркально)
        bool isFight;
        long long UID;
        QString result;
        int DAY_FIGHT;
        int TIME_FIGHT;

        explicit NodeOfTournirGrid(long long tournamentCategory = -1,
                                   int v = -1,
                                   bool isFighing = false,
                                   long long UID = -1,
                                   QString result = "",
                                   int DAY_FIGHT = -1,
                                   int TIME_FIGHT = -1) :
            tournamentCategory(tournamentCategory),
            v(v),
            isFight(isFighing),
            UID(UID),
            result(result),
            DAY_FIGHT(DAY_FIGHT),
            TIME_FIGHT(TIME_FIGHT)
        {

        }

        bool operator < (const NodeOfTournirGrid& other) const
        {
            return v < other.v;
        }
    };

    static QString getField(const QString& field, const QString& table, const QString& UID, QString PRETTY_FUNCTION = __PRETTY_FUNCTION__);
    static QString getField(const QString& field, const QString& table, const long long UID, QString PRETTY_FUNCTION = __PRETTY_FUNCTION__);
    static QString getFieldDate(const QString& field, const QString& table, const long long UID, QString PRETTY_FUNCTION = __PRETTY_FUNCTION__);
    static QDate getFieldDateAsDate(const QString& field, const QString& table, const long long UID);


    // для таблицы ORDERS
    static QString getSecondNameAndFirstName(long long UID);
    static QString getSecondNameAndOneLetterOfName(long long UID);
    static QSet<long long> getSetOfOrdersInTournamentCategory(long long uidTournamentCategory); // TODO DELETE ?



    // для таблицы TOURNAMENTS
    static QString getTournamentNameAsHeadOfDocument(long long tournamentUID);
    static QStringList get_DAYS_FROM_TOURNAMENTS(long long);
    static QVector<QString> getJudges(long long tournamentUID);
    static QVector<std::tuple<int, int, int, int>> get_MAX_UID_TC___TYPE_FK___AGE_FROM___AGE_TILL(const int tournamentUID);
    static QSqlQuery *get___AGE_CATEGORY_FK___SEX_FK                                        (int tournamentUID, int TYPE_FK, int AGE_FROM, int AGE_TILL);
    static QSqlQuery *get___WEIGHT_FROM___WEIGHT_TILL                                       (int tournamentUID, int TYPE_FK, int AGE_FROM, int AGE_TILL, int SEX_FK, int ageCatUID);
    static QSqlQuery *get___TC_UIDS                                                         (int tournamentUID, int TYPE_FK, int AGE_FROM, int AGE_TILL, int SEX_FK, int ageCatUID, int WEIGHT_FROM, int WEIGHT_TILL);


    // для таблицы GRID
    static QVector<NodeOfTournirGrid> getNodes(long long tournamentCategoryUID);
    static QSqlQuery* getFightNodes(int tournamentCategoryUID);
    //static int f(int tournamentCategoryUID, int day, int time);
    //static QSqlQuery * ff(int tournamentCategoryUID);
    static QVector<QVector<NodeOfTournirGrid> > getNodesAsLevelListOfList(long long tournamentCategoryUID);
    static QVector<NodeOfTournirGrid> getLeafOFTree(long long tournamentCategoryUID);
    static QVector<NodeOfTournirGrid> getFightingNodes(long long tournamentCategoryUID);
    static void insertLeafOfGrid(long long TOURNAMENT_CATEGORIES_FK, long long VERTEX, long long orderUID);
    static bool insertResultOfFightForNodeOfGrid(long long TOURNAMENT_CATEGORIES_FK, long long VERTEX, long long orderUID, QString result);
    static void swapNodesOfGrid(long long tournamentCategoryUID, int node0v, int node1v);
    static int getDurationOfGrid(long long tournamentCategoryUID, int delay = 0);
    static int getDurationOfFightinPair(long long tournamentCategoryUID);
    static std::pair<int, int> getPlace(long long UIDOrder);
    static QVector<std::pair<long long, std::pair<int, int>>> getUIDsAndPlaces(long long tournamentCategoryUID, int maxPlace, bool skeepEmptyGrids);
    static int getNumberOfCastingOfLots(long long UIDOrder);
    static bool updateLevelOfNodeOfGrid(int TOURNAMENT_CATEGORIES_FK, int VERTEX, int DAY_FIGHT, int TIME_FIGHT);




    // для таблицы TOURNAMENT_CATEGORIES
    static QVector<long long> get_UIDs_of_TOURNAMENT_CATEGORIES(long long tournamentUID);
    static QVector<long long> get_UIDOrder_for_TC(long long UIDtournamentCategory);
    static QVector<std::tuple<long long, int, int, long long> > get_distinct_TYPE_FK_AgeFrom_AgeTill(long long tournamentUID);
    static QMap<QString, QVector<long long> > get_weight_and_orderUIDs(long long tournamentUID, long long type_fk, int age_from, int age_till, int sex_fk, int maxPlace);
    static QString getWeightAsOneNumberPlusMinus(long long uidCategory);
    static QString getNormanAgeRangeFromTOURNAMENT_CATEGORIES(long long uidCategory);
    static QString getNameForExcelSheet(long long uidTC);
    static int getMaxDayFromGrids(long long tournamentUID);
    static QString insertTournamentCaregory(
            long long ageCatUID, int ageFrom, int ageTill, QVector<double> weights,
            long long tournamentUID, long long typeUID, long long sexUID,
            int durationFighting, int durationBreak, int roundCount,
            int IN_CASE_TIE, int DURATION_EXTRA_ROUND,
            QString ageUnit, QString wordAgeFrom, QString wordAgeTill,
            QString weightUnit, QString wordWeightFrom, QString wordWeightTill);


    // для таблицы RING_TATAMI_LISTS_DATA
    static QSqlQuery *get___TYPE_FK___AGE_FROM___AGE_TILL(const int RING_TATAMI_LIST_FK);


    // для таблицы SCHEDULES
    static int getMaxCountOfRings(const int tournamentUID, const int day);
    static QSqlQuery* getSchelder(const int tournamentUID, const int day, const int ring);
    static bool updateSchedule(const int tournamentUID, const int day, const int ring, const int order, const int newOrder);
    static bool insertInSchedule(const int tournamentUID, const int day, const int ring, const int order, const int uidTC, const int level, const QString name);
    static bool deleteInSchedule(const int tournamentUID, const int day, const int ring, const int order);
    static QSqlQuery* getDateRingOrderFromSchedule(const int tournamentCategoryUID, const int level = -1);
    static int getAnotherRing(const int tournamentCategoryUID, const int day, const int ring);
    static std::tuple<int, int, int> getDayRingOrder(const int tournamentCategoryUID, const int level);

    static int getAge(QDate DATE_WEIGHTING, QDate birthdayDate);
    static QString roundDouble(double x, int precision);
    static QString convertToRoman(int val);
    static int isPow2(int a);


    // FIELD_TRANSLATES
    static QMap<QString, std::tuple<QString, QString>> get_NAME_RUS__RELATION_TABLE_NAME();


    enum TypeField
    {
        stringNumber,

        secondName,
        firstName,
        patromicName,
        birthyhdate,
        sex,
        weight,
        sportCategory,
        country,
        region,
        city,
        club,
        coach,

        NumberOfCastingOfLots,

        arabPlace,
        arabPlaceRange,
        romePlace,
        romePlaceRange,

        TC_ageRange,
        TC_weightRange,
        TC_weight,
        TC_sexAgeType,
        TC_TYPES,

        PlainText
    };


    static QVector<TypeField> getAllTypeFieldl(){
        QVector<TypeField> allTypeField({
                                            stringNumber,

                                            secondName,
                                            firstName,
                                            patromicName,
                                            birthyhdate,
                                            sex,
                                            weight,
                                            sportCategory,
                                            country,
                                            region,
                                            city,
                                            club,
                                            coach,

                                            NumberOfCastingOfLots,

                                            arabPlace,
                                            arabPlaceRange,
                                            romePlace,
                                            romePlaceRange,

                                            TC_ageRange,
                                            TC_weightRange,
                                            TC_weight,
                                            TC_sexAgeType,
                                            TC_TYPES,

                                            PlainText
                                        });
        return allTypeField;
    }

    static QMap<TypeField, QString> getExplanationOfTypeField()
    {
        QMap<TypeField, QString> map;
        map[TypeField::stringNumber   ] = "# (Порядковый номер строки)";

        map[TypeField::secondName     ] = "Фамилия";
        map[TypeField::firstName      ] = "Имя";
        map[TypeField::patromicName   ] = "Отчество";
        map[TypeField::birthyhdate    ] = "Дата рождения";
        map[TypeField::sex            ] = "Пол";
        map[TypeField::weight         ] = "Вес спортсмена";
        map[TypeField::sportCategory  ] = "Спортивный разряд";
        map[TypeField::country        ] = "Страна";
        map[TypeField::region         ] = "Регион";
        map[TypeField::city           ] = "Город";
        map[TypeField::club           ] = "Клуб";
        map[TypeField::coach          ] = "Тренер";

        map[TypeField::NumberOfCastingOfLots] = "Номер жеребьёвки";



        map[TypeField::arabPlace      ] = "Занятое место арабскими цифрами (1, 2, 3, ...)";
        map[TypeField::arabPlaceRange ] = "Диапазон мест арабскими цифрами (1, 2, 3-4, ...)";
        map[TypeField::romePlace      ] = "Занятое место римскими цифрами (I, II, III, IV, ...)";
        map[TypeField::romePlaceRange ] = "Диапазон мест римскими цифрами (I, II, III-IV, ...)";

        map[TypeField::TC_ageRange    ] = "ТК: до 7 лет, 12-15 лет, от 35 лет";
        map[TypeField::TC_weightRange ] = "ТК: до 40 кг, от 50 до 70 кг, свыше 90 кг";
        map[TypeField::TC_weight      ] = "ТК: -40 кг, 50 кг, 70 кг, +83 кг";
        map[TypeField::TC_sexAgeType  ] = "ТК: Юноши, Девушки, Юниоры...";
        map[TypeField::TC_TYPES       ] = "TК: Фулконтакт, Лайт, Пойнтфайтинг..." ;

        map[TypeField::PlainText      ] = "Произвольный текст";

        return map;
    }

    static QString get(QVector<std::pair<DBUtils::TypeField, QString>> arrayData, long long uidOrder, int rowNumber = -1)
    {
        QString result;
        for (int i = 0; i < arrayData.size(); ++i)
        {
            result += get(arrayData[i], uidOrder, rowNumber);
        }
        return result;
    }

    static QString get(std::pair<DBUtils::TypeField, QString> data, long long uidOrder, int rowNumber = -1)
    {
        QString text;
        long long uidTC = getField("TOURNAMENT_CATEGORY_FK", "ORDERS", uidOrder).toLongLong();

        TypeField typeField = data.first;

        if (typeField == stringNumber)
        {
            text = QString::number(rowNumber);
        }

        else if (typeField == secondName)
        {
            text = getField("SECOND_NAME", "ORDERS", uidOrder, __PRETTY_FUNCTION__);
        }
        else if (typeField == firstName)
        {
            text = getField("FIRST_NAME", "ORDERS", uidOrder, __PRETTY_FUNCTION__);
        }
        else if (typeField == patromicName)
        {
            text = getField("PATRONYMIC", "ORDERS", uidOrder, __PRETTY_FUNCTION__);
        }
        else if (typeField == birthyhdate)
        {
            text = getFieldDate("BIRTHDATE", "ORDERS", uidOrder, __PRETTY_FUNCTION__);
        }
        else if (typeField == sex)
        {
            text = getField("SHORTNAME", "SEXES", getField("SEX_FK", "ORDERS", uidOrder, __PRETTY_FUNCTION__), __PRETTY_FUNCTION__);
        }
        else if (typeField == weight)
        {
            text = roundDouble(getField("WEIGHT", "ORDERS", uidOrder, __PRETTY_FUNCTION__).toDouble(), 3);
        }
        else if (typeField == sportCategory)
        {
            text = getField("NAME", "SPORT_CATEGORIES", getField("SPORT_CATEGORY_FK", "ORDERS", uidOrder, __PRETTY_FUNCTION__), __PRETTY_FUNCTION__);
        }
        else if (typeField == country)
        {
            text = getField("NAME", "COUNTRIES", getField("COUNTRY_FK", "ORDERS", uidOrder, __PRETTY_FUNCTION__), __PRETTY_FUNCTION__);
        }
        else if (typeField == region)
        {
            text = getField("NAME", "REGIONS", getField("REGION_FK", "ORDERS", uidOrder, __PRETTY_FUNCTION__), __PRETTY_FUNCTION__);
        }
        else if (typeField == city)
        {
            text = getField("NAME", "REGION_UNITS", getField("REGION_UNIT_FK", "ORDERS", uidOrder, __PRETTY_FUNCTION__), __PRETTY_FUNCTION__);
        }
        else if (typeField == club)
        {
            text = getField("NAME", "CLUBS", getField("CLUB_FK", "ORDERS", uidOrder, __PRETTY_FUNCTION__), __PRETTY_FUNCTION__);
        }
        else if (typeField == coach)
        {
            text = getField("NAME", "COACHS", getField("COACH_FK", "ORDERS", uidOrder, __PRETTY_FUNCTION__), __PRETTY_FUNCTION__);
        }


        else if (typeField == NumberOfCastingOfLots)
        {
            text = QString::number(getNumberOfCastingOfLots(uidOrder));
        }


        else if (typeField == arabPlace)
        {
            std::pair<int, int> place = DBUtils::getPlace(uidOrder);
            if (1 <= place.first)
                text = QString::number(place.first);
        }
        else if (typeField == arabPlaceRange)
        {
            std::pair<int, int> place = DBUtils::getPlace(uidOrder);
            if (1 <= place.first)
            {
                if (place.first == place.second)
                    text = QString::number(place.first);
                else
                    text = QString::number(place.first) + '-' + QString::number(place.second);
            }
        }
        else if (typeField == romePlace)
        {
            std::pair<int, int> place = DBUtils::getPlace(uidOrder);
            if (1 <= place.first)
            {
                text = convertToRoman(place.first);
            }
        }
        else if (typeField == romePlaceRange)
        {
            std::pair<int, int> place = DBUtils::getPlace(uidOrder);
            if (1 <= place.first)
            {
                if (place.first == place.second)
                    text = convertToRoman(place.first);
                else
                    text = convertToRoman(place.first) + "-" + convertToRoman(place.second);
            }
        }


        else if (typeField == TC_ageRange)
        {
            text = DBUtils::getField("AGE", "TOURNAMENT_CATEGORIES", uidTC);
        }
        else if (typeField == TC_weightRange)
        {
            text = DBUtils::getField("WEIGHT", "TOURNAMENT_CATEGORIES", uidTC);
        }
        else if (typeField == TC_weight)
        {
            text = getWeightAsOneNumberPlusMinus(uidTC);
        }
        else if (typeField == TC_sexAgeType)
        {
            text = getField("NAME", "AGE_CATEGORIES", getField("AGE_CATEGORY_FK", "TOURNAMENT_CATEGORIES", uidTC, __PRETTY_FUNCTION__), __PRETTY_FUNCTION__);
        }
        else if (typeField == TC_TYPES)
        {
            text = getField("NAME", "TYPES", getField("TYPE_FK", "TOURNAMENT_CATEGORIES", uidTC, __PRETTY_FUNCTION__), __PRETTY_FUNCTION__);
        }

        else if (typeField == PlainText)
        {
            text = data.second;
        }
        else
        {
            qDebug() << "WTF" << __PRETTY_FUNCTION__;
        }
        return text;
    }


    static QString toString(std::pair<TypeField, QString> pair);

    static QString toString(QVector<std::pair<TypeField, QString>> vector);

};


#endif // DBUTILS_H
