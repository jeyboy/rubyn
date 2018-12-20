#ifndef CODE_FORMATS_H
#define CODE_FORMATS_H

#pragma once

#include <qhash.h>

enum FormatType : quint32 {

    // (1 << 8)

    // ...

    ft_level_four = (1 << 13),
    ft_level_three = (1 << 14), // 256
    ft_level_two = (1 << 15),
    ft_level_one = (1 << 16),

    // ...

    ft_broken = (1 << 23),
    ft_system = (1 << 24),
    ft_datum = (1 << 25),
    ft_folder = (1 << 26),
    ft_image = (1 << 27),
    ft_text = (1 << 28),
    ft_binary = (1 << 29),
    ft_tree = (1 << 30),

    ft_unknown =             0,

    ft_file_rb =             1 | ft_text | ft_level_one,
    ft_file_sql =            2 | ft_text | ft_level_one,
    ft_file_html =           3 | ft_text | ft_level_three,
    ft_file_css =            4 | ft_text | ft_level_three, // ft_level_one
    ft_file_scss =           5 | ft_text | ft_level_one,
    ft_file_sass =           6 | ft_text | ft_level_one,
    ft_file_js =             7 | ft_text | ft_level_four,
    ft_file_coffee =         8 | ft_text | ft_level_one,
    ft_file_xml =            9 | ft_text | ft_level_one,
    ft_file_json =           10 | ft_text | ft_tree | ft_level_one,
    ft_file_erb =            11 | ft_text | ft_level_two,
    ft_file_haml =           12 | ft_text | ft_level_two,
    ft_file_slim =           13 | ft_text | ft_level_two,
    ft_file_yml =            14 | ft_text | ft_level_one,
    ft_file_lock =           15 | ft_text | ft_level_one,
    ft_file_gemfile =        16 | ft_text | ft_level_one,
    ft_file_rake =           17 | ft_text | ft_level_one,


    //        ft_c,
    //        ft_h,
    //        ft_cpp,
    //        ft_cs,
    //        ft_pas,
    //        ft_java,
    //        ft_php,
    //        ft_py,
    //        ft_vb,


    ft_file_ctree =         94 | ft_tree | ft_level_one,
    ft_file_datum =         95 | ft_datum | ft_system | ft_level_one,
    ft_file_bin =           95 | ft_binary | ft_level_one,
    ft_file_text =          96 | ft_text | ft_level_four,
    ft_file_ico =           97 | ft_image | ft_level_one,
    ft_file_image =         98 | ft_image | ft_level_one,
    ft_file_font =          99 | ft_system | ft_level_one,
    ft_file_log =           100 | ft_text | ft_level_one,


    ft_folder_app =         193 | ft_folder,
    ft_folder_config =      194 | ft_folder,
    ft_folder_db =          195 | ft_folder,
    ft_folder_public =      196 | ft_folder,
    ft_folder_log =         197 | ft_folder,
    ft_folder_temp =        198 | ft_folder,
    ft_folder_test =        199 | ft_folder,

    ft_user_defined =       200 | ft_level_four,

    ft_base_file_types =    ft_image | ft_text | ft_binary | ft_tree,
    ft_priority =           ft_level_one | ft_level_two | ft_level_three | ft_level_four
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
