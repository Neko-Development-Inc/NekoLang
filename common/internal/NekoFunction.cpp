#include "NekoFunction.h"

namespace vm {

    void NekoFunction::init(Runtime& r) {

        addInsn(r.createImplT(NOP));

        addLabel(r.createImplT(LABEL, "start"));
        addInsn(r.createImplT(JUMP, "end"));

        addInsn(r.createImplT(STRING, "hello world"));
        addInsn(r.createImplT(OUT));

        addLabel(r.createImplT(LABEL, "end"));
        addInsn(r.createImplT(RETURN));

    }

    void NekoFunction::execute(Runtime& r) {
        NekoStack stack;

        // TODO: If non-static (instanced),
        //  add `self/this` to top of Stack
//        auto retVal = nullptr;

        // Loop through all instructions
        for (size_t i = 0; i < instructions.size();) {
            // Cache current instruction index
            auto tmp = i + 0; // ugly hack for false CLion warning

            // Get current instruction
            auto& insn = instructions[i];

            // Execute current instruction
            long long next = insn->execute(r, stack, i);

            // Check if we returned from the function
            if (next == NekoOp::HALT_EXECUTION) {
                // Return from function
                println("Return from function");
                break;
            }

            // Check if we didn't jump (= go to next instruction)
            if (tmp == i)
                i++;

            // ^ Otherwise we probably jumped using i=...
        }

        // TODO: Do something with return value
    }

    void NekoFunction::addInsn(unique_ptr<NekoOp>&& insn) {
        instructions.emplace_back(std::move(insn));
    }

    void NekoFunction::addLabel(unique_ptr<NekoOp>&& insn) {
        auto labelId = insn.get()->getArgString();
        labels[labelId] = instructions.size();
        instructions.emplace_back(std::move(insn));
    }

}