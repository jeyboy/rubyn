#ifndef COUNTRY_H
#define COUNTRY_H

#include <qhash.h>

//#include <qjsondocument.h>
//#include <qjsonarray.h>
//#include <qjsonobject.h>

//#include <qtextstream.h>
//#include <qfile.h>
//#include <qapplication.h>

#include "singleton.h"

struct CountryCell {
    QByteArray name;
    QByteArray second_name;
    QByteArray name2letters;
    QByteArray name3letters;
    QList<QByteArray> borders;
};

class Country : public Singleton<Country> {
    QHash<QByteArray, CountryCell *> list;

    friend class Singleton<Country>;

    Country();
    ~Country() {
        for(QHash<QByteArray, CountryCell *>::Iterator it = list.begin(); it != list.end(); it++) {
            CountryCell * cell = it.value();

            if (cell) {
                list[cell -> name] = 0;
                list[cell -> second_name] = 0;
                list[cell -> name2letters] = 0;
                list[cell -> name3letters] = 0;

                delete cell;
            }
        }

        list.clear();
    }

    void init();
public:
    CountryCell * find(const QByteArray & name) {
        return list[name];
    }

//    bool convert() {
//        QFile f(USTR("F:\\countries.json"));

//        if (f.open(QFile::ReadOnly)) {
//            QJsonArray ar = QJsonDocument::fromJson(f.readAll()).array();

//            QFile fo(USTR("F:\\countries.txt"));

//            if (fo.open(QFile::WriteOnly | QFile::Truncate)) {
//                QTextStream ts(&fo);

//                ts << QByteArrayLiteral("CountryCell * cell;");

//                for(QJsonArray::Iterator it = ar.begin(); it != ar.end(); it++) {
//                    QJsonObject ob = (*it).toObject();

//                    QString cl2 = ob.value(QLatin1String("cca2")).toString();
//                    QString cl3 = ob.value(QLatin1String("cca3")).toString();
//                    QJsonObject names = ob.value(QLatin1String("name")).toObject();
//                    QString name1 = names.value(QLatin1String("common")).toString();
//                    QString name2 = names.value(QLatin1String("official")).toString();

//                    QJsonArray borders = ob.value(LSTR("borders")).toArray();
//                    QByteArray borders_list;
//                    for(QJsonArray::Iterator bord = borders.begin(); bord != borders.end(); bord++) {
//                        QString border = (*bord).toString();

//                        borders_list.append(QByteArrayLiteral(", \"")).append(border).append('"');
//                    }

//                    ts << QByteArrayLiteral("cell = new CountryCell {QByteArrayLiteral(\"") +
//                          name2 +
//                          QByteArrayLiteral("\"), QByteArrayLiteral(\"") +
//                          name1 +
//                          QByteArrayLiteral("\"), QByteArrayLiteral(\"") +
//                          cl2 +
//                          QByteArrayLiteral("\"), QByteArrayLiteral(\"") +
//                          cl3 +
//                          QByteArrayLiteral("\"), {") +
//                          borders_list.mid(2) +
//                          QByteArrayLiteral("}};\r\n");

//                    ts << QByteArrayLiteral("list.insert(QByteArrayLiteral(\"") + cl2 + QByteArrayLiteral("\"), cell);\r\n");
//                    ts << QByteArrayLiteral("list.insert(QByteArrayLiteral(\"") + cl3 + QByteArrayLiteral("\"), cell);\r\n");
//                    if (name1 != name2)
//                        ts << QByteArrayLiteral("list.insert(QByteArrayLiteral(\"") + name2 + QByteArrayLiteral("\"), cell);\r\n");
//                    ts << QByteArrayLiteral("list.insert(QByteArrayLiteral(\"") + name1 + QByteArrayLiteral("\"), cell);\r\n\r\n");
//                }

//                fo.close();
//                return true;
//            }

//            f.close();
//            return false;
//        }

//        return false;
//    }
};

#endif // COUNTRY_H
