#ifndef SCOPE_ITEM_TYPES_H
#define SCOPE_ITEM_TYPES_H

#pragma once

#define SIT(v) (ScopeItemType)(v)

enum ScopeItemType {
    sct_none = 0,
    sct_global = (1 << 0),
    sct_module = (1 << 1),
    sct_class = (1 << 2),
    sct_instance = (1 << 3),
    sct_local = (1 << 4)
};

#endif // SCOPE_ITEM_TYPES_H
