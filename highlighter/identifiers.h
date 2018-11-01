#ifndef IDENTIFIERS_H
#define IDENTIFIERS_H

#pragma once

#include "misc/defines.h"

enum Identifier : UID_TYPE {
    hid_para_content_popup = -14,
    hid_para_hover_overlay = -13,
    hid_search_results_overlay = -12,
    hid_folding_level_line = -11,
    hid_folding_content_popup = -10,
    hid_chars_limiter_line = -9,
    hid_breakpoint_line = -8,
    hid_breakpoints_range = -7,
    hid_folding_para_range = -6,
    hid_folding_hover_range = -5,
    hid_folded_overlay = -4,
    hid_current_line = -3,
    hid_current_line_extra = -2,
    hid_selection = -1,

    hid_none = 0,

    hid_operator,
    hid_label,
    hid_name_def,
    hid_name_call,
    hid_var,
    hid_const,
    hid_symbol,
    hid_keyword,
    hid_spec_keyword,
    hid_numeric,
    hid_string,
    hid_string_border,
    hid_regexp,
    hid_regexp_border,
    hid_commentary,
    hid_scope_visibility,
    hid_unclosed_para,

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

    hid_unknown_name,

    hid_error,
    hid_warning,
    hid_notice
};

#endif // IDENTIFIERS_H
