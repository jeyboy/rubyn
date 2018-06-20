#ifndef JSON_OBJ_H
#define JSON_OBJ_H

#include "json.h"

#include <qjsonobject.h>

class JsonObj : public Json, public QJsonObject {
public:
    static JsonObj fromJsonStr(const QByteArray & text);
    static JsonObj fromJsonStr(const QByteArray & text, QString & error);
    static JsonObj fromJsonStr(const QString & text);
    static JsonObj fromJsonStr(const QString & text, QString & error);

    QByteArray toJsonStr(const JsonFormat & format = Compact);
    QVariant toVariant() const;

    JsonObj();
    JsonObj(const QJsonObject & oth);
    JsonObj & operator=(const QJsonObject & x);

    operator QJsonObject() const;
    operator Json() const;

    Json::Type type() const;

    inline bool isObject() const { return true; }

    int size();

    bool hasKey(const QString & key);

    QString concatKeys(const QString & key1, const QString & key2, const QString & separator);

    Json operator[](const QString & key);
    Json val(const QString & key);

    JsonObj obj() const;
    JsonObj obj(const QString & key);
    JsonObj obj(const QString & key, const JsonObj & def_val);

    bool boolean(const QString & key, const bool & def_val = false);

    int integer(const QString & key, const int & def_val = 0);

    qint64 bigInt(const QString & key, const qint64 & def_val = 0);

    double rational(const QString & key, const double & def_val = 0);

    QString string(const QString & key);
    QString stringDef(const QString & key, const QString & def_val);

    QString forceString(const QString & key);
    QString forceStringDef(const QString & key, const QString & def_val);
};

#endif // JSON_OBJ_H
