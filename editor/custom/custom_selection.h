#ifndef CUSTOM_SELECTION_H
#define CUSTOM_SELECTION_H

namespace Custom {
    class IBlock;

    struct Selection {
        int _start_screen_point;
        int _end_screen_point;

        int _start_pos;
        int _end_pos;

        IBlock * _start;
        IBlock * _end;

        Selection();

        void preinit(IBlock * start, int start_pos);
        inline void clear() { preinit(nullptr, -1); }

        inline bool initStartRequires() { return _start_screen_point == -1; }
        bool isValid();
    };
}

#endif // CUSTOM_SELECTION_H
