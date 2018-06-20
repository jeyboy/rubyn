#ifndef WEB_PROXY_H
#define WEB_PROXY_H

#include "web_manager_global.h"

#include "qnetworkproxy.h"

namespace Web {
    class Proxy : public QNetworkProxy {
        QByteArray country;
        float response_time;
        float response_rate;
        bool encrypted;

        static QHash<QLatin1String, bool> blacklisted;
    public:
        enum ManagerProxyType {
            pt_unsupported = -2,
            pt_any = -1,

            pt_none = 0,

            pt_system = 1,
            pt_tor = 1 << 1,

            pt_ssl = 1 << 2,

            pt_http = 1 << 3,
            pt_https = 1 << 4 | pt_ssl,
            pt_socks5 = 1 << 5,
            pt_socks5s = 1 << 6 | pt_ssl,
        };

        Proxy(const ManagerProxyType & ptype = pt_system, const QString & hostName = QString(),
            quint16 port = 0, const QByteArray & country = QByteArray(),
            const float & response_time = 0, const float & response_rate = 0,
            const QString & user = QString(), const QString & password = QString()) :
                QNetworkProxy(HttpProxy, hostName, port, user, password), country(country),
                response_time(response_time), response_rate(response_rate), encrypted(ptype == pt_https || ptype == pt_socks5s) {}

        static Proxy * find(const ManagerProxyType & ptype = pt_any, const QByteArray & country = QByteArray());

    private:
        static QHash<QString, ManagerProxyType> type_mapping;

        static ManagerProxyType strToType(const QString & str) {
            return type_mapping.value(str.toLower(), pt_unsupported);
        }

        static Proxy * findinSource1(const ManagerProxyType & ptype = pt_any, const QByteArray & country = QByteArray());
        static Proxy * findinSource2(const ManagerProxyType & ptype = pt_any, const QByteArray & country = QByteArray());
        static Proxy * findinSource3(const ManagerProxyType & ptype = pt_any, const QByteArray & country = QByteArray());
//        static Proxy * findinSource5(const ManagerProxyType & ptype = pt_any, const QByteArray & country = QByteArray());
    };
}

#endif // WEB_PROXY_H
