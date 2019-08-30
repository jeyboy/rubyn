#ifndef YAML_GRAMMAR_H
#define YAML_GRAMMAR_H

#include "lexer/igrammar.h"
#include "state_lexems.h"

namespace Yaml {
    class Grammar : public IGrammar, public Singleton<Grammar> {
        Grammar();

        friend class Singleton<Grammar>;
    protected:
        void initParas();
    public:
        void initFlags(StackLexemFlag & flags, const StateLexem & lex, const StateLexem & last_non_blank_lex);

        bool stackDropable(const StateLexem & state, const StateLexem & input);

//        LEXEM_TYPE toInterceptor(const StateLexem & lex);

        StateLexem stateForHeredoc(const StateLexem & lex, const bool & content);

        char percentagePresentationBlocker(const char & ch);

//        bool isStackDroppable(const StateLexem & lexem);

//        bool isInterpolable(const StateLexem & lexem);

//        StateLexem toHeredocContinious(const StateLexem & lexem);

//        StateLexem fromContinious(const StateLexem & lexem);

        Identifier toHighlightable(const StateLexem & lexem);

        StateLexem translate(const StateLexem & state, const StateLexem & input);
    };
}

#endif // YAML_GRAMMAR_H
