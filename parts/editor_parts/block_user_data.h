#ifndef BLOCK_USER_DATA_H
#define BLOCK_USER_DATA_H

#include <QTextBlockUserData>
//#include "parts/lexer/lexer_state.h"

class LexerState;

struct BlockUserData : public QTextBlockUserData {
    bool has_folding;
    bool has_break_point;
    LexerState * state;
public:
    BlockUserData(bool has_break_point = false, bool has_folding = false, LexerState * state = 0)
        : has_folding(has_folding), has_break_point(has_break_point), state(state) {}
};

#endif // BLOCK_USER_DATA_H
