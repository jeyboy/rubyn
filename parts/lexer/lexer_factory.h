#ifndef LEXER_FACTORY
#define LEXER_FACTORY

#include <qhash.h>

#include "parts/lexer/lexer.h"
#include "parts/formats/format_types.h"

#define IDENT_FORMAT(iter, sub, format) \
    {\
        FormatType nft = types.value(QByteArray(sub, iter - sub), ft_unknown);\
        format = (FormatType)(format | nft);\
    }

class LexerFactory {
    static QHash<QByteArray, FormatType> types;
public:
    static bool determine(const QString & path, Lexer *& lexer);
};

#endif // LEXER_FACTORY
