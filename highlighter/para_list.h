#ifndef PARA_LIST_H
#define PARA_LIST_H

#include <qhash.h>
#include <qdebug.h>

#include "para_info.h"

struct ParaCell {
    ParaCell * prev;
    ParaCell * next;

    ParaCell * close;

    PARA_TYPE para_type;
    EDITOR_POS_TYPE line_num;
    EDITOR_POS_TYPE pos;

    ParaCell(const PARA_TYPE & para, const EDITOR_POS_TYPE & start_pos, ParaCell * prev_token = 0)
        : prev(0), next(0), close(0), para_type(para), line_num(-1), pos(start_pos)
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
    }

    EDITOR_POS_TYPE linesCoverage() {
        if (!close) {
            qDebug() << "MISSED CLOSE";
            return 0;
        }

        return close -> line_num - line_num;
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
    inline ParaList() : root(0), last(0) {
        root = new ParaCell(ParaInfo::pt_none, 0);
        last = new ParaCell(ParaInfo::pt_max_end, 0, root);
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

    void registerLine(ParaCell *& left, ParaCell *& right, ParaCell * prev_end = 0) {
        if (!prev_end)
            prev_end = last -> prev;

        left = new ParaCell(ParaInfo::pt_none, 0, prev_end);
        right = new ParaCell(ParaInfo::pt_max, 0, left);
    }

    static void removeLine(ParaCell * left, ParaCell * right) {
        while(left && left != right) {
            ParaCell * curr = left;
            left = left -> next;

            delete curr;
        }

        delete right;
    }

    ParaCell * append(const PARA_TYPE & para, const EDITOR_POS_TYPE & start_pos) {
        return new ParaCell(para, start_pos, last -> prev);
    }

    static ParaCell * insert(ParaCell * left, const PARA_TYPE & para, const EDITOR_POS_TYPE & start_pos) {
        return new ParaCell(para, start_pos, left);
    }
};

#endif // PARA_LIST_H