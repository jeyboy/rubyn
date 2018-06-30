#ifndef LEXEM_MEAN_TYPE_H
#define LEXEM_MEAN_TYPE_H

#pragma once

enum LexerMeanType : uint {
    lmt_unknow = 0,
    lmt_const,
    lmt_private_const,
    lmt_global_method,
    lmt_global_var,
    lmt_private_instance_method,
    lmt_instance_method,
    lmt_instance_var,
    lmt_local_var,
    lmt_private_obj_method,
    lmt_obj_method,
    lmt_obj_var,
    lmt_template
};

#endif // LEXEM_MEAN_TYPE_H
