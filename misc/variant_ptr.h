#ifndef VARIANTPTR_H
#define VARIANTPTR_H

#include <qvariant.h>

//MyClass *p;
//QVariant v = VPtr<MyClass>::asQVariant(p);

//MyClass *p1 = VPtr<MyClass>::asPtr(v);

template <class T> class VariantPtr {
public:
    static T * asPtr(const QVariant & v) { return  (T *) v.value<void *>(); }
    static QVariant asQVariant(T * ptr) { return qVariantFromValue((void *) ptr); }
};

#endif // VARIANTPTR_H
