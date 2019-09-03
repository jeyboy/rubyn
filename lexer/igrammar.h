#ifndef IGRAMMAR_H
#define IGRAMMAR_H

#include "misc/singleton.h"
#include "highlighter/para_type.h"
#include "highlighter/identifiers.h"
#include "lexer/lexer_stack_flags.h"
#include "lexer/state_lexem.h"

class IGrammar {
protected:
    QHash<LEXEM_TYPE, ParaType> para_tokens;

    virtual ~IGrammar();
public:  
    //    static inline bool hasPara(const QByteArray & poss_para) { return para_tokens.contains(poss_para); }
    inline const ParaType & paraType(const LEXEM_TYPE & poss_para) { return para_tokens[poss_para]; }
//    inline PARA_TYPE oppositePara(const PARA_TYPE & para_type) { return para_opposition.value(para_type, pt_none); }

    virtual LEXEM_TYPE translate(const LEXEM_TYPE & state, const LEXEM_TYPE & input) {
        if (input == lex_none)
            return state;

        return input;
    }

    virtual void initFlags(StackLexemFlag & flags, const LEXEM_TYPE & lex, const LEXEM_TYPE & last_non_blank_lex) = 0;

    virtual bool stackDropable(const LEXEM_TYPE & state, const LEXEM_TYPE & input);

    virtual Identifier toHighlightable(const LEXEM_TYPE & /*lexem*/) = 0;
};

#endif // IGRAMMAR_H
