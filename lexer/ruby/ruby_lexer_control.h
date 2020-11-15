#ifndef RUBY_LEXER_CONTROL_H
#define RUBY_LEXER_CONTROL_H

#include "ruby_grammar.h"
#include "ruby_state_lexems.h"
#include "lexer/ilexer_control.h"

namespace Ruby {
    struct LexerControl : public ILexerControl {
        Grammar * grammar;

        StateLexem lex_prev_word;
        StateLexem lex_word;
        StateLexem lex_delimiter;


        LexerControl(BlockUserData *& user_data, TokenCell * stack_token = nullptr, IHighlighter * lighter = nullptr) : ILexerControl(user_data, stack_token, lighter),
            grammar(&Grammar::obj()), lex_prev_word(lex_none), lex_word(lex_none), lex_delimiter(lex_none) {}

        ~LexerControl() {}

        void postCachingPredecate() {
            if (lex_word != lex_none) {
                lex_prev_word = lex_word;
            }
        }

        inline Ruby::StateLexem & sublastToken() { return (Ruby::StateLexem &)(token -> prev -> lexem); }
        inline Ruby::StateLexem & lastToken() { return (Ruby::StateLexem &)(token -> lexem); }
        inline Ruby::StateLexem lastNonBlankLexem() {
            if (last_non_blank_token)
                return Ruby::StateLexem(last_non_blank_token -> lexem);

            TokenCell * it = token;

            while(it) {
                if (it -> lexem >= lex_none)
                    return Ruby::StateLexem((last_non_blank_token = it) -> lexem);

                it = it -> prev;
            }

            return lex_none;
        }

        void procStackable(const Ruby::StateLexem & lexem, const uint & flags);

        ScopeCell * scopeParent(ScopeCell * curr_scope);
        void attachScope(const Ruby::ScopeLexem & scope_lexem, const uint & flags = slf_none);

        void attachToken(const Ruby::StateLexem & lexem, const uint & flags = slf_none);
    //    inline void replaceToken(const StateLexem & lexem, const uint & flags = slf_none) {
    //        token -> lexem = lexem;
    //        token -> length += cached_length;

    //        if (flags != slf_none && stack_token != token) {
    //            token -> stacked_prev = stack_token;
    //            stack_token = token;
    //        }
    //    }

    //    void popStack() {
    //        if (!stack_token) return;

    //        stack_token = stack_token -> stacked_prev;
    //    }


        void light(const LEXEM_TYPE & lexem) {
            light((const Identifier &)grammar -> toHighlightable((const Ruby::StateLexem &)lexem));
        }

        inline void light(const Ruby::StateLexem & lexem) {
            light((const Identifier &)grammar -> toHighlightable(lexem));
        }

        inline ParaCell * prevFoldableInActiveParaLine(ParaCell * pcell) {
            ParaCell * it = pcell;

            while(it && it -> para_type != pt_none) {
                it = it -> prev;

                if (it -> is_foldable && it -> is_opener)
                    return it;
            }

            return nullptr;
        }

    //    inline ParaCell * lastNonClosedPara(const bool & replaceable) {
    //        ParaCell * it = !replaceable && active_para ? active_para : para -> prev;

    //        while(it) {
    //            if (!it -> close && ((replaceable && it -> para_type == pt_none) || (!replaceable && it -> pos != -1))) {
    //                return it;
    //            }

    //            it = it -> prev;
    //        }

    //        return nullptr;
    //    }
    //    inline bool paraInActiveParaLine(ParaCell * pcell) {
    //        ParaCell * it = active_para;

    //        while(it && it -> para_type != pt_max) {
    //            if (it == pcell)
    //                return true;

    //            it = it -> next;
    //        }

    //        return false;
    //    }
    //    inline bool paraIsNextToActiveParaLine(ParaCell * pcell) {
    //        ParaCell * it = active_para;

    //        if (it) {
    //            while(it -> para_type != pt_none && (it = it -> next));
    //            return it == pcell;
    //        }

    //        return false;
    //    }

        ParaCell * paraParent(int & lines_between, ParaCell * para, const bool & foldable, const bool & only_blockators = false);

        void attachPara(const Ruby::ParaLexem & ptype, const uint & flags, const bool & closable);

        void validateHeredocState();
        void registerHeredocMark(const Ruby::StateLexem & lexem, QString * name);
    };
}

#endif // RUBY_LEXER_CONTROL_H
