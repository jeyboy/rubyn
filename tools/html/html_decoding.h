#ifndef HTML_DECODING
#define HTML_DECODING

#include <qhash.h>

#include "unicode.h"

namespace Html {
    class Decoding {
    public:
        enum CharsetType {
            charset_utf8 = 0,
            charset_ascii = 1,
            charset_cp1251 = 2,
            charset_ansi = 4, // cp1252 // ISO-8859-1

            charset_max = 8,
        };

        enum DecodingFlags {
            decode_none = 0,
            decode_content = charset_max * 2,
            decode_mnemo = decode_content * 2
        };

        static QHash<QByteArray, int> html_entities;

        static CharsetType charsetType(const QByteArray & val);

        static QByteArray & decodeMnemonics(QByteArray & val);
        static QByteArray & decodeContent(const CharsetType & charset, QByteArray & val);
        static QByteArray & decodeUrl(QByteArray & url, QByteArray * base_url = 0);
    };
}

#endif // HTML_DECODING
