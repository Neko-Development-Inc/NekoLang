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

    void execute(Runtime& r, NekoStack& s) override {
        cout << "NekoOpPop\n";

        int n = 1;
        if (!args.empty()) {
            auto first = args[0];
            if (!first.has_value()) {
                cerr << "Error: NekoOpPop args was empty\n";
                exit(1);
            }
            const auto& type = first.type();
            if (type != typeid(int)) {
                cerr << "Error: NekoOpPop args[0] wasn't a number, "
                        "it was: '" << type.name() << "'\n";
                exit(1);
            }
            n = std::any_cast<int>(first);
        }
        cout << "\tRunning pops " << n << " times\n";
        while (n--) {
            auto result = s.pop(); // Pop the top of the stack, and discard it
            if (!result.success) {
                cerr << "Error: NekoOpPop: Stack is already empty, can't pop again.\n";
                exit(1);
            }
        }
    }

};
}

#endif //NEKO_OP_POP_H