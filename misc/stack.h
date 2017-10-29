#ifndef STACK_H
#define STACK_H

#include <qglobal.h>
#include <qhash.h>

#define CURR_INDEX (uint)(curr - data)

template <typename T>
class Stack {
    T * data;
    T * curr;

    uint size;

    QHash<uint, QByteArray> * level_data;
public:   
    Stack(const T & default_val, const uint & default_size = 16) : size(default_size == 0 ? 32 : default_size), level_data(new QHash<uint, QByteArray>()) {
        curr = data = new T[size + 1];
        *curr = default_val;
    }

    Stack(Stack<T> * st) {
        size = st -> size;
        data = new T[size + 1];

        memcpy(data, st -> data, (size + 1) * sizeof(T));

        curr = &data[st -> curr - st -> data];
        level_data = new QHash<uint, QByteArray>(*st -> level_data);
    }

    ~Stack() {
        delete [] data;
//        delete curr;
        delete level_data;
    }

    inline void setDataForTop(const QByteArray & item_data) { level_data -> insert(CURR_INDEX, item_data); }
    inline QByteArray dataForTop() { return level_data -> operator [](CURR_INDEX); }

    inline bool atBegin() { return curr == data; }

    inline T * items() const { return data; }

    inline T & touch() { return *curr; }

    inline T & touch(const int & level) { return *(curr - level); }

    inline T & touchSublevel() { return *(curr - 1); }

    inline bool drop() {
        if (atBegin())
            return false;

        level_data -> remove(CURR_INDEX);
        --curr;
        return true;
    }

    inline bool pop(T & res) {
        if (atBegin())
            return false;

        res = *curr;
        level_data -> remove(CURR_INDEX);
        --curr;

        return true;
    }

    inline void replace(const T & new_val) {
        level_data -> remove(CURR_INDEX);
        (*curr) = new_val;
    }

    inline void push(const T & val1, const T & val2) {
        push(val1);
        push(val2);
    }

    inline const T & push(const T & val) {
        if (CURR_INDEX == size) {
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

    inline const T & push(const T & val, const QByteArray & item_data) {
        push(val);
        setDataForTop(item_data);
        return val;
    }

    inline const T & pushToLevel(const int & level, const T & val, const QByteArray & item_data) {
        push(*curr, dataForTop());

        uint index = CURR_INDEX;

        for(int i = 1; i < level; i++) {
            *(curr - i) = *(curr - i - 1);
            level_data -> insert(index - i, level_data ->operator [](index - i - 1));
        }

        *(curr - level) = val;
        level_data -> insert(index - level, item_data);

        return val;
    }
};

#endif // STACK_H
