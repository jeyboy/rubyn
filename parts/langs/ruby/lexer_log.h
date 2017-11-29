#ifndef LEXER_LOG_H
#define LEXER_LOG_H

#include "parts/lexer/lexer.h"
//#include "grammar_ruby.h"

class LexerLog : public Lexer {
    bool cutWord(LexerState * state, const Lexem & predefined_lexem = lex_none) {
        bool has_predefined = predefined_lexem != lex_none;

        state -> cachingPredicate(has_predefined);

        if (state -> cached_length || has_predefined) {
            state -> lex_word =
                has_predefined ? predefined_lexem : PredefinedRuby::obj().lexem(state -> cached);

//            Lexem prev_highlightable = lex_none;

//            if (state -> cached_length) {


//                if (state -> lex_word == lex_word)
//                    identifyWordType(state);

//                prev_highlightable = GrammarRuby::obj().toHighlightable(state -> lex_word);
//            }

////            // translate state
//            translateState(state);

//            if (state -> cached_length) {
//                if (state -> lex_word == lex_word)
//                    registerVariable(state);

//                Lexem highlightable = GrammarRuby::obj().toHighlightable(state -> lex_word);
//                if (highlightable == lex_none)
//                    highlightable = prev_highlightable;

//                if (highlightable != lex_none)
//                    state -> light(highlightable);
//            }

//            state -> attachToken(state -> lex_word);


////            Lexem cont_lexem = GrammarRuby::obj().fromContinious(state -> lex_word);

////            if (cont_lexem != lex_none) {
////                Lexem & top = state -> stack -> touch();

////                if (top == cont_lexem)
////                    state -> stack -> push(state -> lex_word);
////                else state -> lightWithMessage(lex_error, QByteArrayLiteral("Wrong state!!!"));
////            }
        }
        else state -> lex_word = lex_none;

        if (state -> next_offset) {
            state -> cachingDelimiter();
            state -> lex_delimiter = PredefinedRuby::obj().lexem(state -> cached);

//            if (state -> lex_word == lex_none) {
//                Lexem new_state =
//                    GrammarRuby::obj().translate(state -> lex_prev_delimiter, state -> lex_delimiter);

//                if (new_state == lex_error) {
//                    state -> lightWithMessage(
//                        lex_error,
//                        ERROR_STATE(QByteArrayLiteral("Wrong delimiter satisfy state!!!"), state -> lex_prev_delimiter, state -> lex_delimiter)
//                    );
//            //                return false;
//                }

//                state -> lex_delimiter = new_state;


//                state -> replaceToken(state -> lex_delimiter);
//            }
//            else {
//                state -> attachToken(state -> lex_delimiter);
//            }
        }

        state -> dropCached();

        return true;
    }

protected:
    void handle(LexerState * state) {
        if (ECHAR0 == '#') { // note line
            state -> moveBufferToEnd();
            cutWord(state, lex_inline_commentary);
            goto exit;
        }



        while(true) {
            switch(ECHAR0) {
                case 0: {
                    state -> next_offset = 0;
                    cutWord(state);
                    goto exit;
                break;}

                default:
                    iterate:
                        ++state -> buffer;
            }
        }

        exit: return;
    }

    void handle1(LexerState * state) {
        while(true) {
            switch(ECHAR0) {
                case 0: {
                    state -> next_offset = 0;
                    cutWord(state);
                    goto exit;
                break;}

                default:
                    iterate:
                        ++state -> buffer;
            }
        }

        exit: return;
    }

    void handle2(LexerState * state) {
        while(true) {
            switch(ECHAR0) {
                case 0: {
                    state -> next_offset = 0;
                    cutWord(state);
                    goto exit;
                break;}

                default:
                    iterate:
                        ++state -> buffer;
            }
        }

        exit: return;
    }
public:
    inline FormatType format() const { return ft_log; }
};

#endif // LEXER_LOG_H
