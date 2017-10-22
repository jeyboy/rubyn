#ifndef IDOCUMENT_H
#define IDOCUMENT_H

class IDocument {
    bool fully_readed;
protected:
    inline void setFullyReaded(const bool & readed) { fully_readed = readed; }
public:
    IDocument() : fully_readed(false) {}

    inline bool isFullyReaded() const { return fully_readed; }
};

#endif // IDOCUMENT_H
