#include "yaml_predefined.h"

using namespace Yaml;

//https://yaml.org/spec/1.2/spec.html

Predefined::Predefined() {   
//    keys.insert(QByteArrayLiteral("#{"), lex_interpolation);
}


bool Predefined::hasKey(const QByteArray & key) { return keys.contains(key); }
Yaml::StateLexem Predefined::lexem(const QByteArray & key) {
    return keys.value(key, lex_undefined);
}
