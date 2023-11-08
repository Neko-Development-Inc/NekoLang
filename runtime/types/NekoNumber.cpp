#include "NekoNumber.h"

namespace types {

    long double NekoNumber::get() {
        return value;
    }

    void NekoNumber::set(long double val) {
        value = val;
    }

    bool NekoNumber::hasDecimals() {
        return value > std::floor(value);
    }

}