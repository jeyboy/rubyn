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


    int size;
public:
    Stack(const int & default_size = 64) : size(default_size) {
        data = new T[default_size + 1];
        curr = start = data;
        end = &data[default_size];
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

            size = (int)(size * 1.5);
            start = data = (T*)realloc(data, size + 1);
            end = &data[size];
            curr = &data[curr_pos];
        }

        *(++curr) = val;
        return val;
    }
};

#endif // STACK_H
