#ifndef DOCUMENTS
#define DOCUMENTS

#include <qurl.h>
#include <qhash.h>
#include <qfile>
#include <qdebug.h>

#include "misc/singleton.h"

#include "parts/documents/idocument.h"
#include "parts/documents/documents_list.h"

class Documents : public QObject, public Singleton<Documents> {
    Q_OBJECT

    QHash<QString, IDocument *> documents;
    QHash<QString, DocumentType> docTypes;
public:
    Documents() {
        docTypes.insert(QStringLiteral("rb"), doc_type_text);
        docTypes.insert(QStringLiteral("h"), doc_type_text);
        docTypes.insert(QStringLiteral("cpp"), doc_type_text);
        docTypes.insert(QStringLiteral("sql"), doc_type_text);
        docTypes.insert(QStringLiteral("c"), doc_type_text);
        docTypes.insert(QStringLiteral("cs"), doc_type_text);
        docTypes.insert(QStringLiteral("html"), doc_type_text);
        docTypes.insert(QStringLiteral("css"), doc_type_text);
        docTypes.insert(QStringLiteral("sass"), doc_type_text);
        docTypes.insert(QStringLiteral("pas"), doc_type_text);
        docTypes.insert(QStringLiteral("java"), doc_type_text);
        docTypes.insert(QStringLiteral("js"), doc_type_text);
        docTypes.insert(QStringLiteral("php"), doc_type_text);
        docTypes.insert(QStringLiteral("py"), doc_type_text);
        docTypes.insert(QStringLiteral("vb"), doc_type_text);
        docTypes.insert(QStringLiteral("xml"), doc_type_text);
        docTypes.insert(QStringLiteral("json"), doc_type_text);
        docTypes.insert(QStringLiteral("erb"), doc_type_text);
        docTypes.insert(QStringLiteral("haml"), doc_type_text);
        docTypes.insert(QStringLiteral("yml"), doc_type_text);
    }
    ~Documents() { qDeleteAll(documents); }
    bool openDocument(const QUrl & url) {
        bool isLocal = url.isLocalFile();
        QString path = isLocal ? url.toLocalFile() : url.toString();


        if (!documents.contains(path)) {
            QString mime;
            QString name;
            QIODevice * device = 0;

            if (url.isLocalFile()) {
                QFile * file = new QFile(path);

                if (file -> open(QFile::ReadOnly | QFile::Text)) {
                    name = file -> fileName();
                    mime = IDocument::extractMime(name);
                    device = file;
                } else {
                    file -> deleteLater();
                    return false;
                }
            } else {
                // proceed remote file
                return false; // but not now ...
            }



            switch(docTypes.value(mime)) {
                case doc_type_text: {
                    documents.insert(path, new TextDocument(mime, path, name, device));
                    emit documentAdded(path);
                    emit textDocumentAdded(path);
                break; }

                case doc_type_image: {
                    documents.insert(path, new ImageDocument(mime, path, name, device));
                    emit documentAdded(path);
                    emit imageDocumentAdded(path);
                break; }

                default: return false;
            }
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
