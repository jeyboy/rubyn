#ifndef LEXER_CONTEXT_H
#define LEXER_CONTEXT_H

#include <qlist.h>

#include "project/code_formats.h"

struct LexerContext {
    FormatType _main_format;

    QList<FormatType> _additional_formats;

    LexerContext();

    void append(const FormatType & new_format) {
        int u = 0;
        _main_format = new_format;
    }

    bool hasType() { return _main_format != ft_unknown; }
};

#endif // LEXER_CONTEXT_H
