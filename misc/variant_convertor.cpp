#include "variant_convertor.h"

#include <qvariant.h>
#include <qdatetime.h>
#include <qurl.h>

QString VariantConvertor::toStr(const QVariant & data) {
    QString res;

    switch(data.type()) {
        case QVariant::Int: { res = QString::number(data.toInt()); break;}
        case QVariant::UInt: { res = QString::number(data.toUInt()); break;}
        case QVariant::LongLong: { res = QString::number(data.toLongLong()); break;}
        case QVariant::ULongLong: { res = QString::number(data.toULongLong()); break;}
        case QVariant::Double: { res = QString::number(data.toDouble()); break;}

        case QVariant::Map: {
                QVariantMap map = data.toMap();
                for(QVariantMap::Iterator entry = map.begin(); entry != map.end(); entry++)
                    res = res % LSTR(", ") % '"' % entry.key() % '"' % ':' % toStr(entry.value());

                res = '{' % res.mid(2) % '}';

            break;}
        case QVariant::List: {
                QVariantList map = data.toList();
                for(QVariantList::Iterator entry = map.begin(); entry != map.end(); entry++)
                    res += LSTR(", ") % toStr(*entry);

                res = '[' % res.mid(2) % ']';

            break;}
        case QVariant::StringList: {
                QStringList map = data.toStringList();
                for(QStringList::Iterator entry = map.begin(); entry != map.end(); entry++)
                    res += LSTR(", ") % '"' % (*entry) % '"';

                res = '[' % res.mid(2) % ']';

            break;}
        case QVariant::Hash: {
                QVariantHash map = data.toHash();
                for(QVariantHash::Iterator entry = map.begin(); entry != map.end(); entry++)
                    res += LSTR(", ") % '"' % entry.key() % '"' % ':' % toStr(entry.value());

                res = '{' % res.mid(2) % '}';

            break;}


        case QVariant::Url: { res = '"' % data.toUrl().toString() % '"'; break;}
        case QVariant::Date: { res = '"' % data.toDate().toString() % '"'; break;}
        case QVariant::Time: { res = '"' % data.toTime().toString() % '"'; break;}
        case QVariant::DateTime: { res = '"' % data.toDateTime().toString() % '"'; break;}


        case QVariant::Bool: { res = data.toBool() ? LSTR("true") : LSTR("false"); break;}
        case QVariant::Char: { res = '\'' % data.toChar() % '\''; break;}
        default: res = '"' % data.toString() % '"';
    }

    return res;
}
