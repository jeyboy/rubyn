#ifndef WEB_HEADERS
#define WEB_HEADERS

#include "web_manager_global.h"

#include <qhash.h>
#include <qregularexpression.h>

namespace Web {
    class Headers : public QHash<QByteArray, QByteArray> {
    public:
        static inline Headers extract(const QString & url) {
            QStringList heads = url.split(QRegularExpression(LSTR("%0D%0A|\\r\\n")), QString::SkipEmptyParts);
            Headers res;
            if (heads.size() > 1) {
                const_cast<QString &>(url) = heads.takeFirst();

                while(!heads.isEmpty()) {
                    QStringList parts = heads.takeLast().split(LSTR(": "), QString::SkipEmptyParts);
                    res.insert(parts.first().toUtf8(), parts.last().toUtf8());
                }
            }

            return res;
        }
        static inline Headers extract(const QUrl & url) {
            QString urlStr = url.toString();
            Headers headers = Headers::extract(urlStr);
            if (!headers.isEmpty()) const_cast<QUrl &>(url) = QUrl(urlStr);
            return headers;
        }

        inline Headers() : QHash<QByteArray, QByteArray>() {}
        #ifdef Q_COMPILER_INITIALIZER_LISTS
            inline Headers(std::initializer_list<std::pair<QByteArray, QByteArray> > list) : QHash<QByteArray, QByteArray>(list) {}
        #endif

        inline Headers(QHash<QByteArray, QByteArray> & hsh) {
            for(QHash<QByteArray, QByteArray>::ConstIterator it = hsh.constBegin(); it != hsh.constEnd(); it++)
                insert(it.key(), it.value());
        }

        Headers & unite(const Headers & other) {
            return (Headers &) QHash<QByteArray, QByteArray>::unite((QHash<QByteArray, QByteArray>)other);
        }
    };
}

#endif // WEB_HEADERS
