#include "igrammar.h"

IGrammar::~IGrammar() {}

StateLexem IGrammar::translate(const StateLexem & state, const StateLexem & input) {
    return rules[state][input];
}
