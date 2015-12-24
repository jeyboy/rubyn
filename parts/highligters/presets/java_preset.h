#ifndef JAVA_PRESET
#define JAVA_PRESET

#include "ihighlight_preset.h"


// keywords=
//  abstract assert boolean break byte case catch char class const continue default do double else enum extends false final finally float for goto if implements
//  import instanceof int interface long native new null package private protected public return short static strictfp super switch synchronized this throw throws
//  true transient try void volatile while
//  \\@interface\\b

// SingleLineCComments
// MultiLineCComments

// DoubleQuotedString
// SingleQuotedString

// annotation=
//  (?!\\@interface\\b)\\@[\\$\\w]+\\b

// number=
//  \\b([\\d]+(\\.[\\d]+)?|0x[a-f0-9]+)\\b

class JavaPreset : public IHighlightPreset, public SingletonPtr<JavaPreset> {
public:
    JavaPreset() {
        HighlightingRule rule;

//        QString keywords = "void class char volatile template typedef union unsigned virtual typename const double enum explicit friend private protected public inline short signals static struct slots signed int long namespace operator";
//        rule.pattern = QRegularExpression("\\b(" % keywords.replace(" ", "|") % ")\\b");
//        rule.format = HighlightFormatFactory::obj().getFormatFor(format_keyword);
//        highlighting_rules.append(rule);


//        rule.pattern = QRegularExpression("\\b(?<![\"])[A-Z_]\\w*[a-z]\\w*(?![\"\\)=\\.\\-])\\b");
//        rule.format = HighlightFormatFactory::obj().getFormatFor(format_class);
//        highlighting_rules.append(rule);


//        rule.pattern = QRegularExpression("^ *#.*");
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

#endif // JAVA_PRESET
