#ifndef DBUTILS_H
#define DBUTILS_H

#include <algorithm>

#include <algorithm>

#include <QDate>
#include <QDebug>
#include <QMap>
#include <QVector>
#include <QSqlDatabase>
#include <QStringList>


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


    static QString getNameTournamentByUID(const QSqlDatabase& , long long);
    static QString getTypeNameByUID(const QSqlDatabase& , long long);
    static QString get_SHORTNAME_FROM_SEXES(const QSqlDatabase& , long long);
    static QStringList get_DAYS_FROM_TOURNAMENTS(const QSqlDatabase& , long long);

    // для таблицы ORDERS
    static QString getSecondNameAndFirstName(long long UID);
    static QString getSecondNameAndOneLetterOfName(long long UID);
    static QString get__REGION(const QSqlDatabase& database, long long UID);
    static QSet<long long> getSetOfOrdersInTournamentCategory(long long uidTournamentCategory);
    static int getAge(QDate DATE_WEIGHTING, QDate birthdayDate);

    // для таблицы TOURNAMENTS
    static QString get_MAIN_JUDGE(const QSqlDatabase& database, long long tournamentUID);
    static QString get_MAIN_SECRETARY(const QSqlDatabase& database, long long tournamentUID);
    static QString get_ASSOCIATE_MAIN_JUDGE(const QSqlDatabase& database, long long tournamentUID);


    // для таблицы GRID
    static QVector<NodeOfTournirGrid> getNodes(long long tournamentCategoryUID);
    static QVector<QVector<NodeOfTournirGrid>> getNodesAsLevelListOfList(long long tournamentCategoryUID);
    static QVector<NodeOfTournirGrid> getLeafOFTree(const QSqlDatabase& database, long long tournamentCategoryUID);
    static QVector<NodeOfTournirGrid> getFightingNodes(long long tournamentCategoryUID);
    static QVector<QVector<Fighing>> getListsOfPairsForFighting(long long tournamentUID);
    static QVector<Fighing> getListOfPairsForFighting(long long TOURNAMENT_CATEGORIES_FK);
    static QVector<Fighing> getListOfPairsForFightingForPointFighting(long long TOURNAMENT_CATEGORIES_FK);
    static void insertLeafOfGrid(long long TOURNAMENT_CATEGORIES_FK, long long VERTEX, long long orderUID);
    static bool updateNodeOfGrid(const QSqlDatabase& database, long long TOURNAMENT_CATEGORIES_FK, long long VERTEX, long long orderUID, QString result);
    static void swapNodesOfGrid(long long tournamentCategoryUID, int node0v, int node1v);
    static int findDurationOfGrid(long long tournamentCategoryUID, int delay = 0);
    static int findDurationOfFightinPair(long long tournamentCategoryUID);
    static std::pair<int, int> getPlace(long long UIDOrder);



    // для таблицы TOURNAMENT_CATEGORIES
    static QVector<long long> get_UIDs_of_TOURNAMENT_CATEGORIES(long long tournamentUID);
    static QVector<long long> get_UIDOrder_for_TC(long long UIDtournamentCategory);
    static QVector<std::tuple<long long, int, int, long long> > get_distinct_TYPE_FK_AgeFrom_AgeTill(long long tournamentUID);
    static QMap<QString, QVector<long long> > get_weight_and_orderUIDs(long long tournamentUID, long long type_fk, int age_from, int age_till, int sex_fk);
    static QString getNormanWeightRangeFromTOURNAMENT_CATEGORIES(long long uidCategory);
    static QString getWeightAsOneNumberPlusMinus(long long uidCategory);
    static QString getNormanAgeRangeFromTOURNAMENT_CATEGORIES(long long uidCategory);




    static QString getNormanWeightRange(double a, double b);
    static QString getNormanAgeRange(int a, int b);
    static QString roundDouble(double x, int precision);
    static QString getTournamentNameAsHeadOfDocument(long long tournamentUID);
    static QString convertToRoman(int val);
    static int isPow2(int a);
    static QString getRussianMonth(int m);




    enum TypeField
    {
        secondName,
        firstName,
        patromicName,

        arabPlace,
        arabPlaceRange,
        romePlace,
        romePlaceRange,

        TC_ageRange,
        TC_yearRange,

        TC_weightRange,
        TC_weight,

        TC_sexAgeType,
        TC_TYPES,

        club,
        coach,

        PlainText
    };


    static QVector<TypeField> getAllTypeFieldl(){
        QVector<TypeField> allTypeField({
                                            secondName,
                                            firstName,
                                            patromicName,

                                            arabPlace,
                                            arabPlaceRange,
                                            romePlace,
                                            romePlaceRange,

                                            TC_ageRange,
                                            TC_yearRange,

                                            TC_weightRange,
                                            TC_weight,

                                            TC_sexAgeType,
                                            TC_TYPES,

                                            club,
                                            coach,

                                            PlainText
                                        });
        return allTypeField;
    }

    static QMap<TypeField, QString> getExplanationOfTypeField()
    {
        QMap<TypeField, QString> map;
        map[TypeField::secondName     ] = "Фамилия";
        map[TypeField::firstName      ] = "Имя";
        map[TypeField::patromicName   ] = "Отчество";

        map[TypeField::arabPlace      ] = "Занятое место арабскими цифрами (1, 2, 3, ...)";
        map[TypeField::arabPlaceRange ] = "Занятое место арабскими цифрами (1, 2, 3-4, ...)";
        map[TypeField::romePlace      ] = "Занятое место римскими цифрами (1, 2, 3, ...)";
        map[TypeField::romePlaceRange ] = "Занятое место римскими цифрами (1, 2, 3-4, ...)";

        map[TypeField::TC_ageRange    ] = "ТК: до 7 лет, 12-15 лет, от 35 лет";
        map[TypeField::TC_yearRange   ] = "ТК: 1997-1999 г.р., 2000-2003 г.р.";
        map[TypeField::TC_weightRange ] = "ТК: до 40 кг, от 50 до 70 кг, свыше 90 кг";
        map[TypeField::TC_weight      ] = "ТК: -40 кг, 50 кг, 70 кг, +83 кг";
        map[TypeField::TC_sexAgeType  ] = "ТК: Юноши, Девушки, Юниоры...";
        map[TypeField::TC_TYPES       ] = "TК: Фулконтакт, Лайт, Пойнтфайтинг..." ;

        map[TypeField::PlainText      ] = "Произвольный текст";

        map[TypeField::PlainText      ] = "Произвольный текст";

        return map;
    }

    static QString get(TypeField typeField, long long uidOrder)
    {
        QString text;
        long long uidTC = getField("TOURNAMENT_CATEGORY_FK", "ORDERS", uidOrder).toLongLong();

        if (typeField == secondName)
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
        else if (typeField == TC_ageRange)
        {
            text = getNormanAgeRangeFromTOURNAMENT_CATEGORIES(uidTC);
        }
        else if (typeField == TC_weightRange)
        {
            text = getNormanWeightRangeFromTOURNAMENT_CATEGORIES(uidTC);
        }
        else if (typeField == TC_weight)
        {
            text = getWeightAsOneNumberPlusMinus(uidTC);
        }
        else if (typeField == arabPlace)
        {
            text = QString::number(DBUtils::getPlace(uidOrder).first);
        }
        else if (typeField == romePlace)
        {
            text = convertToRoman(DBUtils::getPlace(uidOrder).first);
        }
        else if (typeField == TC_sexAgeType)
        {
            text = getField("NAME", "AGE_CATEGORIES", getField("AGE_CATEGORY_FK", "TOURNAMENT_CATEGORIES", uidTC, __PRETTY_FUNCTION__), __PRETTY_FUNCTION__);
        }
        else if (typeField == TC_TYPES)
        {
            text = getField("NAME", "TYPES", getField("TYPE_FK", "TOURNAMENT_CATEGORIES", uidTC, __PRETTY_FUNCTION__), __PRETTY_FUNCTION__);
        }
        else
        {
            qDebug() << "WTF" << __PRETTY_FUNCTION__;
        }
        return text;
    }


};

#endif // DBUTILS_H
