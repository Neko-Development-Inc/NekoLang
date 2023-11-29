#pragma once

#ifndef NEKO_OP_NOP_H
#define NEKO_OP_NOP_H

#include "NekoOp.h"

namespace ops {
class NekoOpNop : public NekoOp {

public:
    explicit NekoOpNop(short opcode)
            : NekoOp(opcode) {}

    void execute(Runtime& r, vm::NekoStack& s) override {
        // Do nothing
        cout << "NekoOpNop\n";
        //s->count();
    }

};
}

#endif //NEKO_OP_NOP_H