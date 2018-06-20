#include "html_set.h"

#include "html_tag.h"
#include "html_selector.h"

using namespace Html;

QByteArray Set::link() { return (isEmpty()) ? QByteArray() : first() -> link(); }
QByteArray Set::text() { return (isEmpty()) ? QByteArray() : first() -> text(); }
QByteArray Set::value(const QByteArray & name) { return (isEmpty()) ? QByteArray() : first() -> value(name); }

Set Set::find(const char * predicate, const bool & find_first) const {
    Selector selector(predicate);
    return find(&selector, find_first);
}

Set & Set::find(const Selector * selector, Set & set, const bool & find_first) const {
    if (selector -> has_error) return set;

    for(Set::ConstIterator tag = cbegin(); tag != cend(); tag++) {
        bool has_children = (*tag) -> hasChildren();
        bool has_next_selector = selector -> next != 0;
        bool is_forward_selector = has_next_selector && selector -> next -> isForward();

        if (!has_children && has_next_selector && is_forward_selector) continue; // ignore leafs if selector has next segment
        if ((*tag) -> isText() && selector -> _token_id != Tag::tg_text) continue; // ignore text block if it not required directly in selector

        if ((*tag) -> validTo(selector)) {
                if (has_next_selector) {
                    Tag * proc_tag = 0;

                    switch(selector -> next -> turn) {
                        case Selector::any:
                        case Selector::parent: { (*tag) -> children().find(selector -> next, set, find_first); break;}

                        case Selector::sibling: {
                            (*tag) -> parent() -> children().find(selector -> next, set, find_first);
                        break;}

                        case Selector::sibling_next: {
                            if (tag + 1 == cend()) continue;
                            proc_tag = *(tag + 1);
                        }
                        case Selector::sibling_prev: {
                            if (!proc_tag) {
                                if (tag == cbegin()) continue;
                                proc_tag = *(tag - 1);
                            }
                            (Set() << proc_tag).find(selector -> next, set, find_first);
                        break;}

                        case Selector::parent_prev: {
                            Tag * parent_tag = (*tag) -> parent() -> parent();
                            if (!parent_tag) continue;
                            parent_tag -> children().find(selector -> next, set, find_first);
                        break;}
                    }
                }
                else {
                    set.append(*tag);
                    if (find_first) break;
                }
        }
        else if (!selector -> isDirect() && has_children)
            (*tag) -> children().find(selector, set);

        if (find_first && !set.isEmpty()) break;
    }

    return set;
}

//QHash<QString, QString> & Set::findLinks(const Selector * selector, QHash<QString, QString> & links) const {
//    for(Set::Iterator tag = begin(); tag != end(); tag++) {
//        if ((*tag) -> validTo(selector)) {
//            if (selector -> next) {
//                if (selector -> next -> isBackward())
//                    (*tag) -> backwardFindLinks(selector -> next, links);
//                else if (!(*tag) -> children().isEmpty())
//                    (*tag) -> children().findLinks(selector -> next, links);
//            } else if ((*tag) -> is_link())
//                links.insert((*tag) -> link(), (*tag) -> text());
//        }
//        else if (!selector -> isDirect() && !(*tag) -> children().isEmpty())
//            (*tag) -> children().findLinks(selector, links);
//    }

//    return links;
//}
