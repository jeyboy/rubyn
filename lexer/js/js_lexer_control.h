#ifndef JS_LEXER_CONTROL_H
#define JS_LEXER_CONTROL_H

//#include "misc/stack.h"
#include "js_state_lexems.h"
#include "lexer/ilexer_control.h"
//#include "scopes/scope.h"

namespace Js {
    struct LexerControl : public ILexerControl {
        LexerControl(IGrammar * cgrammar, BlockUserData *& user_data, TokenCell * stack_token = nullptr, IHighlighter * lighter = nullptr) :
            ILexerControl(cgrammar, user_data, stack_token, lighter)
        {}

        ~LexerControl() {}

        void validateHeredocState();
        void registerHeredocMark(const StateLexem & lexem, QByteArray * name);
    };
}

#endif // JS_LEXER_CONTROL_H
