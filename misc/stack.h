#ifndef STACK_H
#define STACK_H

#include <qglobal.h>

template <typename T>
class Stack {
    T * data;
    T * curr;

    uint size;
public:   
    Stack(const T & default_val, const uint & default_size = 8) : size(default_size == 0 ? 32 : default_size) {
        curr = data = new T[size + 1];
        *curr = default_val;
    }

    Stack(Stack<T> * st) {
        size = st -> size;
        data = new T[size + 1];

        memcpy(data, st -> data, (size + 1) * sizeof(T));

        curr = &data[st -> curr - st -> data];
    }

    ~Stack() {
        delete [] data;
//        delete curr;
    }

    inline bool atBegin() { return curr == data; }

    inline T * items() const { return curr; }

    inline T & touch() { return *curr; }

    inline T & touchSublevel() { return *(curr - 1); }

    inline bool drop() {
        if (atBegin())
            return false;

        --curr;
        return true;
    }

    inline bool pop(T & res) {
        if (atBegin())
            return false;

        res = *curr;
        --curr;

        return true;
    }

    inline void replace(const T & new_val) {
        (*curr) = new_val;
    }

    inline void push(const T & val1, const T & val2) {
        push(val1);
        push(val2);
    }

    inline const T & push(const T & val) {
        if ((uint)(curr - data) == size) {
            int curr_pos = size;

            T * old_data = data;
            size = (int)(size * (size < 20 ? 2 : 1.5));

            data = new T[size + 1];
            memcpy(data, old_data, (curr_pos + 1) * sizeof(T));

            curr = &data[curr_pos];
            delete [] old_data;
        }

        *(++curr) = val;
        return val;
    }
};

#endif // STACK_H
