#ifndef FORMAT_H
#define FORMAT_H

#include <qstringbuilder.h>
#include <qstringlist.h>

class Info {
    static QString unitList[];
public:
    static bool isNumber(const QString & str);
    static bool extractNumber(const QString & text, QString & res, int index = 0);
    // return first part, splited by start and end predicate (result includes predicates)
    static bool extract(const QString & text, const QString & start_predicate, const QString & end_predicate, QString & res);

    // return first part, splited by start and end predicate (without predicates)
    static QString extractLimitedBy(const QString & text, const QString & before_predicate, const QString & after_predicate);
    // return all parts, splited by start and end predicate
    static QStringList extractPartsLimitedBy(const QString & text, const QString & start_predicate, const QString & end_predicate);

    static QString toUnits(long long val);
    static long long fromUnits(const QString & val);

    static QString paddedNumber(quint64 time);

    static QString & camelcaseToUnderscore(QString & str);
};

//class Duration {
//public:
//    static QString fromHMS(int h, int m, int s, bool forciblyIncludeHours);
//    static QString fromSeconds(int seconds, bool includeHours = false);
//    static QString fromMillis(qint64 millis, bool includeHours = false);

//    static bool hasHours(qint64 millis);
//    static qint64 ISO8601StrtoMillis(const QString & str);
//    static qint64 toSecs(const QString & str);
//    static qint64 toMillis(const QString & str);
//};

#endif // FORMAT_H
