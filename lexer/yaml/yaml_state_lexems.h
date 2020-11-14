#ifndef YAML_STATE_LEXEMS_H
#define YAML_STATE_LEXEMS_H

#pragma once

#include <qbytearray.h>

#include "misc/defines.h"

namespace Yaml {
    enum StateLexem : LEXEM_TYPE {
        DefaultStateLexems,

        lex_key,

        lex_scalar,
        lex_multiline, // |
        lex_multiline_formating, // >
        lex_list_item, // -

//        my:
//           servers: [dev, prod]

        lex_list_begin, // [
        lex_list_end, // ]
        lex_list_splitter, // ,

//        map1:
//          key1:value1
//          key2:value2

//        map1: {key1=value1, key2=value2}
        lex_map_begin, // {
        lex_map_end, // }
        lex_map_splitter, // ,
        lex_map__key_value_splitter, // =


//        'here''s to "quotes"' => !!str "here's to \"quotes\""
        lex_single_quote,
        lex_double_quote,

        lex_comment, // !

        lex_relation, // &
        lex_pointer, // *

        lex_profile_splitter, // ---
    };
}

#endif // YAML_STATE_LEXEMS_H
