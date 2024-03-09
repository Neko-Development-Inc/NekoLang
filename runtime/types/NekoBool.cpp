#include "NekoBool.h"

bool types::NekoBool::get() {
    return value;
}

void types::NekoBool::set(bool val) {
    value = val;
}

const string types::NekoBool::TRUE  = "fact";
const string types::NekoBool::FALSE = "fake";