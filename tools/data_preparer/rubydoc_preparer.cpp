#include "rubydoc_preparer.h"

#include "tools/web_manager/web_manager.h"
#include "tools/files_proc_manager.h"

#include "tools/json/json.h"
#include "tools/json/json_obj.h"

#include "tools/fuzzy_comparison.h"
#include "tools/archive.h"
#include "controls/logger.h"

#include "misc/dir.h"

#include "rubydoc_parser.h"

#include <qregularexpression.h>

QString VersionUrls::core_type(QLatin1Literal("core"));
QString VersionUrls::stdlib_type(QLatin1Literal("stdlib"));

RubyDocPreparer::RubyDocPreparer() {}

bool RubyDocPreparer::takeListOfAvailableDocs(DocsList & list) {
    Web::Manager * manager = Web::Manager::prepare();

    QByteArray host("https://ruby-doc.org/");

//    Web::RequestParams * params = new Web::RequestParams(
//        QUrl(host % QLatin1Literal("downloads/"))
//    );

    Web::RequestParams * params = new Web::RequestParams(
        QUrl::fromLocalFile("F://rubyn test//Ruby-Doc.org  Documenting the Ruby Language.htm")
    );

    Html::Page html = manager -> sendGet(params) -> toHtml();

    Html::Set results = html.find("a[href*'rdocs.tgz']");

    if (!results.isEmpty()) {
        Json cache;
        JsonObj cache_obj = cache.obj();

        for(Html::Set::Iterator result = results.begin(); result != results.end(); result++) {
            QString href = (*result) -> link(&host);

            QRegularExpression re("ruby((_\\d+)+)([_\\w]+)?_([\\w]+)_rdocs", QRegularExpression::CaseInsensitiveOption);
            QRegularExpressionMatch match = re.match(href);

            if (match.hasMatch()) {
                QString version(match.capturedRef(1).mid(1).toString());
                version.replace('_', '.');

                if (!list.contains(version)) {
                    cache_obj.insert(version, QJsonObject());
                    list.insert(version, VersionUrls());
                }

                VersionUrls & ver_urls = list[version];

//                match.capturedRef(3).mid(1); // if presents then we have preview

                QStringRef url_type = match.capturedRef(4);

                if (url_type == VersionUrls::core_type) {
                    ver_urls.core_url = href;
                    cache_obj.obj(version).insert(VersionUrls::core_type, href);
                } else if (url_type == VersionUrls::stdlib_type) {
                    ver_urls.stdlib_url = href;
                    cache_obj.obj(version).insert(VersionUrls::stdlib_type, href);
                } else
                    Logger::error(
                        QLatin1Literal("RubyDocPreparer"), QLatin1Literal("Unknown link type: ") %
                            url_type % QLatin1Literal("for href: ") % href
                    );
            }
        }

        qDebug() << "JSON" << cache.toJsonStr();

        Archive::save(
            versionsDataName(),
            cache.toJsonStr()
        );
    }

    return !list.isEmpty();
}

bool RubyDocPreparer::prepare(const QString & version) {
    if (Dir::hasEntry(FilesProcManager::dataPath(), rubyPackName(version, false)))
        return true;

    Archive ar;

    QString output_path = FilesProcManager::dataPath(rubyPackName(version, false));

    return ar.decompress(
        FilesProcManager::dataPath(rubyPackName(version)),
        output_path
    );



//    QByteArray buf;

//    if (Archive::load(rubyPackName(version), buf)) {
//        unpackRubyPack(buf);
//        return;
//    }

//    if (Archive::load(versionsDataName(), buf)) {
//        Json versions = Json::fromJsonStr(buf);

//        JsonObj ver_obj = versions.obj();

//        if (ver_obj.contains(version)) {
//            VersionUrls urls;

//            urls.core_url = ver_obj.string(VersionUrls::core_type);
//            urls.stdlib_url = ver_obj.string(VersionUrls::stdlib_type);

//            if (urls.isValid())
//                downloadRubyPack(urls);
//            else
//                Logger::error(
//                    QLatin1Literal("RubyDocPreparer"),
//                    QLatin1Literal("Corrupted links data for ruby version: ") % version
//                );
//        } else {

//        }
//    }

//    DocsList list;

//    if (takeListOfAvailableDocs(list)) {
//        if (list.contains(version)) {
//            downloadRubyPack(list[version]);
//        } else {
//            Logger::error(
//                QLatin1Literal("RubyDocPreparer"),
//                QLatin1Literal("Can find data for ruby version: ") % version
//            );

//            QString nearest_version;

//            if (findNearestVersion(version, list, nearest_version)) {
//                Logger::info(
//                    QLatin1Literal("RubyDocPreparer"),
//                    QLatin1Literal("Finded nearest version: ") % nearest_version
//                );

//                prepare(nearest_version);
//            } else {
//                Logger::error(
//                    QLatin1Literal("RubyDocPreparer"),
//                    QLatin1Literal("Cant find acceptable version for: ") % version
//                );
//            }
//        }
//    }
}

void RubyDocPreparer::syncList() {
    DocsList res;

    if (RubyDocPreparer().takeListOfAvailableDocs(res)) {
        for(DocsList::Iterator it = res.begin(); it != res.end(); it++) {
            VersionUrls urls = it.value();

            prepareVersionPack(it.key(), urls);
        }
    }
}

bool RubyDocPreparer::prepareVersionPack(const QString & version, VersionUrls & urls) {
    qDebug() << "!!!!!!!!!!!prepareVersionPack" << version;

    if (hasPackForVersion(version)) {
        qDebug() << "!!!!!!!!!!! hasPackForVersion" << version;
        return true;
    }

    RubydocParser parser;
    Archive ar;

    /////////////////////// DOWNLOAD //////////////////////////
    Web::Manager * manager = Web::Manager::prepare();

    {
        Web::RequestParams * params = new Web::RequestParams(QUrl(urls.core_url));
        QByteArray core_data = manager -> sendGet(params) -> toBytes();
        delete params;

        urls.local_core_path = FilesProcManager::tempPath(urls.coreName());
        FilesProcManager::saveToFile(urls.local_core_path, core_data);
    }


    {
        Web::RequestParams * params = new Web::RequestParams(QUrl(urls.stdlib_url));
        QByteArray lib_data = manager -> sendGet(params) -> toBytes();
        delete params;

        urls.local_stdlib_path = FilesProcManager::tempPath(urls.stdlibName());
        FilesProcManager::saveToFile(urls.local_stdlib_path, lib_data);
    }

    /////////////////////// UNZIP //////////////////////////

    QString result_path;
    ar.decompress(urls.local_core_path, result_path);
    Dir::removePath(urls.local_core_path);

    QString result_path2;
    ar.decompress(urls.local_stdlib_path, result_path2);
    Dir::removePath(urls.local_stdlib_path);

    /////////////////////// PARSE //////////////////////////

    parser.parse(result_path);
    parser.parse(result_path2);

    QString parsed_data_path = FilesProcManager::dataPath(rubyPackName(version, false));
    parser.saveParsedDatum(parsed_data_path);

    Dir::removePath(result_path);
    Dir::removePath(result_path2);

    /////////////////////// PACK //////////////////////////

    bool compress_res = ar.compress(
        FilesProcManager::concatPath(parsed_data_path, "*"),
        FilesProcManager::dataPath(rubyPackName(version))
    );

    Dir::removePath(parsed_data_path);

    return compress_res;
}

bool RubyDocPreparer::hasPackForVersion(const QString & target_version) {
    return Dir::hasEntry(FilesProcManager::dataPath(), rubyPackName(target_version));
}

bool RubyDocPreparer::findNearestVersion(const QString & target_version, QString & nearest_res) {
    quint64 target_uversion = uVersion(target_version);

    quint64 nearest_uversion = 0;
    QByteArray buf;

    if (Archive::load(versionsDataName(), buf)) {
        Json versions = Json::fromJsonStr(buf);

        JsonObj ver_obj = versions.obj();

        if (ver_obj.contains(target_version)) {
            nearest_res = target_version;

            return true;
//            VersionUrls urls;

//            urls.core_url = ver_obj.string(VersionUrls::core_type);
//            urls.stdlib_url = ver_obj.string(VersionUrls::stdlib_type);

//            if (urls.isValid())
//                downloadRubyPack(urls);
//            else
//                Logger::error(
//                    QLatin1Literal("RubyDocPreparer"),
//                    QLatin1Literal("Corrupted links data for ruby version: ") % version
//                );
        } else {
            for(JsonObj::ConstIterator it = ver_obj.constBegin(); it != ver_obj.constEnd(); it++) {
                quint64 uversion = uVersion(it.key());

                if (uversion > nearest_uversion && uversion <= target_uversion) {
                    nearest_uversion = uversion;
                    nearest_res = it.key();
                }
            }
        }
    }

    return nearest_uversion > 0;
}

quint64 RubyDocPreparer::uVersion(const QString & version) {
    QStringList parts = version.split('.');

    QString res('1');

    for(QStringList::Iterator it = parts.begin(); it != parts.end(); it++) {
        res = res % (*it).leftJustified(3, '0');
    }

    return res.toULongLong();
}

//void RubyDocPreparer::responseReady(Web::Response * response) {

//}
