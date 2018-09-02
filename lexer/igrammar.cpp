#include "igrammar.h"

IGrammar::~IGrammar() {}

StateLexem IGrammar::translate(const StateLexem & state, const StateLexem & input) {
    if (state == lex_none)
        return input;

    if (input == lex_none)
        return state;


    if (rules[state][input] == lex_error) {
        int y = 0;
    }

    return rules[state][input];
}

bool IGrammar::stackDropable(const StateLexem & /*state*/, const StateLexem & /*input*/) { return true; }
