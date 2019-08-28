#ifndef RUBY_GRAMMAR_H
#define RUBY_GRAMMAR_H

//https://github.com/ruby/ruby/tree/trunk/doc

#include "lexer/igrammar.h"

namespace Ruby {
    class Grammar : public IGrammar, public Singleton<Grammar> {
        Grammar();

        friend class Singleton<Grammar>;
    protected:
        void initParas();
    public:
        void initFlags(StackLexemFlag & flags, const LEXEM_TYPE & lex, const LEXEM_TYPE & last_non_blank_lex);

        bool stackDropable(const LEXEM_TYPE & state, const LEXEM_TYPE & input);

//        LEXEM_TYPE toInterceptor(const StateLexem & lex);

        LEXEM_TYPE stateForHeredoc(const LEXEM_TYPE & lex, const bool & content);

        char percentagePresentationBlocker(const char & ch);

//        bool isStackDroppable(const LEXEM_TYPE & lexem);

//        bool isInterpolable(const LEXEM_TYPE & lexem);

//        StateLexem toHeredocContinious(const LEXEM_TYPE & lexem);

//        StateLexem fromContinious(const LEXEM_TYPE & lexem);

        Identifier toHighlightable(const LEXEM_TYPE & lexem);

        LEXEM_TYPE translate(const LEXEM_TYPE & state, const LEXEM_TYPE & input);
    };
}

#endif // GRAMMAR_RUBY_H
