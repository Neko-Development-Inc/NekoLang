#include "NekoOp.h"

namespace ops {
class NekoOpReturn : public NekoOp {

public:
    explicit NekoOpReturn()
            : NekoOp(RETURN) {}

    explicit NekoOpReturn(short opcode)
            : NekoOp(opcode) {}

    std::unique_ptr<NekoOp> clone() const override {
        return std::make_unique<NekoOpReturn>(*this);
    }

    long long execute(Runtime& r, NekoStack& s, size_t& i) override {
        println("NekoOpReturn");
        return HALT_EXECUTION;
    }

};
}