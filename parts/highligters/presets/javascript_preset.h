#ifndef JAVASCRIPT_PRESET
#define JAVASCRIPT_PRESET

#include "ihighlight_preset.h"

// keywords=
//  abstract boolean break byte case catch char class const continue debugger default delete do double else enum export extends false final finally float
//  for function goto if implements import in instanceof int interface long native new null package private protected public return short static super switch
//  synchronized this throw throws transient true try typeof var void volatile while with

// SingleLineCComments
// MultiLineCComments

// DoubleQuotedString
// SingleQuotedString

class JavascriptPreset : public IHighlightPreset, public SingletonPtr<JavascriptPreset> {
public:
    JavascriptPreset() {
        HighlightingRule rule;

//        QString keywords = "void class char volatile template typedef union unsigned virtual typename const double enum explicit friend private protected public inline short signals static struct slots signed int long namespace operator";
//        rule.pattern = QRegularExpression("\\b(" % keywords.replace(" ", "|") % ")\\b");
//        rule.format = HighlightFormatFactory::obj().getFormatFor(format_keyword);
//        highlighting_rules.append(rule);


//        rule.pattern = QRegularExpression("\\b(?<![\"])[A-Z_]\\w*[a-z]\\w*(?![\"\\)=\\.\\-])\\b");
//        rule.format = HighlightFormatFactory::obj().getFormatFor(format_class);
//        highlighting_rules.append(rule);


        rule.pattern = QRegularExpression("^\\s*#.*");
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_preprocessing);
        highlighting_rules.append(rule);


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

#endif // JAVASCRIPT_PRESET
