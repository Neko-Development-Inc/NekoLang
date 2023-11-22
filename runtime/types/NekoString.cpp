#include "NekoString.h"

namespace types {

    string NekoString::get() {
        return value;
    }

    void NekoString::set(string val) {
        value = val;
    }

}