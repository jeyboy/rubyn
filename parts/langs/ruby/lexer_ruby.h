#ifndef LEXER_RUBY_H
#define LEXER_RUBY_H

#include "parts/lexer/lexer.h"
#include "predefined_ruby.h"

class LexerRuby : public Lexer {
    bool checkStack(const Lexem & lex_flag, LexerState * state) {
//        if (lex_flag & lex_start) {
//            if (lex_flag & lex_chain) {
//                // INFO: if line is not empty then we have deal with inline branching
//                if (state -> new_line_state == lex_none)
//                    state -> stack -> push(lex_flag);
//            } else
//                state -> stack -> push(lex_flag);
//        } else if (lex_flag & lex_end) {
//            Lexem stack_top = state -> stack -> touch();
//            bool condition =
//                stack_top & lex_block ?
//                    lex_flag & lex_block
//                :
//                    EXCLUDE_BIT(lex_flag, lex_end) == EXCLUDE_BIT(stack_top, lex_start);


//            if (condition) {
//                state -> stack -> drop();
//            } else {
//                lighter -> setFormat(
//                    state -> index - word_length,
//                    state -> cached_str_length,
//                    HighlightFormatFactory::obj().getFormatFor(lex_error)
//                );
////                APPEND_ERR(QByteArray::number(state -> stack -> touch()) + QByteArrayLiteral(" required, but ") + QByteArray::number(lex_flag) + QByteArrayLiteral(" received"));

//                return false;
//            }
//        } else if (lex_flag & lex_chain_block) {
//            Lexem stack_top = state -> stack -> touch();

//            if (stack_top & lex_chain_block)
//                state -> stack -> replace(lex_flag);
//            else
//                lighter -> setFormat(
//                    state -> index - word_length,
//                    state -> cached_str_length,
//                    HighlightFormatFactory::obj().getFormatFor(lex_error)
//                );

////                APPEND_ERR(QByteArrayLiteral("Error in condition logic"));
//        } else if (lex_flag & lex_def)
//            state -> stack -> push(lex_flag);

        return true;
    }

    bool cutWord(LexerState * state, const Lexem & predefined_lexem = lex_none) {
        state -> cachingStrLength();

        if (state -> cached_str_length) {
            QByteArray word;
            state -> getStr(word);

            state -> lex_state =
                predefined_lexem
                    ?
                        predefined_lexem
                    :
                        PredefinedRuby::obj().lexem(word);


            if (state -> lex_state == lex_undefined) {
                if (!state -> scope -> hasVar(word)) {
                    Lexem & stack_top = state -> stack -> touch();

                    if ((stack_top & lex_def) > lex_key) {
                        state -> scope -> addVar(
                            word,
                            new FilePoint(
                                stack_top == lex_class_def ? lex_class_def_name : lex_module_def_name,
                                0, 0, state -> bufferPos()
                            )
                        );
                        state -> stack -> replace(lex_block_start);
                        state -> lex_state = lex_def; // TODO: maybe change to something else
                    }
                    else {
                        switch(LCHAR) { // INFO: determine type of word
                            case ':': { state -> lex_state = lex_name_symbol; break;}
                            case '$': { state -> lex_state = lex_name_global; break;}
                            case '@': {
                                if (LCHAR2 == '@')
                                    state -> lex_state = lex_name_object;
                                else
                                    state -> lex_state = lex_name_instance;
                            break;}
                            default: {
                                state -> lex_state =
                                    (RCHAR_PREV == ':')
                                        ?
                                            lex_name_symbol
                                        :
                                            lex_name_local;
                            }
                        }

                        if (state -> lex_state != lex_name_symbol)
                            state -> scope -> addVar(
                                word,
                                new FilePoint(state -> lex_state, 0, 0, state -> bufferPos())
                            );

    //                    if (!state -> var_def_state)
    //                         state -> stack -> push(lex_var_chain_start);

    //                    state -> scope -> addUnregVar(state -> word, 0); // new FilePoint() // TODO: write me

    //                    if (state -> var_def_state == state -> lex_state) {
    //                        APPEND_ERR(QByteArrayLiteral("Error in variable def"));
    //                        return false;
    //                    }

    //                    state -> var_def_state = state -> lex_state;
                    }
                }
                else state -> lex_state = state -> scope -> varType(word);

            } else {
                if (state -> lex_state & lex_continue) { // TODO: check me
                    Lexem top = state -> stack -> touch();

                    if (top == state -> lex_state || top == EXCLUDE_BIT(state -> lex_state, lex_continue)) {
                        state -> stack -> push(state -> lex_state);
                    } else {
                        state -> lightWithMessage(lex_error, QByteArrayLiteral("Wrong state!!!"));
                        return false;
                    }
                }
                else if (!checkStack(state -> lex_state, state))
                        return false;
            }

            Lexem highlightable = Lexem(state -> lex_state & lex_highlightable);
            if (highlightable)
                state -> light(highlightable);

            qDebug() << word;
        } else if (predefined_lexem) {
            if (!checkStack(state -> lex_state, state))
                return false;
        }
        else state -> lex_state = lex_ignore;

        if (state -> lex_state < lex_end_line)
            state -> new_line_state = state -> lex_state;



        if (state -> next_offset) {
            // proc delimiter
            bool is_close_block = RCHAR == '}';

            if (predefined_lexem != lex_string_end && (!is_close_block || (is_close_block && state -> cached_str_length == 0))) {
                state -> lockToDelimiter();

                QByteArray delimiter;
                state -> getStr(delimiter);
                state -> lex_state = PredefinedRuby::obj().lexem(delimiter);

                if (state -> lex_state == lex_end_line)
                    state -> new_line_state = lex_none;
                else if (state -> lex_state < lex_end_line)
                    state -> new_line_state = state -> lex_state;

                if (!checkStack(state -> lex_state, state))
                    return false;

    //            if (state -> var_def_state) {
    //                if (state -> lex_state == lex_var_chain_end) {
    //                    state -> scope -> clearUnregVar();
    //                    state -> var_def_state = lex_none;
    //                } else {
    //                    if (
    //                            (
    //                                state -> lex_state == state -> var_def_state &&
    //                                (
    //                                    state -> var_def_state == lex_var ||
    //                                    state -> var_def_state == lex_comma
    //                                )
    //                            )
    //                            || state -> lex_state == lex_end_line
    //                            || state -> lex_state == lex_binary_operator
    //                    ) {

    //                        APPEND_ERR(QByteArrayLiteral("Error in variable def"));
    //                        return false;
    //                    }
    //                    else if (state -> lex_state != lex_ignore)
    //                        state -> var_def_state = state -> lex_state;
    //                }
    //            }
            }
        }

        state -> dropStr();

        return true;
    }
protected:
    LexerStatus handle(LexerState * state) {
        char end_str_symb;
        LexerStatus status = ls_none;

//        a + b is interpreted as a.+(b)
//        a + b is interpreted as a+b ( Here a is a local variable)
//        a  +b is interpreted as a(+b) ( Here a is a method call)

//        Ruby interprets semicolons and newline characters as the ending of a statement.
//        However, if Ruby encounters operators, such as +, −, or backslash at the end of a line,
//        they indicate the continuation of a statement.


        continue_mark:
            Lexem top = state -> stack -> touch();

            if (top & lex_continue) {
                state -> stack -> drop();
                --state -> buffer;

                switch(top) {
                    case lex_estring_continue: goto handle_string;
                    case lex_heredoc_continue: goto handle_heredoc;
                    case lex_regexp_continue: goto handle_regexp;
                    case lex_commentary_continue: goto handle_multiline_comment;
                    default:;
                };
            }

        while(true) {
            next_step:

            switch(RCHAR) {
                case ';':
                case '\r':
                case '\n':
                case '\v':
                case '\t':
                case ' ':
                case ',':
                case '^':
                case '~':
                case '(':
                case ')': {
                    if(!cutWord(state))
                        goto exit;
                break;}



                case '.': {
                    if (RCHAR2 == '.') { // is range
                        ++state -> next_offset;

                        if (RCHAR3 == '.') // is range with exclusion
                            ++state -> next_offset;
                    } /*else {
                        if (PREVCHAR == '$' || isDigit(next_char)) // is float or $.
                            goto iterate;
                    }*/

                    if (!cutWord(state))
                        goto exit;
                break;}


                case '`':
                case '\'':
                case '"': {
                    end_str_symb = RCHAR;
                    state -> stack -> push(lex_string_start);

                    handle_string:
                        bool ended = false;
                        bool out_req = false;
                        bool def_required = false;

                        while(!ended && !out_req) {
                            ++state -> buffer;

                            switch(RCHAR) {
                                case '#': {
                                    if (end_str_symb != '\'' && RCHAR2 == '{') {
                                        def_required = ended = true;
                                    }
                                break;}

                                case '`':
                                case '\'':
                                case '"': {
                                    if (RCHAR_PREV != '\\') {
                                        ++state -> buffer;
                                        ended = true;
                                    }
                                break;}

                                case 0: {
                                    out_req = true;
                                break;}
                            }
                        }


                    if (!cutWord(state, out_req ? lex_string_continue : lex_string_end))
                        goto exit;

                    if (def_required) { // INFO: patch for interpolation
                        state -> stack -> push(lex_string_continue);
                    }
                break;}



                case ':': {
                    if (RCHAR2 == ':')
                        ++state -> next_offset;
                    else { // if we have deal with symbol
                        if (isWord(RCHAR_PREV)) {
                            ++state -> buffer;
                            state -> next_offset = 0;
                        }
                        else if (state -> lex_state > lex_undefined) {
                            goto iterate;
                        }
                    }

                    if (!cutWord(state))
                        goto exit;
                break;}



                case '=': {
                    if (NEXTCHAR == 'b') { // =begin
                       if (NEXT_CHAR(window + 1) == 'e' && NEXT_CHAR(window + 2) == 'g' &&
                            NEXT_CHAR(window + 3) == 'i' && NEXT_CHAR(window + 4) == 'n') {
                                MOVE(4);

                                handle_multiline_comment:
                                    bool ended = false;
                                    bool out_req = false;
                                    state -> stack -> push(lex_commentary_start);

                                    while(!ended && !out_req) {
                                        ++state -> buffer;

                                        switch(CURRCHAR) {
                                            case '=': {
                                                if (NEXTCHAR == 'e' && NEXT_CHAR(window + 1) == 'n' && NEXT_CHAR(window + 2) == 'd')
                                                    ended = true;
                                                    MOVE(4);
                                            break;}

                                            case 0: {
                                                out_req = true;
                                                cutWord(state, lex_commentary_continue);

                                                status = ls_comment;

                                                goto exit;
                                            break;}

                                            default:;
                                        }
                                    }
                       }
                    } else if (NEXTCHAR == 'e' && NEXT_CHAR(window + 1) == 'n' && NEXT_CHAR(window + 2) == 'd') {
                        MOVE(4);
                        state -> next_offset = 0;
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

                    if (!cutWord(state))
                        goto exit;
                break;}




                case '|': {
                    if (NEXTCHAR == '|')
                        ++state -> next_offset;

                    if (NEXTCHAR == '=')
                        ++state -> next_offset;

                    if (!cutWord(state))
                        goto exit;
                break;}



                case '&': {
                    if (NEXTCHAR == '&' || NEXTCHAR == '.')
                        ++state -> next_offset;                   

                    if (!cutWord(state))
                        goto exit;
                break;}



                case '!': {
                    if (!isBlank(PREVCHAR))
                        goto iterate;

                    if (NEXTCHAR == '~' || NEXTCHAR == '=')
                        ++state -> next_offset;

                    if (!cutWord(state))
                        goto exit;
                break;}



                case '?': {
                    if (!isBlank(PREVCHAR))
                        goto iterate;

                    if (!cutWord(state))
                        goto exit;
                break;}



                case '<': {
                    if (NEXTCHAR == '<')
                        ++state -> next_offset;

                        if (isUpper(NEXTCHAR2)) {
                            handle_heredoc:
                                ;
                                //TODO: realize heredoc
                        }
                    else {
                        if (NEXTCHAR == '=') {
                            ++state -> next_offset;

                            if (NEXTCHAR == '>')
                                ++state -> next_offset;
                        }
                    }

                    if (!cutWord(state))
                        goto exit;
                break;}



                case '>': {
                    if (NEXTCHAR == '>' || NEXTCHAR == '=')
                        ++state -> next_offset;

                    if (!cutWord(state))
                        goto exit;
                break;}



                case '[': {
                    if (!cutWord(state))
                        goto exit;
                break;}
                case ']': {
                    if (!cutWord(state))
                        goto exit;
                break;}



                case '{': {
                    if (!cutWord(state))
                        goto exit;
                break;}
                case '}': {
                    if (!cutWord(state))
                        goto exit;

                    Lexem top = state -> stack -> touch();
                    if (top & lex_continue) { // after interpolation
                        state -> stack -> replace(
                            LEX(
                                EXCLUDE_BIT(top, lex_continue),
                                lex_start
                            )
                        );

                        state -> stack -> push(top);

                        goto continue_mark;
                    }
                break;}



                case '#': { // inline comment
                    Lexem predef = lex_none;

                    if (NEXTCHAR == '{' && state -> stack -> touch() == lex_string_continue) {
                        ++state -> next_offset;
                    } else {
                        bool ended = false;
                        predef = lex_inline_commentary;

                        while(!ended) {
                            ++state -> buffer;

                            switch(CURRCHAR) {
                                case 0: { ended = true; break;}
                            }
                        }
                    }

                    if (!cutWord(state, predef))
                        goto exit;
                break;}



                case '-': {
                    if (NEXTCHAR == '>' || NEXTCHAR == '=') { // lambda
                        ++state -> next_offset;
                    }

                    if (!cutWord(state))
                        goto exit;
                break;}



                case '+': {
                    if (NEXTCHAR == '=')
                        ++state -> next_offset;

                    if (!cutWord(state))
                        goto exit;
                break;}



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
                            case 'x': { predef = lex_number_hex; break; }
                            case 'b': { predef = lex_number_bin; break; }
                            case '1':
                            case '2':
                            case '3':
                            case '4':
                            case '5':
                            case '6':
                            case '7':
                            case '8':
                            case '9': { predef = lex_number_oct; break; }
                            default: {
                                ended = true;
                                predef = lex_number_dec;
                            }
                        }

                        ++state -> buffer;
                    } else predef = lex_number_dec;

                    bool is_valid = predef != lex_number_hex && predef != lex_number_bin;

                    while(!ended) {
                        ++state -> buffer;

                        switch(*window) {
                            case '.': {
                                if ((predef & lex_number_float) == lex_number_float)
                                    ended = true;
                                else
                                    predef = lex_number_float;
                            break;}

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
                                if (predef != lex_number_hex) {
                                    int word_length = window - prev;
                                    lighter -> setFormat(
                                        state -> index - word_length,
                                        word_length,
                                        HighlightFormatFactory::obj().getFormatFor(lex_error)
                                    );
//                                    lexems -> next = new LexError(state -> index, window - prev, QByteArrayLiteral("Error in number: wrong literal"));
                                    goto exit;
                                } else is_valid = true;
                            break;}

                            case 'e':
                            case 'E': {
                                if (predef < lex_number_dec) {
                                    int word_length = window - prev;
                                    lighter -> setFormat(
                                        state -> index - word_length,
                                        word_length,
                                        HighlightFormatFactory::obj().getFormatFor(lex_error)
                                    );
//                                    lexems -> next = new LexError(state -> index, window - prev, QByteArrayLiteral("Error in number: exponent part available only for decimals"));
                                    goto exit;
                                } else if (predef == lex_number_dec) {
                                    if (has_exp_part) {
                                        int word_length = window - prev;
                                        lighter -> setFormat(
                                            state -> index - word_length,
                                            word_length,
                                            HighlightFormatFactory::obj().getFormatFor(lex_error)
                                        );
//                                        lexems -> next = new LexError(state -> index, window - prev, QByteArrayLiteral("Error in number: double exponent part"));
                                    } else {
                                        has_exp_part = true;

                                        if (NEXTCHAR == '-' || NEXTCHAR == '+') {
                                            ++state -> buffer;
                                        }
                                    }
                                }
                                else is_valid = true;
                            break;}

                            case '8':
                            case '9': {
                                if (predef < lex_number_dec) {
                                    int word_length = window - prev;
                                    lighter -> setFormat(
                                        state -> index - word_length,
                                        word_length,
                                        HighlightFormatFactory::obj().getFormatFor(lex_error)
                                    );

//                                    lexems -> next = new LexError(state -> index, window - prev, QByteArrayLiteral("Error in number: 0-7 literals only"));
                                    goto exit;
                                }
                            break;}


                            case '2':
                            case '3':
                            case '4':
                            case '5':
                            case '6':
                            case '7': {
                                if (predef < lex_number_oct) {
                                    int word_length = window - prev;
                                    lighter -> setFormat(
                                        state -> index - word_length,
                                        word_length,
                                        HighlightFormatFactory::obj().getFormatFor(lex_error)
                                    );

//                                    lexems -> next = new LexError(state -> index, window - prev, QByteArrayLiteral("Error in number: 0,1 literals only"));
                                    goto exit;
                                }
                            break;}

                            case '0':
                            case '1': { is_valid = true; }
                            case '_': { break;}

                            default: ended = true;
                        }
                    }

                    if (!is_valid) { // if is hex or is bin and does not have any value: 0x or 0b
                        int word_length = window - prev;
                        lighter -> setFormat(
                            state -> index - word_length,
                            word_length,
                            HighlightFormatFactory::obj().getFormatFor(lex_error)
                        );
                    }

                    if (!cutWord(state, predef))
                        goto exit;
                break;}



                case '*': {
                    if (NEXTCHAR == '*' || NEXTCHAR == '=')
                        ++state -> next_offset;

                    if (!cutWord(state))
                        goto exit;
                break;}



                case '%': {
                    if (NEXTCHAR == '=')
                        ++state -> next_offset;

                    if (!cutWord(state))
                        goto exit;
                break;}




                case '/': {
                    if (NEXTCHAR == '=')
                        ++state -> next_offset;
                    else {
                        switch(state -> new_line_state) {                       
                            case lex_method: {

                            }
                            case lex_key:
                            case lex_wrap_start:
                            case lex_unary_operator:
                            case lex_binary_operator:
                            case lex_none: {
                                state -> stack -> push(lex_regexp_start);

                                handle_regexp:
                                    bool ended = false;
                                    bool out_req = false;
                                    bool def_required = false;

                                    while(!ended && !out_req) {
                                        ++state -> buffer;

                                        switch(CURRCHAR) {
                                            case '#': {
                                                if (NEXTCHAR == '{') {
                                                    def_required = ended = true;
                                                }
                                            break;}

                                            case '/': {
                                                if (PREVCHAR != '\\') {
                                                    ended = true;
                                                }
                                            break;}

                                            case 0: {
                                                out_req = true;
                                            break;}
                                        }
                                    }


                                    ended = false;

                                    while(!ended && !out_req) {
                                        ++state -> buffer;

                                        switch(CURRCHAR) {
                                            case 'm': // Treat a newline as a character matched by .
                                            case 'i': // Ignore case
                                            case 'x': // Ignore whitespace and comments in the pattern
                                            case 'o': // Perform #{} interpolation only once
                                            case 'u': // encoding:  UTF-8
                                            case 'e': // encoding:  EUC-JP
                                            case 's': // encoding:  Windows-31J
                                            case 'n': // encoding:  ASCII-8BIT
                                                { break;}
                                            case 0: {
                                                out_req = true;
                                            break;}
                                            default: {
                                                ended = true;
                                            }
                                        }
                                    }


                                if (!cutWord(state, out_req ? lex_regexp_continue : lex_regexp_end))
                                    goto exit;

                                if (def_required) { // INFO: patch for interpolation
                                    state -> stack -> push(lex_regexp_continue);
                                }

                                goto next_step;
                            break;}
                            default:;
                        }
                    }

                    if (!cutWord(state))
                        goto exit;
                break;}



                case '@': {
                    if (NEXTCHAR == '@')
                        ++state -> buffer;

                    cutWord(state);
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

                    if (has_match) {
                        if (!cutWord(state))
                            goto exit;
                    } else
                        goto iterate;
                break;}


                case 0: {
                    cutWord(state);
                    goto exit;
                break;}


                default:
                    iterate:
                        // Ruby identifier names may consist of alphanumeric characters and the
                        //  underscore character ( _ ).
                        // check if word isWord(*window)
                        ++state -> buffer;
            }
        }

        exit: return status;
    }

public:
    inline FormatType format() const { return ft_rb; }
};

#endif // LEXER_RUBY_H
