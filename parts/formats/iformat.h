#ifndef IFORMAT_H
#define IFORMAT_H

#include <qhash.h>

#include "format_types.h"
#include "misc/singleton.h"

#define IDENT_FORMAT(iter, sub, format, complex) \
    {\
        FormatType nft = types.value(QByteArray(sub, iter - sub), ft_unknown);\
        complex = complex || (format != ft_unknown && nft != ft_unknown && nft != format); \
        format = (FormatType)(format | nft);\
    }

class IFormat : public Singleton<IFormat> {
    static QHash<QByteArray, FormatType> types;
public:
    virtual FormatType formatType() const = 0;

    static bool determine(const QString & path, FormatType & format, bool & complex);
};

#endif // IFORMAT_H
