#ifndef DELPHI_PRESET
#define DELPHI_PRESET

#include "ihighlight_preset.h"

// keywords=
//  abs addr and ansichar ansistring array as asm begin boolean byte cardinal case char class comp const constructor currency destructor div do double
//  downto else end except exports extended false file finalization finally for function goto if implementation in inherited int64 initialization integer
//  interface is label library longint longword mod nil not object of on or packed pansichar pansistring pchar pcurrency pdatetime pextended pint64 pointer
//  private procedure program property pshortstring pstring pvariant pwidechar pwidestring protected public published raise real real48 record repeat set shl
//  shortint shortstring shr single smallint string then threadvar to true try type unit until uses val var varirnt while widechar widestring with word write
//  writeln xor

// comment=
//  \\(\\*[\\s\\S]*?\\*\\)
//  {(?!\\$)[\\s\\S]*?}
//  SingleLineCComments


// RegexLib.SingleQuotedString

// directive=
//  \\{\\$[a-zA-Z]+ .+\\}

// number=
//  \\$[a-zA-Z0-9]+\\b


class DelphiPreset : public IHighlightPreset, public SingletonPtr<CssPreset> {
public:
    DelphiPreset() {
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

#endif // DELPHI_PRESET
