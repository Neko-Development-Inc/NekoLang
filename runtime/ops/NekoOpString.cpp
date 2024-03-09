#include "NekoOp.h"

class ops::NekoOpString : public NekoOp {

public:
    explicit NekoOpString(Opcodes& ops)
            : NekoOp(STRING, ops) {}

    explicit NekoOpString(short opcode, Opcodes& ops)
            : NekoOp(opcode, ops) {}

    std::unique_ptr<NekoOp> clone() const override {
        return std::make_unique<NekoOpString>(*this);
    }

    long long execute(Runtime& r, NekoStack& s, size_t& i) override {
        println("NekoOpString");
        if (args.empty()) {
            errorln("Error: NekoOpString args was empty");
            exit(1);
        }
        auto first = args[0];
        if (!first.has_value()) {
            errorln("Error: NekoOpString args was empty");
            exit(1);
        }
        const auto& type = first.type();
        if (type == typeid(const char *)) {
            s.add(std::any_cast<const char *>(first), T_STRING);
            return CONTINUE_EXECUTION;
        } else if (type == typeid(string)) {
            s.add(any_cast<string>(first), T_STRING);
            return CONTINUE_EXECUTION;
        }
        errorln("Error: NekoOpString args[0] wasn't a string, ",
                "it was: '", type.name(), "'");
        exit(1);
    }

};