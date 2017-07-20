#ifndef FORMAT_TEXT_H
#define FORMAT_TEXT_H

#include "iformat.h"

class FormatText : public IFormat, public Singleton<FormatText> {
public:
    FormatText() {}

    inline FormatType formatType() const { return ft_text; }
    inline IHighlightPreset * highlightPreset() const { return 0; }
};

#endif // FORMAT_TEXT_H
