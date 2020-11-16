#include "js_predefined.h"

#include <qdebug.h>

using namespace Js;

// http://largescalejs.ru/module-pattern/
// https://www.ecma-international.org/publications/standards/Ecma-262.htm
// https://www.ecma-international.org/ecma-262/10.0/index.html#sec-ecmascript-standard-built-in-objects


Predefined::Predefined() {
//    keys.insert(QByteArrayLiteral("alias"), lex_alias); // Creates an alias between two methods (and other things)
}


bool Predefined::hasKey(const QByteArray & key) { return keys.contains(key); }
StateLexem Predefined::lexem(const QByteArray & key) {
    return keys.value(key, lex_word);
}
