#ifndef LEXER_RUBY_H
#define LEXER_RUBY_H

#include "parts/lexer/lexer.h"
#include "predefined_ruby.h"

#define NEXTCHAR NEXT_CHAR(window)
#define PREVCHAR PREV_CHAR(window)
// TODO: use ++state -> index && *(++window)
#define ITERATE {\
        ++state -> index; \
        ++window;\
    }
#define MOVE(offset) {\
        state -> index += offset; \
        window += offset; \
    }


class LexerRuby : public Lexer {
    bool cutWord(const char *& window, const char *& prev, LexerState * state,
                 LexToken * lexems, const Lexem & predefined_lexem = lex_none)
    {
        int word_length = window - prev;

        if (word_length > 0) {
            state -> word = QByteArray(prev, word_length);

            Lexem & stack_top = state -> stack -> touch();

            if ((stack_top & lex_def_start) > lex_start) {
                state -> scope -> addVar(state -> word, 0); // new FilePoint() // TODO: write me
                state -> lex_state = LEX(lex_block_requred, EXCLUDE_BIT(stack_top, lex_def_start));
            }
            else state -> lex_state =
                predefined_lexem ? predefined_lexem : PredefinedRuby::obj().lexem(state -> word);


            if (state -> lex_state == lex_undefined) {
                state -> lex_state = lex_var;

                if (!state -> scope -> hasVar(state -> word)) {
                    // TODO: determine type of word

                    state -> scope -> addUnregVar(state -> word, 0); // new FilePoint() // TODO: write me

                    if (state -> var_def_state == state -> lex_state) {
                        lexems -> next = new LexError(state -> index, word_length, QByteArrayLiteral("Error in variable def"));
                        return false;
                    }

                    state -> var_def_state = state -> lex_state;
                }
            } else {
                if (state -> lex_state & lex_continue) { // TODO: check me
                    StackCell<Lexem> * top = state -> stack -> touchLevel();

                    if (top -> obj == state -> lex_state || top -> obj == EXCLUDE_BIT(state -> lex_state, lex_continue)) {
                        top -> obj = state -> lex_state;
                    } else {
                        lexems -> next = new LexError(state -> index, word_length, QByteArrayLiteral("Wrong state!!!"));
                        return false;
                    }
                } else if (state -> lex_state & lex_start)
                    state -> stack -> push(state -> lex_state);
                else if (state -> lex_state & lex_end) {
                    if (EXCLUDE_BIT(state -> lex_state, lex_end) == EXCLUDE_BIT(state -> stack -> touch(), lex_start)) {
                        state -> stack -> drop();
                    } else {
                        lexems -> next = new LexError(state -> index, word_length, QByteArray::number(state -> stack -> touch()) + QByteArrayLiteral(" required, but ") + QByteArray::number(state -> lex_state) + QByteArrayLiteral(" received"));
                        return false;
                    }
                }
            }

            Lexem highlightable = Lexem(state -> lex_state & lex_highlightable);

            if (highlightable)
                lexems -> next = new LexToken(highlightable, state -> index, word_length);

            qDebug() << state -> word;
        }

        // proc delimiter
        if (predefined_lexem != lex_string_end) {
            prev = window;

            MOVE(state -> next_offset);

            state -> delimiter = QByteArray(prev, window - prev);
            state -> lex_control_state = PredefinedRuby::obj().lexem(state -> delimiter);

            if (state -> var_def_state) {
                if (state -> lex_control_state == lex_var_chain_end) {
                    state -> scope -> clearUnregVar();
                    state -> var_def_state = lex_none;
                } else {
                    if (state -> lex_control_state == state -> var_def_state &&
                        (state -> var_def_state == lex_var || state -> var_def_state == lex_comma)
                    ) {
                        lexems -> next = new LexError(state -> index, word_length, QByteArrayLiteral("Error in variable def"));
                        return false;
                    }
                    else if (state -> lex_control_state != lex_ignore)
                        state -> var_def_state = state -> lex_control_state;
                }
            }
        }

        state -> next_offset = 1;
        prev = window;

        return true;
    }
protected:
    LexToken * parse(const char * window, LexerState * state) {
        LexToken * lexems = new LexToken();

        char end_str_symb;
        const char * prev = window;

//        a + b is interpreted as a+b ( Here a is a local variable)
//        a  +b is interpreted as a(+b) ( Here a is a method call)

//        Ruby interprets semicolons and newline characters as the ending of a statement.
//        However, if Ruby encounters operators, such as +, −, or backslash at the end of a line,
//        they indicate the continuation of a statement.

//        Ruby identifier names may consist of alphanumeric characters and the underscore character ( _ ).

        switch(state -> stack -> touch()) {
            case lex_string_continious: goto handle_string;
            case lex_multiline_commentary_continious: goto handle_multiline_comment;
            default:;
        };

        while(window) {
            switch(*window) {
                case ';':
                case '\r':
                case '\n':
                case '\v':
                case '\t':
                case ' ': {
                    cutWord(window, prev, state, lexems);
                break;}



                case '.': {
                    char next_char = NEXTCHAR;
                    bool next_is_dot = next_char == '.';

                    if (next_is_dot) { // is range
                        ++state -> next_offset;

                        if (NEXTCHAR == '.') // is range with exclusion
                            ++state -> next_offset;
                    } else {
                        if (PREVCHAR == '$' || isDigit(next_char)) // is float or $.
                            goto iterate;
                    }

                    cutWord(window, prev, state, lexems);
                break;}



                case ',': {                   
                    cutWord(window, prev, state, lexems);
                break;}




                case '`':
                case '\'':
                case '"': {
                    end_str_symb = *window;
                    state -> lex_state = state -> stack -> push(lex_string_start);

                    handle_string:
                        bool ended = false;
                        bool out_req = false;

                        while(!ended && !out_req) {
                            ITERATE;

                            switch(*window) {
                                case '#': {
                                    if (end_str_symb != '\'' && NEXTCHAR == '{') {
                                        state -> stack -> push(lex_string_def_required);
                                        ended = true;
                                    }
                                break;}

                                case '`':
                                case '\'':
                                case '"': {
                                    if (PREVCHAR != '\\') {
                                        ITERATE;
                                        ended = true;
                                    }
                                }
                                case 0: {
                                    out_req = true;
                                break;}
                            }
                        }


                    cutWord(window, prev, state, lexems, out_req ? lex_string_continious : lex_string_end);
                break;}



                case ':': {
                    if (NEXTCHAR == ':')
                        ++state -> next_offset;

                    cutWord(window, prev, state, lexems);
                break;}



                case '=': {
                    if (NEXTCHAR == 'b') { // =begin
                       if (NEXT_CHAR(window + 1) == 'e' && NEXT_CHAR(window + 2) == 'g' &&
                            NEXT_CHAR(window + 3) == 'i' && NEXT_CHAR(window + 4) == 'n') {
                                MOVE(4);

                                handle_multiline_comment:
                                    bool ended = false;
                                    bool out_req = false;
                                    state -> lex_state = state -> stack -> push(lex_multiline_commentary_start);

                                    while(!ended && !out_req) {
                                        ITERATE;

                                        switch(*window) {
                                            case '=': {
                                                if (NEXTCHAR == 'e' && NEXT_CHAR(window + 1) == 'n' && NEXT_CHAR(window + 2) == 'd')
                                                    ended = true;
                                            break;}

                                            case 0: {
                                                out_req = true;
                                                cutWord(window, prev, state, lexems, lex_multiline_commentary_continious);
                                                goto go_out;
                                            break;}

                                            default:;
                                        }
                                    }
                       }
                    } else {
                        if (NEXTCHAR == '~')
                            ++state -> next_offset;
                        else {
                            if (NEXTCHAR == '=') // ==
                                ++state -> next_offset;

                            if (NEXTCHAR == '=') // ===
                                ++state -> next_offset;
                        }
                    }

                    cutWord(window, prev, state, lexems);
                break;}



                case '^': {
                    cutWord(window, prev, state, lexems);
                break;}



                case '|': {
                    if (NEXTCHAR == '|')
                        ++state -> next_offset;

                    cutWord(window, prev, state, lexems);
                break;}



                case '&': {
                    if (NEXTCHAR == '&')
                        ++state -> next_offset;

                    cutWord(window, prev, state, lexems);
                break;}



                case '!': {
                    if (!isBlank(PREVCHAR))
                        goto iterate;

                    if (NEXTCHAR == '~' || NEXTCHAR == '=')
                        ++state -> next_offset;

                    cutWord(window, prev, state, lexems);
                break;}



                case '~': {
                    cutWord(window, prev, state, lexems);
                break;}



                case '?': {
                    if (!isBlank(PREVCHAR))
                        goto iterate;

                    cutWord(window, prev, state, lexems);
                break;}



                case '<': {
                    if (NEXTCHAR == '<')
                        ++state -> next_offset;
                    else {
                        if (NEXTCHAR == '=') {
                            ++state -> next_offset;

                            if (NEXTCHAR == '>')
                                ++state -> next_offset;
                        }
                    }

                    cutWord(window, prev, state, lexems);
                break;}



                case '>': {
                    if (NEXTCHAR == '>' || NEXTCHAR == '=')
                        ++state -> next_offset;

                    cutWord(window, prev, state, lexems);
                break;}



                case '[': {
                    cutWord(window, prev, state, lexems);
                break;}
                case ']': {
                    cutWord(window, prev, state, lexems);
                break;}



                case '(': {
                    cutWord(window, prev, state, lexems);
                break;}
                case ')': {                    
                    cutWord(window, prev, state, lexems);
                break;}



                case '{': {
                    cutWord(window, prev, state, lexems);
                break;}
                case '}': {
                    cutWord(window, prev, state, lexems);

                    if (state -> stack -> touch() == lex_string_def_required) { // return to string after interpolation
                        state -> stack -> drop();
                        goto handle_string;
                    }
                break;}



                case '#': { // inline comment
                    bool ended = false;
                    bool out_req = false;
                    state -> lex_state = state -> stack -> push(lex_inline_commentary_start);

                    while(!ended && !out_req) {
                        ITERATE;

                        switch(*window) {
                            case '\n': {
                                ended = true;
                            break;}

                            case 0: {
                                out_req = true;
                            break;}

                            default:;
                        }
                    }

                    cutWord(window, prev, state, lexems, lex_inline_commentary_end);
                break;}



                case '-': {
                    if (NEXTCHAR == '>' || NEXTCHAR == '=') { // lambda
                        ++state -> next_offset;
                    }

                    cutWord(window, prev, state, lexems);
                break;}

                case '+': {
                    if (NEXTCHAR == '=')
                        ++state -> next_offset;

                    cutWord(window, prev, state, lexems);
                break;}




                //# INTEGERS

                //123                  # Fixnum decimal
                //1_234                # Fixnum decimal with underline
                //-500                 # Negative Fixnum
                //0377                 # octal
                //0xff                 # hexadecimal
                //0b1011               # binary
                //12345678901234567890 # Bignum

                //# FLOATS

                //123.4                # floating point value
                //1.0e6                # scientific notation
                //4E20                 # dot not required
                //4e+20                # sign before exponential

                //    +3
                //    3.2e23
                //    -4.70e+9
                //    -.2E-4
                //    -7.6603

                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9': {
                    if (isWord(PREVCHAR))
                        goto iterate;

                    bool ended = false, has_exp_part = false;
                    Lexem predef = lex_none;

                    if (*window == '0') {
                        switch(NEXTCHAR) {
                            case 'x': { predef = lex_hex; break; }
                            case 'b': { predef = lex_bin; break; }
                            default: predef = lex_oct;
                        }
                    }
                    else predef = lex_dec;

                    while(!ended) {
                        ITERATE;

                        if (!*window)
                            break;

                        switch(*window) {
                            case '.': {
                                if (predef & lex_float) {
                                    ended = true;
                                    break;
                                }

                                predef = lex_float;
                            }

                            case 'a':
                            case 'A':
                            case 'b':
                            case 'B':
                            case 'c':
                            case 'C':
                            case 'd':
                            case 'D':
                            case 'f':
                            case 'F': {
                                if (predef != lex_hex) {
                                    lexems -> next = new LexError(state -> index, window - prev, QByteArrayLiteral("Error in number: wrong literal"));
                                    return lexems;
                                }
                            break;}

                            case 'e':
                            case 'E': {
                                if (predef < lex_dec) {
                                    lexems -> next = new LexError(state -> index, window - prev, QByteArrayLiteral("Error in number: exponent part available only for decimals"));
                                    return lexems;
                                } else if (predef == lex_dec) {
                                    if (has_exp_part) {
                                        lexems -> next = new LexError(state -> index, window - prev, QByteArrayLiteral("Error in number: double exponent part"));
                                    } else {
                                        has_exp_part = true;

                                        if (NEXTCHAR == '-' || NEXTCHAR == '+') {
                                            ITERATE;
                                        }
                                    }
                                }
                            break;}

                            case '8':
                            case '9': {
                                if (predef < lex_dec) {
                                    lexems -> next = new LexError(state -> index, window - prev, QByteArrayLiteral("Error in number: 0-7 literals only"));
                                    return lexems;
                                }
                            break;}



                            case '2':
                            case '3':
                            case '4':
                            case '5':
                            case '6':
                            case '7': {
                                if (predef < lex_oct) {
                                    lexems -> next = new LexError(state -> index, window - prev, QByteArrayLiteral("Error in number: 0,1 literals only"));
                                    return lexems;
                                }
                            break;}

                            case '_':
                            case '0':
                            case '1':
                                { break;}

                            default: ended = true;
                        }
                    }

                    cutWord(window, prev, state, lexems, predef);
                break;}



                case '*': {
                    if (NEXTCHAR == '*' || NEXTCHAR == '=')
                        ++state -> next_offset;

                    cutWord(window, prev, state, lexems);
                break;}



                case '%':
                case '/': {
                    if (NEXTCHAR == '=')
                        ++state -> next_offset;

                    cutWord(window, prev, state, lexems);
                break;}



                case '@': {
                    cutWord(window, prev, state, lexems);

//                    if (NEXTCHAR == '@')
//                        window++;
                break;}

                case '$': {
                    bool has_match = false;
                    char next_char = NEXTCHAR;

                    switch(next_char) {
                        case '!':
                        case '@':
                        case '/':
                        case '\\':
                        case ',':
                        case ';':
                        case '.':
                        case '<':
                        case '>':
                        case '0':
                        case '$':
                        case '?':
                        case ':':
                        case '~':
                        case '&':
                        case '`':
                        case '\'':
                        case '+': {
                            ++state -> next_offset;
                            has_match = true;
                        break; }

                        default: {
                            const char & n1_char = NEXT_CHAR(window + 1);

                            if (next_char == '-') {
                                switch(n1_char) {
                                    case '0':
                                    case 'a':
                                    case 'd':
                                    case 'F':
                                    case 'i':
                                    case 'K':
                                    case 'l':
                                    case 'p':
                                    case 'v':
                                    case '+': {
                                        state -> next_offset += 2;
                                        has_match = true;
                                    break; }

                                    default:;
                                }
                            } else if (next_char == '_') {
                                if (!isAlphaNum(n1_char))
                                    has_match = true;
                            } else if (isDigit(next_char) && isDigit(n1_char)) // $0-$99
                                has_match = true;
                        }
                    }

                    if (has_match)
                        cutWord(window, prev, state, lexems);
                break;}

                default:
                    iterate:
                        ITERATE;
            }
        }

        go_out:
            return lexems;
    }
};

#endif // LEXER_RUBY_H
