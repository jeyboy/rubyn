#include "ruby_lexer_frontend.h"

#include "ruby_lexer_control.h"
#include "ruby_grammar.h"
#include "ruby_predefined.h"

#include <qdatetime.h>

using namespace Ruby;

void LexerFrontend::highlightMarkupInComments(LexerControl * state) {
    state -> buffer -= state -> token -> length;

    while(true) {
        switch(ECHAR0) {
            case 'i':
            case 'I': {
                if (ECHAR4 == ':' && (ECHAR1 == 'N' || ECHAR1 == 'n') && (ECHAR2 == 'F' || ECHAR2 == 'f') && (ECHAR3 == 'O' || ECHAR3 == 'o')) {
                    state -> light(state -> scratchPos(), 5, hid_comment_mark_info);
                    state -> buffer += 4;
                }
            break;}

            case 'w':
            case 'W': {
                if (ECHAR4 == ':' && (ECHAR1 == 'A' || ECHAR1 == 'a') && (ECHAR2 == 'R' || ECHAR2 == 'r') && (ECHAR3 == 'N' || ECHAR3 == 'n')) {
                    state -> light(state -> scratchPos(), 5, hid_comment_mark_warn);
                    state -> buffer += 4;
                }
            break;}

            case 't':
            case 'T': {
                if (ECHAR4 == ':' && (ECHAR1 == 'O' || ECHAR1 == 'o') && (ECHAR2 == 'D' || ECHAR2 == 'd') && (ECHAR3 == 'O' || ECHAR3 == 'o')) {
                    state -> light(state -> scratchPos(), 5, hid_comment_mark_todo);
                    state -> buffer += 4;
                }
            break;}

            case 0: return;
        }

        ++state -> buffer;
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

void LexerFrontend::registerMethod(LexerControl * state) {
//    if (!state -> scope -> hasVar(state -> cached)) {
//        state -> scope -> addVar(
//            state -> cached,
//            new FilePoint(state -> lex_word, 0, 0, state -> cached_str_pos)
//        );
//    }
//    else state -> lex_word = state -> scope -> varType(state -> cached);
}

void LexerFrontend::registerClass(LexerControl * state) {

}

void LexerFrontend::registerModule(LexerControl * state) {

}


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
            if (ECHAR_1 == ':')
                state -> lex_word = lex_symbol_key;
            else if (isUpper(state -> cached[0])) {
                const char * it = state -> cached;
                bool is_const = true;
                EDITOR_LEN_TYPE pos = 0;

                while(is_const && *++it && (++pos < state -> cached_length)) { is_const = is_const && isUpper(*it); }

                if (is_const)
                    state -> lex_word = lex_const;
            }
        }
    }
}

void LexerFrontend::translateState(LexerControl * state) {
    LEXEM_TYPE new_state = state -> grammar -> translate(state -> lex_prev_word, state -> lex_delimiter);

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


//bool LexerFrontend::cutWord(LexerControl * state, const LEXEM_TYPE & predefined_lexem, const LEXEM_TYPE & predefined_delimiter, StackLexemFlag flags) {
//    bool has_predefined = predefined_lexem != lex_none;

//    state -> cachingPredicate();

//    if (state -> cached_length || has_predefined) {
//        LEXEM_TYPE last_non_blank = state -> lastNonBlankLexem();

//        if (has_predefined)
//            state -> lex_word = predefined_lexem;
//        else {
//            LEXEM_TYPE pot_lex = Predefined::obj().lexem(state -> cached);

//            switch(pot_lex) {
//                case lex_yield: { break; } // yield can call through object: 'block.yield'
//                case lex_word: { break; }

//                default: { // proc lex with dot in front like
//                    if (last_non_blank == lex_dot)
//                       pot_lex = lex_word;
//                }
//            }

//            state -> lex_word = pot_lex;
//        }

//        if (state -> cached_length) {
//            if (state -> lex_word == lex_word)
//                identifyWordType(state);
//            else
//                state -> grammar -> initFlags(flags, state -> lex_word, last_non_blank);

////            if (state -> lex_word == lex_word) {
////                switch(last_non_blank) {
////                    case lex_method_def: {
////                        state -> lex_word = lex_method_def_name;
////                    break;}
////                    case lex_module_def: {
////                        state -> lex_word = lex_module_def_name;
////                    break;}
////                    case lex_class_def: {
////                        state -> lex_word = lex_class_def_name;
////                    break;}
////                    default:;
////                }
////            }

//            Identifier highlightable = state -> grammar -> toHighlightable(state -> lex_word);
//            if (highlightable != hid_none)
//                state -> light(highlightable);
//        }

//        state -> attachToken(state -> lex_word, flags & slf_word_related);

//        translateState(state);

//        if (state -> cached_length) {
////            if (state -> lex_word == lex_word)
////                registerVariable(state);

//            Identifier highlightable = state -> grammar -> toHighlightable(state -> lex_word);
//            if (highlightable == hid_none) {
//                highlightable = state -> grammar -> toHighlightable(state -> lex_prev_word);
//            }

//            if (highlightable != hid_none)
//                state -> light(highlightable);
//        }
//    }
//    else state -> lex_word = lex_none;

//    if (state -> next_offset) {
//        LEXEM_TYPE prev_delimiter = state -> lex_delimiter;

//        state -> cachingDelimiter();

//        state -> lex_delimiter =
//            predefined_delimiter == lex_none ?
//                Predefined::obj().lexem(state -> cached) :
//                predefined_delimiter;

//        Identifier highlightable = state -> grammar -> toHighlightable(state -> lex_delimiter);
//        if (highlightable != hid_none)
//            state -> light(highlightable);

//        state -> attachToken(state -> lex_delimiter, flags & slf_delimiter_related);

//        if (state -> lex_word == lex_none) {
//            LEXEM_TYPE new_state = state -> grammar -> translate(prev_delimiter, state -> lex_delimiter);

//            if (new_state == lex_error) {
//                state -> lightWithMessage(
//                    lex_error,
//                    ERROR_STATE(QByteArrayLiteral("Wrong delimiter satisfy state!!!"), prev_delimiter, state -> lex_delimiter)
//                );
//                //return false;
//            }

//            state -> lex_delimiter = new_state;
//        }
//    }

//    state -> dropCached();

//    return true;
//}


bool LexerFrontend::cutWord(LexerControl * state, const LEXEM_TYPE & predefined_lexem, const LEXEM_TYPE & predefined_delimiter, StackLexemFlag flags) {
    bool has_predefined = predefined_lexem != lex_none;

    state -> cachingPredicate();

    if (state -> cached_length || has_predefined) {
        if (has_predefined)
            state -> lex_word = predefined_lexem;
        else {
            LEXEM_TYPE pot_lex = Predefined::obj().lexem(state -> cached);

//            switch(pot_lex) {
//                case lex_yield: { break; } // yield can call through object: 'block.yield'
//                case lex_word: { break; }

//                default: { // proc lex with dot in front like
//                    if (last_non_blank == lex_dot)
//                       pot_lex = lex_word;
//                }
//            }

            state -> lex_word = pot_lex;
        }

        if (state -> cached_length) {
            LEXEM_TYPE last_non_blank = state -> lastNonBlankLexem();

            if (state -> lex_word == lex_word) {
                switch(last_non_blank) {
//                    case lex_class_def: {
//                        state -> lex_word = lex_class_def_name;
//                        registerClass(state);
//                    break;}

//                    case lex_module_def: {
//                        state -> lex_word = lex_module_def_name;
//                        registerModule(state);
//                    break;}

//                    case lex_method_def: {
//                        state -> lex_word = lex_method_def_name;
//                        registerMethod(state);
//                    break;}

                    default: identifyWordType(state);
                }
            } else {
                state -> grammar -> initFlags(flags, state -> lex_word, last_non_blank);
            }
        }

        state -> attachToken(state -> lex_word, flags & slf_word_related);

        translateState(state);

        if (state -> cached_length) {
            Identifier highlightable = state -> grammar -> toHighlightable(state -> lex_word);
            if (highlightable == hid_none) {
                highlightable = state -> grammar -> toHighlightable(state -> lex_prev_word);
            }

            if (highlightable != hid_none)
                state -> light(highlightable);
        }
    }
    else state -> lex_word = lex_none;

    if (state -> next_offset) {
        LEXEM_TYPE prev_delimiter = state -> lex_delimiter;

        state -> cachingDelimiter();

        state -> lex_delimiter =
            predefined_delimiter == lex_none ?
                Predefined::obj().lexem(state -> cached) :
                predefined_delimiter;

        Identifier highlightable = state -> grammar -> toHighlightable(state -> lex_delimiter);
        if (highlightable != hid_none)
            state -> light(highlightable);

        state -> attachToken(state -> lex_delimiter, flags & slf_delimiter_related);

        if (state -> lex_word == lex_none) {
            LEXEM_TYPE new_state = state -> grammar -> translate(prev_delimiter, state -> lex_delimiter);

            if (new_state == lex_error) {
                state -> lightWithMessage(
                    lex_error,
                    ERROR_STATE(QByteArrayLiteral("Wrong delimiter satisfy state!!!"), prev_delimiter, state -> lex_delimiter)
                );
                //return false;
            }

            state -> lex_delimiter = new_state;
        }
    }

    state -> dropCached();

    return true;
}


bool LexerFrontend::parseContinious(LexerControl * state) {
    if (state -> stack_token) {
        switch(state -> stack_token -> lexem) {
            case lex_string_start: { return parseString(state); }

            case lex_estring_start: { return parseEString(state); }

            case lex_regexp_start: { return parseRegexp(state); }

            case lex_percent_presentation_start:
            case lex_epercent_presentation_start: { return parsePercentagePresenation(state); }

            case lex_commentary_start: { return parseComment(state); }

            case lex_cheredoc_start:
            case lex_cheredoc_intended_start:
            case lex_eheredoc_start:
            case lex_eheredoc_intended_start:
            case lex_heredoc_start:
            case lex_heredoc_intended_start: { return parseHeredoc(state); }

            case lex_command_start: { return parseCommand(state); }

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
                else {
                    switch(ECHAR1) {
                        case '0':
                        case '1':
                        case '2':
                        case '3':
                        case '4':
                        case '5':
                        case '6':
                        case '7':
                        case '8':
                        case '9': { predef = lex_float; break;}

                        default: { ended = true; } //INFO: exit if we have deal with calling of the method for a number
                    }
                }
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
    StateLexem del_lex = lex_none;
    StackLexemFlag flags = slf_none;

    while(true) {
        switch(ECHAR0) {
            case '\'': {
                if (ECHAR_1 != '\\') {
                    lex = lex_string_content;
                    del_lex = lex_string_end;
                    flags = slf_unstack_delimiter;
                }
            break;}

            case 0: {
                state -> next_offset = 0;
                lex = lex_string_content;
                del_lex = lex_end_line;
            break;}
        }

        if (lex == lex_none)
            ++state -> buffer;
        else break;
    }

    return cutWord(state, lex, del_lex, flags);
}

bool LexerFrontend::parseEString(LexerControl * state) {
    StateLexem lex = lex_none;
    StateLexem del_lex = lex_none;
    StackLexemFlag flags = slf_none;

    while(true) {
        switch(ECHAR0) {
            case '#': {
                if (ECHAR1 == '{' && ECHAR_1 != '\\') {
                    ++state -> next_offset;
                    lex = lex_estring_content;
                    del_lex = lex_estring_interception;
                    flags = slf_stack_delimiter;
                }
            break; }

            case '"': {
                if (ECHAR_1 != '\\') {
                    lex = lex_estring_content;
                    del_lex = lex_estring_end;
                    flags = slf_unstack_delimiter;
                }
            break;}

            case 0: {
                state -> next_offset = 0;
                lex = lex_estring_content;
                del_lex = lex_end_line;
            break;}
        }

        if (lex == lex_none)
            ++state -> buffer;
        else break;
    }

    return cutWord(state, lex, del_lex, flags);
}

bool LexerFrontend::parseCommand(LexerControl * state) {
    StateLexem lex = lex_none;
    StateLexem del_lex = lex_none;
    StackLexemFlag flags = slf_none;

    while(lex == lex_none) {
        switch(ECHAR0) {
            case '#': {
                if (ECHAR1 == '{' && ECHAR_1 != '\\') {
                    ++state -> next_offset;
                    lex = lex_command_content;
                    del_lex = lex_command_interception;
                }
            break; }

            case '`': {
                if (ECHAR_1 != '\\') {
                    ++state -> buffer;
                    lex = lex_command_content;
                    del_lex = lex_command_end;
                    flags = slf_unstack_delimiter;
                }
            break;}

            case 0: {
                state -> next_offset = 0;
                lex = lex_command_content;
                del_lex = lex_end_line;
            break;}
        }

        if (lex == lex_none)
            ++state -> buffer;
        else break;
    }

    return cutWord(state, lex, del_lex, flags);
}

bool LexerFrontend::parsePercentagePresenation(LexerControl * state) {
    //# %i Non-interpolated Array of symbols, separated by whitespace
    //# %l Interpolated Array of symbols, separated by whitespace
    //# %q String
    //# %Q String with interpolation
    //# %/ String with interpolation
    //# %r Regular Expression
    //# %s Symbol
    //# %w Array of Strings
    //# %W Array of double quoted strings
    //# %x Backtick (capture subshell result)

    TokenCell * stack_state = state -> stack_token;

    if (!stack_state || !stack_state -> data) {
        state -> cacheAndLightWithMessage(lex_error, QByteArrayLiteral("Wrong stack state"));
        return true; // false;
    }

    const char blocker = stack_state -> data -> operator[](0);

    LEXEM_TYPE stack_lexem = state -> stack_token -> lexem;
    LEXEM_TYPE lex = lex_none;
    LEXEM_TYPE del_lex = lex_none;
    StackLexemFlag flags = slf_none;

    bool is_interable = stack_lexem != lex_percent_presentation_start;

    while(true) {
        switch(ECHAR0) {
            case '#': {
                if (is_interable) {
                    if (ECHAR1 == '{' && ECHAR_1 != '\\') {
                        ++state -> next_offset;
                        lex = lex_epercent_presentation_content;
                        del_lex = lex_epercent_presentation_interception;
                        flags = slf_stack_delimiter;
                    }
                }
            break; }

            case 0: {
                state -> next_offset = 0;
                lex = is_interable ? lex_epercent_presentation_content : lex_percent_presentation_content;
            break;}

            default: {
                if (ECHAR0 == blocker && ECHAR_1 != '\\') {
                    lex = is_interable ? lex_epercent_presentation_content : lex_percent_presentation_content;
                    del_lex = is_interable ? lex_epercent_presentation_end  : lex_percent_presentation_end;
                    flags = slf_unstack_delimiter;
                }
            }
        }

        if (lex == lex_none)
            ++state -> buffer;
        else break;
    }

    return cutWord(state, lex, del_lex, flags);
}

bool LexerFrontend::parseHeredocMarks(LexerControl * state, LEXEM_TYPE & lex) {
    const char * curr = state -> buffer + 2;
    bool is_intended = false;

    if (*curr == '-' || *curr == '~') { // ~ added only in Ruby 2.3.0
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
    state -> buffer += (curr - state -> buffer) + (is_quoted ? 1 : 0);
    state -> next_offset = 0;

    bool res = cutWord(state, lex);

    state -> registerHeredocMark(lex, new QByteArray(doc_name));
    // decrease buffer on 1 symbol because after func we go to the iteration
    --state -> buffer;

    return res;
}

bool LexerFrontend::parseHeredoc(LexerControl * state) {
    if (!state -> stack_token || !state -> stack_token -> data) {
        state -> cacheAndLightWithMessage(lex_error, QByteArrayLiteral("Wrong stack status for heredoc content"));
        return true; // false;
    }

    LEXEM_TYPE lex = lex_none;
    LEXEM_TYPE del_lex = lex_none;
    StackLexemFlag flags = slf_none;

    QByteArray stop_token = *state -> stack_token -> data;

    if (state -> isBufferStart()) { // this branching required here?
        switch(state -> stack_token -> lexem) {
            case lex_heredoc_intended_start:
            case lex_eheredoc_intended_start:
            case lex_cheredoc_intended_start: {
                while(true) {
                    if (isBlank(*state -> buffer)) {
                        ++state -> prev;
                        ++state -> buffer;
                    }
                    else break;
                }
            }

            case lex_heredoc_start:
            case lex_eheredoc_start:
            case lex_cheredoc_start: {
                if (*state -> buffer == stop_token[0]) {
                    int token_length = stop_token.length();

                    if (QByteArray(state -> buffer, token_length) == stop_token && !isWord(*(state -> buffer + token_length))) {
                        state -> buffer += token_length;
                        state -> next_offset = 0;
                        lex = lex_heredoc_close_mark;
                        del_lex = lex_end_line;
                        flags = slf_unstack_word;
                    }
                }
            break;}

            default: state -> cacheAndLightWithMessage(lex_error, QByteArrayLiteral("Wrong stack status for heredoc content"));
        }
    }

    if (lex == lex_none) {
        switch(state -> stack_token -> lexem) {
            case lex_heredoc_start:
            case lex_heredoc_intended_start: { state -> moveBufferToEnd(); break;}

            case lex_eheredoc_intended_start:
            case lex_cheredoc_intended_start:
            case lex_eheredoc_start:
            case lex_cheredoc_start: {
                while(true) {
                    switch(ECHAR0) {
                        case '#': {
                            if (ECHAR1 == '{' && ECHAR_1 != '\\') {
                                ++state -> next_offset;
                                lex = Grammar::obj().stateForHeredoc(state -> stack_token -> lexem, true);
                                del_lex = lex_heredoc_interception;
                                flags = slf_stack_delimiter;
                            }
                        break; }

                        case 0: {
                            state -> next_offset = 0;
                            lex = Grammar::obj().stateForHeredoc(state -> stack_token -> lexem, true);
                            del_lex = lex_none;
                        break;}
                    }

                    if (lex == lex_none)
                        ++state -> buffer;
                    else break;
                }
            break;}

            default:;
        }
    }

    return cutWord(state, lex, del_lex, flags);
}

bool LexerFrontend::parseRegexp(LexerControl * state) {
    StateLexem lex = lex_none;
    StateLexem del_lex = lex_none;
    StackLexemFlag flags = slf_none;

    while(true) {
        switch(ECHAR0) {
            case '#': {
                if (ECHAR1 == '{' && ECHAR_1 != '\\') {
                    ++state -> next_offset;

                    lex = lex_regexp_content;
                    del_lex = lex_regexp_interception;
                    flags = slf_stack_delimiter;
                }
            break;}

            case '/': {
                if (ECHAR_1 != '\\') {
                    lex = lex_regexp_content;
                    del_lex = lex_regexp_end;
                    flags = slf_unstack_delimiter;
                }
            break;}

            case 0: {
                lex = lex_regexp_content;
                del_lex = lex_end_line;
            break;}
        }

        if (lex == lex_none)
            ++state -> buffer;
        else break;
    }

    bool status = cutWord(state, lex, del_lex, flags);

    /// check regexp flags

    bool has_wrong_flags = false;
    bool has_flags = false;

    lex = lex_none;

    while(lex == lex_none) {
        switch(ECHAR0) {
            case 'm': // Treat a newline as a character matched by .
            case 'i': // Ignore case
            case 'x': // Ignore whitespace and comments in the pattern
            case 'o': // Perform #{} interpolation only once
            case 'u': // encoding:  UTF-8
            case 'e': // encoding:  EUC-JP
            case 's': // encoding:  Windows-31J
            case 'n': // encoding:  ASCII-8BIT
            {
                has_flags = true;
            break;}
            case 0: {
                lex = lex_regexp_flags;
            break;}
            default: {
                if (has_flags && isAlphaNum(ECHAR0)) {
                    has_wrong_flags = true;
                    state -> next_offset = 0;
                }

                lex = lex_regexp_flags;
            }
        }

        if (lex == lex_none)
            ++state -> buffer;
        else break;
    }

    if (has_flags) {
        state -> next_offset = 0;
        status = /*status &&*/ cutWord(state, lex);
    }


    if (has_wrong_flags) {
        state -> cacheAndLightWithMessage(lex_error, QByteArrayLiteral("Wrong regexp flag"));
    }

    return status;
}

bool LexerFrontend::parseRegexpGroup(LexerControl * state) {
    bool has_error = false;
    bool parsed = false;

    while(!parsed) {
        switch(ECHAR0) {
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '0': {
                ++state -> buffer;
            break;}

            default: {
                has_error = isWord(ECHAR0, false);
                parsed = true;
            }
        }
    };

    bool res = cutWord(state, lex_method);

    if (has_error)
        state -> cacheAndLightWithMessage(lex_error, QByteArrayLiteral("Wrong symbol code"));

    return res;
}

bool LexerFrontend::parseComment(LexerControl * state) {
    state -> next_offset = 0;

    if (state -> isBufferStart()) {
        if (ECHAR0 == '=' && ECHAR1 == 'e' && ECHAR2 == 'n' && ECHAR3 == 'd') {
            state -> buffer += 4;
            return cutWord(state);
        }
    }

    state -> moveBufferToEnd();

    cutWord(state, lex_commentary_content);

    highlightMarkupInComments(state);

    return false;
}

bool LexerFrontend::parseCharCode(LexerControl * state) {
    bool has_error = false;
    bool parsed = false;
    state -> next_offset = 0;

    quint8 cpart = ccp_none;

    while(!parsed) {
        switch(ECHAR0) {
            case '\\': {
                ++state -> buffer;

                switch(ECHAR0) {
                    case 'C': { //    \C-\M-x #	meta-control-x
                        ++state -> buffer;
                        has_error |= (cpart & ccp_ctrl);

                        if (isBlank(ECHAR0)) {
                            parsed = has_error = true;
                            break;
                        }

                        if (ECHAR0 == '-') {
                            ++state -> buffer;
                            cpart |= ccp_ctrl;
                        }

                        if (isBlank(ECHAR0)) {
                            parsed = true;
                            break;
                        }
                    break;}

                    case 'M': { //    \M-\C-x #	meta-control-x
                        ++state -> buffer;
                        has_error |= (cpart & ccp_meta);

                        if (isBlank(ECHAR0)) {
                            parsed = has_error = true;
                            break;
                        }

                        if (ECHAR0 == '-') {
                            ++state -> buffer;
                            cpart |= ccp_meta;
                        }

                        if (isBlank(ECHAR0)) {
                            parsed = true;
                            break;
                        }
                    break;}

                    case 'x': { //    \xnn 	# character with hexadecimal value nn
                        ++state -> buffer;

                        if (isBlank(ECHAR0)) {
                            parsed = has_error = true;
                            break;
                        }

                        if (isHDigit(ECHAR0)) {
                            ++state -> buffer;
                            cpart |= ccp_hex;
                        }

                        if (isBlank(ECHAR0)) {
                            parsed = true;
                            break;
                        }

                        if (isHDigit(ECHAR0)) {
                            ++state -> buffer;
                            parsed = true;
                        }
                    break; }

                    case 8:
                    case 9: { parsed = has_error = true; break;}
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 0: { // \nnn #	character with octal value nnn
                        ++state -> buffer;

                        for(int i = 0; i < 3; i++) {
                            switch(ECHAR0) {
                                case 1:
                                case 2:
                                case 3:
                                case 4:
                                case 5:
                                case 6:
                                case 7:
                                case 0: {
                                    ++state -> buffer;
                                break;}

                                default: {
                                    if (isWord(ECHAR0)) {
                                        has_error = true;
                                    }

                                    parsed = true;
                                }
                            }
                        }
                    break;}

                    case 'c': { // \cx #	control-x
                        ++state -> buffer;
                        has_error |= (cpart & ccp_ctrl || cpart & ccp_short_ctrl);

                        if (isBlank(ECHAR0)) {
                            parsed = true;
                            break;
                        }
                    break;}

                    case 'u': { //    \unnnn #	Unicode code point U+nnnn (Ruby 1.9 and later)
                        //    \u{nnnnn} # 	Unicode code point U+nnnnn with more than four hex digits must be enclosed in curly braces
                        has_error |= (cpart & ccp_unicode || cpart & ccp_ctrl || cpart & ccp_meta);

                        ++state -> buffer;
                        cpart |= ccp_unicode;

                        if (ECHAR0 == '{') {
                            ++state -> buffer;

                            for(int i = 0; i < 5; i++) {
                                if (isHDigit(ECHAR0)) {
                                    ++state -> buffer;
                                }
                                else {
                                    break;
                                }
                            }

                            if (ECHAR0 == '}')
                                ++state -> buffer;
                            else
                                has_error = true;
                        } else {
                            for(int i = 0; i < 4; i++) {
                                if (isHDigit(ECHAR0)) {
                                    ++state -> buffer;
                                }
                                else {
                                    break;
                                }
                            }
                        }

                        parsed = true;
                    break;}

                    default: { // \x #	character x itself (for example \" is the double quote character)
                        ++state -> buffer;
                        parsed = true;
                    }
                }
            break;}

            default: {
                ++state -> buffer;
                parsed = true;
            }
        }
    };

    while(isWord(ECHAR0)) {
        has_error = true;
        ++state -> buffer;
    }

    bool res = cutWord(state, lex_char_sequence);

    if (has_error)
        state -> cacheAndLightWithMessage(lex_error, QByteArrayLiteral("Wrong symbol code"));

    return res;
}


void LexerFrontend::lexicate(LexerControl * state) {
//        a + b is interpreted as a.+(b)
//        a + b is interpreted as a+b ( Here a is a local variable)
//        a  +b is interpreted as a(+b) ( Here a is a method call)

//        Ruby interprets semicolons and newline characters as the ending of a statement.
//        However, if Ruby encounters operators, such as +, −, or backslash at the end of a line,
//        they indicate the continuation of a statement.

    if (state -> bufferIsEmpty())
        goto exit;

    if (!parseContinious(state))
        goto exit;

    while(true) {
        switch(ECHAR0) {
            case ' ': {
                StateLexem status = lex_blanks;

                if (ECHAR1 == ' ') {
                    int iter = 1;

                    do { ++state -> next_offset; }
                    while(*(state -> buffer + ++iter) == ' ');
                }

                if(!cutWord(state, lex_none, status)) goto exit;
            break;}

            case '\t':{
                StateLexem status = lex_tabs;

                if (ECHAR1 == '\t') {
                    int iter = 1;

                    do { ++state -> next_offset; }
                    while(*(state -> buffer + ++iter) == '\t');
                }

                if(!cutWord(state, lex_none, status)) goto exit;
            break;}

            case ',':
            case '~':
            case ';':
            case '\r':
            case '\n':
            case '\v': {
                if(!cutWord(state)) goto exit;
            break;}


            case '{':
            case '[':
            case '(': {
                if(!cutWord(state, lex_none, lex_none, slf_stack_delimiter)) goto exit;
            break;}
            case ']':
            case ')': {
                if(!cutWord(state, lex_none, lex_none, slf_unstack_delimiter)) goto exit;
            break;}
            case '}': {
                StateLexem lex = lex_close_curly_bracket;

                switch(state -> stack_token -> lexem) {
                    case lex_estring_interception:
                    case lex_regexp_interception:
                    case lex_epercent_presentation_interception:
                    case lex_command_interception:
                    case lex_heredoc_interception: {
                        lex = lex_interception_close;
                    break;}

                    default:;
                }

                if(!cutWord(state, lex_none, lex, slf_unstack_delimiter)) goto exit;

                if (!parseContinious(state))
                    goto exit;
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
                if (!cutWord(state, lex_none, lex_command_start, slf_stack_delimiter)) goto exit;

                if (!parseCommand(state)) goto exit;
            break;}


            case '\'': {
                if (!cutWord(state, lex_none, lex_string_start, slf_stack_delimiter)) goto exit;

                if (!parseString(state)) goto exit;
            break;}


            case '"': {
                if (!cutWord(state, lex_none, lex_estring_start, slf_stack_delimiter)) goto exit;

                if (!parseEString(state)) goto exit;
            break;}


            case ':': {
                StateLexem del_state = lex_none;
                StackLexemFlag flags = slf_none;

                if (ECHAR1 == ':')
                    ++state -> next_offset;
                else { // if we have deal with symbol
                    EDITOR_LEN_TYPE len = state -> strLength();

                    if (len > 0 && isWord(ECHAR_1)) {
                        ++state -> buffer;
                        state -> next_offset = 0;
                    } else {
                        if (len == 0 && isWord(ECHAR1, false))
                            goto iterate;
                        else {
                            // ternary parts should be on the same stack level
                            if (state -> stack_token -> lexem == lex_ternary_main_start) {
                                del_state = lex_ternary_alt_start;
                                flags = slf_unstack_delimiter;
                            }
                        }
                    }
                }

                if (!cutWord(state, lex_none, del_state, flags)) goto exit;
            break;}


            case '^': {
                if (ECHAR1 == '=')
                    ++state -> next_offset;

                if (!cutWord(state)) goto exit;
            break;}


            case '=': {
                if (ECHAR1 == '~')
                    ++state -> next_offset;
                else if (ECHAR1 == '=') {// ==
                    ++state -> next_offset;

                    if (ECHAR2 == '=') // ===
                        ++state -> next_offset;
                }
                else if (ECHAR1 == '>') {
                    ++state -> next_offset;
                }
                else if (ECHAR1 == 'b') { // =begin
                   if (ECHAR2 == 'e' && ECHAR3 == 'g' &&
                        ECHAR4 == 'i' && ECHAR5 == 'n')
                   {
                        state -> buffer += 6;
                        state -> next_offset = 0;

                        if (!cutWord(state)) goto exit;

                        parseComment(state);
                        goto exit;
                   }
                }

                if (!cutWord(state)) goto exit;
            break;}


            case '|': {
                if (ECHAR1 == '|') {
                    ++state -> next_offset;

                    if (ECHAR2 == '=') {
                        ++state -> next_offset;
                    }
                }

                if (ECHAR1 == '=')
                    ++state -> next_offset;

                if (!cutWord(state)) goto exit;
            break;}


            case '&': {
                if (ECHAR1 == '&') {
                    ++state -> next_offset;

                    if (ECHAR2 == '=')
                        ++state -> next_offset;
                }

                if (ECHAR1 == '=')
                    ++state -> next_offset;

                if (ECHAR1 == '.')
                    ++state -> next_offset;

                if (!cutWord(state)) goto exit;
            break;}


            case '!': {
                if (isAlphaNum(ECHAR_1))
                    goto iterate;

                if (ECHAR1 == '~' || ECHAR1 == '=')
                    ++state -> next_offset;

                if (!cutWord(state)) goto exit;
            break;}


            case '?': {
                uint len = state -> strLength();
                LEXEM_TYPE lex = lex_ternary_main_start;

                if (len == 0) {
                    LEXEM_TYPE sublex = state -> lastNonBlankLexem();

                    bool is_charcode = sublex == lex_none || (sublex & lex_ruby_ternary_braker && !isBlank(ECHAR1));

                    if (is_charcode) {
                        ++state -> buffer;

                        if (parseCharCode(state)) {
                            --state -> buffer;
                            goto iterate;
                        }
                    }
                } else {
                    if (isWord(ECHAR_1)) goto iterate;
                }

                if (!cutWord(state, lex_none, lex, lex == lex_ternary_main_start ? slf_stack_delimiter : slf_none)) goto exit;
            break;}


            case '<': {
                LEXEM_TYPE lex = lex_none;

                if (ECHAR1 == '<') {
                    ++state -> next_offset;

                    if (ECHAR2 == '=') {
                        ++state -> next_offset;
                    } else if (!isBlank(ECHAR2)) {
                        if (parseHeredocMarks(state, lex))
                            goto iterate;
                    }
                } else {
                    if (ECHAR1 == '=') {
                        ++state -> next_offset;

                        if (ECHAR2 == '>')
                            ++state -> next_offset;
                    }
                }

                if (!cutWord(state)) goto exit;
            break;}


            case '>': {
                if (ECHAR1 == '>') {
                    ++state -> next_offset;

                    if (ECHAR2 == '=')
                        ++state -> next_offset;
                }

                if (ECHAR1 == '=')
                    ++state -> next_offset;

                if (!cutWord(state)) goto exit;
            break;}


            // make inline comments collapsable
            case '#': { // inline comment
                state -> moveBufferToEnd();
                state -> next_offset = 0;

                if (!cutWord(state, lex_inline_commentary_content)) goto exit;

                highlightMarkupInComments(state);
            break;}


            case '-': {
                if (ECHAR1 == '>' || ECHAR1 == '=')
                    ++state -> next_offset;
                else if(isDigit(ECHAR1) && (state -> isBufferStart() || isBlank(ECHAR_1))) {
                    goto parse_number;
                }

                if (!cutWord(state)) goto exit;
            break;}


            case '+': {
                if (ECHAR1 == '=')
                    ++state -> next_offset;
                else if(isDigit(ECHAR1) && (state -> isBufferStart() || isBlank(ECHAR_1))) {
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
                if (isWord(ECHAR_1))
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
                char braker = '\0';

                switch(ECHAR1) {
                    case '=': { ++state -> next_offset; break; }

                    case '{':
                    case '(':
                    case '/': {
                        ++state -> next_offset;
                        braker = ECHAR1;
                        res = lex_epercent_presentation_start;
                    break;}


                    case 'l': // Interpolated Array of Symbols
                    case 'Q': // double quoted string
                    case 'r': // Regular Expression
                    case 'W': // Array of double quoted Strings
                    case 'x': // Backtick (capture subshell result)
                        {
                            state -> next_offset += 2;
                            braker = ECHAR2;
                            res = lex_epercent_presentation_start;
                        break;}

                    case 'i': // Array of Symbols
                    case 'q': // single quoted string
                    case 's': // Symbol
                    case 'w': // Array of Strings
                        {
                            state -> next_offset += 2;
                            braker = ECHAR2;
                            res = lex_percent_presentation_start;
                        break;}
                };

                if (res != lex_none) {
                    if (!cutWord(state, lex_none, res, slf_stack_delimiter)) goto exit;

                    if (state -> stack_token -> data) {
                        state -> stack_token -> data -> clear();
                        state -> stack_token -> data -> append(Grammar::obj().percentagePresentationBlocker(braker));
                    }
                    else state -> stack_token -> data = new QByteArray(1, Grammar::obj().percentagePresentationBlocker(braker));

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
                    LEXEM_TYPE lex = state -> lastNonBlankLexem();
                    bool next_is_blank = isBlank(ECHAR1);

                    bool is_division = (lex != lex_none || (!state -> isBufferStart() && isAlphaNum(ECHAR_1))) &&
                        (next_is_blank || !(lex & lex_ruby_division_breaker));

                    if (is_division) {
                        if (!cutWord(state)) goto exit;
                    } else {
                        if (!cutWord(state, lex_none, lex_regexp_start, slf_stack_delimiter)) goto exit;
                        if (!parseRegexp(state)) goto exit;
                    }
                }
            break;}


            case '@': {
                if (ECHAR1 == '@')
                    ++state -> buffer;

                goto iterate;

//                if (!cutWord(state)) goto exit;
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
                            ++state -> buffer;
                            parseRegexpGroup(state);
                            goto iterate;
                        }
                    }
                }

                if (!cutWord(state)) goto exit;

                if (!has_match)
                    state -> cacheAndLightWithMessage(lex_error, QByteArrayLiteral("Expression requires"));

                else goto iterate;
            break;}


            case 0: {
                state -> next_offset = 0;
                cutWord(state, lex_end_line);
                goto exit;
            /*break;*/}


            default:
                iterate:
                    // Ruby identifier names may consist of alphanumeric characters and the
                    //  underscore character ( _ ).
                    // check if word isWord(*window)
                    ++state -> buffer;
        }
    }

    exit:;
//        state -> validateHeredocState();
}

int LexerFrontend::rubyLineState(BlockUserData * udata, const int & prev_user_state, const bool & override_status) {
    //INFO: Hack for heredoc marks
    if (override_status || udata -> stack_token) {
        TokenCell * it = udata -> stack_token;

//        if (!it -> data)
//            it = udata -> stack_token;

        if (override_status || it -> data) {
//            QByteArray res(*it -> data);
            int hash = 0;
//            int steps = 0;

//            while(it -> next -> data) {
//                it = it -> next;
//                res.append(' ');
//                res.append(*it -> data);
//            }

            while(true) {
                hash = static_cast<int>(qHash(QDateTime::currentMSecsSinceEpoch()));

                if (hash > 0) hash = -hash;
//                uint seed = qHash(QDateTime::currentMSecsSinceEpoch());
//                hash = static_cast<int>(qHash(res, seed));

                if (hash < lex_min && hash != prev_user_state)
                    break;
            }

            return hash;
        }
    }

    return ILexer::lineState(udata);
}

LexerFrontend::LexerFrontend() {}

LexerFrontend::~LexerFrontend() {}

void LexerFrontend::handle(const QString & text, IHighlighter * lighter) {
    BlockUserData * prev_udata = lighter -> prevUserData();
    BlockUserData * udata = lighter -> userData();

    QByteArray text_val = text.toUtf8();
    lighter -> initCurrentBlockUserData(prev_udata, udata, text_val.length());

    LexerControl state(
        &Ruby::Grammar::obj(),
        udata,
        prev_udata && prev_udata -> stack_token ? prev_udata -> stack_token : udata -> token_begin,
        lighter
    );


    const char * window = text_val.constData();
    bool override_status = false;

    state.setBuffer(window);

    lexicate(&state);

    if (udata -> para_control && (!state.control_para || (state.control_para -> para_type != udata -> para_control -> para_type))) {
        if (udata -> isFolded()) {
            override_status = lighter -> toggleFolding();
        }
    }

    udata -> syncLine(state.stack_token, state.token, state.para, state.control_para);

    int prev_state = lighter -> userState();
    int new_state = rubyLineState(udata, prev_state, override_status);

    lighter -> setUserState(new_state);
}

void LexerFrontend::paraOpositionStr(const PARA_TYPE & para, QString & res) {
    switch(para) {
        case pt_curly_bracket:
        case pt_foldable_curly_bracket: { res = QLatin1Literal("}"); break;}
        case pt_close_curly_bracket:
        case pt_close_foldable_curly_bracket: { res = QLatin1Literal("{"); break;}

        case pt_square_bracket:
        case pt_foldable_square_bracket: { res = QLatin1Literal("]"); break;}
        case pt_close_square_bracket:
        case pt_close_foldable_square_bracket: { res = QLatin1Literal("["); break;}

        case pt_round_bracket: { res = QLatin1Literal(")"); break;}
        case pt_close_round_bracket: { res = QLatin1Literal("("); break;}

        case pt_angle_bracket: { res = QLatin1Literal(">"); break;}
        case pt_close_angle_bracket: { res = QLatin1Literal("<"); break;}

        case pt_interpolation: { res = QLatin1Literal("}"); break;}
        case pt_close_interpolation: { res = QLatin1Literal("#{"); break;}

        case pt_string:
        case pt_close_string: { res = QLatin1Literal("'"); break;}

        case pt_estring:
        case pt_close_estring: { res = QLatin1Literal("\""); break;}

        case pt_command:
        case pt_close_command: { res = QLatin1Literal("`"); break;}

        case pt_regexp:
        case pt_close_regexp: { res = QLatin1Literal("//"); break;}

//        case pt_open_do_block:
        case pt_open_begin_block:
        case pt_open_method:
//        case pt_open_class:
//        case pt_open_module:
        case pt_open_if:
        case pt_open_unless:
        case pt_open_case:
        case pt_open_while:
        case pt_open_until:
        case pt_open_for: { res = QLatin1Literal("end"); break;}

        case pt_comment:
        case pt_foldable_comment: { res = QLatin1Literal("=end"); break;}
        case pt_close_comment:
        case pt_close_foldable_comment: { res = QLatin1Literal("=begin"); break;}

        default: ILexer::paraOpositionStr(para, res);
    }
}


bool LexerFrontend::isCompleterInitiable(const LEXEM_TYPE & lex, const bool & at_end) {
    switch(lex) {
        case lex_inline_commentary_content:
        case lex_commentary_content:
        case lex_bin:
        case lex_oct:
        case lex_dec:
        case lex_hex:
        case lex_float:
        case lex_double:
            return false;

        case lex_operator_add:
        case lex_operator_minus:
        case lex_operator_multiplication:
        case lex_operator_division:
        case lex_operator_modulus:
        case lex_operator_exponentiation:

        case lex_operator_add_assigment:
        case lex_operator_minus_assigment:
        case lex_operator_multiplication_assigment:
        case lex_operator_division_assigment:
        case lex_operator_modulus_assigment:
        case lex_operator_exponentiation_assigment:

        case lex_operator_assigment:
        case lex_operator_comparison:
        case lex_operator_not_equal:
        case lex_operator_great:
        case lex_operator_less:
        case lex_operator_great_eql:
        case lex_operator_less_eql:
        case lex_operator_sort:
        case lex_operator_equality:
        case lex_dot_dot:
        case lex_dot_dot_dot:

        case lex_operator_bit_and:
        case lex_operator_bit_or:
        case lex_operator_bit_exclusive_or:
        case lex_operator_bit_not:
        case lex_operator_bit_left_shift:
        case lex_operator_bit_right_shift:

        case lex_operator_bit_and_assigment:
        case lex_operator_bit_or_assigment:
        case lex_operator_bit_exclusive_or_assigment:
        case lex_operator_bit_left_shift_assigment:
        case lex_operator_bit_right_shift_assigment:


        case lex_rocket:
        case lex_question_mark:
        case lex_colon:

        case lex_operator_not:
        case lex_operator_and:
        case lex_operator_or:


        case lex_operator_and_assigment:
        case lex_operator_or_assigment:

        case lex_resolution:
            return at_end;
    }

    return true;
}

bool LexerFrontend::isCompleterContinuable(const LEXEM_TYPE & lex, const bool & /*at_end*/) {
    switch(lex) {
        case lex_undefined: //INFO: compatibility for not lexable documents

        case lex_method:
        case lex_word:
        case lex_const:
        case lex_var_local:
        case lex_var_instance:
        case lex_var_object:
        case lex_var_global:
        case lex_end_of_code:
        case lex_commentary_start:
        case lex_commentary_end:

        case lex_global_pre_hook:
        case lex_global_post_hook:

        case lex_alias:
        case lex_operator_and_word:

        case lex_begin:
        case lex_loop_break:
        case lex_case:
        case lex_class_def:
        case lex_method_def:
        case lex_do:
        case lex_else:
        case lex_elsif:
        case lex_end:
        case lex_block_ensure:

        case lex_operator_comparison:
        case lex_operator_equality:

        case lex_extend:
        case lex_for:
        case lex_if:
        case lex_in:
        case lex_include:

        case lex_lambda_def:
        case lex_module_def:
        case lex_loop_next:
        case lex_operator_not:
        case lex_operator_or_word:
        case lex_visibility_scope:
        case lex_proc_def:
        case lex_raise:
        case lex_loop_redo:
        case lex_require:
        case lex_block_rescue:
        case lex_block_retry:
        case lex_return:
        case lex_self:
        case lex_super:
        case lex_then:
        case lex_undef:
        case lex_unless:
        case lex_until:
        case lex_when:
        case lex_while:
        case lex_yield:
        case lex_loop:
            return true;
    }

    return false;
}

bool LexerFrontend::isCompleterReplaceable(const LEXEM_TYPE & lex, const bool & at_start) {
    switch(lex) {
        case lex_undefined: //INFO: compatibility for not lexable documents

        case lex_method:
        case lex_word:
        case lex_class_def:
        case lex_method_def:
        case lex_module_def:
        case lex_const:
        case lex_var_local:
        case lex_var_instance:
        case lex_var_object:
        case lex_var_global:
            return !at_start;
    }

    return false;
}

