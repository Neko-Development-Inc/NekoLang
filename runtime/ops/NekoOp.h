#pragma once
#ifndef NEKO_OP_H
#define NEKO_OP_H

namespace runtime {
    class Runtime;
}

namespace ops {
class NekoOp {
public:
    const short opcode;
    explicit NekoOp(short opcode) :
            opcode(opcode) { }
    virtual void execute(const runtime::Runtime& r)
        = 0;
};
}

#endif //NEKO_OP_H