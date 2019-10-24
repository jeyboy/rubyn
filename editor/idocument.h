#ifndef IDOCUMENT_H
#define IDOCUMENT_H

#include "project/code_formats.h"

#include <qvariant.h>

#define READ_LIMIT 512000LL // ~512 kb

class ILexer;

class IDocument {
    bool _fully_readed;
protected:
    ILexer * _lexer;
    int scroll_pos_y;

    static QLatin1String tab_space;
    static QHash<QChar, bool> word_boundary;

    inline void setFullyReaded(const bool & readed) { _fully_readed = readed; }
public:
    inline IDocument() : _fully_readed(false), _lexer(nullptr), scroll_pos_y(0) {}
    virtual ~IDocument();

    inline bool isFullyReaded() const { return _fully_readed; }
    virtual bool isChanged() const { return false; }

    virtual bool save() { return false; }
    virtual bool dump(QVariant & /*data*/) { return false; }
    virtual bool restore(const QVariant & /*data*/) { return false; }

    virtual bool registerStateChangedCallback(QObject * /*target*/, const char * /*slot*/) { return false; }
};

#endif // IDOCUMENT_H
