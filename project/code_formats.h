#ifndef CODE_FORMATS_H
#define CODE_FORMATS_H

#pragma once

#include <qhash.h>

enum FormatType : quint16 {
    ft_primary = (1 << 9), // 512
    ft_secondary = (1 << 10),
    ft_third = (1 << 11),

    ft_folder = (1 << 12),
    ft_image = (1 << 13),
    ft_text = (1 << 14),
    ft_binary = (1 << 15),

    ft_unknown =             0 | ft_third,

    ft_file_rb =             1 | ft_text | ft_primary,
    ft_file_sql =            2 | ft_text | ft_primary,
    ft_file_html =           3 | ft_text | ft_third,
    ft_file_css =            4 | ft_text | ft_primary,
    ft_file_scss =           5 | ft_text | ft_primary,
    ft_file_sass =           6 | ft_text | ft_primary,
    ft_file_js =             7 | ft_text | ft_primary,
    ft_file_xml =            8 | ft_text | ft_primary,
    ft_file_json =           9 | ft_text | ft_primary,
    ft_file_erb =            10 | ft_text | ft_secondary,
    ft_file_haml =           11 | ft_text | ft_secondary,
    ft_file_slim =           12 | ft_text | ft_secondary,
    ft_file_yml =            13 | ft_text | ft_primary,

    //        ft_c,
    //        ft_h,
    //        ft_cpp,
    //        ft_cs,
    //        ft_pas,
    //        ft_java,
    //        ft_php,
    //        ft_py,
    //        ft_vb,

    ft_file_log =           200 | ft_text,


    ft_folder_db =          395 | ft_folder,
    ft_folder_public =      396 | ft_folder,
    ft_folder_log =         397 | ft_folder,
    ft_folder_temp =        398 | ft_folder,
    ft_folder_test =        399 | ft_folder,

    ft_user_defined =       400,

    ft_base_file_types =    ft_image | ft_text | ft_binary,
    ft_priority =           ft_primary | ft_secondary | ft_third
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
