#ifndef BLOCK_USER_DATA_H
#define BLOCK_USER_DATA_H

#include <QTextBlockUserData>

class BlockUserData : public QTextBlockUserData {
    bool has_folding;
    bool has_break_point;
public:
    BlockUserData(bool has_folding, bool has_break_point) : has_folding(has_folding), has_break_point(has_break_point) {}
};

#endif // BLOCK_USER_DATA_H
