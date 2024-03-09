#include "NekoOp.h"

namespace ops {
class NekoOpPop : public NekoOp {

public:
    explicit NekoOpPop(Opcodes& ops)
            : NekoOp(POP, ops) {}

    explicit NekoOpPop(short opcode, Opcodes& ops)
            : NekoOp(opcode, ops) {}

    std::unique_ptr<NekoOp> clone() const override {
        return std::make_unique<NekoOpPop>(*this);
    }

    long long execute(Runtime& r, NekoStack& s, size_t& i) override {
        println("NekoOpPop");
        int n = 1;
        if (!args.empty()) {
            auto first = args[0];
            if (!first.has_value()) {
                errorln("Error: NekoOpPop args was empty");
                exit(1);
            }
            const auto& type = first.type();
            if (type != typeid(_NekoNumberType_)) {
                errorln("Error: NekoOpPop args[0] wasn't a number, "
                        "it was: '", type.name(), "'");
                exit(1);
            }
            n = std::any_cast<_NekoNumberType_>(first);
        }
        errorln("\tRunning pops ", n, " times");
        while (n--) {
            auto result = s.pop(); // Pop the top of the stack, and discard it
            if (!result.success) {
                errorln("Error: NekoOpPop: Stack is already empty, can't pop again.");
                exit(1);
            }
        }
        return CONTINUE_EXECUTION;
    }

};
}