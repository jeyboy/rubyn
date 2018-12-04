#ifndef IDOCUMENT_H
#define IDOCUMENT_H

#include "project/code_formats.h"

#include <qvariant.h>

class ILexer;

class IDocument {
    bool _fully_readed;
protected:
    bool _changed;

    ILexer * _lexer;

    inline void setFullyReaded(const bool & readed) { _fully_readed = readed; }
public:
    inline IDocument() : _fully_readed(false), _changed(false), _lexer(nullptr) {}
    virtual ~IDocument();

    inline bool isFullyReaded() const { return _fully_readed; }
    inline bool isChanged() const { return _changed; }

    virtual bool save() { return false; }
    virtual bool dump(QVariant & /*data*/) { return false; }
    virtual bool restore(const QVariant & /*data*/) { return false; }

    virtual bool registerStateChangedCallback(QObject * /*target*/, const char * /*slot*/) { return false; }
};

#endif // IDOCUMENT_H
