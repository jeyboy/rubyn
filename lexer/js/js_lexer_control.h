#ifndef JS_LEXER_CONTROL_H
#define JS_LEXER_CONTROL_H

#include "js_grammar.h"
#include "js_state_lexems.h"
#include "lexer/ilexer_control.h"

namespace Js {
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

#endif // JS_LEXER_CONTROL_H
