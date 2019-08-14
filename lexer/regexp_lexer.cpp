#include "regexp_lexer.h"

#include "highlighter/highlight_format_factory.h"

RegexpLexer::RegexpLexer() : ILexer() {
//    HighlightingRule rule;

//    keywordFormat.setForeground(Qt::darkBlue);
//    keywordFormat.setFontWeight(QFont::Bold);
//    QStringList keywordPatterns;
//    keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
//                    << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
//                    << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
//                    << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
//                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
//                    << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
//                    << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
//                    << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
//                    << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
//                    << "\\bvoid\\b" << "\\bvolatile\\b" << "\\bbool\\b";
//    foreach (const QString &pattern, keywordPatterns) {
//        rule.pattern = QRegularExpression(pattern);
//        rule.format = keywordFormat;
//        highlightingRules.append(rule);
//    }

//    classFormat.setFontWeight(QFont::Bold);
//    classFormat.setForeground(Qt::darkMagenta);
//    rule.pattern = QRegularExpression("\\bQ[A-Za-z]+\\b");
//    rule.format = classFormat;
//    highlightingRules.append(rule);

//    singleLineCommentFormat.setForeground(Qt::red);
//    rule.pattern = QRegularExpression("//[^\n]*");
//    rule.format = singleLineCommentFormat;
//    highlightingRules.append(rule);

//    multiLineCommentFormat.setForeground(Qt::red);

//    quotationFormat.setForeground(Qt::darkGreen);
//    rule.pattern = QRegularExpression("\".*\"");
//    rule.format = quotationFormat;
//    highlightingRules.append(rule);

//    functionFormat.setFontItalic(true);
//    functionFormat.setForeground(Qt::blue);
//    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
//    rule.format = functionFormat;
//    highlightingRules.append(rule);

//    commentStartExpression = QRegularExpression("/\\*");
//    commentEndExpression = QRegularExpression("\\*/");
}

RegexpLexer::~RegexpLexer() {
    qDeleteAll(_rules);
    _rules.clear();
}

void RegexpLexer::handle(const QString & text, IHighlighter * lighter) {
    lighter -> setUserState(0);

    for(RulesList::ConstIterator it = _rules.cbegin(); it != _rules.cend(); it++) {
        const QTextCharFormat & format = HighlightFormatFactory::obj().getFormatFor((*it) -> format_uid);

        if ((*it) -> end_pattern) {
            int start_index = 0;
            if (lighter -> prevUserState() != 1)
                start_index = text.indexOf(*(*it) -> start_pattern);

            while (start_index >= 0) {
                QRegularExpressionMatch match = (*it) -> end_pattern -> match(text, start_index);

                int end_index = match.capturedStart();
                int captured_length = 0;

                if (end_index == -1) {
                    lighter -> setUserState(1);
                    captured_length = text.length() - start_index;
                } else {
                    captured_length =
                        end_index - start_index + match.capturedLength();
                }

                lighter -> setFormat(start_index, captured_length, format);
                start_index = text.indexOf(*(*it) -> start_pattern, start_index + captured_length);
            }
        } else {
            QRegularExpressionMatchIterator match_iterator = (*it) -> start_pattern -> globalMatch(text);

            while (match_iterator.hasNext()) {
                QRegularExpressionMatch match = match_iterator.next();
                lighter -> setFormat(match.capturedStart(), match.capturedLength(), format);
            }
        }
    }
}

bool RegexpLexer::isCompleterInitiable(const LEXEM_TYPE & lex, const bool & at_end) {
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

bool RegexpLexer::isCompleterContinuable(const LEXEM_TYPE & lex, const bool & /*at_end*/) {
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

bool RegexpLexer::isCompleterReplaceable(const LEXEM_TYPE & lex, const bool & at_start) {
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

