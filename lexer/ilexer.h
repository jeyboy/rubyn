#ifndef ILEXER_H
#define ILEXER_H

#include <qstring.h>

#include "highlighter/highlighter.h"

class ILexer {
public:
    ILexer();

    inline virtual ~ILexer() {}

    virtual void handle(const QString & text, Highlighter * lighter) = 0;

//    virtual bool dump(QIODevice * device, ) { return false; }

    virtual void calcFoldings() {}
};

#endif // ILEXER_H
