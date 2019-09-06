#include "igrammar.h"

IGrammar::~IGrammar() {}

bool IGrammar::stackDropable(const LEXEM_TYPE & /*state*/, const LEXEM_TYPE & /*input*/) { return true; }
