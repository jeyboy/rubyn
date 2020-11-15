#ifndef CSS_LEXER_CONTROL_H
#define CSS_LEXER_CONTROL_H

#include "css_grammar.h"
#include "css_state_lexems.h"
#include "lexer/ilexer_control.h"

namespace Css {
    struct LexerControl : public ILexerControl {
        Grammar * grammar;

        LexerControl(BlockUserData *& user_data, TokenCell * stack_token = nullptr, IHighlighter * lighter = nullptr) :
            ILexerControl(user_data, stack_token, lighter), grammar(&Grammar::obj())
        {}

        ~LexerControl() {}

        void validateHeredocState();
        void registerHeredocMark(const StateLexem & lexem, QByteArray * name);
    };
}

#endif // CSS_LEXER_CONTROL_H
