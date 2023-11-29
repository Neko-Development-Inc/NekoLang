#pragma once

#ifndef NEKO_OP_RETURN_H
#define NEKO_OP_RETURN_H

#include "NekoOp.h"

namespace ops {
class NekoOpReturn : public NekoOp {

public:
    explicit NekoOpReturn(short opcode)
            : NekoOp(opcode) {}

    void execute(Runtime& r, vm::NekoStack& s) override {
        // TODO: Return from the current executing function
        //int count = s->count();
        cout << "NekoOpReturn\n";
    }

};
}

#endif //NEKO_OP_RETURN_H