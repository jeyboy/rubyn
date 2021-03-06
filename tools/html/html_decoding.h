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
            decode_mnemo = decode_content * 2,
            simplify_needed = decode_mnemo * 2
        };

        static QHash<QByteArray, uint> html_entities;
        static QHash<uint, QByteArray> simplifications;

        static CharsetType charsetType(const QByteArray & val);

//        static QString & simplify(QString & str);

        static QByteArray & decodeMnemonics(QByteArray & val, const bool & simplify = false);
        static QByteArray & decodeContent(const CharsetType & charset, QByteArray & val);
        static QByteArray & decodeUrl(QByteArray & url, QByteArray * base_url = 0);
    };
}

#endif // HTML_DECODING
