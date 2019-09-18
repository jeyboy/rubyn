#ifndef LEXER_CONTEXT_H
#define LEXER_CONTEXT_H

#include <qhash.h>

#include "project/code_formats.h"
#include "lexer/lexers_factory.h"

class ILexer;

struct LexerContext {
    FormatType _main_format;
    FormatType _add_format;

    QHash<FormatType, ILexer *> _formats;

    LexerContext();

    void append(const FormatType & new_format) {
        if (new_format == ft_unknown)
            return;

        if (_main_format == ft_file_css && (new_format == ft_file_scss || new_format == ft_file_sass)) {
            _main_format = new_format;
        }
        else if (_main_format == ft_file_js && new_format == ft_file_coffee) {
            _main_format = new_format;
        } else {
            int curr_priority = _main_format & ft_priority;
            int new_priority = new_format & ft_priority;

            if (curr_priority != new_priority) {
                if (curr_priority < new_priority) {
                    if (new_priority == ft_level_two)
                         _add_format = _main_format;

                    _main_format = new_format;
                } else {
                    if (new_priority == ft_level_two)
                        _add_format = new_format;
                }
            }
        }

        attachFormat(_main_format = new_format);
    }

    void attachFormat(const FormatType & new_format) {
        switch(new_format) {
            case ft_file_html: {
                _formats.insert(ft_file_css, LexersFactory::obj().lexerFor(ft_file_css));
                _formats.insert(ft_file_js, LexersFactory::obj().lexerFor(ft_file_js));
            break;}

            default:;
        }

        _formats.insert(_main_format, LexersFactory::obj().lexerFor(new_format));
    }

    bool hasType() { return _main_format != ft_unknown; }
};

#endif // LEXER_CONTEXT_H
