#ifndef TEXT_DOCUMENT
#define TEXT_DOCUMENT

#include <qpointer.h>
#include <qtextdocument.h>

#include "misc/defines.h"
#include "project/code_formats.h"
#include "editor/idocument.h"
#include "editor/text_document_layout.h"

#define READ_LIMIT 512000LL // ~512 kb

class Project;
class File;
class ILexer;
class Highlighter;

class TextDocument : public QObject, public IDocument {
    Q_OBJECT

    static QLatin1String tab_space;
    static QHash<QChar, bool> word_boundary;

    int scroll_pos_y;
//    int pos, removed, added;
protected:
    QPointer<QTextDocument> _doc;

    ILexer * _lexer;

    File * _file;

    bool identificateLexer();
    bool registerStateChangedCallback(QObject * target, const char * slot);
signals:
    void hasChanges(const QString & uid, const bool & has);
    void enterPressed();
    void wordHovered(const QPoint & point, const int & start, const int & end);
public:
    TextDocumentLayout * layout;

    TextDocument(File * file);

    ~TextDocument();

    inline bool canHasFoldings() { return _lexer != nullptr; }
    inline bool canHasBreakpoints() { return _lexer != nullptr; }

    const QLatin1String & tabSpace() { return tab_space; }

    QTextDocument * toQDoc() { return _doc; }

    const QString & documentUid();

    void readNextBlock();

    void lexicate(const QString & text, Highlighter * highlighter);

    bool isCompleterInitiable(const LEXEM_TYPE & lex, const bool & at_end);
    bool isCompleterContinuable(const LEXEM_TYPE & lex, const bool & at_end);

    void paraOpositionStr(const PARA_TYPE & para, QString & res);

    LEXEM_TYPE getWordBoundaries(EDITOR_POS_TYPE & start, EDITOR_POS_TYPE & length, const QTextBlock & block, const EDITOR_POS_TYPE & pos, const bool & global_offset = true);
    ParaCell * getPara(const QTextBlock & block, const EDITOR_POS_TYPE & pos);

    bool save();
    bool dump(QVariant & data);
    bool restore(const QVariant & data);

    inline void setRevision(const int & new_revision) { _revision = new_revision; }
    inline int revision() { return _revision; }

    inline void setVerticalScrollPos(const int & pos) { scroll_pos_y = pos; }
    inline int verticalScrollPos(const bool & drop = true) {
        int res = scroll_pos_y;
        if (drop)
            scroll_pos_y = 0;
        return res;
    }
protected slots:
    void hasUnsavedChanges(const bool & has);
//    void changesInContent(int position, int removed_count, int added_count);
};

#endif // TEXT_DOCUMENT
