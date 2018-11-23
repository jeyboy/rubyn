#ifndef IDOCUMENT_H
#define IDOCUMENT_H

#include <qvariant.h>

class IDocument {
    bool fully_readed;
protected:
    inline void setFullyReaded(const bool & readed) { fully_readed = readed; }
public:
    IDocument() : fully_readed(false) {}
    virtual ~IDocument() {}

    inline bool isFullyReaded() const { return fully_readed; }
    virtual bool isChanged() const { return false; }
    virtual bool save() const { return false; }

    virtual bool dump(QVariant & /*data*/) { return false; }
    virtual bool restore(const QVariant & /*data*/) { return false; }
};

#endif // IDOCUMENT_H
