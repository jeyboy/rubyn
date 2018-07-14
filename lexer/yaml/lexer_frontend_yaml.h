#ifndef LEXER_DUMPER_YAML_H
#define LEXER_DUMPER_YAML_H

#include <qstring.h>

class QIODevice;

class LexerFrontendYaml {
public:
    LexerFrontendYaml(QIODevice * device);
};

#endif // LEXER_DUMPER_YAML_H
