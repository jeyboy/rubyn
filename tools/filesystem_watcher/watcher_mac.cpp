#include "watcher.h"

namespace {   
    class MacWatcher : public QWidget, public RelSingleton<MacWatcher> {
        public:
            MacWatcher() {}
            ~MacWatcher() {}

            bool registerPath(qintptr & id, const QString & path, const bool & recursive) {}
            void unregisterPath(const qintptr & ptr) {}
    };
}
