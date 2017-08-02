#ifndef FILE_POINT_H
#define FILE_POINT_H

#include "scope_item_types.h"
#include "parts/lexer/lexems.h"
#include "file_point.h"
#include "scope_item_types.h"

class File;

#define DEF_LINE -1
#define DEF_LINE_END -2

struct VarPoint {
    ScopeItemType stype;
    int line_start;
    int left;

    VarPoint(const ScopeItemType & stype, const int & line_start, const int & left)
        : stype(stype), line_start(line_start), left(left) {}
};

template <class T>
class VarPointChain;

template <class T>
class ChainCell {
  ChainCell * next;
  T val;

  friend class VarPointChain<T>;
public:
  ChainCell(const T & val) : next(0), val(val) {}
};

template <class T>
class VarPointChain {
    ChainCell<T> * root;
    ChainCell<T> * last;
public:
    VarPointChain() : root(0), last(0) {}

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

struct FilePoint : public VarPoint {
    File * file;
    int line_end;

    FilePoint(const ScopeItemType & stype, File * file, const int & line_start, const int & left, const int & line_end = DEF_LINE_END)
        : VarPoint(stype, line_start, left), file(file), line_end(line_end) {}
};

#endif // FILE_POINT_H
