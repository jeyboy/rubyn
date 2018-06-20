#ifndef JSON_ARR_H
#define JSON_ARR_H

#include "json.h"
#include <qjsonarray.h>

class JsonArr : public Json, public QJsonArray {
public:
    static JsonArr fromJsonStr(const QByteArray & text);
    static JsonArr fromJsonStr(const QByteArray & text, QString & error);
    static JsonArr fromJsonStr(const QString & text);
    static JsonArr fromJsonStr(const QString & text, QString & error);

    QByteArray toJsonStr(const JsonFormat & format = Compact);
    QVariant toVariant() const;

    JsonArr();
    JsonArr(const QJsonArray & oth);
    JsonArr & operator=(const QJsonArray & x);

    operator QJsonArray() const;
    operator Json() const;

    Json::Type type() const;

    inline bool isArray() const { return true; }

    int size();

    QString concatKeys(const QString & key, const QString & separator);
    QString concatKeys(const QString & separator);

    Json operator[](const int & index);
    Json val(const int & index);

    JsonArr arr() const;
    JsonArr arr(const int & index);
    JsonArr arr(const int & index, const JsonArr & def_val);

    bool boolean(const int & index, const bool def_val = false);
    int integer(const int & index, const int def_val = 0);
    qint64 bigInt(const int & index, const qint64 def_val = 0);
    double rational(const int & index, const double def_val = 0);
    QString string(const int & index);
    QString stringDef(const int & index, const QString & def_val);
    QString forceString(const int & index);
    QString forceStringDef(const int & index, const QString & def_val);
};

#endif // JSON_ARR_H
