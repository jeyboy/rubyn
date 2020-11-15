#ifndef YAML_LEXER_H
#define YAML_LEXER_H

#include "lexer/ilexer.h"

namespace Yaml {
    struct LexerControl;

    class Lexer : public ILexer {
        void lexicate(LexerControl * state);
    public:
        Lexer();
        ~Lexer();

        void handle(const QString & text, IHighlighter * lighter);

        bool isCompleterInitiable(const LEXEM_TYPE & lex, const bool & at_end);
        bool isCompleterContinuable(const LEXEM_TYPE & lex, const bool & at_end);
        bool isCompleterReplaceable(const LEXEM_TYPE & lex, const bool & at_start);
    };
}


#endif // YAML_LEXER_H
