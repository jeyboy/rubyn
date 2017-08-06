#ifndef LEXER_RUBY_H
#define LEXER_RUBY_H

#include "parts/lexer/lexer.h"
#include "predefined_ruby.h"

class LexerRuby : public Lexer {
    bool cutWord(Stack<Lexem> & stack, const char * window, const char *& prev,
                QByteArray & word, Lexem & lexem, Scope * scope, LexToken * lexems, const & index)
    {
        int word_length = window - prev;

        if (word_length == 0) {
            lexem = lex_none;
            prev = window;
            return true;
        }

        word = QByteArray(prev, word_length);

        lexem = PredefinedRuby::obj().lexem(word);

        if (lexem == lex_undefined) {
            if (scope -> hasVariable(word))
                lexem = lex_var;
        } else {
            if (lexem & lex_start)
                stack.push(lexem);
            else if (lexem & lex_end) {
                if (EXCLUDE_BIT(lexem, lex_end) == EXCLUDE_BIT(stack.touch(), lex_end)) {
                    stack.drop();
                } else {
                    lexems -> next = new LexError(index, word_length, QByteArray::number(stack.touch()) + QByteArrayLiteral(" required, but ") + QByteArray::number(lexem) + QByteArrayLiteral(" received"));
                    return false;
                }
            }
        }

        if (lexem)
            lexems -> next = new LexToken(Lexem(lexem & lex_highlightable), index, word_length);

        prev = window;
        return true;
    }
protected:
    LexToken * parse(const char * window, Lexem lex_state, Scope * scope) {
        Stack<Lexem> stack(lex_state);
        QByteArray word;
        LexToken * lexems = new LexToken();

        int index = 0;

        char end_str_symb = 0;
        const char * prev = window;
        bool prev_is_blank = true;

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
                    prev_is_blank = true;
                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index);
                    qDebug() << (*window) << word;
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

                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index);
                    qDebug() << (*window) << word;
                break;}



                case ',': {                   
                    if (lex_state == lex_comma)
                        ; // raise error

                    //                    lex_state = stack.push(lex_comma);

                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index);

                    qDebug() << (*window) << word;
                break;}



                case '`':
                case '\'':
                case '"': {               
                    if (end_str_symb) {
                        if (*window == end_str_symb) {
                            if (*(window - 1) != '\\')
                                goto iterate;

                            if (stack.touch() == lex_string_start)
                                stack.drop();
                            else
                                ; // output err

                            end_str_symb = 0;
                        }
                    } else {
                        end_str_symb = *window;
                        lex_state = stack.push(lex_string_start);
                    }

                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index);
                    qDebug() << (*window) << word;
                break;}



                case ':': {
                    if (PREV_CHAR(window) == '$')
                        window++;
                    else if (NEXT_CHAR(window) == ':') {
                        window++;
                    }

                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index);
                    qDebug() << (*window) << word;
                break;}



                case '=': {
                    if (NEXT_CHAR(window) == 'b') { // =begin
                       if (NEXT_CHAR(window + 1) == 'e' && NEXT_CHAR(window + 2) == 'g' &&
                            NEXT_CHAR(window + 3) == 'i' && NEXT_CHAR(window + 4) == 'n')
                                window +=5;
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

                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index);
                    qDebug() << (*window) << word;
                break;}

                case '^': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index);
                    qDebug() << (*window) << word;
                break;}

                case '|': {
                    if (NEXT_CHAR(window) == '|')
                        window++;

                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index);
                    qDebug() << (*window) << word;
                break;}



                case '&': {
                    if (NEXT_CHAR(window) == '&')
                        window++;

                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index);
                    qDebug() << (*window) << word;
                break;}



                case '!': {
                    if (!prev_is_blank)
                        goto iterate;

                    if (NEXT_CHAR(window) == '~')
                        window++;
                    else if (NEXT_CHAR(window) == '=')
                        window++;

                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index);
                    qDebug() << (*window) << word;
                break;}

                case '~': {
                    if (PREV_CHAR(window) == '=')
                        goto iterate;

                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index);
                    qDebug() << (*window) << word;
                break;}



                case '?': {
                    if (!prev_is_blank)
                        goto iterate;

                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index);
                    qDebug() << (*window) << word;
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

                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index);
                    qDebug() << (*window) << word;
                break;}



                case '>': {
                    if (NEXT_CHAR(window) == '>')
                        window++;
                    else if (NEXT_CHAR(window) == '=')
                        window++;

                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index);
                    qDebug() << (*window) << word;
                break;}



                case '[': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index);
                    qDebug() << (*window) << word;
                break;}
                case ']': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index);
                    qDebug() << (*window) << word;
                break;}



                case '(': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index);
                    qDebug() << (*window) << word;
                break;}
                case ')': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index);
                    qDebug() << (*window) << word;
                break;}



                case '{': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index);
                    qDebug() << (*window) << word;
                break;}

                case '}': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index);
                    qDebug() << (*window) << word;
                break;}



                case '#': {
                    if (end_str_symb && end_str_symb != '\'' && NEXT_CHAR(window) == '{') { // if string interpolation
                        lex_state = stack.push(lex_block_start);
                        goto iterate;
                    }

                    // if inline comment
                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index);
                    qDebug() << (*window) << word;

                    int offset = strlen(window) - index;

                    word = QByteArray(prev, offset);
                    qDebug() << word;
                    window += offset - 1;
                break;}



                case '-':
                    if (NEXT_CHAR(window) == '>') { // lambda
                        window++;

                        cutWord(stack, window, prev, word, lex_state, scope, lexems, index);
                        qDebug() << (*window) << word;
                    }
                case '+': {
                    if (isDigit(NEXT_CHAR(window)) || PREV_CHAR(window) == 'e')
                        goto iterate;

                    if (NEXT_CHAR(window) == '=')
                        window++;

                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index);
                    qDebug() << (*window) << word;
                break;}


                case '*': {
                    if (NEXT_CHAR(window) == '*') {
                        window++;
                    }

                    if (NEXT_CHAR(window) == '=')
                        window++;


                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index);
                    qDebug() << (*window) << word;
                break;}

                case '%':
                case '/': {
                    if (NEXT_CHAR(window) == '=')
                        window++;

                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index);
                    qDebug() << (*window) << word;
                break;}



                case '@': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index);
                    qDebug() << (*window) << word;

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

                    if (has_match) {
                        cutWord(stack, window, prev, word, lex_state, scope, lexems, index);
                        qDebug() << (*window) << word;
                    }
                break;}

//                case '\\': {
//                    cutWord(stack, window, prev, word, lex_state, scope, lexems, index);
//                    qDebug() << (*window) << word;
//                break;}

                default: prev_is_blank = false;
            }

            iterate:
                ++index;
                ++window;
        }

        return lexems;
    }
};

#endif // LEXER_RUBY_H
