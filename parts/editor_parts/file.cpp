#include "file.h"

#include "parts/document_types/documents_types.h"

void File::init(const QString & name, const QString & path, const bool & is_local) {
    QIODevice * device = 0;
    Lexer * lexer;

    bool res = LexerFactory::determine(name, lexer);

    if (!res) {
        //TODO: ask user about preffered type of file
    }

    _main_format = lexer -> format();

    bool is_text = _main_format & ft_text, is_bynary = _main_format & ft_binary;

    if (is_text || is_bynary) {
        if (is_local) {
            QFile * file = new QFile(path);

            //TODO: update permissions for file before opening

            QFile::OpenMode omode = QFile::ReadOnly;
            if (is_text)
                omode |= QFile::Text;

            if (file -> open(omode)) {
                device = file;
            } else {
                file -> deleteLater();
                return 0;
            }
        } else {
            //TODO: proceed remote file
            return 0; // but not now ...
        }

        //TODO: return BynaryDocument if is_bynary

        doc = new TextDocument(device, lexer);
    }

//    if (format & ft_image)
//        return new ImageDocument(path, name, device, project, f);
}

File::File(const QString & name, const QString & path, Project * project)
    : doc(0), project(project), _path(path), _name(name)
{
    init(_name, _path, true);
}

File::File(const QUrl & uri, Project * project = 0) : doc(0), project(project) {
    bool isLocal = uri.isLocalFile();
    _path = isLocal ? uri.toLocalFile() : uri.toString();

    if (isLocal)
        _name = _path.section('/', -1, -1);
    else
        _name = _path;

    init(_name, _path, is_local);
}
