#ifndef WEB_HEADERS
#define WEB_HEADERS

#include "web_manager_global.h"

#include <qhash.h>
#include <qregularexpression.h>
#include <qurl.h>

namespace Web {
    class Headers : public QMultiHash<QByteArray, QByteArray> {
    public:
        static inline Headers extract(const QString & url) {
            QStringList heads = url.split(QRegularExpression(LSTR("%0D%0A|\\r\\n")), Qt::SkipEmptyParts);
            Headers res;
            if (heads.size() > 1) {
                const_cast<QString &>(url) = heads.takeFirst();

                while(!heads.isEmpty()) {
                    QStringList parts = heads.takeLast().split(LSTR(": "), Qt::SkipEmptyParts);
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

        inline Headers() : QMultiHash<QByteArray, QByteArray>() {}
        #ifdef Q_COMPILER_INITIALIZER_LISTS
            inline Headers(std::initializer_list<std::pair<QByteArray, QByteArray> > list) : QMultiHash<QByteArray, QByteArray>(list) {}
        #endif

        inline Headers(QMultiHash<QByteArray, QByteArray> & hsh) {
            for(QMultiHash<QByteArray, QByteArray>::ConstIterator it = hsh.constBegin(); it != hsh.constEnd(); it++)
                insert(it.key(), it.value());
        }

        Headers & unite(const Headers & other) {
            return (Headers &) QMultiHash<QByteArray, QByteArray>::unite((QMultiHash<QByteArray, QByteArray>)other);
        }
    };
}

#endif // WEB_HEADERS
