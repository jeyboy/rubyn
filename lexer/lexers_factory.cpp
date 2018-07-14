#include "lexers_factory.h"

#include "lexer/ruby/ruby_regexp_lexer.h"

LexersFactory::LexersFactory() {
//    QHash<FormatType, ILexer *> lexers;

    _lexers.insert(ft_file_rb, new RubyRegexpLexer());
    _lexers.insert(ft_file_gemfile, new RubyRegexpLexer());
}

LexersFactory::~LexersFactory() {
    qDeleteAll(_lexers);
}

ILexer * LexersFactory::lexerFor(const FormatType & format) {
    return _lexers.value(format, 0);
}
