#include "NekoFunction.h"

namespace vm {

    void NekoFunction::init(Runtime& r) {
        instructions.emplace_back(r.createImplT(
            NOP,
            "Hello", 123, true
        ));
        instructions.emplace_back(r.createImplT(
            RETURN,
            123, 456, string("World"), false
        ));
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