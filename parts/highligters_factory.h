#ifndef HIGHLIGTERS_FACTORY
#define HIGHLIGTERS_FACTORY

#include "parts/documents/text_document.h"
#include "misc/singleton.h"

#include "highligters/presets/presets_list.h"
#include "highligters/highlighter.h"

class HighlightersFactory : public QObject, public Singleton<HighlightersFactory> {
    QHash<QString, IHighlightPreset *> presets;
public:
    HighlightersFactory() {
        presets.insert(QStringLiteral("rb"), &RubyPreset::obj());

        presets.insert(QStringLiteral("h"), &CPlusPreset::obj());
        presets.insert(QStringLiteral("cpp"), &CPlusPreset::obj());

        presets.insert(QStringLiteral("sql"), &SQLPreset::obj());

        presets.insert(QStringLiteral("cs"), &CSharpPreset::obj());
    }

    bool proceedDocument(TextDocument * document) {
        bool result = presets.contains(document -> mime());

        if (presets.contains(document -> mime())) {
            new Highlighter(document, presets[document -> mime()]);
        } else {
            //TODO: inform about missed preset
        }

        return result;
    }
};

#endif // HIGHLIGTERS_FACTORY
