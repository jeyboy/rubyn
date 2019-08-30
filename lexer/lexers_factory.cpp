#include "lexers_factory.h"

//#include "lexer/ruby/lexer_regexp_ruby.h"
#include "lexer/ruby/lexer_frontend.h"
#include "lexer/css/lexer_frontend.h"

LexersFactory::LexersFactory() {
    _lexers.insert(ft_file_rb, new Ruby::LexerFrontend());
    _lexers.insert(ft_file_gemfile, new Ruby::LexerFrontend());
    _lexers.insert(ft_file_rake, new Ruby::LexerFrontend());
    _lexers.insert(ft_file_css, new Css::LexerFrontend());
}

LexersFactory::~LexersFactory() {
    qDeleteAll(_lexers);
}

ILexer * LexersFactory::lexerFor(const FormatType & format) {
    return _lexers.value(format, nullptr);
}
