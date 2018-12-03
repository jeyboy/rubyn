#ifndef PSEUDO_TEXT_DOCUMENT_H
#define PSEUDO_TEXT_DOCUMENT_H

#include "editor/idocument.h"

class PseudoTextDocument : public IDocument {
public:
    PseudoTextDocument(const FormatType & format);
};

#endif // PSEUDO_TEXT_DOCUMENT_H
