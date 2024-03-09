#include "NekoOp.h"

namespace ops {
class NekoOpNop : public NekoOp {

public:
    explicit NekoOpNop(Opcodes& ops)
            : NekoOp(NOP, ops) {}

    explicit NekoOpNop(short opcode, Opcodes& ops)
            : NekoOp(opcode, ops) {}

    std::unique_ptr<NekoOp> clone() const override {
        return std::make_unique<NekoOpNop>(*this);
    }

    _OpsNumberIndexType_ execute(Runtime& r, NekoStack& s, size_t& i) override {
        // Do nothing
        println("NekoOpNop");
        return CONTINUE_EXECUTION;
    }

};
}