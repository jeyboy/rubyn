#ifndef LEXER_RUBY_H
#define LEXER_RUBY_H

#include "parts/lexer/lexer.h"
#include "predefined_ruby.h"

//$ ruby [ options ] [.] [ programfile ] [ arguments ... ]

//-a
//Used with -n or -p to split each line. Check -n and -p options.

//-c
//Checks syntax only, without executing program.

//-C dir
//Changes directory before executing (equivalent to -X).

//-d
//Enables debug mode (equivalent to -debug).

//-F pat
//Specifies pat as the default separator pattern ($;) used by split.

//-e prog
//Specifies prog as the program from the command line. Specify multiple -e options for multiline programs.

//-h
//Displays an overview of command-line options.

//-i [ ext]
//Overwrites the file contents with program output. The original file is saved with the extension ext. If ext isn't specified, the original file is deleted.

//-I dir
//Adds dir as the directory for loading libraries.

//-K [ kcode]
//Specifies the multibyte character set code (e or E for EUC (extended Unix code); s or S for SJIS (Shift-JIS); u or U for UTF8; and a, A, n, or N for ASCII).

//-l
//Enables automatic line-end processing. Chops a newline from input lines and appends a newline to output lines.

//-n
//Places code within an input loop (as in while gets; ... end).

//-0[ octal]
//Sets default record separator ($/) as an octal. Defaults to \0 if octal not specified.

//-p
//Places code within an input loop. Writes $_ for each iteration.

//-r lib
//Uses require to load lib as a library before executing.

//-s
//Interprets any arguments between the program name and filename arguments fitting the pattern -xxx as a switch and defines the corresponding variable.

//-T [level]
//Sets the level for tainting checks (1 if level not specified).

//-v
//Displays version and enables verbose mode.

//-w
//Enables verbose mode. If program file not specified, reads from STDIN.

//-x [dir]
//Strips text before #!ruby line. Changes directory to dir before executing if dir is specified.

//-X dir
//Changes directory before executing (equivalent to -C).

//-y
//Enables parser debug mode.

//--copyright
//Displays copyright notice.

//--debug
//Enables debug mode (equivalent to -d).

//--help
//Displays an overview of command-line options (equivalent to h).

//--version
//Displays version.

//--verbose
//Enables verbose mode (equivalent to -v). Sets $VERBOSE to true.

//--yydebug
//Enables parser debug mode (equivalent to -y).


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

        char end_str_symb = 0;
        const char * prev = window;

//        a + b is interpreted as a+b ( Here a is a local variable)
//        a  +b is interpreted as a(+b) ( Here a is a method call)

//        Ruby interprets semicolons and newline characters as the ending of a statement.
//        However, if Ruby encounters operators, such as +, −, or backslash at the end of a line,
//        they indicate the continuation of a statement.

//        Ruby identifier names may consist of alphanumeric characters and the underscore character ( _ ).

        while(window) {
            switch(*window) {
                case '\v':
                case '\t':
                case ' ': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems);
                    qDebug() << (*window) << word;
                break;}



                case '.': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems);
                    qDebug() << (*window) << word;
                break;}



                case ',': {
                    cutWord(stack, window, prev, word, lex_state, scope, lexems);
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
                        stack.push(lex_string_start);
                    }

                    cutWord(stack, window, prev, word, lex_state, scope, lexems);
                    qDebug() << (*window) << word;
                break;}



                case ':': {
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
                    cutWord(stack, window, prev, word, lex_state, scope, lexems);
                    qDebug() << (*window) << word;
                break;}



                case '*':
                case '/':
                case '+':
                case '-': {
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
                ++window;
        }

        return lexems;
    }
};

#endif // LEXER_RUBY_H
