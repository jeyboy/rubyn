#ifndef CUSTOM_DOCUMENT_H
#define CUSTOM_DOCUMENT_H

#include <QObject>
#include "editor/idocument.h"
#include "custom_iblock.h"

class File;

namespace Custom {
    class Document : public QObject, public IDocument {
        Q_OBJECT

        IBlock * _root, * _last, _curr;
        quint32 _inline_pos;
        File * _file;

        void openFile();
    public:
        Document(File * file, QObject * parent = nullptr);
        ~Document();

        void clear();

        void addLine(const QString & line);
    };
}

#endif // CUSTOM_DOCUMENT_H
