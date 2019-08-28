#ifndef YAML_LEXER_FRONTEND_H
#define YAML_LEXER_FRONTEND_H

#include <qstring.h>

class QIODevice;

class LexerFrontendYaml {
public:
    LexerFrontendYaml(QIODevice * device);
};

#endif // YAML_LEXER_FRONTEND_H
