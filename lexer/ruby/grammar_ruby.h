#ifndef GRAMMAR_RUBY_H
#define GRAMMAR_RUBY_H

//https://github.com/ruby/ruby/tree/trunk/doc

#include "lexer/igrammar.h"

namespace Ruby {
    class Grammar : public IGrammar, public Singleton<Grammar> {
        Grammar();

        friend class Singleton<Grammar>;
    protected:
        void initRules();
        void initParas();
    public:
        void initFlags(StackLexemFlag & flags, const StateLexem & lex, const StateLexem & last_non_blank_lex);

        bool stackDropable(const StateLexem & state, const StateLexem & input);

//        StateLexem toInterceptor(const StateLexem & lex);

        StateLexem stateForHeredoc(const StateLexem & lex, const bool & content);

        char percentagePresentationBlocker(const char & ch);

//        bool isStackDroppable(const StateLexem & lexem);

//        bool isInterpolable(const StateLexem & lexem);

//        StateLexem toHeredocContinious(const StateLexem & lexem);

//        StateLexem fromContinious(const StateLexem & lexem);

        Identifier toHighlightable(const StateLexem & lexem);
    };
}

#endif // GRAMMAR_RUBY_H
