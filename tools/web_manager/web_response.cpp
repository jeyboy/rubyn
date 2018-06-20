#include "web_response.h"

#include "web_manager.h"

#include <qtextcodec.h>

using namespace Web;

QHash<QByteArray, Response::ResponseType> Response::response_predefined_types = {
    {QByteArrayLiteral("text/html"), Response::rt_html },
    {QByteArrayLiteral("application/javascript"), Response::rt_js },
    {QByteArrayLiteral("application/json"), Response::rt_json }
};

Response * Response::fromReply(QNetworkReply * reply) {
    return reinterpret_cast<Response *>(reply);
}

void Response::initInfoFromContentHeader() {
    QByteArray content_type = header(QNetworkRequest::ContentTypeHeader).toByteArray();
    QList<QByteArray> type_parts = content_type.split(';');

    qDebug() << type_parts;

    setProperty(
        RESPONSE_TYPE_PROPERTY,
        response_predefined_types.contains(type_parts[0]) ? response_predefined_types[type_parts[0]] : rt_unknown
    );

    if (type_parts.length() == 1) {
        setProperty(RESPONSE_ENCODING_PROPERTY, DEFAULT_ENCODING);
    } else {
        QList<QByteArray> parts;
        Utils::split(type_parts.last(), QByteArrayLiteral("charset="), parts);

        setProperty(RESPONSE_ENCODING_PROPERTY, parts.length() == 1 ? DEFAULT_ENCODING : parts.last());
    }
}

Response::ResponseType Response::reponseType() {
    int res = property(RESPONSE_TYPE_PROPERTY).toInt();
    if (res == rt_none) {
        initInfoFromContentHeader();
        res = property(RESPONSE_TYPE_PROPERTY).toInt();
    }
    return (ResponseType)res;
}
QByteArray Response::encoding() {
    QByteArray res = property(RESPONSE_ENCODING_PROPERTY).toByteArray();
    if (res.isEmpty()) {
        initInfoFromContentHeader();
        res = property(RESPONSE_ENCODING_PROPERTY).toByteArray();
    }
    return res;
}

//QByteArray Response::encoding() {
//    QByteArray content_type = header(QNetworkRequest::ContentTypeHeader).toByteArray();
//    QList<QByteArray> type_parts = content_type.split(';');

//    qDebug() << type_parts;

////    rtype = response_predefined_types.contains(type_parts[0]) ? response_predefined_types[type_parts[0]] : rt_unknown;

//    if (type_parts.length() == 1) {
//        return DEFAULT_ENCODING;
//    } else {
//        QList<QByteArray> parts;
//        Utils::split(type_parts.last(), QByteArrayLiteral("charset="), parts);

//        if (parts.length() == 1)
//            return DEFAULT_ENCODING;
//        else
//            return parts.last();
//    }
//}

Response * Response::print() {
    qDebug() << "-------------------------";
    qDebug() << "URL:" << toUrl(false);
    qDebug() << "REDIRECT URL:" << toRedirectUrl(false);
    qDebug() << "HEADERS:" << rawHeaderPairs();
    qDebug() << "-------------------------";

    return this;
}

void Response::printHeaders() {
    QList<RawHeaderPair> headers = rawHeaderPairs();

    qDebug() << "------------ HEADERS LIST ----------------";

    for(QList<RawHeaderPair>::ConstIterator it = headers.cbegin(); it != headers.cend(); it++)
        qDebug() << (*it).first << (*it).second;

    qDebug() << "------------ END OF LIST ----------------";
}

QUrl Response::redirectUrl() {
    QVariant possibleRedirectUrl = attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (possibleRedirectUrl.isValid()) {
        QUrl new_url = possibleRedirectUrl.toUrl();

        if (new_url.isRelative())
            new_url = url().resolved(new_url);

        return new_url;

    } else return QUrl();
}

Response * Response::followByRedirect(QHash<QUrl, bool> prev_urls) {
    QUrl new_url = redirectUrl();

    if (!new_url.isEmpty()) {
        if (prev_urls.contains(new_url)) return this;
        else prev_urls.insert(new_url, true);

        RequestParams * params = VariantPtr<RequestParams>::asPtr(
            property(MANAGER_PROPERTY_NAME)
        );

        RequestParams * current_params = RequestParams::buildRedirectParams(
            new_url,
            params,
            new Headers({ {QByteArrayLiteral("Referer"), url().toString().toUtf8() } }) // source -> request().rawHeader("Referer")
        );

        deleteLater();
        return ((Manager *)manager()) -> sendGet(current_params);
    }


    return this;
}

Cookies * Response::cookies() {
    return Cookies::fromJar(manager() -> cookieJar());
}

QUrlQuery Response::toQuery(const bool & destroy) {
    QByteArray ar = readAll();
    if (destroy) deleteLater();
    return QUrlQuery(QUrl::fromPercentEncoding(ar));
}

QByteArray Response::toBytes(const bool & destroy) {
    QByteArray ar = readAll();
    printHeaders();
    if (destroy) deleteLater();
    return ar;
}

QString Response::toText(const bool & destroy) {
    QByteArray ar = readAll();
    QByteArray enc = encoding();
    qDebug() << "ENC" << enc;
    QTextCodec * codec = QTextCodec::codecForName(enc);

    if (destroy) deleteLater();

    return codec -> toUnicode(ar);
}
Json Response::toJson(const QString & wrap, const bool & destroy) { //TODO: enc not used yet
    QByteArray ar = readAll();

    ResponseType rtype = reponseType();

    if (rtype == rt_json || rtype == rt_js) {
//       ar.replace('\'', '"'); // ' wraps responds to errors on parsing // need to replace ' with "
        if (!wrap.isEmpty()) { ar.prepend(USTR("{\"%1\":").arg(wrap).toUtf8()); ar.append("}"); }
        if (destroy) deleteLater();

        QString err;
        Json res = Json::fromJsonStr(ar, err);
        if (err.isEmpty()) return res;
        qCritical() << "JSON PARSING ERR" << err;
    }

    qCritical() << "NOT JSON" << rawHeader("Content-Type");
    return QJsonObject {{JSON_ERR_FIELD, QString(ar)}};
}

QImage Response::toImage(const bool & destroy) {
    QByteArray data = readAll();
    if (destroy) deleteLater();

    QImage img = QImage::fromData(data);

    if (img.isNull()) {
        QByteArray ext_bytes = Utils::extractExtension(url());

        if (ext_bytes.isEmpty())
            ext_bytes = QByteArrayLiteral("PNG");

        return QImage::fromData(data, ext_bytes.constData());
    }

    return img;
}

//    INFO: this working only in GUI thread
QPixmap Response::toPixmap(const bool & destroy) {
    QByteArray data = readAll();
    if (destroy) deleteLater();

    QPixmap image;
    image.loadFromData(data);
    return image;
}

QUrl Response::toUrl(const bool & destroy) {
    QUrl uri = url();
    if (destroy) deleteLater();
    return uri;
}

Html::Page Response::toHtml(const bool & destroy) {
    QByteArray enc = encoding();
    Html::Page doc(this, Html::Decoding::charsetType(enc));
    if (destroy) deleteLater();
    return doc;
}

QUrl Response::toRedirectUrl(const bool & destroy) {
    QUrl uri = redirectUrl();
    if (destroy) deleteLater();
    return uri;
}

QByteArray Response::toHeader(const QByteArray & header_field, const bool &  destroy) {
    if (destroy) deleteLater();

    if (hasRawHeader(header_field))
        return rawHeader(header_field);

    return QByteArray();
}

