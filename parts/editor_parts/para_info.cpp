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

    { QByteArrayLiteral("do"), ParaInfo::pt_open_block },
    { QByteArrayLiteral("class"), ParaInfo::pt_open_class },
    { QByteArrayLiteral("module"), ParaInfo::pt_open_module },

    { QByteArrayLiteral("end"), ParaInfo::pt_close_struct },
};

QHash<PARA_TYPE, PARA_TYPE> ParaInfo::para_opposition = {
    { ParaInfo::pt_open_curly_bracket, ParaInfo::pt_close_curly_bracket },
    { ParaInfo::pt_close_curly_bracket, ParaInfo::pt_open_curly_bracket },
    { ParaInfo::pt_open_square_bracket, ParaInfo::pt_close_square_bracket },
    { ParaInfo::pt_close_square_bracket, ParaInfo::pt_open_square_bracket },
    { ParaInfo::pt_open_round_bracket, ParaInfo::pt_close_round_bracket },
    { ParaInfo::pt_close_round_bracket, ParaInfo::pt_open_round_bracket },

    { ParaInfo::ParaInfo::pt_open_block, ParaInfo::pt_close_struct },
    { ParaInfo::ParaInfo::pt_open_class, ParaInfo::pt_close_struct },
    { ParaInfo::ParaInfo::pt_open_module, ParaInfo::pt_close_struct },

    { ParaInfo::ParaInfo::pt_close_struct, ParaInfo::pt_open_struct },
};
