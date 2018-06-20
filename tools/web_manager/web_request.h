#ifndef WEB_REQUEST_H
#define WEB_REQUEST_H

#include "web_manager_global.h"

#include "qnetworkrequest.h"

namespace Web {
    class RequestParams;

    class Request : public QNetworkRequest {
    public:
        Request(RequestParams * params);

        QByteArray headersStr() const;
    };
}

#endif // WEB_REQUEST_H
