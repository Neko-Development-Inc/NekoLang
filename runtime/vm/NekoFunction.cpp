#include "NekoFunction.h"

namespace vm {

    void NekoFunction::init(Runtime& r) {
        instructions.emplace_back(r.createImplT(NOP));
        instructions.emplace_back(r.createImplT(NUMBER, 123));
        instructions.emplace_back(r.createImplT(STRING, "hello"));
        instructions.emplace_back(r.createImplT(CONCAT));
        instructions.emplace_back(r.createImplT(OUT));
    }

    void NekoFunction::execute(Runtime& r) {
        NekoStack stack;
        // TODO: If non-static (instanced),
        //  add `self/this` to top of Stack
        for (auto& op : instructions) {
            op->execute(r, stack);
            op->debugArguments();
        }
    }

}