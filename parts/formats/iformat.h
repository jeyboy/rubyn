#ifndef IFORMAT_H
#define IFORMAT_H

#include <qhash.h>

#include "format_types.h"
#include "misc/singleton.h"

#define IDENT_FORMAT(iter, sub, format) \
    {\
        FormatType nft = types.value(QByteArray(sub, iter - sub), ft_unknown);\
        format = (FormatType)(format | nft);\
    }

class IHighlightPreset;

class IFormat {
    static QHash<QByteArray, FormatType> types;
    static QHash<FormatType, IFormat *> formats;
public:
    virtual FormatType formatType() const = 0;
    virtual IHighlightPreset * highlightPreset() const = 0;

    static bool determine(const QString & path, IFormat *& format);
};

#endif // IFORMAT_H
