#include "file.h"

#include "editor/document_types/documents_types.h"
//#include "parts/lexer/lexer_factory.h"


//QFile::setPermissions(path,
//    QFile::ReadOwner | QFile::WriteOwner | QFile::ExeOwner |
//    QFile::ReadUser | QFile::WriteUser | QFile::ExeUser |
//    QFile::ReadGroup | QFile::WriteGroup | QFile::ExeGroup /*|
//    QFile::ReadOther | QFile::WriteOther | QFile::ExeOther*/
//);



bool File::identifyType(const QString & name) {
//    _main_format =

//    QByteArray ch_arr = path.toUtf8();
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



//    QString ext = name.section('.', -1, -1);
//    if (sExt != fileName && sExt.indexOf(' ') == -1) {
//        if (extract)
//            fileName = fileName.section('.', 0, -2);
//        return true;
//    } else {
//        sExt.clear();
//        return false;
//    }
}

void File::init(const QString & name, const QString & path) {
//    Lexer * lexer;

//    bool res = LexerFactory::determine(name, lexer);

//    if (!res) {
//        //TODO: ask user about preffered type of file
//        return;
//    }

//    _main_format = lexer -> format();

    bool is_text = _main_format & ft_text, is_bynary = _main_format & ft_binary;

    if (is_text || is_bynary) {
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


        //TODO: return BynaryDocument if is_bynary

        _doc = new TextDocument(this, _main_format);
    }
//    else if (_main_format & ft_image)
//        _doc = new ImageDocument(path, name, device, project, f);
}

File::File(const QString & name, const QString & path)
    : _doc(0), _device(0), _path(path), _name(name)
{
    init(_name, _path);
}

//File::File(const QUrl & uri, Project * project) : _doc(0), _device(0), _project(project) {
//    bool is_local = uri.isLocalFile();
//    _path = is_local ? uri.toLocalFile() : uri.toString();

//    if (is_local)
//        _name = _path.section('/', -1, -1);
//    else
//        _name = _path;

//    init(_name, _path, is_local);
//}

TextDocument * File::asText() { return dynamic_cast<TextDocument *>(_doc); }
ImageDocument * File::asImage() { return dynamic_cast<ImageDocument *>(_doc); }
BinaryDocument * File::asBinary() { return dynamic_cast<BinaryDocument *>(_doc); }
