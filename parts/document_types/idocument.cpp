#include "idocument.h"
#include "documents_types.h"

IDocument * IDocument::create(const QUrl & url, Project * project) {
    bool isLocal = url.isLocalFile();
    QString path = isLocal ? url.toLocalFile() : url.toString();

    QString name;
    QIODevice * device = 0;
    Lexer * f;

    if (isLocal)
        name = path.section('/', -1, -1);
    else
        name = path;

    bool res = LexerFactory::determine(name, f);

    if (!res) {
        //TODO: ask user about preffered type of file
    }

    FormatType format = f -> format();

    bool is_text = format & ft_text, is_bynary = format & ft_bynary;

    if (is_text || is_bynary) {
        if (isLocal) {
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

        return new TextDocument(path, name, device, project, f);
    }

    if (format & ft_image)
        return new ImageDocument(path, name, device, project, f);

    return 0;
}

IDocument::IDocument(const QString & path, const QString & name, QIODevice * device, Project * project, Lexer * lexer) :
    File(name, path, project), _device(device), _lexer(lexer), fully_readed(true)
{

    QTextOption option =  defaultTextOption();
    option.setFlags(option.flags() | QTextOption::ShowTabsAndSpaces);
//    else
//        option.setFlags(option.flags() & ~QTextOption::ShowTabsAndSpaces);
    option.setFlags(option.flags() | QTextOption::AddSpaceForLineAndParagraphSeparators);
    setDefaultTextOption(option);
}

IDocument::~IDocument() {
    if (_device) {
        if (_device -> isOpen())
            _device -> close();

        delete _device;
    }

    delete _lexer;
}
