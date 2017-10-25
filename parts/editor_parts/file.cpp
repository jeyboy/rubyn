#include "file.h"

#include "parts/document_types/documents_types.h"
#include "parts/lexer/lexer_factory.h"

void File::init(const QString & name, const QString & path, const bool & is_local) {
    Lexer * lexer;

    bool res = LexerFactory::determine(name, lexer);

    if (!res) {
        //TODO: ask user about preffered type of file
        return;
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
                _device = file;
            } else {
                file -> deleteLater();
                return;
            }
        } else {
            //TODO: proceed remote file
            return; // but not now ...
        }

        //TODO: return BynaryDocument if is_bynary

        _doc = new TextDocument(this, lexer);
    }
//    else if (_main_format & ft_image)
//        _doc = new ImageDocument(path, name, device, project, f);
}

File::File(const QString & name, const QString & path, Project * project)
    : _doc(0), _device(0), _project(project), _path(path), _name(name)
{
    init(_name, _path, true);
}

File::File(const QUrl & uri, Project * project) : _doc(0), _device(0), _project(project) {
    bool is_local = uri.isLocalFile();
    _path = is_local ? uri.toLocalFile() : uri.toString();

    if (is_local)
        _name = _path.section('/', -1, -1);
    else
        _name = _path;

    init(_name, _path, is_local);
}

TextDocument * File::asText() { return dynamic_cast<TextDocument *>(_doc); }
ImageDocument * File::asImage() { return dynamic_cast<ImageDocument *>(_doc); }
BinaryDocument * File::asBinary() { return dynamic_cast<BinaryDocument *>(_doc); }
