#ifndef HIGHLIGHT_RULE_H
#define HIGHLIGHT_RULE_H

#include "identifiers.h"

#include <QRegularExpression>

struct HighlightingRule {
    QRegularExpression * start_pattern;
    QRegularExpression * end_pattern;
    Identifier format_uid;

    HighlightingRule() : start_pattern(0), end_pattern(0), format_uid(hid_none) {}

    HighlightingRule(QRegularExpression * spattern, const Identifier & uid, QRegularExpression * epattern = 0)
        : start_pattern(spattern), end_pattern(epattern), format_uid(uid) { }

    ~HighlightingRule() {
        delete start_pattern;
        delete end_pattern;
    }
};

#endif // HIGHLIGHT_RULE_H
