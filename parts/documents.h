#ifndef DOCUMENTS
#define DOCUMENTS

#include <qurl.h>
#include <qhash.h>
#include <qfile>
#include <qdebug.h>

#include "misc/singleton.h"
#include "parts/document_types/idocument.h"

class Documents : public QObject, public Singleton<Documents> {
    Q_OBJECT

    QHash<QString, IDocument *> documents;
//    QHash<QString, DocumentType> docTypes;
public:
    Documents() {
//        docTypes.insert(QStringLiteral("rb"), doc_type_text);
//        docTypes.insert(QStringLiteral("h"), doc_type_text);
//        docTypes.insert(QStringLiteral("cpp"), doc_type_text);
//        docTypes.insert(QStringLiteral("sql"), doc_type_text);
//        docTypes.insert(QStringLiteral("c"), doc_type_text);
//        docTypes.insert(QStringLiteral("cs"), doc_type_text);
//        docTypes.insert(QStringLiteral("html"), doc_type_text);
//        docTypes.insert(QStringLiteral("css"), doc_type_text);
//        docTypes.insert(QStringLiteral("sass"), doc_type_text);
//        docTypes.insert(QStringLiteral("pas"), doc_type_text);
//        docTypes.insert(QStringLiteral("java"), doc_type_text);
//        docTypes.insert(QStringLiteral("js"), doc_type_text);
//        docTypes.insert(QStringLiteral("php"), doc_type_text);
//        docTypes.insert(QStringLiteral("py"), doc_type_text);
//        docTypes.insert(QStringLiteral("vb"), doc_type_text);
//        docTypes.insert(QStringLiteral("xml"), doc_type_text);
//        docTypes.insert(QStringLiteral("json"), doc_type_text);
//        docTypes.insert(QStringLiteral("erb"), doc_type_text);
//        docTypes.insert(QStringLiteral("haml"), doc_type_text);
//        docTypes.insert(QStringLiteral("yml"), doc_type_text);
    }
    ~Documents() { qDeleteAll(documents); }

    bool openDocument(const QUrl & url) {
        bool isLocal = url.isLocalFile();
        QString path = isLocal ? url.toLocalFile() : url.toString();

        if (!documents.contains(path)) {
            QString name;
            QIODevice * device = 0;

            if (isLocal) {
                QFile * file = new QFile(path);

                if (file -> open(QFile::ReadOnly | QFile::Text)) {
                    name = path.section('/', -1, -1);
                    device = file;
                } else {
                    file -> deleteLater();
                    return false;
                }
            } else {
                //TODO: proceed remote file
                return false; // but not now ...
            }

            IDocument * doc = IDocument::create(path, name, device);
            if (doc) {
                documents.insert(path, doc);
                emit documentAdded(path);

                if (doc -> isText())
                    emit textDocumentAdded(path);
                else if (doc -> isImage())
                    emit imageDocumentAdded(path);
            }
            else return false;
        }

        return true;
    }

    IDocument * document(const QString & path) { return documents.value(path, 0); }


signals:
    void documentAdded(const QString & path);
    void textDocumentAdded(const QString & path);
    void imageDocumentAdded(const QString & path);
    void documentRemoved(const QString & path);
    void documentRenamed(const QString & fromPath, const QString & toPath);
};

#endif // DOCUMENTS
