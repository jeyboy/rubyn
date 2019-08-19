#ifndef CODE_FORMATS_H
#define CODE_FORMATS_H

#pragma once

#include <qhash.h>

enum FormatType : quint32 {

    // (1 << 14)

    // ...

    ft_level_three = (1 << 17),
    ft_level_two = (1 << 18),
    ft_level_one = (1 << 19),

    // ...

    ft_broken = (1 << 23),
    ft_system = (1 << 24),
    ft_datum = (1 << 25),
    ft_folder = (1 << 26),
    ft_image = (1 << 27),
    ft_text = (1 << 28),
    ft_binary = (1 << 29),
    ft_tree = (1 << 30),


//    https://www.ruby-toolbox.com/categories/template_engines
//    https://github.com/rtomayko/tilt/

    ft_unknown =             0,

    ft_file_erb =            1 | ft_text | ft_level_two,
    ft_file_haml =           2 | ft_text | ft_level_two,
    ft_file_slim =           3 | ft_text | ft_level_two,


    ft_file_rb =             10 | ft_text | ft_level_one,
    ft_file_sql =            20 | ft_text | ft_level_one,
    ft_file_html =           30 | ft_text | ft_level_one,
    ft_file_css =            40 | ft_text | ft_level_one,
    ft_file_scss =           50 | ft_text | ft_level_one,
    ft_file_sass =           60 | ft_text | ft_level_one,
    ft_file_js =             70 | ft_text | ft_level_one,
    ft_file_coffee =         80 | ft_text | ft_level_one,
    ft_file_xml =            90 | ft_text | ft_level_one,
    ft_file_json =           100 | ft_tree | ft_level_one,
    ft_file_yml =            110 | ft_text | ft_level_one,
    ft_file_lock =           120 | ft_text | ft_level_one,
    ft_file_gemfile =        130 | ft_text | ft_level_one,
    ft_file_rake =           140 | ft_text | ft_level_one,

    //        ft_c,
    //        ft_h,
    //        ft_cpp,
    //        ft_cs,
    //        ft_pas,
    //        ft_java,
    //        ft_php,
    //        ft_py,
    //        ft_vb,


    ft_file_ctree =         500 | ft_tree | ft_level_one,
    ft_file_datum =         510 | ft_datum | ft_system | ft_level_one,
    ft_file_bin =           520 | ft_binary | ft_level_one,
    ft_file_text =          530 | ft_text | ft_level_three,
    ft_file_ico =           540 | ft_image | ft_level_one,
    ft_file_image =         550 | ft_image | ft_level_one,
    ft_file_font =          560 | ft_system | ft_level_one,
    ft_file_log =           570 | ft_text | ft_level_one,


    ft_folder_lib =         800 | ft_folder,
    ft_folder_app =         810 | ft_folder,
    ft_folder_config =      820 | ft_folder,
    ft_folder_db =          830 | ft_folder,
    ft_folder_public =      840 | ft_folder,
    ft_folder_log =         850 | ft_folder,
    ft_folder_temp =        860 | ft_folder,
    ft_folder_test =        870 | ft_folder,

    ft_user_defined =       8000 | ft_level_three,

    ft_base_file_types =    ft_image | ft_text | ft_binary | ft_tree,
    ft_priority =           ft_level_one | ft_level_two | ft_level_three
};

class CodeFormats {
    static QHash<QString, FormatType> _formats;
    static QHash<QString, FormatType> _user_mappings;
public:
    static FormatType identify(const QString & ext);
    static QString formatIcoPath(const FormatType & ft, const FormatType & add_ft = ft_unknown);

    static void addMappings(const QString & ext, const FormatType & format);
    static void removeMappings(const QString & ext);

    static void loadMappings();
    static void saveMappings();
};

#endif // CODE_FORMATS_H
