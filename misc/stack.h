#ifndef STACK_H
#define STACK_H

#include <QtGlobal>

//template <typename T>
//class Stack;

//template <typename T>
//class StackCell {
//    StackCell * next;
//    friend class Stack<T>;
//public:
//    inline StackCell(StackCell * next, const T & val) : next(next), obj(val) {}
//    inline void deleteChildren() {
//        if (next)
//            next -> deleteChildren();

//        delete this;
//    }

//    T obj;
//};

//template <typename T>
//class Stack {
//    StackCell<T> * root;
//public:
//    Stack(const T & init_val)
//        : root(new StackCell<T>(0, init_val)) {}

//    ~Stack() {
//        if (root)
//            root -> deleteChildren();
//    }

//    inline T & touch() {
//        return root -> obj;
//    }

//    inline StackCell<T> * touchLevel() {
//        return root;
//    }

//    inline bool drop() {
//        if (root -> next) {
//            StackCell<T> * cell = root;
//            root = root ? root -> next : 0;
//            delete cell;
//            return true;
//        }
//        else return false;
//    }

//    inline bool pop(T & res) {
//        if (root -> next) {
//            StackCell<T> * cell = root;
//            root = root -> next;
//            res = cell -> obj;
//            delete cell;
//            return true;
//        }
//        else return false;
//    }

//    void replace(const T & new_val) {
//        root -> obj = new_val;
//    }

//    const T & push(const T & val) {
//        root = new StackCell<T>(root, val);
//        return val;
//    }
//};


template <typename T>
class Stack {
    T * data;
    T * start, * end;
    T * curr;

    uint size;
public:
    Stack(const T default_val, const uint & default_size = 2) : size(default_size == 0 ? 64 : default_size) {
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
