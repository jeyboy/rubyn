#ifndef PARA_LIST_H
#define PARA_LIST_H

#include <qhash.h>

#include "para_type.h"

struct ParaCell {
    ParaCell * prev;
    ParaCell * next;

    ParaCell * close;

    ParaType para_type;
    EDITOR_POS_TYPE line_num;
    EDITOR_POS_TYPE pos;
    EDITOR_LEN_TYPE length;

    char offset;
    bool is_blockator;

    ParaCell(const ParaType & para, const EDITOR_POS_TYPE & start_pos, ParaCell * prev_token = nullptr)
        : prev(nullptr), next(nullptr), close(nullptr), para_type(para), line_num(-1), pos(start_pos),
          length(1), offset(0), is_blockator(false)
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

    bool isValid() { return close && linesCoverage() > 0; }

    EDITOR_POS_TYPE linesCoverage() {
        if (!close) {
            qDebug() << "MISSED CLOSE";
            return 0;
        }

        return (close -> line_num - line_num) + offset;
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
        root = new ParaCell(pt_none, 0);
        last = new ParaCell(pt_max_end, 0, root);
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
