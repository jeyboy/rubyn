#ifndef RUBY_GRAMMAR_H
#define RUBY_GRAMMAR_H

//https://github.com/ruby/ruby/tree/trunk/doc

//#include "lexer/igrammar.h"
//#include "lexer/state_lexem.h"

#include "controls/logger.h"
#include "highlighter/identifiers.h"
#include "lexer/lexer_stack_flags.h"
#include "lexer/para_type.h"

#include "misc/singleton.h"
#include "ruby_state_lexems.h"
#include "ruby_para_lexem.h"

namespace Ruby {
    class Grammar : public Singleton<Grammar> {
        QHash<Ruby::StateLexem, Ruby::ParaLexem> para_tokens;
        QHash<Ruby::ParaLexem, Ruby::ParaLexem> para_closers;

        Grammar();

        friend class Singleton<Grammar>;
    protected:
        void initParas();
    public:
        void initFlags(StackLexemFlag & flags, const Ruby::StateLexem & lex, const Ruby::StateLexem & last_non_blank_lex);

        bool stackDropable(const Ruby::StateLexem & state, const Ruby::StateLexem & input);

        inline const Ruby::ParaLexem & paraType(const Ruby::StateLexem & poss_para) { return para_tokens[poss_para]; }

        inline const Ruby::ParaLexem & potentialCloserParaType(const Ruby::ParaLexem & target_para) {
            if (!para_closers.contains(target_para)) {
                Logger::obj().error("Ruby::Grammar", "Closer not set for " % QString::number(target_para));
                para_closers[target_para] = pt_reserved;
            }

            return para_closers[target_para];
        }

//        LEXEM_TYPE toInterceptor(const Ruby::StateLexem & lex);

        Ruby::StateLexem stateForHeredoc(const Ruby::StateLexem & lex, const bool & content);

        QChar percentagePresentationBlocker(const QChar & ch);

//        bool isStackDroppable(const Ruby::StateLexem & lexem);

//        bool isInterpolable(const Ruby::StateLexem & lexem);

//        LEXEM_TYPE toHeredocContinious(const Ruby::StateLexem & lexem);

//        LEXEM_TYPE fromContinious(const Ruby::StateLexem & lexem);

        Identifier toHighlightable(const Ruby::StateLexem & lexem);

        Ruby::StateLexem translate(const Ruby::StateLexem & state, const Ruby::StateLexem & handle);
    };
}

#endif // GRAMMAR_RUBY_H
