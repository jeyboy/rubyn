#ifndef WEB_COOKIES_H
#define WEB_COOKIES_H

#include "web_manager_global.h"

#include "qnetworkcookie.h"
#include "qnetworkcookiejar.h"


#include <qdebug.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

namespace Web {
    class Cookies : public QNetworkCookieJar {
    public:
        static Cookies * fromJar(QNetworkCookieJar * jar);

        static Cookies * loadCookies(const QJsonObject & store);

        void saveCookies(QJsonObject & store, const QUrl & url = QUrl());

        inline explicit Cookies(QObject * parent = 0) : QNetworkCookieJar(parent) {}
        inline QList<QNetworkCookie> allCookies() const { return QNetworkCookieJar::allCookies(); }

        void appendCookie(const QByteArray & cookies_data);
        void removeCookies(const QUrl & url = QUrl());

        void print(const QUrl & url = QUrl());

        QByteArray asHeaderStr(const QUrl & url = QUrl(), const QHash<QByteArray, bool> & acceptable = QHash<QByteArray, bool>());
        QByteArray cookie(const QByteArray & name, const QUrl & url = QUrl());
    };
}

#endif // WEB_COOKIES_H
