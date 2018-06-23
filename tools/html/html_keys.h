#ifndef HTML_PARSER_KEYS
#define HTML_PARSER_KEYS

#include "misc/defines.h"
//#include <qbytearray.h>

#define HTML_ANY_TAG QByteArrayLiteral("*")
#define HTML_TEXT_BLOCK QByteArrayLiteral("text")
#define HTML_NEWLINE_BLOCK QByteArrayLiteral("newline")
#define HTML_TAG_DOCTYPE QByteArrayLiteral("!doctype")
#define HTML_TAG_XML QByteArrayLiteral("?xml")
#define HTML_TAG_INPUT QByteArrayLiteral("input")
#define HTML_TAG_IMG QByteArrayLiteral("img")
#define HTML_TAG_BR QByteArrayLiteral("br")
#define HTML_TAG_BODY QByteArrayLiteral("body")
#define HTML_TAG_HEAD QByteArrayLiteral("head")
#define HTML_TAG_LINK QByteArrayLiteral("link")
#define HTML_TAG_A QByteArrayLiteral("a")
#define HTML_TAG_META QByteArrayLiteral("meta")
#define HTML_TAG_IFRAME QByteArrayLiteral("iframe")
#define HTML_TAG_SCRIPT QByteArrayLiteral("script")
#define HTML_TAG_STYLE QByteArrayLiteral("style")
#define HTML_TAG_SELECT QByteArrayLiteral("select")
#define HTML_TAG_TEXTAREA QByteArrayLiteral("textarea")

#define HTML_ATTR_TYPE QByteArrayLiteral("type")

namespace Html {
//    extern const char tkn_split;
    Q_DECL_EXPORT extern const QByteArray tkn_any_elem;
    Q_DECL_EXPORT extern const QByteArray tkn_text_block;
    Q_DECL_EXPORT extern const QByteArray tkn_newline_block;
    Q_DECL_EXPORT extern const QByteArray tkn_comment_block;

    Q_DECL_EXPORT extern const QByteArray tkn_charset;
    Q_DECL_EXPORT extern const QByteArray tkn_encoding;
    Q_DECL_EXPORT extern const QByteArray tkn_charset_attr;
    Q_DECL_EXPORT extern const QByteArray tkn_http_equiv;
    Q_DECL_EXPORT extern const QByteArray tkn_content_type;
    Q_DECL_EXPORT extern const QByteArray tkn_content;

    Q_DECL_EXPORT extern const QByteArray tkn_scdata;
    Q_DECL_EXPORT extern const QByteArray tkn_ecdata;

    Q_DECL_EXPORT extern const QByteArray attr_name;
    Q_DECL_EXPORT extern const QByteArray attr_action;
    Q_DECL_EXPORT extern const QByteArray attr_href;
    Q_DECL_EXPORT extern const QByteArray attr_src;
    Q_DECL_EXPORT extern const QByteArray attr_id;
    Q_DECL_EXPORT extern const QByteArray attr_class;
    Q_DECL_EXPORT extern const QByteArray attr_type;
    Q_DECL_EXPORT extern const QByteArray attr_default;
    Q_DECL_EXPORT extern const QByteArray attr_checked;
    Q_DECL_EXPORT extern const QByteArray attr_disabled;

    Q_DECL_EXPORT extern const QByteArray type_radio;
    Q_DECL_EXPORT extern const QByteArray type_checkbox;
}

#endif // HTML_PARSER_KEYS
