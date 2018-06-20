#include "json_obj.h"
#include <qjsonarray.h>
#include <qvariant.h>

JsonObj JsonObj::fromJsonStr(const QByteArray & text) { return Json::fromJsonStr(text).toObject(); }
JsonObj JsonObj::fromJsonStr(const QByteArray & text, QString & error) { return Json::fromJsonStr(text, error).toObject(); }
JsonObj JsonObj::fromJsonStr(const QString & text) { return Json::fromJsonStr(text).toObject(); }
JsonObj JsonObj::fromJsonStr(const QString & text, QString & error) { return Json::fromJsonStr(text, error).toObject(); }

QByteArray JsonObj::toJsonStr(const JsonFormat & format) { return operator Json().toJsonStr(format); }
QVariant JsonObj::toVariant() const { return operator Json().toVariant(); }

JsonObj::JsonObj() : QJsonObject() {}
JsonObj::JsonObj(const QJsonObject & oth_json) : QJsonObject(oth_json) {}

JsonObj & JsonObj::operator=(const QJsonObject & x) { QJsonObject::operator=(x); return *this; }

JsonObj::operator QJsonObject() const  { return (QJsonObject)*this; }
JsonObj::operator Json() const  { return Json(operator QJsonObject()); }

Json::Type JsonObj::type() const { return Json::Object; }

int JsonObj::size() { return QJsonObject::size(); }

bool JsonObj::hasKey(const QString & key) { return contains(key); }

QString JsonObj::concatKeys(const QString & key1, const QString & key2, const QString & separator) {
   return string(key1) % separator % string(key2);
}

Json JsonObj::operator[](const QString & key) { return QJsonObject::value(key); }
Json JsonObj::val(const QString & key) { return QJsonObject::value(key); }

JsonObj JsonObj::obj() const { return *this; }
JsonObj JsonObj::obj(const QString & key) { return val(key).toObject(); }
JsonObj JsonObj::obj(const QString & key, const JsonObj & def_val) { return val(key).toObject(def_val); }

bool JsonObj::boolean(const QString & key, const bool & def_val) { return val(key).toBool(def_val); }

int JsonObj::integer(const QString & key, const int & def_val) { return val(key).toInt(def_val); }

qint64 JsonObj::bigInt(const QString & key, const qint64 & def_val) { return JOBJ_BINT(val(key), def_val); }

double JsonObj::rational(const QString & key, const double & def_val) { return val(key).toDouble(def_val); }

QString JsonObj::string(const QString & key) { return val(key).toString(); }
QString JsonObj::stringDef(const QString & key, const QString & def_val) { return val(key).toString(def_val); }

QString JsonObj::forceString(const QString & key) { return J_STR(val(key)); }
QString JsonObj::forceStringDef(const QString & key, const QString & def_val) { return J_STR_DEF(val(key), def_val); }
