#include "ruby_lexer_control.h"

using namespace Ruby;

void LexerControl::validateHeredocState() {
    //TODO: remove all stack values till we have heredoc start on the top
    if (stack_token) {
        switch(stack_token -> lexem) {
            case lex_heredoc_intended_start:
            case lex_heredoc_start:
            case lex_cheredoc_intended_start:
            case lex_cheredoc_start:
            case lex_eheredoc_intended_start:
            case lex_eheredoc_start: { break;}

            default: {
                lightWithMessage(
                    lex_error,
                    QByteArrayLiteral("Wrong stack state for begin of heredoc")
                );
            }
        }
    }
}

void LexerControl::registerHeredocMark(const Ruby::StateLexem & lexem, QString * name) {
    StateLexem doc_lex = lex_none;

    switch(lexem) {
        case lex_heredoc_intended_mark:     { doc_lex = lex_heredoc_intended_start; break;}
        case lex_heredoc_mark:              { doc_lex = lex_heredoc_start; break;}
        case lex_cheredoc_intended_mark:    { doc_lex = lex_cheredoc_intended_start; break;}
        case lex_cheredoc_mark:             { doc_lex = lex_cheredoc_start; break;}
        case lex_eheredoc_intended_mark:    { doc_lex = lex_eheredoc_intended_start; break;}
        case lex_eheredoc_mark:             { doc_lex = lex_eheredoc_start; break;}
        default:;
    };

    if (doc_lex != lex_none) {
        TokenCell * new_heredoc =
            TokenList::insert(user_data -> token_begin, doc_lex, -1, 0);

        new_heredoc -> data = name;

        if (!heredoc_token) {
            new_heredoc -> stacked_prev = stack_token;
            heredoc_token = stack_token = new_heredoc;
        } else {
            new_heredoc -> stacked_prev = heredoc_token -> stacked_prev;
            heredoc_token -> stacked_prev = new_heredoc;
            heredoc_token = new_heredoc;
        }

        if (!heredoc_para) {
            para = heredoc_para = ParaList::insert(para, grammar -> paraType(doc_lex), cached_str_pos, quint8(cached_length));
        } else {
            heredoc_para = ParaList::insert(heredoc_para -> prev, grammar -> paraType(doc_lex), cached_str_pos, quint8(cached_length));
        }
    } else {
        int i = 0;
    }
}

void LexerControl::procStackable(const Ruby::StateLexem & lexem, const uint & flags) {
    if (flags != slf_none) {
        bool stackable = flags & slf_stackable;
        bool unstackable = flags & slf_unstackable;

        if (unstackable) {
            if (stack_token) {
                attachPara(grammar -> paraType(lexem), flags, true);

                if (!grammar -> stackDropable((Ruby::StateLexem &)stack_token -> lexem, lexem))
                    cacheAndLightWithMessage(lex_error, QByteArrayLiteral("Wrong stack state"));
                else {
//                        lex_prev_word = stack_token -> stacked_state_lexem;

//                        if (lex_prev_word == lex_none)
//                            lex_prev_word = stack_token -> lexem;

                    stack_token = stack_token -> stacked_prev;
                }
            } else {
                cacheAndLightWithMessage(lex_error, QByteArrayLiteral("Wrong stack state"));
            }
        }

        if (stackable) {
//            if (!heredoc_token) {
//                heredoc_token = token;
//            }

            token -> stacked_prev = stack_token;
            stack_token = token;

//                stack_token -> stacked_state_lexem = lex_none; //stack_word ? lex_prev_word : lex_word;
            lex_prev_word = lex_none;

            attachPara(grammar -> paraType(lexem), flags, false);
        }

//            lex_word = lex_none;
//            lex_delimiter = lex_none;
    }
}

ScopeCell * LexerControl::scopeParent(ScopeCell * curr_scope) {
    ScopeCell * it = curr_scope -> prev;

    while(it) {
        if (it -> pos == -1) {
            it = it -> prev;
        } else {
            if (it -> is_opener && !it -> closer) {
               return it;
            }


            if (!it -> is_opener && it -> closer) {
                it = it -> closer;
            }

            it = it -> prev;
        }
    }

    return nullptr;
}

void LexerControl::attachScope(const Ruby::ScopeLexem & scope_lexem, const uint & flags) {
    if (scope -> next) {
        scope = scope -> next;
        scope -> scope_type = scope_lexem;
        scope -> pos = cached_str_pos;
        scope -> length = cached_length;
    }
    else scope = ScopeList::insert(scope, scope_lexem, cached_str_pos, cached_length);

    scope -> is_opener = flags & slf_stack_word;

    if (!scope -> is_opener) {
        ScopeCell * para_scope = scopeParent(scope);
        para_scope -> closer = scope;
    }
}

void LexerControl::attachToken(const Ruby::StateLexem & lexem, const uint & flags) {
    if (token -> next) {
        token = token -> next;
        token -> lexem = lexem;
        token -> start_pos = cached_str_pos;
        token -> length = cached_length;

        if (token -> data) {
            delete token -> data;
            token -> data = nullptr;
        }
    }
    else token = TokenList::insert(token, lexem, cached_str_pos, cached_length);

    if (token -> lexem >= lex_none)
        last_non_blank_token = token;

    procStackable(lexem, flags);
}

ParaCell * LexerControl::paraParent(int & lines_between, ParaCell * para, const bool & foldable, const bool & only_blockators) {
    ParaCell * it = para -> prev;
    lines_between = 0;

    while(it) {
        if (it -> pos == -1) {
            ++lines_between;
            it = it -> prev;
        } else {
            if (it -> is_opener && it -> is_foldable == foldable) {
                if (!only_blockators || (only_blockators && it -> is_blockator)) {
                    if ((it -> para_type != pt_heredoc && para -> para_type != pt_close_heredoc) || (it -> para_type == pt_heredoc && para -> para_type == pt_close_heredoc)) {
                        return it;
                    }
                }
            }


            // skip only if type is equal to target one: ] => ] and etc.
            if (!it -> is_opener && it -> closer && para -> para_type != pt_close_heredoc) {
                it = it -> closer;
            }

            it = it -> prev;
        }
    }

    return nullptr;
}

void LexerControl::attachPara(const Ruby::ParaLexem & ptype, const uint & flags, const bool & closable) {
    if (!ptype) return;

    bool replaceable = flags & slf_replace_word;

    if (!replaceable || (replaceable && closable)) {
        if (para -> next) {
            para = para -> next;

            if (!para -> is_opener)
                para -> closer = nullptr;

            para -> para_type = ptype;
            para -> pos = cached_str_pos;
            para -> length = quint8(cached_length); // 8 bits should be enough for any type of para

            para -> is_foldable = false;
            para -> is_oneliner = false;
        }
        else para = ParaList::insert(para, ptype, cached_str_pos, quint8(cached_length));

        para -> is_blockator = !replaceable;
    }

    para -> is_opener = !closable;
    para -> is_foldable = ptype & pt_foldable;

    if (closable) {
        int lines_between;
        ParaCell * parent = paraParent(lines_between, para, para -> is_foldable, false);

        if (parent) {
            if (para -> is_foldable) {
                if (!replaceable && parent -> is_blockator == false) {
                    user_data -> level -= lines_between > 0 ? 2 : 1;

                    parent -> is_oneliner = parent -> is_blockator ? lines_between == 1 : lines_between < 2;
                    parent = paraParent(lines_between, para, true, true);

                } else if (lines_between > 0 && parent -> is_blockator != replaceable) {
                    parent -> is_oneliner = lines_between < 2;
                    --user_data -> level;
                }
            }

            if (parent) {
                parent -> is_oneliner = parent -> is_oneliner || lines_between == 0;

                if (!replaceable) {
                    if (parent -> closer && parent -> closer != para)
                        parent -> closer -> closer = nullptr;

                    parent -> closer = para;

                    if (para -> closer && para -> closer != parent)
                        para -> closer -> closer = nullptr;

                    para -> closer = parent;
                }
            }
        }
        else para -> closer = nullptr;

        if (parent && parent -> is_oneliner && para -> is_foldable) {
            control_para = prevFoldableInActiveParaLine(parent);
            return;
        }
    } else {
        if (ptype == pt_heredoc) {
            para -> data = new QString(cached);
        }

//        para -> potential_closer_para_type = grammar -> potentialCloserParaType((Ruby::ParaLexem &)para -> para_type);
    }

    if (para -> is_foldable) {
        control_para = para;
    }
}
