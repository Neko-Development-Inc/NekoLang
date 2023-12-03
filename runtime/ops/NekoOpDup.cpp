#pragma once

#ifndef NEKO_OP_DUP_H
#define NEKO_OP_DUP_H

#include "NekoOp.h"

namespace ops {
class NekoOpDup : public NekoOp {

public:
    explicit NekoOpDup()
        : NekoOp(DUP) {}

    std::unique_ptr<NekoOp> clone() const override {
        return std::make_unique<NekoOpDup>(*this);
    }

    void execute(Runtime& r, NekoStack& s) override {
        cout << "NekoOpDup\n";
        auto size = s.count();
        auto a = s.pop();
        if (!a.success) {
            cerr << "Error: NekoOpDup: Failed to pop from stack. (Size: " << size << ")\n";
            exit(1);
        }
        cout << "NekoOpDup: Stack size before dup: " << s.count() << "\n";
        auto b = &a.obj;
        if (!b->has_value()) {
            cerr << "Error: NekoOpDup: Optional was empty\n";
            exit(1);
        }
        auto c = **b->value();
        auto d = c; // Copy object
        s.add(&c, a.type); // TODO: This will exit the program, due to
        s.add(&d, a.type); //       wrong types (only support primitives rn)
        cout << "NekoOpDup: Stack size after dup: " << s.count() << "\n";
    }

};
}

#endif //NEKO_OP_DUP_H