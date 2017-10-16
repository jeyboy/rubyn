#ifndef IDOCUMENT_H
#define IDOCUMENT_H

#include <qfile>
#include <qpointer.h>

class BinaryDocument;
class ImageDocument;
class TextDocument;

class IDocument {
    IDocument * doc;
protected:
    QPointer<QIODevice> device;
    bool fully_readed;
public:
    IDocument(QIODevice * device) : device(device) {}

    virtual ~IDocument() {
        if (device) {
            if (device -> isOpen())
                device -> close();

            delete device;
        }
    }

    inline bool isOpened() const { return device && device -> isOpen(); }
    inline bool isReaded() const { return device && fully_readed; }

    BinaryDocument * asBinary() { return reinterpret_cast<BinaryDocument *>(doc); }
    ImageDocument * asImage() { return reinterpret_cast<ImageDocument *>(doc); }
    TextDocument * asText() { return reinterpret_cast<TextDocument *>(doc); }
};

#endif // IDOCUMENT_H
