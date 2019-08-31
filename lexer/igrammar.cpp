#include "igrammar.h"

IGrammar::~IGrammar() {}

bool IGrammar::stackDropable(const IState::Lexem & /*state*/, const IState::Lexem & /*input*/) { return true; }
