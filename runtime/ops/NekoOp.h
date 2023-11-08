#pragma once
#ifndef NEKO_OP_H
#define NEKO_OP_H

#include <string>
#include "../../utils/utils.h"

using std::string, std::to_string;

namespace runtime {
    class Runtime;
}

namespace vm {
    class NekoStack;
}

namespace ops {
class NekoOp {
public:
    const short opcode;
    explicit NekoOp(short op) :
            opcode(op) { }
    virtual void execute(const runtime::Runtime&, const vm::NekoStack&)
        = 0;
};
}

#endif //NEKO_OP_H