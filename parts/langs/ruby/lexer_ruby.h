#ifndef LEXER_RUBY_H
#define LEXER_RUBY_H

#include "parts/lexer/lexer.h"
#include "predefined_ruby.h"
#include "grammar_ruby.h"

#define ERROR_STATE(msg, lex1, lex2) msg + QByteArrayLiteral(" (") + Lexems::toStr(lex1) + QByteArrayLiteral(" VS ") + Lexems::toStr(lex2) + QByteArrayLiteral(")")

class LexerRuby : public Lexer {
    void identifyWordType(LexerState * state) {
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

    void registerVariable(LexerState * state) {
        if (!state -> scope -> hasVar(state -> cached)) {
            state -> scope -> addVar(
                state -> cached,
                new FilePoint(state -> lex_word, 0, 0, state -> cached_str_pos)
            );
        }
        else state -> lex_word = state -> scope -> varType(state -> cached);
    }

    void translateState(LexerState * state) {
        Lexem new_state = GrammarRuby::obj().translate(state -> lex_prev_word, state -> lex_delimiter);

        if (new_state == lex_error) {
            state -> lightWithMessage(
                lex_error,
                ERROR_STATE(QByteArrayLiteral("Wrong prev delimiter satisfy state!!!"), state -> lex_prev_word, state -> lex_delimiter)
            );
    //                return false;
        }

        state -> lex_prev_word = new_state;

        new_state = GrammarRuby::obj().translate(state -> lex_prev_word, state -> lex_word);

        if (new_state == lex_error) {
            state -> lightWithMessage(
                lex_error,
                ERROR_STATE(QByteArrayLiteral("Wrong token state!!!"), state -> lex_prev_word, state -> lex_word)
            );
    //                return false;
        }

        state -> lex_word = new_state;
    }

    bool cutWord(LexerState * state, const Lexem & predefined_lexem = lex_none) {
        bool has_predefined = predefined_lexem != lex_none;

        state -> cachingPredicate(has_predefined);

        if (state -> cached_length || has_predefined) {
            state -> lex_word =
                has_predefined ? predefined_lexem : PredefinedRuby::obj().lexem(state -> cached);

            Lexem prev_highlightable = lex_none;

            if (state -> cached_length) {


                if (state -> lex_word == lex_word)
                    identifyWordType(state);

                prev_highlightable = GrammarRuby::obj().toHighlightable(state -> lex_word);
            }

//            // translate state
            translateState(state);

            if (state -> cached_length) {
                if (state -> lex_word == lex_word)
                    registerVariable(state);

                Lexem highlightable = GrammarRuby::obj().toHighlightable(state -> lex_word);
                if (highlightable == lex_none)
                    highlightable = prev_highlightable;

                if (highlightable != lex_none)
                    state -> light(highlightable);
            }

            state -> attachToken(state -> lex_word);


//            Lexem cont_lexem = GrammarRuby::obj().fromContinious(state -> lex_word);

//            if (cont_lexem != lex_none) {
//                Lexem & top = state -> stack -> touch();

//                if (top == cont_lexem)
//                    state -> stack -> push(state -> lex_word);
//                else state -> lightWithMessage(lex_error, QByteArrayLiteral("Wrong state!!!"));
//            }
        }
        else state -> lex_word = lex_none;

        if (state -> next_offset) {
            state -> cachingDelimiter();
            state -> lex_delimiter = PredefinedRuby::obj().lexem(state -> cached);

            if (state -> lex_word == lex_none) {
                Lexem new_state =
                    GrammarRuby::obj().translate(state -> lex_prev_delimiter, state -> lex_delimiter);

                if (new_state == lex_error) {
                    state -> lightWithMessage(
                        lex_error,
                        ERROR_STATE(QByteArrayLiteral("Wrong delimiter satisfy state!!!"), state -> lex_prev_delimiter, state -> lex_delimiter)
                    );
            //                return false;
                }

                state -> lex_delimiter = new_state;


                state -> replaceToken(state -> lex_delimiter);
            }
            else {
                state -> attachToken(state -> lex_delimiter);
            }
        }

//        if (state -> lex_delimiter == lex_dot) {
//            switch(state -> sublastToken()) {
//                case lex_method_def_name: {
//                    state -> updateSubToken(lex_method_def_scope);
//                break;}

//                default:;
//            }
//        }

        state -> dropCached();

        return true;
    }

    bool parsePercentagePresenation(LexerState * state) {
        const char blocker = state -> stack -> dataForTop()[0];

        if (isAlphaNum(blocker)) {
            state -> cacheAndLightWithMessage(lex_error, QByteArrayLiteral("Wrong limiter for construction. Must be any non alpha numeric"));
            return true;
        }

        switch(state -> stack -> touch()) {
            case lex_percent_presentation_start:
            case lex_percent_presentation_continue: {
                while(true) {
                    switch(ECHAR0) {
                        case 0: {
                            state -> setStatus(LexerState::ls_percentage_presentation);
                            return cutWord(state, lex_percent_presentation_continue);
                        break;}

                        default: {
                            if (ECHAR0 == blocker && ECHAR_PREV1 != '\\') {
                                ++state -> buffer;
                                state -> next_offset = 0;
                                state -> stack -> drop();
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
                            state -> setStatus(LexerState::ls_epercentage_presentation);
                            return cutWord(state, lex_epercent_presentation_continue);
                        break;}

                        case '#': {
                            if (ECHAR1 == '{') {
                                ++state -> next_offset;
                                state -> stack -> replace(lex_epercent_presentation_continue, false);
                                return cutWord(state, GrammarRuby::obj().toInterceptor(state -> stack -> touch()));
                            }
                        break;}

                        default: {
                            if (ECHAR0 == blocker && ECHAR_PREV1 != '\\') {
                                ++state -> buffer;
                                state -> next_offset = 0;
                                state -> stack -> drop();
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

    bool parseHeredoc(LexerState * state) {
        QByteArray stop_token = state -> stack -> dataForTop();

        if (state -> isBufferStart()) {
            switch(state -> stack -> touch()) {
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
                        state -> stack -> drop();
                        state -> buffer += token_length;
                        return cutWord(state, lex_heredoc_mark);
                    }
                break;}

                default: state -> cacheAndLightWithMessage(lex_error, QByteArrayLiteral("Wrong stack status for heredoc content"));
            }
        }

        switch(state -> stack -> touch()) {
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
                                return cutWord(state, GrammarRuby::obj().toInterceptor(state -> stack -> touch()));
                            }
                        }

                        default: ++state -> buffer;
                    }
                }
            break;}
            default:;
        }


        switch(state -> stack -> touch()) {
            case lex_heredoc_continue: { state -> setStatus(LexerState::ls_heredoc); break;}
            case lex_heredoc_intended_continue: { state -> setStatus(LexerState::ls_heredoc_intended); break;}
            case lex_eheredoc_intended_continue: { state -> setStatus(LexerState::ls_eheredoc_intended); break;}
            case lex_cheredoc_intended_continue: { state -> setStatus(LexerState::ls_cheredoc_intended); break;}
            case lex_eheredoc_continue: { state -> setStatus( LexerState::ls_eheredoc); break;}
            case lex_cheredoc_continue: { state -> setStatus(LexerState::ls_cheredoc); break;}
            default:;
        }
        return cutWord(state, lex_heredoc_continue);
    }

    bool parseRegexp(LexerState * state) {
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
                case '/': { ended = ECHAR_PREV1 != '\\';  break;}
                case 0: {
                    out_req = true;
                    state -> setStatus(LexerState::ls_regexp);
                    break;
                }
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

        if (def_required)
            state -> stack -> push(lex_regexp_continue);

        return true;
    }
protected:
    void handle(LexerState * state) {
//        a + b is interpreted as a.+(b)
//        a + b is interpreted as a+b ( Here a is a local variable)
//        a  +b is interpreted as a(+b) ( Here a is a method call)

//        Ruby interprets semicolons and newline characters as the ending of a statement.
//        However, if Ruby encounters operators, such as +, −, or backslash at the end of a line,
//        they indicate the continuation of a statement.


        continue_mark:
            Lexem top = state -> stack -> touch();

            if (GrammarRuby::obj().isContinious(top)) {
                if (GrammarRuby::obj().isStackDroppable(top)) {
                    state -> stack -> drop();
                    --state -> buffer;
                }

                switch(top) {
                    case lex_string_continue: goto handle_string;
                    case lex_estring_continue: goto handle_estring;
                    case lex_regexp_continue: {
                        if (!parseRegexp(state))
                            goto exit;
                    break;}

                    case lex_percent_presentation_continue:
                    case lex_epercent_presentation_continue: {
                        if (!parsePercentagePresenation(state))
                            goto exit;
                    break;}

                    case lex_cheredoc_continue:
                    case lex_cheredoc_intended_continue:
                    case lex_eheredoc_continue:
                    case lex_eheredoc_intended_continue:
                    case lex_heredoc_continue:
                    case lex_heredoc_intended_continue: {
                        if (!parseHeredoc(state))
                            goto exit;
                    break;}
                    case lex_commentary_continue: goto handle_multiline_comment;
                    case lex_command_continue: goto handle_command;
                    default:;
                };
            }

        while(true) {
            switch(ECHAR0) {
                case ' ':
                case ',':
                case '^':
                case '~':
                case '(':
                case ')':
                case ';':
                case '\t':
                case '\r':
                case '\n':
                case '\v': {
                    if(!cutWord(state))
                        goto exit;
                break;}


                case '.': {
                    if (ECHAR1 == '.') { // is range
                        ++state -> next_offset;

                        if (ECHAR2 == '.') // is range with exclusion
                            ++state -> next_offset;
                    } /*else {
                        if (PREVCHAR == '$' || isDigit(next_char)) // is float or $.
                            goto iterate;
                    }*/

                    if (!cutWord(state))
                        goto exit;
                break;}


                case '`': {
                    state -> stack -> push(lex_command_start);

                    handle_command:
                        bool ended = false;
                        bool out_req = false;
                        bool def_required = false;
                        state -> next_offset = 0;

                        while(!ended && !out_req) {
                            ++state -> buffer;

                            switch(ECHAR0) {
                                case '#': {
                                    if ((def_required = ended = ECHAR1 == '{'))
                                        ++state -> next_offset;
                                break; }

                                case '`': {
                                    if (ECHAR_PREV1 != '\\') {
                                        ++state -> buffer;
                                        ended = true;
                                    }
                                break;}

                                case 0: {
                                    out_req = true;
                                    state -> setStatus(LexerState::ls_command);
                                    break;
                                }
                            }
                        }


                    if (!cutWord(state, out_req ? lex_command_continue : (def_required ? lex_command_interception : lex_command_end)))
                        goto exit;

                    if (def_required)
                        state -> stack -> push(lex_command_continue);
                break;}


                case '\'': {
                    state -> stack -> push(lex_string_start);

                    handle_string:
                        bool ended = false;
                        bool out_req = false;
                        state -> next_offset = 0;

                        while(!ended && !out_req) {
                            ++state -> buffer;

                            switch(ECHAR0) {
                                case '\'': {
                                    if (ECHAR_PREV1 != '\\') {
                                        ++state -> buffer;
                                        ended = true;
                                    }
                                break;}

                                case 0: {
                                    out_req = true;
                                    state -> setStatus(LexerState::ls_string);
                                    break;
                                }
                            }
                        }


                    if (!cutWord(state, out_req ? lex_string_continue : lex_string_end))
                        goto exit;
                break;}


                case '"': {
                    state -> stack -> push(lex_estring_start);

                    handle_estring:
                        bool ended = false;
                        bool out_req = false;
                        bool def_required = false;
                        state -> next_offset = 0;

                        while(!ended && !out_req) {
                            ++state -> buffer;

                            switch(ECHAR0) {
                                case '#': {
                                    if ((def_required = ended = ECHAR1 == '{'))
                                        ++state -> next_offset;
                                break; }

                                case '"': {
                                    if (ECHAR_PREV1 != '\\') {
                                        ++state -> buffer;
                                        ended = true;
                                    }
                                break;}

                                case 0: {
                                    out_req = true;
                                    state -> setStatus(LexerState::ls_estring);
                                    break;
                                }
                            }
                        }


                    if (!cutWord(state, out_req ? lex_estring_continue : (def_required ? lex_estring_interception : lex_estring_end)))
                        goto exit;

                    if (def_required)
                        state -> stack -> push(lex_estring_continue);
                break;}



                case ':': {
                    if (ECHAR1 == ':')
                        ++state -> next_offset;
                    else { // if we have deal with symbol
                        if (isWord(ECHAR_PREV1)) {
                            ++state -> buffer;
                            state -> next_offset = 0;
                        }
//                        else if (state -> lex_state > lex_undefined) {
//                            goto iterate;
//                        }
                    }

                    if (!cutWord(state))
                        goto exit;
                break;}



                case '=': {
                    if (ECHAR1 == 'b') { // =begin
                       if (ECHAR2 == 'e' && ECHAR3 == 'g' &&
                            ECHAR4 == 'i' && ECHAR5 == 'n') {
                                state -> buffer += 5;

                                handle_multiline_comment:
                                    bool ended = false;
                                    bool out_req = false;
                                    state -> stack -> push(lex_commentary_start);

                                    while(!ended && !out_req) {
                                        ++state -> buffer;

                                        switch(ECHAR0) {
                                            case '=': {
                                                if (ECHAR1 == 'e' && ECHAR2 == 'n' && ECHAR3 == 'd')
                                                    ended = true;
                                                    state -> buffer += 4;
                                            break;}

                                            case 0: {
                                                out_req = true;
                                                cutWord(state, lex_commentary_continue);
                                                state -> stack -> push(lex_commentary_continue);
                                                state -> setStatus(LexerState::ls_comment);

                                                goto exit;
                                            break;}

                                            default:;
                                        }
                                    }
                       }
                    } else if (ECHAR1 == 'e' && ECHAR2 == 'n' && ECHAR3 == 'd') {
                        state -> buffer += 4;
                        state -> next_offset = 0;
                    } else {
                        if (ECHAR1 == '~')
                            ++state -> next_offset;
                        else {
                            if (ECHAR1 == '=') // ==
                                ++state -> next_offset;

                            if (ECHAR1 == '=') // ===
                                ++state -> next_offset;
                        }
                    }

                    if (!cutWord(state))
                        goto exit;
                break;}



                case '|': {
                    if (ECHAR1 == '|')
                        ++state -> next_offset;

                    if (ECHAR1 == '=')
                        ++state -> next_offset;

                    if (!cutWord(state))
                        goto exit;
                break;}



                case '&': {
                    if (ECHAR1 == '&' || ECHAR1 == '.')
                        ++state -> next_offset;                   

                    if (!cutWord(state))
                        goto exit;
                break;}



                case '!': {
                    if (!isBlank(ECHAR_PREV1))
                        goto iterate;

                    if (ECHAR1 == '~' || ECHAR1 == '=')
                        ++state -> next_offset;

                    if (!cutWord(state))
                        goto exit;
                break;}



                case '?': {
                    if (!isBlank(ECHAR_PREV1))
                        goto iterate;

                    if (!cutWord(state))
                        goto exit;
                break;}



                case '<': {
                    Lexem lex = lex_none;

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
                            Lexem top = GrammarRuby::obj().toHeredocContinious(state -> stack -> touch());
                            if (top != lex_none) {
                                int level = 0;
                                while(GrammarRuby::obj().toHeredocContinious(state -> stack -> touch(++level)) != lex_none);
                                state -> stack -> pushToLevel(level, lex, doc_name);
                            }
                            else {
                                state -> stack -> push(lex, doc_name);
                                state -> setStatus(
                                    is_simple ?
                                        is_intended ? LexerState::ls_heredoc_intended : LexerState::ls_heredoc
                                          :
                                        is_command ?
                                            is_intended ? LexerState::ls_cheredoc_intended : LexerState::ls_cheredoc
                                                :
                                            is_intended ? LexerState::ls_eheredoc_intended : LexerState::ls_eheredoc
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

                    if (!cutWord(state, lex))
                        goto exit;
                break;}



                case '>': {
                    if (ECHAR1 == '>' || ECHAR1 == '=')
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
                    Lexem top_conv = GrammarRuby::obj().fromContinious(top);

                    if (top_conv != lex_none) { // after interpolation
                        if (GrammarRuby::obj().isStackDroppable(top))
                            state -> stack -> pushToLevel(1, top_conv);

                        goto continue_mark;
                    }
                break;}



                case '#': { // inline comment
                    Lexem predef = lex_none;
                    bool ended = false;

                    if (ECHAR1 == '{' && GrammarRuby::obj().isInterpolable(state -> stack -> touch())) {
                        ++state -> next_offset;
                    } else {
                        predef = lex_inline_commentary;

                        while(!ended) {
                            ++state -> buffer;

                            switch(ECHAR0) {
                                case 0: { ended = true; break;}
                            }
                        }

                        state -> next_offset = 0;
                    }

                    if (!cutWord(state, predef) || ended)
                        goto exit;
                break;}



                case '-': {
                    if (ECHAR1 == '>' || ECHAR1 == '=')
                        ++state -> next_offset;

                    if (!cutWord(state))
                        goto exit;
                break;}



                case '+': {
                    if (ECHAR1 == '=')
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
                    if (isWord(ECHAR_PREV1))
                        goto iterate;

                    bool ended = false, has_exp_part = false;
                    Lexem predef = lex_none;

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
                                if ((predef & lex_float) == lex_float)
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

                                    goto exit;
                                } else is_valid = true;
                            break;}

                            case 'e':
                            case 'E': {
                                if (predef < lex_dec) {
                                    state -> cacheAndLightWithMessage(
                                        lex_error,
                                        QByteArrayLiteral("Error in number: exponent part available only for decimals")
                                    );

                                    goto exit;
                                } else if (predef == lex_dec) {
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

                                    goto exit;
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
                        state -> cacheAndLightWithMessage(
                            lex_error,
                            QByteArrayLiteral("Error in number: must have value")
                        );

                        goto exit;
                    }

                    if (!cutWord(state, predef))
                        goto exit;
                break;}



                case '*': {
                    if (ECHAR1 == '*' || ECHAR1 == '=')
                        ++state -> next_offset;

                    if (!cutWord(state))
                        goto exit;
                break;}



                case '%': {
                    Lexem res = lex_none;
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
                        state -> stack -> push(res, QByteArray(1, shorted ? '/' : GrammarRuby::obj().percentagePresentationBlocker(ECHAR2)));

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

                        if (!cutWord(state))
                            goto exit;
                    } else {
                        bool is_regexp = true; //state -> new_line_state != lex_predefined;

                        state -> next_offset = is_regexp ? 0 : 1;

                        if (!cutWord(state))
                            goto exit;

                        if (is_regexp) {
                            state -> stack -> push(lex_regexp_start);

                            if (!parseRegexp(state))
                                goto exit;
                        }
                    }
                break;}



                case '@': {
                    if (ECHAR1 == '@')
                        ++state -> buffer;

                    cutWord(state);
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

        exit:
            Lexem replaceable = GrammarRuby::obj().toHeredocContinious(state -> stack -> touch());
            if (replaceable != lex_none)
                state -> stack -> replace(replaceable, false);
    }

public:
    inline FormatType format() const { return ft_rb; }
};

#endif // LEXER_RUBY_H
