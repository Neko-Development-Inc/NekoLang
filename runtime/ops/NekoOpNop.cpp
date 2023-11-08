#pragma once
#ifndef NEKO_OP_NOP_H
#define NEKO_OP_NOP_H

#include "NekoOp.h"

using runtime::Runtime;
using vm::NekoStack;

namespace ops {
class NekoOpNop : public NekoOp {

public:
    explicit NekoOpNop(short opcode)
            : NekoOp(opcode) {}

    void execute(const Runtime &r, const NekoStack &s) override {
        // Do nothing
        println("NekoOpNop");
    }

};
}

#endif //NEKO_OP_NOP_H