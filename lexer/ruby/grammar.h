#ifndef RUBY_GRAMMAR_H
#define RUBY_GRAMMAR_H

//https://github.com/ruby/ruby/tree/trunk/doc

#include "lexer/igrammar.h"
#include "state_lexems.h"

namespace Ruby {
    class Grammar : public IGrammar, public Singleton<Grammar> {
        Grammar();

        friend class Singleton<Grammar>;
    protected:
        void initParas();
    public:
        void initFlags(StackLexemFlag & flags, const IState::Lexem & lex, const IState::Lexem & last_non_blank_lex);

        bool stackDropable(const IState::Lexem & state, const IState::Lexem & input);

//        LEXEM_TYPE toInterceptor(const IState::Lexem & lex);

        IState::Lexem stateForHeredoc(const IState::Lexem & lex, const bool & content);

        char percentagePresentationBlocker(const char & ch);

//        bool isStackDroppable(const IState::Lexem & lexem);

//        bool isInterpolable(const IState::Lexem & lexem);

//        IState::Lexem toHeredocContinious(const IState::Lexem & lexem);

//        IState::Lexem fromContinious(const IState::Lexem & lexem);

        Identifier toHighlightable(const IState::Lexem & lexem);

        IState::Lexem translate(const IState::Lexem & state, const IState::Lexem & input);
    };
}

#endif // GRAMMAR_RUBY_H
