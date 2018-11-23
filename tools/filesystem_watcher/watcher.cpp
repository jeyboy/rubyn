#include "watcher.h"

#ifdef Q_OS_WIN
    #include "watcher_win.cpp"
#elif Q_OS_MAC
    #include "watcher_mac.cpp"
#else
    #include "watcher_x11.cpp"
#endif

bool FileSystemWatcher::registerPathProc(qintptr & ptr, const QString & path, const bool & recursive) {
    return
        #ifdef Q_OS_WIN
            WinWatcher::obj()
        #elif Q_OS_MAC
            MacWatcher::obj()
        #else
            X11Watcher::obj()
        #endif
            .registerPath(ptr, path, recursive);
}
void FileSystemWatcher::unregisterPathProc(const qintptr & ptr) {
    #ifdef Q_OS_WIN
        WinWatcher::obj()
    #elif Q_OS_MAC
        MacWatcher::obj()
    #else
        X11Watcher::obj()
    #endif
        .unregisterPath(ptr);
}

FileSystemWatcher::~FileSystemWatcher() {
    clear();
}
