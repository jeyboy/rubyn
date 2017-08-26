#ifndef LEXER_RUBY_REGEXP_H
#define LEXER_RUBY_REGEXP_H

//http://www.regextester.com/22
//https://ruby-doc.org/core-2.4.1/Regexp.html

#include "parts/lexer/lexer.h"
#include "predefined_ruby.h"


//                        var = "Value|a|test"
//                        str = "a test Value"
//                        str.gsub( /#{var}/, 'foo' ) # => "foo foo foo"
//                        However, if your search string contains metacharacters and you do not want them interpreted as metacharacters, then use Regexp.escape like this:

//                        var = "*This*"
//                        str = "*This* is a string"
//                        p str.gsub( /#{Regexp.escape(var)}/, 'foo' )
//                        # => "foo is a string"
//                        Or just give gsub a string instead of a regular expression. In MRI >= 1.8.7, gsub will treat a string replacement argument as a plain string, not a regular expression:

//                        var = "*This*"
//                        str = "*This* is a string"
//                        p str.gsub(var, 'foo' ) # => "foo is a string"
//                        (It used to be that a string replacement argument to gsub was automatically converted to a regular expression. I know it was that way in 1.6. I don't recall which version introduced the change).

//                        As noted in other answers, you can use Regexp.new as an alternative to interpolation:

//                        var = "*This*"
//                        str = "*This* is a string"
//                        p str.gsub(Regexp.new(Regexp.escape(var)), 'foo' )
//                        # => "foo is a string"


class LexerRubyRegexp : public Lexer {
//    bool checkStack(const Lexem & lex_flag, LexerState * state, LexToken *& lexems_cursor, const int & word_length) {
//        if (lex_flag & lex_start) {
//            if ((lex_flag & lex_chain_block) == lex_chain_block) {
//                // INFO: if line is not empty then we have deal with inline branching
//                if (state -> new_line_state == lex_none)
//                    state -> stack -> push(lex_flag);
//            } else
//                state -> stack -> push(lex_flag);
//        } else if (lex_flag & lex_end) {
//            Lexem stack_top = state -> stack -> touch();
//            bool condition =
//                stack_top & lex_block ?
//                    lex_flag & lex_block
//                :
//                    EXCLUDE_BIT(lex_flag, lex_end) == EXCLUDE_BIT(stack_top, lex_start);


//            if (condition) {
//                state -> stack -> drop();
//            } else {
//                APPEND_ERR(QByteArray::number(state -> stack -> touch()) + QByteArrayLiteral(" required, but ") + QByteArray::number(lex_flag) + QByteArrayLiteral(" received"));
//                return false;
//            }
//        } else if (lex_flag & lex_chain_block) {
//            Lexem stack_top = state -> stack -> touch();

//            if (stack_top & lex_chain_block)
//                state -> stack -> replace(lex_flag);
//            else
//                APPEND_ERR(QByteArrayLiteral("Error in condition logic"));
//        }

//        return true;
//    }

//    bool cutWord(const char *& window, const char *& prev, LexerState * state,
//                 LexToken *& lexems_cursor, const Lexem & predefined_lexem = lex_none)
//    {
//        int word_length = window - prev;

//        if (word_length > 0) {
//            state -> word = QByteArray(prev, word_length);

//            Lexem & stack_top = state -> stack -> touch();

//            if ((stack_top & lex_def_start) > lex_start) {
//                state -> scope -> addVar(state -> word, 0); // new FilePoint() // TODO: write me
//                state -> stack -> replace(lex_block_start);
//                state -> lex_state = lex_var; // TODO: maybe change to something else
//            }
//            else state -> lex_state =
//                predefined_lexem
//                    ?
//                        predefined_lexem
//                    :
//                        PredefinedRuby::obj().lexem(state -> word);


//            if (state -> lex_state == lex_undefined) {
//                if (!state -> scope -> hasVar(state -> word)) {
//                    switch(*prev) { // INFO: determine type of word
//                        case ':': { state -> lex_state = lex_key; break;}
//                        case '$': { state -> lex_state = lex_global_var; break;}
//                        case '@': {
//                            if (*(prev + 1) == '@')
//                                state -> lex_state = lex_class_var;
//                            else
//                                state -> lex_state = lex_instance_var;
//                        break;}
//                        default: {
//                            state -> lex_state =
//                                (PREVCHAR == ':')
//                                    ?
//                                        lex_key
//                                    :
//                                        lex_local_var;
//                        }
//                    }

//                    state -> scope -> addVar(state -> word, 0); // new FilePoint() // TODO: write me

////                    if (!state -> var_def_state)
////                         state -> stack -> push(lex_var_chain_start);

////                    state -> scope -> addUnregVar(state -> word, 0); // new FilePoint() // TODO: write me

////                    if (state -> var_def_state == state -> lex_state) {
////                        APPEND_ERR(QByteArrayLiteral("Error in variable def"));
////                        return false;
////                    }

////                    state -> var_def_state = state -> lex_state;
//                }
//                else state -> lex_state = lex_var;

//            } else {
//                if (state -> lex_state & lex_continue) { // TODO: check me
//                    StackCell<Lexem> * top = state -> stack -> touchLevel();

//                    if (top -> obj == state -> lex_state || top -> obj == EXCLUDE_BIT(state -> lex_state, lex_continue)) {
//                        top -> obj = state -> lex_state;
//                    } else {
//                        APPEND_ERR(QByteArrayLiteral("Wrong state!!!"));
//                        return false;
//                    }
//                }
//                else if (!checkStack(state -> lex_state, state, lexems_cursor, word_length))
//                        return false;
//            }

//            Lexem highlightable = Lexem(state -> lex_state & lex_highlightable);

//            if (highlightable)
//                lexems_cursor = (
//                    lexems_cursor -> next =
//                        new LexToken(
//                            highlightable,
//                            state -> index,
//                            word_length
//                        )
//                );

//            qDebug() << state -> word;
//        } else if (predefined_lexem) {
//            state -> lex_state = predefined_lexem;

//            if (!checkStack(state -> lex_state, state, lexems_cursor, word_length))
//                return false;
//        }
//        else state -> lex_state = lex_ignore;

//        if (state -> lex_state < lex_end_line)
//            state -> new_line_state = state -> lex_state;



//        if (state -> next_offset) {
//            // proc delimiter
//            bool is_close_block = CURRCHAR == '}';

//            if (predefined_lexem != lex_string_end && (!is_close_block || (is_close_block && word_length == 0))) {
//                prev = window;

//                MOVE(state -> next_offset);

//                state -> delimiter = QByteArray(prev, window - prev);
//                state -> lex_state = PredefinedRuby::obj().lexem(state -> delimiter);

//                if (state -> lex_state == lex_end_line)
//                    state -> new_line_state = lex_none;
//                else if (state -> lex_state < lex_end_line)
//                    state -> new_line_state = state -> lex_state;


//                word_length = window - prev;

//                if (!checkStack(state -> lex_state, state, lexems_cursor, word_length))
//                    return false;

//    //            if (state -> var_def_state) {
//    //                if (state -> lex_state == lex_var_chain_end) {
//    //                    state -> scope -> clearUnregVar();
//    //                    state -> var_def_state = lex_none;
//    //                } else {
//    //                    if (
//    //                            (
//    //                                state -> lex_state == state -> var_def_state &&
//    //                                (
//    //                                    state -> var_def_state == lex_var ||
//    //                                    state -> var_def_state == lex_comma
//    //                                )
//    //                            )
//    //                            || state -> lex_state == lex_end_line
//    //                            || state -> lex_state == lex_binary_operator
//    //                    ) {

//    //                        APPEND_ERR(QByteArrayLiteral("Error in variable def"));
//    //                        return false;
//    //                    }
//    //                    else if (state -> lex_state != lex_ignore)
//    //                        state -> var_def_state = state -> lex_state;
//    //                }
//    //            }
//            }
//        }

//        state -> next_offset = 1;
//        prev = window;

//        return true;
//    }
protected:
    LexToken * parse(const char * window, LexerState * state, LexToken * lexems = new LexToken()) {
        LexToken * lexems_cursor = lexems;

        const char * prev = window;

        while(CURRCHAR) {
//            next_step:



            //                Character Classes¶ ↑

            //                A character class is delimited with square brackets ([, ]) and lists characters that may appear at that point in the match. /[ab]/ means a or b, as opposed to /ab/ which means a followed by b.

            //                The following metacharacters also behave like character classes:

            //                    /./ - Any character except a newline.

            //                    /./m - Any character (the m modifier enables multiline mode)

            //                    /\w/ - A word character ([a-zA-Z0-9_])

            //                    /\W/ - A non-word character ([^a-zA-Z0-9_]). Please take a look at Bug #4044 if using /\W/ with the /i modifier.

            //                    /\d/ - A digit character ([0-9])

            //                    /\D/ - A non-digit character ([^0-9])

            //                    /\h/ - A hexdigit character ([0-9a-fA-F])

            //                    /\H/ - A non-hexdigit character ([^0-9a-fA-F])

            //                    /\s/ - A whitespace character: /[ \t\r\n\f\v]/

            //                    /\S/ - A non-whitespace character: /[^ \t\r\n\f\v]/

            //                POSIX bracket expressions are also similar to character classes. They provide a portable alternative to the above, with the added benefit that they encompass non-ASCII characters. For instance, /\d/ matches only the ASCII decimal digits (0-9); whereas /[[:digit:]]/ matches any character in the Unicode Nd category.

            //                    /[[:alnum:]]/ - Alphabetic and numeric character

            //                    /[[:alpha:]]/ - Alphabetic character

            //                    /[[:blank:]]/ - Space or tab

            //                    /[[:cntrl:]]/ - Control character

            //                    /[[:digit:]]/ - Digit

            //                    /[[:graph:]]/ - Non-blank character (excludes spaces, control characters, and similar)

            //                    /[[:lower:]]/ - Lowercase alphabetical character

            //                    /[[:print:]]/ - Like [:graph:], but includes the space character

            //                    /[[:punct:]]/ - Punctuation character

            //                    /[[:space:]]/ - Whitespace character ([:blank:], newline, carriage return, etc.)

            //                    /[[:upper:]]/ - Uppercase alphabetical

            //                    /[[:xdigit:]]/ - Digit allowed in a hexadecimal number (i.e., 0-9a-fA-F)

            //                Ruby also supports the following non-POSIX character classes:

            //                    /[[:word:]]/ - A character in one of the following Unicode general categories Letter, Mark, Number, Connector_Punctuation

            //                    /[[:ascii:]]/ - A character in the ASCII character set



            //                Repetition¶ ↑

            //                The constructs described so far match a single character. They can be followed by a repetition metacharacter to specify how many times they need to occur. Such metacharacters are called quantifiers.

            //                    * - Zero or more times

            //                    + - One or more times

            //                    ? - Zero or one times (optional)

            //                    {n} - Exactly n times

            //                    {n,} - n or more times

            //                    {,m} - m or less times

            //                    {n,m} - At least n and at most m times



            //                ^ - Matches beginning of line

            //                $ - Matches end of line

            //                \A - Matches beginning of string.

            //                \Z - Matches end of string. If string ends with a newline, it matches just before newline

            //                \z - Matches end of string

            //                \G - Matches first matching position:
            //                  In methods like String#gsub and String#scan, it changes on each iteration.
            //                  It initially matches the beginning of subject, and in each following iteration it matches where the last match finished.

            //                \b - Matches word boundaries when outside brackets; backspace (0x08) when inside brackets

            //                \B - Matches non-word boundaries

            //                (?=pat) - Positive lookahead assertion: ensures that the following characters match pat, but doesn't include those characters in the matched text

            //                (?!pat) - Negative lookahead assertion: ensures that the following characters do not match pat, but doesn't include those characters in the matched text

            //                (?<=pat) - Positive lookbehind assertion: ensures that the preceding characters match pat, but doesn't include those characters in the matched text

            //                (?<!pat) - Negative lookbehind assertion: ensures that the preceding characters do not match pat, but doesn't include those characters in the matched text



            //                The \p{} construct matches characters with the named property, much like POSIX bracket classes.

            //                    /\p{Alnum}/ - Alphabetic and numeric character

            //                    /\p{Alpha}/ - Alphabetic character

            //                    /\p{Blank}/ - Space or tab

            //                    /\p{Cntrl}/ - Control character

            //                    /\p{Digit}/ - Digit

            //                    /\p{Graph}/ - Non-blank character (excludes spaces, control characters, and similar)

            //                    /\p{Lower}/ - Lowercase alphabetical character

            //                    /\p{Print}/ - Like \p{Graph}, but includes the space character

            //                    /\p{Punct}/ - Punctuation character

            //                    /\p{Space}/ - Whitespace character ([:blank:], newline, carriage return, etc.)

            //                    /\p{Upper}/ - Uppercase alphabetical

            //                    /\p{XDigit}/ - Digit allowed in a hexadecimal number (i.e., 0-9a-fA-F)

            //                    /\p{Word}/ - A member of one of the following Unicode general category Letter, Mark, Number, Connector_Punctuation

            //                    /\p{ASCII}/ - A character in the ASCII character set

            //                    /\p{Any}/ - Any Unicode character (including unassigned characters)

            //                    /\p{Assigned}/ - An assigned character

            //                A Unicode character’s General Category value can also be matched with \p{Ab} where Ab is the category’s abbreviation as described below:

            //                    /\p{L}/ - 'Letter'

            //                    /\p{Ll}/ - 'Letter: Lowercase'

            //                    /\p{Lm}/ - 'Letter: Mark'

            //                    /\p{Lo}/ - 'Letter: Other'

            //                    /\p{Lt}/ - 'Letter: Titlecase'

            //                    /\p{Lu}/ - 'Letter: Uppercase

            //                    /\p{Lo}/ - 'Letter: Other'

            //                    /\p{M}/ - 'Mark'

            //                    /\p{Mn}/ - 'Mark: Nonspacing'

            //                    /\p{Mc}/ - 'Mark: Spacing Combining'

            //                    /\p{Me}/ - 'Mark: Enclosing'

            //                    /\p{N}/ - 'Number'

            //                    /\p{Nd}/ - 'Number: Decimal Digit'

            //                    /\p{Nl}/ - 'Number: Letter'

            //                    /\p{No}/ - 'Number: Other'

            //                    /\p{P}/ - 'Punctuation'

            //                    /\p{Pc}/ - 'Punctuation: Connector'

            //                    /\p{Pd}/ - 'Punctuation: Dash'

            //                    /\p{Ps}/ - 'Punctuation: Open'

            //                    /\p{Pe}/ - 'Punctuation: Close'

            //                    /\p{Pi}/ - 'Punctuation: Initial Quote'

            //                    /\p{Pf}/ - 'Punctuation: Final Quote'

            //                    /\p{Po}/ - 'Punctuation: Other'

            //                    /\p{S}/ - 'Symbol'

            //                    /\p{Sm}/ - 'Symbol: Math'

            //                    /\p{Sc}/ - 'Symbol: Currency'

            //                    /\p{Sc}/ - 'Symbol: Currency'

            //                    /\p{Sk}/ - 'Symbol: Modifier'

            //                    /\p{So}/ - 'Symbol: Other'

            //                    /\p{Z}/ - 'Separator'

            //                    /\p{Zs}/ - 'Separator: Space'

            //                    /\p{Zl}/ - 'Separator: Line'

            //                    /\p{Zp}/ - 'Separator: Paragraph'

            //                    /\p{C}/ - 'Other'

            //                    /\p{Cc}/ - 'Other: Control'

            //                    /\p{Cf}/ - 'Other: Format'

            //                    /\p{Cn}/ - 'Other: Not Assigned'

            //                    /\p{Co}/ - 'Other: Private Use'

            //                    /\p{Cs}/ - 'Other: Surrogate'


            // To match a backslash literally backslash-escape that: \\\

            // OPTIONS

            //            case 'm': // Treat a newline as a character matched by .
            //            case 'i': // Ignore case
            //            case 'x': // Ignore whitespace and comments in the pattern
            //            case 'o': // Perform #{} interpolation only once
            //            case 'u': // encoding:  UTF-8
            //            case 'e': // encoding:  EUC-JP
            //            case 's': // encoding:  Windows-31J
            //            case 'n': // encoding:  ASCII-8BIT

            switch(CURRCHAR) {
                case '|': {

                break;}



                case '^': {

                break;}



                case '.': {

                break;}



                case '?': {

                break;}



                case '+': {

                break;}



                case '*': {

                break;}



                case '(': {

                break;}
                case ')': {

                break;}



                case '[': {

                break;}
                case ']': {

                break;}



                case '{': {

                break;}
                case '}': {

                break;}



                case '/': {

                break;}



                default:
                    iterate:
                        // Ruby identifier names may consist of alphanumeric characters and the
                        //  underscore character ( _ ).
                        // check if word isWord(*window)
                        ITERATE;
            }
        }

        exit:
            return lexems;
    }
};

#endif // LEXER_RUBY_REGEXP_H
