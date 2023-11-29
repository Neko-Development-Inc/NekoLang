#pragma once

#include "../../headers.h"

namespace ops {
class NekoOp {
public:
    const short opcode;
    explicit NekoOp(short op) :
            opcode(op) { }
    virtual void execute(runtime::Runtime&, vm::NekoStack&)
        = 0;
    virtual ~NekoOp() = default;
};
}