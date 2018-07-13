#ifndef LEXER_DUMPER_YAML_H
#define LEXER_DUMPER_YAML_H

#include <qstring.h>

class QIODevice;

class LexerDumperYaml {
public:
    LexerDumperYaml(QIODevice * device);
};

#endif // LEXER_DUMPER_YAML_H
