#ifndef SCOPE_TYPES_H
#define SCOPE_TYPES_H

#pragma once

enum ScopeType {
    sct_none = 0,
    sct_global,
    sct_module,
    sct_class,
    sct_instance,
    sct_local
};

#endif // SCOPE_TYPES_H
