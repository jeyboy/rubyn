#include "code_formats.h"

QHash<QString, FormatType> CodeFormats::_formats = {
    { QLatin1Literal("txt"), ft_text },
    { QLatin1Literal("rb"), ft_rb },
    { QLatin1Literal("sql"), ft_sql },
    { QLatin1Literal("html"), ft_html },
    { QLatin1Literal("css"), ft_css },
    { QLatin1Literal("xml"), ft_xml },
    { QLatin1Literal("js"), ft_js },
    { QLatin1Literal("scss"), ft_scss },
    { QLatin1Literal("sass"), ft_sass },
    { QLatin1Literal("json"), ft_json },
    { QLatin1Literal("erb"), ft_erb },
    { QLatin1Literal("haml"), ft_haml },
    { QLatin1Literal("slim"), ft_slim },
    { QLatin1Literal("yml"), ft_yml },
    { QLatin1Literal("log"), ft_log },
};

QHash<QString, FormatType> CodeFormats::_user_mappings;

FormatType CodeFormats::identify(const QString & ext) {
    QString ext_lower = ext.toLower();

    if (_user_mappings.contains(ext_lower)) {
        return _user_mappings.value(ext_lower);
    }
    else return _formats.value(ext_lower, ft_unknown);
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
