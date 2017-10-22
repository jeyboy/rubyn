#ifndef TEXT_DOCUMENT
#define TEXT_DOCUMENT

#include <qtextcursor>
#include <qtextdocument.h>
#include <QPlainTextDocumentLayout>
#include <qdebug.h>

#include "idocument.h"
#include "parts/lexer/lexer.h"
#include "parts/lexer/scopes/scope.h"
#include "parts/editor_parts/highlighter.h"

//#include "parts/langs/ruby/lexer_ruby.h"


#define READ_LIMIT (qint64)(512000) // ~512 kb

class Project;
class File;

class TextDocument : public QTextDocument, public IDocument {
protected:
    TokenList * _tokens;
    Scope * _scope;
    Lexer * _lexer;
    File * _file;
public:
    TextDocument(File * file, Lexer * lexer = 0);

    inline ~TextDocument() {
        delete _lexer;
        delete _scope;
        delete _tokens;
    }

    void readNextBlock();

    void lexicate(const QString & text, Highlighter * highlighter) {
        if (_lexer)
            _lexer -> handle(text, highlighter, _scope, _tokens);
    }
};

#endif // TEXT_DOCUMENT
