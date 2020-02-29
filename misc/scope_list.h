#ifndef SCOPE_LIST_H
#define SCOPE_LIST_H

#include "lexer/scope_type.h"

struct ScopeCell {
    ScopeCell * prev;
    ScopeCell * next;

    ScopeCell * closer;

    SCOPE_TYPE para_type;
    EDITOR_POS_TYPE pos;
    quint8 length;

    bool is_opener;

    ScopeCell(const SCOPE_TYPE & para, const EDITOR_POS_TYPE & start_pos, const quint8 & length = 0, ScopeCell * prev_token = nullptr)
        : prev(prev_token), next(nullptr), closer(nullptr), para_type(para), pos(start_pos), length(length), is_opener(true)
    {
        if (prev) {
            if ((next = prev -> next))
                next -> prev = this;

            prev -> next = this;
        }
    }

    ~ScopeCell() {
        if (prev)
            prev -> next = next;

        if (next)
            next -> prev = prev;

        if (closer) // remove link with chained elem
            closer -> closer = nullptr;
    }
};

class ScopeList {
    ScopeCell * root, * last;
public:
    inline ScopeList() : root(nullptr), last(nullptr) {
        root = new ScopeCell(sc_none, -1);
        last = new ScopeCell(sc_max, -1, 0, root);
    }

    inline ~ScopeList() {
        clear();

        delete root;
        delete last;
    }

    inline ScopeCell * rootToken() { return root; }

    inline void clear() {
        ScopeCell * curr;
        ScopeCell * it = last -> prev;

        while(it != root) {
            curr = it;
            it = it -> prev;
            delete curr;
        }

        if (root -> next != last) {
            last -> prev = root;
            root -> next = last;
        }
    }

    ScopeCell * iter() { return root -> next; }
    ScopeCell * iter_end() { return last; }

    void registerLine(ScopeCell *& left, ScopeCell *& right, ScopeCell * prev_end = nullptr) {
        if (!prev_end)
            prev_end = root; //last -> prev;

        left = new ScopeCell(sc_none, -1, 0, prev_end);
        right = new ScopeCell(sc_max, -1, 0, left);

        right -> is_opener = false;
    }

    static void removeLine(ScopeCell * left, ScopeCell * right) {
        while(left && left != right) {
            ScopeCell * curr = left;
            left = left -> next;

//            //TODO: need to check: speed up this removing of sequence or not
//            curr -> next = nullptr;
//            curr -> prev = nullptr;
//            ////////////

            delete curr;
        }

        delete right;
    }

    ScopeCell * append(const SCOPE_TYPE & para, const EDITOR_POS_TYPE & start_pos, const quint8 & length = 0) {
        return new ScopeCell(para, start_pos, length, last -> prev);
    }

    static ScopeCell * insert(ScopeCell * left, const SCOPE_TYPE & para, const EDITOR_POS_TYPE & start_pos, const quint8 & length = 0) {
        return new ScopeCell(para, start_pos, length, left);
    }
};

#endif // SCOPE_LIST_H
