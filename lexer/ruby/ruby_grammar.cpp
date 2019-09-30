#include "ruby_grammar.h"

using namespace Ruby;

Grammar::Grammar() : IGrammar() {
    initParas();
}

void Grammar::initParas() {
    para_tokens[lex_ternary_main_start] = pt_ternary;
    para_tokens[lex_ternary_alt_start] = pt_close_ternary;

    para_tokens[lex_open_curly_bracket] = pt_foldable_curly_bracket;
    para_tokens[lex_close_curly_bracket] = pt_close_foldable_curly_bracket;
    para_tokens[lex_interpolation] = pt_interpolation;
    para_tokens[lex_command_interception] = pt_interpolation;
    para_tokens[lex_estring_interception] = pt_interpolation;
    para_tokens[lex_epercent_presentation_interception] = pt_interpolation;
    para_tokens[lex_heredoc_interception] = pt_interpolation;
    para_tokens[lex_regexp_interception] = pt_interpolation;
    para_tokens[lex_interception_close] = pt_close_interpolation;
    para_tokens[lex_open_square_bracket] = pt_square_bracket;
    para_tokens[lex_close_square_bracket] = pt_close_square_bracket;
    para_tokens[lex_wrap_open] = pt_round_bracket;
    para_tokens[lex_wrap_close] = pt_close_round_bracket;


    para_tokens[lex_percent_presentation_start] = pt_representation;
    para_tokens[lex_percent_presentation_end] = pt_close_representation;
    para_tokens[lex_epercent_presentation_start] = pt_representation;
    para_tokens[lex_epercent_presentation_end] = pt_close_representation;


    para_tokens[lex_do] = pt_open_begin_block; //pt_open_do_block;
    para_tokens[lex_begin] = pt_open_begin_block;
    para_tokens[lex_method_def] = pt_open_method;
    para_tokens[lex_class_def] = pt_open_class; //pt_open_class;
    para_tokens[lex_module_def] = pt_open_module; //pt_open_module;

    para_tokens[lex_if] = pt_open_if;
    para_tokens[lex_then] = pt_open_then;
    para_tokens[lex_elsif] = pt_open_elsif;
    para_tokens[lex_else] = pt_open_else;
    para_tokens[lex_unless] = pt_open_unless;
    para_tokens[lex_case] = pt_open_case;
    para_tokens[lex_when] = pt_open_when;
    para_tokens[lex_while] = pt_open_while;
    para_tokens[lex_until] = pt_open_until;
    para_tokens[lex_for] = pt_open_for;
    para_tokens[lex_block_rescue] = pt_rescue;
    para_tokens[lex_block_ensure] = pt_ensure;
    para_tokens[lex_end] = pt_close_struct;

    para_tokens[lex_string_start] = pt_string;
    para_tokens[lex_string_end] = pt_close_string;
    para_tokens[lex_estring_start] = pt_estring;
    para_tokens[lex_estring_end] = pt_close_estring;
    para_tokens[lex_regexp_start] = pt_regexp;
    para_tokens[lex_regexp_end] = pt_close_regexp;

    para_tokens[lex_commentary_start] = pt_foldable_comment;
    para_tokens[lex_commentary_end] = pt_close_foldable_comment;
}

void Grammar::initFlags(StackLexemFlag & flags, const LEXEM_TYPE & lex, const LEXEM_TYPE & last_non_blank_lex) {
    switch(lex) {
        case lex_end:
        case lex_commentary_end:
            { flags = slf_unstack_word; break;}

        case lex_if:
        case lex_unless: {
            switch(last_non_blank_lex) {
                case lex_none:

                case lex_question_mark:

                case lex_operator_assigment:
                case lex_operator_comparison:
                case lex_operator_equality:
                case lex_operator_not_equal:

                case lex_operator_less:
                case lex_operator_less_eql:
                case lex_operator_great:
                case lex_operator_great_eql:

                case lex_operator_sort:

                case lex_operator_add:
                case lex_operator_add_assigment:
                case lex_operator_minus:
                case lex_operator_minus_assigment:
                case lex_operator_multiplication:
                case lex_operator_multiplication_assigment:
                case lex_operator_division:
                case lex_operator_division_assigment:
                case lex_operator_exponentiation:
                case lex_operator_exponentiation_assigment:
                case lex_operator_modulus:
                case lex_operator_modulus_assigment:

                case lex_operator_bit_and:
                case lex_operator_bit_or:
                case lex_operator_bit_exclusive_or:
                case lex_operator_bit_not:
                case lex_operator_bit_left_shift:
                case lex_operator_bit_right_shift:

                case lex_operator_and:
                case lex_operator_or:
                case lex_operator_or_assigment:
                case lex_operator_not: {
                    flags = slf_stack_word;
                break;}

                default: ;
            }
        break;}

        case lex_do:
        case lex_begin:
        case lex_method_def:
        case lex_case:
        case lex_until:
        case lex_for:
        case lex_while:
        case lex_module_def:
        case lex_class_def:
        case lex_commentary_start:
            { flags = slf_stack_word; break;}

        case lex_when:
        case lex_elsif:
        case lex_else:
        case lex_block_rescue:
        case lex_block_ensure:
        case lex_then:
            { flags = slf_replace_word; break;}

        default:;
    }
}

bool Grammar::stackDropable(const LEXEM_TYPE & state, const LEXEM_TYPE & input) {
    switch(state) {
        case lex_if:
            return input == lex_end || input == lex_elsif || input == lex_else || input == lex_then;

        case lex_unless:
            return input == lex_end || input == lex_else;

        case lex_else:
            return input == lex_end || input == lex_block_ensure; // can stacked with ensure if 'else' used in scope of error types catching

        case lex_elsif:
            return input == lex_end || input == lex_elsif || input == lex_else;           

        case lex_open_curly_bracket: return input == lex_close_curly_bracket;

        case lex_estring_interception:
        case lex_regexp_interception:
        case lex_epercent_presentation_interception:
        case lex_command_interception:
        case lex_heredoc_interception: return input == lex_interception_close;

//        ruby 2.5: supports rescue/else/ensure in do/end blocks
        case lex_do: return input == lex_end;

        case lex_epercent_presentation_start: return input == lex_epercent_presentation_end;
        case lex_percent_presentation_start: return input == lex_percent_presentation_end;

        case lex_wrap_open: return input == lex_wrap_close;
        case lex_open_square_bracket: return input == lex_close_square_bracket;

        case lex_string_start: return input == lex_string_end;
        case lex_estring_start: return input == lex_estring_end;

        case lex_regexp_start: return input == lex_regexp_end;
        case lex_command_start: return input == lex_command_end;

        case lex_module_def:
        case lex_class_def:
            return input == lex_end;

        case lex_begin:
        case lex_method_def:
            return input == lex_end || input == lex_block_rescue || input == lex_block_ensure;

        case lex_for:
        case lex_until:
        case lex_while:
            return input == lex_end;


        case lex_block_rescue:
            return input == lex_else || input == lex_block_ensure || input == lex_block_rescue || input == lex_end;
        case lex_block_ensure:
            return input == lex_end;

        case lex_heredoc_start:
        case lex_heredoc_intended_start:
        case lex_cheredoc_intended_start:
        case lex_cheredoc_start:
        case lex_eheredoc_intended_start:
        case lex_eheredoc_start: return input == lex_heredoc_close_mark;

        case lex_ternary_main_start: return input == lex_ternary_alt_start;

        case lex_case:
            return input == lex_end || input == lex_when;

        case lex_when:
            return input == lex_end || input == lex_when || input == lex_else;

        case lex_commentary_start:
            return input == lex_commentary_end;

        default: return false;
    }
}

//StateLexem Grammar::toInterceptor(const StateLexem & lex) {
//    switch(lex) {
//        case lex_estring_continue: return lex_estring_interception;
//        case lex_regexp_continue: return lex_regexp_interception;

//        case lex_epercent_presentation_start:
//        case lex_epercent_presentation_continue: return lex_epercent_presentation_interception;

//        case lex_eheredoc_intended_continue: return lex_eheredoc_intended_interception;
//        case lex_cheredoc_intended_continue: return lex_cheredoc_intended_interception;
//        case lex_eheredoc_continue: return lex_eheredoc_interception;
//        case lex_cheredoc_continue: return lex_cheredoc_interception;
//        case lex_command_continue: return lex_command_interception;

//        default: return lex_none;
//    };
//}

LEXEM_TYPE Grammar::stateForHeredoc(const LEXEM_TYPE & lex, const bool & content) {
    switch(lex) {
        case lex_eheredoc_intended_start:
            return content ? lex_eheredoc_intended_content : lex_eheredoc_intended_end;
        case lex_cheredoc_intended_start:
            return content ? lex_cheredoc_intended_content : lex_cheredoc_intended_end;
        case lex_eheredoc_start:
            return content ? lex_eheredoc_content : lex_eheredoc_end;
        case lex_cheredoc_start:
            return content ? lex_cheredoc_content : lex_cheredoc_end;
        case lex_heredoc_start:
            return content ? lex_heredoc_content : lex_heredoc_end;
        case lex_heredoc_intended_start:
            return content ? lex_heredoc_intended_content : lex_heredoc_intended_end;

        default: return lex_none;
    };
}

char Grammar::percentagePresentationBlocker(const char & ch) {
    switch(ch) {
        case '(': return ')';
        case '[': return ']';
        case '{': return '}';

        default: return ch;
    };
}

//bool Grammar::isStackDroppable(const StateLexem & lexem) {
//    switch(lexem) {
//        case lex_string_continue:
//        case lex_estring_continue:
//        case lex_commentary_continue:
//        case lex_command_continue:
//        case lex_regexp_continue:
//            return true;

////            case lex_heredoc_continue:
////            case lex_heredoc_intended_continue:
////            case lex_eheredoc_continue:
////            case lex_eheredoc_intended_continue:
////            case lex_cheredoc_continue:
////            case lex_cheredoc_intended_continue:

//        default: return false;
//    }
//}

//bool Grammar::isInterpolable(const StateLexem & lexem) {
//    switch(lexem) {
//        case lex_estring_continue:
//        case lex_command_continue:
//        case lex_eheredoc_continue:
//        case lex_eheredoc_intended_continue:
//        case lex_cheredoc_continue:
//        case lex_cheredoc_intended_continue:
//        case lex_regexp_continue:
//        case lex_epercent_presentation_continue:
//            return true;
//        default: return false;
//    }
//}

Identifier Grammar::toHighlightable(const LEXEM_TYPE & lexem) {
    switch(lexem) {
        case lex_method_def:
        case lex_class_def:
        case lex_module_def:
        case lex_require:
        case lex_include:
        case lex_extend:
        case lex_undef:
        case lex_alias:
        case lex_unless:
        case lex_if:
        case lex_then:
        case lex_elsif:
        case lex_else:
        case lex_case:
        case lex_when:
        case lex_while:
        case lex_until:
        case lex_for:
        case lex_in:
        case lex_do:
        case lex_begin:
        case lex_end:
        case lex_global_pre_hook:
        case lex_global_post_hook:
        case lex_end_of_code:
        case lex_block_rescue:
        case lex_block_ensure:
            return hid_keyword;


        case lex_raise:
        case lex_super:
        case lex_self:
        case lex_yield:
        case lex_return:
        case lex_loop:
        case lex_loop_break:
        case lex_loop_redo:
        case lex_loop_next:
        case lex_block_retry:
            return hid_spec_keyword;


        case lex_bin:
        case lex_oct:
        case lex_dec:
        case lex_hex:
        case lex_float:
        case lex_double:
            return hid_numeric;


        case lex_symbol_key:
        case lex_symbol: return hid_symbol;


        case lex_const: return hid_const;


        case lex_var_scoped:
        case lex_var_local:
        case lex_var_instance:
        case lex_var_object:
        case lex_var_global:
        case lex_method_def_scoped_name:
        case lex_method_call_block_var_name:
        case lex_lambda_def_var_name:
        case lex_proc_def_var_name:
        case lex_undef_arg:
        case lex_visibility_scope_arg:
        case lex_alias_base_name:
        case lex_alias_alt_name:
            return hid_var;


        case lex_method_def_arg_name:
        case lex_method_def_var_name:
            return hid_name_arg;

        case lex_heredoc_close_mark:
        case lex_heredoc_mark:
        case lex_heredoc_intended_mark:
        case lex_eheredoc_mark:
        case lex_eheredoc_intended_mark:
        case lex_cheredoc_mark:
        case lex_cheredoc_intended_mark:
            return hid_label;


        case lex_method_def_name:
        case lex_method_def_scope_or_name:
        case lex_class_def_name_part:
        case lex_class_def_ancestor:
        case lex_module_def_name_part:
        case lex_module_def_ancestor:
        case lex_include_obj_part:
            return hid_name_def;

        case lex_method:
            return hid_name_call;

        case lex_inline_commentary_content:
        case lex_commentary_start:
        case lex_commentary_end:
        case lex_commentary_content:
            return hid_commentary;


        case lex_string_start:
        case lex_string_end:
        case lex_estring_start:
        case lex_estring_end:
        case lex_command_start:
        case lex_command_end:
            return hid_string_border;


        case lex_string_content:
        case lex_estring_content:
        case lex_command_content:
        case lex_require_path:

        case lex_epercent_presentation_content:
        case lex_percent_presentation_content:

        case lex_heredoc_content:
        case lex_heredoc_intended_content:
        case lex_eheredoc_intended_content:
        case lex_cheredoc_intended_content:
        case lex_eheredoc_content:
        case lex_cheredoc_content:
            return hid_string;

        case lex_regexp_content:
            return hid_regexp;

        case lex_regexp_start:
        case lex_regexp_end:
        case lex_regexp_flags:
        case lex_epercent_presentation_start:
        case lex_percent_presentation_start:
        case lex_epercent_presentation_end:
        case lex_percent_presentation_end:
            return hid_regexp_border;

        case lex_ternary_main_start:
        case lex_ternary_alt_start:
            return hid_ternary;

        case lex_char_sequence:
            return hid_sequence;

        case lex_visibility_scope: return hid_scope_visibility;

        case lex_word: return hid_unknown_name;

        case lex_error: return hid_error;

        default: return hid_none;
    }
}

LEXEM_TYPE Grammar::translate(const LEXEM_TYPE & state, const LEXEM_TYPE & handle) {
    if (state == lex_none)
        return handle;

    if (handle == lex_none)
        return state;

    LEXEM_TYPE input = handle;

    if (handle == lex_blanks || handle == lex_tabs)
        input = lex_spacing;

    switch(state) {
        case lex_blanks: {
            switch(input) {
                case lex_spacing: return lex_blanks;
                default: return input;
            }
        }

        case lex_tabs: {
            switch(input) {
                case lex_spacing: return lex_blanks;
                default: return input;
            }
        }





        case lex_method_def: {
            switch(input) {
                case lex_spacing: return lex_method_def_pre_name;
                default: return lex_error;
            }
        }

        case lex_method_def_pre_name: {
            switch(input) {
                case lex_spacing: return state;
                case lex_self: return lex_method_def_scoped_name;
                case lex_word: return lex_method_def_scope_or_name;
                default: return lex_error;
            }
        }

        case lex_method_def_scoped_name: {
            switch(input) {
                case lex_spacing: return state;
                case lex_dot: return lex_method_def_scoped_delimiter;
                default: return lex_error;
            }
        }

        case lex_method_def_scope_or_name: {
            switch(input) {
                case lex_spacing: return lex_method_def_post_scope_or_name;
                case lex_wrap_open: return lex_method_def_args_start;
                case lex_dot: return lex_method_def_scoped_delimiter;
                case lex_end_line: return lex_method_call_block;
                default: return lex_error;
            }
        }

        case lex_method_def_post_scope_or_name: {
            switch(input) {
                case lex_spacing: return state;
                case lex_wrap_open: return lex_method_def_args_start;
                case lex_dot: return lex_method_def_scoped_delimiter;
                case lex_end_line: return lex_method_call_block;
                default: return lex_error;
            }
        }

        case lex_method_def_scoped_delimiter: {
            switch(input) {
                case lex_spacing: return state;
                case lex_word: return lex_method_def_name;
                default: return lex_error;
            }
        }

        case lex_method_def_name: {
            switch(input) {
                case lex_spacing: return lex_method_def_post_name;
                case lex_wrap_open: return lex_method_def_args_start;
                case lex_end_line: return lex_method_def_block_start;
                default: return lex_error;
            }
        }

        case lex_method_def_post_name: {
            switch(input) {
                case lex_spacing: return state;
                case lex_word: return lex_method_def_vars_start;
                case lex_wrap_open: return lex_method_def_args_start;
                case lex_end_line: return lex_method_def_block_start;
                default: return lex_error;
            }
        }


        case lex_method_def_args_start: {
            switch(input) {
                case lex_spacing: return state;
                case lex_operator_multiplication: return lex_method_def_arg_access_type;
                case lex_operator_exponentiation: return lex_method_def_arg_access_type;
                case lex_operator_bit_and: return lex_method_def_arg_access_type;
                case lex_word: return lex_method_def_arg_name;
                case lex_wrap_close: return lex_method_def_args_end;
                default: return lex_error;
            }
        }

//    case lex_method_def_arg_assign_val: {
//        switch(input) {
//            case lex_comma: return lex_method_def_arg_splitter;
//            default: return lex_error;
//        }
//    }

        case lex_method_def_arg_access_type: {
            switch(input) {
                case lex_spacing: return state;
                case lex_word: return lex_method_def_arg_name;
                default: return lex_error;
            }
        }

        case lex_method_def_arg_name: {
            switch(input) {
                case lex_spacing: return state;
                case lex_operator_equality: return lex_method_def_arg_assign;
                case lex_comma: return lex_method_def_arg_splitter;
                case lex_wrap_close: return lex_method_def_args_end;
                default: return lex_error;
            }
        }

        case lex_method_def_arg_splitter: {
            switch(input) {
                case lex_spacing: return state;
                case lex_operator_multiplication: return lex_method_def_arg_access_type;
                case lex_operator_exponentiation: return lex_method_def_arg_access_type;
                case lex_operator_bit_and: return lex_method_def_arg_access_type;
                case lex_word: return lex_method_def_arg_name;
                default: return lex_error;
            }
        }


//        lex_symbol
//        lex_wrap_open
//        lex_open_curly_bracket
//        lex_open_square_bracket
//        lex_word
//        lex_const
//        lex_var_local
//        lex_var_instance
//        lex_var_object
//        lex_var_global
//        lex_var_or_method
//        lex_unknown_var_or_method
//        lex_bin
//        lex_oct
//        lex_dec
//        lex_hex
//        lex_float
//        lex_double
//        lex_char_sequence
//        lex_lambda_def
//        lex_proc_def
//        lex_method
//        lex_command_start
//        lex_string_start
//        lex_estring_start
//        lex_percent_presentation_start
//        lex_epercent_presentation_start
//        lex_heredoc_mark
//        lex_heredoc_intended_mark
//        lex_eheredoc_mark
//        lex_eheredoc_intended_mark
//        lex_cheredoc_mark
//        lex_cheredoc_intended_mark
//        lex_regexp_start
//        lex_if
//        lex_unless
//        lex_case
//        lex_begin
//        lex_resolution ???



//        case lex_method_def_arg_assign: {
//            switch(input) {
//                case lex_spacing: return state;
//                case lex_number: return lex_method_def_arg_assign_val;
//                default: return lex_error;
//            }
//        }


        case lex_method_def_args_end: {
            switch(input) {
                case lex_spacing: return state;
                case lex_end_line: return lex_method_def_block_start;
                default: return lex_error;
            }
        }















        case lex_extend:
        case lex_prepend:
        case lex_include: {
            switch(input) {
                case lex_spacing: return lex_include_pre_obj;
                default: return lex_error;
            }
        }

        case lex_include_pre_obj: {
            switch(input) {
                case lex_resolution: return lex_include_resolution;
                case lex_word:
                case lex_const: return lex_include_obj_part;
                default: return lex_error;
            }
        }

        case lex_include_obj_part: {
            switch(input) {
                case lex_spacing: return lex_include_obj_part;
                case lex_resolution: return lex_include_resolution;
                case lex_comma: return lex_include_splitter;
                case lex_end_line: return lex_include_end;
                default: return lex_error;
            }
        }

        case lex_include_resolution: {
            switch(input) {
                case lex_word:
                case lex_const: return lex_include_obj_part;
                default: return lex_error;
            }
        }

        case lex_include_splitter: {
            switch(input) {
                case lex_spacing: return lex_include_splitter;
                case lex_resolution: return lex_include_resolution;
                case lex_word:
                case lex_const: return lex_include_obj_part;
                default: return lex_error;
            }
        }



        case lex_class_def: {
            switch(input) {
                case lex_spacing: return lex_class_def_prename;
                default: return lex_error;
            }
        }

        case lex_class_def_prename: {
            switch(input) {
                case lex_word:
                case lex_const: return lex_class_def_name_part;
                default: return lex_error;
            }
        }

        case lex_class_def_name_part: {
            switch(input) {
                case lex_resolution: return lex_class_def_resolution;
                case lex_operator_less: return lex_class_def_inheritance;
                case lex_spacing:
                case lex_end_line:
                case lex_semicolon: return lex_class_def_name_end;
                default: return lex_error;
            }
        }

        case lex_class_def_name_end: {
            switch(input) {
                case lex_spacing:
                case lex_end_line:
                case lex_semicolon: return lex_class_def_name_end;
                case lex_resolution: return lex_class_def_resolution;
                case lex_operator_less: return lex_class_def_inheritance;
                default: return lex_error;
            }
        }

        case lex_class_def_extension: {
            switch(input) {
                case lex_word:
                case lex_const: return lex_class_def_extender;
                default: return lex_error;
            }
        }

        case lex_class_def_resolution: {
            switch(input) {
                case lex_spacing: return state;
                case lex_word:
                case lex_const: return lex_class_def_ancestor;
                default: return lex_error;
            }
        }

        case lex_class_def_extender: {
            switch(input) {
                case lex_end_line: return lex_class_def_name_end;
                default: return lex_error;
            }
        }

        case lex_class_def_inheritance: {
            switch(input) {
                case lex_spacing: return state;
                case lex_word:
                case lex_const: return lex_class_def_ancestor;
                case lex_resolution: return lex_class_def_resolution;
                default: return lex_error;
            }
        }

        case lex_class_def_ancestor: {
            switch(input) {
                case lex_resolution: return lex_class_def_resolution;
                case lex_semicolon: return lex_block_start;
                case lex_end_line: return lex_block_start;
                default: return lex_error;
            }
        }



        case lex_module_def: {
            switch(input) {
                case lex_spacing: return lex_module_def_prename;
                case lex_resolution: return lex_module_def_resolution;
                default: return lex_error;
            }
        }

        case lex_module_def_resolution: {
            switch(input) {
                case lex_spacing: return state;
                case lex_word:
                case lex_const: return lex_module_def_ancestor;
                default: return lex_error;
            }
        }

        case lex_module_def_name_part: {
            switch(input) {
                case lex_spacing:
                case lex_end_line:
                case lex_semicolon: return lex_module_def_name_end;
                case lex_resolution: return lex_module_def_resolution;
                default: return lex_error;
            }
        }

        case lex_module_def_prename: {
            switch(input) {
                case lex_resolution: return lex_module_def_resolution;
                case lex_word:
                case lex_const: return lex_module_def_name_part;
                default: return lex_error;
            }
        }

        case lex_module_def_ancestor: {
            switch(input) {
                case lex_spacing: return state;
                case lex_resolution: return lex_module_def_resolution;
                case lex_end_line: return lex_block_start;
                default: return lex_error;
            }
        }

        case lex_module_def_name_end: {
            switch(input) {
                case lex_spacing:
                case lex_end_line:
                case lex_semicolon: return state;
                case lex_resolution: return lex_module_def_resolution;
                default: return lex_error;
            }
        }












        case lex_symbol_key: {
            switch(input) {
                case lex_spacing:
                case lex_end_line: return state;
                default: return input;
            }
        }

        case lex_operator_assigment: {
            switch(input) {
                case lex_spacing:
                case lex_end_line: return state;
                default: return input;
            }
        }



        case lex_string_start: {
            switch(input) {
                case lex_string_content: return lex_string_content;
                case lex_string_end: return lex_string_end;
                default: return lex_error;
            }
        }

        case lex_string_content: {
            switch(input) {
                case lex_string_end: return lex_string_end;
                default: return lex_error;
            }
        }

        case lex_estring_start: {
            switch(input) {
                case lex_estring_content: return lex_estring_content;
                case lex_estring_interception: return lex_estring_interception;
                case lex_estring_end: return lex_estring_end;
                default: return lex_error;
            }
        }

        case lex_estring_content: {
            switch(input) {
                case lex_estring_end: return lex_estring_end;
                case lex_estring_interception: return lex_estring_interception;
                default: return lex_error;
            }
        }

        case lex_command_start: {
            switch(input) {
                case lex_command_content: return lex_command_content;
                case lex_command_interception: return lex_command_interception;
                case lex_command_end: return lex_command_end;
                default: return lex_error;
            }
        }

        case lex_command_content: {
            switch(input) {
                case lex_command_end: return lex_command_end;
                case lex_command_interception: return lex_command_interception;
                default: return lex_error;
            }
        }

        case lex_percent_presentation_start: {
            switch(input) {
                case lex_percent_presentation_content: return lex_percent_presentation_content;
                case lex_percent_presentation_end: return lex_percent_presentation_end;
                default: return lex_error;
            }
        }

        case lex_percent_presentation_content: {
            switch(input) {
                case lex_percent_presentation_end: return lex_percent_presentation_end;
                default: return lex_error;
            }
        }

        case lex_epercent_presentation_start: {
            switch(input) {
                case lex_epercent_presentation_content: return lex_epercent_presentation_content;
                case lex_epercent_presentation_interception: return lex_epercent_presentation_interception;
                case lex_epercent_presentation_end: return lex_epercent_presentation_end;
                default: return lex_error;
            }
        }

        case lex_epercent_presentation_content: {
            switch(input) {
                case lex_epercent_presentation_end: return lex_epercent_presentation_end;
                case lex_epercent_presentation_interception: return lex_epercent_presentation_interception;
                default: return lex_error;
            }
        }




        case lex_word: {
            switch(input) {
                case lex_spacing: return lex_method_call_vars_start;
                case lex_wrap_open: return lex_method_call_args_start;
                case lex_dot: return lex_method_access;
                default: return lex_error;
            }
        }

        case lex_wrap_open: {
            switch(input) {
                case lex_wrap_close: return lex_method_call_args_close;
                default: return lex_error;
            }
        }

        case lex_method: {
            switch(input) {
                case lex_dot: return lex_method_access;
                default: return lex_error;
            }
        }

        case lex_method_access: {
            switch(input) {
                case lex_word: return lex_method;
                default: return lex_error;
            }
        }

        case lex_none: {
            switch(input) {
//                case lex_module_def_block_end: return lex_none;
                default: return lex_error;
            }
        }

        default: {
            switch(input) {
                case lex_end_line:
                case lex_spacing: return state;
                default: return lex_error;
            }
        }
    };
}

