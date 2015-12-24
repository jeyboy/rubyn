#ifndef C_SHARP_PRESET
#define C_SHARP_PRESET

#include "ihighlight_preset.h"

//keywords=
//  abstract as base bool break byte case catch char checked class const continue decimal default delegate do double else enum event explicit
//  extern false finally fixed float for foreach get goto if implicit in int interface internal is lock long namespace new null object operator
//  out override params private protected public readonly ref return sbyte sealed set short sizeof stackalloc static string struct switch this
//  throw true try typeof uint ulong unchecked unsafe ushort using virtual void while

class CSharpPreset : public IHighlightPreset, public SingletonPtr<CSharpPreset> {
public:
    CSharpPreset() {
        HighlightingRule rule;

//        QString keywords = "void class char volatile template typedef union unsigned virtual typename const double enum explicit friend private protected public inline short signals static struct slots signed int long namespace operator";
//        rule.pattern = QRegularExpression("\\b(" % keywords.replace(" ", "|") % ")\\b");
//        rule.format = HighlightFormatFactory::obj().getFormatFor(format_keyword);
//        highlighting_rules.append(rule);


//        rule.pattern = QRegularExpression("\\b(?<![\"])[A-Z_]\\w*[a-z]\\w*(?![\"\\)=\\.\\-])\\b");
//        rule.format = HighlightFormatFactory::obj().getFormatFor(format_class);
//        highlighting_rules.append(rule);


//        rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
//        rule.format = HighlightFormatFactory::obj().getFormatFor(format_func);
//        highlighting_rules.append(rule);


        rule.pattern = QRegularExpression("^\\s*#.*");
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_preprocessing);
        highlighting_rules.append(rule);


        highlighting_rules.append(doubleQuotationRule());


        highlighting_rules.append(singleQuotationRule());


        rule.pattern = QRegularExpression("//[^\n]*");
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_signle_line_comment);
        highlighting_rules.append(rule);

        comment_start_expression = QRegularExpression("/\\*");
        comment_end_expression = QRegularExpression("\\*/");
    }
};

#endif // C_SHARP_PRESET
