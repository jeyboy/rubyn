#ifndef CSS_PREDEFINED_H
#define CSS_PREDEFINED_H

#include <qhash.h>
#include <qbytearray.h>

#include "misc/singleton.h"
#include "css_state_lexems.h"

namespace Css {
    class Predefined : public Singleton<Predefined> {
        QHash<QByteArray, StateLexem> keys;

        Predefined();
        friend class Singleton<Predefined>;
    public:
        bool hasKey(const QByteArray & key);
        StateLexem lexem(const QByteArray & key);
    };
}

#endif // CSS_PREDEFINED_H
