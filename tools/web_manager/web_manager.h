#ifndef WEB_MANAGER_H
#define WEB_MANAGER_H

//#include <QtNetwork>

#include "qnetworkaccessmanager.h"
#include "misc/variant_ptr.h"

#include "web_request_params.h"
#include "web_request.h"
#include "web_response.h"
#include "web_proxy.h"

#define MANAGER_PROPERTY_NAME "settings"
//#define SERIALIZE_JSON(json) (json.isArray() ? QJsonDocument(json.toArray()) : QJsonDocument(json.toObject())).toJson(QJsonDocument::Compact)
#define ERROR_OUTPUT(source) qCritical() << "IOERROR" << source -> error() << source -> url();

namespace Web {
    class ManagerController;

    class Manager : public QNetworkAccessManager {
        Q_OBJECT

        QSsl::SslProtocol protocol;
        QSslSocket::PeerVerifyMode mode;

        static QThread * main_thread;
        static Cookies default_cookies;
        static QHash<QObject *, Manager *> managers;

        friend class ManagerController;

        enum requestType {
            rt_custom = 0,
            rt_head,
            rt_get,
            rt_delete,
            rt_post,
            rt_put
        };
    protected:
        Manager(QObject * parent = 0, QSsl::SslProtocol protocol = QSsl::TlsV1_3OrLater, QSslSocket::PeerVerifyMode mode = QSslSocket::VerifyNone);
        QNetworkReply * createRequest(Operation op, const QNetworkRequest & req, QIODevice * outgoingData = 0);

        Response * setupCallback(QNetworkReply * m_http, RequestParams * params);
        Response * proceed(QNetworkReply * m_http, RequestParams * params);
        Response * synchronizeRequest(QNetworkReply * m_http);
        void setup(const requestType & rtype, const Request & request, RequestParams * params);
        Response * sendSimple(const requestType & rtype, RequestParams * params);
        Response * sendData(const requestType & rtype, RequestDataParams * params);
    public:
        void setCookieJar(Cookies * cookieJar) {
            QNetworkAccessManager::setCookieJar(cookieJar);
            cookieJar -> setParent(0);
        }

//        qApp -> thread()
        static void setMainThreadSync(QThread * main) { main_thread = main; }

        static Manager * prepare();

        static Response * procHead(const QUrl & url, const bool & async = false) { return procHead(RequestParams::buildDefaultParams(url, async)); }
        static Response * procGet(const QUrl & url, const bool & async = false) { return procGet(RequestParams::buildDefaultParams(url, async)); }
        static Response * procDelete(const QUrl & url, const bool & async = false) { return procDelete(RequestParams::buildDefaultParams(url, async)); }

        static Response * procHead(RequestParams * params) { return prepare() -> sendSimple(rt_head, params); }
        static Response * procGet(RequestParams * params) { return prepare() -> sendSimple(rt_get, params); }
        static Response * procDelete(RequestParams * params) { return prepare() -> sendSimple(rt_delete, params); }

        static Response * procPost(RequestDataParams * params) { return prepare() -> sendData(rt_post, params); }
        static Response * procPut(RequestDataParams * params) { return prepare() -> sendData(rt_put, params); }
//       static Response * procCustom(RequestDataParams * params) { return prepare() -> sendSimple(rt_custom, params); }
    public slots:
//        inline void sendGet(const QString & url) { getFollowed(url) -> deleteLater(); }

        Response * sendHead(RequestParams * params) { return sendSimple(rt_head, params); }
        Response * sendGet(RequestParams * params) { return sendSimple(rt_get, params); }
        Response * sendDelete(RequestParams * params) { return sendSimple(rt_delete, params); }

        Response * sendPost(RequestDataParams * params) { return sendSimple(rt_post, params); }
        Response * sendPut(RequestDataParams * params) { return sendSimple(rt_put, params); }
//        Response * sendCustom(RequestParams * params) { return sendSimple(rt_custom, params); }

    protected slots:
        void requestFinished();

    signals:
        void requestCompleted(Response *);
    };

    class ManagerController : public QObject {
        Q_OBJECT
    protected slots:
        inline void disconnectThread() {
            qDebug() << "!!!!!!!!!!!!!!!!!!!! UNREGISTRATE MANAGER";
            Manager * tmanager = Manager::managers.take(sender());

//            // INFO: if last manager is closed then we removing all static data
//            if (Manager::managers.isEmpty()) {
//                Manager::default_cookies -> deleteLater();
//            }

            if (tmanager) tmanager -> deleteLater();
            deleteLater();
        }
    };
}

#endif // WEB_MANAGER_H
