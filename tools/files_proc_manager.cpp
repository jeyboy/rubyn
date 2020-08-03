#include "files_proc_manager.h"

#include "tools/thread_utils.h"
#include "misc/dir.h"

#include <qdiriterator.h>
#include <qtimer.h>
#include <qdatetime.h>

QString FilesProcManager::temp_path;
QString FilesProcManager::data_path;
QString FilesProcManager::tools_path;

FilesProcManager::FilesProcManager() : cleaner_proc_delay(1800000) { // 1/2 hr
    FilesProcManager::temp_path = Dir::appPath(QLatin1String("temp"), true);
    FilesProcManager::data_path = Dir::appPath(QLatin1String("data"), true);
    FilesProcManager::tools_path = Dir::appPath(QLatin1String("tools"), true);

    clearTemps();
}

QString FilesProcManager::generateRandomName() {
    return QString("temp_") +
        QString::number(QDateTime::currentMSecsSinceEpoch());
}

QString FilesProcManager::tempPath(const QString & path) { return Dir::concatPaths(temp_path, path); }
QString FilesProcManager::toolPath(const QString & tool_name) { return Dir::concatPaths(tools_path, tool_name); }
QString FilesProcManager::dataPath(const QString & path) { return Dir::concatPaths(data_path, path); }

QString FilesProcManager::concatPath(const QString & path, const QString & add) {
    return Dir::concatPaths(path, add);
}

QString FilesProcManager::appPath(const QString & name) {
    return Dir::appPath(name);
}

bool FilesProcManager::saveToFile(const QString & path, QByteArray & content) {
    QFile f(path);

    if (f.open(QFile::WriteOnly)) {
        int res = f.write(content);
        f.close();
        return res != -1;
    }

    return false;
}

void FilesProcManager::cleanerProc() {
    QDirIterator files_it(temp_path, QDir::Files | QDir::Dirs | QDir::Hidden | QDir::NoDotAndDotDot);

    while(files_it.hasNext()) {
        QString path = files_it.next();

        if (!_proc_files.contains(path) || _proc_files[path] != ps_proc) {
            QDir dir(path);

            if (dir.exists())
                dir.removeRecursively();
            else
                QFile(path).remove();
        }
    }
}

void FilesProcManager::clearTemps() {
    ThreadUtils::obj().run(
        this, &FilesProcManager::cleanerProc,
        new Func()
    );

    QTimer::singleShot(cleaner_proc_delay, this, SLOT(clearTemps()));
}
