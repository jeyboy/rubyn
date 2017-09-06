#ifndef IMAGE_DOCUMENT
#define IMAGE_DOCUMENT

#include "idocument.h"

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
    ImageDocument(const QString & path, const QString & name, QIODevice * device, Lexer * lexer = 0)
        : IDocument(path, name, device, lexer)
    {
        _device -> close();
    }
};

#endif // IMAGE_DOCUMENT
