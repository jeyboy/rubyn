#include "json.h"

#include <qjsondocument.h>
#include <qvariant.h>

#include "json_obj.h"
#include "json_arr.h"


Json Json::fromVariant(const QVariant & variant) { return QJsonValue::fromVariant(variant); }

Json Json::fromJsonStr(const QString & text) { return fromJsonStr(text.toUtf8()); }
Json Json::fromJsonStr(const QString & text, QString & error) { return fromJsonStr(text.toUtf8(), error); }
Json Json::fromJsonStr(const QByteArray & text) {
    QString error;
    return fromJsonStr(text, error);
}
Json Json::fromJsonStr(const QByteArray & text, QString & error) {
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(text, &err);
    if (err.error != QJsonParseError::NoError) {
        error = err.errorString();
        return Json();
    }
    return (Json)doc;
}

QByteArray Json::toJsonStr(const JsonFormat & format) {
    return (isArray() ? QJsonDocument(toArray()) : QJsonDocument(toObject())).toJson((QJsonDocument::JsonFormat)format);
}
QVariant Json::toVariant() const { return QJsonValue::toVariant(); }

Json::Json(const Json::Type & jtype) : QJsonValue(jtype) {}
Json::Json(const QJsonDocument & doc) : QJsonValue(doc.isArray() ? (QJsonValue)doc.array() : (QJsonValue)doc.object()) {}
Json::Json(const JsonObj & obj) : QJsonValue((QJsonObject)obj) {}
Json::Json(const QJsonObject & obj) : QJsonValue(obj) {}
Json::Json(const JsonArr & arr) : QJsonValue((QJsonArray)arr) {}
Json::Json(const QJsonArray & arr) : QJsonValue(arr) {}
Json::Json(const QJsonValueRef & ref) : QJsonValue(ref) {}

Json::Json(const QJsonValue & val) : QJsonValue(val) { }
Json & Json::operator=(const QJsonValue & x) { QJsonValue::operator=(x); return *this; }
Json & Json::operator=(const QJsonValueRef & x) { QJsonValue::operator=(x); return *this; }
Json::operator QJsonValue() { return (QJsonValue)*this; }

Json::~Json() {}

Json::Type Json::type() const { return QJsonValue::type(); }

int Json::size() { return isArray() ? QJsonValue::toArray().size() : QJsonValue::toObject().size(); }

bool Json::hasKey(const QString & key) { return QJsonValue::toObject().contains(key); }
bool Json::hasIndex(const int & index) { return QJsonValue::toArray().size() > index; }

// only object
QString Json::concatKeys(const QString & key1, const QString & key2, const QString & separator) {
    return ((JsonObj)toObject()).concatKeys(key1, key2, separator);
}

// only array
QString Json::concatKeys(const QString & key, const QString & separator) {
    return ((JsonArr)QJsonValue::toArray()).concatKeys(key, separator);
}

QString Json::concatKeys(const QString & separator) {
    return ((JsonArr)QJsonValue::toArray()).concatKeys(separator);
}


Json Json::operator[](const int & index) { return val(index); }
Json Json::operator[](const QString & key) { return val(key); }


Json Json::val(const int & index) { return QJsonValue::toArray().at(index); }
Json Json::val(const QString & key) { return QJsonValue::toObject().value(key); }


JsonObj Json::obj() const { return QJsonValue::toObject(); }
JsonObj Json::obj(const QJsonObject & default_value) const { return QJsonValue::toObject(default_value); }
JsonObj Json::obj(const int & index) { return val(index).toObject(); }
JsonObj Json::obj(const int & index, const JsonObj & def_val) { return val(index).toObject(def_val); }
JsonObj Json::obj(const QString & key) { return val(key).toObject(); }
JsonObj Json::obj(const QString & key, const JsonObj & def_val) { return val(key).toObject(def_val); }


JsonArr Json::arr() const { return QJsonValue::toArray(); }
JsonArr Json::arr(const QJsonArray & default_value) const { return QJsonValue::toArray(default_value); }
JsonArr Json::arr(const int & index) { return val(index).toArray(); }
JsonArr Json::arr(const int & index, const JsonArr & def_val) { return val(index).toArray(def_val); }
JsonArr Json::arr(const QString & key) { return val(key).toArray(); }
JsonArr Json::arr(const QString & key, const JsonArr & def_val) { return val(key).toArray(def_val); }


bool Json::boolean(const bool def_val) { return QJsonValue::toBool(def_val); }
bool Json::boolean(const int & index, const bool def_val) { return operator[](index).toBool(def_val); }
bool Json::boolean(const QString & key, const bool def_val) { return operator[](key).toBool(def_val); }


int Json::integer(const int def_val) { return QJsonValue::toInt(def_val); }
int Json::integer(const int & index, const int def_val) { return operator[](index).toInt(def_val); }
int Json::integer(const QString & key, const int def_val) { return operator[](key).toInt(def_val); }


qint64 Json::bigInt(const qint64 & def_val) { return JOBJ_BINT((*this), def_val); }
qint64 Json::bigInt(const int & index, const qint64 & def_val) { return JOBJ_BINT(operator[](index), def_val); }
qint64 Json::bigInt(const QString & key, const qint64 & def_val) { return JOBJ_BINT(operator[](key), def_val); }


double Json::rational(const double & def_val) { return QJsonValue::toDouble(def_val); }
double Json::rational(const int & index, const double & def_val) { return operator[](index).toDouble(def_val); }
double Json::rational(const QString & key, const double & def_val) { return operator[](key).toDouble(def_val); }


QString Json::string() { return QJsonValue::toString(); }
QString Json::stringDef(const QString & def_val) { return QJsonValue::toString(def_val); }
QString Json::string(const int & index) { return operator[](index).toString(); }
QString Json::string(const int & index, const QString & def_val) { return operator[](index).toString(def_val); }
QString Json::string(const QString & key) { return operator[](key).toString(); }
QString Json::string(const QString & key, const QString & def_val) { return val(key).toString(def_val); }


QString Json::forceString() { return J_STR((*this)); }
QString Json::forceStringDef(const QString & def_val) { return J_STR_DEF((*this), def_val); }
QString Json::forceString(const int & index) { return J_STR(operator[](index)); }
QString Json::forceString(const int & index, const QString & def_val) { return J_STR_DEF(operator[](index), def_val); }
QString Json::forceString(const QString & key) { return J_STR(operator[](key)); }
QString Json::forceString(const QString & key, const QString & def_val) { return J_STR_DEF(operator[](key), def_val); }
