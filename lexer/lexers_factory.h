#ifndef LEXERS_FACTORY_H
#define LEXERS_FACTORY_H

#include "misc/singleton.h"

#include "project/code_formats.h"

class ILexer;

class LexersFactory : public Singleton<LexersFactory> {
    QHash<FormatType, ILexer *> _lexers;

    LexersFactory();
    ~LexersFactory();
public:
    ILexer * lexerFor(const FormatType & format);

    friend class Singleton<LexersFactory>;
};

#endif // LEXERS_FACTORY_H
