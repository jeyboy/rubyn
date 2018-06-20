#ifndef VARIANT_CONVERTOR_H
#define VARIANT_CONVERTOR_H

#include "defines.h"

class QVariant;

class VariantConvertor {
public:
    static QString toStr(const QVariant & data);
};

#endif // VARIANT_CONVERTOR_H
