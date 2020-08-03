#include "code_formats.h"

#include <qstringbuilder.h>

QHash<QString, FormatType> CodeFormats::_formats = {
    { QLatin1String("txt"),    ft_file_text },
    { QLatin1String("text"),   ft_file_text },
    { QLatin1String("plain"),  ft_file_text },
    { QLatin1String("rich"),   ft_file_text },


    { QLatin1String("xls"),   ft_file_datum },
    { QLatin1String("csv"),   ft_file_datum },
    { QLatin1String("xlsx"),  ft_file_datum },


    { QLatin1String("ico"),    ft_file_ico },


    { QLatin1String("svg"),    ft_file_image },
    { QLatin1String("png"),    ft_file_image },
    { QLatin1String("jpg"),    ft_file_image },
    { QLatin1String("jpeg"),   ft_file_image },
    { QLatin1String("jfif"),   ft_file_image },
    { QLatin1String("tiff"),   ft_file_image },
    { QLatin1String("gif"),    ft_file_image },
    { QLatin1String("bmp"),    ft_file_image },


    { QLatin1String("eot"),    ft_file_font },
    { QLatin1String("ttf"),    ft_file_font },
    { QLatin1String("otf"),    ft_file_font },
    { QLatin1String("woff"),   ft_file_font },
    { QLatin1String("woff2"),  ft_file_font },


    { QLatin1String("rb"),     ft_file_rb }, // script will open up a console window
    { QLatin1String("rbw"),    ft_file_rb }, // script will run, but with no console window
    { QLatin1String("rake"),   ft_file_rake },
    { QLatin1String("sql"),    ft_file_sql },
    { QLatin1String("html"),   ft_file_html },
    { QLatin1String("htm"),    ft_file_html },
    { QLatin1String("css"),    ft_file_css },
    { QLatin1String("xml"),    ft_file_xml },
    { QLatin1String("js"),     ft_file_js },
    { QLatin1String("coffee"), ft_file_coffee },
    { QLatin1String("scss"),   ft_file_scss },
    { QLatin1String("sass"),   ft_file_sass },
    { QLatin1String("json"),   ft_file_json },
    { QLatin1String("erb"),    ft_file_erb },
    { QLatin1String("haml"),   ft_file_haml },
    { QLatin1String("slim"),   ft_file_slim },


    { QLatin1String("lock"),   ft_file_lock },
    { QLatin1String("yml"),    ft_file_yml },
    { QLatin1String("log"),    ft_file_log },
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
    QString res = QLatin1String(":/doc_types/");

    switch(ft) {
        case ft_folder: return res % QLatin1String("folder");
        case ft_broken: return res % QLatin1String("file_broken");

        case ft_file_image: return res % QLatin1String("file_img");
        case ft_file_text: return res % QLatin1String("file_txt");
        case ft_file_bin: return res % QLatin1String("file_bin");

        case ft_file_rb: return res % QLatin1String("file_ruby");
        case ft_file_rake: return res % QLatin1String("file_rake");
        case ft_file_sql: return res % QLatin1String("file_sql");
        case ft_file_html: {
            switch(add_ft) {
                case ft_file_erb: return res % QLatin1String("file_html_erb");
                case ft_file_haml: return res % QLatin1String("file_html_haml");
                case ft_file_slim: return res % QLatin1String("file_html_slim");
                default: return res % QLatin1String("file_html");
            }
        }

        case ft_file_css: {
            switch(add_ft) {
                case ft_file_erb: return res % QLatin1String("file_css_erb");
                case ft_file_haml: return res % QLatin1String("file_css_haml");
                case ft_file_slim: return res % QLatin1String("file_css_slim");
                default: return res % QLatin1String("file_css");
            }
        }
        case ft_file_scss: {
            switch(add_ft) {
                case ft_file_erb: return res % QLatin1String("file_scss_erb");
                case ft_file_haml: return res % QLatin1String("file_scss_haml");
                case ft_file_slim: return res % QLatin1String("file_scss_slim");
                default: return res % QLatin1String("file_scss");
            }
        }
        case ft_file_sass: {
            switch(add_ft) {
                case ft_file_erb: return res % QLatin1String("file_sass_erb");
                case ft_file_haml: return res % QLatin1String("file_sass_haml");
                case ft_file_slim: return res % QLatin1String("file_sass_slim");
                default: return res % QLatin1String("file_sass");
            }
        }

        case ft_file_js: {
            switch(add_ft) {
                case ft_file_erb: return res % QLatin1String("file_js_erb");
                case ft_file_haml: return res % QLatin1String("file_js_haml");
                case ft_file_slim: return res % QLatin1String("file_js_slim");
                default: return res % QLatin1String("file_js");
            }
        }
        case ft_file_coffee: {
            switch(add_ft) {
                case ft_file_erb: return res % QLatin1String("file_coffee_erb");
                case ft_file_haml: return res % QLatin1String("file_coffee_haml");
                case ft_file_slim: return res % QLatin1String("file_coffee_slim");
                default: return res % QLatin1String("file_coffee");
            }
        }

        case ft_file_xml: return res % QLatin1String("file_xml");
        case ft_file_json: return res % QLatin1String("file_json");
        case ft_file_yml: return res % QLatin1String("file_yml");

        case ft_file_erb: return res % QLatin1String("file_erb");
        case ft_file_haml: return res % QLatin1String("file_haml");
        case ft_file_slim: return res % QLatin1String("file_slim");

        case ft_file_lock: return res % QLatin1String("file_lock");
        case ft_file_gemfile: return res % QLatin1String("file_gemfile");
        case ft_file_font: return res % QLatin1String("file_font");
        case ft_file_log: return res % QLatin1String("file_log");
        case ft_file_datum: return res % QLatin1String("file_datum");


        case ft_folder_db: return res % QLatin1String("folder_db");
        case ft_folder_public: return res % QLatin1String("folder_public");
        case ft_folder_log: return res % QLatin1String("folder_log");
        case ft_folder_temp: return res % QLatin1String("folder_temp");
        case ft_folder_test: return res % QLatin1String("folder_test");
        case ft_folder_config: return res % QLatin1String("folder_config");
        case ft_folder_app: return res % QLatin1String("folder_app");
        case ft_folder_lib: return res % QLatin1String("folder_lib");

        default: return res % QLatin1String("file_unknown");
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
