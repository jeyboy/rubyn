#include "dir.h"

#include "controls/logger.h"

#include <qapplication.h>
#include <qdir.h>
#include <qprocess.h>
//#include <qfile.h>

bool Dir::hasEntry(const QString & path, const QString & name, const bool & is_folder) {
    if (is_folder) {
        QDir dir(concatPaths(path, name));
        return dir.exists();
    } else {
        QDir dir(path);
        return dir.exists(name);
    }
}

bool Dir::createFolder(const QString & path, const QString & name) {
    QDir dir(path);

    return dir.mkdir(name);
}
bool Dir::createPath(const QString & path, const QString & name) {
    QDir dir(path);

    return dir.mkpath(name);
}

bool Dir::removePath(const QString & path) {
    QFileInfo f(path);

    if (f.isFile()) {
        return QFile::remove(path);
    }

    QDir dir(path);
    return dir.removeRecursively();
}

QString Dir::appPath(const QString & name, const bool & invalidate) {
    QString res = qApp -> applicationDirPath();

    if (!name.isEmpty()) {
        if (invalidate)
            createPath(res, name);

        res = res % '/' % name;
    }

    return res;
}

QString Dir::concatPaths(const QString & path, const QString & name) {
    return path % '/' % name;
}

bool Dir::showInGraphicalShell(const QString & path_in) {
    bool success = false;

    #ifdef Q_OS_WIN
        QStringList args;
        QProcess browser_proc;
        args << "/select," << QDir::toNativeSeparators(path_in);
        success = browser_proc.startDetached("explorer", args);

        if (!success) {
            const QString error = QString::fromLocal8Bit(browser_proc.readAllStandardError());
            Logger::obj().error("showInGraphicalShell", error);
        }
    #elif Q_OS_MAC
        QStringList args;
        QProcess browser_proc;

        args << "-e";
        args << "tell application \"Finder\"";
        args << "-e";
        args << "activate";
        args << "-e";
        args << "select POSIX file \""+path_in+"\"";
        args << "-e";
        args << "end tell";
        success = browser_proc.startDetached("osascript", args);

        if (!success) {
            const QString error = QString::fromLocal8Bit(browser_proc.readAllStandardError());
            Logger::obj().error("showInGraphicalShell", error);
        }
     #elif defined(Q_OS_UNIX) && !defined(Q_OS_MAC)
        QProcess browser_proc;
        QString output;

        browser_proc.start("xdg-mime", QStringList() << "query" << "default" << "inode/directory");
        browser_proc.waitForFinished();
        output = browser_proc.readLine().simplified();

        if (output == "dolphin.desktop" || output == "org.kde.dolphin.desktop") {
            browser_proc.startDetached("dolphin", QStringList() << "--select" << QDir::toNativeSeparators(path_in));
        } else if (output == "nautilus.desktop" || output == "org.gnome.Nautilus.desktop" || output == "nautilus-folder-handler.desktop") {
            browser_proc.startDetached("nautilus", QStringList() << "--no-desktop" << QDir::toNativeSeparators(path_in));
        } else if (output == "caja-folder-handler.desktop") {
            browser_proc.startDetached("caja", QStringList() << "--no-desktop" << QDir::toNativeSeparators(path_in));
        } else if (output == "nemo.desktop") {
            browser_proc.startDetached("nemo", QStringList() << "--no-desktop" << QDir::toNativeSeparators(path_in));
        } else if (output == "kfmclient_dir.desktop") {
            browser_proc.startDetached("konqueror", QStringList() << "--select" << QDir::toNativeSeparators(path_in));
        } else {
            Logger::obj().error("showInGraphicalShell", "Unsupported desktop type: " % output);

            return false;
        }

        if (!success) {
            const QString error = QString::fromLocal8Bit(browser_proc.readAllStandardError());
            Logger::obj().error("showInGraphicalShell", error);
        }
    #endif

//    QString path = QDir::toNativeSeparators(QApplication::applicationDirPath());
//    QDesktopServices::openUrl(QUrl::fromLocalFile(path));

    return success;
}
