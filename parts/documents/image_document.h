#ifndef IMAGE_DOCUMENT
#define IMAGE_DOCUMENT

#include "idocument.h"

class ImageDocument : public IDocument {

public:
    ImageDocument(const QString & mime, const QString & path, const QString & name, QIODevice * device)
        : IDocument(mime, path, name, device) {
        _doc_type = doc_type_image;

    }
};

#endif // IMAGE_DOCUMENT
