#include "code_formats.h"

#include <qstringbuilder.h>

QHash<QString, FormatType> CodeFormats::_formats = {
    { QLatin1Literal("txt"),    ft_text },
    { QLatin1Literal("rb"),     ft_file_rb },
    { QLatin1Literal("sql"),    ft_file_sql },
    { QLatin1Literal("html"),   ft_file_html },
    { QLatin1Literal("css"),    ft_file_css },
    { QLatin1Literal("xml"),    ft_file_xml },
    { QLatin1Literal("js"),     ft_file_js },
    { QLatin1Literal("scss"),   ft_file_scss },
    { QLatin1Literal("sass"),   ft_file_sass },
    { QLatin1Literal("json"),   ft_file_json },
    { QLatin1Literal("erb"),    ft_file_erb },
    { QLatin1Literal("haml"),   ft_file_haml },
    { QLatin1Literal("slim"),   ft_file_slim },
    { QLatin1Literal("yml"),    ft_file_yml },
    { QLatin1Literal("log"),    ft_file_log },
};

QHash<QString, FormatType> CodeFormats::_user_mappings;

FormatType CodeFormats::identify(const QString & ext) {
    QString ext_lower = ext.toLower();

    if (_user_mappings.contains(ext_lower)) {
        return _user_mappings.value(ext_lower);
    }
    else return _formats.value(ext_lower, ft_unknown);
}

QString CodeFormats::formatIcoPath(const FormatType & ft) {
    QString res = QLatin1Literal(":/doc_types/");

    switch(ft) {
        case ft_unknown: return res %  QLatin1Literal("file_unknown");

        case ft_folder: return res %  QLatin1Literal("folder");

        case ft_image: return res %  QLatin1Literal("file_img");
        case ft_text: return res %  QLatin1Literal("file_txt");
        case ft_binary: return res %  QLatin1Literal("file_bin");

        case ft_file_rb: return res %  QLatin1Literal("file_ruby");
        case ft_file_sql: return res %  QLatin1Literal("file_sql");
        case ft_file_html: return res %  QLatin1Literal("file_html");

        case ft_file_css: return res %  QLatin1Literal("file_css");
        case ft_file_scss: return res %  QLatin1Literal("file_scss");
        case ft_file_sass: return res %  QLatin1Literal("file_sass");

        case ft_file_js: return res %  QLatin1Literal("file_js");

        case ft_file_xml: return res %  QLatin1Literal("file_xml");
        case ft_file_json: return res %  QLatin1Literal("file_json");
        case ft_file_erb: return res %  QLatin1Literal("file_erb");
        case ft_file_haml: return res %  QLatin1Literal("file_haml");
        case ft_file_slim: return res %  QLatin1Literal("file_slim");
        case ft_file_yml: return res %  QLatin1Literal("file_yml");
        case ft_file_log: return res %  QLatin1Literal("file_log");

        case ft_folder_public: return res %  QLatin1Literal("folder_public");
        case ft_folder_log: return res %  QLatin1Literal("folder_log");
        case ft_folder_temp: return res %  QLatin1Literal("folder_temp");
        case ft_folder_test: return res %  QLatin1Literal("folder_test");
    }
}

void CodeFormats::addMappings(const QString & ext, const FormatType & format) {
    _user_mappings[ext] = format;
}
void CodeFormats::removeMappings(const QString & ext) {
    _user_mappings.remove(ext);
}

void CodeFormats::loadMappings() {

}
void CodeFormats::saveMappings() {

}
