#ifndef C_PLUS_PRESET
#define C_PLUS_PRESET

#include "ihighlight_preset.h"

class CPlusPreset : public IHighlightPreset, public SingletonPtr<CPlusPreset> {
public:
    ~CPlusPreset() {}

    CPlusPreset() {
        HighlightingRule rule;

        QStringList keywordPatterns;
        keywordPatterns << "char" << "class" << "const"
                        << "double" << "enum" << "explicit"
                        << "friend" << "inline" << "int"
                        << "long" << "namespace" << "operator"
                        << "private" << "protected" << "public"
                        << "short" << "signals" << "signed"
                        << "slots" << "static" << "struct"
                        << "template" << "typedef" << "typename"
                        << "union" << "unsigned" << "virtual"
                        << "void" << "volatile";
        for(QStringList::ConstIterator pattern = keywordPatterns.constBegin(); pattern != keywordPatterns.constEnd(); pattern++) {
            rule.pattern = QRegularExpression(QString("\\b" + (*pattern) + "\\b"));
            rule.format = HighlightFormatFactory::obj().getFormatFor(format_keyword);
            highlighting_rules.append(rule);
        }


        rule.pattern = QRegularExpression("\\b(?<![\"])[A-Z_]\\w*[a-z]\\w*(?![\"\\)=\\.\\-])\\b");
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_class);
        highlighting_rules.append(rule);


        rule.pattern = QRegularExpression("\".*\"");
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_double_quotation);
        highlighting_rules.append(rule);


        rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_func);
        highlighting_rules.append(rule);


        rule.pattern = QRegularExpression("//[^\n]*");
        rule.format = HighlightFormatFactory::obj().getFormatFor(format_signle_line_comment);
        highlighting_rules.append(rule);


        comment_start_expression = QRegularExpression("/\\*");
        comment_end_expression = QRegularExpression("\\*/");
    }
};

#endif // C_PLUS_PRESET
