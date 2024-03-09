#include "NekoOp.h"

namespace ops {
class NekoOpCs : public NekoOp {

public:
    explicit NekoOpCs(Opcodes& ops)
            : NekoOp(CS, ops) {}

    explicit NekoOpCs(short opcode, Opcodes& ops)
            : NekoOp(opcode, ops) {}

    std::unique_ptr<NekoOp> clone() const override {
        return std::make_unique<NekoOpCs>(*this);
    }

    _OpsNumberIndexType_ execute(Runtime& r, NekoStack& s, size_t& i) override {
        println("NekoOpCs");
        println("NekoOpCs: Stack size before CS: ", s.count());
        s.clear();
        println("NekoOpCs: Stack size after CS: ", s.count());
        return CONTINUE_EXECUTION;
    }

};
}