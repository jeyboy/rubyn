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
    FilesProcManager::temp_path = Dir::appPath(QLatin1Literal("temp"), true);
    FilesProcManager::data_path = Dir::appPath(QLatin1Literal("data"), true);
    FilesProcManager::tools_path = Dir::appPath(QLatin1Literal("tools"), true);

    clearTemps();
}

QString FilesProcManager::generateRandomName() {
    return QString("temp_") +
            QString::number(QDateTime::currentMSecsSinceEpoch());
}

QString FilesProcManager::tempPath(const QString & path) { return Dir::concatPaths(temp_path, path); }
QString FilesProcManager::toolPath(const QString & tool_name) { return Dir::concatPaths(tools_path, tool_name); }

QString FilesProcManager::appPath(const QString & name) {
    return Dir::appPath(name);
}

void FilesProcManager::cleanerProc() {
    QDirIterator files_it(temp_path, QDir::Files | QDir::Dirs | QDir::Hidden);

    while(files_it.hasNext()) {
        QString path = files_it.next();

        if (!_proc_files.contains(path)) {
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
