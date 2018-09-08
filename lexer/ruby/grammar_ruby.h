#ifndef GRAMMAR_RUBY_H
#define GRAMMAR_RUBY_H

#include "lexer/igrammar.h"

namespace Ruby {
    class Grammar : public IGrammar, public Singleton<Grammar> {
        Grammar();

        friend class Singleton<Grammar>;
    public:
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
