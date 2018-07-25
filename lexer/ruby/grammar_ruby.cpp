#include "grammar_ruby.h"

using namespace Ruby;

Grammar::Grammar() : IGrammar() {
    for(quint32 i = 0; i < lex_max; i++) {
        StateLexem curr = (StateLexem)i;

        rules[i][lex_none] = curr;
        rules[lex_none][i] = curr;

        rules[i][lex_end_line] = curr;
        rules[lex_end_line][i] = curr;

        rules[i][lex_blank] = curr;
        rules[lex_blank][i] = curr;

        rules[lex_blanks][i] = curr;
        rules[i][lex_blanks] = curr;

        rules[i][lex_tab] = curr;
        rules[lex_tab][i] = curr;

        rules[i][lex_inline_commentary] = lex_inline_commentary;
        rules[lex_inline_block_start][i] = curr;
        rules[i][lex_close_curly_bracket] = lex_expression;
    }

    rules[lex_blank][lex_blank] = lex_blanks;
    rules[lex_blank][lex_tab] = lex_blanks;
    rules[lex_tab][lex_blank] = lex_blanks;
    rules[lex_tab][lex_tab] = lex_blanks;
    rules[lex_blanks][lex_blank] = lex_blanks;
    rules[lex_blanks][lex_tab] = lex_blanks;


    // PERCENTAGE PRESENTATION
//        %r(/home/#{foo})#=> "/\\/home\\/Foo/"


    rules[lex_percent_presentation_start][lex_percent_presentation_end] = lex_expression;
    rules[lex_epercent_presentation_start][lex_epercent_presentation_end] = lex_expression;

    rules[lex_epercent_presentation_start][lex_epercent_presentation_interception] = lex_epercent_presentation_intercepted;

    rules[lex_epercent_presentation_intercepted][lex_interpolation] = lex_inline_block_start;

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
}

//    bool Grammar::isPushable(const Lexem & lexem) {
//        switch(lexem) {
//            case lex_inline_block_start:
//                return true;

//            default: return false;
//        }
//    }

//    bool Grammar::isPopable(const Lexem & lexem) {
//        switch(lexem) {
//            case:;
//        }
//    }

StateLexem Grammar::toInterceptor(const StateLexem & lex) {
    switch(lex) {
        case lex_estring_continue: return lex_estring_interception;
        case lex_regexp_continue: return lex_regexp_interception;

        case lex_epercent_presentation_start:
        case lex_epercent_presentation_continue: return lex_epercent_presentation_interception;

        case lex_eheredoc_intended_continue: return lex_eheredoc_intended_interception;
        case lex_cheredoc_intended_continue: return lex_cheredoc_intended_interception;
        case lex_eheredoc_continue: return lex_eheredoc_interception;
        case lex_cheredoc_continue: return lex_cheredoc_interception;
        case lex_command_continue: return lex_command_interception;

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

bool Grammar::isStackDroppable(const StateLexem & lexem) {
    switch(lexem) {
        case lex_string_continue:
        case lex_estring_continue:
        case lex_commentary_continue:
        case lex_command_continue:
        case lex_regexp_continue:
            return true;

//            case lex_heredoc_continue:
//            case lex_heredoc_intended_continue:
//            case lex_eheredoc_continue:
//            case lex_eheredoc_intended_continue:
//            case lex_cheredoc_continue:
//            case lex_cheredoc_intended_continue:

        default: return false;
    }
}

bool Grammar::isInterpolable(const StateLexem & lexem) {
    switch(lexem) {
        case lex_estring_continue:
        case lex_command_continue:
        case lex_eheredoc_continue:
        case lex_eheredoc_intended_continue:
        case lex_cheredoc_continue:
        case lex_cheredoc_intended_continue:
        case lex_regexp_continue:
        case lex_epercent_presentation_continue:
            return true;
        default: return false;
    }
}

StateLexem Grammar::toHeredocContinious(const StateLexem & lexem) {
    switch(lexem) {
        case lex_heredoc_mark: return lex_heredoc_continue;
        case lex_heredoc_intended_mark: return lex_heredoc_intended_continue;
        case lex_eheredoc_mark: return lex_eheredoc_continue;
        case lex_eheredoc_intended_mark: return lex_eheredoc_intended_continue;
        case lex_cheredoc_mark: return lex_cheredoc_continue;
        case lex_cheredoc_intended_mark: return lex_cheredoc_intended_continue;
        default: return lex_none;
    }
}

bool Grammar::isContinious(const StateLexem & lexem) {
    switch(lexem) {
        case lex_string_continue:
        case lex_estring_continue:
        case lex_commentary_continue:
        case lex_command_continue:
        case lex_heredoc_continue:
        case lex_heredoc_intended_continue:
        case lex_eheredoc_continue:
        case lex_eheredoc_intended_continue:
        case lex_cheredoc_continue:
        case lex_cheredoc_intended_continue:
        case lex_regexp_continue:
        case lex_epercent_presentation_continue:
        case lex_percent_presentation_continue:
            return true;
        default: return false;
    }
}

StateLexem Grammar::fromContinious(const StateLexem & lexem) {
    switch(lexem) {
        case lex_string_continue: return lex_string_start;
        case lex_estring_continue: return lex_estring_start;
        case lex_commentary_continue: return lex_commentary_start;
        case lex_command_continue: return lex_command_start;
        case lex_heredoc_continue: return lex_heredoc_start;
        case lex_heredoc_intended_continue: return lex_heredoc_intended_start;
        case lex_eheredoc_continue: return lex_eheredoc_start;
        case lex_eheredoc_intended_continue: return lex_eheredoc_intended_start;
        case lex_cheredoc_continue: return lex_cheredoc_start;
        case lex_cheredoc_intended_continue: return lex_cheredoc_intended_start;
        case lex_regexp_continue: return lex_regexp_start;
        case lex_epercent_presentation_continue: return lex_epercent_presentation_start;
        case lex_percent_presentation_continue: return lex_percent_presentation_start;

        default: return lex_none;
    }
}

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
            return hid_keyword;

        case lex_bin:
        case lex_oct:
        case lex_dec:
        case lex_hex:
        case lex_float:
        case lex_double:
            return hid_numeric;


        case lex_symbol: return hid_symbol;

        case lex_const: return hid_const;


        case lex_var_scoped:
        case lex_var_local:
        case lex_var_instance:
        case lex_var_object:
        case lex_var_global:
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


        case lex_heredoc_mark:
        case lex_heredoc_intended_mark:
        case lex_eheredoc_mark:
        case lex_eheredoc_intended_mark:
        case lex_cheredoc_mark:
        case lex_cheredoc_intended_mark:
            return hid_label;

        case lex_method_def_name:
        case lex_class_def_name:
        case lex_module_def_name:
            return hid_name_def;

        case lex_method:
            return hid_name_call;

        case lex_inline_commentary:
        case lex_commentary_continue:
        case lex_commentary_end:
            return hid_commentary;

//            case lex_string:
        case lex_command_continue:
        case lex_command_intercepted:
        case lex_command_interception:
        case lex_command_end:
        case lex_string_continue:
        case lex_string_end:
        case lex_estring_continue:
        case lex_estring_intercepted:
        case lex_estring_interception:
        case lex_estring_end:
        case lex_heredoc_continue:
        case lex_heredoc_intended_continue:
        case lex_heredoc_end:
        case lex_eheredoc_continue:
        case lex_eheredoc_intercepted:
        case lex_eheredoc_interception:
        case lex_eheredoc_intended_continue:
        case lex_cheredoc_continue:
        case lex_cheredoc_intercepted:
        case lex_cheredoc_interception:
        case lex_cheredoc_intended_continue:
        case lex_require_path:

        case lex_epercent_presentation_intercepted:
        case lex_epercent_presentation_interception:
        case lex_epercent_presentation_end:
        case lex_percent_presentation_end:
        case lex_epercent_presentation_continue:
        case lex_percent_presentation_continue:
            return hid_string;

        case lex_regexp_continue:
        case lex_regexp_intercepted:
        case lex_regexp_interception:
        case lex_regexp_end:
            return hid_regexp;


        //hid_scope_visibility

        case lex_error: return hid_error;

        default: return hid_none;
    }
}
