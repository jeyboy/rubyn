#include "iformat.h"

#include "parts/formats/format_text.h"
#include "parts/formats/format_image.h"
#include "parts/langs/ruby/format_ruby.h"

QHash<QByteArray, FormatType> IFormat::types = {
    { QByteArrayLiteral("rb"), ft_rb },
    { QByteArrayLiteral("sql"), ft_sql },
    { QByteArrayLiteral("html"), ft_html },
    { QByteArrayLiteral("css"), ft_css },
    { QByteArrayLiteral("scss"), ft_scss },
    { QByteArrayLiteral("sass"), ft_sass },
    { QByteArrayLiteral("js"), ft_js },
    { QByteArrayLiteral("xml"), ft_xml },
    { QByteArrayLiteral("json"), ft_json },
    { QByteArrayLiteral("erb"), ft_erb },
    { QByteArrayLiteral("haml"), ft_haml },
    { QByteArrayLiteral("slim"), ft_slim },
    { QByteArrayLiteral("yml"), ft_yml },

//    { QByteArrayLiteral("c"), ft_c },
//    { QByteArrayLiteral("h"), ft_h },
//    { QByteArrayLiteral("cpp"), ft_cpp },
//    { QByteArrayLiteral("cs"), ft_cs },
//    { QByteArrayLiteral("pas"), ft_pas },
//    { QByteArrayLiteral("java"), ft_java },
//    { QByteArrayLiteral("php"), ft_php },
//    { QByteArrayLiteral("py"), ft_py },
//    { QByteArrayLiteral("vb"), ft_vb },
};

QHash<FormatType, IFormat *> IFormat::formats = {
    { ft_text, &FormatText::obj() },
    { ft_image, &FormatImage::obj() },

    { ft_rb, &FormatRuby::obj() },
};

bool IFormat::determine(const QString & path, IFormat *& iformat) {
    QByteArray ch_arr = path.toUtf8();
    const char * str = ch_arr.constData();
    const char * iter = str, * sub = 0;

    FormatType format_type = ft_unknown;

    while(true) {
        switch(*iter) {
            case '.': {
                if (sub) IDENT_FORMAT(iter, sub, format_type);

                sub = iter + 1;
            break;}

            case 0: {
                if (sub) IDENT_FORMAT(iter, sub, format_type);

                goto exit;
            }

            default:;
        }

        ++iter;
    }

    exit:
        iformat = formats[format_type];

        return iformat && format_type == ft_unknown;
}
