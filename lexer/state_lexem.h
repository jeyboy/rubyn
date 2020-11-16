#ifndef STATE_LEXEM_H
#define STATE_LEXEM_H

#pragma once

//#define LEX(val, flag) (Lexem)(val | flag)
//#define EXCLUDE_BIT(val, flag) (Lexem)(val & ~flag)

 // = (1ULL << 1),

#include "misc/defines.h"

enum StateLexem : LEXEM_TYPE {
    DefaultStateLexems
};

#endif // STATE_LEXEM_H
