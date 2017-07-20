#ifndef FORMAT_RUBY_H
#define FORMAT_RUBY_H

#include "iformat.h"

class FormatRuby : public IFormat {
public:
    FormatRuby();

    inline FormatType formatType() const { return ft_rb; }
};

#endif // FORMAT_RUBY_H
