#ifndef DOCUMENTS
#define DOCUMENTS

#include <qobject.h>
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
    }
    ~Documents() { qDeleteAll(documents); }
    bool openDocument(const QString & path) {
        if (!documents.contains(path)) {
            QFile * file = new QFile(path);
            if (file -> open(QFile::ReadOnly | QFile::Text)) {
                QString mime = IDocument::extractMime(file -> fileName());

                switch(docTypes.value(mime)) {
                    case doc_type_text: {
                        documents.insert(path, new TextDocument(mime, path, file -> fileName(), file));
                        emit documentAdded(path);
                        emit textDocumentAdded(path);
                    break; }

                    case doc_type_image: {
                        documents.insert(path, new ImageDocument(mime, path, file -> fileName(), file));
                        emit documentAdded(path);
                        emit imageDocumentAdded(path);
                    break; }

                    default: return false;
                }
            }
            else {
                file -> deleteLater();
                return false;
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
