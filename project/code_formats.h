#ifndef CODE_FORMATS_H
#define CODE_FORMATS_H

#pragma once

#include <qhash.h>

enum FormatType : quint16 {
    ft_folder = (1 << 12), // 4096
    ft_image = (1 << 13),
    ft_text = (1 << 14),
    ft_binary = (1 << 15),

    ft_unknown = 0,

    ft_file_rb =             1 | ft_text,
    ft_file_sql =            2 | ft_text,
    ft_file_html =           3 | ft_text,
    ft_file_css =            4 | ft_text,
    ft_file_scss =           5 | ft_text,
    ft_file_sass =           6 | ft_text,
    ft_file_js =             7 | ft_text,
    ft_file_xml =            8 | ft_text,
    ft_file_json =           9 | ft_text,
    ft_file_erb =            10 | ft_text,
    ft_file_haml =           11 | ft_text,
    ft_file_slim =           12 | ft_text,
    ft_file_yml =            13 | ft_text,

    //        ft_c,
    //        ft_h,
    //        ft_cpp,
    //        ft_cs,
    //        ft_pas,
    //        ft_java,
    //        ft_php,
    //        ft_py,
    //        ft_vb,

    ft_file_log =           500 | ft_text,


    ft_folder_public =      996 | ft_folder,
    ft_folder_log =         997 | ft_folder,
    ft_folder_temp =        998 | ft_folder,
    ft_folder_test =        999 | ft_folder,

    ft_user_defined =       1000,

    ft_base_file_types = ft_image | ft_text | ft_binary
};

class CodeFormats {
    static QHash<QString, FormatType> _formats;
    static QHash<QString, FormatType> _user_mappings;
public:
    static FormatType identify(const QString & ext);
    static QString formatIcoPath(const FormatType & ft);

    static void addMappings(const QString & ext, const FormatType & format);
    static void removeMappings(const QString & ext);

    static void loadMappings();
    static void saveMappings();
};

#endif // CODE_FORMATS_H
