#ifndef CUSTOM_DOCUMENT_H
#define CUSTOM_DOCUMENT_H

#include <qobject.h>
#include <qhash.h>

#include "editor/idocument.h"
#include "custom_iblock.h"

class File;

namespace Custom {
    class Editor;
    class Cursor;

    class Document : public QObject, public IDocument {
        Q_OBJECT

        IBlock * _root, * _last;
        quint64 _inline_pos;
        quint64 _max_line_length;
        int _max_line_count;
        quint64 _lines_count;
        File * _file;
        QHash<Editor *, QPoint> scroll_pos;

        void openFile();
        QPoint & editorScrollPos(Editor * editor);
    public:
        Document(File * file, QObject * parent = nullptr);
        ~Document();

        IBlock * first() { return _root -> next(); }
        IBlock * last() { return _last; }

        void clear();

        void highlight(QRegularExpression * reg_exp, const bool & scroll = true);

        void insertLine(IBlock * after, const QByteArray & line);
        void appendLine(const QByteArray & line);
        quint64 linesCount() { return _lines_count; }

    protected:
        void procLineChange(IBlock * blk, const int & from, const int & to);

    signals:
        void maxCharsCountChanged(const quint64 &);
        void linesCountChanged(const quint64 &);

        friend class DrawContext;
        friend class Editor;
        friend class Cursor;
    };
}

#endif // CUSTOM_DOCUMENT_H
