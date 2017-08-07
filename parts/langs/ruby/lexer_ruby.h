#ifndef LEXER_RUBY_H
#define LEXER_RUBY_H

#include "parts/lexer/lexer.h"
#include "predefined_ruby.h"

class LexerRuby : public Lexer {
    bool cutWord(Stack<Lexem> & stack, const char * window, const char *& prev,
                QByteArray & word, Lexem & lexem, Scope * scope, LexToken * lexems,
                 const & index, Lexem & var_def_state, const Lexem & predefined_lexem = lex_none)
    {
        int word_length = window - prev;

        if (word_length > 0) { // ignore empty words
            word = QByteArray(prev, word_length);

            Lexem & stack_top = stack.touch();

            if (stack_top == lex_module_start || stack_top == lex_class_start || stack_top == lex_method_start) {
                scope -> addVariable(word, 0); // new FilePoint() // TODO: write me
            }
            else lexem = predefined_lexem ? predefined_lexem : PredefinedRuby::obj().lexem(word);

            if (lexem != lex_ignore) {
                if (var_def_state == lex_var_chain_end) {
                    scope -> clearUnregVar();
                    var_def_state = lex_none;
                } else {
                    if (var_def_state && lexem != lex_undefined && lexem != lex_none) {
                        if (var_def_state == lexem) {
                            lexems -> next = new LexError(index, word_length, QByteArrayLiteral("Error in variable def"));
                            return false;
                        }
                    }

                    if (lexem == lex_undefined) {
                        lexem = lex_var;

                        if (!scope -> hasVariable(word)) {
                            scope -> registerUnregVar(word, index);

                            if (var_def_state == lexem) {
                                lexems -> next = new LexError(index, word_length, QByteArrayLiteral("Error in variable def"));
                                return false;
                            }

                            var_def_state = lexem;
                        }
                    } else {
                        if (lexem & lex_start)
                            stack.push(lexem);
                        else if (lexem & lex_end) {
                            if (EXCLUDE_BIT(lexem, lex_end) == EXCLUDE_BIT(stack.touch(), lex_start)) {
                                stack.drop();
                            } else {
                                lexems -> next = new LexError(index, word_length, QByteArray::number(stack.touch()) + QByteArrayLiteral(" required, but ") + QByteArray::number(lexem) + QByteArrayLiteral(" received"));
                                return false;
                            }
                        }
                    }
                }

                Lexem highlightable = Lexem(lexem & lex_highlightable);

                if (highlightable)
                    lexems -> next = new LexToken(highlightable, index, word_length);

                qDebug() << word;
            }
        }

        prev = window;
        return true;
    }
protected:
    LexToken * parse(const char * window, Lexem lex_state, Scope * scope) {
        Stack<Lexem> stack(lex_state);
        QByteArray word;
        LexToken * lexems = new LexToken();
        Lexem var_def_state = lex_none;

        int index = 0;

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
                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index, var_def_state);
                    ++prev;
                break;}



                case '.': {
                    char next_char = NEXT_CHAR(window);
                    bool next_is_dot = next_char == '.';

                    if (next_is_dot) { // is range
                        ++window;

                        if (NEXT_CHAR(window) == '.') // is range with exclusion
                            ++window;
                    } else {
                        if (PREV_CHAR(window) == '$' || isDigit(next_char)) // is float or $.
                            goto iterate;
                    }

                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index, var_def_state);
                break;}



                case ',': {                   
//                    var_def_state = lex_comma;
                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index, var_def_state);
                break;}



                case '`':
                case '\'':
                case '"': {
                    end_str_symb = *window;
                    lex_state = stack.push(lex_string_start);

                    handle_string:
                        while(++window) {
                            ++index;

                            switch(*window) {
                                case '#': {
                                    if (end_str_symb != '\'' && NEXT_CHAR(window) == '{') {
                                        stack.push(lex_string_def_required);
                                        goto end_str;
                                    }
                                break;}

                                case '`':
                                case '\'':
                                case '"': {
                                    if (PREV_CHAR(window) != '\\') {
                                        window++;
                                        goto end_str;
                                    }
                                }
                            }
                        }

                    end_str:
                        cutWord(stack, window, prev, word, lex_state, scope, lexems, index, var_def_state, lex_string_end);
                break;}



                case ':': {
                    if (PREV_CHAR(window) == '$')
                        window++;
                    else if (NEXT_CHAR(window) == ':') {
                        window++;
                    }

                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index, var_def_state);
                break;}



                case '=': {
                    if (NEXT_CHAR(window) == 'b') { // =begin
                       if (NEXT_CHAR(window + 1) == 'e' && NEXT_CHAR(window + 2) == 'g' &&
                            NEXT_CHAR(window + 3) == 'i' && NEXT_CHAR(window + 4) == 'n') {
                                int offset = strlen(window) - index;
                                window += offset - 1;
                       }
                    }
                    else if (NEXT_CHAR(window) == 'e') { // =end
                       if (NEXT_CHAR(window + 1) == 'n' && NEXT_CHAR(window + 2) == 'd')
                                window +=3;
                    } else {
                        if (NEXT_CHAR(window) == '=') // ==
                            window++;

                        if (NEXT_CHAR(window) == '=') // ===
                            window++;
                    }

//                    if (window - prev == 1)
//                        var_def_state == lex_var_chain_end;

                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index, var_def_state);
                break;}

                case '^': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index, var_def_state);
                break;}

                case '|': {
                    if (NEXT_CHAR(window) == '|')
                        window++;

                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index, var_def_state);
                break;}



                case '&': {
                    if (NEXT_CHAR(window) == '&')
                        window++;

                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index, var_def_state);
                break;}



                case '!': {
                    if (!isBlank(PREV_CHAR(window)))
                        goto iterate;

                    if (NEXT_CHAR(window) == '~')
                        window++;
                    else if (NEXT_CHAR(window) == '=')
                        window++;

                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index, var_def_state);
                break;}

                case '~': {
                    if (PREV_CHAR(window) == '=')
                        goto iterate;

                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index, var_def_state);
                break;}



                case '?': {
                    if (!isBlank(PREV_CHAR(window)))
                        goto iterate;

                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index, var_def_state);
                break;}


                case '<': {
                    if (NEXT_CHAR(window) == '<')
                        window++;
                    else {
                        if (NEXT_CHAR(window) == '=')
                            window++;

                        if (NEXT_CHAR(window) == '>')
                            window++;
                    }

                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index, var_def_state);
                break;}



                case '>': {
                    if (NEXT_CHAR(window) == '>')
                        window++;
                    else if (NEXT_CHAR(window) == '=')
                        window++;

                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index, var_def_state);
                break;}



                case '[': {
//                    var_def_state = lex_array_start;
                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index, var_def_state);
                break;}
                case ']': {
//                    var_def_state = lex_array_end;
                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index, var_def_state);
                break;}



                case '(': {
//                    var_def_state = lex_wrap_start;
                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index, var_def_state);
                break;}
                case ')': {
//                    var_def_state = lex_wrap_end;
                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index, var_def_state);
                break;}



                case '{': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index, var_def_state);
                break;}

                case '}': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index, var_def_state);

                    if (stack.touch() == lex_string_def_required) { // return to string after interpolation
                        stack.drop();
                        goto handle_string;
                    }
                break;}



                case '#': { // inline comment
                    int offset = strlen(window) - index;
                    window += offset - 1;
                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index, var_def_state);
                break;}



                case '-':
                    if (NEXT_CHAR(window) == '>') { // lambda
                        window++;

                        cutWord(stack, window, prev, word, lex_state, scope, lexems, index, var_def_state);
                    }
                case '+': {
                    if (isDigit(NEXT_CHAR(window)) || PREV_CHAR(window) == 'e')
                        goto iterate;

                    if (NEXT_CHAR(window) == '=')
                        window++;

                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index, var_def_state);
                break;}


                case '*': {
                    if (NEXT_CHAR(window) == '*') {
                        window++;
                    }

                    if (NEXT_CHAR(window) == '=')
                        window++;

                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index, var_def_state);
                break;}

                case '%':
                case '/': {
                    if (NEXT_CHAR(window) == '=')
                        window++;

                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index, var_def_state);
                break;}



                case '@': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index, var_def_state);

                    if (NEXT_CHAR(window) == '@')
                        window++;
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
                            window++;
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
                                        window+=2;
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
                        cutWord(stack, window, prev, word, lex_state, scope, lexems, index, var_def_state);
                break;}

//                case '\\': {
//                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index, var_def_state);
//                break;}

                default:;
            }

            iterate:
                ++index;
                ++window;
        }

        return lexems;
    }
};

#endif // LEXER_RUBY_H
