#ifndef JSON_H
#define JSON_H

#include "json_global.h"
#include <qjsonvalue.h>

class QJsonDocument;
class JsonObj;
class QJsonObject;
class JsonArr;
class QJsonArray;
class QJsonValueRef;
class QJsonParseError;

//#define J_KEY2SS(key1, key2) toObject().value(key1).toObject().value(key2)
//#define J_KEY2II(index1, index2) toArray().at(index1).toArray()[index2]
//#define J_KEY2IS(index1, key2) toArray().at(index1).toObject().value(key2)
//#define J_KEY2SI(key1, index2) toObject().value(key1).toArray().at(index2)

//#define JOBJ_KEY2SS(key1, key2) value(key1).toObject().value(key2)
//#define JOBJ_KEY2II(index1, index2) at(index1).toArray().at(index2)
//#define JOBJ_KEY2IS(index1, key2) at(index1).toObject().value(key2)
//#define JOBJ_KEY2SI(key1, index2) value(key1).toArray().at(index2)

#define J_STR(jval) jval.isString() ? jval.toString() : QString::number(JOBJ_BINT(jval, 0));
#define J_STR_DEF(jval, def_val) jval.isString() ? jval.toString(def_val) : QString::number(JOBJ_BINT(jval, 0));
#define JOBJ_BINT(val, def_val) (qint64)val.toDouble(def_val)

class Json : public QJsonValue {
public:
    enum JsonFormat { Indented, Compact };

    static Json fromVariant(const QVariant & variant);

    static Json fromJsonStr(const QString & text);
    static Json fromJsonStr(const QString & text, QString & error);
    static Json fromJsonStr(const QByteArray & text);
    static Json fromJsonStr(const QByteArray & text, QString & error);

    virtual QVariant toVariant() const;
    virtual QByteArray toJsonStr(const JsonFormat & format = Compact);

    virtual bool isArray() const { return type() == Array; }
    virtual bool isObject() const { return type() == Object; }

    Json(const Json::Type & = Null);
    Json(const QJsonDocument & doc);
    explicit Json(const JsonObj & obj);
    Json(const QJsonObject & obj);
    explicit Json(const JsonArr & arr);
    Json(const QJsonArray & arr);
    Json(const QJsonValueRef & ref);

    Json(const QJsonValue &);
    Json & operator=(const QJsonValue & x);
    Json & operator=(const QJsonValueRef & x);
    operator QJsonValue();

    virtual ~Json();

    virtual Json::Type type() const;

    virtual int size();

    virtual bool hasKey(const QString & key);
    virtual bool hasIndex(const int & index);

    // concat keys from obj hash
    virtual QString concatKeys(const QString & key1, const QString & key2, const QString & separator);
    // concat key from array of objs
    virtual QString concatKeys(const QString & key, const QString & separator);
    virtual QString concatKeys(const QString & separator);

    virtual Json operator[](const int & index);
    virtual Json operator[](const QString & key);
    virtual Json val(const int & index);
    virtual Json val(const QString & key);

    virtual JsonObj obj() const;  
    virtual JsonObj obj(const QJsonObject & default_value) const;
    virtual JsonObj obj(const int & index);
    virtual JsonObj obj(const int & index, const JsonObj & def_val);
    virtual JsonObj obj(const QString & key);
    virtual JsonObj obj(const QString & key, const JsonObj & def_val);

    virtual JsonArr arr() const;
    virtual JsonArr arr(const QJsonArray & default_value) const;
    virtual JsonArr arr(const int & index);
    virtual JsonArr arr(const int & index, const JsonArr & def_val);
    virtual JsonArr arr(const QString & key);
    virtual JsonArr arr(const QString & key, const JsonArr & def_val);


    virtual bool boolean(const bool def_val = false);
    virtual bool boolean(const int & index, const bool def_val = false);
    virtual bool boolean(const QString & key, const bool def_val = false);


    virtual int integer(const int def_val = 0);
    virtual int integer(const int & index, const int def_val = 0);
    virtual int integer(const QString & key, const int def_val = 0);


    virtual qint64 bigInt(const qint64 & def_val = 0);
    virtual qint64 bigInt(const int & index, const qint64 & def_val = 0);
    virtual qint64 bigInt(const QString & key, const qint64 & def_val = 0);


    virtual double rational(const double & def_val = 0);
    virtual double rational(const int & index, const double & def_val = 0);
    virtual double rational(const QString & key, const double & def_val = 0);


    virtual QString string();
    virtual QString stringDef(const QString & default_value);
    virtual QString string(const int & index);
    virtual QString string(const int & index, const QString & default_value);
    virtual QString string(const QString & key);
    virtual QString string(const QString & key, const QString & default_value);


    virtual QString forceString();
    virtual QString forceStringDef(const QString & default_value);
    virtual QString forceString(const int & index);
    virtual QString forceString(const int & index, const QString & default_value);
    virtual QString forceString(const QString & key);
    virtual QString forceString(const QString & key, const QString & default_value);
};

#endif // JSON_H
