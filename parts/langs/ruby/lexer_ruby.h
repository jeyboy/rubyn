#ifndef LEXER_RUBY_H
#define LEXER_RUBY_H

#include "parts/lexer/lexer.h"
#include "predefined_ruby.h"

class LexerRuby : public Lexer {
    Lexem cutWord(Stack<Lexem> & stack, const char * window, const char *& prev, QByteArray & word, Lexem & lexem, Scope * scope, LexToken * root) {
        int word_length = window - prev;

        if (word_length == 0) return lex_none;

        word = QByteArray(prev, word_length);

        lexem = PredefinedRuby::obj().lexem(word);

        if (lexem == lex_undefined) {
            if (scope -> hasVariable(word))
                lexem = lex_var;
        }

        prev = window;

        return stack.push(lexem);
    }
protected:
    LexToken * parse(const char * window, Lexem lex_state, Scope * scope) {
        Stack<Lexem> stack(lex_state);
        QByteArray word;
        LexToken * lexems = new LexToken();

        int index = 0;

        char end_str_symb = 0;
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


//        c = a + b
//        a, b, c = 10, 20, 30

//        c += a
//        c -= a
//        c *= a
//        c /= a
//        c %= a
//        c **= a

//        a + b = 23
//        a - b = -10
//        a * b = 2000
//        b / a = 2
//        b % a = 1
//        a**b = 8

//        (a == b)
//        (a != b)
//        (a > b)
//        (a < b)
//        (a >= b)
//        (a <= b)
//        (a <=> b) # Combined comparison operator. Returns 0 if first operand equals second, 1 if first operand is greater than the second and -1 if first operand is less than the second.
//        (1...10) === 5 # Used to test equality within a when clause of a case statement
//        1.eql?(1.0) == false  True if the receiver and argument have both the same type and equal values
//        a.equal?b # True if the receiver and argument have the same object id

//        a    = 60 # 0011 1100
//        b    = 13 # 0000 1101
//        -----------------
//        a&b = 12 # =  0000 1100
//        a|b = 61 # =  0011 1101
//        a^b = 49 # =  0011 0001
//        ~a = -61 # =  1100 0011
//        a << 2 = 240 # = 1111 0000
//        a >> 2 = 15 # = 0000 1111

//        (a and b) == true
//        (a or b) == true.
//        not(a && b) == false.
//        (a && b) == true.
//        (a || b) == true.
//        !(a && b) == false.

//        a > b ? 1 : 0 # ternary


        while(window) {
            switch(*window) {
                case '\v':
                case '\t':
                case ' ': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems);
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

                    cutWord(stack, window, prev, word, lex_state, scope, lexems);
                    qDebug() << (*window) << word;
                break;}



                case ',': {                   
                    cutWord(stack, window, prev, word, lex_state, scope, lexems);

                    if (stack.touch() == lex_comma)
                        ; // raise error

                    lex_state = stack.push(lex_comma);

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

                    cutWord(stack, window, prev, word, lex_state, scope, lexems);
                    qDebug() << (*window) << word;
                break;}



                case ':': {
                    if (PREV_CHAR(window == '$'))
                        window++;
                    else if (NEXT_CHAR(window) == ':') {
                        window++;
                        lex_state = lex_chain_access;
                    }

                    cutWord(stack, window, prev, word, lex_state, scope, lexems);
                    qDebug() << (*window) << word;
                break;}



                case '=': {



                    cutWord(stack, window, prev, word, lex_state, scope, lexems);
                    qDebug() << (*window) << word;
                break;}



                case '|': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems);
                    qDebug() << (*window) << word;
                break;}



                case '&': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems);
                    qDebug() << (*window) << word;
                break;}



                case '!': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems);
                    qDebug() << (*window) << word;
                break;}



                case '?': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems);
                    qDebug() << (*window) << word;
                break;}



                case '<': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems);
                    qDebug() << (*window) << word;
                break;}



                case '>': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems);
                    qDebug() << (*window) << word;
                break;}



                case '[': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems);
                    qDebug() << (*window) << word;
                break;}
                case ']': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems);
                    qDebug() << (*window) << word;
                break;}



                case '(': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems);
                    qDebug() << (*window) << word;
                break;}
                case ')': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems);
                    qDebug() << (*window) << word;
                break;}



                case '{': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems);
                    qDebug() << (*window) << word;
                break;}

                case '}': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems);
                    qDebug() << (*window) << word;
                break;}



                case '#': {
                    if (end_str_symb && end_str_symb != '\'' && NEXT_CHAR(window) == '{') { // if string interpolation
                        lex_state = stack.push(lex_block_start);
                        goto iterate;
                    }

                    // if inline comment
                    cutWord(stack, window, prev, word, lex_state, scope, lexems);
                    qDebug() << (*window) << word;

                    int offset = strlen(window) - index;

                    word = QByteArray(prev, offset);
                    qDebug() << word;
                    window += offset - 1;
                break;}



                case '+':
                case '-': {
                    if (!isDigit(*(window + 1)) || (*(window - 1)) != 'e') {
                        cutWord(stack, window, prev, word, lex_state, scope, lexems);
                        qDebug() << (*window) << word;
                    }
                break;}



                case '*':
                case '/': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems);
                    qDebug() << (*window) << word;
                break;}



                case '@': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems);
                    qDebug() << (*window) << word;
                break;}
                case '$': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems);
                    qDebug() << (*window) << word;
                break;}



                case '\\': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems);
                    qDebug() << (*window) << word;
                break;}



                case '~': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems);
                    qDebug() << (*window) << word;
                break;}



                case ';': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems);
                    qDebug() << (*window) << word;
                break;}


                case '\r':
                case '\n': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems);
                    qDebug() << (*window) << word;
                break;}

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
