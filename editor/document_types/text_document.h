#ifndef TEXT_DOCUMENT
#define TEXT_DOCUMENT

#include <qtextdocument.h>

#include "misc/defines.h"
#include "editor/idocument.h"
#include "editor/text_document_layout.h"

class Project;
class IHighlighter;

class TextDocument : public QTextDocument, public IDocument {
    Q_OBJECT

    IHighlighter * highlighter;
protected:
    void openFile();
    bool identificateLexer();
    bool registerStateChangedCallback(QObject * target, const char * slot);
public:
    TextDocumentLayout * layout;

    TextDocument(File * file);

    ~TextDocument();

    inline bool canHasFoldings() { return _lexer != nullptr; }
    inline bool canHasBreakpoints() { return _lexer != nullptr; }

    const QLatin1String & tabSpace() { return tab_space; }

    const QString & documentUid();
    const QString docName();

//    void readNextBlock();

    void lexicate(const QString & text, IHighlighter * highlighter);

    bool isChanged() const { return isModified(); }
    bool isCompleterInitiable(const LEXEM_TYPE & lex, const bool & at_end);
    bool isCompleterContinuable(const LEXEM_TYPE & lex, const bool & at_end);
    bool isCompleterReplaceable(const LEXEM_TYPE & lex, const bool & at_start);

    void paraOpositionStr(const PARA_TYPE & para, QString & res);

    LEXEM_TYPE getWordBoundaries(EDITOR_POS_TYPE & start, EDITOR_POS_TYPE & length, const QTextBlock & block, const EDITOR_POS_TYPE & pos, const bool & global_offset = true);
    ParaCell * getPara(const QTextBlock & block, const EDITOR_POS_TYPE & pos);

    bool save();
    bool dump(QVariant & data);
    bool restore(const QVariant & data);

    void highlight(QRegularExpression * reg_exp, const bool & scroll = true);

//    inline void setRevision(const int & new_revision) { _revision = new_revision; }
//    inline int revision() { return _revision; }

    void emitBreakpointAdded(const EDITOR_POS_TYPE & line_num);
    void emitBreakpointRemoved(const EDITOR_POS_TYPE & line_num);
    void emitBreakpointMoved(const EDITOR_POS_TYPE & old_line_num, const EDITOR_POS_TYPE & line_num);
    void setWordWrap(const bool & word_wrap);

signals:
    void highlightRequires(const QRegularExpression & reg_exp, const bool & scroll);
    void wordWrapChanged(const bool & word_wrap);
    void rowRedrawRequired(const EDITOR_POS_TYPE & pos);
    void blocksLayoutChange(const EDITOR_POS_TYPE & pos, const EDITOR_POS_TYPE & amount);
    void hasChanges(const QString & uid, const bool & has);
    void enterPressed();
    void wordHovered(const QPoint & point, const int & start, const int & end);
    void highlightingComplete();

    void breakpointAdded(const QString & path, const EDITOR_POS_TYPE & line_num);
    void breakpointMoved(const QString & path, const EDITOR_POS_TYPE & prev_line_num, const EDITOR_POS_TYPE & line_num);
    void breakpointRemoved(const QString & path, const EDITOR_POS_TYPE & line_num);

public slots:
    void activateBreakpoint(const EDITOR_POS_TYPE & line_num);
    void removeBreakpoint(const EDITOR_POS_TYPE & line_num);

protected slots:
    void hasUnsavedChanges(const bool & has = true);
    void changesInContent(int position, int removed_count, int added_count);
    void highlighterFinished();
};

#endif // TEXT_DOCUMENT
