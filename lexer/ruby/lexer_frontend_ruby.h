#ifndef LEXER_FRONTEND_RUBY_H
#define LEXER_FRONTEND_RUBY_H

#include "lexer/ilexer.h"

class LexerControl;

namespace Ruby {
    class LexerFrontend : public ILexer {
        void identifyWordType(LexerControl * state);
        void registerVariable(LexerControl * state);
        void translateState(LexerControl * state);
        bool cutWord(LexerControl * state, const StateLexem & predefined_lexem = lex_none,
                     const StateLexem & predefined_delimiter = lex_none, StackLexemFlag flags = slf_none);

        bool parseContinious(LexerControl * state);
        bool parseNumber(LexerControl * state);
        bool parseString(LexerControl * state);
        bool parseEString(LexerControl * state);
        bool parseCommand(LexerControl * state);
        bool parsePercentagePresenation(LexerControl * state);
        bool parseHeredocMarks(LexerControl * state, StateLexem & lex);
        bool parseHeredoc(LexerControl * state);
        bool parseRegexp(LexerControl * state);
        bool parseComment(LexerControl * state);

        void lexicate(LexerControl * control);
    protected:
        int lineState(BlockUserData * udata, const int & prev_user_state);
    public:
        LexerFrontend();
        ~LexerFrontend();

        void handle(const QString & text, Highlighter * lighter);

        void paraOpositionStr(const PARA_TYPE & para, QString & res);
    };
}

#endif // LEXER_FRONTEND_RUBY_H
