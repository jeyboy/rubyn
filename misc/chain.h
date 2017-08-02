#ifndef CHAIN_H
#define CHAIN_H

template <class T>
class Chain;

template <class T>
class ChainCell {
  ChainCell * next;
  T val;

  friend class Chain<T>;
public:
  ChainCell(const T & val) : next(0), val(val) {}
};

template <class T>
class Chain {
    ChainCell<T> * root;
    ChainCell<T> * last;
public:
    Chain() : root(0), last(0) {}

    void add(const T & val) {
        if (last)
            last = (last -> next = new ChainCell<T>(val));
        else
            root = last = new ChainCell<T>(val);
    }

    void remove(const T & val) {
        ChainCell<T> * iter = root;

        if (root && root -> val == val) {
            root = root -> next;
            delete iter;
            return;
        }

        while(iter) {
            if (iter -> next && iter -> next -> val == val) {
                ChainCell<T> * temp = iter;
                iter -> next = iter -> next -> next;
                delete temp;
            }
        }
    }
};


#endif // CHAIN_H
