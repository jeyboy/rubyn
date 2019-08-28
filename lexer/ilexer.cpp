#include "ilexer.h"

#include <qdebug.h>

bool ILexer::isBDigit(const char & c) { return c == '0' || c == '1'; }
bool ILexer::isODigit(const char & c) { return c >= '0' && c <= '7'; }
bool ILexer::isDigit(const char & c) { return c >= '0' && c <= '9'; }
bool ILexer::isHDigit(const char & c) { return isDigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'); }

bool ILexer::isUpper(const char & c) { return c >= 'A' && c <= 'Z'; }
bool ILexer::isLower(const char & c) { return c >= 'a' && c <= 'z'; }
bool ILexer::isAlpha(const char & c) { return isLower(c) || isUpper(c); }
bool ILexer::isAlphaNum(const char & c) { return isAlpha(c) || isDigit(c); }

bool ILexer::isWord(const char & c, const bool & with_digits) { return c == '_' || isAlpha(c) || (with_digits && isDigit(c)); }

//    bool ILexer::isCtrl(const char & c) { return c >= 0 && c < 0x20 || c == 0x7f; }
bool ILexer::isBlank(const char & c) { return c == ' ' || c == '\t'; }
//bool ILexer::isSpace(const char & c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v'; }
    //template<typename ch_t> inline bool is_punct(ch_t c)   {   return c>='!' && c<='/' || c>=':' && c<='@' || c>='[' && c<='`' || c>='{' && c<='~';    }
    //template<typename ch_t> inline bool is_graph(ch_t c)   {   return c>='!' && c<='~';    }
    //template<typename ch_t> inline bool is_print(ch_t c)   {   return c>=' ' && c<='~';    }
    //template<typename ch_t> inline bool is_crlf(ch_t c) { return c=='\r' || c=='\n'; }

int ILexer::lineState(BlockUserData * udata) {
    LEXEM_TYPE lex = LEX_NONE_STATE;

    if (udata -> stack_token)
        lex = udata -> stack_token -> lexem;
    else lex = udata -> token_end -> prev -> lexem;

    return lex | (udata -> level << int_bits_offset);
}

bool ILexer::isCompleterInitiable(const LEXEM_TYPE & lex, const bool & at_end) {
    switch(lex) {
        case lex_inline_commentary_content:
        case lex_commentary_content:
        case lex_bin:
        case lex_oct:
        case lex_dec:
        case lex_hex:
        case lex_float:
        case lex_double:
            return false;

        case lex_operator_add:
        case lex_operator_minus:
        case lex_operator_multiplication:
        case lex_operator_division:
        case lex_operator_modulus:
        case lex_operator_exponentiation:

        case lex_operator_add_assigment:
        case lex_operator_minus_assigment:
        case lex_operator_multiplication_assigment:
        case lex_operator_division_assigment:
        case lex_operator_modulus_assigment:
        case lex_operator_exponentiation_assigment:

        case lex_operator_assigment:
        case lex_operator_comparison:
        case lex_operator_not_equal:
        case lex_operator_great:
        case lex_operator_less:
        case lex_operator_great_eql:
        case lex_operator_less_eql:
        case lex_operator_sort:
        case lex_operator_equality:
        case lex_dot_dot:
        case lex_dot_dot_dot:

        case lex_operator_bit_and:
        case lex_operator_bit_or:
        case lex_operator_bit_exclusive_or:
        case lex_operator_bit_not:
        case lex_operator_bit_left_shift:
        case lex_operator_bit_right_shift:

        case lex_operator_bit_and_assigment:
        case lex_operator_bit_or_assigment:
        case lex_operator_bit_exclusive_or_assigment:
        case lex_operator_bit_left_shift_assigment:
        case lex_operator_bit_right_shift_assigment:


        case lex_rocket:
        case lex_question_mark:
        case lex_colon:

        case lex_operator_not:
        case lex_operator_and:
        case lex_operator_or:


        case lex_operator_and_assigment:
        case lex_operator_or_assigment:

        case lex_resolution:
            return at_end;
    }

    return true;
}

bool ILexer::isCompleterContinuable(const LEXEM_TYPE & lex, const bool & /*at_end*/) {
    switch(lex) {
        case lex_undefined: //INFO: compatibility for not lexable documents

        case lex_method:
        case lex_word:
        case lex_const:
        case lex_var_local:
        case lex_var_instance:
        case lex_var_object:
        case lex_var_global:
        case lex_end_of_code:
        case lex_commentary_start:
        case lex_commentary_end:

        case lex_global_pre_hook:
        case lex_global_post_hook:

        case lex_alias:
        case lex_operator_and_word:

        case lex_begin:
        case lex_loop_break:
        case lex_case:
        case lex_class_def:
        case lex_method_def:
        case lex_do:
        case lex_else:
        case lex_elsif:
        case lex_end:
        case lex_block_ensure:

        case lex_operator_comparison:
        case lex_operator_equality:

        case lex_extend:
        case lex_for:
        case lex_if:
        case lex_in:
        case lex_include:

        case lex_lambda_def:
        case lex_module_def:
        case lex_loop_next:
        case lex_operator_not:
        case lex_operator_or_word:
        case lex_visibility_scope:
        case lex_proc_def:
        case lex_raise:
        case lex_loop_redo:
        case lex_require:
        case lex_block_rescue:
        case lex_block_retry:
        case lex_return:
        case lex_self:
        case lex_super:
        case lex_then:
        case lex_undef:
        case lex_unless:
        case lex_until:
        case lex_when:
        case lex_while:
        case lex_yield:
        case lex_loop:
            return true;
    }

    return false;
}

bool ILexer::isCompleterReplaceable(const LEXEM_TYPE & lex, const bool & at_start) {
    switch(lex) {
        case lex_undefined: //INFO: compatibility for not lexable documents

        case lex_method:
        case lex_word:
        case lex_const:
        case lex_var_local:
        case lex_var_instance:
        case lex_var_object:
        case lex_var_global:
            return !at_start;
    }

    return false;
}

ILexer::ILexer() : int_bits_offset(sizeof(int) / 2 * 8) {

}

ILexer::~ILexer() {

}
