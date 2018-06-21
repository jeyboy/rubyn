#include "rubydoc_preparer.h"

#include "tools/web_manager/web_manager.h"
#include "tools/files_proc_manager.h"

#include "tools/json/json.h"
#include "tools/json/json_obj.h"

#include "tools/fuzzy_comparison.h"
#include "tools/archive.h"
#include "controls/logger.h"

#include <qregularexpression.h>

QString VersionUrls::core_type(QLatin1Literal("core"));
QString VersionUrls::stdlib_type(QLatin1Literal("stdlib"));

RubyDocPreparer::RubyDocPreparer() {}

bool RubyDocPreparer::takeListOfAvailableDocs(DocsList & list) {
    Web::Manager * manager = Web::Manager::prepare();

    Web::RequestParams * params = new Web::RequestParams(
        QUrl::fromLocalFile("F://rubyn test//Ruby-Doc.org  Documenting the Ruby Language.htm")
    );

//    QByteArray host("https://ruby-doc.org/");

//    Web::RequestParams * params = new Web::RequestParams(
//        QUrl(host % QLatin1Literal("downloads/"))
//    );

    Html::Page html = manager -> sendGet(params) -> toHtml();

    Html::Set results = html.find("a[href*'rdocs.tgz']");

    if (!results.isEmpty()) {
        Json cache;

        for(Html::Set::Iterator result = results.begin(); result != results.end(); result++) {
            QString href = (*result) -> link(/*&host*/);

            QRegularExpression re("ruby((_\\d+)+)([_\\w]+)_rdocs", QRegularExpression::CaseInsensitiveOption);
            QRegularExpressionMatch match = re.match(href);

            if (match.hasMatch()) {
                QString version(match.capturedRef(1).mid(1).toString());
                version.replace('_', '.');

                qDebug() << version;

                if (!list.contains(version)) {
                    list.insert(version, VersionUrls());
                }

                VersionUrls & ver_urls = list[version];

                QStringRef url_type = match.capturedRef(3).mid(1);

                if (url_type == VersionUrls::core_type)
                    ver_urls.core_url = href;
                else if (url_type == VersionUrls::stdlib_type)
                    ver_urls.stdlib_url = href;
                else
                    Logger::obj().write(
                        QLatin1Literal("RubyDocPreparer"), QLatin1Literal("Unknown link type: ") %
                            url_type % QLatin1Literal("for href: ") % href,
                        Logger::log_error
                    );
            }
        }

        Archive::save(
            versionsDataName(),
            cache.toJsonStr()
        );
    }

    return !list.isEmpty();
}

void RubyDocPreparer::prepare(const QString & version) {
    QByteArray buf;

    if (Archive::load(rubyPackName(version), buf)) {
        unpackRubyPack(buf);
        return;
    }

    if (Archive::load(versionsDataName(), buf)) {
        Json versions = Json::fromJsonStr(buf);

        JsonObj ver_obj = versions.obj();

        if (ver_obj.contains(version)) {
            VersionUrls urls;

            urls.core_url = ver_obj.string(VersionUrls::core_type);
            urls.stdlib_url = ver_obj.string(VersionUrls::stdlib_type);

            if (urls.isValid())
                downloadAndParsePacks(urls);
            else
                Logger::obj().write(
                    QLatin1Literal("RubyDocPreparer"),
                    QLatin1Literal("Corrupted links data for ruby version: ") % version,
                    Logger::log_error
                );
        }
    }

    DocsList list;

    if (takeListOfAvailableDocs(list)) {
        if (list.contains(version)) {
            downloadAndParsePacks(list[version]);
        } else {
            Logger::obj().write(
                QLatin1Literal("RubyDocPreparer"),
                QLatin1Literal("Can find data for ruby version: ") % version,
                Logger::log_error
            );

            QString nearest_version;

            if (findNearestVersion(version, list, nearest_version)) {
                Logger::obj().write(
                    QLatin1Literal("RubyDocPreparer"),
                    QLatin1Literal("Finded nearest version: ") % nearest_version
                );

                prepare(nearest_version);
            } else {
                Logger::obj().write(
                    QLatin1Literal("RubyDocPreparer"),
                    QLatin1Literal("Cant find acceptable version for: ") % version,
                    Logger::log_error
                );
            }
        }
    }
}

void RubyDocPreparer::downloadAndParsePacks(const VersionUrls & urls) {

}

bool RubyDocPreparer::findNearestVersion(const QString & target_version, const DocsList & available_versions, QString & nearest_res) {
    QVector<QStringRef> parts = target_version.splitRef('.');

    QString pattern = parts.takeFirst() % buildPatternPart(parts, 1);

    qDebug() << "PATTERN: " << pattern;

    QRegularExpression r(pattern);

    int score = 0;

    for(DocsList::ConstIterator it = available_versions.cbegin(); it != available_versions.cend(); it++) {
        QRegularExpressionMatch match = r.match(it.key());

        int i = 0;

        if (match.hasMatch()) {
            int val_score = match.capturedLength();

            if (val_score > score) {
                score = val_score;
                nearest_res = it.key();
            }
        }
    }
}

QString RubyDocPreparer::buildPatternPart(QVector<QStringRef> & parts, int index) {
    return '(' % parts[index] % (index + 1 < parts.length() ? buildPatternPart(parts, index + 1) : QString()) % ')' % '?';
}

void RubyDocPreparer::unpackRubyPack(const QByteArray & buf) {

}

void RubyDocPreparer::responseReady(Web::Response * response) {

}
