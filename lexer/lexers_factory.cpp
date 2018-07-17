#include "lexers_factory.h"

#include "lexer/ruby/lexer_regexp_ruby.h"

LexersFactory::LexersFactory() {
    _lexers.insert(ft_file_rb, new LexerRegexpRuby());
    _lexers.insert(ft_file_gemfile, new LexerRegexpRuby());
}

LexersFactory::~LexersFactory() {
    qDeleteAll(_lexers);
}

ILexer * LexersFactory::lexerFor(const FormatType & format) {
    return _lexers.value(format, 0);
}
