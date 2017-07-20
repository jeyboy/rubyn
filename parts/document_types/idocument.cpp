#include "idocument.h"
#include "documents_types.h"
#include "parts/formats/iformat.h"

IDocument * IDocument::create(const QString & path, const QString & name, QIODevice * device) {
    FormatType f;
    bool complex;

    bool res = IFormat::determine(name, f, complex);

    if (!res) {
        //TODO: ask user about preffered type of file
    }

    if (f & ft_text)
        return new TextDocument(path, name, device, f, complex);

    if (f & ft_image)
        return new ImageDocument(path, name, device, f, complex);

    return 0;
}
