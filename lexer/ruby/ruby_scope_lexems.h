#ifndef RUBY_SCOPE_LEXEMS_H
#define RUBY_SCOPE_LEXEMS_H

#pragma once

#include "misc/defines.h"

namespace Ruby {
    enum ScopeLexem : SCOPE_TYPE {
        DefaultScopeLexems,
        slex_method_vars = 1,
        slex_method_args,
        slex_lambda_params,
        slex_block_params,
        slex_hash,
        slex_array,
    };
}

#endif // RUBY_SCOPE_LEXEMS_H
