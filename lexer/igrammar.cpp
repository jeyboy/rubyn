#include "igrammar.h"

IGrammar::~IGrammar() {}

StateLexem IGrammar::translate(const StateLexem & state, const StateLexem & input) {
    if (rules[state][input] == lex_error) {
        int y = 0;
    }

    return rules[state][input];
}
