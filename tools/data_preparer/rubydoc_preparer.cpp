#include "rubydoc_preparer.h"

#include "tools/web_manager/web_manager.h"

RubyDocPreparer::RubyDocPreparer() {

}

void RubyDocPreparer::prepare(const QString & version) {
    Web::Manager * manager = Web::Manager::prepare();



//    manager -> sendGet()
}

void RubyDocPreparer::responseReady(Web::Response * response) {

}
