#ifndef IGRAMMAR_H
#define IGRAMMAR_H

#include "misc/singleton.h"
#include "highlighter/para_type.h"
#include "highlighter/identifiers.h"
#include "lexer/lexer_stack_flags.h"
#include "lexer/istate_lexem.h"

class IGrammar {
protected:
    QHash<IState::Lexem, ParaType> para_tokens;

    virtual ~IGrammar();
public:  
    //    static inline bool hasPara(const QByteArray & poss_para) { return para_tokens.contains(poss_para); }
    inline const ParaType & paraType(const IState::Lexem & poss_para) { return para_tokens[poss_para]; }
//    inline PARA_TYPE oppositePara(const PARA_TYPE & para_type) { return para_opposition.value(para_type, pt_none); }

    virtual IState::Lexem translate(const IState::Lexem & state, const IState::Lexem & input) {
        if (input == IState::LEX_NONE_STATE)
            return state;

        return input;
    }

    virtual void initFlags(StackLexemFlag & flags, const IState::Lexem & lex, const IState::Lexem & last_non_blank_lex) = 0;

    virtual bool stackDropable(const IState::Lexem & state, const IState::Lexem & input);

    virtual Identifier toHighlightable(const IState::Lexem & /*lexem*/) = 0;
};

#endif // IGRAMMAR_H
