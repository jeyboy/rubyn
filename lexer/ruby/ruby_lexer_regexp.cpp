#include "ruby_lexer_regexp.h"

using namespace Ruby;

LexerRegexp::LexerRegexp() : RegexpLexer() {
    QString keywords = "new nil def do self if unless yield each true else not elsif super then end ensure false for undef or when until module class return while throw rescue in alias and begin break next case retry define_method raise defined redo BEGIN END";

    addRule(
        new HighlightingRule(
            new QRegularExpression("\\b\\d+\\b"),
            hid_numeric
        )
    );

    addRule(
        new HighlightingRule(
            new QRegularExpression("\\b(" % keywords.replace(" ", "|") % ")\\b"),
            hid_keyword
        )
    );

    addRule(
        new HighlightingRule(
            new QRegularExpression("\\b(require)\\b"),
            hid_notice
        )
    );

    addRule(
        new HighlightingRule(
            new QRegularExpression("(\\$|@@|@)\\w+"),
            hid_var
        )
    );

    addRule(
        new HighlightingRule(
            new QRegularExpression("(\\b[a-z][!\\?\\w]*:)|((?<!:):[a-z][\\w!\\?]*)"),
            hid_symbol
        )
    );

    addRule(
        new HighlightingRule(
            new QRegularExpression("\\b[A-Z][A-Za-z]*\\b"),
            hid_name_def
        )
    );

    addRule(
        new HighlightingRule(
            new QRegularExpression("\\b[A-Z_]+\\b"),
            hid_const
        )
    );

    addRule(
        new HighlightingRule(
            new QRegularExpression("(\".*?(?=#{)|(?<=}).*?(?=#{)|(?<=}).*?\"|(\".*\"))"),
            hid_string
        )
    );

    addRule(
        new HighlightingRule(
            new QRegularExpression("'.*?'"),
            hid_string
        )
    );


    addRule(
        new HighlightingRule(
            new QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()"),
            hid_name_def
        )
    );

    addRule(
        new HighlightingRule(
            new QRegularExpression("\\/.*?\\/\\w*?"),
            hid_regexp
        )
    );

    addRule(
        new HighlightingRule(
            new QRegularExpression("#[^{][^\n]*"),
            hid_commentary
        )
    );

    addRule(
        new HighlightingRule(
            new QRegularExpression("=begin"),
            hid_commentary,
            new QRegularExpression("=end")
        )
    );
}

LexerRegexp::~LexerRegexp() {}
