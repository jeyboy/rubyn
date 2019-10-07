#include "css_lexer_frontend.h"

#include "css_lexer_control.h"
#include "css_grammar.h"
#include "css_predefined.h"

#include <qdatetime.h>

using namespace Css;

//bool LexerFrontend::cutWord(LexerControl * state, const StateLexem & predefined_lexem, const StateLexem & predefined_delimiter, StackLexemFlag flags) {
//    bool has_predefined = predefined_lexem != lex_none;

//    state -> cachingPredicate();

//    if (state -> cached_length || has_predefined) {
//        StateLexem last_non_blank = state -> lastNonBlankLexem();

//        if (has_predefined)
//            state -> lex_word = predefined_lexem;
//        else {
//            StateLexem pot_lex = Predefined::obj().lexem(state -> cached);

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
//        StateLexem prev_delimiter = state -> lex_delimiter;

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
//            StateLexem new_state = state -> grammar -> translate(prev_delimiter, state -> lex_delimiter);

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


//bool LexerFrontend::parseContinious(LexerControl * state) {
//    if (state -> stack_token) {
//        switch(state -> stack_token -> lexem) {
//            case lex_string_start: { return parseString(state); }

//            case lex_estring_start: { return parseEString(state); }

//            case lex_regexp_start: { return parseRegexp(state); }

//            case lex_percent_presentation_start:
//            case lex_epercent_presentation_start: { return parsePercentagePresenation(state); }

//            case lex_commentary_start: { return parseComment(state); }

//            case lex_cheredoc_start:
//            case lex_cheredoc_intended_start:
//            case lex_eheredoc_start:
//            case lex_eheredoc_intended_start:
//            case lex_heredoc_start:
//            case lex_heredoc_intended_start: { return parseHeredoc(state); }

//            case lex_command_start: { return parseCommand(state); }

//            default:;
//        };
//    }

//    return true;
//}

//bool LexerFrontend::parseNumber(LexerControl * state) {
//    //    +3
//    //    3.2e23
//    //    -4.70e+9
//    //    -.2E-4
//    //    -7.6603
//    //    -4.70e+9

//    state -> next_offset = 0;
//    bool ended = false, has_exp_part = false;
//    StateLexem predef = lex_none;

//    if (ECHAR0 == '0') {
//        switch(ECHAR1) {
//            case 'X':
//            case 'x': { predef = lex_hex; break; }
//            case 'B':
//            case 'b': { predef = lex_bin; break; }
//            case 'o':
//            case 'O': { predef = lex_oct; break; }
//            case 'd':
//            case 'D': { predef = lex_dec; break; }
//            case '0':
//            case '1':
//            case '2':
//            case '3':
//            case '4':
//            case '5':
//            case '6':
//            case '7':
//            case '8':
//            case '9': { predef = lex_dec; break;}
//            default: {
//                ended = true;
//                predef = lex_dec;
//            }
//        }

//        ++state -> buffer;
//    } else predef = lex_dec;

//    bool is_valid = predef != lex_hex && predef != lex_bin;

//    while(!ended) {
//        ++state -> buffer;

//        switch(ECHAR0) {
//            case '.': {
//                if (predef == lex_float)
//                    ended = true;
//                else {
//                    switch(ECHAR1) {
//                        case '0':
//                        case '1':
//                        case '2':
//                        case '3':
//                        case '4':
//                        case '5':
//                        case '6':
//                        case '7':
//                        case '8':
//                        case '9': { predef = lex_float; break;}

//                        default: { ended = true; } //INFO: exit if we have deal with calling of the method for a number
//                    }
//                }
//            break;}

//            case 'a':
//            case 'A':
//            case 'b':
//            case 'B':
//            case 'c':
//            case 'C':
//            case 'd':
//            case 'D':
//            case 'f':
//            case 'F': {
//                if (predef != lex_hex) {
//                    state -> cacheAndLightWithMessage(
//                        lex_error,
//                        QByteArrayLiteral("Error in number: wrong literal")
//                    );

//                    return false;
//                } else is_valid = true;
//            break;}

//            case 'e':
//            case 'E': {
//                if (predef < lex_dec) {
//                    state -> cacheAndLightWithMessage(
//                        lex_error,
//                        QByteArrayLiteral("Error in number: exponent part available only for decimals")
//                    );

//                    return false;
//                } else if (predef >= lex_dec) {
//                    if (has_exp_part) {
//                        state -> cacheAndLightWithMessage(
//                            lex_error,
//                            QByteArrayLiteral("Error in number: double exponent part")
//                        );
//                    } else {
//                        has_exp_part = true;

//                        if (ECHAR1 == '-' || ECHAR1 == '+') {
//                            ++state -> buffer;
//                        }
//                    }
//                }
//                else is_valid = true;
//            break;}

//            case '8':
//            case '9': {
//                if (predef < lex_dec) {
//                    state -> cacheAndLightWithMessage(
//                        lex_error,
//                        QByteArrayLiteral("Error in number: 0-7 literals only")
//                    );

//                    return false;
//                }
//            break;}


//            case '2':
//            case '3':
//            case '4':
//            case '5':
//            case '6':
//            case '7': {
//                if (predef < lex_oct) {
//                    state -> cacheAndLightWithMessage(
//                        lex_error,
//                        QByteArrayLiteral("Error in number: 0,1 literals only")
//                    );

//                    return false;
//                }
//            break;}

//            case '0':
//            case '1': { is_valid = true; }
//            case '_': { break;}

//            default: ended = true;
//        }
//    }

//    if (!is_valid) { // if is hex or is bin and does not have any value: 0x or 0b
//        state -> cacheAndLightWithMessage(
//            lex_error,
//            QByteArrayLiteral("Error in number: must have value")
//        );

//        return false;
//    }

//    return cutWord(state, predef);
//}

//bool LexerFrontend::parseString(LexerControl * state) {
//    StateLexem lex = lex_none;
//    StateLexem del_lex = lex_none;
//    StackLexemFlag flags = slf_none;

//    while(true) {
//        switch(ECHAR0) {
//            case '\'': {
//                if (ECHAR_PREV1 != '\\') {
//                    lex = lex_string_content;
//                    del_lex = lex_string_end;
//                    flags = slf_unstack_delimiter;
//                }
//            break;}

//            case 0: {
//                state -> next_offset = 0;
//                lex = lex_string_content;
//                del_lex = lex_end_line;
//            break;}
//        }

//        if (lex == lex_none)
//            ++state -> buffer;
//        else break;
//    }

//    return cutWord(state, lex, del_lex, flags);
//}

//bool LexerFrontend::parseEString(LexerControl * state) {
//    StateLexem lex = lex_none;
//    StateLexem del_lex = lex_none;
//    StackLexemFlag flags = slf_none;

//    while(true) {
//        switch(ECHAR0) {
//            case '#': {
//                if (ECHAR1 == '{' && ECHAR_PREV1 != '\\') {
//                    ++state -> next_offset;
//                    lex = lex_estring_content;
//                    del_lex = lex_estring_interception;
//                    flags = slf_stack_delimiter;
//                }
//            break; }

//            case '"': {
//                if (ECHAR_PREV1 != '\\') {
//                    lex = lex_estring_content;
//                    del_lex = lex_estring_end;
//                    flags = slf_unstack_delimiter;
//                }
//            break;}

//            case 0: {
//                state -> next_offset = 0;
//                lex = lex_estring_content;
//                del_lex = lex_end_line;
//            break;}
//        }

//        if (lex == lex_none)
//            ++state -> buffer;
//        else break;
//    }

//    return cutWord(state, lex, del_lex, flags);
//}

//bool LexerFrontend::parseComment(LexerControl * state) {
//    state -> next_offset = 0;

//    if (state -> isBufferStart()) {
//        if (ECHAR0 == '=' && ECHAR1 == 'e' && ECHAR2 == 'n' && ECHAR3 == 'd') {
//            state -> buffer += 4;
//            return cutWord(state);
//        }
//    }

//    state -> moveBufferToEnd();

//    cutWord(state, lex_commentary_content);

//    highlightMarkupInComments(state);

//    return false;
//}

//bool LexerFrontend::parseCharCode(LexerControl * state) {
//    bool has_error = false;
//    bool parsed = false;
//    state -> next_offset = 0;

//    quint8 cpart = ccp_none;

//    while(!parsed) {
//        switch(ECHAR0) {
//            case '\\': {
//                ++state -> buffer;

//                switch(ECHAR0) {
//                    case 'C': { //    \C-\M-x #	meta-control-x
//                        ++state -> buffer;
//                        has_error |= (cpart & ccp_ctrl);

//                        if (isBlank(ECHAR0)) {
//                            parsed = has_error = true;
//                            break;
//                        }

//                        if (ECHAR0 == '-') {
//                            ++state -> buffer;
//                            cpart |= ccp_ctrl;
//                        }

//                        if (isBlank(ECHAR0)) {
//                            parsed = true;
//                            break;
//                        }
//                    break;}

//                    case 'M': { //    \M-\C-x #	meta-control-x
//                        ++state -> buffer;
//                        has_error |= (cpart & ccp_meta);

//                        if (isBlank(ECHAR0)) {
//                            parsed = has_error = true;
//                            break;
//                        }

//                        if (ECHAR0 == '-') {
//                            ++state -> buffer;
//                            cpart |= ccp_meta;
//                        }

//                        if (isBlank(ECHAR0)) {
//                            parsed = true;
//                            break;
//                        }
//                    break;}

//                    case 'x': { //    \xnn 	# character with hexadecimal value nn
//                        ++state -> buffer;

//                        if (isBlank(ECHAR0)) {
//                            parsed = has_error = true;
//                            break;
//                        }

//                        if (isHDigit(ECHAR0)) {
//                            ++state -> buffer;
//                            cpart |= ccp_hex;
//                        }

//                        if (isBlank(ECHAR0)) {
//                            parsed = true;
//                            break;
//                        }

//                        if (isHDigit(ECHAR0)) {
//                            ++state -> buffer;
//                            parsed = true;
//                        }
//                    break; }

//                    case 8:
//                    case 9: { parsed = has_error = true; break;}
//                    case 1:
//                    case 2:
//                    case 3:
//                    case 4:
//                    case 5:
//                    case 6:
//                    case 7:
//                    case 0: { // \nnn #	character with octal value nnn
//                        ++state -> buffer;

//                        for(int i = 0; i < 3; i++) {
//                            switch(ECHAR0) {
//                                case 1:
//                                case 2:
//                                case 3:
//                                case 4:
//                                case 5:
//                                case 6:
//                                case 7:
//                                case 0: {
//                                    ++state -> buffer;
//                                break;}

//                                default: {
//                                    if (isWord(ECHAR0)) {
//                                        has_error = true;
//                                    }

//                                    parsed = true;
//                                }
//                            }
//                        }
//                    break;}

//                    case 'c': { // \cx #	control-x
//                        ++state -> buffer;
//                        has_error |= (cpart & ccp_ctrl || cpart & ccp_short_ctrl);

//                        if (isBlank(ECHAR0)) {
//                            parsed = true;
//                            break;
//                        }
//                    break;}

//                    case 'u': { //    \unnnn #	Unicode code point U+nnnn (Ruby 1.9 and later)
//                        //    \u{nnnnn} # 	Unicode code point U+nnnnn with more than four hex digits must be enclosed in curly braces
//                        has_error |= (cpart & ccp_unicode || cpart & ccp_ctrl || cpart & ccp_meta);

//                        ++state -> buffer;
//                        cpart |= ccp_unicode;

//                        if (ECHAR0 == '{') {
//                            ++state -> buffer;

//                            for(int i = 0; i < 5; i++) {
//                                if (isHDigit(ECHAR0)) {
//                                    ++state -> buffer;
//                                }
//                                else {
//                                    break;
//                                }
//                            }

//                            if (ECHAR0 == '}')
//                                ++state -> buffer;
//                            else
//                                has_error = true;
//                        } else {
//                            for(int i = 0; i < 4; i++) {
//                                if (isHDigit(ECHAR0)) {
//                                    ++state -> buffer;
//                                }
//                                else {
//                                    break;
//                                }
//                            }
//                        }

//                        parsed = true;
//                    break;}

//                    default: { // \x #	character x itself (for example \" is the double quote character)
//                        ++state -> buffer;
//                        parsed = true;
//                    }
//                }
//            break;}

//            default: {
//                ++state -> buffer;
//                parsed = true;
//            }
//        }
//    };

//    while(isWord(ECHAR0)) {
//        has_error = true;
//        ++state -> buffer;
//    }

//    bool res = cutWord(state, lex_char_sequence);

//    if (has_error)
//        state -> cacheAndLightWithMessage(lex_error, QByteArrayLiteral("Wrong symbol code"));

//    return res;
//}


void LexerFrontend::lexicate(LexerControl * state) {
//    if (state -> bufferIsEmpty())
//        goto exit;

//    if (!parseContinious(state))
//        goto exit;

//    while(true) {
//        switch(ECHAR0) {
//            case ' ': {
//                StateLexem status = lex_blanks;

//                if (ECHAR1 == ' ') {
//                    int iter = 1;

//                    do { ++state -> next_offset; }
//                    while(*(state -> buffer + ++iter) == ' ');
//                }

//                if(!cutWord(state, lex_none, status)) goto exit;
//            break;}

//            case '\t':{
//                StateLexem status = lex_tabs;

//                if (ECHAR1 == '\t') {
//                    int iter = 1;

//                    do { ++state -> next_offset; }
//                    while(*(state -> buffer + ++iter) == '\t');
//                }

//                if(!cutWord(state, lex_none, status)) goto exit;
//            break;}

//            case ',':
//            case '~':
//            case ';':
//            case '\r':
//            case '\n':
//            case '\v': {
//                if(!cutWord(state)) goto exit;
//            break;}


//            case '{':
//            case '[':
//            case '(': {
//                if(!cutWord(state, lex_none, lex_none, slf_stack_delimiter)) goto exit;
//            break;}
//            case ']':
//            case ')': {
//                if(!cutWord(state, lex_none, lex_none, slf_unstack_delimiter)) goto exit;
//            break;}
//            case '}': {
//                StateLexem lex = lex_close_curly_bracket;

//                switch(state -> stack_token -> lexem) {
//                    case lex_estring_interception:
//                    case lex_regexp_interception:
//                    case lex_epercent_presentation_interception:
//                    case lex_command_interception:
//                    case lex_heredoc_interception: {
//                        lex = lex_interception_close;
//                    break;}

//                    default:;
//                }

//                if(!cutWord(state, lex_none, lex, slf_unstack_delimiter)) goto exit;

//                if (!parseContinious(state))
//                    goto exit;
//            break;}


//            case '.': {
//                if (ECHAR1 == '.') { // is range
//                    ++state -> next_offset;

//                    if (ECHAR2 == '.') // is range with exclusion
//                        ++state -> next_offset;
//                }

//                if (!cutWord(state)) goto exit;
//            break;}


//            case '`': {
//                if (!cutWord(state, lex_none, lex_command_start, slf_stack_delimiter)) goto exit;

//                if (!parseCommand(state)) goto exit;
//            break;}


//            case '\'': {
//                if (!cutWord(state, lex_none, lex_string_start, slf_stack_delimiter)) goto exit;

//                if (!parseString(state)) goto exit;
//            break;}


//            case '"': {
//                if (!cutWord(state, lex_none, lex_estring_start, slf_stack_delimiter)) goto exit;

//                if (!parseEString(state)) goto exit;
//            break;}


//            case ':': {
//                StateLexem del_state = lex_none;
//                StackLexemFlag flags = slf_none;

//                if (ECHAR1 == ':')
//                    ++state -> next_offset;
//                else { // if we have deal with symbol
//                    EDITOR_LEN_TYPE len = state -> strLength();

//                    if (len > 0 && isWord(ECHAR_PREV1)) {
//                        ++state -> buffer;
//                        state -> next_offset = 0;
//                    } else {
//                        if (len == 0 && isWord(ECHAR1, false))
//                            goto iterate;
//                        else {
//                            // ternary parts should be on the same stack level
//                            if (state -> stack_token -> lexem == lex_ternary_main_start) {
//                                del_state = lex_ternary_alt_start;
//                                flags = slf_unstack_delimiter;
//                            }
//                        }
//                    }
//                }

//                if (!cutWord(state, lex_none, del_state, flags)) goto exit;
//            break;}


//            case '^': {
//                if (ECHAR1 == '=')
//                    ++state -> next_offset;

//                if (!cutWord(state)) goto exit;
//            break;}


//            case '=': {
//                if (ECHAR1 == '~')
//                    ++state -> next_offset;
//                else if (ECHAR1 == '=') {// ==
//                    ++state -> next_offset;

//                    if (ECHAR2 == '=') // ===
//                        ++state -> next_offset;
//                }
//                else if (ECHAR1 == '>') {
//                    ++state -> next_offset;
//                }
//                else if (ECHAR1 == 'b') { // =begin
//                   if (ECHAR2 == 'e' && ECHAR3 == 'g' &&
//                        ECHAR4 == 'i' && ECHAR5 == 'n')
//                   {
//                        state -> buffer += 6;
//                        state -> next_offset = 0;

//                        if (!cutWord(state)) goto exit;

//                        parseComment(state);
//                        goto exit;
//                   }
//                }

//                if (!cutWord(state)) goto exit;
//            break;}


//            case '|': {
//                if (ECHAR1 == '|') {
//                    ++state -> next_offset;

//                    if (ECHAR2 == '=') {
//                        ++state -> next_offset;
//                    }
//                }

//                if (ECHAR1 == '=')
//                    ++state -> next_offset;

//                if (!cutWord(state)) goto exit;
//            break;}


//            case '&': {
//                if (ECHAR1 == '&') {
//                    ++state -> next_offset;

//                    if (ECHAR2 == '=')
//                        ++state -> next_offset;
//                }

//                if (ECHAR1 == '=')
//                    ++state -> next_offset;

//                if (ECHAR1 == '.')
//                    ++state -> next_offset;

//                if (!cutWord(state)) goto exit;
//            break;}


//            case '!': {
//                if (isAlphaNum(ECHAR_PREV1))
//                    goto iterate;

//                if (ECHAR1 == '~' || ECHAR1 == '=')
//                    ++state -> next_offset;

//                if (!cutWord(state)) goto exit;
//            break;}


//            case '?': {
//                uint len = state -> strLength();
//                StateLexem lex = lex_ternary_main_start;

//                if (len == 0) {
//                    StateLexem sublex = state -> lastNonBlankLexem();

//                    bool is_charcode = sublex == lex_none || (sublex & lex_ruby_ternary_braker && !isBlank(ECHAR1));

//                    if (is_charcode) {
//                        ++state -> buffer;

//                        if (parseCharCode(state)) {
//                            --state -> buffer;
//                            goto iterate;
//                        }
//                    }
//                } else {
//                    if (isWord(ECHAR_PREV1)) goto iterate;
//                }

//                if (!cutWord(state, lex_none, lex, lex == lex_ternary_main_start ? slf_stack_delimiter : slf_none)) goto exit;
//            break;}


//            case '<': {
//                StateLexem lex = lex_none;

//                if (ECHAR1 == '<') {
//                    ++state -> next_offset;

//                    if (ECHAR2 == '=') {
//                        ++state -> next_offset;
//                    } else if (!isBlank(ECHAR2)) {
//                        if (parseHeredocMarks(state, lex))
//                            goto iterate;
//                    }
//                } else {
//                    if (ECHAR1 == '=') {
//                        ++state -> next_offset;

//                        if (ECHAR2 == '>')
//                            ++state -> next_offset;
//                    }
//                }

//                if (!cutWord(state)) goto exit;
//            break;}


//            case '>': {
//                if (ECHAR1 == '>') {
//                    ++state -> next_offset;

//                    if (ECHAR2 == '=')
//                        ++state -> next_offset;
//                }

//                if (ECHAR1 == '=')
//                    ++state -> next_offset;

//                if (!cutWord(state)) goto exit;
//            break;}


//            case '#': { // inline comment
//                state -> moveBufferToEnd();
//                state -> next_offset = 0;

//                if (!cutWord(state, lex_inline_commentary_content)) goto exit;

//                highlightMarkupInComments(state);
//            break;}


//            case '-': {
//                if (ECHAR1 == '>' || ECHAR1 == '=')
//                    ++state -> next_offset;
//                else if(isDigit(ECHAR1) && (state -> isBufferStart() || isBlank(ECHAR_PREV1))) {
//                    goto parse_number;
//                }

//                if (!cutWord(state)) goto exit;
//            break;}


//            case '+': {
//                if (ECHAR1 == '=')
//                    ++state -> next_offset;
//                else if(isDigit(ECHAR1) && (state -> isBufferStart() || isBlank(ECHAR_PREV1))) {
//                    goto parse_number;
//                }

//                if (!cutWord(state)) goto exit;
//            break;}


//            case '0':
//            case '1':
//            case '2':
//            case '3':
//            case '4':
//            case '5':
//            case '6':
//            case '7':
//            case '8':
//            case '9': {
//                if (isWord(ECHAR_PREV1))
//                    goto iterate;

//                parse_number:
//                    if (!parseNumber(state)) goto exit;
//            break;}


//            case '*': {
//                if (ECHAR1 == '*' || ECHAR1 == '=')
//                    ++state -> next_offset;

//                if (!cutWord(state)) goto exit;
//            break;}


//            case '%': {
//                StateLexem res = lex_none;
//                char braker = '\0';

//                switch(ECHAR1) {
//                    case '=': { ++state -> next_offset; break; }

//                    case '{':
//                    case '(':
//                    case '/': {
//                        ++state -> next_offset;
//                        braker = ECHAR1;
//                        res = lex_epercent_presentation_start;
//                    break;}


//                    case 'l': // Interpolated Array of Symbols
//                    case 'Q': // double quoted string
//                    case 'r': // Regular Expression
//                    case 'W': // Array of double quoted Strings
//                    case 'x': // Backtick (capture subshell result)
//                        {
//                            state -> next_offset += 2;
//                            braker = ECHAR2;
//                            res = lex_epercent_presentation_start;
//                        break;}

//                    case 'i': // Array of Symbols
//                    case 'q': // single quoted string
//                    case 's': // Symbol
//                    case 'w': // Array of Strings
//                        {
//                            state -> next_offset += 2;
//                            braker = ECHAR2;
//                            res = lex_percent_presentation_start;
//                        break;}
//                };

//                if (res != lex_none) {
//                    if (!cutWord(state, lex_none, res, slf_stack_delimiter)) goto exit;

//                    if (state -> stack_token -> data) {
//                        state -> stack_token -> data -> clear();
//                        state -> stack_token -> data -> append(Grammar::obj().percentagePresentationBlocker(braker));
//                    }
//                    else state -> stack_token -> data = new QByteArray(1, Grammar::obj().percentagePresentationBlocker(braker));

//                    if (!parsePercentagePresenation(state))
//                        goto exit;
//                } else {
//                    if (!cutWord(state))
//                        goto exit;
//                }
//            break;}


//            case '/': {
//                if (ECHAR1 == '=') {
//                    ++state -> next_offset;

//                    if (!cutWord(state)) goto exit;
//                } else {
//                    StateLexem lex = state -> lastNonBlankLexem();
//                    bool next_is_blank = isBlank(ECHAR1);

//                    bool is_division = (lex != lex_none || (!state -> isBufferStart() && isAlphaNum(ECHAR_PREV1))) &&
//                        (next_is_blank || !(lex & lex_ruby_division_breaker));

//                    if (is_division) {
//                        if (!cutWord(state)) goto exit;
//                    } else {
//                        if (!cutWord(state, lex_none, lex_regexp_start, slf_stack_delimiter)) goto exit;
//                        if (!parseRegexp(state)) goto exit;
//                    }
//                }
//            break;}


//            case '@': {
//                if (ECHAR1 == '@')
//                    ++state -> buffer;

//                goto iterate;

////                if (!cutWord(state)) goto exit;
//            break;}


//            case '$': {
//                bool has_match = false;
//                char next_char = ECHAR1;

//                switch(next_char) {
//                    case '!':
//                    case '@':
//                    case '/':
//                    case '\\':
//                    case ',':
//                    case ';':
//                    case '.':
//                    case '<':
//                    case '>':
//                    case '0':
//                    case '$':
//                    case '?':
//                    case ':':
//                    case '~':
//                    case '&':
//                    case '`':
//                    case '\'':
//                    case '+': {
//                        ++state -> next_offset;
//                        has_match = true;
//                    break; }

//                    default: {
//                        const char & n1_char = ECHAR2;

//                        if (next_char == '-') {
//                            switch(n1_char) {
//                                case '0':
//                                case 'a':
//                                case 'd':
//                                case 'F':
//                                case 'i':
//                                case 'K':
//                                case 'l':
//                                case 'p':
//                                case 'v':
//                                case '+': {
//                                    state -> next_offset += 2;
//                                    has_match = true;
//                                break; }

//                                default:;
//                            }
//                        } else if (next_char == '_') {
//                            if (!isAlphaNum(n1_char)) {
//                                has_match = true;
//                                state -> next_offset += 2;
//                            }
//                        } else if (isDigit(next_char)) { // $0-$99
//                            ++state -> buffer;
//                            parseRegexpGroup(state);
//                            goto iterate;
//                        }
//                    }
//                }

//                if (!cutWord(state)) goto exit;

//                if (!has_match)
//                    state -> cacheAndLightWithMessage(lex_error, QByteArrayLiteral("Expression requires"));

//                else goto iterate;
//            break;}


//            case 0: {
//                state -> next_offset = 0;
//                cutWord(state);
//                goto exit;
//            break;}


//            default:
//                iterate:
//                    // Ruby identifier names may consist of alphanumeric characters and the
//                    //  underscore character ( _ ).
//                    // check if word isWord(*window)
//                    ++state -> buffer;
//        }
//    }

//    exit:;
////        state -> validateHeredocState();
}

LexerFrontend::LexerFrontend() {}

LexerFrontend::~LexerFrontend() {}

void LexerFrontend::handle(const QString & text, IHighlighter * lighter) {
//    BlockUserData * prev_udata = lighter -> prevUserData();
//    BlockUserData * udata = lighter -> userData();

//    QByteArray text_val = text.toUtf8();
//    lighter -> initCurrentBlockUserData(prev_udata, udata, text_val.length());

//    LexerControl state(
//        &Ruby::Grammar::obj(),
//        udata,
//        prev_udata && prev_udata -> stack_token ? prev_udata -> stack_token : udata -> token_begin,
//        lighter
//    );


//    const char * window = text_val.constData();
//    bool override_status = false;

//    state.setBuffer(window);

//    lexicate(&state);

//    if (udata -> para_control && (!state.control_para || (state.control_para -> para_type != udata -> para_control -> para_type))) {
//        if (udata -> isFolded()) {
//            override_status = lighter -> toggleFolding();
//        }
//    }

//    udata -> syncLine(state.stack_token, state.token, state.para, state.control_para);

//    int prev_state = lighter -> userState();
//    int new_state = rubyLineState(udata, prev_state, override_status);

//    lighter -> setUserState(new_state);
}

//void LexerFrontend::paraOpositionStr(const PARA_TYPE & para, QString & res) {
//    switch(para) {
//        case pt_curly_bracket:
//        case pt_foldable_curly_bracket: { res = QLatin1Literal("}"); break;}
//        case pt_close_curly_bracket:
//        case pt_close_foldable_curly_bracket: { res = QLatin1Literal("{"); break;}

//        case pt_square_bracket:
//        case pt_foldable_square_bracket: { res = QLatin1Literal("]"); break;}
//        case pt_close_square_bracket:
//        case pt_close_foldable_square_bracket: { res = QLatin1Literal("["); break;}

//        case pt_round_bracket: { res = QLatin1Literal(")"); break;}
//        case pt_close_round_bracket: { res = QLatin1Literal("("); break;}

//        case pt_angle_bracket: { res = QLatin1Literal(">"); break;}
//        case pt_close_angle_bracket: { res = QLatin1Literal("<"); break;}

//        case pt_interpolation: { res = QLatin1Literal("}"); break;}
//        case pt_close_interpolation: { res = QLatin1Literal("#{"); break;}

//        case pt_string:
//        case pt_close_string: { res = QLatin1Literal("'"); break;}

//        case pt_estring:
//        case pt_close_estring: { res = QLatin1Literal("\""); break;}

//        case pt_command:
//        case pt_close_command: { res = QLatin1Literal("`"); break;}

//        case pt_regexp:
//        case pt_close_regexp: { res = QLatin1Literal("//"); break;}

////        case pt_open_do_block:
//        case pt_open_begin_block:
//        case pt_open_method:
////        case pt_open_class:
////        case pt_open_module:
//        case pt_open_if:
//        case pt_open_unless:
//        case pt_open_case:
//        case pt_open_while:
//        case pt_open_until:
//        case pt_open_for: { res = QLatin1Literal("end"); break;}

//        case pt_comment:
//        case pt_foldable_comment: { res = QLatin1Literal("=end"); break;}
//        case pt_close_comment:
//        case pt_close_foldable_comment: { res = QLatin1Literal("=begin"); break;}

//        default: ILexer::paraOpositionStr(para, res);
//    }
//}

bool LexerFrontend::isCompleterInitiable(const LEXEM_TYPE & lex, const bool & at_end) {}

bool LexerFrontend::isCompleterContinuable(const LEXEM_TYPE & lex, const bool & /*at_end*/) {}

bool LexerFrontend::isCompleterReplaceable(const LEXEM_TYPE & lex, const bool & at_start) {}
