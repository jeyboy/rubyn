#include "file.h"

#include <qdatetime.h>
#include <qstringbuilder.h>
#include <qregularexpression.h>
#include <qfileinfo.h>

#include "lexer/lexer_context.h"
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
    if (_context -> _main_format & ft_text)
        omode = QFile::Text | QFile::ReadOnly;

    return omode;
}

bool File::isFolder(const QString & url) {
    QFileInfo f(url);

    return f.isDir();
}

bool File::identifyType(const QString & name, LexerContext *& _context, const uint & level) {
    QString lower_name = name.toLower();
    QStringList parts = lower_name.split('.', QString::SkipEmptyParts);

    if (parts.length() > 1) {
        for(QStringList::Iterator it = ++parts.begin(); it != parts.end(); it++) {
            FormatType ft = CodeFormats::identify(*it);

            if (ft == ft_unknown) continue;

            _context -> append(ft);
        }
    } else if (lower_name.startsWith('.')) {
        _context -> append(ft_text);
    }

    if (_context -> _main_format == ft_unknown && level == 0) {
        _context -> append(Projects::obj().identificateName(lower_name));
    }

    return _context -> _main_format > ft_unknown;
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

bool File::identifyTypeByShebang(const QString & str, LexerContext *& context) {
    if (str.startsWith(QLatin1Literal("#!"))) {
        QRegularExpression regex(QLatin1Literal("\\b(ruby)\\b"), QRegularExpression::CaseInsensitiveOption);

        QRegularExpressionMatch match = regex.match(str);

        if (match.hasMatch()) {
            QString captured = match.captured(1);

            if (captured.toLower() == QLatin1Literal("ruby")) {
                context -> append(ft_file_rb);
            }
        }
    }

    return context -> hasType();
}

bool File::identifyTypeByShebang(const QString & str) {
    if (identifyTypeByShebang(str, _context)) {
        emit Projects::obj().fileIconChanged(_path, ico());
        return true;
    }

    return false;
}

const QString & File::firstStr() {
    if (first_non_null_str.isEmpty()) {
        QTextStream in(_device);
        while (!in.atEnd()) {
          first_non_null_str = in.readLine();
          if (!first_non_null_str.isEmpty())
            break;
        }

        if (first_non_null_str.isEmpty())
            first_non_null_str.append(' ');

        _device -> reset();
    }

    return first_non_null_str;
}

bool File::openRaw() {
    return openDevice();
}

bool File::open() {
    if (!openRaw())
        return false;

    if (!_context -> hasType()) {
        if (!identifyTypeByShebang(firstStr())) {
            if (!userAskFileType())
                _context -> _main_format = ft_custom_text;
//                return false;
        }
    }

    if (tooLarge() && !isCustomText()) {
        _context -> _main_format = FormatType(_context -> _main_format - ft_text + ft_custom_text);
    }

    if (isCustomText()) {
        _doc = new Custom::Document(this);
        return true;
    }
    else if (isText()) {
        _doc = new TextDocument(this);
        return true;
    }
    else if (isTree()) {
        _doc = new TreeDocument(this);
        return true;
    }
    else if (isBinary()) {
        qDebug() << "ft_binary";
    }
    else if (isImage()) {
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
    : _doc(nullptr), _device(nullptr), _context(new LexerContext()), _path(path),
      _name(name), level(inproject_level), opened_count(0), is_external(false)
{
    identifyType(_name, _context, level);

    if (ops & fo_open) {
        open();
    }
}

File::~File() {
    close();

    emit Projects::obj().fileRemoved(uid());

    delete _doc;
    delete _context;
}

QIcon File::ico() {
    if (_context -> _main_format == ft_file_ico) {
        QIcon ico(_path);

        if (ico.isNull() || ico.availableSizes().isEmpty())
            return Projects::obj().getIco(ft_broken);
        else {
            int ico_size = Projects::obj().icoSize();
            QIcon ret_ico;
            QPixmap pix = ico.pixmap(QSize(ico_size, ico_size)).scaled(ico_size, ico_size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            ret_ico.addPixmap(pix);
            return ret_ico;
        }
    }

    return Projects::obj().getIco(_context -> _main_format, _context -> _add_format);
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

    return dynamic_cast<TextDocument *>(document());
}

Custom::Document * File::asCustomText() {
    if (!isCustomText()) return nullptr;

    return dynamic_cast<Custom::Document *>(document());
}

ImageDocument * File::asImage() {
    if (!isImage()) return nullptr;

    return dynamic_cast<ImageDocument *>(document());
}
BinaryDocument * File::asBinary() {
    if (!isBinary()) return nullptr;

    return dynamic_cast<BinaryDocument *>(document());
}
TreeDocument * File::asTree() {
    if (!isTree()) return nullptr;

    return dynamic_cast<TreeDocument *>(document());
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

QPoint File::scrollState(const bool & drop) {
    //TODO: implement restore on IDocument level
    if (isText()) {
        return asText() -> scrollPos(drop);
    }

    return QPoint(0, 0);
}

bool File::setScrollState(const QPoint & coords) {
    //TODO: implement restore on IDocument level
    if (isText()) {
        TextDocument * doc = asText();

        doc -> setHorizontalScrollPos(coords.x());
        doc -> setVerticalScrollPos(coords.y());
        //TODO: need additional update for current doc
        return true;
    }

    return false;
}
