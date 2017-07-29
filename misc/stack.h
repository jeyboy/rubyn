#ifndef STACK_H
#define STACK_H

template <typename T>
class Stack;

template <typename T>
class StackCell {
    StackCell * next;
    friend class Stack<T>;
public:
    inline StackCell(StackCell * next, const T & val) : next(next), obj(val) {}
    inline void deleteChildren() {
        if (next)
            next -> deleteChildren();

        delete this;
    }

    T obj;
};

template <typename T>
class Stack {
    StackCell<T> * root;
public:
    Stack(const T & init_val)
        : root(new StackCell<T>(0, init_val)) {}

    ~Stack() {
        if (root)
            root -> deleteChildren();
    }

    inline T touch() {
        return root -> obj;
    }

    inline StackCell<T> touchLevel() {
        return root;
    }

    inline bool drop() {
        if (root -> next) {
            StackCell<T> * cell = root;
            root = root ? root -> next : 0;
            delete cell;
            return true;
        }
        else return false;
    }

    inline bool pop(T & res) {
        if (root -> next) {
            StackCell<T> * cell = root;
            root = root -> next;
            res = cell -> obj;
            delete cell;
            return true;
        }
        else return false;
    }

    void replace(const T & new_val) {
        root -> obj = new_val;
    }

    T & push(const T & val) {
        new StackCell<T>(root, val);
        return val;
    }
};

#endif // STACK_H
