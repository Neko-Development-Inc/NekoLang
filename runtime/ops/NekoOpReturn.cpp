#pragma once
#ifndef NEKO_OP_RETURN_H
#define NEKO_OP_RETURN_H

#include "NekoOp.h"
#include "../../utils/utils.h"

using runtime::Runtime;

namespace ops {
class NekoOpReturn : public NekoOp {

public:
    explicit NekoOpReturn(short opcode)
            : NekoOp(opcode) {}

    void execute(const Runtime &r) override {
        // Return from the current executing function
        println("NekoOpReturn");
    }

};
}

#endif //NEKO_OP_RETURN_H