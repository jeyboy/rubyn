#include "ab_lexer.h"

//#include "parts/lexer/lexer.h"
//#include "parts/lexer/scopes/scope.h"
//#include "parts/editor_parts/highlighter.h"
//#include "misc/para_list.h"

ABLexer::ABLexer() : ILexer() {  // , _tokens(new TokenList()), _paras(new ParaList()), _scope(new Scope()), _lexer(lexer)

}

ABLexer::~ABLexer() {
    //        delete _lexer;
    //        delete _scope;
    //        delete _tokens;
    //        delete _paras;
}

void ABLexer::handle(const QString & text, Highlighter * lighter) {

}

void ABLexer::calcFoldings() {
//        ParaCell * iter = _paras -> iter();
//        EDITOR_POS_TYPE curr_line = 0;

//        QVector<ParaCell *> waiters;
//        waiters.reserve(5);

//        while(iter != _paras -> iter_end()) {
//            switch(iter -> para_type) {
//                case ParaInfo::pt_none: { break; }
//                case ParaInfo::pt_max: { ++curr_line; break;}
//                case ParaInfo::pt_max_end: {
//                    if (!waiters.isEmpty()) {
//                        qWarning() << "PARA OBJECTS VERIFICATION IS FAILED: " << waiters.count();
//                        waiters.clear();
//                    }

//                    return;
//                }
//                default: {
//                    iter -> line_num = curr_line;

//                    if (iter -> para_type & ParaInfo::pt_open) {
//                        waiters << iter;
//                    } else {
//                        PARA_TYPE opposite_type = ParaInfo::oppositePara(iter -> para_type);

//                        if (!waiters.isEmpty()) {
//                            ParaCell * waiter = waiters.takeLast();

//                            if ((waiter -> para_type & opposite_type) == waiter -> para_type) {
//                                waiter -> close = iter;
//                            } else {
//                                qWarning() << "PARA OBJECTS CLOSING IS FAILED: " << ParaInfo::toString(waiter -> para_type) << ParaInfo::toString(opposite_type);
//                                // TODO: do something with wrong state
//                            }
//                        } else {
//                            qWarning() << "PARA OBJECTS CLOSING WITHOUT OPEN: " << ParaInfo::toString(opposite_type);
//                        }
//                    }
//                }
//            };

//            iter = iter -> next;
//        }
}
