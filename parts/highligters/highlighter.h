#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <qsyntaxhighlighter.h>

#include "ihighlight_preset.h"

class Highlighter : public QSyntaxHighlighter {
    Q_OBJECT
protected:
    void highlightBlock(const QString & text) Q_DECL_OVERRIDE;

    IHighlightPreset * preset;
public:
    Highlighter(QTextDocument * parent, IHighlightPreset * preset);
};

#endif // IHIGHLIGHTER_H
