#include "NekoOp.h"

namespace ops {
class NekoOpNop : public NekoOp {

public:
    explicit NekoOpNop()
        : NekoOp(NOP) {}

    std::unique_ptr<NekoOp> clone() const override {
        return std::make_unique<NekoOpNop>(*this);
    }

    long int execute(Runtime& r, NekoStack& s, size_t& i) override {
        // Do nothing
        println("NekoOpNop");
        return 0;
    }

};
}