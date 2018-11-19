#include "igrammar.h"

IGrammar::~IGrammar() {}

bool IGrammar::stackDropable(const StateLexem & /*state*/, const StateLexem & /*input*/) { return true; }
