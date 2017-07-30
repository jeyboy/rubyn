#ifndef SCOPE_ITEM_TYPES_H
#define SCOPE_ITEM_TYPES_H

#pragma once

enum ScopeItemType {
    sct_none = 0,
    sct_global,
    sct_module,
    sct_class,
    sct_instance,
    sct_local
};

#endif // SCOPE_ITEM_TYPES_H
