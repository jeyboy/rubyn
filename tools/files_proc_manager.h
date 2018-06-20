#ifndef FILES_PROC_MANAGER_H
#define FILES_PROC_MANAGER_H

#include <qurl.h>
#include <qhash.h>

#include "misc/singleton.h"

class FilesProcManager : public QObject, public Singleton<FilesProcManager> {
    Q_OBJECT

    uint cleaner_proc_delay; // ms

    static QString temp_path;
    static QString data_path;
protected:
    FilesProcManager();
    ~FilesProcManager() { _proc_files.clear(); }
    void cleanerProc();
public:
    enum ProcState : uint {
        ps_none = 0,
        ps_proc = 1,
        ps_failed = 2
    };

    static const QString & tempPath() { return temp_path; }
    static const QString & dataPath() { return data_path; }

    inline void registerFileProc(const QUrl & path, const ProcState & state = ps_proc) {
        _proc_files.insert(path, state);
    }
    inline void unregisterFileProc(const QUrl & path) {
        _proc_files.remove(path);
    }

public slots:
    void clearTemps();
private:
    QHash<QUrl, bool> _proc_files;

    friend class Singleton<FilesProcManager>;
};


#endif // FILES_PROC_MANAGER_H
