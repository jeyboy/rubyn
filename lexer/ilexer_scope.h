#ifndef ILEXER_SCOPE_H
#define ILEXER_SCOPE_H

#pragma once

enum ILexerScope : int {
    scp_none = 0,
    scp_func_args_init = 1,
    scp_array = 2,
    scp_hash = 3,
};

#endif // ILEXER_SCOPE_H
