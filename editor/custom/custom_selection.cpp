#include "custom_selection.h"
#include "custom_iblock.h"

using namespace Custom;

Selection::Selection() : _start_screen_point(-1), _end_screen_point(-1), _start_pos(-1), _end_pos(-1), _start(nullptr), _end(nullptr) {

}

void Selection::preinit(IBlock * start, int start_pos) {
    _start = start;
    _start_pos = start_pos;

    _start_screen_point = -1;
    _end_screen_point = -1;
    _end_pos = -1;
    _end = nullptr;
}

bool Selection::isValid() {
    return _start && _start != _end;
}
