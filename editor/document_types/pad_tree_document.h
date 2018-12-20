#ifndef PAD_TREE_DOCUMENT_H
#define PAD_TREE_DOCUMENT_H

#include "tree_document.h"

class PadTreeDocument : public TreeDocument {
    Q_OBJECT

    QString file_pad;
public:
    PadTreeDocument(File * file, const QString & pad);
};

#endif // PAD_TREE_DOCUMENT_H
