#ifndef COMPLETER_FACTORY_H
#define COMPLETER_FACTORY_H

#include <qhash.h>

#include "lexer/lexem_mean_type.h"

#include "misc/singleton.h"

#include "controls/completer.h"

class CompleterFactory : public Singleton<CompleterFactory> {
    QHash<LexerMeanType, QIcon> icons;

    CompleterFactory();
public:
    inline QIcon & ico(const LexerMeanType & ico_type) { return icons[ico_type]; }

    friend class Singleton<CompleterFactory>;
};

#endif // COMPLETER_FACTORY_H
