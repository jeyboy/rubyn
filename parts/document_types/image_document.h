#ifndef IMAGE_DOCUMENT
#define IMAGE_DOCUMENT

#include "idocument.h"

#include "parts/formats/format_image.h"

//For example, you can add an image as a resource in order to reference it from within the document:

//    document->addResource(QTextDocument::ImageResource,
//        QUrl("mydata://image.png"), QVariant(image));

//The image can be inserted into the document using the QTextCursor API:

//    QTextImageFormat imageFormat;
//    imageFormat.setName("mydata://image.png");
//    cursor.insertImage(imageFormat);

//Alternatively, you can insert images using the HTML img tag:

//    editor->append("<img src=\"mydata://image.png\" />");

class ImageDocument : public IDocument {
public:
    ImageDocument(const QString & path, const QString & name, QIODevice * device, IFormat * format)
        : IDocument(path, name, device, format) {}
};

#endif // IMAGE_DOCUMENT
