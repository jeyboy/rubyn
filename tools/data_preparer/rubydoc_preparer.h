#ifndef RUBYDOC_PREPARER_H
#define RUBYDOC_PREPARER_H

#include "iruby_stubs_preparer.h"

//http://doc.qt.io/qt-5/qprocess.html#start

//https://sevenzip.osdn.jp/chm/cmdline/commands/extract.htm
//https://sevenzip.osdn.jp/chm/cmdline/commands/
//https://sevenzip.osdn.jp/chm/cmdline/commands/extract_full.htm

namespace Web {
    class Response;
}

struct VersionUrls {
    static QString core_type;
    static QString stdlib_type;

    QString core_url;
    QString stdlib_url;

    bool isValid() { return !core_url.isEmpty() && !stdlib_url.isEmpty(); }
};

typedef QHash<QString, VersionUrls> DocsList;

class RubyDocPreparer : public IRubyStubsPreparer {
    Q_OBJECT

    inline QString versionsDataName() { return QLatin1Literal("versions"); }
    inline QString rubyPackName(const QString & version) { return QLatin1Literal("ruby_stubs_") % version; }

    void unpackRubyPack(const QByteArray & buf);

    void downloadRubyPacks(const VersionUrls & urls);
    bool findNearestVersion(const QString & target_version, const DocsList & available_versions, QString & nearest_res);
    quint64 uVersion(const QString & version);
public:
    RubyDocPreparer();

    void parseRubyPack(const VersionUrls & urls);

    bool takeListOfAvailableDocs(DocsList & list);

    void prepare(const QString & version);

protected slots:
    void responseReady(Web::Response *);
};

#endif // RUBYDOC_PREPARER_H
