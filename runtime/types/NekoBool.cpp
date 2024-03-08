#include "NekoBool.h"

namespace types {

    bool NekoBool::get() {
        return value;
    }

    void NekoBool::set(bool val) {
        value = val;
    }

    const string NekoBool::TRUE  = "fact";
    const string NekoBool::FALSE = "fake";

}