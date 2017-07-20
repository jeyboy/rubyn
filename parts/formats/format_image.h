#ifndef FORMAT_IMAGE_H
#define FORMAT_IMAGE_H

#include "iformat.h"

class FormatImage : public IFormat, public Singleton<FormatImage> {
public:
    FormatImage() {}

    inline FormatType formatType() const { return ft_image; }
    inline IHighlightPreset * highlightPreset() const { return 0; }
};

#endif // FORMAT_IMAGE_H
