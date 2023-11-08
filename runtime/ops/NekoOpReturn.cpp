#pragma once
#ifndef NEKO_OP_RETURN_H
#define NEKO_OP_RETURN_H

#include "NekoOp.h"

using runtime::Runtime;
using vm::NekoStack;

namespace ops {
class NekoOpReturn : public NekoOp {

public:
    explicit NekoOpReturn(short opcode)
            : NekoOp(opcode) {}

    void execute(Runtime* r, NekoStack* s) override {
        // Return from the current executing function
        println("NekoOpReturn");
    }

};
}

#endif //NEKO_OP_RETURN_H