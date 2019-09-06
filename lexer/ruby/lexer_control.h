#ifndef RUBY_LEXER_CONTROL_H
#define RUBY_LEXER_CONTROL_H

//#include "misc/stack.h"
#include "state_lexems.h"
#include "lexer/ilexer_control.h"
//#include "scopes/scope.h"

namespace Ruby {
    struct LexerControl : public ILexerControl {
        LexerControl(IGrammar * cgrammar, BlockUserData *& user_data, TokenCell * stack_token = nullptr, IHighlighter * lighter = nullptr) :
            ILexerControl(cgrammar, user_data, stack_token, lighter)
        {}

        ~LexerControl() {}

        void validateHeredocState();
        void registerHeredocMark(const LEXEM_TYPE & lexem, QByteArray * name);
    };
}

#endif // RUBY_LEXER_CONTROL_H
