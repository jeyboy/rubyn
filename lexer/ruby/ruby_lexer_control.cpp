#include "ruby_lexer_control.h"

using namespace Ruby;

void LexerControl::validateHeredocState() {
    //TODO: remove all stack values till we have heredoc start on the top
    if (stack_token) {
        switch(stack_token -> lexem) {
            case lex_heredoc_intended_start:
            case lex_heredoc_start:
            case lex_cheredoc_intended_start:
            case lex_cheredoc_start:
            case lex_eheredoc_intended_start:
            case lex_eheredoc_start: { break;}

            default: {
                lightWithMessage(
                    lex_error,
                    QByteArrayLiteral("Wrong stack state for begin of heredoc")
                );
            }
        }
    }
}

void LexerControl::registerHeredocMark(const LEXEM_TYPE & lexem, QString * name) {
    StateLexem doc_lex = lex_none;

    switch(lexem) {
        case lex_heredoc_intended_mark:     { doc_lex = lex_heredoc_intended_start; break;}
        case lex_heredoc_mark:              { doc_lex = lex_heredoc_start; break;}
        case lex_cheredoc_intended_mark:    { doc_lex = lex_cheredoc_intended_start; break;}
        case lex_cheredoc_mark:             { doc_lex = lex_cheredoc_start; break;}
        case lex_eheredoc_intended_mark:    { doc_lex = lex_eheredoc_intended_start; break;}
        case lex_eheredoc_mark:             { doc_lex = lex_eheredoc_start; break;}
        default:;
    };

    if (doc_lex != lex_none) {
        TokenCell * new_heredoc =
            TokenList::insert(user_data -> token_begin, doc_lex, -1, 0);

        new_heredoc -> data = name;

        if (!heredoc_token) {
            new_heredoc -> stacked_prev = stack_token;
            heredoc_token = stack_token = new_heredoc;
        } else {
            new_heredoc -> stacked_prev = heredoc_token -> stacked_prev;
            heredoc_token -> stacked_prev = new_heredoc;
            heredoc_token = new_heredoc;
        }
    } else {
        int i = 0;
    }
}
