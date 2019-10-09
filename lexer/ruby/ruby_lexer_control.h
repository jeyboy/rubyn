#ifndef RUBY_LEXER_CONTROL_H
#define RUBY_LEXER_CONTROL_H

//#include "misc/stack.h"
#include "ruby_state_lexems.h"
#include "lexer/ilexer_control.h"
//#include "scopes/scope.h"

namespace Ruby {
    struct LexerControl : public ILexerControl {
        LexerControl(IGrammar * cgrammar, BlockUserData *& udata, TokenCell * init_stack_token = nullptr, IHighlighter * curr_lighter = nullptr) :
            ILexerControl(cgrammar, udata, init_stack_token, curr_lighter) {}

        ~LexerControl() {}

        void validateHeredocState();
        void registerHeredocMark(const LEXEM_TYPE & lexem, QByteArray * name);
    };
}

#endif // RUBY_LEXER_CONTROL_H
