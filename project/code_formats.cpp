#include "code_formats.h"

#include <qstringbuilder.h>

QHash<QString, FormatType> CodeFormats::_formats = {
    { QLatin1Literal("txt"),    ft_file_text },
    { QLatin1Literal("text"),   ft_file_text },
    { QLatin1Literal("plain"),  ft_file_text },
    { QLatin1Literal("rich"),   ft_file_text },


    { QLatin1Literal("xls"),   ft_file_datum },
    { QLatin1Literal("csv"),   ft_file_datum },
    { QLatin1Literal("xlsx"),  ft_file_datum },


    { QLatin1Literal("ico"),    ft_file_ico },


    { QLatin1Literal("svg"),    ft_file_image },
    { QLatin1Literal("png"),    ft_file_image },
    { QLatin1Literal("jpg"),    ft_file_image },
    { QLatin1Literal("jpeg"),   ft_file_image },
    { QLatin1Literal("jfif"),   ft_file_image },
    { QLatin1Literal("tiff"),   ft_file_image },
    { QLatin1Literal("gif"),    ft_file_image },
    { QLatin1Literal("bmp"),    ft_file_image },


    { QLatin1Literal("eot"),    ft_file_font },
    { QLatin1Literal("ttf"),    ft_file_font },
    { QLatin1Literal("otf"),    ft_file_font },
    { QLatin1Literal("woff"),   ft_file_font },
    { QLatin1Literal("woff2"),  ft_file_font },


    { QLatin1Literal("rb"),     ft_file_rb }, // script will open up a console window
    { QLatin1Literal("rbw"),    ft_file_rb }, // script will run, but with no console window
    { QLatin1Literal("rake"),   ft_file_rake },
    { QLatin1Literal("sql"),    ft_file_sql },
    { QLatin1Literal("html"),   ft_file_html },
    { QLatin1Literal("css"),    ft_file_css },
    { QLatin1Literal("xml"),    ft_file_xml },
    { QLatin1Literal("js"),     ft_file_js },
    { QLatin1Literal("coffee"), ft_file_coffee },
    { QLatin1Literal("scss"),   ft_file_scss },
    { QLatin1Literal("sass"),   ft_file_sass },
    { QLatin1Literal("json"),   ft_file_json },
    { QLatin1Literal("erb"),    ft_file_erb },
    { QLatin1Literal("haml"),   ft_file_haml },
    { QLatin1Literal("slim"),   ft_file_slim },


    { QLatin1Literal("lock"),   ft_file_lock },
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

QString CodeFormats::formatIcoPath(const FormatType & ft, const FormatType & add_ft) {
    QString res = QLatin1Literal(":/doc_types/");

    switch(ft) {
        case ft_folder: return res % QLatin1Literal("folder");
        case ft_broken: return res % QLatin1Literal("file_broken");

        case ft_file_image: return res % QLatin1Literal("file_img");
        case ft_file_text: return res % QLatin1Literal("file_txt");
        case ft_file_bin: return res % QLatin1Literal("file_bin");

        case ft_file_rb: return res % QLatin1Literal("file_ruby");
        case ft_file_rake: return res % QLatin1Literal("file_rake");
        case ft_file_sql: return res % QLatin1Literal("file_sql");
        case ft_file_html: {
            switch(add_ft) {
                case ft_file_erb: return res % QLatin1Literal("file_html_erb");
                case ft_file_haml: return res % QLatin1Literal("file_html_haml");
                case ft_file_slim: return res % QLatin1Literal("file_html_slim");
                default: return res % QLatin1Literal("file_html");
            }
        }

        case ft_file_css: {
            switch(add_ft) {
                case ft_file_erb: return res % QLatin1Literal("file_css_erb");
                case ft_file_haml: return res % QLatin1Literal("file_css_haml");
                case ft_file_slim: return res % QLatin1Literal("file_css_slim");
                default: return res % QLatin1Literal("file_css");
            }
        }
        case ft_file_scss: {
            switch(add_ft) {
                case ft_file_erb: return res % QLatin1Literal("file_scss_erb");
                case ft_file_haml: return res % QLatin1Literal("file_scss_haml");
                case ft_file_slim: return res % QLatin1Literal("file_scss_slim");
                default: return res % QLatin1Literal("file_scss");
            }
        }
        case ft_file_sass: {
            switch(add_ft) {
                case ft_file_erb: return res % QLatin1Literal("file_sass_erb");
                case ft_file_haml: return res % QLatin1Literal("file_sass_haml");
                case ft_file_slim: return res % QLatin1Literal("file_sass_slim");
                default: return res % QLatin1Literal("file_sass");
            }
        }

        case ft_file_js: {
            switch(add_ft) {
                case ft_file_erb: return res % QLatin1Literal("file_js_erb");
                case ft_file_haml: return res % QLatin1Literal("file_js_haml");
                case ft_file_slim: return res % QLatin1Literal("file_js_slim");
                default: return res % QLatin1Literal("file_js");
            }
        }
        case ft_file_coffee: {
            switch(add_ft) {
                case ft_file_erb: return res % QLatin1Literal("file_coffee_erb");
                case ft_file_haml: return res % QLatin1Literal("file_coffee_haml");
                case ft_file_slim: return res % QLatin1Literal("file_coffee_slim");
                default: return res % QLatin1Literal("file_coffee");
            }
        }

        case ft_file_xml: return res % QLatin1Literal("file_xml");
        case ft_file_json: return res % QLatin1Literal("file_json");
        case ft_file_yml: return res % QLatin1Literal("file_yml");

        case ft_file_erb: return res % QLatin1Literal("file_erb");
        case ft_file_haml: return res % QLatin1Literal("file_haml");
        case ft_file_slim: return res % QLatin1Literal("file_slim");

        case ft_file_lock: return res % QLatin1Literal("file_lock");
        case ft_file_gemfile: return res % QLatin1Literal("file_gemfile");
        case ft_file_font: return res % QLatin1Literal("file_font");
        case ft_file_log: return res % QLatin1Literal("file_log");
        case ft_file_datum: return res % QLatin1Literal("file_datum");


        case ft_folder_db: return res % QLatin1Literal("folder_db");
        case ft_folder_public: return res % QLatin1Literal("folder_public");
        case ft_folder_log: return res % QLatin1Literal("folder_log");
        case ft_folder_temp: return res % QLatin1Literal("folder_temp");
        case ft_folder_test: return res % QLatin1Literal("folder_test");
        case ft_folder_config: return res % QLatin1Literal("folder_config");
        case ft_folder_app: return res % QLatin1Literal("folder_app");
        case ft_folder_lib: return res % QLatin1Literal("folder_lib");

        default: return res % QLatin1Literal("file_unknown");
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
