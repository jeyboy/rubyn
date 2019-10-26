#ifndef CUSTOM_DOCUMENT_H
#define CUSTOM_DOCUMENT_H

#include <qobject.h>

#include "editor/idocument.h"
#include "custom_iblock.h"

class File;

namespace Custom {
    class Editor;

    class Document : public QObject, public IDocument {
        Q_OBJECT

        IBlock * _root, * _last;
        quint64 _inline_pos;
        quint64 _max_line_length;
        quint64 _lines_count;
        File * _file;

        void openFile();
    public:
        Document(File * file, QObject * parent = nullptr);
        ~Document();

        void clear();

        void addLine(const QString & line);
        quint64 linesCount() { return _lines_count; }

        friend class Editor;
    };
}

#endif // CUSTOM_DOCUMENT_H
