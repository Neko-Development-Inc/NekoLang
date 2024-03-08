#include "NekoOp.h"

namespace ops {
class NekoOpNop : public NekoOp {

public:
    explicit NekoOpNop()
        : NekoOp(NOP) {} // TODO: Test if we need `ops[...]` here aswell (and for all other opcodes)

    explicit NekoOpNop(short opcode)
            : NekoOp(opcode) {}

    std::unique_ptr<NekoOp> clone() const override {
        return std::make_unique<NekoOpNop>(*this);
    }

    long long execute(Runtime& r, NekoStack& s, size_t& i) override {
        // Do nothing
        println("NekoOpNop");
        return CONTINUE_EXECUTION;
    }

};
}