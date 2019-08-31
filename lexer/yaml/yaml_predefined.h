#ifndef YAML_PREDEFINED_H
#define YAML_PREDEFINED_H

#include <qhash.h>
#include <qbytearray.h>

#include "misc/singleton.h"
#include "yaml_state_lexems.h"

namespace Yaml {
    class Predefined : public Singleton<Predefined> {
        QHash<QByteArray, StateLexem> keys;

        Predefined();
        friend class Singleton<Predefined>;
    public:
        bool hasKey(const QByteArray & key);
        StateLexem lexem(const QByteArray & key);
    };
}

#endif // YAML_PREDEFINED_H
