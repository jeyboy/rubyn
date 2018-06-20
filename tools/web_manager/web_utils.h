#ifndef WEB_UTILS_H
#define WEB_UTILS_H

#include <qurl.h>
#include <qurlquery.h>

#include "web_manager_global.h"

namespace Web {
    class Utils {
    public:
        static inline QString paramVal(const QUrl & url, const QString & param) { return QUrlQuery(url).queryItemValue(param); }
        static QByteArray extractParams(QUrl & url) {
            QByteArray params = url.query().toUtf8();
            url.setQuery(QString());
            return params;
        }

        static QByteArray extractExtension(const QUrl & url) {
            QString uri = url.toString();

            QString ext = uri.section('.', -1, -1);

            if (ext != uri && ext.indexOf(' ') == -1)
                return ext.toUtf8();
            else return QByteArray();
        }

        static void split(const QByteArray & val, const QByteArray & predicate, QList<QByteArray> & res) {
            const char * iter = val.constData();
            const char * predicate_iter = predicate.constData();
            const char * sub_iter, * predicate_sub_iter, * fix_iter = iter;

            while(*iter) {
                if (*iter == *predicate_iter) {
                    sub_iter = iter + 1;
                    predicate_sub_iter = predicate_iter + 1;

                    while(true) {
                        if (*sub_iter == 0) {
                            if (*predicate_sub_iter == 0) {
                                res.append(QByteArray(iter));
                                return;
                            }

                            break;
                        } else {
                            if (*predicate_sub_iter == 0) {
                                res.append(QByteArray(iter, sub_iter - iter));
                                fix_iter = iter = sub_iter;

                                break;
                            }

                            if (*predicate_sub_iter != *sub_iter)
                                break;
                        }

                        sub_iter++;
                        predicate_sub_iter++;
                    }
                }

                iter++;
            }

            if (*fix_iter)
                res.append(QByteArray(fix_iter));
        }
    };
}

#endif // WEB_UTILS_H
