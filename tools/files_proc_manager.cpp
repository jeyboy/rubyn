#include "files_proc_manager.h"

#include "tools/thread_utils.h"
#include "misc/dir.h"

#include <qdiriterator.h>
#include <qtimer.h>

QString FilesProcManager::temp_path;
QString FilesProcManager::data_path;

FilesProcManager::FilesProcManager() : cleaner_proc_delay(1800000) { // 1/2 hr
    FilesProcManager::temp_path = Dir::appPath(QLatin1Literal("temp"), true);
    FilesProcManager::data_path = Dir::appPath(QLatin1Literal("data"), true);

    clearTemps();
}

void FilesProcManager::cleanerProc() {
    QDirIterator files_it(temp_path, QDir::Files | QDir::Hidden);

    while(files_it.hasNext()) {
        QString path = files_it.next();

        if (!_proc_files.contains(path)) {
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
