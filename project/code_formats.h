#ifndef CODE_FORMATS_H
#define CODE_FORMATS_H

#pragma once

#include <qhash.h>

enum FormatType : quint16 {
    ft_image = (1 << 13), // 8192
    ft_text = (1 << 14),
    ft_binary = (1 << 15),

    ft_unknown = 0,

    ft_rb =             1 | ft_text,
    ft_sql =            2 | ft_text,
    ft_html =           3 | ft_text,
    ft_css =            4 | ft_text,
    ft_scss =           5 | ft_text,
    ft_sass =           6 | ft_text,
    ft_js =             7 | ft_text,
    ft_xml =            8 | ft_text,
    ft_json =           9 | ft_text,
    ft_erb =            10 | ft_text,
    ft_haml =           11 | ft_text,
    ft_slim =           12 | ft_text,
    ft_yml =            13 | ft_text,

    //        ft_c,
    //        ft_h,
    //        ft_cpp,
    //        ft_cs,
    //        ft_pas,
    //        ft_java,
    //        ft_php,
    //        ft_py,
    //        ft_vb,

    ft_log =            999 | ft_text,

    ft_user_defined =   1000,

    ft_base = ft_image | ft_text | ft_binary
};

class CodeFormats {
    static QHash<QString, FormatType> _formats;
    static QHash<QString, FormatType> _user_mappings;
public:
    static FormatType identify(const QString & ext);

    static void addMappings(const QString & ext, const FormatType & format);
    static void removeMappings(const QString & ext);

    static void loadMappings();
    static void saveMappings();
};

#endif // CODE_FORMATS_H
