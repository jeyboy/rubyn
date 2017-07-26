#ifndef LEXER_H
#define LEXER_H

#include <qstring.h>
#include <qdatetime.h>

#include "scopes/scope_node.h"

class Lexer {
public:
    void analize(const QString & text) {
        QByteArray text_val = text.toUtf8();
        analize(text_val);
    }

    void analize(const QByteArray & text) {
        ScopeNode * scope = new ScopeNode(0);

        quint64 date = QDateTime::currentMSecsSinceEpoch();
        const char * window = text.constData();

        while(window) {

            ++window;
        }

        qDebug() << QDateTime::currentMSecsSinceEpoch() - date;
    }
};

#endif // LEXER_H
