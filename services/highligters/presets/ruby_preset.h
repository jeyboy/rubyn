#ifndef RUBY_PRESET
#define RUBY_PRESET

#include "ihighlight_preset.h"

class RubyPreset : public IHighlightPreset, public SingletonPtr<RubyPreset> {
public:
    virtual ~RubyPreset() { qDebug() << "RubyPreset"; }

    RubyPreset() {
        HighlightingRule rule;

        QStringList keywordPatterns;
        keywordPatterns << "alias" << "and" << "BEGIN"
                        << "begin" << "break" << "case"
                        << "class" << "def" << "define_method"
                        << "defined" << "do" << "each"
                        << "else" << "elsif" << "END"
                        << "end" << "ensure" << "false"
                        << "for" << "if" << "in"
                        << "module" << "new" << "next"
                        << "nil" << "not" << "or"
                        << "raise" << "redo" << "rescue"
                        << "retry" << "return" << "self"
                        << "super" << "then" << "throw"
                        << "true" << "undef" << "unless"
                        << "until" << "when" << "while"
                        << "yield";
        for(QStringList::ConstIterator pattern = keywordPatterns.constBegin(); pattern != keywordPatterns.constEnd(); pattern++) {
            rule.pattern = QRegularExpression("\\b" % (*pattern) % "\\b");
            rule.format = HighlightFormatFactory::obj().getFormatFor(format_keyword);
            highlighting_rules.append(rule);
        }

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

        rule.pattern = QRegularExpression("'.*?'"); // need to check
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_single_quotation);
        highlighting_rules.append(rule);


        rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_func);
        highlighting_rules.append(rule);

        rule.pattern = QRegularExpression("#[^{][^\n]*");
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_signle_line_comment);
        highlighting_rules.append(rule);

        //TODO: set method color for numbers
        //TODO: add rule for regular expresions /.*/\w*

        comment_start_expression = QRegularExpression("=begin");
        comment_end_expression = QRegularExpression("=end");
    }
};

#endif // RUBY_PRESET
