#include "grammar_ruby.h"

using namespace Ruby;

Grammar::Grammar() : IGrammar() {
    para_tokens = {
        { lex_open_curly_bracket, pt_open_curly_bracket },

        { lex_interpolation, pt_open_interpolation },
        { lex_command_interception, pt_open_interpolation },
        { lex_estring_interception, pt_open_interpolation },
        { lex_epercent_presentation_interception, pt_open_interpolation },
        { lex_heredoc_interception, pt_open_interpolation },
        { lex_regexp_interception, pt_open_interpolation },

        { lex_close_curly_bracket, pt_close_curly_bracket },
        { lex_open_square_bracket, pt_open_square_bracket },
        { lex_close_square_bracket, pt_close_square_bracket },
        { lex_wrap_open, pt_open_round_bracket },
        { lex_wrap_close, pt_close_round_bracket },
    //    { lex_operator_less, pt_open_angle_bracket },
    //    { lex_operator_great, pt_close_angle_bracket },

        { lex_do, pt_open_do_block },
        { lex_begin, pt_open_begin_block },
        { lex_method_def, pt_open_method },
        { lex_class_def, pt_open_class },
        { lex_module_def, pt_open_module },

        { lex_if, pt_open_if },
        { lex_elsif, pt_open_elsif },
        { lex_else, pt_open_else },
        { lex_unless, pt_open_unless },
        { lex_case, pt_open_case },
        { lex_when, pt_open_when },
        { lex_while, pt_open_while },
        { lex_until, pt_open_until },
        { lex_for, pt_open_for },

        { lex_block_rescue, pt_rescue },
        { lex_block_ensure, pt_ensure },

        { lex_end, pt_close_struct },

        { lex_string_start, pt_open_string },
        { lex_string_end, pt_close_string },

        { lex_estring_start, pt_open_string },
        { lex_estring_end, pt_close_string },

        { lex_regexp_start, pt_open_regexp },
        { lex_regexp_end, pt_close_regexp }
    };

    for(quint32 i = 0; i < lex_max; i++) {
        StateLexem curr = static_cast<StateLexem>(i);

        rules[i][lex_end_line] = curr;
//        rules[lex_end_line][i] = curr;

        rules[i][lex_blank] = curr;
        rules[lex_blank][i] = curr;

        rules[lex_blanks][i] = curr;
        rules[i][lex_blanks] = curr;

        rules[i][lex_tab] = curr;
        rules[lex_tab][i] = curr;

        rules[i][lex_tabs] = curr;
        rules[lex_tabs][i] = curr;


        rules[lex_operator_assigment][i] = curr;


        rules[lex_symbol_key][i] = curr;

        rules[i][lex_inline_commentary_content] = lex_inline_commentary_content;

        rules[lex_estring_interception][i] = curr;
        rules[lex_command_interception][i] = curr;

//        rules[lex_inline_block_start][i] = curr;
    }

    rules[lex_symbol_key][lex_end_line] = lex_symbol_key;

    rules[lex_symbol_key][lex_blank] = lex_symbol_key;
    rules[lex_symbol_key][lex_blanks] = lex_symbol_key;

    rules[lex_symbol_key][lex_tab] = lex_symbol_key;
    rules[lex_symbol_key][lex_tabs] = lex_symbol_key;

    rules[lex_blank][lex_tab] = lex_blanks;
    rules[lex_tab][lex_blank] = lex_blanks;
    rules[lex_blanks][lex_tab] = lex_blanks;
    rules[lex_blanks][lex_tabs] = lex_blanks;

    rules[lex_string_start][lex_string_content] = lex_string_content;
    rules[lex_string_content][lex_string_end] = lex_string_end;

    rules[lex_estring_start][lex_estring_content] = lex_estring_content;
    rules[lex_estring_content][lex_estring_end] = lex_estring_end;

    rules[lex_command_start][lex_command_content] = lex_command_content;
    rules[lex_command_content][lex_command_end] = lex_command_end;

    // PERCENTAGE PRESENTATION
//        %r(/home/#{foo})#=> "/\\/home\\/Foo/"

    rules[lex_percent_presentation_start][lex_percent_presentation_end] = lex_expression;
    rules[lex_epercent_presentation_start][lex_epercent_presentation_end] = lex_expression;


    // MODULE DEFINITION

    rules[lex_module_def][lex_word] = lex_module_def_name;
    rules[lex_module_def][lex_module_def_resolution] = lex_module_def_resolution;
    rules[lex_module_def_name][lex_resolution] = lex_module_def_resolution;
    rules[lex_module_def_resolution][lex_word] = lex_module_def_name;

    rules[lex_module_def_name][lex_end_line] = lex_module_def_block;
    rules[lex_none][lex_module_def_block_end] = lex_none;

    // CLASS DEFINITION

    rules[lex_class_def][lex_word] = lex_class_def_name;
    rules[lex_class_def][lex_operator_bit_left_shift] = lex_class_def_extension;

    rules[lex_class_def_name][lex_operator_less] = lex_class_def_inheritance;
    rules[lex_class_def_name][lex_semicolon] = lex_block_start;
    rules[lex_class_def_name][lex_end_line] = lex_block_start;

    rules[lex_class_def_extension][lex_word] = lex_class_def_extender;
    rules[lex_class_def_extender][lex_semicolon] = lex_block_start;
    rules[lex_class_def_extender][lex_end_line] = lex_block_start;

    rules[lex_class_def_inheritance][lex_word] = lex_class_def_ancestor;
    rules[lex_class_def_inheritance][lex_resolution] = lex_class_def_resolution;
    rules[lex_class_def_ancestor][lex_resolution] = lex_class_def_resolution;
    rules[lex_class_def_resolution][lex_word] = lex_class_def_ancestor;
    rules[lex_class_def_ancestor][lex_semicolon] = lex_block_start;
    rules[lex_class_def_ancestor][lex_end_line] = lex_block_start;

    rules[lex_method_def][lex_word] = lex_method_def_scope_or_name;
    rules[lex_method_def_scope_or_name][lex_dot] = lex_method_def_scoped_delimiter;
    rules[lex_method_def_scope_or_name][lex_blank] = lex_method_def_vars_start;
    rules[lex_method_def_scope_or_name][lex_blanks] = lex_method_def_vars_start;

    rules[lex_method_def_vars_start][lex_operator_multiplication] = lex_method_def_var_access_type;
    rules[lex_method_def_vars_start][lex_operator_exponentiation] = lex_method_def_var_access_type;
    rules[lex_method_def_vars_start][lex_operator_bit_and] = lex_method_def_var_access_type;
    rules[lex_method_def_vars_start][lex_word] = lex_method_def_var_name;
    rules[lex_method_def_var_access_type][lex_word] = lex_method_def_var_name;
    rules[lex_method_def_var_name][lex_operator_equality] = lex_method_def_var_assign;
    rules[lex_method_def_var_assign][lex_expression] = lex_method_def_var_assign_val;

    rules[lex_method_def_var_assign_val][lex_comma] = lex_method_def_vars_splitter;
    rules[lex_method_def_vars_splitter][lex_operator_multiplication] = lex_method_def_var_access_type;
    rules[lex_method_def_vars_splitter][lex_operator_exponentiation] = lex_method_def_var_access_type;
    rules[lex_method_def_vars_splitter][lex_operator_bit_and] = lex_method_def_var_access_type;
    rules[lex_method_def_vars_splitter][lex_word] = lex_method_def_var_name;

    rules[lex_method_def_var_assign_val][lex_end_line] = lex_method_call_block;
    rules[lex_method_def_vars_start][lex_end_line] = lex_method_call_block;



    rules[lex_method_def][lex_self] = lex_method_def_scoped_name;
    rules[lex_method_def_scoped_name][lex_dot] = lex_method_def_scoped_delimiter;
    rules[lex_method_def_scoped_delimiter][lex_word] = lex_method_def_name;
    rules[lex_method_def_name][lex_blank] = lex_method_def_vars_start;
    rules[lex_method_def_name][lex_blanks] = lex_method_def_vars_start;
    rules[lex_method_def_name][lex_wrap_open] = lex_method_def_args_start;
    rules[lex_method_def_scope_or_name][lex_wrap_open] = lex_method_def_args_start;


    rules[lex_method_def_args_start][lex_operator_multiplication] = lex_method_def_arg_access_type;
    rules[lex_method_def_args_start][lex_operator_exponentiation] = lex_method_def_arg_access_type;
    rules[lex_method_def_args_start][lex_operator_bit_and] = lex_method_def_arg_access_type;

    rules[lex_method_def_args_start][lex_word] = lex_method_def_arg_name;
    rules[lex_method_def_arg_access_type][lex_word] = lex_method_def_arg_name;
    rules[lex_method_def_arg_name][lex_operator_equality] = lex_method_def_arg_assign;
    rules[lex_method_def_arg_name][lex_comma] = lex_method_def_arg_splitter;
    rules[lex_method_def_arg_assign][lex_expression] = lex_method_def_arg_assign_val;
    rules[lex_method_def_arg_assign_val][lex_comma] = lex_method_def_arg_splitter;

    rules[lex_method_def_var_assign_val][lex_comma] = lex_method_def_arg_splitter;
    rules[lex_method_def_arg_splitter][lex_operator_multiplication] = lex_method_def_arg_access_type;
    rules[lex_method_def_arg_splitter][lex_operator_exponentiation] = lex_method_def_arg_access_type;
    rules[lex_method_def_arg_splitter][lex_operator_bit_and] = lex_method_def_arg_access_type;
    rules[lex_method_def_arg_splitter][lex_word] = lex_method_def_arg_name;




    rules[lex_method_def_var_assign_val][lex_wrap_close] = lex_method_def_args_end;
    rules[lex_method_def_args_start][lex_wrap_close] = lex_method_def_args_end;
    rules[lex_method_def_args_end][lex_end_line] = lex_method_call_block;


    rules[lex_method_def_scope_or_name][lex_end_line] = lex_method_call_block;
    rules[lex_method_def_name][lex_end_line] = lex_method_call_block;



//        rules[lex_module_def][lex_word] = lex_module_def_name;
//        rules[lex_module_def_resolution][lex_word] = lex_module_def_name;
//        rules[lex_module_def_name][lex_resolution] = lex_module_def_resolution;
//        rules[lex_module_def_name][lex_semicolon] = lex_block_start;
//        rules[lex_module_def_name][lex_end_line] = lex_block_start;


//        rules[lex_method_def][lex_self] = lex_method_def_name;
//        rules[lex_method_def][lex_word] = lex_method_def_name;
//        rules[lex_method_def_scoped][lex_word] = lex_method_def_scoped_name;

//        rules[lex_method_def_name][lex_dot] = lex_method_def_scoped;
//        rules[lex_method_def_name][lex_wrap_start] = lex_method_def_vars_start;
//        rules[lex_method_def_name][lex_operator_multiplication] = lex_method_def_var_access_type;
//        rules[lex_method_def_name][lex_word] = lex_method_def_var_name;
//        rules[lex_method_def_name][lex_semicolon] = lex_block_start;
//        rules[lex_method_def_name][lex_end_line] = lex_block_start;

//        rules[lex_method_def_scoped_name][lex_wrap_start] = lex_method_def_vars_start;
//        rules[lex_method_def_scoped_name][lex_operator_multiplication] = lex_method_def_var_access_type;
//        rules[lex_method_def_scoped_name][lex_word] = lex_method_def_var_name;
//        rules[lex_method_def_scoped_name][lex_semicolon] = lex_block_start;
//        rules[lex_method_def_scoped_name][lex_end_line] = lex_block_start;

//        rules[lex_method_def_vars_start][lex_wrap_end] = lex_method_def_vars_end;
//        rules[lex_method_def_vars_start][lex_operator_multiplication] = lex_method_def_var_access_type;
//        rules[lex_method_def_vars_start][lex_word] = lex_method_def_var_name;

//        rules[lex_method_def_var_access_type][lex_word] = lex_method_def_var_name;

//        rules[lex_method_def_var_name][lex_wrap_end] = lex_method_def_vars_end;
//        rules[lex_method_def_var_name][lex_comma] = lex_method_def_vars_splitter;

//        rules[lex_method_def_vars_splitter][lex_operator_multiplication] = lex_method_def_var_access_type;
//        rules[lex_method_def_vars_splitter][lex_word] = lex_method_def_var_name;

    rules[lex_word][lex_blank] = lex_method_call_vars_start;
    rules[lex_word][lex_blanks] = lex_method_call_vars_start;

    rules[lex_word][lex_wrap_open] = lex_method_call_args_start;
    rules[lex_wrap_open][lex_wrap_close] = lex_method_call_args_close;
    rules[lex_method_call_args_close][lex_end_line] = lex_none;
    rules[lex_method_call_args_close][lex_semicolon] = lex_none;

    rules[lex_method][lex_dot] = lex_method_access;
    rules[lex_word][lex_dot] = lex_method_access;
    rules[lex_method_access][lex_word] = lex_method;



//    lex_method_call_args_start,
//    lex_method_call_args_close,
//    lex_method_call_arg_entry,
//    lex_method_call_args_splitter,

//    lex_method_call_vars_start,
//    lex_method_call_var_entry,
//    lex_method_call_vars_splitter,
//    lex_method_call_vars_end,


    // HEREDOC

//    rules[lex_method_call_vars_start][lex_eheredoc_intended_mark] = lex_eheredoc_intended_mark;
}

void Grammar::initFlags(StackLexemFlag & flags, const StateLexem & lex, const StateLexem & last_non_blank_lex) {
    switch(lex) {
        case lex_end: { flags = slf_unblocker_word; break;}

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
                    flags = slf_blocker_word;
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
            { flags = slf_blocker_word; break;}

        case lex_when:
        case lex_elsif:
        case lex_else:
        case lex_block_rescue:
        case lex_block_ensure:
        case lex_block_retry:
            { flags = slf_replace_word; break;}

        default:;
    }
}

bool Grammar::stackDropable(const StateLexem & state, const StateLexem & input) {
    switch(state) {
        case lex_if:
            return input == lex_end || input == lex_elsif || input == lex_else;

        case lex_unless:
            return input == lex_end || input == lex_else;

        case lex_else:
            return input == lex_end || input == lex_block_ensure; // can stacked with ensure if 'else' used in scope of error types catching

        case lex_elsif:
            return input == lex_end || input == lex_elsif || input == lex_else;           

        case lex_open_curly_bracket:
        case lex_estring_interception:
        case lex_regexp_interception:
        case lex_epercent_presentation_interception:
        case lex_command_interception:
        case lex_heredoc_interception: return input == lex_close_curly_bracket;

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

        case lex_case:
            return input == lex_end || input == lex_when;

        case lex_when:
            return input == lex_end || input == lex_when || input == lex_else;

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

StateLexem Grammar::stateForHeredoc(const StateLexem & lex, const bool & content) {
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

//StateLexem Grammar::toHeredocContinious(const StateLexem & lexem) {
//    switch(lexem) {
//        case lex_heredoc_mark: return lex_heredoc_continue;
//        case lex_heredoc_intended_mark: return lex_heredoc_intended_continue;
//        case lex_eheredoc_mark: return lex_eheredoc_continue;
//        case lex_eheredoc_intended_mark: return lex_eheredoc_intended_continue;
//        case lex_cheredoc_mark: return lex_cheredoc_continue;
//        case lex_cheredoc_intended_mark: return lex_cheredoc_intended_continue;
//        default: return lex_none;
//    }
//}

//StateLexem Grammar::fromContinious(const StateLexem & lexem) {
//    switch(lexem) {
//        case lex_string_continue: return lex_string_start;

//        case lex_estring_start:
//        case lex_estring_continue: return lex_estring_start;

//        case lex_commentary_continue: return lex_commentary_start;

//        case lex_command_start:
//        case lex_command_continue: return lex_command_start;

//        case lex_heredoc_continue: return lex_heredoc_start;
//        case lex_heredoc_intended_continue: return lex_heredoc_intended_start;

//        case lex_eheredoc_start:
//        case lex_eheredoc_continue: return lex_eheredoc_start;

//        case lex_eheredoc_intended_start:
//        case lex_eheredoc_intended_continue: return lex_eheredoc_intended_start;

//        case lex_cheredoc_start:
//        case lex_cheredoc_continue: return lex_cheredoc_start;

//        case lex_cheredoc_intended_start:
//        case lex_cheredoc_intended_continue: return lex_cheredoc_intended_start;

//        case lex_regexp_start:
//        case lex_regexp_continue: return lex_regexp_start;

//        case lex_percent_presentation_continue: return lex_percent_presentation_start;

//        case lex_epercent_presentation_start:
//        case lex_epercent_presentation_continue: return lex_epercent_presentation_start;

//        default: return lex_none;
//    }
//}

Identifier Grammar::toHighlightable(const StateLexem & lexem) {
    switch(lexem) {
        case lex_super:
        case lex_self:
        case lex_method_def:
        case lex_class_def:
        case lex_module_def:
        case lex_require:
        case lex_include:
        case lex_extend:
        case lex_undef:
        case lex_visibility_scope:
        case lex_alias:
        case lex_then:
        case lex_unless:
        case lex_if:
        case lex_elsif:
        case lex_else:
        case lex_switch:
        case lex_case:
        case lex_when:
        case lex_while:
        case lex_until:
        case lex_for:
        case lex_in:
        case lex_loop_break:
        case lex_loop_redo:
        case lex_loop_next:
        case lex_do:
        case lex_begin:
        case lex_end:
        case lex_return:
        case lex_global_pre_hook:
        case lex_global_post_hook:
        case lex_end_of_code:
        case lex_block_rescue:
        case lex_block_ensure:
        case lex_block_retry:
            return hid_keyword;

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
//        case lex_method:
        case lex_method_def_scoped_name:
        case lex_method_def_var_name:
        case lex_method_call_block_var_name:
        case lex_class_def_ancestor:
        case lex_class_def_resolution:
        case lex_class_def_extender:
        case lex_lambda_def_var_name:
        case lex_proc_def_var_name:
        case lex_include_obj:
        case lex_extend_obj:
        case lex_undef_arg:
        case lex_visibility_scope_arg:
        case lex_alias_base_name:
        case lex_alias_alt_name:
            return hid_var;


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
        case lex_class_def_name:
        case lex_module_def_name:
            return hid_name_def;

        case lex_method:
            return hid_name_call;

        case lex_inline_commentary_content:
        case lex_commentary_end:
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

        case lex_epercent_presentation_start:
        case lex_percent_presentation_start:
        case lex_epercent_presentation_end:
        case lex_percent_presentation_end:
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
            return hid_regexp_border;

        //hid_scope_visibility

        case lex_word: return hid_unknown_name;

        case lex_error: return hid_error;

        default: return hid_none;
    }
}
