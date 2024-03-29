#include "NekoOp.h"

class ops::NekoOpBool : public NekoOp {

public:
    explicit NekoOpBool(Opcodes& ops)
            : NekoOp(BOOL, ops) {}

    explicit NekoOpBool(short opcode, Opcodes& ops)
            : NekoOp(opcode, ops) {}

    std::unique_ptr<NekoOp> clone() const override {
        return std::make_unique<NekoOpBool>(*this);
    }

    _OpsNumberIndexType_ execute(Runtime& r, NekoStack& s, size_t& i) override {
        println("NekoOpBool");
        if (args.empty()) {
            errorln("Error: NekoOpBool args was empty");
            exit(1);
        }
        auto first = args[0];
        if (!first.has_value()) {
            errorln("Error: NekoOpBool args was empty");
            exit(1);
        }
        const auto& type = first.type();
        if (type != typeid(bool)) {
            errorln("Error: NekoOpBool args[0] expected bool, ",
                    "but found '", type.name(), "'");
            exit(1);
        }
        s.add(any_cast<bool>(first), T_BOOL);
        return CONTINUE_EXECUTION;
    }

};