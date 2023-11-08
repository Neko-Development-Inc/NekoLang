#include "runtime.h"

using namespace ops;

namespace runtime {

    void Runtime::init() {
        auto* nop = new NekoOpNop(ops[NOP]);
        impls[nop->opcode] = nop;

        auto* ret = new NekoOpReturn(ops[RETURN]);
        impls[ret->opcode] = ret;
    }

    NekoOp& Runtime::getImpl(short op) {
        return *impls[ops[op]];
    }

} // runtime