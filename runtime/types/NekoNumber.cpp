#include "NekoNumber.h"

namespace types {

    _NekoNumberType_ NekoNumber::get() {
        return value;
    }

    void NekoNumber::set(_NekoNumberType_ val) {
        value = val;
    }

    bool NekoNumber::hasDecimals() {
        return value > std::floor(value);
    }

}