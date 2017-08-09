#ifndef LEXER_RUBY_H
#define LEXER_RUBY_H

#include "parts/lexer/lexer.h"
#include "predefined_ruby.h"

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
                if (state -> lex_state & lex_start)
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
        if (!predefined_lexem) {
            prev = window;
            window += state -> next_offset;
            state -> index += state -> next_offset;

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

//# INTEGERS

//123                  # Fixnum decimal
//1_234                # Fixnum decimal with underline
//-500                 # Negative Fixnum
//0377                 # octal
//0xff                 # hexadecimal
//0b1011               # binary
//?a                   # character code for 'a'
//?\n                  # code for a newline (0x0a)
//12345678901234567890 # Bignum

//# FLOATS

//123.4                # floating point value
//1.0e6                # scientific notation
//4E20                 # dot not required
//4e+20                # sign before exponential

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
                    char next_char = NEXT_CHAR(window);
                    bool next_is_dot = next_char == '.';

                    if (next_is_dot) { // is range
                        ++state -> next_offset;

                        if (NEXT_CHAR(window) == '.') // is range with exclusion
                            ++state -> next_offset;
                    } else {
                        if (PREV_CHAR(window) == '$' || isDigit(next_char)) // is float or $.
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
                        while(!ended && ++window) {
                            ++state -> index;

                            switch(*window) {
                                case '#': {
                                    if (end_str_symb != '\'' && NEXT_CHAR(window) == '{') {
                                        state -> stack -> push(lex_string_def_required);
                                        ended = true;
                                    }
                                break;}

                                case '`':
                                case '\'':
                                case '"': {
                                    if (PREV_CHAR(window) != '\\') {
                                        window++;
                                        ended = true;
                                    }
                                }
                            }
                        }


                    cutWord(window, prev, state, lexems, lex_string_end);
                break;}



                case ':': {
                    if (NEXT_CHAR(window) == ':' || PREV_CHAR(window) == '$')
                        ++state -> next_offset;

                    cutWord(window, prev, state, lexems);
                break;}



                case '=': {
                    if (NEXT_CHAR(window) == 'b') { // =begin
                       if (NEXT_CHAR(window + 1) == 'e' && NEXT_CHAR(window + 2) == 'g' &&
                            NEXT_CHAR(window + 3) == 'i' && NEXT_CHAR(window + 4) == 'n') {
                                int offset = strlen(window) - state -> index;
                                window += offset - 1;
                       }
                    }
                    else if (NEXT_CHAR(window) == 'e') { // =end
                       if (NEXT_CHAR(window + 1) == 'n' && NEXT_CHAR(window + 2) == 'd')
                                window +=3;
                    } else {
                        if (NEXT_CHAR(window) == '~')
                            ++state -> next_offset;
                        else {
                            if (NEXT_CHAR(window) == '=') // ==
                                ++state -> next_offset;

                            if (NEXT_CHAR(window) == '=') // ===
                                ++state -> next_offset;
                        }
                    }

//                    if (window - prev == 1)
//                        var_def_state == lex_var_chain_end;

                    cutWord(window, prev, state, lexems);
                break;}

                case '^': {
                    cutWord(window, prev, state, lexems);
                break;}

                case '|': {
                    if (NEXT_CHAR(window) == '|')
                        ++state -> next_offset;

                    cutWord(window, prev, state, lexems);
                break;}



                case '&': {
                    if (NEXT_CHAR(window) == '&')
                        ++state -> next_offset;

                    cutWord(window, prev, state, lexems);
                break;}



                case '!': {
                    if (!isBlank(PREV_CHAR(window)))
                        goto iterate;

                    if (NEXT_CHAR(window) == '~' || NEXT_CHAR(window) == '=')
                        ++state -> next_offset;

                    cutWord(window, prev, state, lexems);
                break;}

                case '~': {
                    cutWord(window, prev, state, lexems);
                break;}



                case '?': {
                    if (!isBlank(PREV_CHAR(window)))
                        goto iterate;

                    cutWord(window, prev, state, lexems);
                break;}


                case '<': {
                    if (NEXT_CHAR(window) == '<')
                        ++state -> next_offset;
                    else {
                        if (NEXT_CHAR(window) == '=')
                            ++state -> next_offset;

                        if (NEXT_CHAR(window) == '>')
                            ++state -> next_offset;
                    }

                    cutWord(window, prev, state, lexems);
                break;}



                case '>': {
                    if (NEXT_CHAR(window) == '>')
                        ++state -> next_offset;
                    else if (NEXT_CHAR(window) == '=')
                        ++state -> next_offset;

                    cutWord(window, prev, state, lexems);
                break;}



                case '[': {
//                    var_def_state = lex_array_start;
                    cutWord(window, prev, state, lexems);
                break;}
                case ']': {
//                    var_def_state = lex_array_end;
                    cutWord(window, prev, state, lexems);
                break;}



                case '(': {
//                    var_def_state = lex_wrap_start;
                    cutWord(window, prev, state, lexems);
                break;}
                case ')': {                    
//                    var_def_state = lex_wrap_end;
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
                    int offset = strlen(window) - state -> index;
                    window += offset - 1;
                    cutWord(window, prev, state, lexems);
                break;}



                case '-':
                    if (NEXT_CHAR(window) == '>') { // lambda
                        ++state -> next_offset;

                        cutWord(window, prev, state, lexems);
                    }
                case '+': {
                    if (isDigit(NEXT_CHAR(window)) || PREV_CHAR(window) == 'e')
                        goto iterate;

                    if (NEXT_CHAR(window) == '=')
                        ++state -> next_offset;

                    cutWord(window, prev, state, lexems);
                break;}


                case '*': {
                    if (NEXT_CHAR(window) == '*' || NEXT_CHAR(window) == '=')
                        ++state -> next_offset;

                    cutWord(window, prev, state, lexems);
                break;}

                case '%':
                case '/': {
                    if (NEXT_CHAR(window) == '=')
                        ++state -> next_offset;

                    cutWord(window, prev, state, lexems);
                break;}



                case '@': {
                    cutWord(window, prev, state, lexems);

//                    if (NEXT_CHAR(window) == '@')
//                        window++;
                break;}

                case '$': {
                    bool has_match = false;
                    char next_char = NEXT_CHAR(window);

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
                        ++state -> index;
                        ++window;
            }
        }

        return lexems;
    }
};

#endif // LEXER_RUBY_H
