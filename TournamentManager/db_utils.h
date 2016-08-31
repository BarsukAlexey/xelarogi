#ifndef DBUTILS_H
#define DBUTILS_H

#include <algorithm>

#include <QDate>
#include <QDebug>
#include <QMap>
#include <QSqlDatabase>
#include <QStringList>
#include <QVector>


class DBUtils
{

public:

    struct NodeOfTournirGrid
    {
        int v; // id вершины; вершины нумируются как в дереве отрезков (только зеркально)
        QString name;
        QString region;
        bool isFighing;
        long long UID;
        QString result;

        bool operator < (const NodeOfTournirGrid& other) const
        {
            return v < other.v;
        }
    };

    struct Fighing
    {
        long long UID0;
        long long UID1;
        long long VERTEX;
        long long TOURNAMENT_CATEGORIES_FK;
        int winer;

        bool operator < (const Fighing& other) const
        {
            return VERTEX < other.VERTEX;
        }
    };

    static QString getField(const QString& field, const QString& table, const QString& UID, QString PRETTY_FUNCTION = __PRETTY_FUNCTION__);
    static QString getField(const QString& field, const QString& table, const long long UID, QString PRETTY_FUNCTION = __PRETTY_FUNCTION__);
    static QString getFieldDate(const QString& field, const QString& table, const long long UID, QString PRETTY_FUNCTION = __PRETTY_FUNCTION__);
    static QDate getFieldDateAsDate(const QString& field, const QString& table, const long long UID);


    // для таблицы ORDERS
    static QString getSecondNameAndFirstName(long long UID);
    static QString getSecondNameAndOneLetterOfName(long long UID);
    static QSet<long long> getSetOfOrdersInTournamentCategory(long long uidTournamentCategory);


    // для таблицы TOURNAMENTS
    static QString getTournamentNameAsHeadOfDocument(long long tournamentUID);
    static QStringList get_DAYS_FROM_TOURNAMENTS(long long);
    static QVector<QString> getJudges(long long tournamentUID);


    // для таблицы GRID
    static QVector<NodeOfTournirGrid> getNodes(long long tournamentCategoryUID);
    static QVector<QVector<NodeOfTournirGrid> > getNodesAsLevelListOfList(long long tournamentCategoryUID);
    static QVector<NodeOfTournirGrid> getLeafOFTree(long long tournamentCategoryUID);
    static QVector<NodeOfTournirGrid> getFightingNodes(long long tournamentCategoryUID);
    static QVector<QVector<Fighing> > getListsOfPairsForFighting(long long tournamentUID);
    static QVector<Fighing> getListOfPairsForFighting(long long TOURNAMENT_CATEGORIES_FK);
    static QVector<Fighing> getListOfPairsForFightingForPointFighting(long long TOURNAMENT_CATEGORIES_FK);
    static void insertLeafOfGrid(long long TOURNAMENT_CATEGORIES_FK, long long VERTEX, long long orderUID);
    static bool updateNodeOfGrid(long long TOURNAMENT_CATEGORIES_FK, long long VERTEX, long long orderUID, QString result);
    static void swapNodesOfGrid(long long tournamentCategoryUID, int node0v, int node1v);
    static int findDurationOfGrid(long long tournamentCategoryUID, int delay = 0);
    static int findDurationOfFightinPair(long long tournamentCategoryUID);
    static std::pair<int, int> getPlace(long long UIDOrder);
    static QVector<std::pair<long long, std::pair<int, int>>> getUidAndPlace(long long tournamentCategoryUID);
    static int getNumberOfCastingOfLots(long long UIDOrder);



    // для таблицы TOURNAMENT_CATEGORIES
    static QVector<long long> get_UIDs_of_TOURNAMENT_CATEGORIES(long long tournamentUID);
    static QVector<long long> get_UIDOrder_for_TC(long long UIDtournamentCategory);
    static QVector<std::tuple<long long, int, int, long long> > get_distinct_TYPE_FK_AgeFrom_AgeTill(long long tournamentUID);
    static QMap<QString, QVector<long long> > get_weight_and_orderUIDs(long long tournamentUID, long long type_fk, int age_from, int age_till, int sex_fk, int maxPlace);
    //static QString getNormanWeightRangeFromTOURNAMENT_CATEGORIES(long long uidCategory);
    static QString getWeightAsOneNumberPlusMinus(long long uidCategory);
    static QString getNormanAgeRangeFromTOURNAMENT_CATEGORIES(long long uidCategory);
    static QString getNameForExcelSheet(long long uidTC);



    static int getAge(QDate DATE_WEIGHTING, QDate birthdayDate);
    static QString roundDouble(double x, int precision);
    static QString convertToRoman(int val);
    static int isPow2(int a);
    static QString getRussianMonth(int m);




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
            if (i != 0)
                result += " ";
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
            text = QString::number(place.first);
        }
        else if (typeField == arabPlaceRange)
        {
            std::pair<int, int> place = DBUtils::getPlace(uidOrder);
            if (place.first == place.second)
                text = QString::number(place.first);
            else
                text = QString::number(place.first) + '-' + QString::number(place.second);
        }
        else if (typeField == romePlace)
        {
            std::pair<int, int> place = DBUtils::getPlace(uidOrder);
            text = convertToRoman(place.first);
        }
        else if (typeField == romePlaceRange)
        {
            std::pair<int, int> place = DBUtils::getPlace(uidOrder);
            if (place.first == place.second)
                text = convertToRoman(place.first);
            else
                text = convertToRoman(place.first) + "-" + convertToRoman(place.second);
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
