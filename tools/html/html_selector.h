#ifndef HTML_SELECTOR_H
#define HTML_SELECTOR_H

#include "html_global.h"

#include <qpair.h>
#include <qlist.h>
#include <qhash.h>

#define TOKEN_BUFF QByteArray(stoken, (etoken ? etoken : pdata) - stoken)
#define TBUFF_VALID ((pdata - stoken) > 0)
#define TOKEN_BUFF_VALID (stoken && TBUFF_VALID)
#define VAL_BUFF (sval == 0 ? QByteArray() : QByteArray(sval, pdata - sval))

#define SELECTOR_ADD_ATTR(token_data) \
    {\
        if (TOKEN_BUFF_VALID) { \
            selector -> addAttr(TOKEN_BUFF, VAL_BUFF, *rel);\
            etoken = 0; sval = 0; rel = 0; \
        }\
        stoken = token_data;\
    }

#define SELECTOR_ADD_PREDICATE(token_data) \
    {\
        if (TOKEN_BUFF_VALID) {\
            if (!selector -> addPredicate(state, TOKEN_BUFF))\
                SELECTOR_PARSE_ERROR("wrong predicate state: " + char(state));\
            rel = 0; \
        }\
        stoken = token_data;\
    }

#define SELECTOR_PARSE_ERROR(message) \
    {\
        Selector * curr = this; \
        while(curr -> prev) \
            curr = curr ->  prev; \
        curr -> has_error = true;\
        curr -> error = new QString(message);\
        qDebug() << "SELECTOR ERROR: " << message;\
        return;\
    }

#define SELECTOR_PROCEED_CLASSES(rel, classes_token) \
    { \
        const char * data = classes_token.constData(), * sdata = data; \
        while(*data) { \
            switch(*data) { \
                case 32: { \
                    if (data - sdata > 0) \
                        _classes << QPair<char, QByteArray>(rel, QByteArray(sdata, data - sdata)); \
                    sdata = data + 1; \
                break;} \
                default:; \
            } \
            data++; \
        }\
        if (data - sdata > 0)\
            _classes << QPair<char, QByteArray>(rel, QByteArray(sdata, data - sdata));\
    }


namespace Html {
    struct Selector {
        enum SToken {
            sel_id_token = 35, // #
            sel_class_token = 46, // .

            sel_attr_token = 91, // [
            sel_attr_separator = 44, // ,
            sel_attr_token_end = 93, // ]
            sel_attr_eq = 61, // =
            sel_attr_begin = 94, // ^
            sel_attr_begin2 = 124, // |
            sel_attr_end = 36, // $
            sel_attr_not = 33, // !
            sel_attr_match2 = 42, // *
            sel_attr_type_token = 58, // :

            sel_rel_attr_match = 126, // ~ // ul ~ table // All <table> elements that are siblings of a <ul> element.
            sel_rel_any = 32,
            sel_rel_parent = 62, // > // div > p // All <p> elements where the parent is a <div> element.
            sel_rel_prev_parent = 60, // <
            sel_rel_next_sibling = 43, // + // ul + h3 // The <h3> element that are next to each <ul> elements.
            sel_rel_prev_sibling = 45, // -

            sel_cont1_token = 34, // "
            sel_cont2_token = 39 // '
        };
        enum STurn { any = sel_rel_any, parent = sel_rel_parent, sibling = sel_rel_attr_match, parent_prev = sel_rel_prev_parent, sibling_next = sel_rel_next_sibling, sibling_prev = sel_rel_prev_sibling };
        enum SState { st_none = sel_attr_end, st_tag, st_limit, st_attr, st_attr_value, st_id = sel_id_token, st_class = sel_class_token, st_attr_type = sel_attr_type_token, st_in_name, st_in_val };

        const static QHash<QByteArray, QByteArray> attr_predifinitions;

        Selector(const char * predicate);

        Selector(const STurn & turn = any, Selector * prev = 0);
        inline ~Selector() {
            delete next;
            delete error;
        }
        Selector operator= (const char * x) { return Selector(x); }

        bool addPredicate(const SState & state, const QByteArray & token);
        void addAttr(const QByteArray & name, const QByteArray & val, const char & rel);

        inline bool isDirect() const { return turn == parent; }
        inline bool isForward() const { return turn == any || turn == parent; }

        QList<QPair<char, QByteArray> > _classes;
        int _token_id;
        QHash<QByteArray, QPair<char, QByteArray> > _attrs;
        STurn turn;
        int pos_limit;

        Selector * prev;
        Selector * next;
        bool has_error;
        QString * error;
    };
}

#endif // HTML_SELECTOR_H
