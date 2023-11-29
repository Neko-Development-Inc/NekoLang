#include "runtime.h"

namespace runtime {

    void Runtime::init() {
        impls.emplace(ops[NOP], std::make_unique<NekoOpNop>(ops[NOP]));
        impls.emplace(ops[RETURN], std::make_unique<NekoOpReturn>(ops[RETURN]));
    }

    NekoOp& Runtime::getImpl(short op) {
        return *impls[ops[op]];
    }

} // runtime