#ifndef RUBY_PRESET
#define RUBY_PRESET

#include "ihighlight_preset.h"

class RubyPreset : public IHighlightPreset, public SingletonPtr<RubyPreset> {
public:
    RubyPreset() {
        HighlightingRule rule;

        QString keywords = "new nil def do self if unless yield each true else not elsif super then end ensure false for undef or when until module class return while throw rescue in alias and begin break next case retry define_method raise defined redo BEGIN END";
        rule.pattern = QRegularExpression("\\b(" % keywords.replace(" ", "|") % ")\\b");
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_keyword);
        highlighting_rules.append(rule);


        rule.pattern = QRegularExpression("(\\$|@@|@)\\w+");
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_variable);
        highlighting_rules.append(rule);


        rule.pattern = QRegularExpression("(\\b[a-z][!\\?\\w]*:)|((?<!:):[a-z][\\w!\\?]*)");
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_symbol);
        highlighting_rules.append(rule);

//        'Array Bignum Binding Class Continuation Dir Exception FalseClass File::Stat File Fixnum Fload Hash Integer IO MatchData Method Module NilClass Numeric Object Proc Range Regexp String Struct::TMS Symbol ThreadGroup Thread Time TrueClass'
        rule.pattern = QRegularExpression("\\b[A-Z][A-Za-z]*\\b");
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_class);
        highlighting_rules.append(rule);


        // add const support ([A-Z]+)
        rule.pattern = QRegularExpression("\\b[A-Z_]+\\b");
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_const);
        highlighting_rules.append(rule);


        rule.pattern = QRegularExpression("(\".*?(?=#{)|(?<=}).*?(?=#{)|(?<=}).*?\"|(\".*\"))");
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_double_quotation);
        highlighting_rules.append(rule);


        highlighting_rules.append(singleQuotationRule());


        rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_func);
        highlighting_rules.append(rule);


        rule.pattern = QRegularExpression("#[^{][^\n]*");
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_signle_line_comment);
        highlighting_rules.append(rule);


        highlighting_rules.append(numbersRule());


        rule.pattern = QRegularExpression("\\/.*?\\/\\w*?");
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_regular_expresions);
        highlighting_rules.append(rule);


        comment_start_expression = QRegularExpression("=begin");
        comment_end_expression = QRegularExpression("=end");
    }
};

#endif // RUBY_PRESET
