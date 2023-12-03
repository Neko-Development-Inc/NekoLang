#include "runtime.h"

namespace runtime {

    void Runtime::init() {
        impls.emplace(ops[NOP], std::make_unique<NekoOpNop>());
        impls.emplace(ops[POP], std::make_unique<NekoOpPop>());
        impls.emplace(ops[POP_N], std::make_unique<NekoOpPop>());
        impls.emplace(ops[RETURN], std::make_unique<NekoOpReturn>());
    }

} // runtime