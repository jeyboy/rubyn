#include "web_cookies.h"

using namespace Web;

Cookies * Cookies::fromJar(QNetworkCookieJar * jar) {
    return reinterpret_cast<Cookies *>(jar);
}

Cookies * Cookies::loadCookies(const QJsonObject & store) {
    Cookies * cookies = new Cookies();

    QJsonArray arr = store.value(COOKIES_KEY).toArray();
    for(QJsonValue const & cookie: arr) {
        QList<QNetworkCookie> items = QNetworkCookie::parseCookies(cookie.toString().toUtf8());
        for(QNetworkCookie & item: items)
            cookies -> insertCookie(item);
    }

    return cookies;
}

void Cookies::saveCookies(QJsonObject & store, const QUrl & url) {
    QList<QNetworkCookie> cookiesList = url.isEmpty() ? allCookies() : cookiesForUrl(url);
    QJsonArray cookiesArray;
    for(auto const & cookie: cookiesList)
        cookiesArray << QJsonValue(QString(cookie.toRawForm()));

    store.insert(COOKIES_KEY, cookiesArray);
}

void Cookies::appendCookie(const QByteArray & cookies_data) {
    QList<QNetworkCookie> items = QNetworkCookie::parseCookies(cookies_data);
    for(QNetworkCookie & item: items)
        insertCookie(item);
}

void Cookies::removeCookies(const QUrl & url) {
    const QList<QNetworkCookie> items = url.isEmpty() ? allCookies() : cookiesForUrl(url);
    for(QList<QNetworkCookie>::ConstIterator cookie = items.cbegin(); cookie != items.cend(); cookie++)
        deleteCookie(*cookie);
}

void Cookies::print(const QUrl & url) {
//                qDebug() << "COOKIE" << cookies -> allCookies();

    qDebug() << " ----------------------- COOKIES LIST ----------------------------";

    const QList<QNetworkCookie> items = url.isEmpty() ? allCookies() : cookiesForUrl(url);
    for(QList<QNetworkCookie>::ConstIterator cookie = items.cbegin(); cookie != items.cend(); cookie++)
        qDebug() << (*cookie).toRawForm();

    qDebug() << " -----------------------------------------------------------------";
}

QByteArray Cookies::asHeaderStr(const QUrl & url, const QHash<QByteArray, bool> & acceptable) {
    QByteArray res;
    bool ignore_filter = acceptable.isEmpty();

    const QList<QNetworkCookie> items = url.isEmpty() ? allCookies() : cookiesForUrl(url);
    for(QList<QNetworkCookie>::ConstIterator cookie = items.cbegin(); cookie != items.cend(); cookie++) {
        QByteArray name = (*cookie).name();
        if (ignore_filter || acceptable.contains(name))
            res = res + name + '=' + (*cookie).value() + ';' + ' ';
    }

    return QByteArrayLiteral("Cookie: ") + res;
}
QByteArray Cookies::cookie(const QByteArray & name, const QUrl & url) {
    const QList<QNetworkCookie> items = url.isEmpty() ? allCookies() : cookiesForUrl(url);
    for(QList<QNetworkCookie>::ConstIterator cookie = items.cbegin(); cookie != items.cend(); cookie++)
        if ((*cookie).name() == name)
            return (*cookie).value();

    return QByteArray();
}
