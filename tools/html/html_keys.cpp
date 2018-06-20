#include "html_keys.h"

namespace Html {
//    extern const char tkn_split                    = ' ';
    extern const QByteArray tkn_any_elem           = HTML_ANY_TAG;
    extern const QByteArray tkn_text_block         = HTML_TEXT_BLOCK;
    extern const QByteArray tkn_comment_block      = QByteArrayLiteral("comment");

    extern const QByteArray tkn_charset            = QByteArrayLiteral("charset");
    extern const QByteArray tkn_encoding           = QByteArrayLiteral("encoding");
    extern const QByteArray tkn_charset_attr       = QByteArrayLiteral("charset=");
    extern const QByteArray tkn_http_equiv         = QByteArrayLiteral("http-equiv");
    extern const QByteArray tkn_content_type       = QByteArrayLiteral("content-type");
    extern const QByteArray tkn_content            = QByteArrayLiteral("content");


    extern const QByteArray tkn_scdata             = QByteArrayLiteral("![CDATA[");
    extern const QByteArray tkn_ecdata             = QByteArrayLiteral("]]>");

    extern const QByteArray attr_name              = QByteArrayLiteral("name");
    extern const QByteArray attr_action            = QByteArrayLiteral("action");
    extern const QByteArray attr_href              = QByteArrayLiteral("href");
    extern const QByteArray attr_src               = QByteArrayLiteral("src");
    extern const QByteArray attr_id                = QByteArrayLiteral("id");
    extern const QByteArray attr_class             = QByteArrayLiteral("class");
    extern const QByteArray attr_type              = HTML_ATTR_TYPE;
    extern const QByteArray attr_default           = QByteArrayLiteral("value");
    extern const QByteArray attr_checked           = QByteArrayLiteral("checked");
    extern const QByteArray attr_disabled          = QByteArrayLiteral("disabled");


    extern const QByteArray type_radio             = QByteArrayLiteral("radio");
    extern const QByteArray type_checkbox          = QByteArrayLiteral("checkbox");
}
