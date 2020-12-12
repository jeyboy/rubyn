#include "yaml_grammar.h"

using namespace Yaml;

Grammar::Grammar() {}


void Grammar::initParas() {}

void Grammar::initFlags(StackLexemFlag & flags, const LEXEM_TYPE & lex, const LEXEM_TYPE & last_non_blank_lex) {}

bool Grammar::stackDropable(const LEXEM_TYPE & state, const LEXEM_TYPE & input) {}

char Grammar::percentagePresentationBlocker(const char & ch) {}

Identifier Grammar::toHighlightable(const LEXEM_TYPE & lexem) {}

LEXEM_TYPE Grammar::translate(const LEXEM_TYPE & state, const LEXEM_TYPE & input) {

}
