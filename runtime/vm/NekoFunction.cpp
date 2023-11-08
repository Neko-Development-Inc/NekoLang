#include "NekoFunction.h"

#include "../ops/NekoOp.h"
#include "../runtime.h"

using namespace ops;

namespace vm {

    void NekoFunction::init(Runtime r) {
        instructions.emplace_back(&r.getImpl(NOP));
        instructions.emplace_back(&r.getImpl(RETURN));
    }

    void NekoFunction::execute(const Runtime& r) {
//        const auto opsNOP = ops[NOP];
//        const auto opsRETURN = ops[RETURN];
        for (NekoOp* op : instructions) {
            op->execute(r);
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