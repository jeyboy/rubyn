#include "lexer_frontend_ruby.h"

#include "lexer/lexer_control.h"
#include "lexer/ruby/grammar_ruby.h"
#include "lexer/ruby/predefined_ruby.h"

using namespace Ruby;

void LexerFrontend::identifyWordType(LexerControl * state) {
    switch(SCHAR0) {
        case ':': { state -> lex_word = lex_symbol; break;}
        case '$': { state -> lex_word = lex_var_global; break;}
        case '@': {
            if (SCHAR1 == '@')
                state -> lex_word = lex_var_object;
            else
                state -> lex_word = lex_var_instance;
        break;}
        default: {
            if (ECHAR_PREV1 == ':')
                state -> lex_word = lex_symbol;
        }
    }
}

void LexerFrontend::registerVariable(LexerControl * state) {
//    if (!state -> scope -> hasVar(state -> cached)) {
//        state -> scope -> addVar(
//            state -> cached,
//            new FilePoint(state -> lex_word, 0, 0, state -> cached_str_pos)
//        );
//    }
//    else state -> lex_word = state -> scope -> varType(state -> cached);
}

void LexerFrontend::translateState(LexerControl * state) {
    StateLexem new_state = state -> grammar -> translate(state -> lex_prev_word, state -> lex_delimiter);

    if (new_state == lex_error) {
        state -> lightWithMessage(
            lex_error,
            ERROR_STATE(QByteArrayLiteral("Wrong prev delimiter satisfy state!!!"), state -> lex_prev_word, state -> lex_delimiter)
        );
        //return false;
    }

    state -> lex_prev_word = new_state;

    new_state = state -> grammar -> translate(state -> lex_prev_word, state -> lex_word);

    if (new_state == lex_error) {
        state -> lightWithMessage(
            lex_error,
            ERROR_STATE(QByteArrayLiteral("Wrong token state!!!"), state -> lex_prev_word, state -> lex_word)
        );
        //return false;
    }

    state -> lex_word = new_state;
}

bool LexerFrontend::cutWord(LexerControl * state, const StateLexem & predefined_lexem) {
    bool has_predefined = predefined_lexem != lex_none;

    state -> cachingPredicate(has_predefined);

     if (state -> cached_length || has_predefined) {
        state -> lex_word =
            has_predefined ? predefined_lexem : Predefined::obj().lexem(state -> cached);

        if (state -> cached_length) {
            if (state -> lex_word == lex_word)
                identifyWordType(state);

            Identifier highlightable = state -> grammar -> toHighlightable(state -> lex_word);
            if (highlightable != hid_none)
                state -> light(highlightable);
        }

        translateState(state);

        if (state -> cached_length) {
            if (state -> lex_word == lex_word)
                registerVariable(state);

            Identifier highlightable = state -> grammar -> toHighlightable(state -> lex_word);
            if (highlightable == hid_none) {
                highlightable = state -> grammar -> toHighlightable(state -> lex_prev_word);
            }

            if (highlightable != hid_none)
                state -> light(highlightable);
        }

        state -> attachToken(state -> lex_word);
    }
    else state -> lex_word = lex_none;

    if (state -> next_offset) {
        state -> cachingDelimiter();
        state -> lex_delimiter = Predefined::obj().lexem(state -> cached);

        if (state -> lex_word == lex_none) {
            StateLexem new_state =
                state -> grammar -> translate(state -> lex_prev_delimiter, state -> lex_delimiter);

            if (new_state == lex_error) {
                state -> lightWithMessage(
                    lex_error,
                    ERROR_STATE(QByteArrayLiteral("Wrong delimiter satisfy state!!!"), state -> lex_prev_delimiter, state -> lex_delimiter)
                );
                //return false;
            }

            state -> lex_delimiter = new_state;


            state -> replaceToken(state -> lex_delimiter);
        }
        else {
            state -> attachToken(state -> lex_delimiter);
        }
    }

    state -> dropCached();

    return true;
}


bool LexerFrontend::parseContinious(LexerControl * state) {
    if (state -> stack_token) {
        switch(state -> stack_token -> lexem) {
            case lex_string_start:
            case lex_string_continue: { return parseString(state); }

            case lex_estring_start:
            case lex_estring_continue: { return parseEString(state); }


            case lex_regexp_start:
            case lex_regexp_continue: { return parseRegexp(state); }

            case lex_percent_presentation_start:
            case lex_percent_presentation_continue:
            case lex_epercent_presentation_start:
            case lex_epercent_presentation_continue: { return parsePercentagePresenation(state); }

            case lex_commentary_start:
            case lex_commentary_continue: { return parseComment(state); }
            case lex_cheredoc_start:
            case lex_cheredoc_continue:
            case lex_cheredoc_intended_start:
            case lex_cheredoc_intended_continue:
            case lex_eheredoc_start:
            case lex_eheredoc_continue:
            case lex_eheredoc_intended_start:
            case lex_eheredoc_intended_continue:
            case lex_heredoc_start:
            case lex_heredoc_continue:
            case lex_heredoc_intended_start:
            case lex_heredoc_intended_continue: { return parseHeredoc(state); }

            case lex_command_start:
            case lex_command_continue: { return parseCommand(state); }

            default:;
        };
    }

    return true;
}

bool LexerFrontend::parseNumber(LexerControl * state) {
    //    +3
    //    3.2e23
    //    -4.70e+9
    //    -.2E-4
    //    -7.6603
    //    -4.70e+9

    state -> next_offset = 0;
    bool ended = false, has_exp_part = false;
    StateLexem predef = lex_none;

    if (ECHAR0 == '0') {
        switch(ECHAR1) {
            case 'X':
            case 'x': { predef = lex_hex; break; }
            case 'B':
            case 'b': { predef = lex_bin; break; }
            case 'o':
            case 'O': { predef = lex_oct; break; }
            case 'd':
            case 'D': { predef = lex_dec; break; }
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': { predef = lex_dec; break;}
            default: {
                ended = true;
                predef = lex_dec;
            }
        }

        ++state -> buffer;
    } else predef = lex_dec;

    bool is_valid = predef != lex_hex && predef != lex_bin;

    while(!ended) {
        ++state -> buffer;

        switch(ECHAR0) {
            case '.': {
                if (predef == lex_float)
                    ended = true;
                else
                    predef = lex_float;
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
                if (predef != lex_hex) {
                    state -> cacheAndLightWithMessage(
                        lex_error,
                        QByteArrayLiteral("Error in number: wrong literal")
                    );

                    return false;
                } else is_valid = true;
            break;}

            case 'e':
            case 'E': {
                if (predef < lex_dec) {
                    state -> cacheAndLightWithMessage(
                        lex_error,
                        QByteArrayLiteral("Error in number: exponent part available only for decimals")
                    );

                    return false;
                } else if (predef >= lex_dec) {
                    if (has_exp_part) {
                        state -> cacheAndLightWithMessage(
                            lex_error,
                            QByteArrayLiteral("Error in number: double exponent part")
                        );
                    } else {
                        has_exp_part = true;

                        if (ECHAR1 == '-' || ECHAR1 == '+') {
                            ++state -> buffer;
                        }
                    }
                }
                else is_valid = true;
            break;}

            case '8':
            case '9': {
                if (predef < lex_dec) {
                    state -> cacheAndLightWithMessage(
                        lex_error,
                        QByteArrayLiteral("Error in number: 0-7 literals only")
                    );

                    return false;
                }
            break;}


            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7': {
                if (predef < lex_oct) {
                    state -> cacheAndLightWithMessage(
                        lex_error,
                        QByteArrayLiteral("Error in number: 0,1 literals only")
                    );

                    return false;
                }
            break;}

            case '0':
            case '1': { is_valid = true; }
            case '_': { break;}

            default: ended = true;
        }
    }

    if (!is_valid) { // if is hex or is bin and does not have any value: 0x or 0b
        state -> cacheAndLightWithMessage(
            lex_error,
            QByteArrayLiteral("Error in number: must have value")
        );

        return false;
    }

    return cutWord(state, predef);
}

bool LexerFrontend::parseString(LexerControl * state) {
    StateLexem lex = lex_none;

    while(lex == lex_none) {
        switch(ECHAR0) {
            case '\'': {
                if (ECHAR_PREV1 != '\\') {
                    ++state -> buffer;
                    lex = lex_string_end;
                }
            break;}

            case 0: {
                lex = lex_string_continue;
                break;
            }
        }

        ++state -> buffer;
    }


    return cutWord(state, lex); //out_req ? lex_string_continue : lex_string_end);
}

bool LexerFrontend::parseEString(LexerControl * state) {
    bool ended = false;
    bool out_req = false;
    bool def_required = false;
    state -> next_offset = 0;

    while(!ended && !out_req) {
        ++state -> buffer;

        switch(ECHAR0) {
            case '#': {
                if ((def_required = ended = ECHAR1 == '{')) {
                    state -> next_offset += 2;
                    state -> setStatus(LexerControl::ls_estring_interception);
                }
            break; }

            case '"': {
                if (ECHAR_PREV1 != '\\') {
                    ++state -> buffer;
                    ended = true;
                    state -> setStatus(LexerControl::ls_handled);
                }
            break;}

            case 0: {
                out_req = true;
                state -> setStatus(LexerControl::ls_estring);
                break;
            }
        }
    }

    return cutWord(state, out_req ? lex_estring_continue : (def_required ? lex_estring_interception : lex_estring_end));
}

bool LexerFrontend::parseCommand(LexerControl * state) {
    bool ended = false;
    bool out_req = false;
    bool def_required = false;
    state -> next_offset = 0;

    while(!ended && !out_req) {
        ++state -> buffer;

        switch(ECHAR0) {
            case '#': {
                if ((def_required = ended = ECHAR1 == '{')) {
                    ++state -> next_offset;
                    state -> setStatus(LexerControl::ls_command);
                }
            break; }

            case '`': {
                if (ECHAR_PREV1 != '\\') {
                    ++state -> buffer;
                    ended = true;
                    state -> setStatus(LexerControl::ls_handled);
                }
            break;}

            case 0: {
                out_req = true;
                state -> setStatus(LexerControl::ls_command);
                break;
            }
        }
    }

    bool res = cutWord(state, out_req ? lex_command_continue : (def_required ? lex_command_interception : lex_command_end));

//    if (def_required)
//        state -> stack -> push(lex_command_continue);

    return res;
}

bool LexerFrontend::parsePercentagePresenation(LexerControl * state) {
    TokenCell * stack_state = state -> stack_token;

    if (!stack_state || !stack_state -> data) {
        state -> cacheAndLightWithMessage(lex_error, QByteArrayLiteral("Wrong stack state"));
        return true; // false;
    }

    const char blocker = stack_state -> data -> operator[](0);

    if (isAlphaNum(blocker)) {
        state -> cacheAndLightWithMessage(lex_error, QByteArrayLiteral("Wrong limiter for construction. Must be any non alpha numeric"));
        return true; // false;
    }

    switch(stack_state -> lexem) {
        case lex_percent_presentation_start:
        case lex_percent_presentation_continue: {
            while(true) {
                switch(ECHAR0) {
                    case 0: {
                        state -> setStatus(LexerControl::ls_percentage_presentation);
                        return cutWord(state, lex_percent_presentation_continue);
                    break;}

                    default: {
                        if (ECHAR0 == blocker && ECHAR_PREV1 != '\\') {
                            ++state -> buffer;
                            state -> next_offset = 0;
                            state -> setStatus(LexerControl::ls_handled);
                            return cutWord(state, lex_percent_presentation_end);
                        }
                    }
                }

                ++state -> buffer;
            }
        break;}

        case lex_epercent_presentation_start:
        case lex_epercent_presentation_continue: {
            while(true) {
                switch(ECHAR0) {
                    case 0: {
                        state -> setStatus(LexerControl::ls_epercentage_presentation);
                        return cutWord(state, lex_epercent_presentation_continue);
                    break;}

                    case '#': {
                        if (ECHAR1 == '{') {
                            ++state -> next_offset;
//                            state -> stack -> replace(lex_epercent_presentation_continue, false);
                            return cutWord(
                                state,
                                Grammar::obj().toInterceptor(state -> stack_token -> lexem)
                            );
                        }
                    break;}

                    default: {
                        if (ECHAR0 == blocker && ECHAR_PREV1 != '\\') {
                            ++state -> buffer;
                            state -> next_offset = 0;
                            state -> setStatus(LexerControl::ls_handled);
                            return cutWord(state, lex_epercent_presentation_end);
                        }
                    }
                }

                ++state -> buffer;
            }
        break;}

        default: state -> cacheAndLightWithMessage(lex_error, QByteArrayLiteral("Wrong stack state for percent presentation"));
    }

    return true;
}

bool LexerFrontend::parseHeredoc(LexerControl * state) {
    if (!state -> stack_token || !state -> stack_token -> data) {
        state -> cacheAndLightWithMessage(lex_error, QByteArrayLiteral("Wrong stack status for heredoc content"));
        return true; // false;
    }

    QByteArray stop_token = *state -> stack_token -> data;

    if (state -> isBufferStart()) {
        switch(state -> stack_token -> lexem) {
            case lex_heredoc_intended_continue:
            case lex_eheredoc_intended_continue:
            case lex_cheredoc_intended_continue: {
                --state -> buffer;
                while(isBlank(*++state -> buffer)) ++state -> prev;
            }

            case lex_heredoc_continue:
            case lex_eheredoc_continue:
            case lex_cheredoc_continue: {
                int token_length = stop_token.length();

                if (QByteArray(state -> buffer, token_length) == stop_token) {
//                    state -> stack -> drop();
                    state -> buffer += token_length;
                    state -> setStatus(LexerControl::ls_handled);
                    return cutWord(state, lex_heredoc_mark);
                }
            break;}

            default: state -> cacheAndLightWithMessage(lex_error, QByteArrayLiteral("Wrong stack status for heredoc content"));
        }
    }

    switch(state -> stack_token -> lexem) {
        case lex_heredoc_continue:
        case lex_heredoc_intended_continue: { state -> moveBufferToEnd(); break;}

        case lex_eheredoc_intended_continue:
        case lex_cheredoc_intended_continue:
        case lex_eheredoc_continue:
        case lex_cheredoc_continue: {
            bool ended = false;

            while(!ended) {
                switch(ECHAR0) {
                    case 0: {
                        ended = true;
                    break;}

                    case '#': {
                        if (ECHAR1 == '{') {
                            ++state -> next_offset;
                            return cutWord(state, Grammar::obj().toInterceptor(state -> stack_token -> lexem));
                        }
                    }

                    default: ++state -> buffer;
                }
            }
        break;}
        default:;
    }


    switch(state -> stack_token -> lexem) {
        case lex_heredoc_continue: { state -> setStatus(LexerControl::ls_heredoc); break;}
        case lex_heredoc_intended_continue: { state -> setStatus(LexerControl::ls_heredoc_intended); break;}
        case lex_eheredoc_intended_continue: { state -> setStatus(LexerControl::ls_eheredoc_intended); break;}
        case lex_cheredoc_intended_continue: { state -> setStatus(LexerControl::ls_cheredoc_intended); break;}
        case lex_eheredoc_continue: { state -> setStatus(LexerControl::ls_eheredoc); break;}
        case lex_cheredoc_continue: { state -> setStatus(LexerControl::ls_cheredoc); break;}
        default:;
    }
    return cutWord(state, lex_heredoc_continue);
}

bool LexerFrontend::parseRegexp(LexerControl * state) {
    bool ended = false;
    bool out_req = false;
    bool def_required = false;

    while(!ended && !out_req) {
        ++state -> buffer;

        switch(ECHAR0) {
            case '#': {
                if ((def_required = ended = ECHAR1 == '{'))
                    ++state -> next_offset;
            break;}

            case '/': {
                ended = ECHAR_PREV1 != '\\';
                state -> setStatus(LexerControl::ls_handled);
            break;}

            case 0: {
                out_req = true;
                state -> setStatus(LexerControl::ls_regexp);
            break;}
        }
    }

    ended = false;

    while(!ended && !out_req) {
        ++state -> buffer;

        switch(ECHAR0) {
            case 'm': // Treat a newline as a character matched by .
            case 'i': // Ignore case
            case 'x': // Ignore whitespace and comments in the pattern
            case 'o': // Perform #{} interpolation only once
            case 'u': // encoding:  UTF-8
            case 'e': // encoding:  EUC-JP
            case 's': // encoding:  Windows-31J
            case 'n': // encoding:  ASCII-8BIT
                { break;}
            case 0: { ended = true; break; }
            default: { ended = true; } // need to check current char - if its eql to letter then need to show error
        }
    }

    if (!cutWord(state, out_req ? lex_regexp_continue : (def_required ? lex_regexp_interception : lex_regexp_end)))
        return false;

//    if (def_required)
//        state -> stack -> push(lex_regexp_continue);

    return true;
}

bool LexerFrontend::parseComment(LexerControl * state) {
    bool is_ended = false;

    if (state -> isBufferStart()) {
        if (ECHAR0 == '=' && ECHAR1 == 'e' && ECHAR2 == 'n' && ECHAR3 == 'd') {
            is_ended = true;
            state -> buffer += 4;
            cutWord(state);
        }
    }

    if (!is_ended) {
//                                    state -> stack -> push(lex_commentary_start);
        state -> moveBufferToEnd();
        state -> next_offset = 0;
        state -> setStatus(LexerControl::ls_comment);

        cutWord(state, lex_commentary_continue);
        return false;
//                                    state -> stack -> push(lex_commentary_continue);
    }

    return true;
}

void LexerFrontend::lexicate(LexerControl * state) {
//        a + b is interpreted as a.+(b)
//        a + b is interpreted as a+b ( Here a is a local variable)
//        a  +b is interpreted as a(+b) ( Here a is a method call)

//        Ruby interprets semicolons and newline characters as the ending of a statement.
//        However, if Ruby encounters operators, such as +, −, or backslash at the end of a line,
//        they indicate the continuation of a statement.

    //    case ' ': {
    //        StateLexem status = lex_blank;

    //        if (ECHAR1 == ' ') {
    //            status = lex_blanks;
    //            int iter = 1;

    //            do { ++state -> next_offset; }
    //            while(*(state -> buffer + ++iter) == ' ');
    //        }

    //        if(!cutWord(state, status)) goto exit;
    //    break;}

    if (!parseContinious(state))
        goto exit;

    while(true) {
        switch(ECHAR0) {
            case ' ':
            case '\t':
            case ',':
            case '^':
            case '~':
            case '(':
            case ')':
            case ';':
            case '\r':
            case '\n':
            case '\v': {
                if(!cutWord(state)) goto exit;
            break;}


            case '.': {
                if (ECHAR1 == '.') { // is range
                    ++state -> next_offset;

                    if (ECHAR2 == '.') // is range with exclusion
                        ++state -> next_offset;
                }

                if (!cutWord(state)) goto exit;
            break;}


            case '`': {
                state -> attachToken(lex_command_start, true);
                state -> next_offset = 0;
                ++state -> buffer;

                if (!parseCommand(state)) goto exit;
            break;}


            case '\'': {
                state -> attachToken(lex_string_start, true);
                state -> next_offset = 0;
                ++state -> buffer;

                if (!parseString(state)) goto exit;
            break;}


            case '"': {
                state -> attachToken(lex_estring_start, true);
                state -> next_offset = 0;
                ++state -> buffer;

                if (!parseEString(state)) goto exit;
            break;}


            case ':': {
                if (ECHAR1 == ':')
                    ++state -> next_offset;
                else { // if we have deal with symbol
                    if (isWord(ECHAR_PREV1)) {
                        ++state -> buffer;
                        state -> next_offset = 0;
                    } else {
                        if (state -> strLength() == 0 && isWord(ECHAR1))
                            goto iterate;
                    }
                }

                if (!cutWord(state)) goto exit;
            break;}


            case '=': {
                if (ECHAR1 == '~')
                    ++state -> next_offset;
                else if (ECHAR1 == '=') {// ==
                    ++state -> next_offset;

                    if (ECHAR1 == '=') // ===
                        ++state -> next_offset;
                }
                else if (ECHAR1 == 'b') { // =begin
                   if (ECHAR2 == 'e' && ECHAR3 == 'g' &&
                        ECHAR4 == 'i' && ECHAR5 == 'n')
                   {
                        state -> buffer += 6;

                        state -> attachToken(lex_commentary_start);
                        // state -> stack -> push(lex_commentary_start);

                        parseComment(state);
                        goto exit;
                   }
                }

                if (!cutWord(state)) goto exit;
            break;}


            case '|': {
                if (ECHAR1 == '|')
                    ++state -> next_offset;

                if (ECHAR1 == '=')
                    ++state -> next_offset;

                if (!cutWord(state)) goto exit;
            break;}


            case '&': {
                if (ECHAR1 == '&' || ECHAR1 == '.')
                    ++state -> next_offset;

                if (!cutWord(state)) goto exit;
            break;}


            case '!': {
                if (isAlphaNum(ECHAR_PREV1))
                    goto iterate;

                if (ECHAR1 == '~' || ECHAR1 == '=')
                    ++state -> next_offset;

                if (!cutWord(state)) goto exit;
            break;}


            case '?': {
                if (isAlphaNum(ECHAR_PREV1)) goto iterate;

                StateLexem st = lex_none;

//                bool is_spec_sym = ECHAR1 == '\\';

//                if ((!is_spec_sym && !isAlphaNum(ECHAR3)) || (is_spec_sym && !isAlphaNum(ECHAR4))) {
//                    st = lex_dec;

//                    if (is_spec_sym)
//                        state -> buffer += 3;
//                    else
//                        state -> buffer += 2;
//                }

                if (!cutWord(state, st)) goto exit;
            break;}


            case '<': {
                StateLexem lex = lex_none;

                if (ECHAR1 == '<') {
                    ++state -> next_offset;

                    if (!isBlank(ECHAR2) && (state -> isBufferStart() || !isWord(ECHAR_PREV1))) {
                        const char * curr = state -> buffer + 2;
                        bool is_intended = false;

                        if (*curr == '-' || *curr == '~') {
                            ++state -> next_offset;
                            curr++;
                            is_intended = true;
                        }

                        const char * control = curr;
                        bool is_simple = *curr == '\'';
                        bool is_command = *curr == '`';
                        bool is_quoted = is_simple || is_command || *curr == '"';

                        lex =
                            is_simple ?
                                is_intended ? lex_heredoc_intended_mark : lex_heredoc_mark
                                  :
                                is_command ?
                                    is_intended ? lex_cheredoc_intended_mark : lex_cheredoc_mark
                                        :
                                    is_intended ? lex_eheredoc_intended_mark : lex_eheredoc_mark;

                        if (is_quoted) {
                            bool ended = false;

                            while(!ended) {
                                switch(*++curr) {
                                    case '\'':
                                    case '"':
                                    case '`': {
                                        if (*control == *curr)
                                            ended = true;
                                    break;}

                                    case 0: {
                                        state -> cacheAndLightWithMessage(lex_error, QByteArrayLiteral("Heredoc mark is not closed"));
                                        ended = true;
                                    break;}
                                }
                            }
                            ++control;
                        }
                        else while(isWord(*(++curr)));


                        QByteArray doc_name(control, curr - control);
                        state -> buffer += curr - state -> buffer + (is_quoted ? 1 : 0);
                        state -> next_offset = 0;

                        //INFO: stacked heredocs going in revert order so we must to insert new heredoc before previous if heredocs is stacked
                        StateLexem top = Grammar::obj().toHeredocContinious(state -> stack_token -> lexem);

                        if (top != lex_none) {
//                            STACK_INT_TYPE level = 0;
//                            while(Grammar::obj().toHeredocContinious(state -> stack -> touch(++level)) != lex_none);
//                            state -> stack -> pushToLevel(level, lex, doc_name);
                        }
                        else {
                            int y = 0;

//                            state -> stack -> push(lex, doc_name);

                            state -> setStatus(
                                is_simple ?
                                    is_intended ? LexerControl::ls_heredoc_intended : LexerControl::ls_heredoc
                                      :
                                    is_command ?
                                        is_intended ? LexerControl::ls_cheredoc_intended : LexerControl::ls_cheredoc
                                            :
                                        is_intended ? LexerControl::ls_eheredoc_intended : LexerControl::ls_eheredoc
                            );
                        }
                    }
                } else {
                    if (ECHAR1 == '=') {
                        ++state -> next_offset;

                        if (ECHAR2 == '>')
                            ++state -> next_offset;
                    }
                }

                if (!cutWord(state, lex)) goto exit;
            break;}


            case '>': {
                if (ECHAR1 == '>' || ECHAR1 == '=')
                    ++state -> next_offset;

                if (!cutWord(state)) goto exit;
            break;}


            case '[': {
                if (!cutWord(state)) goto exit;
            break;}
            case ']': {
                if (!cutWord(state)) goto exit;
            break;}


            case '{': {
                if (!cutWord(state)) goto exit;
            break;}
            case '}': {
                if (!cutWord(state)) goto exit;

                StateLexem top = state -> stack_token -> lexem;
                StateLexem top_conv = Grammar::obj().fromContinious(top);

                if (top_conv != lex_none) { // after interpolation
//                    if (Grammar::obj().isStackDroppable(top))
//                        state -> stack -> pushToLevel(1, top_conv);

                    if (!parseContinious(state))
                        goto exit;
                }
            break;}


            case '#': { // inline comment
                StateLexem predef = lex_none;

                if (ECHAR1 == '{' && Grammar::obj().isInterpolable(state -> stack_token -> lexem)) {
                    ++state -> next_offset;
                } else {
                    predef = lex_inline_commentary;
                    state -> moveBufferToEnd();
                    state -> next_offset = 0;
                }

                if (!cutWord(state, predef)) goto exit;
            break;}


            case '-': {
                if (ECHAR1 == '>' || ECHAR1 == '=')
                    ++state -> next_offset;
                else if(isDigit(ECHAR1) && (state -> isBufferStart() || isBlank(ECHAR_PREV1))) {
                    goto parse_number;
                }

                if (!cutWord(state)) goto exit;
            break;}


            case '+': {
                if (ECHAR1 == '=')
                    ++state -> next_offset;
                else if(isDigit(ECHAR1) && (state -> isBufferStart() || isBlank(ECHAR_PREV1))) {
                    goto parse_number;
                }

                if (!cutWord(state)) goto exit;
            break;}


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
                if (isWord(ECHAR_PREV1))
                    goto iterate;

                parse_number:
                    if (!parseNumber(state)) goto exit;
            break;}


            case '*': {
                if (ECHAR1 == '*' || ECHAR1 == '=')
                    ++state -> next_offset;

                if (!cutWord(state)) goto exit;
            break;}


            case '%': {
                StateLexem res = lex_none;
                bool shorted = false;

                switch(ECHAR1) {
                    case '=': { ++state -> next_offset; break; }
                    case '/': shorted = true;
                    case 'l': // Interpolated Array of Symbols
                    case 'Q': // double quoted string
                    case 'r': // Regular Expression
                    case 'W': // Array of double quoted Strings
                    case 'x': // Backtick (capture subshell result)
                        { res = lex_epercent_presentation_start; break;}

                    case 'i': // Array of Symbols
                    case 'q': // single quoted string
                    case 's': // Symbol
                    case 'w': // Array of Strings
                        { res = lex_percent_presentation_start; break;}
                };

                if (res != lex_none) {
                    state -> next_offset = 0;
//                    state -> stack -> push(res, QByteArray(1, shorted ? '/' : Grammar::obj().percentagePresentationBlocker(ECHAR2)));

                    if (state -> buffer != state -> prev)
                        if (!cutWord(state, res))
                            goto exit;

                    state -> buffer += shorted ? 2 : 3;
                    if (!parsePercentagePresenation(state))
                        goto exit;
                } else {
                    if (!cutWord(state))
                        goto exit;
                }
            break;}


            case '/': {
                if (ECHAR1 == '=') {
                    ++state -> next_offset;

                    if (!cutWord(state)) goto exit;
                } else {
                    bool is_regexp = true; //state -> new_line_state != lex_predefined;

                    state -> next_offset = is_regexp ? 0 : 1;

                    if (!cutWord(state)) goto exit;

                    if (is_regexp) {
                        state -> attachToken(lex_regexp_start);
//                        state -> stack -> push(lex_regexp_start);

                        if (!parseRegexp(state)) goto exit;
                    }
                }
            break;}


            case '@': {
                if (ECHAR1 == '@')
                    ++state -> buffer;

                if (!cutWord(state)) goto exit;
            break;}


            case '$': {
                bool has_match = false;
                char next_char = ECHAR1;

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
                        const char & n1_char = ECHAR2;

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
                            if (!isAlphaNum(n1_char)) {
                                has_match = true;
                                state -> next_offset += 2;
                            }
                        } else if (isDigit(next_char)) { // $0-$99
                            int offset = 1;

                            if (isDigit(n1_char)) {
                                ++offset;
                            } else if (isAlpha(n1_char)) {
                                // raise error
                            }

                            state -> next_offset += offset;
                            has_match = true;
                        }
                    }
                }

                if (has_match) {
                    if (!cutWord(state)) goto exit;
                }
                else goto iterate;
            break;}


            case 0: {
                state -> next_offset = 0;
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

    exit:;
//        StateLexem replaceable = Grammar::obj().toHeredocContinious(state -> stack_token -> lexem);
//        if (replaceable != lex_none)
//            state -> stack -> replace(replaceable, false);
}

LexerFrontend::LexerFrontend() {}

LexerFrontend::~LexerFrontend() {}

void LexerFrontend::handle(const QString & text, Highlighter * lighter) {
    QTextBlock block = lighter -> currentBlock();
    QTextBlock prev_block = lighter -> prevBlock();

    BlockUserData * prev_udata = reinterpret_cast<BlockUserData *>(prev_block.userData());
    BlockUserData * udata = reinterpret_cast<BlockUserData *>(block.userData());

    lighter -> initBlockUserData(block, prev_udata, udata);

    LexerControl state(
        &Ruby::Grammar::obj(),
        udata,
        prev_udata && prev_udata -> stack_token ? prev_udata -> stack_token : udata -> token_begin,
        lighter
    );

    QByteArray text_val = text.toUtf8();
    const char * window = text_val.constData();
    state.setBuffer(window);

    lexicate(&state);

    int new_user_state = state.stack_token ? state.stack_token -> lexem : lex_none;
    block.setUserState(new_user_state);
    udata -> syncLine(state.stack_token, state.token, state.para, state.control_para);
}
