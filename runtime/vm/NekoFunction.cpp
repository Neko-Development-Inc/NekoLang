#include "NekoFunction.h"

namespace vm {

    void NekoFunction::init(Runtime& r) {
        instructions.emplace_back(r.createImplT(NOP));
        instructions.emplace_back(r.createImplT(STRING, " a "));
        instructions.emplace_back(r.createImplT(NUMBER, 1));
        instructions.emplace_back(r.createImplT(STRING, " b "));
        instructions.emplace_back(r.createImplT(NUMBER, 2));
        instructions.emplace_back(r.createImplT(STRING, " c "));
        instructions.emplace_back(r.createImplT(NUMBER, 3));
        instructions.emplace_back(r.createImplT(STRING, " d "));
        instructions.emplace_back(r.createImplT(NUMBER, 4));
        instructions.emplace_back(r.createImplT(CONCAT_ALL));
        instructions.emplace_back(r.createImplT(DUP));
        instructions.emplace_back(r.createImplT(CONCAT_ALL));
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
    }

}