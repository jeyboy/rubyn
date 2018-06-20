#include "web_request.h"
#include "web_request_params.h"

using namespace Web;

Request::Request(RequestParams * params) : QNetworkRequest(params -> url) {
    if (params -> headers) {
        Headers * headers = params -> headers;
        for(Headers::ConstIterator header = headers -> cbegin(); header != headers -> cend(); header++)
            setRawHeader(header.key(), header.value());
    }
}

QByteArray Request::headersStr() const {
    QList<QByteArray> heads = rawHeaderList();
    QByteArray res;

    for(QList<QByteArray>::ConstIterator h = heads.cbegin(); h != heads.cend(); h++) {
        QByteArray val = rawHeader(*h);
        res += (*h) + ' ' + ':' + val + ';' + ' ';
    }

    return res;
}

//Response * Request::viaGet(bool async) { return manager -> get(*this, async); }

//Response * Request::viaPost(const QByteArray & data, const QString & content_type, bool async) {
//    QByteArray payload = data;

//    if (payload.isEmpty()) {
//        QUrl curl = url();
//        payload = manager -> isExtractParamsToPayload() ? extractParams(curl) : QByteArray();
//        setUrl(curl);
//    }

//    //            QUrl curl = url();
//    //            QByteArray payload = manager -> isExtractParamsToPayload() ? extractParams(curl) : QByteArray();
//    //            setUrl(curl);

//    //            if (!data.isEmpty()) {
//    //                if (!payload.isEmpty()) {
//    //                    payload = payload + '&' + data;
//    //                } else payload = data;
//    //            }

//    setHeader(QNetworkRequest::ContentTypeHeader, content_type);
//    return manager -> post(*this, payload, async);
//}

//Response * Request::viaPut(const QByteArray & data, const QString & content_type, bool async) {
//    QByteArray payload = data;

//    if (payload.isEmpty()) {
//        QUrl curl = url();
//        payload = manager -> isExtractParamsToPayload() ? extractParams(curl) : QByteArray();
//        setUrl(curl);
//    }

//    setHeader(QNetworkRequest::ContentTypeHeader, content_type);
//    return manager -> put(*this, payload, async);
//}

//Response * Request::viaForm(const QByteArray & data, bool async) { return viaPost(data, FORM_URLENCODE, async); }
