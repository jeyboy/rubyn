#ifndef IGRAMMAR_H
#define IGRAMMAR_H

#include "misc/singleton.h"
#include "lexer/state_lexems.h"
#include "highlighter/para_type.h"
#include "highlighter/identifiers.h"

class IGrammar {
protected:
    QHash<StateLexem, PARA_TYPE> para_tokens;
    QHash<PARA_TYPE, PARA_TYPE> para_opposition;

    StateLexem rules[lex_max][lex_max] = {{lex_error}};
    virtual ~IGrammar();
public:  
    //    static inline bool hasPara(const QByteArray & poss_para) { return para_tokens.contains(poss_para); }
    inline const PARA_TYPE & paraType(const StateLexem & poss_para) { return para_tokens[poss_para]; }
    inline PARA_TYPE oppositePara(const PARA_TYPE & para_type) { return para_opposition.value(para_type, pt_none); }

    StateLexem translate(const StateLexem & state, const StateLexem & input);
    virtual bool stackDropable(const StateLexem & state, const StateLexem & input);

    virtual Identifier toHighlightable(const StateLexem & /*lexem*/) = 0;
};

#endif // IGRAMMAR_H
