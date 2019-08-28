#ifndef CSS_LEXER_FRONTEND_H
#define CSS_LEXER_FRONTEND_H

#include "lexer/ilexer.h"

class LexerControl;

namespace Css {
    class LexerFrontend : public ILexer {
        void lexicate(LexerControl * control);
    protected:
        int rubyLineState(BlockUserData * udata, const int & prev_user_state, const bool & override_status);
    public:
        LexerFrontend();
        ~LexerFrontend();

        void handle(const QString & text, IHighlighter * lighter);
    };
}

#endif // CSS_LEXER_FRONTEND_H
