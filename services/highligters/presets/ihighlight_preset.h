#ifndef IHIGHLIGHT_PRESET
#define IHIGHLIGHT_PRESET

#include <qdebug.h>
#include <qvector.h>
#include <qstringbuilder.h>

#include <services/highligters/base/highlighter_rule.h>
#include <services/highligters/base/highlight_format_factory.h>

class IHighlightPreset {
protected:
    QVector<HighlightingRule> highlighting_rules;

    QRegularExpression comment_start_expression;
    QRegularExpression comment_end_expression;
public:
    virtual ~IHighlightPreset() { qDebug() << "IHighlightPreset"; }

    const QVector<HighlightingRule> & rules() const { return highlighting_rules; }
    const QRegularExpression & commentStartExpression() const { return comment_start_expression; }
    const QRegularExpression & commentEndExpression() const { return comment_end_expression; }
};

#endif // IHIGHLIGHT_PRESET
