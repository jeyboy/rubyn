#ifndef FORMAT_TEXT_H
#define FORMAT_TEXT_H

#include "iformat.h"

class FormatText : public Singleton<FormatText> {
public:
    FormatText();

    inline FormatType formatType() const { return ft_text; }
};

#endif // FORMAT_TEXT_H
