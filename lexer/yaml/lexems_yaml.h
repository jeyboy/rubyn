#ifndef LEXEMS_YAML_H
#define LEXEMS_YAML_H

#pragma once

#include <qbytearray.h>

#include "misc/defines.h"

enum LexemsYAML : LEXEM_TYPE {
    lex_none = 0,

    ////////// highlightable
    yml_lex_error,
    yml_lex_warning,
    yml_lex_notice,

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

struct Lexems {
    static QByteArray toStr(const Lexem & lexem) {
        switch(lexem) {
            case lex_error: return QByteArrayLiteral("error_token");
            case lex_warning: return QByteArrayLiteral("warning_token");
            case lex_notice: return QByteArrayLiteral("notice_token");
            case lex_none: return QByteArrayLiteral("none_token");

            case lex_mark: return QByteArrayLiteral("mark_token");
            case lex_key: return QByteArrayLiteral("key_token");
            case lex_predefined: return QByteArrayLiteral("predefined_token");
            case lex_name: return QByteArrayLiteral("name_token");
            case lex_def_name: return QByteArrayLiteral("def_name_token");
            case lex_commentary: return QByteArrayLiteral("commentary_token");
            case lex_string: return QByteArrayLiteral("string_token");
            case lex_regexp: return QByteArrayLiteral("regexp_token");
            case lex_method: return QByteArrayLiteral("method_token");


            case lex_super: return QByteArrayLiteral("super_token");
            case lex_self: return QByteArrayLiteral("self_token");

            case lex_expression: return QByteArrayLiteral("expression_token");
            case lex_predefined_expression: return QByteArrayLiteral("predefined_expression_token");
            case lex_word: return QByteArrayLiteral("word_token");

            case lex_unary_operator: return QByteArrayLiteral("unary_operator_token");
            case lex_binary_operator: return QByteArrayLiteral("binary_operator_token");

            case lex_bin: return QByteArrayLiteral("bin_numb_token");
            case lex_oct: return QByteArrayLiteral("oct_numb_token");
            case lex_dec: return QByteArrayLiteral("dec_numb_token");
            case lex_hex: return QByteArrayLiteral("hex_numb_token");
            case lex_float: return QByteArrayLiteral("float_numb_token");
            case lex_double: return QByteArrayLiteral("double_numb_token");

            case lex_symbol: return QByteArrayLiteral("symbol_token");
            case lex_const: return QByteArrayLiteral("const_token");
            case lex_var_scoped: return QByteArrayLiteral("var_scoped_token");
            case lex_var_local: return QByteArrayLiteral("var_local_token");
            case lex_var_instance: return QByteArrayLiteral("var_instance_token");
            case lex_var_object: return QByteArrayLiteral("var_object_token");
            case lex_var_global: return QByteArrayLiteral("var_global_token");

            case lex_interpolation: return QByteArrayLiteral("interpolation_token");

            case lex_dot: return QByteArrayLiteral("dot_token");
            case lex_dot_dot: return QByteArrayLiteral("dot_dot_token");
            case lex_dot_dot_dot: return QByteArrayLiteral("dot_dot_dot_token");
            case lex_rocket: return QByteArrayLiteral("rocket_token");
            case lex_colon: return QByteArrayLiteral("color_token");
            case lex_semicolon: return QByteArrayLiteral("semicolon_token");
            case lex_resolution: return QByteArrayLiteral("resolution_token");
            case lex_comma: return QByteArrayLiteral("comma_token");
            case lex_open_curly_bracket: return QByteArrayLiteral("open_curly_bracket_token");
            case lex_close_curly_bracket: return QByteArrayLiteral("close_curly_bracket_token");
            case lex_open_square_bracket: return QByteArrayLiteral("open_square_bracket_token");
            case lex_close_square_bracket: return QByteArrayLiteral("close_square_brucket_token");


            case lex_operator_assigment: return QByteArrayLiteral("operator_assigment_token");
            case lex_operator_comparison: return QByteArrayLiteral("operator_comparison_token");
            case lex_operator_equality: return QByteArrayLiteral("operator_equality_token");
            case lex_operator_not_equal: return QByteArrayLiteral("operator_not_equal_token");

            case lex_operator_less: return QByteArrayLiteral("operator_less_token");
            case lex_operator_less_eql: return QByteArrayLiteral("operator_less_eql_token");
            case lex_operator_great: return QByteArrayLiteral("operator_great_token");
            case lex_operator_great_eql: return QByteArrayLiteral("operator_great_eql_token");

            case lex_operator_sort: return QByteArrayLiteral("operator_sort_token");

            case lex_operator_add: return QByteArrayLiteral("operator_add_token");
            case lex_operator_add_assigment: return QByteArrayLiteral("operator_add_assigment_token");
            case lex_operator_increase: return QByteArrayLiteral("operator_increase_token");
            case lex_operator_minus: return QByteArrayLiteral("operator_minus_token");
            case lex_operator_minus_assigment: return QByteArrayLiteral("operator_minus_assigment_token");
            case lex_operator_decrease: return QByteArrayLiteral("operator_decrease_token");
            case lex_operator_multiplication: return QByteArrayLiteral("operator_multiply_token");
            case lex_operator_multiplication_assigment: return QByteArrayLiteral("operator_multiply_assigment_token");
            case lex_operator_division: return QByteArrayLiteral("operator_divide_token");
            case lex_operator_division_assigment: return QByteArrayLiteral("operator_divide_assigment_token");
            case lex_operator_exponentiation: return QByteArrayLiteral("operator_exponent_token");
            case lex_operator_exponentiation_assigment: return QByteArrayLiteral("operator_exponent_assigment_token");
            case lex_operator_modulus: return QByteArrayLiteral("operator_modulus_token");
            case lex_operator_modulus_assigment: return QByteArrayLiteral("operator_modulus_assigment_token");

            case lex_operator_safe_navigation: return QByteArrayLiteral("operator_safe_navigation_token");

            case lex_operator_bit_and: return QByteArrayLiteral("operator_bit_and_token");
            case lex_operator_bit_or: return QByteArrayLiteral("operator_bit_or_token");
            case lex_operator_bit_exclusive_or: return QByteArrayLiteral("operator_bit_exclusive_or_token");
            case lex_operator_bit_not: return QByteArrayLiteral("operator_bit_not_token");
            case lex_operator_bit_left_shift: return QByteArrayLiteral("operator_bit_left_shift_token");
            case lex_operator_bit_right_shift: return QByteArrayLiteral("operator_bit_right_shift_token");

            case lex_operator_and: return QByteArrayLiteral("operator_and_token");
            case lex_operator_or: return QByteArrayLiteral("operator_or_token");
            case lex_operator_or_assigment: return QByteArrayLiteral("operator_or_assigment_token");
            case lex_operator_not: return QByteArrayLiteral("operator_not_token");


            case lex_method_def: return QByteArrayLiteral("method_def_token");
            case lex_method_def_scope: return QByteArrayLiteral("method_def_scope_token");
            case lex_method_def_scoped: return QByteArrayLiteral("method_def_scoped_token");
            case lex_method_def_name: return QByteArrayLiteral("method_def_name_token");
            case lex_method_def_scoped_name: return QByteArrayLiteral("method_def_scoped_name_token");
            case lex_method_def_block: return QByteArrayLiteral("method_def_block_token");
            case lex_method_def_block_end: return QByteArrayLiteral("method_def_block_end_token");
            case lex_method_def_vars_start: return QByteArrayLiteral("method_def_vars_start_token");
            case lex_method_def_var_attr: return QByteArrayLiteral("method_def_var_attr_token");
            case lex_method_def_var_type: return QByteArrayLiteral("method_def_var_type_token");
            case lex_method_def_var_access_type: return QByteArrayLiteral("method_def_var_access_type_token");
            case lex_method_def_var_name: return QByteArrayLiteral("method_def_var_name_token");
            case lex_method_def_vars_splitter: return QByteArrayLiteral("method_def_vars_splitter_token");
            case lex_method_def_vars_end: return QByteArrayLiteral("method_def_vars_end_token");


            case lex_predefined_method_call_name: return QByteArrayLiteral("predefined_method_call_name_token");

            case lex_method_call_name: return QByteArrayLiteral("method_call_name_token");
            case lex_method_call_vars_start: return QByteArrayLiteral("method_call_vars_start_token");
            case lex_method_call_var_entry: return QByteArrayLiteral("method_call_var_entry_token");
            case lex_method_call_vars_splitter: return QByteArrayLiteral("method_call_vars_splitter_token");
            case lex_method_call_vars_end: return QByteArrayLiteral("method_call_vars_end_token");
            case lex_method_call_block: return QByteArrayLiteral("method_call_block_token");
            case lex_method_call_block_vars_start: return QByteArrayLiteral("method_call_block_vars_start_token");
            case lex_method_call_block_var_name: return QByteArrayLiteral("method_call_block_var_name_token");
            case lex_method_call_block_vars_splitter: return QByteArrayLiteral("method_call_block_vars_splitter_token");
            case lex_method_call_block_vars_end: return QByteArrayLiteral("method_call_block_vars_end_token");
            case lex_method_call_block_end: return QByteArrayLiteral("method_call_block_end_token");


            case lex_class_def: return QByteArrayLiteral("class_def_token");
            case lex_class_def_name: return QByteArrayLiteral("class_def_name_token");
            case lex_class_def_extension: return QByteArrayLiteral("class_def_extension_token");
            case lex_class_def_extender: return QByteArrayLiteral("class_def_extender_token");
            case lex_class_def_inheritance: return QByteArrayLiteral("class_def_inheritance_token");
            case lex_class_def_ancestor: return QByteArrayLiteral("class_def_ancestor_token");
            case lex_class_def_block: return QByteArrayLiteral("class_def_block_token");
            case lex_class_def_block_end: return QByteArrayLiteral("class_def_block_end_token");

            case lex_class_def_short: return QByteArrayLiteral("class_def_short_token");
            case lex_class_def_short_accessing: return QByteArrayLiteral("class_def_short_accessing_token");
            case lex_class_def_short_method: return QByteArrayLiteral("class_def_short_method_token");
            case lex_class_def_short_block: return QByteArrayLiteral("class_def_short_block_token");
            case lex_class_def_short_block_end: return QByteArrayLiteral("class_def_short_block_end_token");


            case lex_module_def: return QByteArrayLiteral("module_def_token");
            case lex_module_def_name: return QByteArrayLiteral("module_def_name_token");
            case lex_module_def_resolution: return QByteArrayLiteral("module_def_resolution_token");
            case lex_module_def_block: return QByteArrayLiteral("module_def_block_token");
            case lex_module_def_block_end: return QByteArrayLiteral("module_def_block_end_token");


            case lex_lambda_def: return QByteArrayLiteral("lambda_def_token");
            case lex_lambda_def_vars_start: return QByteArrayLiteral("lambda_def_vars_start_token");
            case lex_lambda_def_var_attr: return QByteArrayLiteral("lambda_def_var_attr_token");
            case lex_lambda_def_var_type: return QByteArrayLiteral("lambda_def_var_type_token");
            case lex_lambda_def_var_access_type: return QByteArrayLiteral("lambda_def_var_access_type_token");
            case lex_lambda_def_var_name: return QByteArrayLiteral("lambda_def_var_name_token");
            case lex_lambda_def_vars_splitter: return QByteArrayLiteral("lambda_def_vars_splitter_token");
            case lex_lambda_def_vars_end: return QByteArrayLiteral("lambda_def_vars_end_token");
            case lex_lambda_def_block: return QByteArrayLiteral("lambda_def_block_token");
            case lex_lambda_def_block_end: return QByteArrayLiteral("lambda_def_block_end_token");


            case lex_proc_def: return QByteArrayLiteral("proc_def_token");
            case lex_proc_def_block: return QByteArrayLiteral("proc_def_block_token");
            case lex_proc_def_block_end: return QByteArrayLiteral("proc_def_block_end_token");
            case lex_proc_def_vars_start: return QByteArrayLiteral("proc_def_vars_start_token");
            case lex_proc_def_var_attr: return QByteArrayLiteral("proc_def_var_attr_token");
            case lex_proc_def_var_type: return QByteArrayLiteral("proc_def_var_type_token");
            case lex_proc_def_var_access_type: return QByteArrayLiteral("proc_def_var_access_type_token");
            case lex_proc_def_var_name: return QByteArrayLiteral("proc_def_var_name_token");
            case lex_proc_def_vars_splitter: return QByteArrayLiteral("proc_def_vars_splitter_token");
            case lex_proc_def_vars_end: return QByteArrayLiteral("proc_def_vars_end_token");

            case lex_inline_commentary: return QByteArrayLiteral("inline_commentary_token");

            case lex_commentary_start: return QByteArrayLiteral("commentary_start_token");
            case lex_commentary_continue: return QByteArrayLiteral("commentary_continue_token");
            case lex_commentary_end: return QByteArrayLiteral("commentary_end_token");

            case lex_command_start: return QByteArrayLiteral("command_start_token");
            case lex_command_interception: return QByteArrayLiteral("command_interception_token");
            case lex_command_intercepted: return QByteArrayLiteral("command_intercepted_token");
            case lex_command_continue: return QByteArrayLiteral("command_continue_token");
            case lex_command_end: return QByteArrayLiteral("command_end_token");

            case lex_string_start: return QByteArrayLiteral("string_start_token");
            case lex_string_continue: return QByteArrayLiteral("string_continue_token");
            case lex_string_end: return QByteArrayLiteral("string_end_token");

            case lex_estring_start: return QByteArrayLiteral("estring_start_token");
            case lex_estring_interception: return QByteArrayLiteral("estring_interception_token");
            case lex_estring_intercepted: return QByteArrayLiteral("estring_intercepted_token");
            case lex_estring_continue: return QByteArrayLiteral("estring_continue_token");
            case lex_estring_end: return QByteArrayLiteral("estring_end_token");

            case lex_percent_presentation_start: return QByteArrayLiteral("percentage_presentation_start_token");
            case lex_percent_presentation_continue: return QByteArrayLiteral("percentage_presentation_continue_token");
            case lex_percent_presentation_end: return QByteArrayLiteral("percentage_presentation_end_token");

            case lex_epercent_presentation_start: return QByteArrayLiteral("epercentage_presentation_start_token");
            case lex_epercent_presentation_interception: return QByteArrayLiteral("epercentage_presentation_interception_token");
            case lex_epercent_presentation_intercepted: return QByteArrayLiteral("epercentage_presentation_intercepted_token");
            case lex_epercent_presentation_continue: return QByteArrayLiteral("epercentage_presentation_continue_token");
            case lex_epercent_presentation_end: return QByteArrayLiteral("epercentage_presentation_end_token");

            case lex_heredoc_mark: return QByteArrayLiteral("heredoc_mark_token");
            case lex_heredoc_start: return QByteArrayLiteral("heredoc_start_token");
            case lex_heredoc_continue: return QByteArrayLiteral("heredoc_continue_token");
            case lex_heredoc_end: return QByteArrayLiteral("heredoc_end_token");

            case lex_heredoc_intended_mark: return QByteArrayLiteral("heredoc_intended_mark_token");
            case lex_heredoc_intended_start: return QByteArrayLiteral("heredoc_intended_start_token");
            case lex_heredoc_intended_continue: return QByteArrayLiteral("heredoc_intended_continue_token");

            case lex_eheredoc_mark: return QByteArrayLiteral("eheredoc_mark_token");
            case lex_eheredoc_start: return QByteArrayLiteral("eheredoc_start_token");
            case lex_eheredoc_interception: return QByteArrayLiteral("eheredoc_interception_token");
            case lex_eheredoc_intercepted: return QByteArrayLiteral("eheredoc_intercepted_token");
            case lex_eheredoc_continue: return QByteArrayLiteral("eheredoc_continue_token");

            case lex_eheredoc_intended_mark: return QByteArrayLiteral("eheredoc_intended_mark_token");
            case lex_eheredoc_intended_start: return QByteArrayLiteral("eheredoc_intended_start_token");
            case lex_eheredoc_intended_interception: return QByteArrayLiteral("eheredoc_intended_interception_token");
            case lex_eheredoc_intended_intercepted: return QByteArrayLiteral("eheredoc_intended_intercepted_token");
            case lex_eheredoc_intended_continue: return QByteArrayLiteral("eheredoc_intended_continue_token");

            case lex_cheredoc_mark: return QByteArrayLiteral("cheredoc_mark_token");
            case lex_cheredoc_start: return QByteArrayLiteral("cheredoc_start_token");
            case lex_cheredoc_interception: return QByteArrayLiteral("cheredoc_interception_token");
            case lex_cheredoc_intercepted: return QByteArrayLiteral("cheredoc_intercepted_token");
            case lex_cheredoc_continue: return QByteArrayLiteral("cheredoc_continue_token");

            case lex_cheredoc_intended_mark: return QByteArrayLiteral("cheredoc_intended_mark_token");
            case lex_cheredoc_intended_start: return QByteArrayLiteral("cheredoc_intended_start_token");
            case lex_cheredoc_intended_interception: return QByteArrayLiteral("cheredoc_intended_interception_token");
            case lex_cheredoc_intended_intercepted: return QByteArrayLiteral("cheredoc_intended_intercepted_token");
            case lex_cheredoc_intended_continue: return QByteArrayLiteral("cheredoc_intended_continue_token");
        //////////////////////////////////////


            case lex_regexp_start: return QByteArrayLiteral("regexp_start_token");
            case lex_regexp_interception: return QByteArrayLiteral("regexp_interception_token");
            case lex_regexp_intercepted: return QByteArrayLiteral("regexp_intercepted_token");
            case lex_regexp_continue: return QByteArrayLiteral("regexp_continue_token");
            case lex_regexp_end: return QByteArrayLiteral("regexp_end_token");


            case lex_require: return QByteArrayLiteral("require_token");
            case lex_require_path: return QByteArrayLiteral("require_path_token");

            case lex_include: return QByteArrayLiteral("include_token");
            case lex_include_obj: return QByteArrayLiteral("include_obj_token");
            case lex_include_resolution: return QByteArrayLiteral("include_resolution_token");
            case lex_include_name: return QByteArrayLiteral("include_name_token");

            case lex_extend: return QByteArrayLiteral("extend_token");
            case lex_extend_obj: return QByteArrayLiteral("extend_obj_token");
            case lex_extend_resolution: return QByteArrayLiteral("extend_resolution_token");
            case lex_extend_name: return QByteArrayLiteral("extend_name_token");

            case lex_undef: return QByteArrayLiteral("undef_token");
            case lex_undef_name: return QByteArrayLiteral("undef_name_token");

            case lex_visibility_scope: return QByteArrayLiteral("visibility_scope_token");
            case lex_visibility_scope_arg: return QByteArrayLiteral("visibility_scope_arg_token");
            case lex_visibility_scope_arg_splitter: return QByteArrayLiteral("visibility_scope_arg_splitter_token");

            case lex_alias: return QByteArrayLiteral("alias_token");
            case lex_alias_base_name: return QByteArrayLiteral("alias_base_name_token");
            case lex_alias_alt_name: return QByteArrayLiteral("alias_alt_name_token");


            case lex_wrap_start: return QByteArrayLiteral("wrap_start_token");
            case lex_wrap_end: return QByteArrayLiteral("wrap_end_token");


            case lex_hash_start: return QByteArrayLiteral("hash_start_token");
            case lex_hash_item: return QByteArrayLiteral("hash_item_token");
            case lex_hash_key: return QByteArrayLiteral("hash_key_token");
            case lex_hash_key_with_relation: return QByteArrayLiteral("hash_key_with_relation_token");
            case lex_hash_key_relation: return QByteArrayLiteral("hash_key_relation_token");
            case lex_hash_val: return QByteArrayLiteral("hash_val_token");
            case lex_hash_splitter: return QByteArrayLiteral("hash_splitter_token");
            case lex_hash_end: return QByteArrayLiteral("hash_end_token");


            case lex_array_start: return QByteArrayLiteral("array_start_token");
            case lex_array_item: return QByteArrayLiteral("array_item_token");
            case lex_array_splitter: return QByteArrayLiteral("array_splitter_token");
            case lex_array_end: return QByteArrayLiteral("array_end_token");


            case lex_ternary_main_start: return QByteArrayLiteral("ternary_main_start_token");
            case lex_ternary_main_val: return QByteArrayLiteral("ternary_main_val_token");
            case lex_ternary_alt_start: return QByteArrayLiteral("ternary_alt_start_token");
            case lex_ternary_alt_val: return QByteArrayLiteral("ternary_alt_val_token");

            case lex_then: return QByteArrayLiteral("then_token");
            case lex_in: return QByteArrayLiteral("in_token");

            case lex_unless: return QByteArrayLiteral("unless_token");
            case lex_unless_rule: return QByteArrayLiteral("unless_rule_token");
            case lex_unless_then: return QByteArrayLiteral("unless_then_token");
            case lex_unless_block: return QByteArrayLiteral("unless_block_token");
            case lex_unless_block_end: return QByteArrayLiteral("unless_block_end_token");

            case lex_if: return QByteArrayLiteral("if_token");
            case lex_if_rule: return QByteArrayLiteral("if_rule_token");
            case lex_if_then: return QByteArrayLiteral("if_then_token");
            case lex_if_block: return QByteArrayLiteral("if_block_token");
            case lex_if_block_end: return QByteArrayLiteral("if_block_end_token");

            case lex_elsif: return QByteArrayLiteral("elsif_token");
            case lex_elsif_rule: return QByteArrayLiteral("elsif_rule_token");
            case lex_elsif_then: return QByteArrayLiteral("elsif_then_token");
            case lex_elsif_block: return QByteArrayLiteral("elsif_block_token");
            case lex_elsif_block_end: return QByteArrayLiteral("elsif_block_end_token");

            case lex_else: return QByteArrayLiteral("else_token");
            case lex_else_block: return QByteArrayLiteral("else_block_token");
            case lex_else_block_end: return QByteArrayLiteral("else_block_end_token");


            case lex_switch: return QByteArrayLiteral("switch_token");
            case lex_switch_target: return QByteArrayLiteral("switch_target_token");
            case lex_switch_block: return QByteArrayLiteral("switch_block_token");
            case lex_switch_block_end: return QByteArrayLiteral("switch_block_end_token");

            case lex_case: return QByteArrayLiteral("case_token");
            case lex_case_target: return QByteArrayLiteral("case_target_token");
            case lex_case_target_block: return QByteArrayLiteral("case_target_block_token");
            case lex_case_target_block_end: return QByteArrayLiteral("case_target_block_end_token");

            case lex_when: return QByteArrayLiteral("when_token");
            case lex_when_target: return QByteArrayLiteral("when_target_token");
            case lex_when_target_splitter: return QByteArrayLiteral("when_target_splitter_token");
            case lex_when_then: return QByteArrayLiteral("when_then_token");
            case lex_when_else: return QByteArrayLiteral("when_else_token");
            case lex_when_block: return QByteArrayLiteral("when_block_token");
            case lex_when_block_end: return QByteArrayLiteral("when_block_token");


            case lex_while: return QByteArrayLiteral("while_token");
            case lex_while_rule: return QByteArrayLiteral("while_rule_token");
            case lex_while_block: return QByteArrayLiteral("while_block_token");
            case lex_while_block_end: return QByteArrayLiteral("while_block_end_token");

            case lex_until: return QByteArrayLiteral("until_token");
            case lex_until_rule: return QByteArrayLiteral("until_rule_token");
            case lex_until_block: return QByteArrayLiteral("until_block_token");
            case lex_until_block_end: return QByteArrayLiteral("until_block_end_token");

            case lex_for: return QByteArrayLiteral("for_token");
            case lex_for_vars_start: return QByteArrayLiteral("for_vars_start_token");
            case lex_for_var: return QByteArrayLiteral("for_var_token");
            case lex_for_vars_splitter: return QByteArrayLiteral("for_vars_splitter_token");
            case lex_for_vars_end: return QByteArrayLiteral("for_vars_token");

            case lex_for_in: return QByteArrayLiteral("for_in_token");
            case lex_for_in_target: return QByteArrayLiteral("for_in_target_token");

            case lex_loop_break: return QByteArrayLiteral("loop_break_token");
            case lex_loop_redo: return QByteArrayLiteral("loop_redo_token");
            case lex_loop_next: return QByteArrayLiteral("loop_next_token");

            case lex_do: return QByteArrayLiteral("do_token");
            case lex_do_block_start: return QByteArrayLiteral("do_block_start_token");
            case lex_do_block_vars_start: return QByteArrayLiteral("do_block_vars_start_token");
            case lex_do_block_var_access_type: return QByteArrayLiteral("do_block_var_access_type_token");
            case lex_do_block_var_name: return QByteArrayLiteral("do_block_var_name_token");
            case lex_do_block_vars_splitter: return QByteArrayLiteral("do_block_vars_splitter_token");
            case lex_do_block_vars_end: return QByteArrayLiteral("do_block_vars_end_token");

            case lex_inline_block_start: return QByteArrayLiteral("inline_block_start_token");

            case lex_inline_do_block_start: return QByteArrayLiteral("inline_do_block_start_token");
            case lex_inline_do_block_vars_start: return QByteArrayLiteral("inline_do_block_vars_start_token");
            case lex_inline_do_block_var_access_type: return QByteArrayLiteral("inline_do_block_var_access_type_token");
            case lex_inline_do_block_var_name: return QByteArrayLiteral("inline_do_block_var_name_token");
            case lex_inline_do_block_vars_splitter: return QByteArrayLiteral("inline_do_block_vars_splitter_token");
            case lex_inline_do_block_vars_end: return QByteArrayLiteral("inline_do_block_vars_end_token");


            case lex_begin: return QByteArrayLiteral("begin_token");
            case lex_end: return QByteArrayLiteral("end_token");

            case lex_block_start: return QByteArrayLiteral("block_start_token");
            case lex_block_rescue: return QByteArrayLiteral("block_rescue_token");
            case lex_block_ensure: return QByteArrayLiteral("block_ensure_token");
            case lex_block_retry: return QByteArrayLiteral("block_retry_token");
            case lex_block_end: return QByteArrayLiteral("block_end_token");


            case lex_return: return QByteArrayLiteral("return_token");


            case lex_global_pre_hook: return QByteArrayLiteral("global_pre_hook_token");
            case lex_global_post_hook: return QByteArrayLiteral("global_post_hook_token");
            case lex_end_of_code: return QByteArrayLiteral("end_of_code_token");


            case lex_undefined: return QByteArrayLiteral("undefined_token");
            case lex_end_line: return QByteArrayLiteral("end_of_code_token");
            case lex_end_doc: return QByteArrayLiteral("end_doc_token");
            case lex_tab: return QByteArrayLiteral("tab_token");
            case lex_blank: return QByteArrayLiteral("blank_token");
            case lex_blanks: return QByteArrayLiteral("blanks_token");
            case lex_ignore: return QByteArrayLiteral("ignore_token");

            default: return QByteArrayLiteral("Unknown: ") + QByteArray::number(lexem);
        }
    }
};

#endif // LEXEMS_YAML_H