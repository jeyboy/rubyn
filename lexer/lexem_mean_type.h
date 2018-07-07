#ifndef LEXEM_MEAN_TYPE_H
#define LEXEM_MEAN_TYPE_H

#pragma once

#include <qglobal.h>

enum LexerMeanType : quint16 {
    lmt_unknow = 0,

    lmt_core = 1,

    lmt_public = 2,
    lmt_protected = 4,
    lmt_private = 8,

    lmt_local = 16,
    lmt_global = 32,
    lmt_instance = 64,
    lmt_object = 128,

    lmt_var = 256,
    lmt_method = 512,
    lmt_class = 1024,
    lmt_const = 2048,
    lmt_template = 4096,

    lmt_private_const = lmt_const | lmt_private,

    lmt_global_method = lmt_global | lmt_method,
    lmt_private_instance_method = lmt_private | lmt_instance | lmt_method,
    lmt_instance_method = lmt_instance | lmt_method,
    lmt_private_obj_method = lmt_private | lmt_object | lmt_method,
    lmt_object_method = lmt_object | lmt_method,

    lmt_global_var = lmt_global | lmt_var,
    lmt_instance_var = lmt_instance | lmt_var,
    lmt_local_var = lmt_local | lmt_var,
    lmt_object_var = lmt_object | lmt_var,
};

#endif // LEXEM_MEAN_TYPE_H
