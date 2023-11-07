#include "runtime.h"

namespace runtime {

    void Runtime::init() {
        ops::NekoOpNop nop(NOP);
        impls[NOP] = &nop;

        ops::NekoOpReturn ret(RETURN);
        impls[RETURN] = &ret;
    }

} // runtime