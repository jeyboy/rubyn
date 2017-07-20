#include "iformat.h"

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

bool IFormat::determine(const QString & path, FormatType & format, bool & complex) {
    QByteArray ch_arr = path.toUtf8();
    const char * str = ch_arr.constData();
    const char * iter = str, * sub = 0;

    format = ft_unknown;

    while(true) {
        switch(*iter) {
            case '.': {
                if (sub) IDENT_FORMAT(iter, sub, format, complex);

                sub = iter + 1;
            break;}

            case 0: {
                if (sub) IDENT_FORMAT(iter, sub, format, complex);

                goto exit;
            }

            default:;
        }

        ++iter;
    }

    exit: return format == ft_unknown;
}
