#include "NekoOp.h"

namespace ops {
class NekoOpReturn : public NekoOp {

public:
    explicit NekoOpReturn(Opcodes& ops)
            : NekoOp(RETURN, ops) {}

    explicit NekoOpReturn(short opcode, Opcodes& ops)
            : NekoOp(opcode, ops) {}

    std::unique_ptr<NekoOp> clone() const override {
        return std::make_unique<NekoOpReturn>(*this);
    }

    _OpsNumberIndexType_ execute(Runtime& r, NekoStack& s, size_t& i) override {
        println("NekoOpReturn");
        return HALT_EXECUTION;
    }

};
}