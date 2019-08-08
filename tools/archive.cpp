#include "archive.h"

#include "misc/dir.h"
#include "tools/thread_utils.h"
#include "tools/files_proc_manager.h"
#include "controls/logger.h"

#include <qstringbuilder.h>
#include <qfile.h>

QString Archive::store_ext = QLatin1Literal("pup");

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

Archive::Archive() {}

const QString & Archive::storePath() {
    return FilesProcManager::obj().dataPath();
}

bool Archive::decompress(const QString & path, const bool & async) {
    Logger::info(LStr("Archive"), LStr("Start unpack: ") % path);

    QString target_folder;
    if (!prepareUniqFolderName(target_folder)) {
        Logger::error(LStr("Archive"), LStr("Can't prepare uniq folder for: ") % path);
        return false;
    }

    QProcess * proc = new QProcess(qApp);
    proc -> setProperty("proc_path", path);
    proc -> setProperty("folder_name", target_folder);

    connect(proc, SIGNAL(started()), this, SLOT(begin()));
    connect(proc, SIGNAL(readyReadStandardError()), this, SLOT(hasError()));
    connect(proc, SIGNAL(readyReadStandardOutput()), this, SLOT(hasOutput()));
    connect(proc, SIGNAL(finished(int)), this, SLOT(done(int)));
    connect(proc, SIGNAL(errorOccurred(QProcess::ProcessError)), this, SLOT(errorOccurred(QProcess::ProcessError)));

    QString cmd;

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


        cmd = FilesProcManager::obj().toolPath(QLatin1Literal("7za.exe"))
                 % QLatin1Literal(" e \"") % path % QLatin1Literal("\" -y -o\"") % FilesProcManager::obj().tempPath(target_folder) % QLatin1Literal("\"");
    #else

    #endif

    Logger::info(LStr("Archive"), LStr("Run proc: ") % cmd);

    if (!async) {
        proc -> start(cmd);

        if (proc -> state() != QProcess::NotRunning) {
            QEventLoop loop;
            connect(proc, SIGNAL(finished(int)), &loop, SLOT(quit()));
            connect(proc, SIGNAL(errorOccurred(QProcess::ProcessError)), &loop, SLOT(quit()));
            loop.exec();
        }

        return proc -> exitStatus() == QProcess::NormalExit;
    }
    else {
        proc -> start(cmd);
    }

    //        ThreadUtils::obj().run(
    //            this, &ImageBank::procImageCall,
    //            QUrl(orders.takeLast()),
    //            new Func(this, SLOT(pixmapDownloaded(Response*)))
    //        );

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
