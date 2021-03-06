#ifndef CSS_LEXER_CONTROL_H
#define CSS_LEXER_CONTROL_H

//#include "misc/stack.h"
#include "css_state_lexems.h"
#include "lexer/ilexer_control.h"
//#include "scopes/scope.h"

namespace Css {
    struct LexerControl : public ILexerControl {
        LexerControl(IGrammar * cgrammar, BlockUserData *& user_data, TokenCell * stack_token = nullptr, IHighlighter * lighter = nullptr) :
            ILexerControl(cgrammar, user_data, stack_token, lighter)
        {}

        ~LexerControl() {}

        void validateHeredocState();
        void registerHeredocMark(const StateLexem & lexem, QByteArray * name);
    };
}

#endif // CSS_LEXER_CONTROL_H
