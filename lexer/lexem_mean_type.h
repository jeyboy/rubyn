#ifndef LEXEM_MEAN_TYPE_H
#define LEXEM_MEAN_TYPE_H

#pragma once

#include <qglobal.h>

enum LexerMeanType : quint16 {
    lmt_unknow = 0,

    lmt_public = 1,
    lmt_protected = 2,
    lmt_private = 4,

    lmt_local = 8,
    lmt_global = 16,
    lmt_instance = 32,
    lmt_object = 64,

    lmt_var = 128,
    lmt_method = 256,
    lmt_class = 512,
    lmt_const = 1024,
    lmt_template = 2048,

    lmt_private_const = lmt_const | lmt_private,

    lmt_global_method = lmt_global | lmt_method,
    lmt_private_instance_method = lmt_private | lmt_instance | lmt_method,
    lmt_instance_method = lmt_instance | lmt_method,
    lmt_private_obj_method = lmt_private | lmt_object | lmt_method,
    lmt_obj_method = lmt_object | lmt_method,

    lmt_global_var = lmt_global | lmt_var,
    lmt_instance_var = lmt_instance | lmt_var,
    lmt_local_var = lmt_local | lmt_var,
    lmt_object_var = lmt_object | lmt_var,
};

#endif // LEXEM_MEAN_TYPE_H
