#ifndef TEXT_DOCUMENT
#define TEXT_DOCUMENT

#include <qpointer.h>
#include <qdebug.h>

#include "idocument.h"
#include "parts/lexer/lexer.h"
#include "parts/lexer/scopes/scope.h"
#include "parts/editor_parts/highlighter.h"
#include "misc/para_list.h"

//#include "parts/langs/ruby/lexer_ruby.h"


#define READ_LIMIT (qint64)(512000) // ~512 kb

class Project;
class File;
class QTextDocument;

class TextDocument : public QObject, public IDocument {
    Q_OBJECT

    static QLatin1String tab_space;
protected:
    QPointer<QTextDocument> _doc;
    TokenList * _tokens;
    ParaList * _paras;
    Scope * _scope;
    Lexer * _lexer;
    File * _file;

signals:
    void enterPressed();
    void wordHovered(const QPoint & point, const int & start, const int & end);
public:
    TextDocument(File * file, Lexer * lexer = 0);

    inline ~TextDocument() {
        delete _doc;
        delete _lexer;
        delete _scope;
        delete _tokens;
        delete _paras;
    }

    QTextDocument * toQDoc() { return _doc; }

    void readNextBlock();

    void lexicate(const QString & text, Highlighter * highlighter) {
        if (_lexer)
            _lexer -> handle(text, highlighter, _scope, _tokens, _paras);
    }

    void calcFoldings() {
        ParaCell * iter = _paras -> iter();
        EDITOR_POS_TYPE curr_line = 0;

        QVector<ParaCell *> waiters;
        waiters.reserve(5);

        while(iter != _paras -> iter_end()) {
            switch(iter -> para_type) {
                case ParaInfo::pt_none: { break; }
                case ParaInfo::pt_max: { ++curr_line; break;}
                case ParaInfo::pt_max_end: {
                    if (!waiters.isEmpty()) {
                        qWarning() << "PARA OBJECTS VERIFICATION IS FAILED: " << waiters.count();
                        waiters.clear();
                    }

                    return;
                }
                default: {
                    iter -> line_num = curr_line;
                    qDebug() << ParaInfo::toString(iter -> para_type);

                    if (iter -> para_type & ParaInfo::pt_open) {
                        waiters << iter;
                    } else {
                        PARA_TYPE opposite_type = ParaInfo::oppositePara(iter -> para_type);

                        if (!waiters.isEmpty()) {
                            ParaCell * waiter = waiters.takeLast();

                            if (waiter -> para_type == opposite_type) {
                                waiter -> close = iter;
                            } else {
                                qWarning() << "PARA OBJECTS CLOSING IS FAILED: " << ParaInfo::toString(waiter -> para_type) << ParaInfo::toString(opposite_type);
                                // TODO: do something with wrong state
                            }
                        } else {
                            qWarning() << "PARA OBJECTS CLOSING WITHOUT OPEN: " << ParaInfo::toString(opposite_type);
                        }
                    }
                }
            };

            iter = iter -> next;
        }
    }
};

#endif // TEXT_DOCUMENT
