#ifndef WEB_REQUEST_PARAMS_H
#define WEB_REQUEST_PARAMS_H

#include <qurl.h>

#include "misc/func.h"
#include "misc/variant_convertor.h"

#include "web_manager_global.h"
#include "web_headers.h"
#include "web_cookies.h"
#include "web_utils.h"

//#define USER_AGENT_HEADER_NAME QByteArrayLiteral("User-Agent")
#define FORM_URLENCODE QByteArrayLiteral("application/x-www-form-urlencoded")
#ifdef Q_OS_WIN
    #define DEFAULT_AGENT QByteArrayLiteral("Mozilla/5.0 (Windows NT 6.1; WOW64; rv:48.0) Gecko/20100101 Firefox/48.0")
#elif Q_OS_MAC // there should be agent for mac
    #define DEFAULT_AGENT QByteArrayLiteral("Mozilla/5.0 (X11; Ubuntu; Linux i686; rv:43.0) Gecko/20100101 Firefox/50.0")
#else
    #define DEFAULT_AGENT QByteArrayLiteral("Mozilla/5.0 (X11; Ubuntu; Linux i686; rv:43.0) Gecko/20100101 Firefox/50.0")
#endif

#define RPF(vals) (RequestParams::RequestParamsFlags)(vals)
#define DEFAULT_REQUEST_PARAMS RPF(RequestParams::rp_destroy_headers | RequestParams::rp_destroy_callback | RequestParams::rp_follow)
#define DEFAULT_FORM_REQUEST_PARAMS RPF(RequestParams::rp_extract_params_to_payload | DEFAULT_REQUEST_PARAMS)

namespace Web {
    struct RequestParams {
        enum RequestParamsFlags : int {
            rp_none = 0,
            rp_follow = 1,
            rp_async = 1 << 1,
            rp_attach_agent = 1 << 2,
            rp_extract_params_to_payload = 1 << 3,
            rp_print_params = 1 << 4,
            rp_has_payload = 1 << 5,

            // destroy params after request

            rp_destroy_headers = 1 << 6,
            rp_destroy_callback = 1 << 7,
            rp_destroy_cookies = 1 << 8,

            rp_destroy = rp_destroy_headers | rp_destroy_callback | rp_destroy_cookies
        };

        QUrl url;
        RequestParamsFlags rparams;
        Headers * headers;
        Cookies * cookies;
        Func * callback;

        RequestParams(const QUrl & url, Headers * headers = 0, Cookies * cookies = 0,
            Func * callback = 0, const RequestParamsFlags & rparams = DEFAULT_REQUEST_PARAMS) : url(url),
                 rparams(rparams), headers(headers), cookies(cookies), callback(callback) { prepare(); }


        static RequestParams * buildDefaultParams(const QUrl & new_url, const bool & async) {
            return new RequestParams(
                new_url,
                0,
                0,
                0,
                RPF(DEFAULT_REQUEST_PARAMS | rp_destroy | (async ? rp_async : rp_none))
            );
        }

        static RequestParams * buildRedirectParams(const QUrl & new_url, RequestParams * prev_params, Headers * headers = 0) {
            Func * prev_callback = prev_params -> callback; prev_params -> callback = 0;
            Cookies * cookies = prev_params -> cookies;

            prev_params -> erase();

            return new RequestParams(
                new_url,
                headers,
                cookies,
                prev_callback,
                RPF(rp_follow | (prev_params -> rparams & rp_async))
            );
        }

        void attachParam(const QString & name, const QVariant & val) {
            QUrlQuery query = QUrlQuery(url.query());
            query.addQueryItem(name, VariantConvertor::toStr(val));
            url.setQuery(query);
        }

        void attachParams(const std::initializer_list<std::pair<QString, QVariant> > & params) {
            QUrlQuery query = QUrlQuery(url.query());

            for (typename std::initializer_list<std::pair<QString, QVariant> >::const_iterator it = params.begin(); it != params.end(); ++it) {
                query.addQueryItem(it -> first, VariantConvertor::toStr(it -> second));
            }

            url.setQuery(query);
        }



        inline bool isAsync() { return rparams & rp_async; }
        inline bool isExtractParams() { return rparams & rp_extract_params_to_payload; }
        inline bool isPrintParams() { return rparams & rp_print_params; }
        inline bool isHasPayload() { return rparams & rp_has_payload; }
        inline bool isFollowed() { return rparams & rp_follow; }
        inline bool isHasCallback() { return callback != 0; }

        void prepare() {
            if (rparams & rp_attach_agent) {
                if (!headers)
                    headers = new Headers();

                headers -> insert(QByteArrayLiteral("User-Agent"), DEFAULT_AGENT);
            }

            if (isAsync() && !callback) {
                qWarning() << "Called async request without callback:" << url;
            }
        }

        void erase() {
            if (rparams & rp_destroy_headers)
                delete headers;

            if (rparams & rp_destroy_callback)
                delete callback;

            if (rparams & rp_destroy_cookies)
                delete cookies;
        }

//        void addHeader(const QByteArray & name, const QByteArray & val) {
//            if (!headers) headers = new Headers();

//            headers -> insert(name, val);
//        }
    };

    struct RequestDataParams : public RequestParams {
        QByteArray data;

//        static RequestDataParams & fromParams(RequestParams & params) { return reinterpret_cast<RequestDataParams &>(params); }

        RequestDataParams(const QUrl & url, const QByteArray & data = QByteArray(), Headers * headers = 0,
                Cookies * cookies = 0, Func * callback = 0, const QByteArray & content_type = FORM_URLENCODE,
                const RequestParamsFlags & rparams = DEFAULT_FORM_REQUEST_PARAMS) :
                RequestParams(url, headers, cookies, callback, RPF(rparams | rp_has_payload)), data(data) { prepare(content_type); }

        void prepare(const QByteArray & content_type) {
            bool has_content_type = !content_type.isEmpty();
            bool is_extract_params = isExtractParams();

            bool require_headers = has_content_type || is_extract_params;

            if (require_headers && !headers)
                headers = new Headers();

            if (has_content_type)
                headers -> insert(QByteArrayLiteral("Content-Type"), content_type);

            if (is_extract_params) {
                QByteArray payload = Utils::extractParams(url);

                if (!payload.isEmpty()) {
                    if(!data.isEmpty())
                        data += '&' + payload;
                    else data = payload;
                }
            }
        }
    };
}

#endif // WEB_REQUEST_PARAMS_H
