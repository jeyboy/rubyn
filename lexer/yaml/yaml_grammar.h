#ifndef YAML_GRAMMAR_H
#define YAML_GRAMMAR_H

#include "lexer/igrammar.h"
#include "yaml_state_lexems.h"

namespace Yaml {
    class Grammar : public IGrammar, public Singleton<Grammar> {
        Grammar();

        friend class Singleton<Grammar>;
    protected:
        void initParas();
    public:
        void initFlags(StackLexemFlag & flags, const LEXEM_TYPE & lex, const LEXEM_TYPE & last_non_blank_lex);

        bool stackDropable(const LEXEM_TYPE & state, const LEXEM_TYPE & input);

//        LEXEM_TYPE toInterceptor(const LEXEM_TYPE & lex);

        char percentagePresentationBlocker(const char & ch);

        Identifier toHighlightable(const LEXEM_TYPE & lexem);

        LEXEM_TYPE translate(const LEXEM_TYPE & state, const LEXEM_TYPE & input);
    };
}

#endif // YAML_GRAMMAR_H
