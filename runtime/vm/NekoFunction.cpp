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
//        auto retVal = nullptr;
        for (size_t i = 0; i < instructions.size();) {
            auto tmp = i + 0; // ugly hack for false CLion warning
            auto& insn = instructions[i];
            long int next = insn->execute(r, stack, i);
            if (next == -1) {
                // Return from function
                cout << "Return from function\n";
                break;
            }
            if (tmp == i)
                i++;
        }
//        stack.process();
    }

}