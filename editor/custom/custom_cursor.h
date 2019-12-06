#ifndef CUSTOM_CURSOR_H
#define CUSTOM_CURSOR_H

namespace Custom {
    class Document;

    class Cursor {
        Document * _doc;
    public:
        Cursor(Document * doc);
    };
};

#endif // CUSTOM_CURSOR_H
