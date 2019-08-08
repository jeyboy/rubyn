#include "archive.h"

#include "misc/dir.h"
#include "tools/thread_utils.h"
#include "tools/files_proc_manager.h"
#include "controls/logger.h"

#include <qregularexpression.h>
#include <qstringbuilder.h>
#include <qfile.h>

QString Archive::store_ext = QLatin1Literal("pup");
QStringList Archive::supported_formats;

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
    if (Archive::supported_formats.isEmpty())
        Archive::supported_formats = supportedUncompressFormats();
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

QString Archive::buildDecompressCmd(const QString & path, const QString & target_folder) {
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
            LStr(" e \"") % path % LStr("\" -y -o\"") %
            FilesProcManager::obj().tempPath(target_folder) % LStr("\"");
    #else

    #endif
}

QStringList Archive::supportedUncompressFormats() {
    QString output;
    QStringList list;

    if (runCmd(buildAvailableFormatsCmd(), output)) {
        QStringList lines = output.split(LStr("\r\n"));
        bool in_list = false;

        QRegularExpression regex(QLatin1Literal("\\b([a-z.()]+)\\b"));

        for(QStringList::Iterator entry = lines.begin(); entry != lines.end(); entry++) {
            if (in_list) {
                if ((*entry).isEmpty())
                    break;



                QRegularExpressionMatchIterator match_it = regex.globalMatch((*entry));

                while (match_it.hasNext()) {
                    QRegularExpressionMatch match = match_it.next();
                    QString captured = match.captured(1);
                    int y = 0;
                }
            } else {
                in_list = (*entry) == LStr("Formats:");
            }
        }
    }

    return list;
}

bool Archive::runCmd(const QString & cmd, QString & output) {
    QProcess * proc = new QProcess(qApp);

//    connect(proc, SIGNAL(started()), this, SLOT(begin()));
//    connect(proc, SIGNAL(readyReadStandardError()), this, SLOT(hasError()));
//    connect(proc, SIGNAL(readyReadStandardOutput()), this, SLOT(hasOutput()));
//    connect(proc, SIGNAL(finished(int)), this, SLOT(done(int)));
//    connect(proc, SIGNAL(errorOccurred(QProcess::ProcessError)), this, SLOT(errorOccurred(QProcess::ProcessError)));

    Logger::info(LStr("Archive"), LStr("Run proc: ") % cmd);

    proc -> start(cmd);

    if (proc -> state() != QProcess::NotRunning) {
        QEventLoop loop;
        connect(proc, SIGNAL(finished(int)), &loop, SLOT(quit()));
        connect(proc, SIGNAL(errorOccurred(QProcess::ProcessError)), &loop, SLOT(quit()));
        loop.exec();
    }

    output = QString(proc -> readAllStandardOutput());

    return proc -> exitStatus() == QProcess::NormalExit;
}

bool Archive::decompress(const QString & path) {
    Logger::info(LStr("Archive"), LStr("Start unpack: ") % path);

    QString output;
    QString target_folder;
    if (!prepareUniqFolderName(target_folder)) {
        Logger::error(LStr("Archive"), LStr("Can't prepare uniq folder for: ") % path);
        return false;
    }

    QString cmd = buildDecompressCmd(path, target_folder);

    runCmd(cmd, output);

    //        ThreadUtils::obj().run(
    //            this, &ImageBank::procImageCall,
    //            QUrl(orders.takeLast()),
    //            new Func(this, SLOT(pixmapDownloaded(Response*)))
    //        );
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
    QProcess * obj = (QProcess *)sender();
    emit started();

    Logger::info(LStr("Archive"), LStr("Proc is started for ") % obj -> program());
}
void Archive::errorOccurred(QProcess::ProcessError error) {
    QProcess * obj = (QProcess *)sender();
    QByteArray err_msg = obj -> errorString().toUtf8();
    hasStatusData(err_msg, ot_error);
    emit finished(false);

    Logger::error(LStr("Archive"), LStr("Proc has error for ") % obj -> program() % LStr(" ") % err_msg);
}
void Archive::hasError() {
    QProcess * obj = (QProcess *)sender();
    QByteArray err_msg = obj -> errorString().toUtf8();
    hasStatusData(err_msg, ot_error);

    Logger::error(LStr("Archive"), LStr("Proc has error for ") % obj -> program() % LStr(" ") % err_msg);
}
void Archive::hasOutput() {
    QProcess * obj = (QProcess *)sender();
    hasStatusData(obj -> readAllStandardOutput(), ot_data);
}
void Archive::done(int status) {
    QProcess * obj = (QProcess *)sender();
    emit finished(status == 0);

    if (status == 0) {
        Logger::success(LStr("Archive"), LStr("Proc is complete for ") % obj -> program());
    } else {
        QByteArray err_msg = obj -> readAllStandardError();
        if (err_msg.isEmpty())
            err_msg = obj -> errorString().toUtf8();

        Logger::error(LStr("Archive"), LStr("Proc status failed for ") % obj -> program() % LStr(" Reason: ") % err_msg);
    }
}

//QByteArray Archive::errToString(const QProcess::ProcessError & error) {
//    switch(error) {
//        case QProcess::FailedToStart: return QByteArray("Failed to start");
//        case QProcess::Crashed: return QByteArray("Crshed");
//        case QProcess::Timedout: return QByteArray("Timedout");
//        case QProcess::ReadError: return QByteArray("Read error");
//        case QProcess::WriteError: return QByteArray("Write error");
//        case QProcess::UnknownError: return QByteArray("Unknown error");
//    };

//    return QByteArray("Super unknown error");
//}
