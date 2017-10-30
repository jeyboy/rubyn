#ifndef LEXER_RUBY_H
#define LEXER_RUBY_H

#include "parts/lexer/lexer.h"
#include "predefined_ruby.h"
#include "grammar_ruby.h"

class LexerRuby : public Lexer {
//    bool checkStack(const Lexem & lex_flag, LexerState * state) {
//        if (state -> lex_state & lex_def || state -> lex_state & lex_start)
//            state -> stack -> push(state -> lex_state);
//        else if (state -> lex_state & lex_end) {
//            Lexem stack_top = state -> stack -> touch();

//            if (EXCLUDE_BIT(lex_flag, lex_end) == EXCLUDE_BIT(stack_top, lex_start))
//                state -> stack -> drop();
//            else {
//                state -> lightWithMessage(lex_error, QByteArrayLiteral("Wrong state!!!"));
//                return false;
//            }
//        }


////        if (lex_flag & lex_start) {
////            if (lex_flag & lex_chain) {
////                // INFO: if line is not empty then we have deal with inline branching
////                if (state -> new_line_state == lex_none)
////                    state -> stack -> push(lex_flag);
////            } else
////                state -> stack -> push(lex_flag);
////        } else if (lex_flag & lex_end) {
////            Lexem stack_top = state -> stack -> touch();
////            bool condition =
////                stack_top & lex_block ?
////                    lex_flag & lex_block
////                :
////                    EXCLUDE_BIT(lex_flag, lex_end) == EXCLUDE_BIT(stack_top, lex_start);


////            if (condition) {
////                state -> stack -> drop();
////            } else {
////                lighter -> setFormat(
////                    state -> index - word_length,
////                    state -> cached_str_length,
////                    HighlightFormatFactory::obj().getFormatFor(lex_error)
////                );
//////                APPEND_ERR(QByteArray::number(state -> stack -> touch()) + QByteArrayLiteral(" required, but ") + QByteArray::number(lex_flag) + QByteArrayLiteral(" received"));

////                return false;
////            }
////        } else if (lex_flag & lex_chain_block) {
////            Lexem stack_top = state -> stack -> touch();

////            if (stack_top & lex_chain_block)
////                state -> stack -> replace(lex_flag);
////            else
////                lighter -> setFormat(
////                    state -> index - word_length,
////                    state -> cached_str_length,
////                    HighlightFormatFactory::obj().getFormatFor(lex_error)
////                );

//////                APPEND_ERR(QByteArrayLiteral("Error in condition logic"));
////        }

//        return true;
//    }

//    bool cutWord(LexerState * state, const Lexem & predefined_lexem = lex_none) {
//        state -> cachingPredicate();

//        if (state -> cached_length) {
//            state -> lex_state =
//                predefined_lexem
//                    ?
//                        predefined_lexem
//                    :
//                        PredefinedRuby::obj().lexem(state -> cached);


//            if (state -> lex_state == lex_undefined) {
//                if (!state -> scope -> hasVar(state -> cached)) {
//                    Lexem & stack_top = state -> stack -> touch();

//                    if ((stack_top & lex_def) > lex_key) {
//                        state -> scope -> addVar(
//                            state -> cached,
//                            new FilePoint(
//                                stack_top == lex_class_def ? lex_class_def_name : lex_module_def_name,
//                                0, 0, state -> bufferPos()
//                            )
//                        );
//                        state -> stack -> replace(lex_block_start);
//                        state -> lex_state = lex_def_name;
//                    }
//                    else {
//                        switch(SCHAR0) { // INFO: determine type of word
//                            case ':': { state -> lex_state = lex_name_symbol; break;}
//                            case '$': { state -> lex_state = lex_name_global; break;}
//                            case '@': {
//                                if (SCHAR1 == '@')
//                                    state -> lex_state = lex_name_object;
//                                else
//                                    state -> lex_state = lex_name_instance;
//                            break;}
//                            default: {
//                                state -> lex_state =
//                                    (ECHAR_PREV1 == ':')
//                                        ?
//                                            lex_name_symbol
//                                        :
//                                            lex_name_local;
//                            }
//                        }

//                        if (state -> lex_state != lex_name_symbol)
//                            state -> scope -> addVar(
//                                state -> cached,
//                                new FilePoint(state -> lex_state, 0, 0, state -> bufferPos())
//                            );

//    //                    if (!state -> var_def_state)
//    //                         state -> stack -> push(lex_var_chain_start);

//    //                    state -> scope -> addUnregVar(state -> state -> cached, 0); // new FilePoint() // TODO: write me

//    //                    if (state -> var_def_state == state -> lex_state) {
//    //                        APPEND_ERR(QByteArrayLiteral("Error in variable def"));
//    //                        return false;
//    //                    }

//    //                    state -> var_def_state = state -> lex_state;
//                    }
//                }
//                else state -> lex_state = state -> scope -> varType(state -> cached);

//            } else {

////                if (state -> lex_state & lex_continue) { // TODO: check me
////                    Lexem top = state -> stack -> touch();

////                    if (top == state -> lex_state || top == EXCLUDE_BIT(state -> lex_state, lex_continue)) {
////                        state -> stack -> push(state -> lex_state);
////                    } else {
////                        state -> lightWithMessage(lex_error, QByteArrayLiteral("Wrong state!!!"));
////                        return false;
////                    }
////                } else
//                if (!checkStack(state -> lex_state, state))
//                    return false;
//            }

//            Lexem highlightable = Lexem(state -> lex_state & lex_highlightable);
//            if (highlightable)
//                state -> light(highlightable);

//            qDebug() << state -> cached;
//        } else if (predefined_lexem) {
//            if (!checkStack(state -> lex_state, state))
//                return false;
//        }
//        else state -> lex_state = lex_ignore;

//        if (state -> lex_state != lex_ignore)
//            state -> new_line_state = state -> lex_state;


//        if (state -> next_offset) {
//            state -> cachingDelimiter();
//            state -> lex_state = PredefinedRuby::obj().lexem(state -> cached);

//            if (state -> lex_state == lex_end_line)
//                state -> new_line_state = lex_none;
//            else if (state -> lex_state != lex_ignore)
//                state -> new_line_state = state -> lex_state;

//            if (!checkStack(state -> lex_state, state))
//                return false;

////            if (state -> var_def_state) {
////                if (state -> lex_state == lex_var_chain_end) {
////                    state -> scope -> clearUnregVar();
////                    state -> var_def_state = lex_none;
////                } else {
////                    if (
////                            (
////                                state -> lex_state == state -> var_def_state &&
////                                (
////                                    state -> var_def_state == lex_var ||
////                                    state -> var_def_state == lex_comma
////                                )
////                            )
////                            || state -> lex_state == lex_end_line
////                            || state -> lex_state == lex_binary_operator
////                    ) {

////                        APPEND_ERR(QByteArrayLiteral("Error in variable def"));
////                        return false;
////                    }
////                    else if (state -> lex_state != lex_ignore)
////                        state -> var_def_state = state -> lex_state;
////                }
////            }
//        }

//        state -> dropCached();

//        return true;
//    }

    bool cutWord(LexerState * state, const Lexem & predefined_lexem = lex_none) {
        state -> cachingPredicate();

        if (state -> cached_length || predefined_lexem != lex_none) {
            state -> lex_word =
                predefined_lexem != lex_none
                    ?
                predefined_lexem
                    :
                PredefinedRuby::obj().lexem(state -> cached);

            if (state -> lex_word == lex_undefined) {
                if (!state -> scope -> hasVar(state -> cached)) {
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
                            state -> lex_word =
                                (ECHAR_PREV1 == ':')
                                    ?
                                        lex_symbol
                                    :
                                        lex_word;
                        }
                    }


                    if (state -> lex_word != lex_symbol && state -> lex_word != lex_word)
                        state -> scope -> addVar(
                            state -> cached,
                            new FilePoint(state -> lex_word, 0, 0, state -> cached_str_pos)
                        );
                }
                else state -> lex_word = state -> scope -> varType(state -> cached);
            }

            Lexem highlightable = GrammarRuby::obj().toHighlightable(state -> lex_word);

            Lexem lex_new_word =
                GrammarRuby::obj().translate(
                    state -> lex_delimiter,
                    state -> lex_word
                );

            if (lex_new_word == lex_error) {
                state -> lightWithMessage(lex_error, QByteArrayLiteral("Wrong state!!!"));
//                return false;
            }

            if (state -> lex_word == lex_new_word) {
                if (lex_new_word == lex_word) {
                    state -> scope -> addVar(
                        state -> cached,
                        new FilePoint(lex_var_local, 0, 0, state -> cached_str_pos)
                    );
                }
            } else {
                state -> lex_word = lex_new_word;

                if (highlightable == lex_none)
                    highlightable = GrammarRuby::obj().toHighlightable(state -> lex_word);
            }

            if (highlightable != lex_none)
                state -> light(highlightable);

            //TODO: prev word satisfy
//            GrammarRuby::obj().translate(
//                state -> chain -> touchSublevel(),
//                state -> lex_word
//            );

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

        if (state -> isBufferEof())
            return false;

        if (state -> next_offset) {
            state -> cachingDelimiter();
            state -> lex_delimiter = PredefinedRuby::obj().lexem(state -> cached);
            state -> attachToken(state -> lex_delimiter);
        }

        if (state -> lex_word == lex_none) {
            Lexem lex_new_delimiter =
                GrammarRuby::obj().translate(
                    state -> lastToken(),
                    state -> lex_delimiter
                );

            if (lex_new_delimiter == lex_chain_item)
                state -> attachToken(state -> lex_delimiter);
            else {
                state -> lex_delimiter = lex_new_delimiter;
                state -> replaceToken(state -> lex_delimiter);
            }
        }

        state -> dropCached();

        return true;
    }

    bool parseHeredoc(LexerState * state) {
        QByteArray stop_token = state -> stack -> dataForTop();
        bool is_intended = false;

        switch(state -> stack -> touch()) {
            case lex_heredoc_intended_continue:
            case lex_eheredoc_intended_continue:
            case lex_cheredoc_intended_continue: {
                while(isBlank(*++state -> buffer));
                is_intended = true;
            }

            case lex_heredoc_continue:
            case lex_eheredoc_continue:
            case lex_cheredoc_continue: {
                if (!is_intended)
                    ++state -> buffer;

                if (QByteArray(state -> buffer, stop_token.length()) == stop_token) {
                    state -> stack -> drop();
                    return cutWord(state, lex_heredoc_end);
                }
            break;}

            default: state -> cacheAndLightWithMessage(lex_error, QByteArrayLiteral("Wrong stack status for heredoc content"));
        }

        return cutWord(state, lex_heredoc_end);
    }

    bool parseRegexp(LexerState * state) {
        bool ended = false;
        bool out_req = false;
        bool def_required = false;

        while(!ended && !out_req) {
            ++state -> buffer;

            switch(ECHAR0) {
                case '#': { def_required = ended = ECHAR1 == '{';  break;}
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

        if (!cutWord(state, out_req ? lex_regexp_continue : lex_regexp_end))
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
                if (GrammarRuby::obj().isStackDroppable(top))
                    state -> stack -> drop();

                --state -> buffer;

                switch(top) {
                    case lex_string_continue: goto handle_string;
                    case lex_estring_continue: goto handle_estring;
                    case lex_cheredoc_continue:
                    case lex_cheredoc_intended_continue:
                    case lex_eheredoc_continue:
                    case lex_eheredoc_intended_continue:
                    case lex_heredoc_continue:
                    case lex_heredoc_intended_continue: {
                        if (!parseHeredoc(state))
                            goto exit;
                    break;}
                    case lex_regexp_continue: {
                        if (!parseRegexp(state))
                            goto exit;
                    break;}
                    case lex_commentary_continue: goto handle_multiline_comment;
                    case lex_command_continue: goto handle_command;
                    default:;
                };
            }

        while(true) {
            switch(ECHAR0) {
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
                                case '#': { def_required = ended = ECHAR1 == '{'; break; }

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


                    if (!cutWord(state, out_req ? lex_command_continue : lex_command_end))
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
                                case '#': { def_required = ended = ECHAR1 == '{'; break; }

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


                    if (!cutWord(state, out_req ? lex_estring_continue : lex_estring_end))
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

                    if (ECHAR1 == '<')
                        ++state -> next_offset;

                        if (!isBlank(ECHAR2) && isBlank(ECHAR_PREV1)) {
                            const char * curr = state -> buffer + 2;

                            if (*curr == '-' || *curr == '~') {
                                ++state -> next_offset;
                                curr++;
                            }

                            const char * control = curr;
                            bool is_simple = *curr == '\'';
                            bool is_command = *curr == '`';
                            bool is_quoted = is_simple || is_command || *curr == '"';

                            lex = is_simple ? lex_heredoc_mark : is_command ? lex_cheredoc_mark : lex_eheredoc_mark;

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
                                state -> setStatus(is_simple ? LexerState::ls_heredoc : is_command ? LexerState::ls_cheredoc : LexerState::ls_eheredoc);
                            }
                        }
                    else {
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
                        state -> stack -> replace(top_conv);
                        state -> stack -> push(top);
//                        ++state -> buffer;
//                        state -> dropCached();
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
                    switch(ECHAR1) {
                        case '=': { ++state -> next_offset; break; }
                        case 'i': { break; } // Array of Symbols
                        case 'q': { break; } // single quoted string
                        case 'Q': { break; } // double quoted string
                        case 'r': { break; } // Regular Expression
                        case 's': { break; } // Symbol
                        case 'w': { break; } // Array of Strings
                        case 'x': { break; } // Backtick (capture subshell result)
                    };

                    if (!cutWord(state))
                        goto exit;


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
