#ifndef ILEXER_H
#define ILEXER_H

#include <qstring.h>

#include "highlighter/highlighter.h"

class ILexer {
public:
    ILexer();

    inline virtual ~ILexer() {}

    virtual void handle(const QString & text, Highlighter * lighter);

    virtual void calcFoldings() {}
};

#endif // ILEXER_H
