#ifndef JS_PREDEFINED_H
#define JS_PREDEFINED_H

#include <qhash.h>
#include <qbytearray.h>

#include "misc/singleton.h"
#include "js_state_lexems.h"

namespace Js {
    class Predefined : public Singleton<Predefined> {
        QHash<QByteArray, StateLexem> keys;

        Predefined();
        friend class Singleton<Predefined>;
    public:
        bool hasKey(const QByteArray & key);
        StateLexem lexem(const QByteArray & key);
    };
}

#endif // JS_PREDEFINED_H
