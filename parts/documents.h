#ifndef DOCUMENTS
#define DOCUMENTS

#include "misc/singleton.h"
#include "parts/document_types/idocument.h"

class Documents : public QObject, public Singleton<Documents> {
    Q_OBJECT

    QHash<QUrl, IDocument *> documents;
public:
    Documents() {}
    ~Documents() { qDeleteAll(documents); }

    bool openDocument(const QUrl & url) {
        if (!documents.contains(url)) {
            IDocument * doc = IDocument::create(url);
            if (doc) {
                documents.insert(url, doc);
                emit documentAdded(url);

                if (doc -> isText())
                    emit textDocumentAdded(url);
                else if (doc -> isImage())
                    emit imageDocumentAdded(url);
            }
            else return false;
        }

        return true;
    }

    IDocument * document(const QUrl & url) { return documents.value(url, 0); }


signals:
    void documentAdded(const QUrl & path);
    void textDocumentAdded(const QUrl & path);
    void imageDocumentAdded(const QUrl & path);
    void documentRemoved(const QUrl & path);
    void documentRenamed(const QUrl & fromPath, const QUrl & toPath);
};

#endif // DOCUMENTS
