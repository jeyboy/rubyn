#include "json_arr.h"
#include <qjsonobject.h>
#include <qvariant.h>

JsonArr JsonArr::fromJsonStr(const QByteArray & text) { return Json::fromJsonStr(text).toArray(); }
JsonArr JsonArr::fromJsonStr(const QByteArray & text, QString & error) { return Json::fromJsonStr(text, error).toArray(); }
JsonArr JsonArr::fromJsonStr(const QString & text) { return Json::fromJsonStr(text).toArray(); }
JsonArr JsonArr::fromJsonStr(const QString & text, QString & error) { return Json::fromJsonStr(text, error).toArray(); }

QByteArray JsonArr::toJsonStr(const JsonFormat & format) { return operator Json().toJsonStr(format); }
QVariant JsonArr::toVariant() const { return operator Json().toVariant(); }

JsonArr::JsonArr() : QJsonArray() {}
JsonArr::JsonArr(const QJsonArray & oth_arr) : QJsonArray(oth_arr) {}
JsonArr & JsonArr::operator=(const QJsonArray & x) { QJsonArray::operator=(x); return *this; }

JsonArr::operator QJsonArray() const { return (QJsonArray)*this; }
JsonArr::operator Json() const { return Json(operator QJsonArray()); }

Json::Type JsonArr::type() const { return Json::Array; }

int JsonArr::size() { return QJsonArray::size(); }

QString JsonArr::concatKeys(const QString & key, const QString & separator) {
    QString cat_str;
    for(QJsonArray::Iterator item = begin(); item != end(); item++) {
        Json item_obj = *item;
        cat_str = cat_str % (cat_str.isEmpty() ? QString() : separator) % item_obj.string(key);
    }
    return cat_str;
}

QString JsonArr::concatKeys(const QString & separator) {
    QString cat_str;
    for(QJsonArray::Iterator item = begin(); item != end(); item++) {
        Json item_obj = *item;
        cat_str = cat_str % (cat_str.isEmpty() ? QString() : separator) % item_obj.forceString();
    }
    return cat_str;
}

Json JsonArr::operator[](const int & index) { return val(index); }
Json JsonArr::val(const int & index) { return this -> at(index); }


JsonArr JsonArr::arr() const { return *this; }
JsonArr JsonArr::arr(const int & index) { return val(index).toArray(); }
JsonArr JsonArr::arr(const int & index, const JsonArr & def_val) { return val(index).toArray(def_val); }

bool JsonArr::boolean(const int & index, const bool def_val) { return val(index).toBool(def_val); }

int JsonArr::integer(const int & index, const int def_val) { return val(index).toInt(def_val); }

qint64 JsonArr::bigInt(const int & index, const qint64 def_val) { return JOBJ_BINT(val(index), def_val); }

double JsonArr::rational(const int & index, const double def_val) { return val(index).toDouble(def_val); }

QString JsonArr::string(const int & index) { return val(index).toString(); }
QString JsonArr::stringDef(const int & index, const QString & def_val) { return val(index).toString(def_val); }

QString JsonArr::forceString(const int & index) { return J_STR(val(index)); }
QString JsonArr::forceStringDef(const int & index, const QString & def_val) { return J_STR_DEF(val(index), def_val); }
