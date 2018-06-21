#include "archive.h"

#include "tools/thread_utils.h"
#include "tools/files_proc_manager.h"

#include <qstringbuilder.h>
#include <qfile.h>
#include <qprocess.h>

QString Archive::store_path;
QString Archive::store_ext = QLatin1Literal("pup");

Archive::Archive() {
    Archive::store_path = FilesProcManager::obj().dataPath();
}

void Archive::decompress(const QString & path) {
    #ifdef Q_OS_WIN
        QProcess c(qApp);

//        7z x archive.zip  //Extract with full paths
//        7z t archive.zip *.doc -r // tests *.doc files in archive archive.zip. // use * for all files testing
//               -ai (Include archives)
//               -an (Disable parsing of archive_name)
//               -ao (Overwrite mode)
//               -ax (Exclude archives)
//               -i (Include)
//               -m (Method)
//               -o (Set Output Directory)
//               -p (Set Password)
//               -r (Recurse)
//               -si (use StdIn)
//               -sni (Store NT security information)
//               -sns (Store NTFS alternate Streams)
//               -so (use StdOut)
//               -spf (Use fully qualified file paths)
//               -t (Type of archive)
//               -x (Exclude)
//               -y (Assume Yes on all queries)

//        7z i // info about supported formats
//        7z l archive.zip // list of files in archive
//               -ai (Include archives)
//               -an (Disable parsing of archive_name)
//               -ax (Exclude archives)
//               -i (Include)
//               -slt (Show technical information)
//               -sns (Store NTFS alternate Streams)
//               -p (Set Password)
//               -r (Recurse)
//               -t (Type of archive)
//               -x (Exclude)

        QString cmd = FilesProcManager::obj().appPath(QLatin1Literal("tools/7za.exe"));

        c.start(cmd % QLatin1Literal(" e \"") % path % QLatin1Literal("\" -y "));


//        ThreadUtils::obj().run(
//            this, &ImageBank::procImageCall,
//            QUrl(orders.takeLast()),
//            new Func(this, SLOT(pixmapDownloaded(Response*)))
//        );

    #else

    #endif
}

bool Archive::load(const QString & name, QByteArray & buf) {
    QFile file(store_path % '/' % name % '.' % store_ext);

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    buf = qUncompress(file.readAll());

    file.close();

    return true;
}

bool Archive::save(const QString & name, const QByteArray & buf) {
    QFile file(store_path % '/' % name % '.' % store_ext);

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    file.write(qCompress(buf, 9));

    file.close();
    return true;
}
