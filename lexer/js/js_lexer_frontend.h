#ifndef JS_LEXER_FRONTEND_H
#define JS_LEXER_FRONTEND_H

#include "lexer/ilexer.h"

namespace Js {
    struct LexerControl;

    class LexerFrontend : public ILexer {
        void lexicate(LexerControl * control);
//    protected:
//        int rubyLineState(BlockUserData * udata, const int & prev_user_state, const bool & override_status);
    public:
        LexerFrontend();
        ~LexerFrontend();

        void handle(const QString & text, IHighlighter * lighter);

        bool isCompleterInitiable(const LEXEM_TYPE & lex, const bool & at_end);

        bool isCompleterContinuable(const LEXEM_TYPE & lex, const bool & at_end);

        bool isCompleterReplaceable(const LEXEM_TYPE & lex, const bool & at_start);
    };
}

#endif // JS_LEXER_FRONTEND_H
