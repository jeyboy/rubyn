#ifndef GRAMMAR_RUBY_H
#define GRAMMAR_RUBY_H

#include "lexer/igrammar.h"

namespace Ruby {
    class Grammar : public IGrammar, public Singleton<Grammar> {
        Grammar();

        friend class Singleton<Grammar>;
    public:
    //    bool isPushable(const Lexem & lexem) {
    //        switch(lexem) {
    //            case lex_inline_block_start:
    //                return true;

    //            default: return false;
    //        }
    //    }

    //    bool isPopable(const Lexem & lexem) {
    //        switch(lexem) {
    //            case:;
    //        }
    //    }

        StateLexem toInterceptor(const StateLexem & lex);

        char percentagePresentationBlocker(const char & ch);

        bool isStackDroppable(const StateLexem & lexem);

        bool isInterpolable(const StateLexem & lexem);

        StateLexem toHeredocContinious(const StateLexem & lexem);

        bool isContinious(const StateLexem & lexem);

        StateLexem fromContinious(const StateLexem & lexem);

        Identifier toHighlightable(const StateLexem & lexem);
    };
}

#endif // GRAMMAR_RUBY_H
