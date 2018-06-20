#include "rubydoc_preparer.h"

#include "tools/web_manager/web_manager.h"

RubyDocPreparer::RubyDocPreparer() {

}

bool RubyDocPreparer::prepare(const QString & version) {
    Web::Manager * manager = Web::Manager::prepare();

    manager -> sendGet()
}
