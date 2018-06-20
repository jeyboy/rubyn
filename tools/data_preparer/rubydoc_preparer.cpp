#include "rubydoc_preparer.h"

#include "tools/web_manager/web_manager.h"

RubyDocPreparer::RubyDocPreparer() {

}

bool RubyDocPreparer::takeListOfVersions(QStringList & versions) {
    Web::Manager * manager = Web::Manager::prepare();

    QByteArray host("https://ruby-doc.org/");

    Web::RequestParams * params = new Web::RequestParams(
        QUrl(host % QLatin1Literal("downloads/"))
    );

    Html::Page html = manager -> sendGet(params) -> toHtml();

    Html::Set results = html.find("a[href*'rdocs.tgz']");

    qDebug() << "RUBY VERSIONS";


    for(Html::Set::Iterator result = results.begin(); result != results.end(); result++) {
        qDebug() << " -- " << (*result) -> link(&host);
    }

    return !results.isEmpty();
}

void RubyDocPreparer::prepare(const QString & version) {
    Web::Manager * manager = Web::Manager::prepare();

    Web::RequestParams * params = new Web::RequestParams(
        QUrl(QLatin1Literal("https://ruby-doc.org/downloads/"))
    );

//    manager -> sendGet();
}

void RubyDocPreparer::responseReady(Web::Response * response) {

}
