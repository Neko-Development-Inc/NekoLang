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
        s.pop(); // Pop the top of the stack, and discard it
    }

};
}

#endif //NEKO_OP_POP_H