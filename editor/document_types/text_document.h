#ifndef TEXT_DOCUMENT
#define TEXT_DOCUMENT

#include <qpointer.h>
#include <qtextdocument.h>

#include "misc/defines.h"
#include "project/code_formats.h"
#include "editor/idocument.h"
#include "editor/text_document_layout.h"

#define READ_LIMIT (qint64)(512000) // ~512 kb

class Project;
class File;
class ILexer;
class Highlighter;

class TextDocument : public QObject, public IDocument {
    Q_OBJECT

    static QLatin1String tab_space;
    static QHash<QChar, bool> word_boundary;

//    int start_scroll_pos;
//    int pos, removed, added;
protected:
    QPointer<QTextDocument> _doc;

    ILexer * _lexer;

    File * _file;

    bool identificateLexer();
signals:
    void enterPressed();
    void wordHovered(const QPoint & point, const int & start, const int & end);
public:
    TextDocumentLayout * layout;

    TextDocument(File * file);

    ~TextDocument();

    const QLatin1String & tabSpace() { return tab_space; }

    QTextDocument * toQDoc() { return _doc; }

    void readNextBlock();

    void lexicate(const QString & text, Highlighter * highlighter);

    bool isCompleterContinuable(const LEXEM_TYPE & lex, const bool & at_end = true);

    void paraOpositionStr(const PARA_TYPE & para, QString & res);

    LEXEM_TYPE getWordBoundaries(EDITOR_POS_TYPE & start, EDITOR_POS_TYPE & length, const QTextBlock & block, const EDITOR_POS_TYPE & pos, const bool & global_offset = true);
    ParaCell * getPara(const QTextBlock & block, const EDITOR_POS_TYPE & pos);

    bool dump(QVariant & data);
    bool restore(const QVariant & data);

//    inline void setStartScrollPos(const int & pos) { start_scroll_pos = pos; }
//    inline int startScrollPos() {
//        int res = start_scroll_pos;
//        start_scroll_pos = 0;
//        return res;
//    }
protected slots:
//    void changesInContent(int position, int removed_count, int added_count);
};

#endif // TEXT_DOCUMENT
