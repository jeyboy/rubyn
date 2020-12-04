#include "lexers_factory.h"

//#include "lexer/ruby/lexer_regexp_ruby.h"
#include "lexer/ruby/ruby_lexer.h"
//#include "lexer/css/css_css_lexer.h"
//#include "lexer/html/html_lexer.h"

LexersFactory::LexersFactory() {
    _lexers.insert(ft_file_rb, new Ruby::Lexer());
    _lexers.insert(ft_file_gemfile, new Ruby::Lexer());
    _lexers.insert(ft_file_rake, new Ruby::Lexer());
//    _lexers.insert(ft_file_css, new Css::LexerFrontend());
//    _lexers.insert(ft_file_html, new Html::LexerFrontend());
}

LexersFactory::~LexersFactory() {
    qDeleteAll(_lexers);
}

ILexer * LexersFactory::lexerFor(const FormatType & format) {
    return _lexers.value(format, nullptr);
}
