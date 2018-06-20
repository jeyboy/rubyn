#include "html_selector.h"
#include "html_tag.h"
#include <qdebug.h>

using namespace Html;

const QHash<QByteArray, QByteArray> Selector::attr_predifinitions = QHash<QByteArray, QByteArray>{
    {"text", HTML_ATTR_TYPE}, {"submit", HTML_ATTR_TYPE}, {"reset", HTML_ATTR_TYPE}, {"radio", HTML_ATTR_TYPE},
    {"password", HTML_ATTR_TYPE}, {"image", HTML_ATTR_TYPE}, {"hidden", HTML_ATTR_TYPE}, {"file", HTML_ATTR_TYPE},
    {"checkbox", HTML_ATTR_TYPE}, {"button", HTML_ATTR_TYPE}, {"week", HTML_ATTR_TYPE}, {"month", HTML_ATTR_TYPE},
    {"url", HTML_ATTR_TYPE}, {"time", HTML_ATTR_TYPE}, {"tel", HTML_ATTR_TYPE}, {"search", HTML_ATTR_TYPE},
    {"range", HTML_ATTR_TYPE}, {"number", HTML_ATTR_TYPE}, {"email", HTML_ATTR_TYPE}, {"datetime-local", HTML_ATTR_TYPE},
    {"datetime", HTML_ATTR_TYPE}, {"date", HTML_ATTR_TYPE}, {"color", HTML_ATTR_TYPE}
};

bool Selector::addPredicate(const SState & state, const QByteArray & token) {
    switch(state) {
        case st_tag: { _token_id = Tag::tagId(token.toLower(), false); break;}
        case st_id: { _attrs.insert(attr_id, QPair<char, QByteArray>(sel_attr_eq, token)); break; }
        case st_class: { SELECTOR_PROCEED_CLASSES(sel_attr_eq, token); break;}
        case st_attr_type: {
            bool ok;
            int level = token.toInt(&ok, 10);
            if (ok)
                pos_limit = level - 1; //INFO: convert to zero based index
            else {
                QByteArray lower_token = token.toLower();

                if (attr_predifinitions.contains(lower_token))
                    _attrs.insert(attr_predifinitions[lower_token], QPair<char, QByteArray>(sel_attr_eq, lower_token));
                else
                    _attrs.insert(lower_token, QPair<char, QByteArray>(sel_attr_eq, tkn_any_elem));
            }
        break;}
        default: return false;
    }

    return true;
}

void Selector::addAttr(const QByteArray & name, const QByteArray & val, const char & rel) {
    if (val.isEmpty()) {
        _attrs.insert(name.toLower(), QPair<char, QByteArray>(sel_attr_eq, tkn_any_elem));
    } else {
        QByteArray lower_name = name.toLower();

        if (lower_name == attr_class) {
            SELECTOR_PROCEED_CLASSES(rel, val);
        } else
            _attrs.insert(lower_name, QPair<char, QByteArray>(rel, val));
    }
}

Selector::Selector(const STurn & turn, Selector * prev)
    : _token_id(Tag::tg_any), turn(turn), pos_limit(-1), prev(prev), next(0), has_error(false), error(0)
{
    if (prev) prev -> next = this;
}

Selector::Selector(const char * predicate) : _token_id(Tag::tg_any), turn(any),
    pos_limit(-1), prev(0), next(0), has_error(false), error(0)
{
    SState state = st_tag;
    Selector * selector = this;
    const char * pdata = predicate, * stoken = pdata, * etoken = 0, * rel = 0, * sval = 0;
    bool in_attr = false;

    while(*pdata) {
        switch(state) {
            case st_in_name: {
                if (*stoken == *pdata && *(pdata - 1) != '\\') {
                    state = st_attr;
                    stoken++; etoken = pdata;
                }
            break;}
            case st_in_val: {
                if (*sval == *pdata && *(pdata - 1) != '\\') {
                    sval++;
                    SELECTOR_ADD_ATTR(0);
                    state = st_attr;
                }
            break;}

            default: {
                switch(*pdata) {
                    case sel_id_token:
                    case sel_class_token: {
                        SELECTOR_ADD_PREDICATE(pdata + 1)
                        state = (SState)*pdata;
                    break;}

                    case sel_attr_match2:{
                        if (!in_attr)
                            goto continue_mark;
                    }
                    case sel_attr_eq:
                    case sel_attr_begin:
                    case sel_attr_begin2:
                    case sel_attr_end:
                    case sel_attr_not: {
                    attr_rel_mark:
                        state = st_attr_value;
                        if (!etoken) // if name surrounded by quotes we should ignore this etoken
                            etoken = pdata;
                        rel = pdata;
                        sval = pdata + 1;
                    break;}


                    case sel_attr_token_end: {
                        in_attr = false;
                        SELECTOR_ADD_ATTR(pdata + 1);
                        state = st_tag;
                    break;}

                    case sel_attr_token: {
                        in_attr = true;
                        rel = 0;
                        SELECTOR_ADD_PREDICATE(pdata + 1)
                        state = st_attr;
                    break;}


                    case sel_attr_type_token: {
                        if (!in_attr) {
                            SELECTOR_ADD_PREDICATE(pdata + 1)
                            state = (SState)*pdata;
                        }
                    break;}

                    case sel_cont1_token:
                    case sel_cont2_token: {
                        if (!in_attr)
                            SELECTOR_PARSE_ERROR(LSTR("quotas is not possible outside of attrs"));

                        if (state == st_attr_value)
                            state = st_in_val;
                        else
                            state = st_in_name;

                    break;}

                    case sel_rel_any: {
                        if (*(pdata + 1) != sel_rel_any) { // ignore multiple spaces
                            if (in_attr) {
                                SELECTOR_ADD_ATTR(pdata + 1);
                                state = st_attr;
                            } else {
                                SELECTOR_ADD_PREDICATE(pdata + 1);

                                if (!rel) {
                                    selector = new Selector((STurn)*pdata, selector);
                                    rel = pdata;
                                }
                                state = st_tag;
                            }
                        }
                    break;}

                    case sel_rel_prev_sibling: {
                        if (state != st_tag || (state == st_tag && (*(pdata - 1) != sel_rel_any || *(pdata + 1) != sel_rel_any)))
                            goto continue_mark;
                    }

                    case sel_rel_attr_match: {
                        if (in_attr)
                            goto attr_rel_mark;
                    }

                    case sel_rel_prev_parent:
                    case sel_rel_next_sibling:
                    case sel_rel_parent: {
                        if (!in_attr) {
                            if (!rel)
                                selector = new Selector((STurn)*pdata, selector);
                            else if (*rel == sel_rel_any)
                                selector -> turn = (STurn)*pdata;
                            else
                                SELECTOR_PARSE_ERROR(LSTR("couple of relations inputed: ") % *pdata);

                            rel = pdata;
                            stoken = pdata + 1;
                            state = st_tag;
                        }
                        else SELECTOR_PARSE_ERROR(LSTR("incorrect relation in attributes: ") % *pdata);
                    break;}

                    case sel_attr_separator: {
//                        selector = new Selector(selector -> turn, selector -> prev);
//                        stoken = pdata + 1;
//                        state = st_tag;
                        SELECTOR_PARSE_ERROR(LSTR("incorrect relation: ") % *pdata);
                    break;}

                    default:;
                }
            }
        }

        continue_mark:
            pdata++;
    }

    SELECTOR_ADD_PREDICATE(0);
}
