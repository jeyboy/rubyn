#ifndef HTML_PREDEFINED_H
#define HTML_PREDEFINED_H

#include <qhash.h>
#include <qbytearray.h>

#include "misc/singleton.h"
#include "html_state_lexems.h"

namespace Html {
    class Predefined : public Singleton<Predefined> {
        QHash<QByteArray, StateLexem> keys;

        Predefined();
        friend class Singleton<Predefined>;
    public:
        bool hasKey(const QByteArray & key);
        StateLexem lexem(const QByteArray & key);
    };
}

#endif // HTML_PREDEFINED_H
