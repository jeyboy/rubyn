#ifndef RUBY_LEXER_FRONTEND_H
#define RUBY_LEXER_FRONTEND_H

#include "lexer/ilexer.h"
#include "lexer/lexer_stack_flags.h"
#include "ruby_lexer_control.h"
#include "ruby_state_lexems.h"
#include "ruby_para_lexem.h"


// Store context variable in control
// List of contexts identificated from list of extensions

// Store code context variable in control \\ in class \\ in module \\ in method \\ in method params and etc and append it to lexems


namespace Ruby {
    struct LexerControl;

    class LexerFrontend : public ILexer {
        enum CharCodePart : quint8 {
            ccp_none = 0,
            ccp_symbol = 1,
            ccp_octal = 2,
            ccp_hex = 4,
            ccp_unicode = 8,
            ccp_ctrl = 16,
            ccp_short_ctrl = 32,
            ccp_meta = 64,
        };

        void highlightMarkupInComments(LexerControl * state);

        void registerVariable(LexerControl * state);
        void registerMethod(LexerControl * state);
        void registerClass(LexerControl * state);
        void registerModule(LexerControl * state);

        void identifyWordType(LexerControl * state);
        LEXEM_TYPE translateState(LexerControl * state, const LEXEM_TYPE & lex1, const LEXEM_TYPE & lex2);
        bool cutWord(LexerControl * state, const LEXEM_TYPE & predefined_lexem = lex_none,
                     const LEXEM_TYPE & predefined_delimiter = lex_none, StackLexemFlag flags = slf_none);

        bool parseContinious(LexerControl * state);
        bool parseNumber(LexerControl * state);
        bool parseString(LexerControl * state);
        bool parseEString(LexerControl * state);
        bool parseCommand(LexerControl * state);
        bool parsePercentagePresenation(LexerControl * state);
        bool parseHeredocMarks(LexerControl * state, LEXEM_TYPE & lex);
        bool parseHeredoc(LexerControl * state);
        bool parseRegexp(LexerControl * state);
        bool parseRegexpGroup(LexerControl * state);
        bool parseComment(LexerControl * state);
        bool parseCharCode(LexerControl * state);

        void lexicate(LexerControl * control);
    protected:
        int rubyLineState(BlockUserData * udata, const int & prev_user_state, const bool & override_status);
    public:
        LexerFrontend();
        ~LexerFrontend();

        void handle(const QString & text, IHighlighter * lighter);

        void paraOpositionStr(const PARA_TYPE & para, QString & res);

        bool isCompleterInitiable(const LEXEM_TYPE & lex, const bool & at_end);

        bool isCompleterContinuable(const LEXEM_TYPE & lex, const bool & /*at_end*/);

        bool isCompleterReplaceable(const LEXEM_TYPE & lex, const bool & at_start);
    };
}

#endif // RUBY_LEXER_FRONTEND_H
