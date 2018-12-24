#ifndef TREE_DOCUMENT
#define TREE_DOCUMENT

#include <qabstractitemmodel.h>

#include "misc/defines.h"
#include "editor/idocument.h"

class Project;
class File;
//class IHighlighter;

class TreeDocument : public QAbstractItemModel, public IDocument {
    Q_OBJECT

//    IHighlighter * highlighter;
protected:
    File * _file;

//    bool identificateLexer();
    bool registerStateChangedCallback(QObject * target, const char * slot);
signals:
    void hasChanges(const QString & uid, const bool & has);
//    void wordHovered(const QPoint & point, const int & start, const int & end);
//    void highlightingComplete();
public:
    TreeDocument(File * file);

    ~TreeDocument();

//    const QLatin1String & tabSpace() { return tab_space; }

    const QString & documentUid();

////    void readNextBlock();

//    void lexicate(const QString & text, IHighlighter * highlighter);

//    bool isChanged() const { return isModified(); }
//    bool isCompleterInitiable(const LEXEM_TYPE & lex, const bool & at_end);
//    bool isCompleterContinuable(const LEXEM_TYPE & lex, const bool & at_end);
//    bool isCompleterReplaceable(const LEXEM_TYPE & lex, const bool & at_start);

//    void paraOpositionStr(const PARA_TYPE & para, QString & res);

//    LEXEM_TYPE getWordBoundaries(EDITOR_POS_TYPE & start, EDITOR_POS_TYPE & length, const QTextBlock & block, const EDITOR_POS_TYPE & pos, const bool & global_offset = true);
//    ParaCell * getPara(const QTextBlock & block, const EDITOR_POS_TYPE & pos);

    bool save();
    bool dump(QVariant & data);
    bool restore(const QVariant & data);

////    inline void setRevision(const int & new_revision) { _revision = new_revision; }
////    inline int revision() { return _revision; }

    inline void setVerticalScrollPos(const int & pos) { scroll_pos_y = pos; }
    inline int verticalScrollPos(const bool & drop = true) {
        int res = scroll_pos_y;
        if (drop)
            scroll_pos_y = 0;
        return res;
    }
//protected slots:
//    void hasUnsavedChanges(const bool & has = true);
//    void changesInContent(int position, int removed_count, int added_count);
//    void highlighterFinished();
};

#endif // TREE_DOCUMENT
