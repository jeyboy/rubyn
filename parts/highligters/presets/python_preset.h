#ifndef PYTHON_PRESET
#define PYTHON_PRESET

#include "ihighlight_preset.h"

//keywords=
//  and assert break class continue def del elif else except exec finally for from global if import in is lambda not or pass print raise return try yield while

//special=
//  None True False self cls class_

// SingleLinePerlComments
//comment=
//  (['\"]{3})([^\\1])*?\\1

//decorator=
//  ^\\s*@\\w+

//string=
//  "(?!")(?:\\.|\\\\\\"|[^\\""\\n\\r])*"
//  '(?!')*(?:\\.|(\\\\\\')|[^\\''\\n\\r])*'

//number=
//  \\b\\d+\\.?\\w*

class PythonPreset : public IHighlightPreset, public SingletonPtr<PythonPreset> {
public:
    PythonPreset() {
        HighlightingRule rule;

//        QString keywords = "void class char volatile template typedef union unsigned virtual typename const double enum explicit friend private protected public inline short signals static struct slots signed int long namespace operator";
//        rule.pattern = QRegularExpression("\\b(" % keywords.replace(" ", "|") % ")\\b");
//        rule.format = HighlightFormatFactory::obj().getFormatFor(format_keyword);
//        highlighting_rules.append(rule);


//        rule.pattern = QRegularExpression("\\b(?<![\"])[A-Z_]\\w*[a-z]\\w*(?![\"\\)=\\.\\-])\\b");
//        rule.format = HighlightFormatFactory::obj().getFormatFor(format_class);
//        highlighting_rules.append(rule);


//        rule.pattern = QRegularExpression("^\\s*#.*");
//        rule.format = HighlightFormatFactory::obj().getFormatFor(format_preprocessing);
//        highlighting_rules.append(rule);


//        rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
//        rule.format = HighlightFormatFactory::obj().getFormatFor(format_func);
//        highlighting_rules.append(rule);


//        highlighting_rules.append(singleQuotationRule());


//        highlighting_rules.append(doubleQuotationRule());


//        highlighting_rules.append(numbersRule());


//        rule.pattern = QRegularExpression("//[^\n]*");
//        rule.format = HighlightFormatFactory::obj().getFormatFor(format_signle_line_comment);
//        highlighting_rules.append(rule);

//        comment_start_expression = QRegularExpression("/\\*");
//        comment_end_expression = QRegularExpression("\\*/");
    }
};

#endif // PYTHON_PRESET
