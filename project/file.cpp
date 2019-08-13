#include "file.h"

#include <qdatetime.h>
#include <qstringbuilder.h>
#include <qregularexpression.h>
#include "editor/document_types/documents_types.h"

#include "controls/logger.h"

QString File::default_uid;

bool File::userAskFileType() {
    //TODO: ask user about file type
    return false;
}

void File::initUid() {
    _uid = _name % QString::number(_device -> size()) % QString::number(QDateTime::currentMSecsSinceEpoch());
}

bool File::openDevice(const QFile::OpenMode & def_mode) {
    if (isOpened() && !def_mode)
        return true;
    else
        closeDevice();

    QFile * file = new QFile(_path);

    QFile::setPermissions(_path,
        QFile::ReadOwner | QFile::WriteOwner | QFile::ExeOwner |
        QFile::ReadUser | QFile::WriteUser | QFile::ExeUser |
        QFile::ReadGroup | QFile::WriteGroup | QFile::ExeGroup /*|
        QFile::ReadOther | QFile::WriteOther | QFile::ExeOther*/
    );

    if (file -> open(def_mode ? def_mode : openMode())) {
        _device = file;

        if (!_doc)
            initUid();
    } else {
        file -> deleteLater();
        return false;
    }

    return true;
}

void File::closeDevice() {
    if (isOpened()) {
        _device -> close();
        _device -> deleteLater();
        _device = nullptr;
    }
}

const QFile::OpenMode File::openMode() {
    QFile::OpenMode omode = QFile::ReadOnly;
    if (_main_format & ft_text)
        omode = QFile::Text | QFile::ReadOnly;

    return omode;
}

bool File::identifyType(const QString & name, FormatType & format, const uint & level) {
    QString lower_name = name.toLower();
    QStringList parts = lower_name.split('.', QString::SkipEmptyParts);

    if (parts.length() > 1) {
        for(QStringList::Iterator it = ++parts.begin(); it != parts.end(); it++) {
            FormatType ft = CodeFormats::identify(*it);

            if (ft == ft_unknown) continue;

            if ((format & ft_priority) < (ft & ft_priority)) {
                format = ft;
//            } else {
//                Logger::error(QLatin1Literal("File"), QLatin1Literal("Cant identify file type for: ") % _name % '(' % name % ')');
            }
        }
    } else if (lower_name.startsWith('.')) {
        format = ft_text;
    }

    if (format == ft_unknown && level == 0) {
        format = Projects::obj().identificateName(lower_name);
    }

    return format > ft_unknown;
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

bool File::identifyTypeByShebang(const QString & str, FormatType & format) {
    if (str.startsWith(QLatin1Literal("#!"))) {
        QRegularExpression regex(QLatin1Literal("\\b(ruby)\\b"), QRegularExpression::CaseInsensitiveOption);

        QRegularExpressionMatch match = regex.match(str);

        if (match.hasMatch()) {
            QString captured = match.captured(1);

            if (captured.toLower() == QLatin1Literal("ruby")) {
                format = ft_file_rb;
            }
        }
    }

    return format != ft_unknown;
}

bool File::identifyTypeByShebang(const QString & str) {
    if (identifyTypeByShebang(str, _main_format)) {
        emit Projects::obj().fileIconChanged(_path, ico());
        return true;
    }

    return false;
}

bool File::open() {
    if (!openDevice())
        return false;

    if (_main_format == ft_unknown) {
        {
            QTextStream in(_device);
            while (!in.atEnd()) {
              first_non_null_str = in.readLine();
              if (!first_non_null_str.isEmpty())
                break;
            }
        }

        _device -> reset();

        if (!identifyTypeByShebang(first_non_null_str)) {
            if (!userAskFileType())
                _main_format = ft_text;
//                return false;
        }
    }

    if (_main_format & ft_text) {
        _doc = new TextDocument(this);
        return true;
    }
    else if (_main_format & ft_tree) {
        _doc = new TreeDocument(this);
        return true;
    }
    else if (_main_format & ft_binary) {
        qDebug() << "ft_binary";
    }
    else if (_main_format & ft_image) {
        qDebug() << "ft_image";
        //_doc = new ImageDocument(_path, _name, device, project, f);
    }

    return false;
}

void File::close() {
    if (isChanged())
        save();

    closeDevice();
}

File::File(const uint & inproject_level, const QString & name, const QString & path, const FileOps & ops)
    : _doc(nullptr), _device(nullptr), _main_format(ft_unknown), _path(path), _name(name), level(inproject_level)
{
    identifyType(_name, _main_format, level);

    if (ops & fo_open) {
        open();
    }
}

File::~File() {
    close();

    delete _doc;
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

TextDocument * File::asText() {
    if (!isText()) return nullptr;

    if (!_doc) {
        if (!open())
            return nullptr;
    }

    return dynamic_cast<TextDocument *>(_doc);
}
ImageDocument * File::asImage() {
    if (!isImage()) return nullptr;

    if (!_doc) {
        if (!open())
            return nullptr;
    }

    return dynamic_cast<ImageDocument *>(_doc);
}
BinaryDocument * File::asBinary() {
    if (!isBinary()) return nullptr;

    if (!_doc) {
        if (!open())
            return nullptr;
    }

    return dynamic_cast<BinaryDocument *>(_doc);
}
TreeDocument * File::asTree() {
    if (!isTree()) return nullptr;

    if (!_doc) {
        if (!open())
            return nullptr;
    }

    return dynamic_cast<TreeDocument *>(_doc);
}

bool File::dumpState(QVariant & data) {
    //TODO: implement dump on IDocument level
    if (isText()) {
        return asText() -> dump(data);
    }

    return false;
}

bool File::restoreState(QVariant & data) {
    //TODO: implement restore on IDocument level
    if (isText()) {
        return asText() -> restore(data);
    }

    return false;
}

int File::verticalScrollState(const bool & drop) {
    //TODO: implement restore on IDocument level
    if (isText()) {
        return asText() -> verticalScrollPos(drop);
    }

    return 0;
}

bool File::setVerticalScrollState(const int & pos) {
    //TODO: implement restore on IDocument level
    if (isText()) {
        asText() -> setVerticalScrollPos(pos);
        //TODO: need additional update for current doc
        return true;
    }

    return false;
}
