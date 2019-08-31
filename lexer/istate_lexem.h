#ifndef STATE_LEXEMS_H
#define STATE_LEXEMS_H

#pragma once

#include "misc/defines.h"


//#define _Enum1_values a, b, c, d

//enum Enum1 {
//    _Enum1_values
//};

//// there aren't strongly typed enums
//class A {
//public:
//    enum Enum2 {
//        _Enum1_values, e, f
//    };
//};

//// there aren't strongly typed enums
//class B {
//public:
//    enum Enum3 {
//        _Enum1_values, g, h
//    };
//};




struct IState {
    enum Lexem : LEXEM_TYPE {
//        #define LEX_MIN -10
//        #define LEX_UNDEFINED_STATE -9
//        #define LEX_END_LINE_STATE -8
//        #define LEX_END_DOC_STATE -7
//        #define LEX_TAB -6
//        #define LEX_TABS -5
//        #define LEX_BLANK -4
//        #define LEX_BLANKS -3
//        #define LEX_IGNORE -2
//        #define LEX_DEFAULT_STATE -1
//        #define LEX_ERROR_STATE 0
//        #define LEX_NONE_STATE 1


        lex_min = -12,
        lex_undefined = -11,
        lex_end_line_state = -10,
        lex_end_doc = -9,
        lex_tab = -8,
        lex_tabs = -7,
        lex_blank = -6,
        lex_blanks = -5,
        lex_ignore = -4,
        lex_default = -3,


        lex_notice = -2,
        lex_warning = -1,
        lex_error = 0,

        lex_none = 1,


    //    lex_mark,
        lex_key,
        lex_predefined,
        lex_name,
    //    lex_def_name,
        lex_commentary,
        lex_string,
    //    lex_regexp,
        lex_method,



    //    lex_key = 1 << 19,
    //    lex_block = 1 << 20,
    //    lex_def = 1 << 21,
    //    lex_commentary = 1 << 22,
    //    lex_string = 1 << 23,
    //    lex_def_name = 1 << 24,
    //    lex_symbol = 1 << 25,
    //    lex_regexp = 1 << 26,
    //    lex_method = 1 << 27,
    //    lex_class = 1 << 28,
    //    lex_predefined = 1 << 29,
    //    lex_name = 1 << 30,
    //    //////////

        lex_undefined,
        lex_end_line,
        lex_end_doc,
        lex_tab,
        lex_blank,
        lex_blanks,
        lex_ignore,
    //    lex_chain_item, // service token

        lex_max
    };
};

#endif // STATE_LEXEMS_H
