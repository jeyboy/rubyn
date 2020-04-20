#include "archive.h"

#include "misc/dir.h"
#include "tools/thread_utils.h"
#include "tools/files_proc_manager.h"
#include "controls/logger.h"

#include <qstringbuilder.h>
#include <qfile.h>
#include <qdiriterator.h>

QString Archive::store_ext = QLatin1Literal("pup");
QRegularExpression Archive::supported_formats_reg_exp;
QHash<QString, bool> Archive::all_formats = {
    { "7z", true }, { "bz2", true }, { "bzip2", true }, { "tbz2", true }, { "tbz", true }, { "gz", true },
    { "gzip", true }, { "tgz", true }, { "tar", true }, { "xz", true }, { "txz", true }, { "zip", true },
    { "zipx", true }, { "lzh", true }, { "lha", true }, { "lzma", true },  { "rar", true }, { "r00", true },

//    { "wim", true }, { "swm", true }, { "esd", true }, { "jar", true }, { "xpi", true },  { "rpm", true },
//    { "odt", true }, { "ods", true }, { "docx", true }, { "xlsx", true }, { "epub", true }, { "apm", true },
//    { "ar", true }, { "a", true }, { "deb", true }, { "lib", true }, { "arj", true }, { "cab", true },
//    { "chm", true }, { "chw", true }, { "chi", true }, { "chq", true }, { "msi", true }, { "msp", true },
//    { "doc", true }, { "xls", true }, { "ppt", true }, { "cpio", true }, { "cramfs", true }, { "dmg", true },
//    { "ext", true }, { "ext2", true }, { "ext3", true }, { "ext4", true }, { "img", true }, { "fat", true },
//    { "img", true }, { "hfs", true }, { "hfsx", true }, { "hxs", true }, { "hxi", true }, { "hxr", true },
//    { "hxq", true }, { "hxw", true }, { "lit", true }, { "ihex", true }, { "iso", true }, { "img", true },
//    { "mbr", true }, { "mslz", true }, { "mub", true }, { "nsis", true }, { "ntfs", true }, { "img", true },
//    { "ppmd", true }, { "qcow", true }, { "qcow2", true }, { "qcow2c", true }, { "squashfs", true },
//    { "udf", true }, { "iso", true }, { "img", true }, { "scap", true }, { "uefif", true }, { "vdi", true },
//    { "vhd", true }, { "vmdk", true }, { "xar", true }, { "pkg", true }, { "z", true }, { "taz", true }
};

bool Archive::prepareUniqFolderName(QString & name) {
    name = FilesProcManager::obj().generateRandomName();
    int counter = 0;

    while(true) {
        if (!Dir::hasEntry(FilesProcManager::obj().tempPath(), name, true))
            return true;

        if (++counter > 100)
            return false;

        name = FilesProcManager::obj().generateRandomName();
    }
}

Archive::Archive() {
    if (Archive::supported_formats_reg_exp.pattern().isEmpty())
        Archive::supported_formats_reg_exp = supportedUncompressFormats();
}

const QString & Archive::storePath() {
    return FilesProcManager::obj().dataPath();
}

QString Archive::buildAvailableFormatsCmd() {
    #ifdef Q_OS_WIN
        return FilesProcManager::obj().toolPath(LStr("7za.exe")) % LStr(" i");
    #else

    #endif
}

QString Archive::buildCompressCmd(const QString & path, const QString & result_path) {
    #ifdef Q_OS_WIN
        return FilesProcManager::obj().toolPath(LStr("7za.exe")) %
            LStr(" a \"") % path % LStr("\" -y\"") % result_path % LStr("\"");
    #else

    #endif
}

//7z a archive2.zip .\subdir\*

QString Archive::buildDecompressCmd(const QString & path, const QString & result_path) {
    #ifdef Q_OS_WIN
    //        http://rus-linux.net/MyLDP/consol/7z-command-switches.html

    //        7z x archive.zip -o[how/to/forge] //Extract with full paths
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


    return FilesProcManager::obj().toolPath(LStr("7za.exe")) %
            LStr(" e \"") % path % LStr("\" -y -o\"") % result_path % LStr("\"");
    #else

    #endif
}

QRegularExpression Archive::supportedUncompressFormats() {
    QString output;
    QHash<QString, bool> list;

    if (runCmd(buildAvailableFormatsCmd(), output)) {
        QStringList lines = output.split(LStr("\r\n"));
        bool in_list = false;

        QRegularExpression regex(QLatin1Literal("\\b([a-z0-9.()]+)\\b"));

        for(QStringList::Iterator entry = lines.begin(); entry != lines.end(); entry++) {
            if (in_list) {
                if ((*entry).isEmpty())
                    break;

                QRegularExpressionMatchIterator match_it = regex.globalMatch((*entry));

                while (match_it.hasNext()) {
                    QRegularExpressionMatch match = match_it.next();
                    QString captured = match.captured(1);

                    if (all_formats.contains(captured)) {
                        list.insert(captured, true);
                    }
                }
            } else {
                in_list = (*entry) == LStr("Formats:");
            }
        }
    }

    return QRegularExpression(LStr("\\.(") % list.keys().join('|') % LStr(")"), QRegularExpression::CaseInsensitiveOption);
}

bool Archive::runCmd(const QString & cmd, QString & output) {
    QProcess * proc = new QProcess(qApp);
    proc -> setProperty("cmd", cmd);

    connect(proc, SIGNAL(started()), this, SLOT(begin()));
    connect(proc, SIGNAL(readyReadStandardError()), this, SLOT(hasError()));
//    connect(proc, SIGNAL(readyReadStandardOutput()), this, SLOT(hasOutput()));
    connect(proc, SIGNAL(finished(int)), this, SLOT(done(int)));
    connect(proc, SIGNAL(errorOccurred(QProcess::ProcessError)), this, SLOT(errorOccurred(QProcess::ProcessError)));

    Logger::info(LStr("Archive"), LStr("Run proc: ") % cmd);

    proc -> start(cmd);

    //        ThreadUtils::obj().run(
    //            this, &ImageBank::procImageCall,
    //            QUrl(orders.takeLast()),
    //            new Func(this, SLOT(pixmapDownloaded(Response*)))
    //        );

    if (proc -> state() != QProcess::NotRunning) {
        QEventLoop loop;
        connect(proc, SIGNAL(finished(int)), &loop, SLOT(quit()));
        connect(proc, SIGNAL(errorOccurred(QProcess::ProcessError)), &loop, SLOT(quit()));
        loop.exec();
    }

    output = QString(proc -> readAllStandardOutput());

    return proc -> exitStatus() == QProcess::NormalExit;
}

bool Archive::decompress(const QString & path, QString & result_path) {
    Logger::info(LStr("Archive"), LStr("Start unpack: ") % path);

    QString output;

    if (result_path.isEmpty()) {
        QString target_folder;

        if (!prepareUniqFolderName(target_folder)) {
            Logger::error(LStr("Archive"), LStr("Can't prepare uniq folder for: ") % path);
            return false;
        }
        result_path = FilesProcManager::obj().tempPath(target_folder);
    }

    QHash<QString, QString> proc_files { { buildDecompressCmd(path, result_path), path } };
    bool in_inner_loop = false;

    while (!proc_files.isEmpty()) {
        QString key = proc_files.keys().first();
        QString origin_file = proc_files.take(key);

        if (runCmd(key, output)) {
            if (in_inner_loop) {
                QFile(origin_file).remove();
            }

            in_inner_loop = true;
            QDirIterator files_it(result_path, QDir::Files | QDir::NoDotAndDotDot);

            while(files_it.hasNext()) {
                QString file_path = files_it.next();

                if (file_path.contains(supported_formats_reg_exp)) {
                    proc_files.insert(buildDecompressCmd(file_path, result_path), file_path);
                }
            }
        }
        else {
            if (!in_inner_loop)
                return false;
        }
    }

    return true;
}

bool Archive::load(const QString & name, QByteArray & buf) {
    QFile file(storePath() % '/' % name % '.' % store_ext);

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    buf = qUncompress(file.readAll());

    file.close();

    return true;
}

bool Archive::save(const QString & name, const QByteArray & buf) {
    QFile file(storePath() % '/' % name % '.' % store_ext);

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    file.write(qCompress(buf, 9));

    file.close();
    return true;
}


void Archive::begin() {
    QProcess * obj = static_cast<QProcess *>(sender());
    emit started();

    Logger::info(LStr("Archive"), LStr("Proc is started for ") % obj -> property("cmd").toByteArray());
}
void Archive::errorOccurred(QProcess::ProcessError) {
    QProcess * obj = static_cast<QProcess *>(sender());
    QByteArray err_msg = obj -> errorString().toUtf8();
    hasStatusData(err_msg, ot_error);
    emit finished(false);

    Logger::error(LStr("Archive"), LStr("Proc has error for ") % obj -> property("cmd").toByteArray() % LStr(" ") % err_msg);
}
void Archive::hasError() {
    QProcess * obj = static_cast<QProcess *>(sender());
    QByteArray err_msg = obj -> errorString().toUtf8();
    hasStatusData(err_msg, ot_error);

    Logger::error(LStr("Archive"), LStr("Proc has error for ") % obj -> property("cmd").toByteArray() % LStr(" ") % err_msg);
}
void Archive::hasOutput() {
    QProcess * obj = static_cast<QProcess *>(sender());
    hasStatusData(obj -> readAllStandardOutput(), ot_data);
}
void Archive::done(int status) {
    QProcess * obj = static_cast<QProcess *>(sender());
    emit finished(status == 0);

    if (status == 0) {
        Logger::success(LStr("Archive"), LStr("Proc is complete for ") % obj -> property("cmd").toByteArray());
    } else {
        QByteArray err_msg = obj -> readAllStandardError();
        if (err_msg.isEmpty())
            err_msg = obj -> errorString().toUtf8();

        Logger::error(LStr("Archive"), LStr("Proc status failed for ") % obj -> property("cmd").toByteArray() % LStr(" Reason: ") % err_msg);
    }
}
