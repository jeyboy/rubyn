#ifndef YAML_LEXER_CONTROL_H
#define YAML_LEXER_CONTROL_H

#include "yaml_grammar.h"
#include "yaml_state_lexems.h"
#include "lexer/ilexer_control.h"

namespace Yaml {
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

#endif // YAML_LEXER_CONTROL_H
