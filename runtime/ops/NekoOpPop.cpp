#pragma once

#ifndef NEKO_OP_POP_H
#define NEKO_OP_POP_H

#include "NekoOp.h"

namespace ops {
class NekoOpPop : public NekoOp {

public:
    explicit NekoOpPop()
        : NekoOp(POP) {}

    std::unique_ptr<NekoOp> clone() const override {
        return std::make_unique<NekoOpPop>(*this);
    }

    long int execute(Runtime& r, NekoStack& s, size_t& i) override {
        println("NekoOpPop");
        int n = 1;
        if (!args.empty()) {
            auto first = args[0];
            if (!first.has_value()) {
                errorln("Error: NekoOpPop args was empty");
                exit(1);
            }
            const auto& type = first.type();
            if (type != typeid(int)) {
                errorln("Error: NekoOpPop args[0] wasn't a number, "
                        "it was: '", type.name(), "'");
                exit(1);
            }
            n = std::any_cast<int>(first);
        }
        errorln("\tRunning pops ", n, " times");
        while (n--) {
            auto result = s.pop(); // Pop the top of the stack, and discard it
            if (!result.success) {
                errorln("Error: NekoOpPop: Stack is already empty, can't pop again.");
                exit(1);
            }
        }
        return 0;
    }

};
}

#endif //NEKO_OP_POP_H