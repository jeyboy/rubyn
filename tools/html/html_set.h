#ifndef HTML_SET_H
#define HTML_SET_H

#include "html_global.h"

#include <qlist.h>

namespace Html {
    class Tag;
    class Selector;

    class Set : public QList<Tag *> {
        Set & find(const Selector * selector, Set & set, const bool & find_first = false) const;
        friend class Tag;
    public:
        QByteArray link();
        QByteArray text();
        QByteArray value(const QByteArray & name = attr_default);

        inline Set find(const Selector * selector, const bool & find_first = false) const {
            Set set;
            return find(selector, set, find_first);
        }
        Set find(const char * predicate, const bool & find_first) const;
        inline Tag * findFirst(const char * predicate) const {
            Set set = find(predicate, true);
            return set.isEmpty() ? 0 : set.first();
        }
        inline Tag * findFirst(const Selector * selector) const {
            Set set = find(selector, true);
            return set.isEmpty() ? 0 : set.first();
        }

        //TODO: rewrite on using of usuall find
//        QHash<QString, QString> & findLinks(const Selector * selector, QHash<QString, QString> & links) const;
        inline Set & operator <<(const Set & l) { *this += l; return *this; }
        inline Set & operator <<(Tag * t) { append(t); return *this; }
    };
}

#endif // HTML_SET_H
