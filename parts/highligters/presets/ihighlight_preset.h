#ifndef IHIGHLIGHT_PRESET
#define IHIGHLIGHT_PRESET

#include <qdebug.h>
#include <qvector.h>
#include <qstringbuilder.h>

#include <parts/highligters/base/highlighter_rule.h>
#include <parts/highligters/base/highlight_format_factory.h>

class IHighlightPreset {
protected:
    QVector<HighlightingRule> highlighting_rules;

    QRegularExpression comment_start_expression;
    QRegularExpression comment_end_expression;
public:
    virtual ~IHighlightPreset() {}

    HighlightingRule numbersRule() {
        HighlightingRule rule;
        rule.pattern = QRegularExpression("\\b\\d+\\b"); // \\b[\\d\\.]+\\b
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_numbers);
        return rule;
    }

    HighlightingRule singleQuotationRule() {
        HighlightingRule rule;
        rule.pattern = QRegularExpression("'.*?'");
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_single_quotation);
        return rule;
    }

    HighlightingRule doubleQuotationRule() {
        HighlightingRule rule;
        rule.pattern = QRegularExpression("\".*?\"");
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_double_quotation);
        return rule;
    }

    const QVector<HighlightingRule> & rules() const { return highlighting_rules; }
    const QRegularExpression & commentStartExpression() const { return comment_start_expression; }
    const QRegularExpression & commentEndExpression() const { return comment_end_expression; }
};

#endif // IHIGHLIGHT_PRESET
