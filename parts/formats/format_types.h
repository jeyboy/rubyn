#ifndef FORMAT_TYPES_H
#define FORMAT_TYPES_H

#pragma once

enum FormatType {
    ft_unknown = 0,

    ft_image = (1 << 0),
    ft_text = (1 << 1),
    ft_bynary = (1 << 2),

    ft_rb = (1 << 3) | ft_text,
    ft_sql = (1 << 4) | ft_text,
    ft_html = (1 << 5) | ft_text,
    ft_css = (1 << 6) | ft_text,
    ft_scss = (1 << 7) | ft_text,
    ft_sass = (1 << 8) | ft_text,
    ft_js = (1 << 9) | ft_text,
    ft_xml = (1 << 10) | ft_text,
    ft_json = (1 << 11) | ft_text,
    ft_erb = (1 << 12) | ft_text,
    ft_haml = (1 << 13) | ft_text,
    ft_slim = (1 << 14) | ft_text,
    ft_yml = (1 << 15) | ft_text,

//        ft_c,
//        ft_h,
//        ft_cpp,
//        ft_cs,
//        ft_pas,
//        ft_java,
//        ft_php,
//        ft_py,
//        ft_vb,

    // COMPLEX

    ft_erhtml = ft_html | ft_erb,
    ft_hahtml = ft_html | ft_haml,
    ft_slhtml = ft_html | ft_slim,

    ft_ercss = ft_css | ft_erb,

    ft_erjs = ft_js | ft_erb,
    ft_hajs = ft_js | ft_haml,
    ft_sljs = ft_js | ft_slim,
};

#endif // FORMAT_TYPES_H
