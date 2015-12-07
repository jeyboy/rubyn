#ifndef HIGHLIGTERS_FACTORY
#define HIGHLIGTERS_FACTORY

#include "misc/singleton.h"
#include "c_plus_highlighter.h"
#include "ruby_highlighter.h"

class HighlightersFactory : public QObject, public Singleton<HighlightersFactory> {
public:
    HighlightersFactory() { }
    ~HighlightersFactory() { }

    bool proceedDocument(const QString & mime, QTextDocument * document) {
        if (mime == QStringLiteral("h") || mime == QStringLiteral("cpp")) {
            new CPlusHighLighter(document);
            return true;
        } else if (mime == QStringLiteral("rb")) {
            new RubyHighLighter(document);
            return true;
        }
        return false;
    }
};

#endif // HIGHLIGTERS_FACTORY
