#include "para_info.h"

QHash<QByteArray, PARA_TYPE> ParaInfo::para_tokens = {
    { QByteArrayLiteral("{"), ParaInfo::pt_open_curly_bracket },
    { QByteArrayLiteral("}"), ParaInfo::pt_close_curly_bracket },
    { QByteArrayLiteral("["), ParaInfo::pt_open_square_bracket },
    { QByteArrayLiteral("]"), ParaInfo::pt_close_square_bracket },
    { QByteArrayLiteral("("), ParaInfo::pt_open_round_bracket },
    { QByteArrayLiteral(")"), ParaInfo::pt_close_round_bracket },
//    { QByteArrayLiteral("<"), ParaInfo::pt_open_angle_bracket },
//    { QByteArrayLiteral(">"), ParaInfo::pt_close_angle_bracket },

    { QByteArrayLiteral("do"), ParaInfo::pt_open_do_block },
    { QByteArrayLiteral("begin"), ParaInfo::pt_open_begin_block },
    { QByteArrayLiteral("def"), ParaInfo::pt_open_method },
    { QByteArrayLiteral("class"), ParaInfo::pt_open_class },
    { QByteArrayLiteral("module"), ParaInfo::pt_open_module },

    { QByteArrayLiteral("if"), ParaInfo::pt_open_if },
    { QByteArrayLiteral("unless"), ParaInfo::pt_open_unless },
    { QByteArrayLiteral("case"), ParaInfo::pt_open_case },
    { QByteArrayLiteral("while"), ParaInfo::pt_open_while },
    { QByteArrayLiteral("until"), ParaInfo::pt_open_until },
    { QByteArrayLiteral("for"), ParaInfo::pt_open_for },

    { QByteArrayLiteral("end"), ParaInfo::pt_close_struct },
};

QHash<PARA_TYPE, PARA_TYPE> ParaInfo::para_opposition = {
    { ParaInfo::pt_open_curly_bracket, ParaInfo::pt_close_curly_bracket },
    { ParaInfo::pt_close_curly_bracket, ParaInfo::pt_open_curly_bracket },
    { ParaInfo::pt_open_square_bracket, ParaInfo::pt_close_square_bracket },
    { ParaInfo::pt_close_square_bracket, ParaInfo::pt_open_square_bracket },
    { ParaInfo::pt_open_round_bracket, ParaInfo::pt_close_round_bracket },
    { ParaInfo::pt_close_round_bracket, ParaInfo::pt_open_round_bracket },

    { ParaInfo::ParaInfo::pt_open_do_block, ParaInfo::pt_close_struct },
    { ParaInfo::ParaInfo::pt_open_method, ParaInfo::pt_close_struct },
    { ParaInfo::ParaInfo::pt_open_class, ParaInfo::pt_close_struct },
    { ParaInfo::ParaInfo::pt_open_module, ParaInfo::pt_close_struct },

    { ParaInfo::ParaInfo::pt_open_if, ParaInfo::pt_close_struct },
    { ParaInfo::ParaInfo::pt_open_unless, ParaInfo::pt_close_struct },
    { ParaInfo::ParaInfo::pt_open_case, ParaInfo::pt_close_struct },
    { ParaInfo::ParaInfo::pt_open_while, ParaInfo::pt_close_struct },
    { ParaInfo::ParaInfo::pt_open_until, ParaInfo::pt_close_struct },
    { ParaInfo::ParaInfo::pt_open_for, ParaInfo::pt_close_struct },

    { ParaInfo::ParaInfo::pt_close_struct, ParaInfo::pt_open_struct },
};
