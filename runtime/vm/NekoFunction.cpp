#include "NekoFunction.h"

namespace vm {

    void NekoFunction::init(Runtime& r) {
        instructions.emplace_back(&r.getImpl(NOP));
        instructions.emplace_back(&r.getImpl(RETURN));
    }

    void NekoFunction::execute(Runtime& r) {
        NekoStack stack;
        // TODO: If non-static (instanced),
        //  add `self/this` to top of Stack
        for (NekoOp* op : instructions) {
            op->execute(r, stack);
        }
    }

}