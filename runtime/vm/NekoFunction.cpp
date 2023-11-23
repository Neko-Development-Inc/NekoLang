#include "NekoFunction.h"

#include "../ops/NekoOp.h"
#include "../runtime.h"

using namespace ops;

namespace vm {

    void NekoFunction::init(Runtime* r) {
        instructions.emplace_back(&r->getImpl(NOP));
        instructions.emplace_back(&r->getImpl(RETURN));
    }

    void NekoFunction::execute(Runtime* r) {
        NekoStack stack;
        // TODO: If non-static (instanced),
        //  add `self/this` to top of Stack
//        const auto opsNOP = ops[NOP];
//        const auto opsRETURN = ops[RETURN];
        for (NekoOp* op : instructions) {
            op->execute(r, &stack);
//            short opcode = op->opcode;
//            if (opcode == opsNOP) {
//                if (auto nop = dynamic_cast<NekoOpNop*>(op))
//                    nop->execute(r);
//            } else if (opcode == opsRETURN) {
//                if (auto ret = dynamic_cast<NekoOpReturn*>(op))
//                    ret->execute(r);
//            }
        }
    }

}