#include "NekoOp.h"

namespace ops {
class NekoOpLabel : public NekoOp {

public:
    explicit NekoOpLabel()
            : NekoOp(LABEL) {}

    explicit NekoOpLabel(short opcode)
            : NekoOp(opcode) {}

    std::unique_ptr<NekoOp> clone() const override {
        return std::make_unique<NekoOpLabel>(*this);
    }

    long long execute(Runtime& r, NekoStack& s, size_t& i) override {
        println("NekoOpLabel");
        return CONTINUE_EXECUTION;
    }

};
}