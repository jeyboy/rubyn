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

#define CUT_WORD(window, prev) \
    QByteArray word(prev, window - prev);\
    new_lex_state = PredefinedRuby::obj().lexem(word);\
    if (new_lex_state == lex_undefined) {\
    \
    }\
    lex_state = stack.push(new_lex_state);\
    prev = window;

class LexerRuby : public Lexer {
protected:
    void parse(const char * window, Lexem lex_state) {
        ScopeNode * scope = new ScopeNode();
        Stack<Lexem> stack(lex_state);
        Lexem new_lex_state;

        const char * prev = window;

//        a + b is interpreted as a+b ( Here a is a local variable)
//        a  +b is interpreted as a(+b) ( Here a is a method call)

//        Ruby interprets semicolons and newline characters as the ending of a statement.
//        However, if Ruby encounters operators, such as +, −, or backslash at the end of a line,
//        they indicate the continuation of a statement.

//        Ruby identifier names may consist of alphanumeric characters and the underscore character ( _ ).

        while(window) {
            switch(*window) {
                case '\f':
                case '\v':
                case '\t':
                case ' ': {
                    int i = 0;
                    CUT_WORD(window, prev);
                    qDebug() << (*window) << word;
                break;}

                case '.': {
                    int i = 0;
                    CUT_WORD(window, prev);
                    qDebug() << (*window) << word;
                break;}

                case ',': {
                    int i = 0;
                    CUT_WORD(window, prev);
                    qDebug() << (*window) << word;
                break;}

                case '\'':
                case '"': {
                    int i = 0;
                    CUT_WORD(window, prev);
                    qDebug() << (*window) << word;
                    parseStr(window); // if false return error
                break;}

                case ':': {
                    int i = 0;
                    CUT_WORD(window, prev);
                    qDebug() << (*window) << word;
                break;}

                case '=': {
                    int i = 0;
                    CUT_WORD(window, prev);
                    qDebug() << (*window) << word;
                break;}
                case '|': {
                    int i = 0;
                    CUT_WORD(window, prev);
                    qDebug() << (*window) << word;
                break;}
                case '&': {
                    int i = 0;
                    CUT_WORD(window, prev);
                    qDebug() << (*window) << word;
                break;}
                case '!': {
                    int i = 0;
                    CUT_WORD(window, prev);
                    qDebug() << (*window) << word;
                break;}
                case '?': {
                    int i = 0;
                    CUT_WORD(window, prev);
                    qDebug() << (*window) << word;
                break;}
                case '<': {
                    int i = 0;
                    CUT_WORD(window, prev);
                    qDebug() << (*window) << word;
                break;}
                case '>': {
                    int i = 0;
                    CUT_WORD(window, prev);
                    qDebug() << (*window) << word;
                break;}


                case '[': {
                    int i = 0;
                    CUT_WORD(window, prev);
                    qDebug() << (*window) << word;
                break;}
                case ']': {
                    int i = 0;
                    CUT_WORD(window, prev);
                    qDebug() << (*window) << word;
                break;}

                case '(': {
                    int i = 0;
                    CUT_WORD(window, prev);
                    qDebug() << (*window) << word;
                break;}
                case ')': {
                    int i = 0;
                    CUT_WORD(window, prev);
                    qDebug() << (*window) << word;
                break;}

                case '{': {
                    int i = 0;
                    CUT_WORD(window, prev);
                    qDebug() << (*window) << word;
                break;}
                case '}': {
                    int i = 0;
                    CUT_WORD(window, prev);
                    qDebug() << (*window) << word;
                break;}

                case '#': {
                    int i = 0;
                    CUT_WORD(window, prev);
                    qDebug() << (*window) << word;
                break;}

                case '*':
                case '/':
                case '+':
                case '-': {
                    int i = 0;
                    CUT_WORD(window, prev);
                    qDebug() << (*window) << word;
                break;}

                case '@': {
                    int i = 0;
                    CUT_WORD(window, prev);
                    qDebug() << (*window) << word;
                break;}
                case '$': {
                    int i = 0;
                    CUT_WORD(window, prev);
                    qDebug() << (*window) << word;
                break;}

                case '\\': {
                    int i = 0;
                    CUT_WORD(window, prev);
                    qDebug() << (*window) << word;
                break;}

                case '~': {
                    int i = 0;
                    CUT_WORD(window, prev);
                    qDebug() << (*window) << word;
                break;}

                case ';': {
                    int i = 0;
                    CUT_WORD(window, prev);
                    qDebug() << (*window) << word;
                break;}

                case '`': {
                    int i = 0;
                    CUT_WORD(window, prev);
                    qDebug() << (*window) << word;
                break;}

                case '\r':
                case '\n': {
                    int i = 0;
                    CUT_WORD(window, prev);
                    qDebug() << (*window) << word;
                break;}

                default:;
            }

            ++window;
        }
    }
};

#endif // LEXER_RUBY_H
