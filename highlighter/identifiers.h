#ifndef IDENTIFIERS_H
#define IDENTIFIERS_H

#pragma once

#include "misc/defines.h"

enum Identifier : UID_TYPE {
    hid_custom = -80, // not used yet

    hid_project_tree_tmp_range = -70,
    hid_project_tree_spec_range = -69,
    hid_project_tree_public_range = -68,
    hid_project_tree_log_range = -67,
    hid_project_tree_db_range = -66,
    hid_project_tree_config_range = -65,
    hid_project_tree_app_range = -64,

    hid_extra_icons_range = -18,
    hid_para_hover_line = -17,
    hid_para_content_popup = -16,
    hid_para_hover_overlay2 = -15,
    hid_para_hover_overlay = -14,
    hid_search_results_overlay = -13,
    hid_folding_level_line = -12,
    hid_folding_content_popup = -11,
    hid_chars_limiter_line = -10,
    hid_breakpoint_line = -9,
    hid_breakpoints_range = -8,
    hid_folding_para_range = -7,
    hid_folding_hover_range = -6,
    hid_folded_selected_overlay = -5,
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
    hid_ternary,
    hid_sequence,

    hid_unknown_name,

    hid_error,
    hid_warning,
    hid_notice
};

#endif // IDENTIFIERS_H
