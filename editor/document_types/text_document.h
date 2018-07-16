#ifndef TEXT_DOCUMENT
#define TEXT_DOCUMENT

#include <qpointer.h>
#include <qtextdocument.h>

#include "project/code_formats.h"
#include "editor/idocument.h"

#define READ_LIMIT (qint64)(512000) // ~512 kb

class Project;
class File;
class ILexer;
class Highlighter;

class TextDocument : public QObject, public IDocument {
    Q_OBJECT

    static QLatin1String tab_space;

    int pos, removed, added;
protected:
    QPointer<QTextDocument> _doc;

    ILexer * _lexer;

    File * _file;

    bool identificateLexer();
signals:
    void enterPressed();
    void wordHovered(const QPoint & point, const int & start, const int & end);
public:
    TextDocument(File * file);

    ~TextDocument();

    QTextDocument * toQDoc() { return _doc; }

    void readNextBlock();

    void lexicate(const QString & text, Highlighter * highlighter);

    void calcFoldings();
protected slots:
    void changesInContent(int position, int removed_count, int added_count);
};

#endif // TEXT_DOCUMENT
