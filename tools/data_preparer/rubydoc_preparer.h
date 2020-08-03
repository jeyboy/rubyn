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

    QString local_core_path;
    QString local_stdlib_path;

    inline bool isValid() { return !core_url.isEmpty() && !stdlib_url.isEmpty(); }

    inline QString coreName() const { return core_url.split('/').last(); }
    inline QString stdlibName() const { return stdlib_url.split('/').last(); }
};

typedef QHash<QString, VersionUrls> DocsList;

class RubyDocPreparer : public IRubyStubsPreparer {
    Q_OBJECT

    inline QString packType() { return QLatin1String("7z"); }
    inline QString versionsDataName() { return QLatin1String("versions"); }
    inline QString rubyPackName(const QString & version, const bool & with_type = true) {
        QString res = QLatin1String("ruby_") % version;

        if (with_type) {
            res = res % '.' % packType();
        }

        return res;
    }

    bool hasPackForVersion(const QString & target_version);
    bool findNearestVersion(const QString & target_version, QString & nearest_res);

    quint64 uVersion(const QString & version);
public:
    RubyDocPreparer();

    bool takeListOfAvailableDocs(DocsList & list);
    bool prepare(const QString & version) override;

public slots:
    void syncList();
    bool prepareVersionPack(const QString & version, VersionUrls & urls);

protected slots:
//    void responseReady(Web::Response *);
};

#endif // RUBYDOC_PREPARER_H
