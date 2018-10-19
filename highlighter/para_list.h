#ifndef PARA_LIST_H
#define PARA_LIST_H

#include "para_type.h"

struct ParaCell {
    ParaCell * prev;
    ParaCell * next;
    ParaCell * close;

    ParaType para_type;
    EDITOR_POS_TYPE pos;

    bool is_blockator;
    bool is_opener;
    bool is_foldable;
    bool is_oneliner;

    ParaCell(const ParaType & para, const EDITOR_POS_TYPE & start_pos, ParaCell * prev_token = nullptr)
        : prev(nullptr), next(nullptr), close(nullptr), para_type(para), pos(start_pos),
          is_blockator(true), is_opener(true), is_foldable(false), is_oneliner(false)
    {
        if ((prev = prev_token)) {
            if ((next = prev -> next))
                next -> prev = this;

            prev -> next = this;
        }
    }

    ~ParaCell() {
        if (prev)
            prev -> next = next;

        if (next)
            next -> prev = prev;

        if (close)
            close -> close = nullptr;
    }

    EDITOR_POS_TYPE linesCoverage() {
        if (!close) {
            qDebug() << "MISSED CLOSE";
            return 0;
        }

        EDITOR_POS_TYPE coverage = 0;
        ParaCell * it = this;

        if (is_opener) {
            while(it && it != close) {
                if (it -> para_type == pt_max)
                    coverage++;

                it = it -> next;
            }

            if (!is_blockator && coverage != 0)
                --coverage;
        } else {
            while(it && it != close) {
                if (it -> para_type == pt_none)
                    coverage--;

                it = it -> prev;
            }

            if (!close -> is_blockator && coverage != 0)
                ++coverage;
        }

        return coverage;
    }

//    T & operator++() // ++A
//    {
//        // Do increment of "this" value
//        return *this ;
//    }

//    T operator++(int) // A++
//    {
//       T temp = *this ;
//       // Do increment of "this" value
//       return temp ;
//    }
};

class ParaList {
    ParaCell * root, * last;
public:
    inline ParaList() : root(nullptr), last(nullptr) {
        root = new ParaCell(pt_none, -1);
        last = new ParaCell(pt_max_end, -1, root);
    }

    inline ~ParaList() {
        clear();

        delete root;
        delete last;
    }

    inline void clear() {
        ParaCell * curr;

        while(last -> prev != root) {
            curr = last;
            last = last -> prev;
            delete curr;
        }
    }

    ParaCell * iter() { return root -> next; }
    ParaCell * iter_end() { return last; }

    void registerLine(ParaCell *& left, ParaCell *& right, ParaCell * prev_end = nullptr) {
        if (!prev_end)
            prev_end = last -> prev;

        left = new ParaCell(pt_none, 0, prev_end);
        right = new ParaCell(pt_max, 0, left);

        left -> close = right;
        right -> close = left;
    }

    static void removeLine(ParaCell * left, ParaCell * right) {
        while(left && left != right) {
            ParaCell * curr = left;
            left = left -> next;

            delete curr;
        }

        delete right;
    }

    ParaCell * append(const ParaType & para, const EDITOR_POS_TYPE & start_pos) {
        return new ParaCell(para, start_pos, last -> prev);
    }

    static ParaCell * insert(ParaCell * left, const ParaType & para, const EDITOR_POS_TYPE & start_pos) {
        return new ParaCell(para, start_pos, left);
    }
};

#endif // PARA_LIST_H
