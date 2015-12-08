#ifndef HIGHLIGTERS_FACTORY
#define HIGHLIGTERS_FACTORY

#include "misc/singleton.h"
#include "presets/presets_list.h"
#include "highlighter.h"

class HighlightersFactory : public QObject, public Singleton<HighlightersFactory> {
    QHash<QString, IHighlightPreset *> presets;
public:
    HighlightersFactory() {
        presets.insert(QStringLiteral("rb"), &RubyPreset::obj());

        presets.insert(QStringLiteral("h"), &CPlusPreset::obj());
        presets.insert(QStringLiteral("cpp"), &CPlusPreset::obj());

        presets.insert(QStringLiteral("sql"), &SQLPreset::obj());
    }

    bool proceedDocument(const QString & mime, QTextDocument * document) {
        bool result = presets.contains(mime);

        if (presets.contains(mime)) {
            new Highlighter(document, presets[mime]);
        } else {
            //TODO: inform about missed preset
        }

        return result;
    }
};

#endif // HIGHLIGTERS_FACTORY
