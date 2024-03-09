#include "NekoOp.h"

namespace ops {
class NekoOpLabel : public NekoOp {

public:
    explicit NekoOpLabel(Opcodes& ops)
            : NekoOp(LABEL, ops) {}

    explicit NekoOpLabel(short opcode, Opcodes& ops)
            : NekoOp(opcode, ops) {}

    std::unique_ptr<NekoOp> clone() const override {
        return std::make_unique<NekoOpLabel>(*this);
    }

    long long execute(Runtime& r, NekoStack& s, size_t& i) override {
        println("NekoOpLabel");
        return CONTINUE_EXECUTION;
    }

};
}