#ifndef STACK_H
#define STACK_H

#include <qglobal.h>

template <typename T>
class Stack {
    T * data;
    T * curr, * start, * end;

    uint size;
public:
    Stack(const T default_val, const uint & default_size = 8) : size(default_size == 0 ? 32 : default_size) {
        data = new T[size + 1];
        curr = start = data;
        *start = default_val;
        end = &data[size];
    }

    ~Stack() {
        delete [] data;
    }

    inline T & touch() {
        return *curr;
    }

    inline bool drop() {
        if (curr == start)
            return false;

        --curr;
        return true;
    }

    inline bool pop(T & res) {
        if (curr != start) {
            res = *curr;
            --curr;
        }

        return false;
    }

    void replace(const T & new_val) {
        (*curr) = new_val;
    }

    const T & push(const T & val) {
        if (curr == end) {
            int curr_pos = size;

            T * old_data = data;
            size = (int)(size * (size < 20 ? 2 : 1.5));

            start = data = new T[size + 1];
            memcpy(data, old_data, (curr_pos + 1) * sizeof(T));

            end = &data[size];
            curr = &data[curr_pos];
            delete [] old_data;
        }

        *(++curr) = val;
        return val;
    }
};

#endif // STACK_H
