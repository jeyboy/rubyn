#include "lexers_factory.h"

#include "lexer/ruby/lexer_regexp_ruby.h"

LexersFactory::LexersFactory() {
    _lexers.insert(ft_file_rb, new Ruby::LexerRegexp());
    _lexers.insert(ft_file_gemfile, new Ruby::LexerRegexp());
}

LexersFactory::~LexersFactory() {
    qDeleteAll(_lexers);
}

ILexer * LexersFactory::lexerFor(const FormatType & format) {
    return _lexers.value(format, nullptr);
}
