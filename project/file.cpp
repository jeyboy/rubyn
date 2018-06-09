#include "file.h"

#include "editor/document_types/documents_types.h"
//#include "parts/lexer/lexer_factory.h"

QString File::icoType() {
    //TODO: write me
    return QLatin1Literal("rb");
}

bool File::userAskFileType() {
    //TODO: ask user about file type
    return false;
}

bool File::identifyType(const QString & name) {
    QStringList parts = name.split('.', QString::SkipEmptyParts);

    if (parts.length() > 1) {
        for(QStringList::Iterator it = ++parts.begin(); it != parts.end(); it++) {
            FormatType ft = CodeFormats::identify(*it);
            _main_format = (FormatType)(_main_format | ft);
        }
    }

    return _main_format > ft_unknown;
//    QByteArray ch_arr = name.toUtf8();
//    const char * str = ch_arr.constData();
//    const char * iter = str, * sub = 0;

//    FormatType format_type = ft_unknown;

//    while(true) {
//        switch(*iter) {
//            case '.': {
//                if (sub) IDENT_FORMAT(iter, sub, format_type);

//                sub = iter + 1;
//            break;}

//            case 0: {
//                if (sub) IDENT_FORMAT(iter, sub, format_type);

//                goto exit;
//            }

//            default:;
//        }

//        ++iter;
//    }
}

bool File::open() {
    if (_main_format == ft_unknown)
        if (!userAskFileType())
            return false;

    bool is_text = _main_format & ft_text;
    bool is_bynary = _main_format & ft_binary;

    if (is_text || is_bynary) {
        QFile * file = new QFile(_path);

        QFile::setPermissions(_path,
            QFile::ReadOwner | QFile::WriteOwner | QFile::ExeOwner |
            QFile::ReadUser | QFile::WriteUser | QFile::ExeUser |
            QFile::ReadGroup | QFile::WriteGroup | QFile::ExeGroup /*|
            QFile::ReadOther | QFile::WriteOther | QFile::ExeOther*/
        );

        QFile::OpenMode omode = QFile::ReadOnly;
        if (is_text)
            omode |= QFile::Text;

        if (file -> open(omode)) {
            _device = file;
        } else {
            file -> deleteLater();
            return false;
        }


        //TODO: return BynaryDocument if is_bynary

        _doc = new TextDocument(this);

        return true;
    }
//    else if (_main_format & ft_image)
//        _doc = new ImageDocument(_path, _name, device, project, f);

    return false;
}

File::File(const QString & name, const QString & path, const FileOps & ops)
    : _doc(0), _device(0), _main_format(ft_unknown), _path(path), _name(name)
{
    identifyType(_name);

    if (ops & fo_open) {
        open();
    }
}

//File::File(const QUrl & uri, Project * project) : _doc(0), _device(0), _project(project) {
//    bool is_local = uri.isLocalFile();
//    _path = is_local ? uri.toLocalFile() : uri.toString();

//    if (is_local)
//        _name = _path.section('/', -1, -1);
//    else
//        _name = _path;

//    open(_name, _path, is_local);
//}

TextDocument * File::asText() { return dynamic_cast<TextDocument *>(_doc); }
ImageDocument * File::asImage() { return dynamic_cast<ImageDocument *>(_doc); }
BinaryDocument * File::asBinary() { return dynamic_cast<BinaryDocument *>(_doc); }
