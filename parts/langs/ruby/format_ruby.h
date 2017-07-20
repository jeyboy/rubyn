#ifndef FORMAT_RUBY_H
#define FORMAT_RUBY_H

#include "parts/formats/iformat.h"
#include "ruby_preset.h"

class FormatRuby : public IFormat, public Singleton<FormatRuby> {
public:
    FormatRuby();

    inline FormatType formatType() const { return ft_rb; }
    inline IHighlightPreset * highlightPreset() const { return &RubyPreset::obj(); }
};

#endif // FORMAT_RUBY_H
